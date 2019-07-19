#include "tcpcontrol.h"


TcpControl::TcpControl(QObject *parent) : QObject(parent)
{
    //const QString& strHost, quint16 port
   // this->host = strHost;
    //this->port = port;

    tcpSocket = new QTcpSocket(this);
    qDebug()<<"start 1";
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(socketReady()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

    tcpSocket->connectToHost("localhost", 7777);
    qDebug()<<"start 2 conectted";
}

void TcpControl::socketReady() {

     qDebug() << "ready";
    if(tcpSocket->waitForConnected(1000)) {
        tcpSocket->waitForReadyRead(1000);
        //QByteArray *data = new QByteArray();
        //*data = tcpSocket->readAll();
        QByteArray data = tcpSocket->readAll();

        qDebug() << data;
    }
}

void TcpControl::socketDisconnected() {
    qDebug() << "disc";
    tcpSocket->deleteLater();
}
