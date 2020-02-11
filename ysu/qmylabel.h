#ifndef QMYLABEL_H
#define QMYLABEL_H
#include "Qdebug"
#include <QPainter>
#include <QPen>
#include <QTime>
#include <QLabel>
#include "QMessageBox"

extern int ind[20];
extern int sum,sum_before;

class QMyLabel:public QLabel
{
public:
    QMyLabel(QWidget *parent):QLabel(parent)
    {}
public:
    void paintEvent(QPaintEvent *);

};

void QMyLabel::paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        QPen pen;
        QString Qsum;
        Qsum=QString::number(sum);
        QString out="最短路径已标出,路径总长:"+Qsum+"m";
        pen.setWidth(6);
        pen.setColor(Qt::red);
        painter.setPen(pen);
        int x=0;
        while(ind[x]!='a')
        {

            if((ind[x]==0&&ind[x+1]==1)||(ind[x]==1&&ind[x+1]==0))   //第四教学楼到机械工程学院
                painter.drawLine(1270, 170,1195,345);
            if((ind[x]==0&&ind[x+1]==3)||(ind[x]==3&&ind[x+1]==0))    //第四教学楼到燕宏桥
                {
                painter.drawLine(1270, 170.0,1210,280);
                painter.drawLine(1210, 280.0,1140,250);
                }
            if((ind[x]==1&&ind[x+1]==2)||(ind[x]==2&&ind[x+1]==1))    //机械工程学院到世纪楼
                {
                painter.drawLine(1195,345,1050,480);
                painter.drawLine(1050,480,1110,550);
                painter.drawLine(1110,550,1140,523);
                }
            if((ind[x]==3&&ind[x+1]==1)||(ind[x]==1&&ind[x+1]==3))   //从机械工程学院到燕宏桥
                {
                painter.drawLine(1195.0, 345.0,1210,280);
                painter.drawLine(1210.0, 280.0,1140,250);
                }
            if((ind[x]==3&&ind[x+1]==4)||(ind[x]==4&&ind[x+1]==3))  //燕宏桥到塔山公园
                {
                painter.drawLine(1140,250,947,188);
                }
            if((ind[x]==4&&ind[x+1]==5)||(ind[x]==5&&ind[x+1]==4))   //塔山公园到第二图书馆
            {
                painter.drawLine(947.0, 188.0,922,73);
            }
            if((ind[x]==4&&ind[x+1]==8)||(ind[x]==8&&ind[x+1]==4))   //塔山公园到里仁教学楼
                {
                painter.drawLine(947.0, 188.0,870,345);
                painter.drawLine(870.0, 345.0,437,334);
                painter.drawLine(437.0, 334.0,440,370);
                }

            if((ind[x]==4&&ind[x+1]==7)||(ind[x]==7&&ind[x+1]==4))   //塔山公园到实验楼
                {
                painter.drawLine(947.0, 188.0,870,345);
                painter.drawLine(870.0, 345.0,600,345);
                painter.drawLine(600.0, 345.0,610,440);
                painter.drawLine(610.0, 440.0,610,460);
                }

            if((ind[x]==8&&ind[x+1]==7)||(ind[x]==7&&ind[x+1]==8))   //里仁教学楼到里仁实验楼
                {
                painter.drawLine(440.0, 370.0,440,430);
                painter.drawLine(440.0, 430.0,610,440);
                painter.drawLine(610.0, 440.0,610,460);
                }

            if((ind[x]==6&&ind[x+1]==8)||(ind[x]==8&&ind[x+1]==6))  //里仁教学楼到图文中心
                painter.drawLine(440.0, 380.0,476,513);

            if((ind[x]==8&&ind[x+1]==9)||(ind[x]==9&&ind[x+1]==8))  //里仁教学楼到公寓4B
                {
                painter.drawLine(440.0,380.0,440,440);
                painter.drawLine(440.0,440.0,300,445);
                painter.drawLine(300.0,445.0,110,450);
                painter.drawLine(110.0,450.0,90,476);
                }
            if((ind[x]==10&&ind[x+1]==8)||(ind[x]==8&&ind[x+1]==10))   //里仁教学楼到西校区食堂
            {
                painter.drawLine(440.0, 380.0,437,334);
                painter.drawLine(437.0, 334.0,265,315);
                painter.drawLine(265.0, 315.0,110,215);
                painter.drawLine(110.0, 215.0,93,285);
                painter.drawLine(93.0, 285.0,65,285);
            }
            if((ind[x]==8&&ind[x+1]==12)||(ind[x]==12&&ind[x+1]==8))   //里仁教学楼到材料楼
                {
                painter.drawLine(440.0, 380.0,437,334);
                painter.drawLine(437.0, 334.0,265,315);
                painter.drawLine(265.0, 315.0,110,215);
                painter.drawLine(110.0, 215.0,180,120);
                }
            if((ind[x]==6&&ind[x+1]==7)||(ind[x]==7&&ind[x+1]==6))    //里仁实验楼到图文中心
                {
                painter.drawLine(610,460,600,490);
                painter.drawLine(600,490,480,490);
                painter.drawLine(480,490,476,513);
                }
            if((ind[x]==6&&ind[x+1]==9)||(ind[x]==9&&ind[x+1]==6))  //图文到公寓
            {
                painter.drawLine(476,513,473,490);
                painter.drawLine(473,490,300,460);
                painter.drawLine(300,460,110,450);
                painter.drawLine(110.0,450.0,90,476);
            }
            if((ind[x]==9&&ind[x+1]==10)||(ind[x]==10&&ind[x+1]==9))  //公寓到大榕树
                painter.drawLine(90,476,65,285);

            if((ind[x]==10&&ind[x+1]==11)||(ind[x]==11&&ind[x+1]==10))  //大榕树到西区医院
                painter.drawLine(65,285,18,178);

            if((ind[x]==11&&ind[x+1]==12)||(ind[x]==12&&ind[x+1]==11))    //医院到材料楼
                {
                painter.drawLine(18,178,110,215);
                painter.drawLine(110,215,180,120);
                }

            if((ind[x]==10&&ind[x+1]==12)||(ind[x]==12&&ind[x+1]==10))    //大榕树到材料楼
                {
                painter.drawLine(65,285,93,285);
                painter.drawLine(93,285,110,215);
                painter.drawLine(110.0, 215.0,180,120);
                }
            x++;
        }
        if(sum!=sum_before&&sum!=0)
        {
            sum_before=sum;
            QMessageBox::information(this, "提示", out);
        }
}




#endif // QMYLABEL_H
