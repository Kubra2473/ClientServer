#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QBuffer>
#include <QFileDialog>
#include <iostream>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class TcpServer; }
QT_END_NAMESPACE

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

private slots:
    void on_pushButtonListen_clicked();

    void on_pushButtonServerGonder_clicked();

private:
    Ui::TcpServer *ui;
    QTcpServer* server;
    QTcpSocket* socket;//A client corresponds to a socket
    void ClientConnect();
    void ReadData1();
};
#endif // TCPSERVER_H
