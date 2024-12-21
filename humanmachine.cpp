/*
 * README
 * humanmachine主要有这几个函数
 * 1.resetDirec
 * 2.Hand: rotateHand,rotateStep
 * 3.Body: moveMachine, moveMachineStep
 * 4.paint: paintEvent, updateHand
 * 新增参量
 * 1.status 0表示普通姿势，1表示手在头顶
 * 2.aim等变量
 */

/*
 * TODO
 * 1.涉及到的动作，jump类动作，copy类动作，add、sub类动作，hand+-类动作
 * 2.动作与栏内容修改先后顺序匹配
 * 3.我试着写了一些，但好像不能正常显示效果（代码所应该达到的效果）
 */

#include "humanmachine.h"
#include <QPainter>
#include <QDebug>
#include <QThread>

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

void Humanmachine::resetDirec(){
    xPos=inixPos;
    yPos=iniyPos;
    handAngle=iniangle;
    update();
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
    rotateHandTimer->start(1);
    if(handAngle==aimAngle){
        rotateHandTimer->stop();
    }
}

void Humanmachine::rotateStep(){
    if(handAngle!=aimAngle){
        handAngle+=(handAngle<aimAngle) ? 1 : -1;
        repaint();
    }
}

// moveMachine表示move的主函数
// moveMachineStep表示move的每一步
// moveMachineStep绑定到moveMachineTimer

void Humanmachine::moveMachine(int aimXSet, int aimYset, std::string action="empty"){
    aimX=aimXSet;
    aimY=aimYset;
    moveMachineTimer->start(2);
    if(xPos==aimX&&yPos==aimY){
        moveMachineTimer->stop();
        if(xPos==aimX&&yPos==aimY) {
            qDebug()<<"START action "<<QString::fromStdString(action);
            if(action=="zero"||action=="pos"||action=="neg"){
                status=1;
                repaint();
                QTimer::singleShot(1000,this,[&]() {
                    status=0;
                    repaint();
                });
            } else if(action=="copyto"){
                qDebug()<<"AAAA";
                rotateHand(90);
                QTimer::singleShot(1000,this,[&]() {
                    rotateHand(30);
                    repaint();
                });
            } else if(action=="copyfrom"){
                qDebug()<<"BBB";
                rotateHand(90);
                QTimer::singleShot(1000,this,[&]() {
                    rotateHand(120);
                    repaint();
                });
                QTimer::singleShot(1000,this,[&]() {
                    rotateHand(30);
                    repaint();
                });
            } else if(action=="copyifpos"||action=="copyifneg"){

            } else if(action=="add"||action=="sub"){

            } else if(action=="hand+"||action=="hand-"){
                qDebug()<<"CCCC";
                status=1;
                repaint();
                QTimer::singleShot(1000,this,[&]() {
                    status=0;
                    repaint();
                });
            } else{
                qDebug()<<"no responding action";
            }
        }
    }
}

void Humanmachine::moveMachineStep() {
    if(xPos!=aimX||yPos!=aimY) {
        if(xPos!=aimX) {
            xPos+=(xPos<aimX) ? 1 : -1;
            update();
        }
        if(yPos!=aimY) {
            yPos+=(yPos<aimY) ? 1 : -1;
            update();
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
