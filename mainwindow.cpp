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
#include <set>
#include <cstdlib>
#include "nunchunk.h"
#include <QMovie>

int level=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stateUpdateTimer(new QTimer(this)){
    ui->setupUi(this);

    QMovie *currentMovie1=ui->labelWelcomeMovieRobot->movie();
    if(!currentMovie1) {
        movieRobot=new QMovie("/Users/lorenzlorentz/HRM/build/Desktop_Qt_5_15_17_for_macOS_Universal-Debug/movieRobot.gif");
        if(!movieRobot->isValid()) {
            qDebug()<<"GIF failed to load. Error code:"<<movieRobot->lastError();
        } else {
            ui->labelWelcomeMovieRobot->setScaledContents(true);
            ui->labelWelcomeMovieRobot->setMovie(movieRobot);
            movieRobot->start();
        }
    }

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
    connect(ui->buttonLevelchoiceLevel4,&QPushButton::clicked,this,[=](){level=3,showGame();});
    connect(ui->buttonLevelchoiceLevel5,&QPushButton::clicked,this,[=](){level=4,showGameNunchunk();});
    connect(ui->buttonLevelchoiceBack,&QPushButton::clicked,this,&MainWindow::buttonBackWelcomepageClicked);

    //playgmae界面
    connect(ui->buttonPlaygameStart,&QPushButton::clicked,this,&MainWindow::buttonStartJudgeClicked);
    connect(ui->buttonPlaygameSkip,&QPushButton::clicked,this,&MainWindow::skiptoend);
    connect(ui->buttonPlaygameStartNunchunk,&QPushButton::clicked,this,&MainWindow::buttonStartJudgeClicked);
    connect(ui->buttonPlaygameSkipNunchunk,&QPushButton::clicked,this,&MainWindow::skiptoend);
    connect(ui->buttonPlaygameSpeedup,&QPushButton::clicked,this,&MainWindow::speedup);
    connect(ui->buttonPlaygameSpeedupNunchunk,&QPushButton::clicked,this,&MainWindow::speedup);

    connect(ui->buttonPlaygameSlowdown,&QPushButton::clicked,this,&MainWindow::slowdown);
    connect(ui->buttonPlaygameStepbystep,&QPushButton::clicked,this,&MainWindow::stepbystep);
    connect(ui->buttonPlaygameRunnonstop,&QPushButton::clicked,this,&MainWindow::runnonstop);
    connect(ui->buttonPlaygameStop,&QPushButton::clicked,this,&MainWindow::stop);

    connect(ui->buttonPlaygameSlowdownNunchunk,&QPushButton::clicked,this,&MainWindow::slowdown);
    connect(ui->buttonPlaygameStepbystepNunchunk,&QPushButton::clicked,this,&MainWindow::stepbystep);
    connect(ui->buttonPlaygameRunnonstopNunchunk,&QPushButton::clicked,this,&MainWindow::runnonstop);
    connect(ui->buttonPlaygameStopNunchunk,&QPushButton::clicked,this,&MainWindow::stop);

    //初始化处理状态定时器
    stateUpdateTimer=new QTimer(this);
    //moveTimer=new QTimer(this);
    connect(stateUpdateTimer,&QTimer::timeout,this,&MainWindow::updateProcessingState);
    //connect(moveTimer,&QTimer::timeout,this,&MainWindow::moveMachine);

    //loadgame界面
    connect(ui->buttonLoadgameLoadlevelinfo,&QPushButton::clicked,this,&MainWindow::loadLevelinfo);
    connect(ui->buttonLoadgameLoadarchive,&QPushButton::clicked,this,&MainWindow::loadArchive);
    connect(ui->buttonLoadgameBackandload,&QPushButton::clicked,this,&MainWindow::loadandback);
    connect(ui->buttonLoadgameAutoload,&QPushButton::clicked,this,&MainWindow::loadAuto);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::clearLayout(QLayout* layout) {
    if(!layout) return;
    while (QLayoutItem* item=layout->takeAt(0)) {
        if (QWidget* widget=item->widget()) {
            delete widget;
        }
        if (QLayout* childLayout=item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}

void MainWindow::queueClear(std::queue<std::string>& q){
    std::queue<std::string> empty;
    swap(empty, q);
}

void MainWindow::buttonEnterClicked() {
    if(games.empty()){
        QMessageBox::warning(this,"warning","You've not loaded game info");
        return;
    }

    ui->labelWelcomeMovieRobot->clear();
    if(movieRobot){
        movieRobot->stop();
        delete movieRobot;
        movieRobot=nullptr;
    }

    if(games[0].passed&&ui->buttonLevelchoiceLevel1->text().toStdString().find("PASSED") == std::string::npos){
        QString currentText=ui->buttonLevelchoiceLevel1->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel1->setText(updatedText);
    }
    if(games[1].passed&&ui->buttonLevelchoiceLevel2->text().toStdString().find("PASSED") == std::string::npos){
        QString currentText=ui->buttonLevelchoiceLevel2->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel2->setText(updatedText);
    }
    if(games[2].passed&&ui->buttonLevelchoiceLevel3->text().toStdString().find("PASSED") == std::string::npos){
        QString currentText=ui->buttonLevelchoiceLevel3->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel3->setText(updatedText);
    }
    if(games[3].passed&&ui->buttonLevelchoiceLevel4->text().toStdString().find("PASSED") == std::string::npos){
        QString currentText=ui->buttonLevelchoiceLevel4->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel4->setText(updatedText);
    }
    if(games[4].passed&&ui->buttonLevelchoiceLevel5->text().toStdString().find("PASSED") == std::string::npos){
        QString currentText=ui->buttonLevelchoiceLevel5->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel5->setText(updatedText);
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

void MainWindow::buttonLoadgameClicked() {
    ui->labelWelcomeMovieRobot->clear();
    if(movieRobot){
        movieRobot->stop();
        delete movieRobot;
        movieRobot=nullptr;
    }

    ui->stackedWidget->setCurrentWidget(ui->loadgame);
}

void MainWindow::buttonBackClicked() {
    QWidget *playGamePage=ui->playgame;
    if(playGamePage->layout()!=nullptr){
        clearLayout(playGamePage->layout());
        delete playGamePage->layout();
    }
    playGamePage=ui->playgameNunchunk;
    if(playGamePage->layout()!=nullptr){
        clearLayout(playGamePage->layout());
        delete playGamePage->layout();
    }

    ui->labelSuccessMovieFirework->clear();
    if(firework!=nullptr){
        firework->stop();
        delete firework;
        firework=nullptr;
    }

    if(games[0].passed&&ui->buttonLevelchoiceLevel1->text().toStdString().find("PASSED") == std::string::npos){
        QString currentText=ui->buttonLevelchoiceLevel1->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel1->setText(updatedText);
    }
    if(games[1].passed&&ui->buttonLevelchoiceLevel2->text().toStdString().find("PASSED") == std::string::npos){
        QString currentText=ui->buttonLevelchoiceLevel2->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel2->setText(updatedText);
    }
    if(games[2].passed&&ui->buttonLevelchoiceLevel3->text().toStdString().find("PASSED") == std::string::npos){
        QString currentText=ui->buttonLevelchoiceLevel3->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel3->setText(updatedText);
    }
    if(games[3].passed&&ui->buttonLevelchoiceLevel4->text().toStdString().find("PASSED") == std::string::npos){
        QString currentText=ui->buttonLevelchoiceLevel4->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel4->setText(updatedText);
    }
    if(games[4].passed&&ui->buttonLevelchoiceLevel5->text().toStdString().find("PASSED") == std::string::npos){
        QString currentText=ui->buttonLevelchoiceLevel5->text();
        QString updatedText=currentText+" PASSED";
        ui->buttonLevelchoiceLevel5->setText(updatedText);
    }
    ui->stackedWidget->setCurrentWidget(ui->levelchoice);
}

void MainWindow::buttonBackWelcomepageClicked(){
    QMovie *currentMovie1=ui->labelWelcomeMovieRobot->movie();
    if(!currentMovie1) {
        movieRobot=new QMovie("/Users/lorenzlorentz/HRM/build/Desktop_Qt_5_15_17_for_macOS_Universal-Debug/movieRobot.gif");
        if(!movieRobot->isValid()) {
            qDebug()<<"GIF failed to load. Error code:"<<movieRobot->lastError();
        } else {
            ui->labelWelcomeMovieRobot->setScaledContents(true);
            ui->labelWelcomeMovieRobot->setMovie(movieRobot);
            movieRobot->start();
        }
    }

    ui->stackedWidget->setCurrentWidget(ui->welcomePage);
}

void MainWindow::buttonRestartClicked() {
    startJudgeCheck=false;
    speedinverse=1000;
    if(level<=3){
        machine=new Humanmachine(this);
        machine->setFixedSize(400, 600);
        machine->lower();

        ui->stackedWidget->setCurrentWidget(ui->playgame);
        if (!machine) {
            qDebug()<<"初始化失败";
        } else {
            qDebug()<<"初始化正常";
        }
        QWidget *playGamePage=ui->playgame;
        if(playGamePage->layout()!=nullptr){
            clearLayout(playGamePage->layout());
            delete playGamePage->layout();
        }
        QVBoxLayout *layout=new QVBoxLayout(playGamePage);
        layout->addWidget(machine);
        machine->resetDirec();
        ui->stackedWidget->setCurrentWidget(ui->playgame);
        std::string showInitialInbox;
        for(int i=0;i<games[level].initialInbox.size();++i){
            showInitialInbox+=games[level].initialInbox[i]+" ";
        }
        ui->showPlaygameInboxbar->setHtml(QString::fromStdString(showInitialInbox));
        ui->showPlaygameLogbar->setHtml(QString::fromStdString(games[level].descrip));
    } else if(level>=4){
        machine=new Humanmachine(this);
        machine->setFixedSize(400, 600);
        machine->lower();
        ui->stackedWidget->setCurrentWidget(ui->playgameNunchunk);
        if (!machine) {
            qDebug()<<"初始化失败";
        } else {
            qDebug()<<"初始化正常";
        }
        QWidget *playGamePage=ui->playgameNunchunk;
        if(playGamePage->layout()!=nullptr){
            clearLayout(playGamePage->layout());
            delete playGamePage->layout();
        }
        QVBoxLayout *layout=new QVBoxLayout(playGamePage);
        layout->addWidget(machine);
        machine->resetDirec();

        ui->stackedWidget->setCurrentWidget(ui->playgameNunchunk);

        std::string showInitialInbox;
        for(int i=0;i<games[level].initialInbox.size();++i){
            showInitialInbox+=games[level].initialInbox[i]+" ";
        }
        ui->showPlaygameInboxbarNunchunk->setHtml(QString::fromStdString(showInitialInbox));
        ui->showPlaygameLogbarNunchunk->setHtml(QString::fromStdString(games[level].descrip));
    }
}

void MainWindow::showGame(){
    startJudgeCheck=false;
    speedinverse=1000;
    qDebug()<<"开始游戏";

    if(games[level].initialInbox.empty()){
        QMessageBox::warning(this,"Warning","You've not loaded game info");
        return;
    }

    if(level>=1){
        if(!games[level-1].passed) {
            QMessageBox::warning(this,"Warning","You've not passed previous level");
            return;
        }
    }

    machine=new Humanmachine(this);
    machine->setFixedSize(400,600);

    machine->lower();
    ui->stackedWidget->setCurrentWidget(ui->playgame);
    if (!machine) {
        qDebug()<<"初始化失败";
    } else {
        qDebug()<<"初始化正常";
    }
    QWidget *playGamePage=ui->playgame;
    if(playGamePage->layout()!=nullptr){
        clearLayout(playGamePage->layout());
        delete playGamePage->layout();
    }
    QVBoxLayout *layout=new QVBoxLayout(playGamePage);
    layout->addWidget(machine);
    machine->resetDirec();

    std::string showInitialInbox;
    for(int i=0;i<games[level].initialInbox.size();++i){
        showInitialInbox+=games[level].initialInbox[i]+" ";
    }
    ui->showPlaygameInboxbar->setPlainText(QString::fromStdString(showInitialInbox));
    ui->showPlaygameLogbar->setPlainText(QString::fromStdString(games[level].descrip));
}

void MainWindow::showGameNunchunk(){
    startJudgeCheck=false;
    speedinverse=1000;
    qDebug()<<"开始游戏";

    if(games[level].initialInbox.empty()){
        QMessageBox::warning(this,"Warning","You've not loaded game info");
        return;
    }

    if(level>=1){
        if(!games[level-1].passed) {
            QMessageBox::warning(this,"Warning","You've not passed previous level");
            return;
        }
    }

    machine=new Humanmachine(this);
    machine->setFixedSize(400, 600);
    machine->lower();
    ui->stackedWidget->setCurrentWidget(ui->playgameNunchunk);
    if (!machine) {
        qDebug()<<"初始化失败";
    } else {
        qDebug()<<"初始化正常";
    }
    QWidget *playGamePage=ui->playgameNunchunk;
    if(playGamePage->layout()!=nullptr){
        clearLayout(playGamePage->layout());
        delete playGamePage->layout();
    }
    QVBoxLayout *layout=new QVBoxLayout(playGamePage);
    layout->addWidget(machine);
    machine->resetDirec();

    std::string showInitialInbox;
    for(int i=0;i<2;++i){
        showInitialInbox+=games[level].initialInbox[i]+" ";
    }
    showInitialInbox+="\n";
    for(int i=2;i<games[level].initialInbox.size();++i){
        showInitialInbox+=games[level].initialInbox[i]+" ";
    }
    qDebug()<<"!!!"<<QString::fromStdString(showInitialInbox);
    /*
    *                size_t startPos = 0;
                string from="\\n";
                string to="\n";
                while((startPos=value.find(from,startPos))!=std::string::npos) {
                    value.replace(startPos,from.length(),to);
                    startPos+=to.length();
                }
                descripRead.push_back(value);
    */
    ui->showPlaygameInboxbarNunchunk->setPlainText(QString::fromStdString(showInitialInbox));
    ui->showPlaygameLogbarNunchunk->setPlainText(QString::fromStdString(games[level].descrip));
}

void MainWindow::buttonStartJudgeClicked() {
    if(startJudgeCheck){
        return;
    }

    startJudgeCheck=true;
    QString commandInput;
    if(level<=3){
        commandInput=ui->inputPlaygameCommand->toPlainText();
    } else if(level>=4){
        commandInput=ui->inputPlaygameCommandNunchunk->toPlainText();
    }
    if(!commandInput.isEmpty()) {
        qDebug()<<"User input:"<<commandInput;
    } else {
        ui->inputPlaygameCommand->clear();
        ui->inputPlaygameCommandNunchunk->clear();
        return;
    }

    ui->showPlaygameLogbar->clear();
    ui->showPlaygameLogbarNunchunk->clear();

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

    games[level].onCarpet11Update=[this](const std::string& state){
        carpet11StateQueue.push(state);
    };
    games[level].onCarpet12Update=[this](const std::string& state){
        carpet12StateQueue.push(state);
    };
    games[level].onCarpet13Update=[this](const std::string& state){
        carpet13StateQueue.push(state);
    };
    games[level].onCarpet14Update=[this](const std::string& state){
        carpet14StateQueue.push(state);
    };
    games[level].onCarpet15Update=[this](const std::string& state){
        carpet15StateQueue.push(state);
    };
    games[level].onCarpet16Update=[this](const std::string& state){
        carpet16StateQueue.push(state);
    };

    games[level].onCarpet21Update=[this](const std::string& state){
        carpet21StateQueue.push(state);
    };
    games[level].onCarpet22Update=[this](const std::string& state){
        carpet22StateQueue.push(state);
    };
    games[level].onCarpet23Update=[this](const std::string& state){
        carpet23StateQueue.push(state);
    };
    games[level].onCarpet24Update=[this](const std::string& state){
        carpet24StateQueue.push(state);
    };
    games[level].onCarpet25Update=[this](const std::string& state){
        carpet25StateQueue.push(state);
    };
    games[level].onCarpet26Update=[this](const std::string& state){
        carpet26StateQueue.push(state);
    };

    games[level].onCarpet31Update=[this](const std::string& state){
        carpet31StateQueue.push(state);
    };
    games[level].onCarpet32Update=[this](const std::string& state){
        carpet32StateQueue.push(state);
    };
    games[level].onCarpet33Update=[this](const std::string& state){
        carpet33StateQueue.push(state);
    };
    games[level].onCarpet34Update=[this](const std::string& state){
        carpet34StateQueue.push(state);
    };
    games[level].onCarpet35Update=[this](const std::string& state){
        carpet35StateQueue.push(state);
    };
    games[level].onCarpet36Update=[this](const std::string& state){
        carpet36StateQueue.push(state);
    };

    games[level].onCarpet41Update=[this](const std::string& state){
        carpet41StateQueue.push(state);
    };
    games[level].onCarpet42Update=[this](const std::string& state){
        carpet42StateQueue.push(state);
    };
    games[level].onCarpet43Update=[this](const std::string& state){
        carpet43StateQueue.push(state);
    };
    games[level].onCarpet44Update=[this](const std::string& state){
        carpet44StateQueue.push(state);
    };
    games[level].onCarpet45Update=[this](const std::string& state){
        carpet45StateQueue.push(state);
    };
    games[level].onCarpet46Update=[this](const std::string& state){
        carpet46StateQueue.push(state);
    };

    games[level].onCarpet51Update=[this](const std::string& state){
        carpet51StateQueue.push(state);
    };
    games[level].onCarpet52Update=[this](const std::string& state){
        carpet52StateQueue.push(state);
    };
    games[level].onCarpet53Update=[this](const std::string& state){
        carpet53StateQueue.push(state);
    };
    games[level].onCarpet54Update=[this](const std::string& state){
        carpet54StateQueue.push(state);
    };
    games[level].onCarpet55Update=[this](const std::string& state){
        carpet55StateQueue.push(state);
    };
    games[level].onCarpet56Update=[this](const std::string& state){
        carpet56StateQueue.push(state);
    };


    games[level].onHandUpdate=[this](const std::string& state){
        handStateQueue.push(state);
    };

    games[level].endSuccessUpdate=[this](const int& actualStepsSet,const int& numOfCommandsSet,const std::string& showOutputSet){
        qDebug()<<"回调函数1被调用";
        actualSteps=actualStepsSet;
        numOfCommands=numOfCommandsSet;
        showOutput=showOutputSet;
        qDebug()<<"回调函数1"<<actualSteps<<" "<<numOfCommands<<" "<<QString::fromStdString(showOutput);
        qDebug()<<actualStepsSet<<" "<<numOfCommandsSet<<" "<<QString::fromStdString(showOutputSet);
    };
    games[level].endFailUpdate=[this](const std::string& whereErrorSet){
        qDebug()<<"回调函数2被调用";
        whereError=whereErrorSet;
    };

    std::string inputStreamString=commandInput.toStdString();
    std::istringstream inputStream(inputStreamString);
    ifWin=games[level].playgame(inputStream);

    qDebug()<<(ifWin ? "win" : "notwin");

    ui->showPlaygameInboxbar->clear();
    ui->showPlaygameInboxbarNunchunk->clear();
    stateUpdateTimer->start(speedinverse);
    stateUpdateTimer->stop();

    //
    startProcessing=true;
    updateProcessingState();
    //
}

void MainWindow::speedup(){
    if(!startJudgeCheck){
        QMessageBox::warning(this,"warning","NOT START");
        return;
    }
    stateUpdateTimer->stop();
    if(speedinverse>1){
        speedinverse/=10;
        stateUpdateTimer->start(speedinverse);
    }
}

void MainWindow::slowdown(){
    if(!startJudgeCheck){
        QMessageBox::warning(this,"warning","NOT START");
        return;
    }
    stateUpdateTimer->stop();
    if(speedinverse<1000){
        speedinverse*=10;
        stateUpdateTimer->start(speedinverse);
    } else if(speedinverse<8000){
        speedinverse*=2;
        stateUpdateTimer->start(speedinverse);
    }
}

void MainWindow::stepbystep(){
    if(!startJudgeCheck){
        QMessageBox::warning(this,"warning","NOT START");
        return;
    }
    if(!stateUpdateTimer->isActive()){
        stateUpdateTimer->stop();
    }
    updateProcessingState();
}

void MainWindow::runnonstop(){
    if(!startJudgeCheck){
        QMessageBox::warning(this,"warning","NOT START");
        return;
    }
    if(!stateUpdateTimer->isActive()) {
        stateUpdateTimer->start(speedinverse);
    }
}

void MainWindow::stop(){
    if(!startJudgeCheck){
        QMessageBox::warning(this,"warning","NOT START");
        return;
    }
    stateUpdateTimer->stop();
}

void MainWindow::updateProcessingState() {
    //
    //if(!machine->isRotationCompleted) return;
    //

    if(level<=3){
        if(!games[level].actionLog.empty()){
            const std::set<std::string> carpetAction={"copyto","copyfrom","copyifpos","copyifneg","add","sub"};
            const std::set<std::string> jumphandAction={"zero","pos","neg","hand+","hand-"};
            std::string currentAction = games[level].actionLog.front();
            if(games[level].actionLog.front()=="inbox"){
                machine->moveMachine(machine->inixPos,machine->iniyPos,games[level].actionLog.front());
            } else if(games[level].actionLog.front()=="outbox"){
                machine->moveMachine(machine->inixPos,350,games[level].actionLog.front());
            } else if(carpetAction.find(games[level].actionLog.front())!=carpetAction.end()){
                machine->moveMachine(260,150,games[level].actionLog.front());
            } else if(jumphandAction.find(games[level].actionLog.front())!=jumphandAction.end()){
                machine->moveMachine(machine->xPos,machine->yPos,games[level].actionLog.front());
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
            //machine->rotateHand(120);
        }
        if(handStateQueue.empty()) {
            //machine->rotateHand(30);
        }
        if(logStateQueue.empty()&&inboxbarStateQueue.empty()&&outboxbarStateQueue.empty()&&carpet1StateQueue.empty()&&carpet2StateQueue.empty()&&carpet3StateQueue.empty()&&carpet4StateQueue.empty()){
            qDebug()<<"All queues are empty";
            stateUpdateTimer->stop();
            ui->inputPlaygameCommand->clear();
            ui->inputPlaygameCommandNunchunk->clear();
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

                ui->textEditSuccessOutput->clear();
                ui->textEditSuccessActualsteps->clear();
                ui->textEditSuccessNumofcmd->clear();

                qDebug()<<QString::fromStdString(showOutput);
                qDebug()<<actualSteps;
                qDebug()<<numOfCommands;

                ui->textEditSuccessOutput->setText(QString::fromStdString(showOutput));
                ui->textEditSuccessActualsteps->setText(QString::fromStdString(std::to_string(actualSteps)));
                ui->textEditSuccessNumofcmd->setText(QString::fromStdString(std::to_string(numOfCommands)));


                QMovie *currentMovie2=ui->labelSuccessMovieFirework->movie();
                if(!currentMovie2) {
                    firework=new QMovie("/Users/lorenzlorentz/HRM/build/Desktop_Qt_5_15_17_for_macOS_Universal-Debug/movieFirework.gif");
                    if(!firework->isValid()) {
                        qDebug()<<"GIF failed to load. Error code:"<<firework->lastError();
                    } else {
                        ui->labelSuccessMovieFirework->setScaledContents(true);
                        ui->labelSuccessMovieFirework->setMovie(firework);
                        firework->start();
                    }
                }

                ui->stackedWidget->setCurrentWidget(ui->success);
            } else {
                qDebug()<<"Fail";

                ui->showFailError->clear();
                ui->showFailError->setText(QString::fromStdString(whereError));

                ui->stackedWidget->setCurrentWidget(ui->fail);
            }
        }
    } else if(level>=4){
        if(!games[level].actionLog.empty()){
            const std::set<std::string> carpetAction={"copyto","copyfrom","copyifpos","copyifneg","add","sub"};
            const std::set<std::string> jumphandAction={"zero","pos","neg","hand+","hand-"};
            std::string currentAction = games[level].actionLog.front();
            if(games[level].actionLog.front()=="inbox"){
                machine->moveMachine(machine->inixPos,machine->iniyPos,games[level].actionLog.front());
            } else if(games[level].actionLog.front()=="outbox"){
                machine->moveMachine(machine->inixPos,350,games[level].actionLog.front());
            } else if(carpetAction.find(games[level].actionLog.front())!=carpetAction.end()){
                machine->moveMachine(260,150,games[level].actionLog.front());
            } else if(jumphandAction.find(games[level].actionLog.front())!=jumphandAction.end()){
                machine->moveMachine(machine->xPos,machine->yPos,games[level].actionLog.front());
            }
            games[level].actionLog.pop();
        }

        if(!logStateQueue.empty()) {
            qDebug()<<"logbar:"<<QString::fromStdString(logStateQueue.front());
            std::string logState=logStateQueue.front();
            logStateQueue.pop();
            ui->showPlaygameLogbarNunchunk->append(QString::fromStdString(logState));
        }

        if(!inboxbarStateQueue.empty()) {
            qDebug()<<"inboxbar"<<QString::fromStdString(inboxbarStateQueue.front());
            std::string inboxbarState=inboxbarStateQueue.front();
            inboxbarStateQueue.pop();
            ui->showPlaygameInboxbarNunchunk->setHtml(QString::fromStdString(inboxbarState));
        }

        if(!outboxbarStateQueue.empty()) {
            qDebug()<<"outboxbar"<<QString::fromStdString(outboxbarStateQueue.front());
            std::string outboxbarState=outboxbarStateQueue.front();
            outboxbarStateQueue.pop();
            ui->showPlaygameOutboxbarNunchunk->setHtml(QString::fromStdString(outboxbarState));
        }


        if(!carpet11StateQueue.empty()) {
            qDebug()<<"carpet11"<<QString::fromStdString(carpet11StateQueue.front());
            std::string carpet11State=carpet11StateQueue.front();
            carpet11StateQueue.pop();
            ui->showPlaygameCarpet11Nunchunk->setHtml(QString::fromStdString(carpet11State));
        }
        if(!carpet12StateQueue.empty()) {
            qDebug()<<"carpet12"<<QString::fromStdString(carpet12StateQueue.front());
            std::string carpet12State=carpet12StateQueue.front();
            carpet12StateQueue.pop();
            ui->showPlaygameCarpet12Nunchunk->setHtml(QString::fromStdString(carpet12State));
        }
        if(!carpet13StateQueue.empty()) {
            qDebug()<<"carpet13"<<QString::fromStdString(carpet13StateQueue.front());
            std::string carpet13State=carpet13StateQueue.front();
            carpet13StateQueue.pop();
            ui->showPlaygameCarpet13Nunchunk->setHtml(QString::fromStdString(carpet13State));
        }
        if(!carpet14StateQueue.empty()) {
            qDebug()<<"carpet14"<<QString::fromStdString(carpet14StateQueue.front());
            std::string carpet14State=carpet14StateQueue.front();
            carpet14StateQueue.pop();
            ui->showPlaygameCarpet14Nunchunk->setHtml(QString::fromStdString(carpet14State));
        }
        if(!carpet15StateQueue.empty()) {
            qDebug()<<"carpet15"<<QString::fromStdString(carpet15StateQueue.front());
            std::string carpet15State=carpet15StateQueue.front();
            carpet15StateQueue.pop();
            ui->showPlaygameCarpet15Nunchunk->setHtml(QString::fromStdString(carpet15State));
        }
        if(!carpet16StateQueue.empty()) {
            qDebug()<<"carpet16"<<QString::fromStdString(carpet16StateQueue.front());
            std::string carpet16State=carpet16StateQueue.front();
            carpet16StateQueue.pop();
            ui->showPlaygameCarpet16Nunchunk->setHtml(QString::fromStdString(carpet16State));
        }

        if(!carpet21StateQueue.empty()) {
            qDebug()<<"carpet21"<<QString::fromStdString(carpet21StateQueue.front());
            std::string carpet21State=carpet21StateQueue.front();
            carpet21StateQueue.pop();
            ui->showPlaygameCarpet21Nunchunk->setHtml(QString::fromStdString(carpet21State));
        }
        if(!carpet22StateQueue.empty()) {
            qDebug()<<"carpet22"<<QString::fromStdString(carpet22StateQueue.front());
            std::string carpet22State=carpet22StateQueue.front();
            carpet22StateQueue.pop();
            ui->showPlaygameCarpet22Nunchunk->setHtml(QString::fromStdString(carpet22State));
        }
        if(!carpet23StateQueue.empty()) {
            qDebug()<<"carpet23"<<QString::fromStdString(carpet23StateQueue.front());
            std::string carpet23State=carpet23StateQueue.front();
            carpet23StateQueue.pop();
            ui->showPlaygameCarpet23Nunchunk->setHtml(QString::fromStdString(carpet23State));
        }
        if(!carpet24StateQueue.empty()) {
            qDebug()<<"carpet24"<<QString::fromStdString(carpet24StateQueue.front());
            std::string carpet24State=carpet24StateQueue.front();
            carpet24StateQueue.pop();
            ui->showPlaygameCarpet24Nunchunk->setHtml(QString::fromStdString(carpet24State));
        }
        if(!carpet25StateQueue.empty()) {
            qDebug()<<"carpet25"<<QString::fromStdString(carpet25StateQueue.front());
            std::string carpet25State=carpet25StateQueue.front();
            carpet25StateQueue.pop();
            ui->showPlaygameCarpet25Nunchunk->setHtml(QString::fromStdString(carpet25State));
        }
        if(!carpet26StateQueue.empty()) {
            qDebug()<<"carpet26"<<QString::fromStdString(carpet26StateQueue.front());
            std::string carpet26State=carpet26StateQueue.front();
            carpet26StateQueue.pop();
            ui->showPlaygameCarpet26Nunchunk->setHtml(QString::fromStdString(carpet26State));
        }

        if(!carpet31StateQueue.empty()) {
            qDebug()<<"carpet31"<<QString::fromStdString(carpet31StateQueue.front());
            std::string carpet31State=carpet31StateQueue.front();
            carpet31StateQueue.pop();
            ui->showPlaygameCarpet31Nunchunk->setHtml(QString::fromStdString(carpet31State));
        }
        if(!carpet32StateQueue.empty()) {
            qDebug()<<"carpet32"<<QString::fromStdString(carpet32StateQueue.front());
            std::string carpet32State=carpet32StateQueue.front();
            carpet32StateQueue.pop();
            ui->showPlaygameCarpet32Nunchunk->setHtml(QString::fromStdString(carpet32State));
        }
        if(!carpet33StateQueue.empty()) {
            qDebug()<<"carpet33"<<QString::fromStdString(carpet33StateQueue.front());
            std::string carpet33State=carpet33StateQueue.front();
            carpet33StateQueue.pop();
            ui->showPlaygameCarpet33Nunchunk->setHtml(QString::fromStdString(carpet33State));
        }
        if(!carpet34StateQueue.empty()) {
            qDebug()<<"carpet34"<<QString::fromStdString(carpet34StateQueue.front());
            std::string carpet34State=carpet34StateQueue.front();
            carpet34StateQueue.pop();
            ui->showPlaygameCarpet34Nunchunk->setHtml(QString::fromStdString(carpet34State));
        }
        if(!carpet35StateQueue.empty()) {
            qDebug()<<"carpet35"<<QString::fromStdString(carpet35StateQueue.front());
            std::string carpet35State=carpet35StateQueue.front();
            carpet35StateQueue.pop();
            ui->showPlaygameCarpet35Nunchunk->setHtml(QString::fromStdString(carpet35State));
        }
        if(!carpet36StateQueue.empty()) {
            qDebug()<<"carpet36"<<QString::fromStdString(carpet36StateQueue.front());
            std::string carpet36State=carpet36StateQueue.front();
            carpet36StateQueue.pop();
            ui->showPlaygameCarpet36Nunchunk->setHtml(QString::fromStdString(carpet36State));
        }

        if(!carpet41StateQueue.empty()) {
            qDebug()<<"carpet41"<<QString::fromStdString(carpet41StateQueue.front());
            std::string carpet41State=carpet41StateQueue.front();
            carpet41StateQueue.pop();
            ui->showPlaygameCarpet41Nunchunk->setHtml(QString::fromStdString(carpet41State));
        }
        if(!carpet42StateQueue.empty()) {
            qDebug()<<"carpet42"<<QString::fromStdString(carpet42StateQueue.front());
            std::string carpet42State=carpet42StateQueue.front();
            carpet42StateQueue.pop();
            ui->showPlaygameCarpet42Nunchunk->setHtml(QString::fromStdString(carpet42State));
        }
        if(!carpet43StateQueue.empty()) {
            qDebug()<<"carpet43"<<QString::fromStdString(carpet43StateQueue.front());
            std::string carpet43State=carpet43StateQueue.front();
            carpet43StateQueue.pop();
            ui->showPlaygameCarpet43Nunchunk->setHtml(QString::fromStdString(carpet43State));
        }
        if(!carpet44StateQueue.empty()) {
            qDebug()<<"carpet44"<<QString::fromStdString(carpet44StateQueue.front());
            std::string carpet44State=carpet44StateQueue.front();
            carpet44StateQueue.pop();
            ui->showPlaygameCarpet44Nunchunk->setHtml(QString::fromStdString(carpet44State));
        }
        if(!carpet45StateQueue.empty()) {
            qDebug()<<"carpet45"<<QString::fromStdString(carpet45StateQueue.front());
            std::string carpet45State=carpet45StateQueue.front();
            carpet45StateQueue.pop();
            ui->showPlaygameCarpet45Nunchunk->setHtml(QString::fromStdString(carpet45State));
        }
        if(!carpet46StateQueue.empty()) {
            qDebug()<<"carpet46"<<QString::fromStdString(carpet46StateQueue.front());
            std::string carpet46State=carpet46StateQueue.front();
            carpet46StateQueue.pop();
            ui->showPlaygameCarpet46Nunchunk->setHtml(QString::fromStdString(carpet46State));
        }


        if(!carpet51StateQueue.empty()) {
            qDebug()<<"carpet51"<<QString::fromStdString(carpet51StateQueue.front());
            std::string carpet51State=carpet51StateQueue.front();
            carpet51StateQueue.pop();
            ui->showPlaygameCarpet51Nunchunk->setHtml(QString::fromStdString(carpet51State));
        }
        if(!carpet52StateQueue.empty()) {
            qDebug()<<"carpet52"<<QString::fromStdString(carpet52StateQueue.front());
            std::string carpet52State=carpet52StateQueue.front();
            carpet52StateQueue.pop();
            ui->showPlaygameCarpet52Nunchunk->setHtml(QString::fromStdString(carpet52State));
        }
        if(!carpet53StateQueue.empty()) {
            qDebug()<<"carpet53"<<QString::fromStdString(carpet53StateQueue.front());
            std::string carpet53State=carpet53StateQueue.front();
            carpet53StateQueue.pop();
            ui->showPlaygameCarpet53Nunchunk->setHtml(QString::fromStdString(carpet53State));
        }
        if(!carpet54StateQueue.empty()) {
            qDebug()<<"carpet54"<<QString::fromStdString(carpet54StateQueue.front());
            std::string carpet54State=carpet54StateQueue.front();
            carpet54StateQueue.pop();
            ui->showPlaygameCarpet54Nunchunk->setHtml(QString::fromStdString(carpet54State));
        }
        if(!carpet55StateQueue.empty()) {
            qDebug()<<"carpet55"<<QString::fromStdString(carpet55StateQueue.front());
            std::string carpet55State=carpet55StateQueue.front();
            carpet55StateQueue.pop();
            ui->showPlaygameCarpet55Nunchunk->setHtml(QString::fromStdString(carpet55State));
        }
        if(!carpet56StateQueue.empty()) {
            qDebug()<<"carpet56"<<QString::fromStdString(carpet56StateQueue.front());
            std::string carpet56State=carpet56StateQueue.front();
            carpet56StateQueue.pop();
            ui->showPlaygameCarpet56Nunchunk->setHtml(QString::fromStdString(carpet56State));
        }


        if(!handStateQueue.empty()) {
            qDebug()<<"hand"<<QString::fromStdString(handStateQueue.front());
            std::string handState=handStateQueue.front();
            handStateQueue.pop();
            machine->handTextBrowser->setHtml("<font size=\"36>\"<b>"+QString::fromStdString(handState)+"</b></font>");
            //machine->rotateHand(120);
        }
        if(handStateQueue.empty()) {
            //machine->rotateHand(30);
        }
        if(logStateQueue.empty()&&inboxbarStateQueue.empty()&&outboxbarStateQueue.empty()&&carpet1StateQueue.empty()&&carpet2StateQueue.empty()&&carpet3StateQueue.empty()&&carpet4StateQueue.empty()){
            qDebug()<<"All queues are empty";
            stateUpdateTimer->stop();
            ui->inputPlaygameCommand->clear();
            ui->inputPlaygameCommandNunchunk->clear();
            ui->showPlaygameLogbarNunchunk->clear();
            ui->showPlaygameInboxbarNunchunk->clear();
            ui->showPlaygameOutboxbarNunchunk->clear();

            ui->showPlaygameCarpet11Nunchunk->clear();
            ui->showPlaygameCarpet12Nunchunk->clear();
            ui->showPlaygameCarpet13Nunchunk->clear();
            ui->showPlaygameCarpet14Nunchunk->clear();
            ui->showPlaygameCarpet15Nunchunk->clear();
            ui->showPlaygameCarpet16Nunchunk->clear();

            ui->showPlaygameCarpet21Nunchunk->clear();
            ui->showPlaygameCarpet22Nunchunk->clear();
            ui->showPlaygameCarpet23Nunchunk->clear();
            ui->showPlaygameCarpet24Nunchunk->clear();
            ui->showPlaygameCarpet25Nunchunk->clear();
            ui->showPlaygameCarpet26Nunchunk->clear();

            ui->showPlaygameCarpet31Nunchunk->clear();
            ui->showPlaygameCarpet32Nunchunk->clear();
            ui->showPlaygameCarpet33Nunchunk->clear();
            ui->showPlaygameCarpet34Nunchunk->clear();
            ui->showPlaygameCarpet35Nunchunk->clear();
            ui->showPlaygameCarpet36Nunchunk->clear();

            ui->showPlaygameCarpet41Nunchunk->clear();
            ui->showPlaygameCarpet42Nunchunk->clear();
            ui->showPlaygameCarpet43Nunchunk->clear();
            ui->showPlaygameCarpet44Nunchunk->clear();
            ui->showPlaygameCarpet45Nunchunk->clear();
            ui->showPlaygameCarpet46Nunchunk->clear();

            ui->showPlaygameCarpet51Nunchunk->clear();
            ui->showPlaygameCarpet52Nunchunk->clear();
            ui->showPlaygameCarpet53Nunchunk->clear();
            ui->showPlaygameCarpet54Nunchunk->clear();
            ui->showPlaygameCarpet55Nunchunk->clear();
            ui->showPlaygameCarpet56Nunchunk->clear();


            machine->resetDirec();
            while(!games[level].actionLog.empty()){
                games[level].actionLog.pop();
            }
            if(ifWin) {
                //暂停一下
                qDebug()<<"*****Success!";

                qDebug()<<"dwqwfhqwoifuq";

                ui->textEditSuccessOutput->clear();
                ui->textEditSuccessActualsteps->clear();
                ui->textEditSuccessNumofcmd->clear();

                qDebug()<<QString::fromStdString(showOutput);
                qDebug()<<actualSteps;
                qDebug()<<numOfCommands;

                ui->textEditSuccessOutput->setText(QString::fromStdString(showOutput));
                ui->textEditSuccessActualsteps->setText(QString::fromStdString(std::to_string(actualSteps)));
                ui->textEditSuccessNumofcmd->setText(QString::fromStdString(std::to_string(numOfCommands)));

                QMovie *currentMovie2=ui->labelSuccessMovieFirework->movie();
                if(!currentMovie2) {
                    firework=new QMovie("/Users/lorenzlorentz/HRM/build/Desktop_Qt_5_15_17_for_macOS_Universal-Debug/movieFirework.gif");
                    if(!firework->isValid()) {
                        qDebug()<<"GIF failed to load. Error code:"<<firework->lastError();
                    } else {
                        ui->labelSuccessMovieFirework->setScaledContents(true);
                        ui->labelSuccessMovieFirework->setMovie(firework);
                        firework->start();
                    }
                }

                ui->stackedWidget->setCurrentWidget(ui->success);
            } else {
                qDebug()<<"Fail";

                ui->showFailError->clear();
                ui->showFailError->setText(QString::fromStdString(whereError));

                ui->stackedWidget->setCurrentWidget(ui->fail);
            }
        }
    }
}

void MainWindow::skiptoend(){
    if(!startJudgeCheck){
        QMessageBox::warning(this,"warning","NOT START");
        return;
    }

    qDebug()<<"REALLYWIN"<<(ifWin ? "WIN!" : "NOTWIN");

    stateUpdateTimer->stop();

    queueClear(logStateQueue);
    queueClear(inboxbarStateQueue);
    queueClear(outboxbarStateQueue);

    queueClear(carpet1StateQueue);
    queueClear(carpet2StateQueue);
    queueClear(carpet3StateQueue);
    queueClear(carpet4StateQueue);

    queueClear(carpet11StateQueue);
    queueClear(carpet12StateQueue);
    queueClear(carpet13StateQueue);
    queueClear(carpet14StateQueue);
    queueClear(carpet15StateQueue);
    queueClear(carpet16StateQueue);

    queueClear(carpet21StateQueue);
    queueClear(carpet22StateQueue);
    queueClear(carpet23StateQueue);
    queueClear(carpet24StateQueue);
    queueClear(carpet25StateQueue);
    queueClear(carpet26StateQueue);

    queueClear(carpet31StateQueue);
    queueClear(carpet32StateQueue);
    queueClear(carpet33StateQueue);
    queueClear(carpet34StateQueue);
    queueClear(carpet35StateQueue);
    queueClear(carpet36StateQueue);

    queueClear(carpet41StateQueue);
    queueClear(carpet42StateQueue);
    queueClear(carpet43StateQueue);
    queueClear(carpet44StateQueue);
    queueClear(carpet45StateQueue);
    queueClear(carpet46StateQueue);

    queueClear(carpet51StateQueue);
    queueClear(carpet52StateQueue);
    queueClear(carpet53StateQueue);
    queueClear(carpet54StateQueue);
    queueClear(carpet55StateQueue);
    queueClear(carpet56StateQueue);

    ui->showPlaygameLogbar->clear();
    ui->showPlaygameLogbarNunchunk->clear();

    ui->inputPlaygameCommand->clear();

    ui->showPlaygameLogbar->clear();
    ui->showPlaygameInboxbar->clear();
    ui->showPlaygameOutboxbar->clear();

    ui->showPlaygameCarpet1->clear();
    ui->showPlaygameCarpet2->clear();
    ui->showPlaygameCarpet3->clear();
    ui->showPlaygameCarpet4->clear();

    ui->inputPlaygameCommandNunchunk->clear();

    ui->showPlaygameLogbarNunchunk->clear();
    ui->showPlaygameInboxbarNunchunk->clear();
    ui->showPlaygameOutboxbarNunchunk->clear();

    ui->showPlaygameCarpet11Nunchunk->clear();
    ui->showPlaygameCarpet12Nunchunk->clear();
    ui->showPlaygameCarpet13Nunchunk->clear();
    ui->showPlaygameCarpet14Nunchunk->clear();
    ui->showPlaygameCarpet15Nunchunk->clear();
    ui->showPlaygameCarpet16Nunchunk->clear();

    ui->showPlaygameCarpet21Nunchunk->clear();
    ui->showPlaygameCarpet22Nunchunk->clear();
    ui->showPlaygameCarpet23Nunchunk->clear();
    ui->showPlaygameCarpet24Nunchunk->clear();
    ui->showPlaygameCarpet25Nunchunk->clear();
    ui->showPlaygameCarpet26Nunchunk->clear();

    ui->showPlaygameCarpet31Nunchunk->clear();
    ui->showPlaygameCarpet32Nunchunk->clear();
    ui->showPlaygameCarpet33Nunchunk->clear();
    ui->showPlaygameCarpet34Nunchunk->clear();
    ui->showPlaygameCarpet35Nunchunk->clear();
    ui->showPlaygameCarpet36Nunchunk->clear();

    ui->showPlaygameCarpet41Nunchunk->clear();
    ui->showPlaygameCarpet42Nunchunk->clear();
    ui->showPlaygameCarpet43Nunchunk->clear();
    ui->showPlaygameCarpet44Nunchunk->clear();
    ui->showPlaygameCarpet45Nunchunk->clear();
    ui->showPlaygameCarpet46Nunchunk->clear();

    ui->showPlaygameCarpet51Nunchunk->clear();
    ui->showPlaygameCarpet52Nunchunk->clear();
    ui->showPlaygameCarpet53Nunchunk->clear();
    ui->showPlaygameCarpet54Nunchunk->clear();
    ui->showPlaygameCarpet55Nunchunk->clear();
    ui->showPlaygameCarpet56Nunchunk->clear();

    machine->resetDirec();
    while(!games[level].actionLog.empty()){
        games[level].actionLog.pop();
    }
    if(ifWin) {
        ifWin=false;
        qDebug()<<"Success!";

        qDebug()<<QString::fromStdString(showOutput);
        qDebug()<<actualSteps;
        qDebug()<<numOfCommands;

        ui->textEditSuccessOutput->clear();
        ui->textEditSuccessActualsteps->clear();
        ui->textEditSuccessNumofcmd->clear();

        ui->textEditSuccessOutput->setText(QString::fromStdString(showOutput));
        ui->textEditSuccessActualsteps->setText(QString::fromStdString(std::to_string(actualSteps)));
        ui->textEditSuccessNumofcmd->setText(QString::fromStdString(std::to_string(numOfCommands)));

        QMovie *currentMovie2=ui->labelSuccessMovieFirework->movie();
        if(!currentMovie2) {
            firework=new QMovie("/Users/lorenzlorentz/HRM/build/Desktop_Qt_5_15_17_for_macOS_Universal-Debug/movieFirework.gif");
            if(!firework->isValid()) {
                qDebug()<<"GIF failed to load. Error code:"<<firework->lastError();
            } else {
                ui->labelSuccessMovieFirework->setScaledContents(true);
                ui->labelSuccessMovieFirework->setMovie(firework);
                firework->start();
            }
        }

        ui->stackedWidget->setCurrentWidget(ui->success);
    } else {
        qDebug()<<"Fail";

        ui->showFailError->clear();
        ui->showFailError->setText(QString::fromStdString(whereError));

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
    std::vector<int> numOfCarpet2D;
    std::string line;
    std::vector<std::string> descripRead;
    while(getline(levelInfoRead,line)){
        parselLevelInfo(line,levelinfoRead,inboxBarSetRead,availableOpRead,goalJudgeRead,numOfCarpet,numOfCarpet2D,descripRead);
    }
    levelInfoRead.close();

    for(int i=0;i<inboxBarSetRead.size();++i){
        for(int j=0;j<inboxBarSetRead[i].size();++j){
            qDebug()<<i<<QString::fromStdString(inboxBarSetRead[i][j]);
        }
        for(int j=0;j<availableOpRead[i].size();++j){
            qDebug()<<i<<QString::fromStdString(availableOpRead[i][j]);
        }
        for(int j=0;j<goalJudgeRead[i].size();++j){
            qDebug()<<i<<QString::fromStdString(goalJudgeRead[i][j]);
        }
        qDebug()<<i<<numOfCarpet[i];
        qDebug()<<i<<numOfCarpet2D[i];
        qDebug()<<i<<QString::fromStdString(descripRead[i]);
    }

    games.clear();
    for(int i=0;i<levelinfoRead.size();++i) {
        //Game tempGameSet={inboxBarSetRead[i],availableOpRead[i],goalJudgeRead[i],numOfCarpet[i],1,descripRead[i]};
        //games.push_back(tempGameSet);
        games.push_back(Game(inboxBarSetRead[i],availableOpRead[i],goalJudgeRead[i],numOfCarpet[i],numOfCarpet2D[i],descripRead[i]));
        //games.emplace_back(inboxBarSetRead[i],availableOpRead[i],goalJudgeRead[i],numOfCarpet[i],numOfCarpet2D[i],descripRead[i]);
    }
    //qDebug()<<"SSSS"<<games.size();

    //games.push_back(Game(std::vector<std::string>{"1", "2"},std::vector<std::string>{"inbox", "outbox", "copyfrom", "copyto", "add", "sub", "jump", "jumpifzero","hand+","hand-"},std::vector<std::string>{"1", "2"},4,1,"第一关\n让机器人取出输入序列上的每个积木放入输出序列中"));
    //games.push_back(Game(std::vector<std::string>{"3", "9", "5", "1", "-2", "-2", "9", "-9"},std::vector<std::string>{"inbox", "outbox", "copyfrom", "copyto", "add", "sub", "jump", "jumpifzero"},std::vector<std::string>{"-6", "6", "4", "-4", "0", "0", "18", "-18"},4,1,"第二关\n对于输入序列中的每两个东西，先把第1个减去第2个，并把结果放在输出序列中，然后把第2个减去第1个，再把结果放在输出序列中，重复"));
    //games.push_back(Game(std::vector<std::string>{"6", "2", "7", "7", "-9", "3", "-3", "-3"},std::vector<std::string>{"inbox", "outbox", "copyfrom", "copyto", "add", "sub", "jump", "jumpifzero"},std::vector<std::string>{"7", "-3"},3,1,"第三关\n从输入序列中依次取2个数字，如果相等则将其中一个输出，否则扔掉。重复这个过程直到输入传送带为空"));
    //games.push_back(Game(std::vector<std::string>{"3","10","1","2","3","1000","3000","6000"},std::vector<std::string>{"inbox", "outbox", "copyfrom", "copyto", "add", "sub", "jump", "jumpifzero" , "hand+" , "hand-" , "jumpifpos" , "jumpifneg" , "copyifneg" , "copyifpos" , "hand*" , "hand/"},std::vector<std::string>{"19233"},1000,4,"第四关 \n 有N种类型的短棒，第i种短棒长度为a_i，武力值为b_i，数量无限\n\n长度为A的棒和长度为B的棒组成一个长度为A+B的棒，此时长度为A+B的棒的武力值为他们的和\n\n如果A与B的长度相等，则其武力值还要再增加233\n\n已知需要一根长M的棒，求最大的武力值是多少"));
}

void MainWindow::loadArchive(){
    if(games.empty()){
        QMessageBox::warning(this,"warning","You 've not loaded gameinfo.");
        return;
    }

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
        QMessageBox::warning(this,"warning","Can't access the gameinfo file");
        qDebug()<<"Can't access the file";
        return;
    }
    std::vector<std::string> levelinfoRead;
    std::vector<std::vector<std::string>> inboxBarSetRead;
    std::vector<std::vector<std::string>> availableOpRead;
    std::vector<std::vector<std::string>> goalJudgeRead;
    std::vector<int> numOfCarpet;
    std::vector<int> numOfCarpet2D;
    std::string line;
    std::vector<std::string> descripRead;
    while(getline(levelInfoRead,line)){
        parselLevelInfo(line,levelinfoRead,inboxBarSetRead,availableOpRead,goalJudgeRead,numOfCarpet,numOfCarpet2D,descripRead);
    }
    levelInfoRead.close();

    for(int i=0;i<inboxBarSetRead.size();++i){
        for(int j=0;j<inboxBarSetRead[i].size();++j){
            qDebug()<<i<<QString::fromStdString(inboxBarSetRead[i][j]);
        }
    }

    games.clear();
    for(int i=0;i<levelinfoRead.size();++i) {
        games.emplace_back(inboxBarSetRead[i],availableOpRead[i],goalJudgeRead[i],numOfCarpet[i],numOfCarpet2D[i],descripRead[i]);
    }

    std::ifstream archiveRead("archive.txt");
    if (!archiveRead.is_open()) {
        QMessageBox::warning(this,"warning","Can't access the archive file");
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
                     std::vector<int>& numOfCarpet,
                     std::vector<int>& numOfCarpet2D,
                     std::vector<std::string>& descripRead) {
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
            } else if(key=="GoalJudge") {
                std::istringstream gjStream(value);
                std::string item;
                std::vector<std::string> parts;
                while(gjStream>>item) {
                    parts.push_back(item);
                }
                goalJudgeRead.push_back(parts);
            } else if(key=="NumOfCarpet"){
                qDebug()<<"size:"<<numOfCarpet.size();
                qDebug()<<"1D"<<std::stoi(value);
                numOfCarpet.push_back(std::stoi(value));
            } else if(key=="NumOfCarpet2D"){
                qDebug()<<"2D"<<std::stoi(value);
                numOfCarpet2D.push_back(std::stoi(value));
            } else if(key=="Description"){
                size_t startPos = 0;
                string from="\\n";
                string to="\n";
                while((startPos=value.find(from,startPos))!=std::string::npos) {
                    value.replace(startPos,from.length(),to);
                    startPos+=to.length();
                }
                descripRead.push_back(value);
            }
        }
    }
}

void MainWindow::geneLevelNunchunk(){
    srand(time(0));
    int nNunchunkGen=(rand()%(15-1+1))+5;
    int mNunchunkGen=(rand()%(15-1+1))+5;
    std::vector<int> aNunchunkGen(nNunchunkGen);
    std::vector<int> bNunchunkGen(nNunchunkGen);
    for(int i=0;i<nNunchunkGen;++i){
        aNunchunkGen[i]=(rand()%(mNunchunkGen-1+1))+1;
        bNunchunkGen[i]=10*(rand()%(100-1+1))+1;
    }
    std::vector<std::string> inboxSetNunchunk;

    int remainNunchunk=mNunchunkGen;
    int chunkGen=0;
    while(remainNunchunk>0){
        aNunchunkGen[chunkGen]=(rand()%(remainNunchunk-1+1))+1;
        remainNunchunk-=aNunchunkGen[chunkGen];
        ++chunkGen;
    }
    for(;chunkGen<nNunchunkGen;++chunkGen){
        aNunchunkGen[chunkGen]=(rand()%(mNunchunkGen-1+1))+1;
    }
    inboxSetNunchunk.push_back(std::to_string(nNunchunkGen));
    inboxSetNunchunk.push_back(std::to_string(mNunchunkGen));
    for(int i=0;i<nNunchunkGen;++i){
        inboxSetNunchunk.push_back(std::to_string(aNunchunkGen[i]));
    }
    for(int i=0;i<nNunchunkGen;++i){
        inboxSetNunchunk.push_back(std::to_string(bNunchunkGen[i]));
    }
    std::stringstream inputStreamNunchunk;
    for(const auto& str:inboxSetNunchunk) {
        inputStreamNunchunk<<str<<" ";
    }

    Nunchunk nunchunkObj;
    std::vector<std::string> outboxSetNunchunk;
    outboxSetNunchunk.push_back(std::to_string(nunchunkObj.nunchunk(inputStreamNunchunk)));
    games.push_back(Game(inboxSetNunchunk,std::vector<std::string>{"inbox", "outbox", "copyfrom", "copyto", "add", "sub", "jump", "jumpifzero" , "hand+" , "hand-" , "jumpifpos" , "jumpifneg" , "copyifneg" , "copyifpos" , "hand0" , "jumpifposzero" , "jumpifnegzero" , "hand*" , "hand/" , "times" , "hand="},outboxSetNunchunk,30,5,"第五关\n通关要求同第四关\n新增操作: hand+ , hand- , hand= , hand0 , hand* , hand/ , times \njumpifpos , jumpifneg , jumpifposzero , jumpifnegzero , copyifneg , copyifpos \n可用空地:30 * 5"));
}

void MainWindow::loadandback(){
    if(games.empty()){
        QMessageBox::warning(this,"warning","You've not loaded game!");
        return;
    }

    geneLevelNunchunk();

    //games.push_back(Game(std::vector<std::string>{"3","5","1","2","3","1000","3000","6000"},std::vector<std::string>{"inbox", "outbox", "copyfrom", "copyto", "add", "sub", "jump", "jumpifzero" , "hand+" , "hand-" , "jumpifpos" , "jumpifneg" , """copyifneg" , "copyifpos" , "hand0" , "jumpifposzero" , "jumpifnegzero" , "hand*" , "hand/" , "times" , "hand="},std::vector<std::string>{"9000"},1000,5,"第四关 \n 有N种类型的短棒，第i种短棒长度为a_i，武力值为b_i，数量无限\n\n长度为A的棒和长度为B的棒组成一个长度为A+B的棒，此时长度为A+B的棒的武力值为他们的和\n\n如果A与B的长度相等，则其武力值还要再增加233\n\n已知需要一根长M的棒，求最大的武力值是多少"));

    qDebug()<<"Num of levels:"<<games.size();
    for(int i=0;i<games.size();++i){
        for(int j=0;j<games[i].initialInbox.size();++j){
            qDebug()<<i<<QString::fromStdString(games[i].initialInbox[j]);
        }
        for(int j=0;j<games[i].goal.size();++j){
            qDebug()<<i<<"goal"<<QString::fromStdString(games[i].goal[j]);
        }
        qDebug()<<QString::fromStdString(games[i].descrip);
        qDebug()<<" "<<(games[i].passed ? "PASSED" : "NOT PASSED");
    }

    QMovie *currentMovie1=ui->labelWelcomeMovieRobot->movie();
    if(!currentMovie1) {
        movieRobot=new QMovie("/Users/lorenzlorentz/HRM/build/Desktop_Qt_5_15_17_for_macOS_Universal-Debug/movieRobot.gif");
        if(!movieRobot->isValid()) {
            qDebug()<<"GIF failed to load. Error code:"<<movieRobot->lastError();
        } else {
            ui->labelWelcomeMovieRobot->setScaledContents(true);
            ui->labelWelcomeMovieRobot->setMovie(movieRobot);
            movieRobot->start();
        }
    }

    ui->stackedWidget->setCurrentWidget(ui->welcomePage);
}
