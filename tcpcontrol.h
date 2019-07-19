#ifndef TCPCONTROL_H
#define TCPCONTROL_H

#include <QtNetwork>
#include <QTcpSocket>
#include <QDebug>

class TcpControl :public QObject
{
    Q_OBJECT
public:
    TcpControl(QObject *parent=nullptr);
    //TcpControl();
    quint16 port;//текущий размер блока данных
    QString host;//имя сервера

public:
    QTcpSocket *tcpSocket; //сокет

public slots:
    void socketReady();
    void socketDisconnected();

};

#endif // TCPCONTROL_H
