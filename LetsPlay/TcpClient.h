#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

class TcpClient : public QObject
{
public:
    TcpClient();
    void sendMessage(QJsonObject);
private:
    QTcpSocket *mSocket;
};

#endif // TCPCLIENT_H
