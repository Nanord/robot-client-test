#include "tcpcontrol.h"


TcpControl::TcpControl(QObject *parent) : QObject(parent)
{
    //const QString& strHost, quint16 port
   // this->host = strHost;
    //this->port = port;

    server = new QTcpServer(this);
    QString log = " server listen port = " + QString::number(port);
    server->listen(QHostAddress::Any, port);
    qDebug() << log;
    connect(server, SIGNAL(newConnection()), this, SLOT(incommingConnection())); // подключаем сигнал "новое подключение" к нашему обработчику подключений
    connect(server, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    qDebug()<<"start 2 conectted";
}

void TcpControl::socketReady() {

     qDebug() << "ready";
    if(socket->waitForConnected(100000)) {
        socket->waitForReadyRead(1000);
        //QByteArray *data = new QByteArray();
        //*data = tcpSocket->readAll();
        QByteArray data = socket->readAll();

        qDebug() << data;
        socket->flush();
    }
}

void TcpControl::socketDisconnected() {
    qDebug() << "disc";
    socket->deleteLater();
}

void TcpControl::incommingConnection() // обработчик подключений
{
    while (server->hasPendingConnections()) {
        socket = server->nextPendingConnection();
        connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
        connect(socket, SIGNAL(readyRead()), this, SLOT(socketReady()));
        socket->write("server hello");
        socket->flush();
    }
}

QAbstractSocket::SocketState TcpControl::stateChanged(QAbstractSocket::SocketState state) // обработчик статуса, нужен для контроля за "вещающим"
{
    if(socket == nullptr) {
        return QAbstractSocket::SocketState::ClosingState;
    }
    if(socket->state() == QTcpSocket::ConnectedState) {
    } else {
    }
    qDebug() << state;
    return state;
}

QAbstractSocket::SocketError TcpControl::onError(QAbstractSocket::SocketError error)
{
    QString strErorr = "ERROR: " + error;
    qDebug() << strErorr;
    return error;
}
