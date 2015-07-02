#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <iostream>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QtGui>
#include <QTextStream>
#include <string>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_Open1_clicked();

    void on_Save_clicked();

    void on_Open2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
