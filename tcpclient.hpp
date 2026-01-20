#pragma once
#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <QObject>
#include <QTcpSocket>

class TCPClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPClient(QObject *parent = nullptr);
    void connectToServer(const QString& host, quint16 port);
    void sendMessage(const QString& message);

signals:
    void messageReceived(const QString& message);
    void connected();
    void disconnected();

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *socket;
};

#endif // TCPCLIENT_HPP
