#include "mainwindow.h"
#include "ui_mainwindow.h"

// Encoding and Decoding
// by RSA

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

int power(int a, int b, int m)
{
    int res = 1;
    while (b > 0)
        if (b & 1) {
            res = (res * a) % m;
            --b;
        }
        else {
            a = (a * a) % m;
            b >>= 1;
        }
    return res % m;
}

void MainWindow::on_decode_clicked()
{
    int p = ui->pb->text().toInt();
    int q = ui->qb->text().toInt();
    int d = ui->db->text().toInt();
    int n = ui->nb->text().toInt();

    // Боб делает свой ключ
    int c;
    for (int i = 0; ; i++)
    {
        if (i * d % ((p - 1) * (q - 1)) == 1) {
            c = i;
            break;
        }
        else
            continue;
    }

    int message = ui->inputData->text().toInt();
    // и декодирует сообщение
    int output = power(message, c, n);

    ui->lineDec->setText(QString::number(output));
}

void MainWindow::on_encode_clicked()
{
    int p = ui->pBox->text().toInt();
    int q = ui->qBox->text().toInt();
    int d = ui->dBox->text().toInt();

    // личный ключ Алисы
    int c;
    for (int i = 0; i < 10; i++)
    {
        if (i * d % ((p - 1) * (q - 1)) == 1) {
            c = i;
            break;
        }
        else
            continue;
    }
    // сообщение которое она хочет закодировать
    int message = ui->inputData->text().toInt();

    int bobsD = ui->db->text().toInt();
    int bobsN = ui->nb->text().toInt();
    // Алиса кодирует сообщение
    int result = power(message, bobsD, bobsN);
    // выводим его
    ui->lineEnc->setText(QString::number(result));

}

MainWindow::~MainWindow()
{
    delete ui;
}
