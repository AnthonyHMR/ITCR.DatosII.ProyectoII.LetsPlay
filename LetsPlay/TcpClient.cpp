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

void TcpClient::sendMessage(QJsonObject obj)
{
    QByteArray data_json;
    QJsonDocument doc;

    doc.setObject(obj);
    data_json = doc.toJson();

    QTextStream T(mSocket);
    T << data_json;
    mSocket->flush();
}
