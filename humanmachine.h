#ifndef HUMANMACHINE_H
#define HUMANMACHINE_H
#include <QWidget>
#include <QTextBrowser>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QTextBrowser>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPushButton>

class Humanmachine : public QWidget {
    Q_OBJECT
public:
    Humanmachine(QWidget *parent=nullptr);


    int inixPos=145;
    int iniyPos=10;
    int iniangle=30;
    int xPos;
    int yPos;
    int handAngle;
    int aimAngle;
    int aimX;
    int aimY;
    int status;
    QTextBrowser* handTextBrowser;
    QTimer* moveMachineTimer;
    QTimer* rotateHandTimer;

    void rotateHand(int angle);
    void resetDirec();
    void updateHand();
    //void upHand();
    void moveMachine(int aimXSet,int aimYset,std::string action);

private slots:
    void rotateStep();
    void moveMachineStep();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // HUMANMACHINE_H
