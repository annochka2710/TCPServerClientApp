#include <QCoreApplication>
#include <QDebug>
#include <QDebug>

#include "tcpserver.hpp"
#include "tcpclient.hpp"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Call a.quit() or a.exit() to quit the application.

    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    //simple server example
    TCPServer server;
    if(server.startServer(1234)){
        qDebug() << "server is running";
    }

    //simple client example
    TCPClient client;
    QObject::connect(&client, &TCPClient::connected, [](){
        qDebug() << "connected to server";
    });

    client.connectToServer("localhost", 1234);

    return app.exec();
}
