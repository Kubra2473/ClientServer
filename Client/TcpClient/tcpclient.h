#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QTcpSocket>
#pragma execution_character_set("utf-8")
#include <QWidget>
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
namespace Ui { class TcpClient; }
QT_END_NAMESPACE

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
    QImage image;

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonclicked_clicked();
    void ReadData();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TcpClient *ui;
    QTcpSocket* socket;
};
#endif // TCPCLIENT_H
