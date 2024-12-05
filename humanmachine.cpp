#include "humanmachine.h"
#include <QPainter>
#include <QDebug>

Humanmachine::Humanmachine(QWidget *parent)
    : QWidget(parent),xPos(inixPos),yPos(iniyPos),handAngle(0) {

    handTextBrowser=new QTextBrowser(this);
    handTextBrowser->setGeometry(xPos+30,yPos+30,25,25);

    qDebug()<<"生成函数被调用";
}

void Humanmachine::moveUp(){
    yPos-=10;
}
void Humanmachine::moveDown(){
    yPos+=10;
}
void Humanmachine::moveLeft(){
    xPos-=10;
}
void Humanmachine::moveRight(){
    xPos+=10;
}
void Humanmachine::rotateHand(int angle){
    handAngle+=angle;
    update();
}

void Humanmachine::resetDirec(){
    xPos=inixPos;
    yPos=iniyPos;
    handAngle=0;
}

void Humanmachine::updateHand(){
    handTextBrowser->move(xPos+30,yPos+30);
}
void Humanmachine::moveMachine(int aimx,int aimy) {
    if (xPos != aimx || yPos != aimy) {
        if (xPos != aimx) {
            xPos += (xPos < aimx) ? 1 : -1;
        }
        if (yPos != aimy) {
            yPos += (yPos < aimy) ? 1 : -1;
        }
        if (xPos == aimx && yPos == aimy) {
            // 到达目标位置后执行的操作
        } else {
            update();  // 继续更新界面
        } // 使用 update() 而不是 repaint()
    }
}
void Humanmachine::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.setPen(QPen(Qt::black,2));
    //painter.drawRect(0,0,width(),height());

    painter.setBrush(Qt::yellow);
    painter.drawEllipse(xPos,yPos,20,20);
    painter.setBrush(Qt::blue);
    painter.drawRect(xPos,yPos+20,20,40);
    painter.setBrush(Qt::red);
    painter.drawRect(xPos,yPos+60,7,40);
    painter.drawRect(xPos+13,yPos+60,7,40);

    painter.setBrush(Qt::red);
    painter.save();
    painter.translate(xPos+24,yPos+20);
    painter.rotate(-30);
    painter.drawRect(-7,0,7,30);
    painter.restore();

    painter.setBrush(Qt::red);
    painter.save();
    painter.translate(xPos+2,yPos+20);
    painter.rotate(30);
    painter.drawRect(-7,0,7,30);
    painter.restore();
}
