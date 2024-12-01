#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "game.h"
#include <queue>
#include <sstream>
#include "humanmachine.h"
extern std::vector<Game> games;

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Humanmachine *machine;
    bool ifWin;
    int level;
    std::queue<std::string> logStateQueue;
    std::queue<std::string> inboxbarStateQueue;
    std::queue<std::string> outboxbarStateQueue;
    std::queue<std::string> carpet1StateQueue;
    std::queue<std::string> carpet2StateQueue;
    std::queue<std::string> carpet3StateQueue;
    std::queue<std::string> carpet4StateQueue;
    std::queue<std::string> handStateQueue;

    void parselArchiveInfo(const std::string& line,int tempIndex);
    void parselLevelInfo(const std::string& line,
                         std::vector<std::string>& levelInfoRead,
                         std::vector<std::vector<std::string>>& inboxBarSetRead,
                         std::vector<std::vector<std::string>>& availableOpRead,
                         std::vector<std::vector<std::string>>& goalJudgeRead,
                         std::vector<int>& numOfCarpet);

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
    void loadEndBack();
    void loadAuto();
    void loadandback();
    void showGame();
    void skiptoend();

private:
    Ui::MainWindow *ui;
    QTimer* stateUpdateTimer;
};
#endif // MAINWINDOW_H
