#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&process, &QProcess::readyReadStandardOutput, this, &MainWindow::readyToRead);
    QObject::connect(&timer, &QTimer::timeout,this, &MainWindow::onTimer);
    timer.setSingleShot(false);
//    connect(&process, &QProcess::stateChanged, this, &MainWindow::statusChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QCoreApplication::applicationDirPath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(dir != "")
        ui->leFolderPath->setText(dir);
}


void MainWindow::on_pbStart_clicked()
{
    QDir dir(ui->leFolderPath->text());

    if(dir.exists()){
        if(ui->cbRecursive->isChecked()){
            QDirIterator it(ui->leFolderPath->text(), QStringList() << "*.7z" << "*.zip", QDir::Files, QDirIterator::Subdirectories);
            while (it.hasNext()){
                archives.append(QFileInfo(it.next()));
            }
        }else{
            archives = dir.entryInfoList(QStringList() << "*.7z" << "*.zip",QDir::Files);
        }

        if(process.state() == QProcess::NotRunning && !archives.isEmpty()){
            QFileInfo file = archives.takeFirst();
            QStringList args;
            args << "x";
            args << "-y";
            args << "-o" + file.absolutePath() + "/"+ file.baseName();
            args << file.absoluteFilePath();

            process.start(sevenZip,args);

            timer.start(10);
        }
    }

}

//void MainWindow::statusChanged(QProcess::ProcessState state)
//{
//    if(state == QProcess::NotRunning && !archives.isEmpty()){
//        QFileInfo file = archives.takeFirst();
//        QStringList args;
//        args << "x";
//        args << "-y";
//        args << "-o" + file.absolutePath() + "/"+ file.baseName();
//        args << file.absoluteFilePath();

//        process.start(sevenZip,args);

////        archives.removeFirst();
//    }
//}

void MainWindow::onTimer(){
//    qDebug("hello");
        if(process.state() == QProcess::NotRunning && !archives.isEmpty()){
            QFileInfo file = archives.takeFirst();
            QStringList args;
            args << "x";
            args << "-y";
            args << "-o" + file.absolutePath() + "/"+ file.baseName();
            args << file.absoluteFilePath();

            process.start(sevenZip,args);

        }

        if(archives.isEmpty())
            timer.stop();
}

void MainWindow::readyToRead()
{
    ui->pteOutput->appendPlainText(process.readAllStandardOutput());
}

