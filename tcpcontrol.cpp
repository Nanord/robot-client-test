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
        QString commandClient = data;
        commandClient = commandClient.split(";").at(0);

        //QRegExp re("((\\d{1,3}\\.\\d{1,3})|(\\d{1,3}))");
        //re.indexIn(commandClient);
        //QStringList listXYZ = re.capturedTexts();
        //qDebug() << "STRING" << listXYZ.join(",") << listXYZ.length();
        //if (listXYZ.length() >= 3) {
//        float x = listXYZ.at(0).isNull()? listXYZ.at(0).toFloat() : 0;
//        float y = listXYZ.at(1).isNull()? listXYZ.at(0).toFloat() : 0;
//        float z = listXYZ.at(2).isNull()? listXYZ.at(0).toFloat() : 0;

        int pos = 0;
        QRegExp rx("((\\d{1,3}\\.\\d{1,3})|(\\d{1,3}))");
        QStringList line;
        while ((pos = rx.indexIn(commandClient, pos)) != -1) {
            line.append(rx.cap(1));
            pos += rx.matchedLength();
        }
        //qDebug() << line;
        float x = !line.at(0).isNull()? line.at(0).toFloat() : 0;
        float y = !line.at(1).isNull()? line.at(0).toFloat() : 0;
        float z = !line.at(2).isNull()? line.at(0).toFloat() : 0;
        x = x > 0 ? static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/x)) : 0;
        y = y > 0 ? static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/y)) : 0;
        z = z > 0 ? static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/z)) : 0;
        QString sendData = "POS=x" + QString::number(x) +",y:" + QString::number(y) +",z:" + QString::number(z) +";";
        qDebug() << "SERVER SEND POS" << sendData ;
        socket->write(sendData.toUtf8());
        socket->flush();



        int g1 = 1+ rand() % 100;
        int g2 = 1+ rand() % 100;
        int g3 = 1+ rand() % 100;
        int g4 = 1+ rand() % 100;
        QString sendData2 = "GAZ=g:" + QString::number(g1) +",g:" + QString::number(g2) +",g:" + QString::number(g3) +",g:" + QString::number(g4)+";";
        socket->write(sendData2.toUtf8());
        qDebug() << "SERVER SEND GAZ" << sendData2 ;
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
