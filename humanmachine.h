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
    int iniyPos=5;
    int xPos;
    int yPos;
    int handAngle;
    QTextBrowser* handTextBrowser;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void rotateHand(int angle);
    void resetDirec();
    void updateHand();
    void moveMachine(int aimx,int aimy);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // HUMANMACHINE_H
