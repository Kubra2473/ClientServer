#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QString>
#include <QDebug>
#include "sifrecoz.h"
TcpServer::TcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
   //Client connection signal slot
    connect(server, &QTcpServer::newConnection, this, &TcpServer::ClientConnect);
}

TcpServer::~TcpServer()
{
    server->close();
    server->deleteLater();
}


void TcpServer::on_pushButtonListen_clicked()
{
    if (ui->pushButtonListen->text()=="Listen")
       {
        //Get the port number from the input box
       int port = ui->lineEditPort->text().toInt();
       //Listen for all ip addresses on the specified port
       if (!server->listen(QHostAddress::Any, port))
       {
           //If an error occurs, an error message is output
           qDebug() << server->errorString();
           return;
       }
       //Modify key text
       ui->pushButtonListen->setText("Cancel listening");

    }
    else
    {
        socket->abort();
        //Cancel listening
        server->close();
        //Modify key text
        ui->pushButtonListen->setText("Listen");
    }

}


void TcpServer::on_pushButtonServerGonder_clicked()
{
    if(ui->comboBox->count()== 0)return;
      //QTcpSocket* skt=  (QTcpSocket*)ui.comboBox->itemData(ui.comboBox->currentIndex()).value<int>();
      socket->write(ui->lineEdit->text().toUtf8());

}

void TcpServer::ClientConnect()
{
    //Resolve all customer connections
        while (server->hasPendingConnections())
        {
            //After connecting, obtain the connection information through socket
            socket = server->nextPendingConnection();
            QString str = QString("[ip:%1,port:%2]").arg(socket->peerAddress().toString()).arg(socket->peerPort());
            //Prompt for successful connection
            ui->textEdit->append(str+"Connect to the server");
            //The check box option is the ip address to which the server is connected
            ui->comboBox->addItem(str);
            //Put the socket address into the combobox attribute
            //ui->comboBox->setItemData(ui.comboBox->count()-1, QVariant((int)socket));
            //Monitor whether the client sends a message
            connect(socket, &QTcpSocket::readyRead, this, &TcpServer::ReadData1);
        }

}

void TcpServer::ReadData1()
{
    sifreCoz deneme;
    QByteArray buf = socket->readAll();//readAll can receive up to 65532 data
    //qDebug()<<"gelen veri:"<<buf;//Gelen Veri Ekrana Yazıldı

    QString proje2=QString(buf);
    //qDebug()<<"buferrr:"<<proje2;g

    QJsonDocument jsonDocument = QJsonDocument::fromJson(QByteArray(proje2.toUtf8()));
    //qDebug()<<"jsonnnn:"<<jsonDocument;
     QJsonObject object = jsonDocument.object();
    //qDebug()<<"sdrftgyhuj::"<<object;

    //Text
    QJsonValue textV = object.value("text");
    //qDebug()<<"text:"<<textV;
    QJsonValue resim = object.value("Resim");
    //qDebug()<<"resim:"<<resim;
    QString decodedText = "";
    decodedText.append(textV.toString());
    //qDebug()<<"Text Metin:"<<decodedText;
    QString decodedResim = "";
    decodedResim.append(resim.toString());
    //qDebug()<<"Resim"<<decodedResim;
    QString textCozuldu = deneme.sifreCozme(decodedText);
    //qDebug()<<"textCozuldu:"<<textCozuldu;
     QString Cozuldu = deneme.sifreCozme(decodedResim);
    QByteArray br = textCozuldu.toUtf8();
    QByteArray brResim = Cozuldu.toUtf8();
    //qDebug()<<"resim:"<<brResim;
    //Resim
    ui->textEdit->append(QString(br));
    QString filename = "output.png";
    QImage image;
    image.loadFromData(QByteArray::fromBase64(brResim), "PNG");
    image=image.scaledToWidth(ui->label->width(),Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(image));//Resmi ekleme
    image.save(filename, "PNG");

}

