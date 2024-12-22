#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "game.h"
#include <queue>
#include <sstream>
#include "humanmachine.h"
#include "game.h"
extern std::vector<Game> games;

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

extern int level;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Humanmachine *machine;
    bool ifWin;

    std::queue<std::string> logStateQueue;
    std::queue<std::string> inboxbarStateQueue;
    std::queue<std::string> outboxbarStateQueue;
    std::queue<std::string> carpet1StateQueue;
    std::queue<std::string> carpet2StateQueue;
    std::queue<std::string> carpet3StateQueue;
    std::queue<std::string> carpet4StateQueue;
    std::queue<std::string> handStateQueue;

    std::queue<std::string> carpet11StateQueue;
    std::queue<std::string> carpet12StateQueue;
    std::queue<std::string> carpet13StateQueue;
    std::queue<std::string> carpet14StateQueue;
    std::queue<std::string> carpet15StateQueue;
    std::queue<std::string> carpet16StateQueue;

    std::queue<std::string> carpet21StateQueue;
    std::queue<std::string> carpet22StateQueue;
    std::queue<std::string> carpet23StateQueue;
    std::queue<std::string> carpet24StateQueue;
    std::queue<std::string> carpet25StateQueue;
    std::queue<std::string> carpet26StateQueue;

    std::queue<std::string> carpet31StateQueue;
    std::queue<std::string> carpet32StateQueue;
    std::queue<std::string> carpet33StateQueue;
    std::queue<std::string> carpet34StateQueue;
    std::queue<std::string> carpet35StateQueue;
    std::queue<std::string> carpet36StateQueue;

    std::queue<std::string> carpet41StateQueue;
    std::queue<std::string> carpet42StateQueue;
    std::queue<std::string> carpet43StateQueue;
    std::queue<std::string> carpet44StateQueue;
    std::queue<std::string> carpet45StateQueue;
    std::queue<std::string> carpet46StateQueue;

    std::queue<std::string> carpet51StateQueue;
    std::queue<std::string> carpet52StateQueue;
    std::queue<std::string> carpet53StateQueue;
    std::queue<std::string> carpet54StateQueue;
    std::queue<std::string> carpet55StateQueue;
    std::queue<std::string> carpet56StateQueue;

    bool startProcessing;

    void clearLayout(QLayout* layout);
    void parselArchiveInfo(const std::string& line,int tempIndex);
    void parselLevelInfo(const std::string& line,
                         std::vector<std::string>& levelInfoRead,
                         std::vector<std::vector<std::string>>& inboxBarSetRead,
                         std::vector<std::vector<std::string>>& availableOpRead,
                         std::vector<std::vector<std::string>>& goalJudgeRead,
                         std::vector<int>& numOfCarpet,
                         std::vector<int>& numOfCarpet2D,
                         std::vector<std::string>& descripRead);
    void setTargetPosition(int x, int y);

signals:
    void startJudge(int level);

private slots:
    void buttonEnterClicked();
    void buttonExitClicked();
    void buttonLoadgameClicked();
    void buttonBackWelcomepageClicked();
    void buttonRestartClicked();
    void buttonStartJudgeClicked();
    void buttonBackClicked();
    void updateProcessingState();
    void loadLevelinfo();
    void loadArchive();
    void loadAuto();
    void loadandback();
    void showGame();
    void showGameNunchunk();
    void skiptoend();
    void geneLevelNunchunk();
    //void startMachineMovement();
    //void stopMachineMovement();
    //void moveMachine();

private:
    Ui::MainWindow *ui;
    QTimer* stateUpdateTimer;
    //QTimer* moveTimer;
    //int targetx;
    //int targety;
};
#endif // MAINWINDOW_H
