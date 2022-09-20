#include "tcpclient.h"
#include "ui_tcpclient.h"
#include "sifreleme.h"
TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
}

TcpClient::~TcpClient()
{
    delete this->socket;//Reclaim memory
}


void TcpClient::on_pushButtonConnect_clicked()
{
    if (ui->pushButtonConnect->text()==tr("Connect server"))
      {
        QString ip = ui->lineEditIP->text();//Get ip
        int port = ui->lineEditPort->text().toInt();//Get port data
        //Cancel existing connection
        socket->abort();
        //Connect server
        socket->connectToHost(ip, port);
        bool isconnect = socket->waitForConnected();//Wait until the connection is successful
        //If the connection is successful
        if (isconnect)
        {
               ui->textEdit->append("The connection was successful!!");
               ui->pushButtonclicked->setEnabled(true);//Button enable
              //Modify key text
               ui->pushButtonConnect->setText("Disconnect server");
              //Receive buffer (server) information
              connect(socket, &QTcpSocket::readyRead, this, &TcpClient::ReadData);

        }
        else
           {
               ui->textEdit->append("The connection falied!!");
           }
    }
    else
      {
          //Disconnect
          socket->disconnectFromHost();
          ui->pushButtonConnect->setText("Connect server");
          ui->pushButtonclicked->setEnabled(false);//Turn off send button enable
      }


}


void TcpClient::on_pushButtonclicked_clicked()
{
    sifreleme a;
    QString metin=ui->lineEdit->text();
    //qDebug()<<"metin"<<metin;
    std::string utf8_text = metin.toUtf8().constData();
    string textSifrele=a.sifre(utf8_text);
    QString textVerisi = QString::fromStdString(textSifrele);

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    image.save(&buffer, "PNG");
    QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());//Resim base64 Qstring dönüştürüldü
    std::string resim = iconBase64.toUtf8().constData();
    //cout<<"iconBase64:"<<resim<<endl<<endl;


    string deneme=a.sifre(resim);
    QString ResimVerisi = QString::fromStdString(deneme);
    QJsonObject mainObject;
    mainObject.insert("text", textVerisi);
    mainObject.insert("Resim", ResimVerisi);
    QJsonDocument doc(mainObject);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    //qDebug()<<"veri:"<<data;
    QString jsonString(data);
    //QByteArray data = ui->lineEdit->text().toUtf8();//Get the data in the lineEdit control and send it to the server
    socket->write(jsonString.toUtf8());
    //Determine whether the write is successful
    bool iswrite = socket->waitForBytesWritten();
    if (iswrite)
       {
           //Write successful
       }
       else
       {
           //No write succeeded
       }

}

void TcpClient::ReadData()
{
    QByteArray buf = socket->readAll();
    ui->textEdit->append(buf);

}


void TcpClient::on_pushButton_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
    if(QString::compare(filename,QString()) !=0)
    {

        bool valid=image.load(filename);
        if(valid)
        {
            image=image.scaledToWidth(ui->labelImage->width(),Qt::SmoothTransformation);
            ui->labelImage->setPixmap(QPixmap::fromImage(image));//Resmi ekleme



        }
        }

}


void TcpClient::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->pushButton->clearMask();
}

