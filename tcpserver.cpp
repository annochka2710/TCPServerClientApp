#include "tcpserver.hpp"

TCPServer::TCPServer(QObject* parent) : QObject(parent)  {
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &TCPServer::newConnection);
}

//запуск сервера
bool TCPServer::startServer(quint16 port){
    //сокет слушает на любом IP-адресе по любому порту
    if(!server->listen(QHostAddress::Any, port)){
        qDebug() << "Server didn't start " << server->errorString();
        return false;
    }
    //получаем дескриптор сервера
    quintptr desriptor = server->socketDescriptor();
    qDebug() << "Server started on port " << port;
    qDebug() << "Server socket descriptor  " << desriptor;
    return true;
}

//слот - добавление нового соединения
void TCPServer::newConnection(){
    QTcpSocket *socket = server->nextPendingConnection();
    //ОС создает новый сокет и дескриптор для сокета клиента
    clients.append(socket);
    //сокет привязан к слоту сервера через readyRead
    connect(socket, &QTcpSocket::readyRead, this, &TCPServer::readyRead);
    //отключение клиента
    connect(socket, &QTcpSocket::disconnected, this, &TCPServer::clientDisconnected);
    qDebug() << "New client connected at address " << socket->peerAddress().toString();
}

//слот - читаем данные от клиента
//Сокет -> ОС -> Дескриптор клиента
void TCPServer::readyRead(){
    //1.определяем отправителя
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    //2. проверка данных
    if(!socket || socket->bytesAvailable() > 0){
        qDebug() << "No socket for ready read in server";
        return;
    }
    if(socket->bytesAvailable() > 1024 * 1024){
        socket->disconnectFromHost();
        qDebug() << "Too big data";
        return;
    }
    //3. читаем данные
    QByteArray data = socket->readAll();
    //4. логирование
    qDebug() << "Data from socket descriptor: " << socket->socketDescriptor();
    qDebug() << "Received data in server: " << data;
    //5. отправка ответа (Эхо)
    socket->write(QString("Server received: %1").arg(QString(data)).toUtf8());
}

//остановка сервера
void TCPServer::stopServer(){
    foreach(QTcpSocket* client, clients){
        client->disconnectFromHost();
    }
    server->close();
    qDebug() << "Server stopped";
}

//слот - клиент отсоединился
void TCPServer::clientDisconnected(){
    //1. определяем сокет клиента
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(!socket) return;
    //2. удаляем из списка clients
    clients.removeAll(socket); //to remove all occurrences of a specific value from a QList
    //безопасное удаление
    socket->deleteLater(); //event loop will delete the object after all pending events have been delivered to it
    qDebug() << "Client disconnected " << socket->peerAddress().toString();
}

//---------------------------additional functions---------------------------

QStringList TCPServer::getClients() const{
    QStringList list;
    foreach(QTcpSocket* client, clients)
        list << client->peerAddress().toString();
    return list;
}
