#include "mainwindow.h"
#include "ui_mainwindow.h"

// Encode and decode
// by Diffie - Halman

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

int MainWindow::search(QString& a, QString b)
{
    int len = a.size();

    for(int i(0); i<len; i++)
    {
        if(a.at(i) == b)
        {
            return i;
        }
    }
    return -1;
}

int MainWindow::Ost(int a, int x, int p) {
     int res = 1;
     for (int i = 1; i <= x; i++)
     {
         res *= a;
         res = res % p;
     }
     return res;
}

void MainWindow::on_KeyGen_clicked()
{
    int p = ui->spin_p->text().toInt();
    int g = ui->spin_g->text().toInt();
    int xa =ui->spin_xa->text().toInt();
    int xb =ui->spin_xb->text().toInt();
    int ya = Ost(g, xa, p);
    int yb = Ost(g, xb, p);
    int key_a = Ost(yb, xa, p);
    int key_b = Ost(ya, xb, p);

    ui->ya->setText(QString::number(ya));

    ui->yb->setText(QString::number(yb));

    ui->keya->setText(QString::number(key_a));

    ui->keyb->setText(QString::number(key_b));

}

// в этих функциях мы будем кодировать слово
// используя лишь один ключ
void MainWindow::on_encodeButton_clicked()
{
    QString* input = new QString[128];
    *input = ui->inputLine->text();
    QString spamInput = ui->inputLine->text();
    QString out;
    int j;

    int key = ui->keya->text().toInt();

    for(int i(0); i< spamInput.size(); i++)
    {
        j = search(spamInput, spamInput.at(i));
        if(j == -1)
        {
           out += spamInput.at(i);
        }
        else
        {
            out += (*input).at((j + key) % ((*input).size()));
            ui->inputLine->setText(out);
        }
    }
    ui->inputLine->setText(out);

    input = nullptr;
}


void MainWindow::on_decodeButton_clicked()
{
    QString* input = new QString[128];
    *input = ui->inputLine->text();
    QString spamInput = ui->inputLine->text();
    QString out;
    int j;

    int key = ui->keya->text().toInt();

    for(int i(0); i< spamInput.size();i++)
    {
        // индекс i-го символа в алфавите
        j = search(spamInput, spamInput.at(i));
        if(j == -1)
        {
            out += spamInput.at(i);
        }
        else
        {
            out += (*input).at((j + key) % ((*input).size()));
        }
    }
    ui->inputLine->setText(out);

    input = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}
