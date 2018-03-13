#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_posCon->setPixmap(QPixmap(":/images/disconnected.png"));
    m_Socketclient= new QTcpSocket(this);
    hasReadImageHead=false;
    connect(m_Socketclient,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(m_Socketclient,SIGNAL(disconnected()),this,SLOT(on_Disconnected()),Qt::DirectConnection);
    connect(m_Socketclient,SIGNAL(connected()),this,SLOT(on_Connected()),Qt::DirectConnection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readyRead()
{
    if(!hasReadImageHead){
        imageData.clear();
        QByteArray by=m_Socketclient->readAll();
 //qDebug() <<"QByteArray by,length=" <<  by.size();
        GraceSizeImage=by.left(10).toLong();
        by.remove(0,10);

        imageData.append(by);

        hasReadImageHead=true;

        if(imageData.length()>=GraceSizeImage){

            //qDebug() <<"receive a image,length=" << avalibleNum;
             QImage m_image =QImage::fromData(imageData,"jpg");
           // ============================  // ============================

             QPixmap Pixmap=QPixmap::fromImage(m_image.scaled(ui->labe_image->size()));
             ui->labe_image->setPixmap(Pixmap);


           // ============================  // ============================
             //qDebug() <<" image,width=" << img.width();
             //qDebug() <<" image,height=" << img.height();
            hasReadImageHead=false;
        }
    }else{
        QByteArray by=m_Socketclient->readAll();
         //qDebug() <<"QByteArray by,length=" <<  by.size();
        imageData.append(by);
        if(imageData.length()>=GraceSizeImage){
            //qDebug() <<"receive a image,length=" << avalibleNum;
            QImage m_image =QImage::fromData(imageData,"jpg");
            // ============================  // ============================

            QPixmap Pixmap=QPixmap::fromImage(m_image.scaled(ui->labe_image->size()));
            ui->labe_image->setPixmap(Pixmap);

            // ============================  // ============================

            //qDebug() <<" image,width=" << img.width();
            //qDebug() <<" image,height=" << img.height();
            hasReadImageHead=false;
        }
    }

}


void MainWindow::on_Connected()
{
  ui->label_posCon->setPixmap(QPixmap(":/images/connected.png"));
//    ui->pushButton_Open->setEabled(true);
}

void MainWindow::on_Disconnected()
{
  ui->label_posCon->setPixmap(QPixmap(":/images/disconnected.png"));
  if (m_Socketclient) {
      m_Socketclient->close();
      delete  m_Socketclient;
      m_Socketclient= new QTcpSocket(this);
      hasReadImageHead=false;
      connect(m_Socketclient,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
      connect(m_Socketclient,SIGNAL(disconnected()),this,SLOT(on_Disconnected()),Qt::DirectConnection);
      connect(m_Socketclient,SIGNAL(connected()),this,SLOT(on_Connected()),Qt::DirectConnection);

  }

}


void MainWindow::on_pushButton_connect_clicked()
{
    m_Socketclient->connectToHost(/*host*/"127.0.0.1",/*portIn*/1234);
    m_Socketclient->waitForConnected(100);
}
