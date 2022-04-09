#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    if(dir != ""){
        ui->leFolderPath->setText(dir);

    }
}


void MainWindow::on_pbStart_clicked()
{
    QDir dir(ui->leFolderPath->text());

    QFileInfoList archives = dir.entryInfoList(QStringList() << "*.7z" << "*.zip",QDir::Files);

    foreach(QFileInfo file, archives) {
        ui->pteOutput->appendPlainText(file.absoluteFilePath());
//        sevenZip.start();
    }
}

