#include "mainwindow.h"
#include "ui_mainwindow.h"

string inputFile, outputFile, keyFile;
QString infile, outfile, kfile;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ifstream input;
    input.open(inputFile.c_str(), ios::binary);
    ofstream output;
    output.open(outputFile.c_str(), ios::binary);
    ifstream key;
    key.open(keyFile.c_str());
    if(!input.is_open())
    {
        QMessageBox::information(this,"Error!","Can't open input file!");
        return;
    }
    if(!output.is_open())
    {
        QMessageBox::information(this,"Error!","Can't open output file!");
        return;
    }
    if(!key.is_open())
    {
            QMessageBox::information(this,"Error!","Can't open key file!");
            return;
    }

    long long pos;
    char * buffer;
    buffer = new char;
    char *message_byte;
    message_byte = new char;

    input.read(buffer, sizeof(char));
    while (!input.eof())
    {
        output.write(buffer, sizeof(char)); //заголовок копируем без изменений
        input.read(buffer, sizeof(char));
        pos = input.tellg();
        if (pos == 100)
        {
            while (!key.eof())
            {
                key.read(message_byte, sizeof(char)); //считываем байт сообщения
                for (int bitIndex = 0; bitIndex < 8; bitIndex++) //записываем каждый из 8 битов каждого байта информации
                {
                    input.read(buffer, sizeof(char)); //считываем байт исходного wav
                    if (*message_byte & 1 << bitIndex) //если текущий бит сообщения == 1
                        *buffer |= 1 << 0; //меняем наименее значащий бит wav данных на 1
                    else //если текущий бит == 0
                        *buffer &= ~(1 << 0); //меняем наименее значащий бит wav данных на 0
                    output.write(buffer, sizeof(char)); //записываем измененный байт данных в выходной wav файл
                }
            }
        }
    }

    input.close();
    output.close();
    key.close();
     QMessageBox::information(this,"Succes!","File is crypted!");
}

void MainWindow::on_Open1_clicked()
{
    infile = QFileDialog::getOpenFileName(this,tr("Открыть файл"),"/Users/","Allfiles(*)");
    inputFile = infile.toStdString();
    ui->label_4->setText(infile);
}

void MainWindow::on_Save_clicked()
{
    outfile = QFileDialog::getSaveFileName(this,tr("Открыть файл"),"/Users/","Allfiles(*)");
    outputFile = outfile.toStdString();
    ui->label_5->setText(outfile);
}

void MainWindow::on_Open2_clicked()
{
    kfile = QFileDialog::getOpenFileName(this,tr("Открыть файл"),"/Users/","Allfiles(*)");
    keyFile = kfile.toStdString();
    ui->label_6->setText(kfile);
}
