#include <QCoreApplication>
#include <tcpcontrol.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //quint16 port = 7676;
    TcpControl * tcpControl = new TcpControl();

    return a.exec();
}
