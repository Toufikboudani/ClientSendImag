#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTcpSocket;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:

public slots:

private slots:
    void on_Connected();
    void on_Disconnected();
    void on_pushButton_connect_clicked();
    void readyRead();
private:
    QTcpSocket *m_Socketclient;
    QPixmap m_Pixmapimage;
    QByteArray imageData;

    bool hasReadImageHead;
    long GraceSizeImage;
    int testImage;

 };

#endif // MAINWINDOW_H
