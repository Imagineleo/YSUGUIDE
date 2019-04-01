#include "ysu.h"
#include "ui_ysu.h"
#include "QLabel"
#include "math.h"
#include "QTextCodec"
#include "Graph.h"
#include "Qdebug"
#include <QPainter>
#include <QPen>
#include <QTime>
#include "QMessageBox"
#include "iostream"
extern AdjWMGraph<const char*> gh;
int point[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
extern int ind[20];
extern int sum,sum_before;

YSU::YSU(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YSU)
{
    ui->setupUi(this);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QLabel *label1 = new QLabel(this);
    QFont font;
    font.setPointSize(20);
    label1 ->setFont(font);
    label1 ->setGeometry(QRect(650,30,300,30));
    label1->setText(QString::fromLocal8Bit("燕山大学导航系统"));
//    label->setGeometry(QRect(20, 100, 1291, 571));
//    label->setPixmap(QPixmap("./map2.jpg"));

    QTextToSpeech *tts1 = new QTextToSpeech(this);
    if(tts1->state()==QTextToSpeech::Ready)
    {
        tts1->say("欢迎使用燕山大学导航系统,请输入出发点和目的地");
    }
    ui->label->show();
}

YSU::~YSU()
{
    delete ui;
}


void YSU::on_pushButton_clicked()
{
    int Start,End;
    Start=ui->comboBox->currentIndex();
    End=ui->comboBox_2->currentIndex();
    gh.FindMinToDist(Start, End,point);
    ui->label_4->clear();
    ui->label_4->paintingActive();
    qDebug()<<Start;
    qDebug()<<End;
    if(Start==End)
    {
      QMessageBox::warning(this, "warning", " ");
      QTextToSpeech *tts3 = new QTextToSpeech(this);
      if(tts3->state()==QTextToSpeech::Ready)
      {
          tts3->say("起始点不应与终点相同,请重新输入");
      }
    }
    else
    {
    QString Nsum;
    Nsum=QString::number(sum);
    QString Ave_foot = QString::number(ceil(sum/69.0));
    QString Ave_bicycle = QString::number(ceil(sum/213.0));
    QTextToSpeech *tts2 = new QTextToSpeech(this);
    if(tts2->state()==QTextToSpeech::Ready)
    {
        tts2->say("导航开始，最短路径已标出,路径总长:"+Nsum+"米,步行约需"+Ave_foot+"分钟,骑行约需"+Ave_bicycle+"分钟");
    }
    }
}




