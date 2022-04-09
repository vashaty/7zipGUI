#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
#include <QDirIterator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbDir_clicked();

    void on_pbStart_clicked();

    void readyToRead();

    void statusChanged(QProcess::ProcessState state);

private:
    Ui::MainWindow *ui;
    QProcess process;
    QString sevenZip = "7za.exe";
    QFileInfoList archives;
};
#endif // MAINWINDOW_H
