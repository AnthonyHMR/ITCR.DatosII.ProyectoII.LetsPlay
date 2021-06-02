#include "TcpClient.h"

TcpClient::TcpClient()
{
    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::readyRead, [&]() {
        QTextStream T(mSocket);
        auto text = T.readLine();
    });

    mSocket->connectToHost("localhost", 54000);
}

void TcpClient::sendMessage(QByteArray data_json)
{
    QTextStream T(mSocket);
    T << data_json;
    mSocket->flush();
}
