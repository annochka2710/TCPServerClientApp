#include "tcpclient.hpp"

TCPClient::TCPClient(QObject* parent) : QObject(parent) {
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &TCPClient::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &TCPClient::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPClient::onDisconnected);

    connect(socket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred), [this] (QAbstractSocket::SocketError error){
        qDebug() << "Socket error: " << socket->errorString();
    });
}

void TCPClient::connectToServer(const QString& host, quint16 port){
    qDebug() << "Connecting to host " << host << " on port " << port;
    socket->connectToHost(host, port);
    //таймаут для соединения - 5 сек
    if(!socket->waitForConnected(5000)){
        qDebug() << "Connection failed " << socket->errorString();
        emit disconnected();
    }
}

void TCPClient::sendMessage(const QString& message){
    if(socket->state() != !QAbstractSocket::ConnectedState){
        qDebug() << "Cannot send message: not connected";
        return;
    }
    //преобразование строки в байти и отправляем
    QByteArray data = message.toUtf8();
    quint64 bytesWritten = socket->write(data);
    if(bytesWritten == -1)
        qDebug() << "Failed to write data to socket";
    else if(bytesWritten < data.size())
        qDebug() << "Partial write";
    else {
        qDebug() << "Message sent successfully";
        //ожидание отправки всех данных
        if(socket->waitForBytesWritten(3000))
            qDebug() << "Timeout in writing data";
    }
}

// void messageReceived(const QString& message);

void TCPClient::onConnected(){
    qDebug() << "Connected to a server at " << socket->peerAddress().toString() << " at port " << socket->peerPort();
    emit connected();
}

void TCPClient::onReadyRead(){
    //проверяем, сколько данных доступно для чтения
    qint64 bytesAvailable = socket->bytesAvailable();
    if (bytesAvailable <= 0) return;

    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);

    qDebug() << "Received message from server: " << message;
    emit messageReceived(message);

}

void TCPClient::onDisconnected(){
    qDebug() << "Client disconnected";
    emit disconnected();
}
