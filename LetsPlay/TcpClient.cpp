#include "TcpClient.h"

TcpClient::TcpClient()
{
}

void TcpClient::Connect()
{
    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::readyRead, [&]() {
        QTextStream T(mSocket);
        text = T.readLine();

    });

    mSocket->connectToHost("localhost", 54000);
}

void TcpClient::sendMessage(QString data_json)
{
    QTextStream T(mSocket);
    T << data_json;
    mSocket->flush();
}

QString TcpClient::getMessage()
{
    return text;
}
