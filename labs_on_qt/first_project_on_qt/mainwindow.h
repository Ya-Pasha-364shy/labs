#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        int Ost(int a, int x, int p);
        int search(QString& a, QString b);
        ~MainWindow();

    private slots:
        void on_KeyGen_clicked();

        void on_encodeButton_clicked();

        void on_decodeButton_clicked();

private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
