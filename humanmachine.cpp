#include "humanmachine.h"
#include <QPainter>
#include <QDebug>

Humanmachine::Humanmachine(QWidget *parent)
    : QWidget(parent),xPos(inixPos),yPos(iniyPos),handAngle(iniangle),status(0) {

    handTextBrowser=new QTextBrowser(this);
    handTextBrowser->setGeometry(xPos+30,yPos+30,25,25);

    moveMachineTimer=new QTimer(this);
    rotateHandTimer=new QTimer(this);
    connect(rotateHandTimer,&QTimer::timeout,this,&Humanmachine::rotateStep);
    connect(moveMachineTimer,&QTimer::timeout,this,&Humanmachine::moveMachineStep);
    qDebug()<<"生成函数被调用";
}

void Humanmachine::updateHand(){
    if(status==0){
        handTextBrowser->move(xPos+55*sin(handAngle*3.1415926/180),yPos+40*cos(handAngle*3.1415926/180));
    }

    if(status==1){
        handTextBrowser->move(xPos-1,yPos-25);
    }
}

void Humanmachine::rotateHand(int angle=30){
    aimAngle=angle;
    rotateHandTimer->start(2);
    if(handAngle==aimAngle){
        rotateHandTimer->stop();
    }
}

void Humanmachine::rotateStep(){
    if(handAngle!=aimAngle){
        handAngle+=(handAngle<aimAngle) ? 1 : -1;
        updateHand();
    }
}

void Humanmachine::resetDirec(){
    xPos=inixPos;
    yPos=iniyPos;
    handAngle=iniangle;
}

// moveMachine表示move的主函数
// moveMachineStep表示move的每一步
// moveMachineStep绑定到moveMachineTimer

void Humanmachine::moveMachine(int aimXSet, int aimYset, std::string action){
    aimX=aimXSet;
    aimY=aimYset;
    moveMachineTimer->start();
    if(xPos==aimX&&yPos==aimY){
        //status=1;
        //rotateHand(60);
        moveMachineTimer->stop();
        if(xPos==aimX&&yPos==aimY) {
            if(action=="zero"||action=="pos"||action=="neg"){
                status=1;
                update();
                status=0;
            } else if(action=="copyto"){
                rotateHand(120);
            } else if(action=="copyfrom"){
                rotateHand(120);
            } else if(action=="sub"){
                rotateHand(120);
            } else if(action=="add"){
                rotateHand(120);
            }
        }
    }
}

void Humanmachine::moveMachineStep() {
    if(xPos!=aimX||yPos!=aimY) {
        if(xPos!=aimX) {
            xPos+=(xPos<aimX) ? 1 : -1;
            repaint();
        }
        if(yPos!=aimY) {
            yPos+=(yPos<aimY) ? 1 : -1;
            repaint();
        }
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
    painter.rotate(-handAngle);
    painter.drawRect(-7,0,7,30);
    painter.restore();

    painter.setBrush(Qt::red);
    painter.save();
    painter.translate(xPos+2,yPos+20);
    painter.rotate(handAngle);
    painter.drawRect(-7,0,7,30);
    painter.restore();

    updateHand();
}
