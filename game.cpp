#include "game.h"
#include <qDebug>
#include "mainwindow.h"
#include "humanmachine.h"
using namespace std;

Game::Game(vector<string> initialInboxSet,
           vector<string> availableOpsSet,
           vector<string> goalSet,
           int numOfCarpetSet,
           std::string descripSet)
    : initialInbox(initialInboxSet),
    availableOps(availableOpsSet),
    goal(goalSet),
    carpetBar(numOfCarpetSet),
    descrip(descripSet){}

bool Game::goalReached() {
    return outboxBar==goal;
}

bool Game::isLegalOperation(string& command) {
    if(command==" ") return true;
    for(int i=0;i<availableOps.size();++i) {
        if(command==availableOps[i]) {
            return true;
        }
    }
    return false;
}

void Game::updateState(){
    qDebug()<<"执行update";
    if(onInboxbarUpdate){
        string inboxbarReturn;
        for(int tempindex=0;tempindex<inboxBar.size();++tempindex){
            if(!inboxbarReturn.empty()){
                inboxbarReturn+=" | ";
            }
            inboxbarReturn+=inboxBar[tempindex];
        }
        onInboxbarUpdate(inboxbarReturn);
    }

    if(onOutboxbarUpdate){
        string outboxbarReturn;
        for(int tempindex=0;tempindex<outboxBar.size();++tempindex){
            if(!outboxbarReturn.empty()){
                outboxbarReturn+=" | ";
            }
            outboxbarReturn+=outboxBar[tempindex];
        }
        onOutboxbarUpdate(outboxbarReturn);
    }

    if(carpetBar.size()>=1){
        if(onCarpet1Update){
            onCarpet1Update(carpetBar[0]);
        }
    }

    if(carpetBar.size()>=2){
        if(onCarpet1Update){
            onCarpet2Update(carpetBar[1]);
        }
    }

    if(carpetBar.size()>=3){
        if(onCarpet1Update){
            onCarpet3Update(carpetBar[2]);
        }
    }

    if(carpetBar.size()>=4){
        if(onCarpet1Update){
            onCarpet4Update(carpetBar[3]);
        }
    }

    if(onHandUpdate){
        onHandUpdate(hand);
    }
}

bool Game::inputProcess(string &command,int& param,bool& jumpInputJudge,bool& endRun,int& numSteps) {
    if(!isLegalOperation(command)) {
        if(onLogbarUpdate) {
            onLogbarUpdate("操作不合法");
        } else {
            qDebug()<<"回调函数未赋值";
        }
        return false;
    }

    if(command=="inbox") {
        if(!jumpInputJudge) {
            if(inboxBar.empty()) {
                return false;
            }
        } else {
            jumpInputJudge=false;
            if(inboxBar.empty()) {
                endRun=true;
                return true;
            }
        }
        hand=inboxBar.front();
        inboxBar.erase(inboxBar.begin());

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("inbox");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate(inboxBar.empty() ? "inbox为空" : "将"+hand+"从inbox取出");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="outbox") {
        if(hand.empty()) {
            return false;
        }
        outboxBar.push_back(hand);
        hand="";

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("outbox");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("将"+outboxBar[0]+"放入outbox");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="copyto") {
        if(param<=0||param>carpetBar.size()) {
            return false;
        }
        if(hand.empty()) {
            return false;
        }
        carpetBar[param-1]=hand;

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("copyto");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("将"+carpetBar[param-1]+"放入carpet["+std::to_string(param-1)+"]");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="copyfrom"){
        if(param<=0||param>carpetBar.size()) {
            return false;
        }
        if(carpetBar[param-1].empty()) {
            return false;
        }
        hand=carpetBar[param-1];

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("copyfrom");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("将"+carpetBar[param-1]+"从carpet["+std::to_string(param)+"]复制到手中");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="add") {
        if(param<=0||param>carpetBar.size()) {
            return false;
        }
        if(hand.empty()) {
            return false;
        }
        if(carpetBar[param-1].empty()) {
            return false;
        }
        hand=to_string(stoi(hand)+stoi(carpetBar[param-1]));

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("add");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("将"+carpetBar[param-1]+"从carpet["+std::to_string(param)+"]加入到手中");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="sub") {
        if(param<=0||param>carpetBar.size()) {
            return false;
        }
        if(hand.empty()) {
            return false;
        }
        if(carpetBar[param-1].empty()) {
            return false;
        }
        hand=to_string(stoi(hand)-stoi(carpetBar[param-1]));

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("sub");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("将"+carpetBar[param-1]+"从carpet["+std::to_string(param)+"]在手中减去");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jump") {
        if(!(0<=param && param<numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            onLogbarUpdate("跳转到"+std::to_string(param)+"步");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jumpifzero") {
        if(!(0<=param && param<numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("zero");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("手中为零，跳转到"+std::to_string(param)+"步");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jumpifpos"){
        if(!(0<=param && param<numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("pos");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("手中为正，跳转到"+std::to_string(param)+"步");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jumpifneg"){
        if(!(0<=param && param<numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("neg");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("手中为负，跳转到"+std::to_string(param)+"步");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="hand+"){
        if(hand.empty()){
            return false;
        }
        hand=to_string(std::stoi(hand)+param);

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("hand+");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("手中加上"+std::to_string(param));
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="hand-"){
        if(hand.empty()){
            return false;
        }
        hand=to_string(std::stoi(hand)-param);

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("hand-");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("手中减去"+std::to_string(param));
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="copyifpos"){
        if(param<=0||param>carpetBar.size()) {
            return false;
        }
        if(carpetBar[param-1].empty()) {
            return false;
        }
        if(stoi(carpetBar[param-1])>0){
            hand=carpetBar[param-1];
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("copypos");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("carpet为正，将"+carpetBar[param-1]+"从carpet["+std::to_string(param)+"]复制到手中");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="copyifneg"){
        if(param<=0||param>carpetBar.size()) {
            return false;
        }
        if(carpetBar[param-1].empty()) {
            return false;
        }
        if(stoi(carpetBar[param-1])<0){
            hand=carpetBar[param-1];
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("copyneg");
            qDebug()<<"actionLog pushed";
            onLogbarUpdate("carpet为负，将"+carpetBar[param-1]+"从carpet["+std::to_string(param)+"]复制到手中");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    }
    return true;
}

bool Game::playgame(istream& inputStream) {
    outboxBar.clear();
    fill(carpetBar.begin(), carpetBar.end(), "");
    qDebug()<<"carpetsize"<<carpetBar.size();
    inboxBar=initialInbox;

    vector<string> command;
    vector<int> param;

    string inputLine;

    while(std::getline(inputStream,inputLine)) {
        if (inputLine.empty()) {
            continue;
        }

        string cmd;
        int par;

        istringstream iss(inputLine);
        iss>>cmd;

        command.push_back(cmd);
        if(iss>>par) {
            param.push_back(par);
        } else {
            param.push_back(-1);
        }
    }

    int doStep=0;
    int numSteps=command.size();
    bool endRun=false;
    bool jumpInputJudge=false;

    while(doStep<numSteps&&!endRun) {
        //jump指令的处理
        if(command[doStep]=="jump"||command[doStep]=="jumpifzero"||command[doStep]=="jumpifpos"||command[doStep]=="jumpifneg") {
            if(!inputProcess(command[doStep],param[doStep],jumpInputJudge,endRun,numSteps)) {
                qDebug()<<"Error on instruction "<<doStep+1;
                if(onLogbarUpdate) {
                    onLogbarUpdate("Error on instruction "+std::to_string(doStep+1));
                } else {
                    qDebug()<<"回调函数未赋值";
                }
                return false;
            }

            if(command[doStep]=="jump"||(command[doStep]=="jumpifzero"&&hand=="0") || (command[doStep]=="jumpifpos"&&std::stoi(hand)>0) || (command[doStep]=="jumpifneg"&&std::stoi(hand)<0)) {
                jumpInputJudge=true;
                doStep=param[doStep]-1; //跳跃至传输的参数指定的位置
            } else if(command[doStep]=="jumpifzero") {
                ++doStep;
            }
        }
        //非jump指令的处理
        else {
            if(!inputProcess(command[doStep],param[doStep],jumpInputJudge,endRun,numSteps)) {
                qDebug()<<"Error on instruction "<<doStep+1;
                if(onLogbarUpdate) {
                    onLogbarUpdate("Error on instruction "+std::to_string(doStep+1));
                } else {
                    qDebug()<<"回调函数未赋值";
                }
                return false;
            }
            ++doStep;
        }
    }

    if(goalReached()) {
        if(onLogbarUpdate) {
            onLogbarUpdate("游戏结束，胜利！");
        } else {
            qDebug()<<"回调函数未赋值";
        }
        passed=true;
        qDebug()<<"SUCCESS!!";
        return true;
    } else {
        if(onLogbarUpdate) {
            onLogbarUpdate("游戏结束，失败。");
        } else {
            qDebug()<<"回调函数未赋值";
        }
        qDebug()<<"FAIL";
        return false;
    }
}
