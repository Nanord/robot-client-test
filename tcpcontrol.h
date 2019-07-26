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
    quint16 port = 7676;//текущий размер блока данных
    QString host;//имя сервера

public:
    QTcpSocket *socket; //сокет
    QTcpServer *server; // указатель на сервер

public slots:
    void incommingConnection(); // обработчик входящего подключения
    QAbstractSocket::SocketState stateChanged(QAbstractSocket::SocketState stat); // обработчик изменения состояния вещающего
    QAbstractSocket::SocketError onError(QAbstractSocket::SocketError socketError);
    void socketReady();
    void socketDisconnected();

};

#endif // TCPCONTROL_H
