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
    void Connect();
    void sendMessage(QString);
    QString getMessage();
private:
    QTcpSocket *mSocket;
    QString text;
};

#endif // TCPCLIENT_H
