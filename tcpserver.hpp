#pragma once
#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);
    bool startServer(quint16 port);
    void stopServer();
    QStringList getClients() const;

private slots:
    void newConnection();
    void readyRead();
    void clientDisconnected();

private:
    QTcpServer *server; //сокет-сервер
    QList<QTcpSocket*> clients;
};

#endif // TCPSERVER_HPP
