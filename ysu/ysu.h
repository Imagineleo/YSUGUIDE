#ifndef YSU_H
#define YSU_H

#include <QWidget>
#include "QTextToSpeech"
namespace Ui {
class YSU;
}

class YSU : public QWidget
{
    Q_OBJECT

public:
    explicit YSU(QWidget *parent = 0);
    ~YSU();

private slots:
    void on_pushButton_clicked();

private:
    Ui::YSU *ui;


};

#endif // YSU_H
