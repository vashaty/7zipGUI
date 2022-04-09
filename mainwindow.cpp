#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDirIterator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&process, &QProcess::readyReadStandardOutput, this, &MainWindow::readyToRead);
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
    QFileInfoList archives;

    if(ui->cbRecursive->isChecked()){
        QDirIterator it(ui->leFolderPath->text(), QStringList() << "*.7z" << "*.zip", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()){
            archives.append(QFileInfo(it.next()));
        }
    }else{
        archives = dir.entryInfoList(QStringList() << "*.7z" << "*.zip",QDir::Files);
    }


    foreach(QFileInfo file, archives) {
//        ui->pteOutput->appendPlainText(file.absoluteFilePath());
        QStringList args;
        args << "x";
        args << "-y";
        args << "-o" + file.absolutePath() + "/"+ file.baseName();
        args << file.absoluteFilePath();

        process.start(sevenZip,args);
        process.waitForFinished();

    }
}

void MainWindow::readyToRead()
{
    ui->pteOutput->appendPlainText(process.readAllStandardOutput());
}

