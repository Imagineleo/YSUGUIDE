#include "ysu.h"
#include <QApplication>
#include "graph.h"
#include "iostream"
#include "fstream"
#include "QMessageBox"
#include "stdio.h"
#include <QTextCodec>
#include "QDebug"


AdjWMGraph<const char*> gh;
int ind[20]={'a',0};
int sum=0,sum_before=0;
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    const char* dis[14] = {"A", "B", "C", "D", "E" ,"F","G","H","I","J","K","L","M"};
    RowColWeight RCW[37];
    int count=0;
    QApplication a(argc, argv);
    FILE *fp;
    //if((fp = fopen("C:/Users/Leo/Desktop/YSU/YSUv2/YSUv2/YSU.txt", "r")) == NULL)
    if((fp = fopen("./YSU.txt", "r")) == NULL)
    {
        QMessageBox::about(NULL, "Warning", QString::fromLocal8Bit("读取文件错误"));
    }
    while(!feof(fp))
    {
        fscanf(fp, "%d,%d,%d", &RCW[count].Row, &RCW[count].Col,&RCW[count].Weight);
                count++;
    }
    for (int i = 0; i < count; ++i)
         qDebug()<< "Row:" << RCW[i].Row << "Col" << RCW[i].Col << "Weigth" << RCW[i].Weight << endl;
    fclose(fp);
    gh.CreateGraph(dis, 14, RCW, 36);

    YSU w;
    w.setWindowTitle(QString::fromLocal8Bit("燕山大学导航系统"));
    w.show();

    return a.exec();
}
