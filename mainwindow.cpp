#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "game.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QPlainTextEdit>
#include <vector>
#include <QFileDialog>
#include <fstream>
#include <string>
#include <QLayout>
#include <QVBoxLayout>
#include "humanmachine.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stateUpdateTimer(new QTimer(this)) {
    ui->setupUi(this);

    //welcome界面
    connect(ui->buttonWelcomePlaygame,&QPushButton::clicked,this,&MainWindow::buttonEnterClicked);
    connect(ui->buttonWelcomeExit,&QPushButton::clicked,this,&MainWindow::buttonExitClicked);
    connect(ui->buttonWelcomeLoadgame,&QPushButton::clicked,this,&MainWindow::buttonLoadgameClicked);

    //Fail界面
    connect(ui->buttonFailExit,&QPushButton::clicked,this,&MainWindow::buttonExitClicked);
    connect(ui->buttonFailRestart,&QPushButton::clicked,this,&MainWindow::buttonRestartClicked);
    connect(ui->buttonFailBack,&QPushButton::clicked,this,&MainWindow::buttonBackClicked);

    //Success界面
    connect(ui->buttonSuccessBack,&QPushButton::clicked,this,&MainWindow::buttonBackClicked);
    connect(ui->buttonSuccessExit,&QPushButton::clicked,this,&MainWindow::buttonExitClicked);

    //levelchoice界面
    connect(ui->buttonLevelchoiceLevel1,&QPushButton::clicked,this,[=](){level=0;showGame();});
    connect(ui->buttonLevelchoiceLevel2,&QPushButton::clicked,this,[=](){level=1;showGame();});
    connect(ui->buttonLevelchoiceLevel3,&QPushButton::clicked,this,[=](){level=2;showGame();});
    connect(ui->buttonLevelchoiceBack,&QPushButton::clicked,this,&MainWindow::buttonBackWelcomepageClicked);

    //playgmae界面
    connect(ui->buttonPlaygameStart,&QPushButton::clicked,this,&MainWindow::buttonStartJudgeClicked);
    connect(ui->buttonPlaygameSkip,&QPushButton::clicked,this,&MainWindow::skiptoend);

    //初始化处理状态定时器
    stateUpdateTimer=new QTimer(this);
    connect(stateUpdateTimer,&QTimer::timeout,this,&MainWindow::updateProcessingState);

    //loadgame界面
    connect(ui->buttonLoadgameLoadlevelinfo,&QPushButton::clicked,this,&MainWindow::loadLevelinfo);
    connect(ui->buttonLoadgameLoadarchive,&QPushButton::clicked,this,&MainWindow::loadArchive);
    connect(ui->buttonLoadgameBackandload,&QPushButton::clicked,this,&MainWindow::loadandback);
    connect(ui->buttonLoadgameAutoload,&QPushButton::clicked,this,&MainWindow::loadAuto);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::buttonEnterClicked() {
    if(games[0].passed){
        QString currentText=ui->buttonLevelchoiceLevel1->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel1->setText(updatedText);
    }
    if(games[1].passed){
        QString currentText=ui->buttonLevelchoiceLevel2->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel2->setText(updatedText);
    }
    if(games[2].passed){
        QString currentText=ui->buttonLevelchoiceLevel3->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel3->setText(updatedText);
    }
    ui->stackedWidget->setCurrentWidget(ui->levelchoice);
}

void MainWindow::buttonExitClicked() {
    std::ofstream archiveFile;
    archiveFile.open("archive.txt");
    for(int i=0;i<games.size();++i) {
        archiveFile<<"Level"<<i<<":";
        if(games[i].passed) {
            archiveFile<<"Passed"<<endl;
        } else {
            archiveFile<<"NotPassed"<<endl;
        }
    }
    archiveFile.close();
    exit(0);
}

void MainWindow::buttonLoadgameClicked(){
    ui->stackedWidget->setCurrentWidget(ui->loadgame);
}

void MainWindow::buttonBackClicked() {
    ui->stackedWidget->setCurrentWidget(ui->levelchoice);
}

void MainWindow::buttonBackWelcomepageClicked(){
    ui->stackedWidget->setCurrentWidget(ui->welcomePage);
}

void MainWindow::buttonRestartClicked() {
    ui->stackedWidget->setCurrentWidget(ui->playgame);
}

void MainWindow::showGame(){
    qDebug()<<"开始游戏";

    if(level>=1){
        if(!games[level-1].passed) {
            QMessageBox::warning(this,"Warning","You've not passed previous level");
            //return;
        }
    }

    machine=new Humanmachine(this);
    machine->setFixedSize(600, 1000);
    machine->lower();
    ui->stackedWidget->setCurrentWidget(ui->playgame);
    if (!machine) {
        qDebug()<<"初始化失败";
    } else {
        qDebug()<<"初始化正常";
    }
    QWidget *playGamePage=ui->playgame;
    //QVBoxLayout *layout=new QVBoxLayout(playGamePage);
    //layout->addWidget(machine);

    //playGamePage->layout()->removeWidget(ui->showPlaygameInboxbar);
    //playGamePage->layout()->removeWidget(machine);
    playGamePage->layout()->addWidget(machine);

    std::string showInitialInbox;
    for(int i=0;i<games[level].initialInbox.size();++i){
        showInitialInbox+=games[level].initialInbox[i]+" ";
    }
    ui->showPlaygameInboxbar->append(QString::fromStdString(showInitialInbox));
}

void MainWindow::buttonStartJudgeClicked() {
    QString commandInput;
    commandInput=ui->inputPlaygameCommand->toPlainText();
    if(!commandInput.isEmpty()) {
        qDebug()<<"User input:"<<commandInput;
    } else {
        ui->inputPlaygameCommand->clear();
        return;
    }

    games[level].onLogbarUpdate=[this](const std::string& state) {
        logStateQueue.push(state);
    };

    games[level].onInboxbarUpdate=[this](const std::string& state){
        inboxbarStateQueue.push(state);
    };

    games[level].onOutboxbarUpdate=[this](const std::string& state){
        outboxbarStateQueue.push(state);
    };

    games[level].onCarpet1Update=[this](const std::string& state){
        carpet1StateQueue.push(state);
    };

    games[level].onCarpet2Update=[this](const std::string& state){
        carpet2StateQueue.push(state);
    };

    games[level].onCarpet3Update=[this](const std::string& state){
        carpet3StateQueue.push(state);
    };

    games[level].onCarpet4Update=[this](const std::string& state){
        carpet4StateQueue.push(state);
    };

    games[level].onHandUpdate=[this](const std::string& state){
        handStateQueue.push(state);
    };

    std::string inputStreamString=commandInput.toStdString();
    std::istringstream inputStream(inputStreamString);
    ifWin=games[level].playgame(inputStream);

    qDebug()<<(ifWin ? "win" : "notwin");

    ui->showPlaygameInboxbar->clear();
    stateUpdateTimer->start(1000);
}

void MainWindow::updateProcessingState() {
    if(!games[level].actionLog.empty()){
        if(games[level].actionLog.front()=="inbox"){
            machine->yPos=machine->iniyPos;
            machine->xPos=machine->inixPos;
            machine->updateHand();
            machine->repaint();
        } else if(games[level].actionLog.front()=="outbox"){
            machine->yPos=350;
            machine->xPos=machine->inixPos;
            machine->updateHand();
            machine->repaint();
        } else if(games[level].actionLog.front()=="copyto"){
            machine->yPos=150;
            machine->xPos=260;
            machine->updateHand();
            machine->repaint();
        } else if(games[level].actionLog.front()=="copyfrom"){
            machine->yPos=150;
            machine->xPos=260;
            machine->updateHand();
            machine->repaint();
        } else if(games[level].actionLog.front()=="add"){
            machine->yPos=150;
            machine->xPos=260;
            machine->updateHand();
            machine->repaint();
        } else if(games[level].actionLog.front()=="sub"){
            machine->yPos=150;
            machine->xPos=260;
            machine->updateHand();
            machine->repaint();
        } else if(games[level].actionLog.front()=="zero"){
            machine->moveDown();
            machine->repaint();
            machine->moveUp();
            machine->repaint();
            machine->moveDown();
            machine->repaint();
            machine->moveUp();
            machine->repaint();
            machine->moveDown();
            machine->repaint();
            machine->moveUp();
            machine->repaint();
            machine->moveDown();
            machine->repaint();
            machine->moveUp();
            machine->repaint();
            machine->updateHand();
            machine->repaint();
        }
        games[level].actionLog.pop();
    }

    if(!logStateQueue.empty()) {
        qDebug()<<"logbar:"<<QString::fromStdString(logStateQueue.front());
        std::string logState=logStateQueue.front();
        logStateQueue.pop();
        ui->showPlaygameLogbar->append(QString::fromStdString(logState));
    }

    if(!inboxbarStateQueue.empty()) {
        qDebug()<<"inboxbar"<<QString::fromStdString(inboxbarStateQueue.front());
        std::string inboxbarState=inboxbarStateQueue.front();
        inboxbarStateQueue.pop();
        ui->showPlaygameInboxbar->setHtml(QString::fromStdString(inboxbarState));
    }

    if(!outboxbarStateQueue.empty()) {
        qDebug()<<"outboxbar"<<QString::fromStdString(outboxbarStateQueue.front());
        std::string outboxbarState=outboxbarStateQueue.front();
        outboxbarStateQueue.pop();
        ui->showPlaygameOutboxbar->setHtml(QString::fromStdString(outboxbarState));
    }

    if(!carpet1StateQueue.empty()) {
        qDebug()<<"carpet1"<<QString::fromStdString(carpet1StateQueue.front());
        std::string carpet1State=carpet1StateQueue.front();
        carpet1StateQueue.pop();
        ui->showPlaygameCarpet1->setHtml(QString::fromStdString(carpet1State));
    }

    if(!carpet2StateQueue.empty()) {
        qDebug()<<"carpet2"<<QString::fromStdString(carpet2StateQueue.front());
        std::string carpet2State=carpet2StateQueue.front();
        carpet2StateQueue.pop();
        ui->showPlaygameCarpet2->setHtml(QString::fromStdString(carpet2State));
    }

    if(!carpet3StateQueue.empty()) {
        qDebug()<<"carpet3"<<QString::fromStdString(carpet3StateQueue.front());
        std::string carpet3State=carpet3StateQueue.front();
        carpet3StateQueue.pop();
        ui->showPlaygameCarpet3->setHtml(QString::fromStdString(carpet3State));
    }

    if(!carpet4StateQueue.empty()) {
        qDebug()<<"carpet4"<<QString::fromStdString(carpet4StateQueue.front());
        std::string carpet4State=carpet4StateQueue.front();
        carpet4StateQueue.pop();
        ui->showPlaygameCarpet4->setHtml(QString::fromStdString(carpet4State));
    }


    if(!handStateQueue.empty()) {
        qDebug()<<"hand"<<QString::fromStdString(handStateQueue.front());
        std::string handState=handStateQueue.front();
        handStateQueue.pop();
        machine->handTextBrowser->setHtml("<font size=\"36>\"<b>"+QString::fromStdString(handState)+"</b></font>");
    }

    if(logStateQueue.empty()&&inboxbarStateQueue.empty()&&outboxbarStateQueue.empty()&&carpet1StateQueue.empty()&&carpet2StateQueue.empty()&&carpet3StateQueue.empty()&&carpet4StateQueue.empty()){
        qDebug()<<"All queues are empty";
        stateUpdateTimer->stop();
        ui->inputPlaygameCommand->clear();
        ui->showPlaygameLogbar->clear();
        ui->showPlaygameInboxbar->clear();
        ui->showPlaygameOutboxbar->clear();
        ui->showPlaygameCarpet1->clear();
        ui->showPlaygameCarpet2->clear();
        ui->showPlaygameCarpet3->clear();
        ui->showPlaygameCarpet4->clear();
        machine->resetDirec();
        while(!games[level].actionLog.empty()){
            games[level].actionLog.pop();
        }
        if(ifWin) {
            qDebug()<<"Success!";
            ui->stackedWidget->setCurrentWidget(ui->success);
        } else {
            qDebug()<<"Fail";
            ui->stackedWidget->setCurrentWidget(ui->fail);
        }
    }
}

void MainWindow::skiptoend(){
    if(ifWin) {
        qDebug()<<"Success!";
        ui->stackedWidget->setCurrentWidget(ui->success);
    } else {
        qDebug()<<"Fail";
        ui->stackedWidget->setCurrentWidget(ui->fail);
    }
}

void MainWindow::loadLevelinfo(){
    QString levelinfoFilePath=QFileDialog::getOpenFileName(this, "Select Game File", "", "Text Files (*.txt);;All Files (*)");

    if (levelinfoFilePath.isEmpty()) {
        QMessageBox::information(this, "No file selected", "You did not select any file.");
        return;
    }

    std::ifstream levelInfoRead(levelinfoFilePath.toStdString());
    if (!levelInfoRead.is_open()) {
        qDebug()<<"Can access the file";
        return;
    }

    std::vector<std::string> levelinfoRead;
    std::vector<std::vector<std::string>> inboxBarSetRead;
    std::vector<std::vector<std::string>> availableOpRead;
    std::vector<std::vector<std::string>> goalJudgeRead;
    std::vector<int> numOfCarpet;
    std::string line;
    while(getline(levelInfoRead,line)){
        parselLevelInfo(line,levelinfoRead,inboxBarSetRead,availableOpRead,goalJudgeRead,numOfCarpet);
    }
    levelInfoRead.close();

    for(int i=0;i<inboxBarSetRead.size();++i){
        for(int j=0;j<inboxBarSetRead[i].size();++j){
            qDebug()<<i<<QString::fromStdString(inboxBarSetRead[i][j]);
        }
    }

    games.clear();
    for(int i=0;i<levelinfoRead.size();++i) {
        games.emplace_back(inboxBarSetRead[i],availableOpRead[i],goalJudgeRead[i],numOfCarpet[i]);
    }
}

void MainWindow::loadArchive(){
    QString archiveFilePath=QFileDialog::getOpenFileName(this, "Select Game File", "", "Text Files (*.txt);;All Files (*)");

    if (archiveFilePath.isEmpty()) {
        QMessageBox::information(this, "No file selected", "You did not select any file.");
        return;
    }

    std::ifstream archiveRead(archiveFilePath.toStdString());
    if (!archiveRead.is_open()) {
        qDebug()<<"Can access the file";
        return;
    }

    std::string line;
    int tempIndex=0;
    while(getline(archiveRead,line)){
        parselArchiveInfo(line,tempIndex);
        ++tempIndex;
    }
    archiveRead.close();

    for(int i=0;i<games.size();++i){
        qDebug()<<" "<<(games[i].passed ? "PASSED" : "NOT PASSED");
    }
}

void MainWindow::loadAuto(){
    std::ifstream levelInfoRead("levelinfo.txt");
    if (!levelInfoRead.is_open()) {
        qDebug()<<"Can't access the file";
        return;
    }
    std::vector<std::string> levelinfoRead;
    std::vector<std::vector<std::string>> inboxBarSetRead;
    std::vector<std::vector<std::string>> availableOpRead;
    std::vector<std::vector<std::string>> goalJudgeRead;
    std::vector<int> numOfCarpet;
    std::string line;
    while(getline(levelInfoRead,line)){
        parselLevelInfo(line,levelinfoRead,inboxBarSetRead,availableOpRead,goalJudgeRead,numOfCarpet);
    }
    levelInfoRead.close();

    for(int i=0;i<inboxBarSetRead.size();++i){
        for(int j=0;j<inboxBarSetRead[i].size();++j){
            qDebug()<<i<<QString::fromStdString(inboxBarSetRead[i][j]);
        }
    }
    games.clear();
    for(int i=0;i<levelinfoRead.size();++i) {
        games.emplace_back(inboxBarSetRead[i],availableOpRead[i],goalJudgeRead[i],numOfCarpet[i]);
    }

    std::ifstream archiveRead("archive.txt");
    if (!archiveRead.is_open()) {
        qDebug()<<"Can access the file";
        return;
    }
    int tempIndex;
    while(getline(archiveRead,line)){
        parselArchiveInfo(line,tempIndex);
        ++tempIndex;
    }
    archiveRead.close();
}

void MainWindow::parselArchiveInfo(const std::string& line,int tempIndex) {
    std::stringstream ss(line);
    std::string segment;
    getline(ss, segment);

    size_t pos=segment.find(':');

    if(pos!=std::string::npos) {
        std::string key=segment.substr(0,pos);
        std::string value=segment.substr(pos+1);

        key.erase(0, key.find_first_not_of(" "));
        key.erase(key.find_last_not_of(" ") + 1);
        value.erase(0, value.find_first_not_of(" "));
        value.erase(value.find_last_not_of(" ") + 1);

        qDebug()<<QString::fromStdString(value);
        if(QString::fromStdString(value)=="Passed\r") {
            qDebug()<<"BBBBBB";
            games[tempIndex].passed=true;
        } else if(QString::fromStdString(value)=="NotPassed\r") {
            qDebug()<<"AAAAAA";
            games[tempIndex].passed=false;
        } else {
            qDebug()<<"CCCCC";
            games[tempIndex].passed=false;
        }
    }
}

void MainWindow::parselLevelInfo(const std::string& line,
                     std::vector<std::string>& levelInfoRead,
                     std::vector<std::vector<std::string>>& inboxBarSetRead,
                     std::vector<std::vector<std::string>>& availableOpRead,
                     std::vector<std::vector<std::string>>& goalJudgeRead,
                     std::vector<int>& numOfCarpet) {
    std::stringstream ss(line);
    qDebug()<<QString::fromStdString(line);
    std::string segment;

    while(getline(ss,segment,'|')) {
        size_t pos=segment.find(':');

        if(pos!=std::string::npos) {
            std::string key=segment.substr(0,pos);
            std::string value=segment.substr(pos+1);

            key.erase(0, key.find_first_not_of(" "));
            key.erase(key.find_last_not_of(" ") + 1);
            value.erase(0, value.find_first_not_of(" "));
            value.erase(value.find_last_not_of(" ") + 1);

            if(key=="LevelInfo") {
                levelInfoRead.push_back(value);
            } else if(key=="InboxBar") {
                std::istringstream inboxStream(value);
                std::string item;
                std::vector<std::string> parts;
                while(inboxStream>>item) {
                    parts.push_back(item);
                }
                inboxBarSetRead.push_back(parts);
            } else if(key=="AvailableOps") {
                std::istringstream opStream(value);
                std::string item;
                std::vector<std::string> parts;
                while(opStream>>item) {
                    parts.push_back(item);
                }
                availableOpRead.push_back(parts);
            }else if(key=="AvailableCarpet") {
                numOfCarpet.push_back(stoi(value));
            }else if(key=="GoalJudge") {
                std::istringstream gjStream(value);
                std::string item;
                std::vector<std::string> parts;
                while(gjStream>>item) {
                    parts.push_back(item);
                }
                goalJudgeRead.push_back(parts);
            } else if(key=="NumOfCarpet"){
                numOfCarpet.push_back(std::stoi(value));
            }
        }
    }
}

void MainWindow::loadandback(){
    qDebug()<<"Num of levels:"<<games.size();
    for(int i=0;i<games.size();++i){
        for(int j=0;j<games[i].initialInbox.size();++j){
            qDebug()<<i<<QString::fromStdString(games[i].initialInbox[j]);
        }
        qDebug()<<" "<<(games[i].passed ? "PASSED" : "NOT PASSED");
    }
    ui->stackedWidget->setCurrentWidget(ui->welcomePage);
}
