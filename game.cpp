#include "game.h"
#include <qDebug>
#include "mainwindow.h"
#include "humanmachine.h"
using namespace std;

Game::Game(vector<string> initialInboxSet,
           vector<string> availableOpsSet,
           vector<string> goalSet,
           int numOfCarpetSet,
           int numOfCarpet2DSet,
           std::string descripSet)
    : initialInbox(initialInboxSet),
    availableOps(availableOpsSet),
    goal(goalSet),
    carpetBar(numOfCarpet2DSet,std::vector<std::string>(numOfCarpetSet)),
    descrip(descripSet) {
    // qDebug()<<"sizeintended"<<numOfCarpet2DSet<<" "<<numOfCarpetSet<<" "<<"size"<<carpetBar.size()<<" "<<carpetBar[0].size();
}

bool Game::isValidInteger(string &input){
    std::regex validIntPattern("^-?\\d+$");
    return std::regex_match(input, validIntPattern);
}

bool Game::goalReached() {
    return outboxBar==goal;
}

std::string Game::removeSpaces(std::string& input) {
    std::string result;
    for(char ch:input) {
        if(ch!=' ') {
            result += ch;
        }
    }
    return result;
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

void Game::commandProcess(string& commandToProcess,int& param,int& paramW,string& extraParam) {
    qDebug()<<"QQQQQQ"<<QString::fromStdString(commandToProcess);
    istringstream iss(commandToProcess);
    size_t tempPos=commandToProcess.find(';');
    if(tempPos!=std::string::npos){
        qDebug()<<"two param";
        string token;
        getline(iss,token,';');
        token=removeSpaces(token);
        if(isValidInteger(token)){
            param=stoi(token);
        } else {
            qDebug()<<"notinteger"<<QString::fromStdString(token);
            param=-1;
        }
        getline(iss,token,' ');
        token=removeSpaces(token);
        if(isValidInteger(token)){
            paramW=stoi(token);
        } else {
            qDebug()<<"NOTINTEGER?"<<QString::fromStdString(token);
            paramW=-1;
        }
    } else {
        string token;
        getline(iss,token,' ');
        token=removeSpaces(token);
        if(isValidInteger(token)){
            param=stoi(token);
        } else {
            qDebug()<<"NOTINTEGER?"<<QString::fromStdString(token);
            param=-1;
        }
        paramW=1;
    }

    string tempStr;
    if(getline(iss,tempStr)) {
        extraParam=tempStr;
    } else {
        extraParam="np";
    }
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

    if(level<=3){
        if(carpetBar[0].size()>=1){
            if(onCarpet1Update){
                onCarpet1Update(carpetBar[0][0]);
            }
        }

        if(carpetBar[0].size()>=2){
            if(onCarpet1Update){
                onCarpet2Update(carpetBar[0][1]);
            }
        }

        if(carpetBar[0].size()>=3){
            if(onCarpet1Update){
                onCarpet3Update(carpetBar[0][2]);
            }
        }

        if(carpetBar[0].size()>=4){
            if(onCarpet1Update){
                onCarpet4Update(carpetBar[0][3]);
            }
        }
    } else if(level>=4){
        //1
        if(carpetBar[0].size()>=1){
            if(onCarpet11Update){
                onCarpet11Update(carpetBar[0][0]);
            }
        }
        if(carpetBar[0].size()>=2){
            if(onCarpet12Update){
                onCarpet12Update(carpetBar[0][1]);
            }
        }
        if(carpetBar[0].size()>=3){
            if(onCarpet13Update){
                onCarpet13Update(carpetBar[0][2]);
            }
        }
        if(carpetBar[0].size()>=4){
            if(onCarpet14Update){
                onCarpet14Update(carpetBar[0][3]);
            }
        }
        if(carpetBar[0].size()>=5){
            if(onCarpet15Update){
                onCarpet15Update(carpetBar[0][4]);
            }
        }
        if(carpetBar[0].size()>=6){
            if(onCarpet16Update){
                onCarpet16Update(carpetBar[0][5]);
            }
        }

        //2
        if(carpetBar[1].size()>=1){
            if(onCarpet21Update){
                onCarpet21Update(carpetBar[1][0]);
            }
        }
        if(carpetBar[1].size()>=2){
            if(onCarpet22Update){
                onCarpet22Update(carpetBar[1][1]);
            }
        }
        if(carpetBar[1].size()>=3){
            if(onCarpet23Update){
                onCarpet23Update(carpetBar[1][2]);
            }
        }
        if(carpetBar[1].size()>=4){
            if(onCarpet24Update){
                onCarpet24Update(carpetBar[1][3]);
            }
        }
        if(carpetBar[1].size()>=5){
            if(onCarpet25Update){
                onCarpet25Update(carpetBar[1][4]);
            }
        }
        if(carpetBar[1].size()>=6){
            if(onCarpet26Update){
                onCarpet26Update(carpetBar[1][5]);
            }
        }

        //3
        if(carpetBar[2].size()>=1){
            if(onCarpet31Update){
                onCarpet31Update(carpetBar[2][0]);
            }
        }
        if(carpetBar[2].size()>=2){
            if(onCarpet32Update){
                onCarpet32Update(carpetBar[2][1]);
            }
        }
        if(carpetBar[2].size()>=3){
            if(onCarpet33Update){
                onCarpet33Update(carpetBar[2][2]);
            }
        }
        if(carpetBar[2].size()>=4){
            if(onCarpet34Update){
                onCarpet34Update(carpetBar[2][3]);
            }
        }
        if(carpetBar[2].size()>=5){
            if(onCarpet35Update){
                onCarpet35Update(carpetBar[2][4]);
            }
        }
        if(carpetBar[2].size()>=6){
            if(onCarpet36Update){
                onCarpet36Update(carpetBar[2][5]);
            }
        }

        //4
        if(carpetBar[3].size()>=1){
            if(onCarpet41Update){
                onCarpet41Update(carpetBar[3][0]);
            }
        }
        if(carpetBar[3].size()>=2){
            if(onCarpet42Update){
                onCarpet42Update(carpetBar[3][1]);
            }
        }
        if(carpetBar[3].size()>=3){
            if(onCarpet43Update){
                onCarpet43Update(carpetBar[3][2]);
            }
        }
        if(carpetBar[3].size()>=4){
            if(onCarpet44Update){
                onCarpet44Update(carpetBar[3][3]);
            }
        }
        if(carpetBar[3].size()>=5){
            if(onCarpet45Update){
                onCarpet45Update(carpetBar[3][4]);
            }
        }
        if(carpetBar[3].size()>=6){
            if(onCarpet46Update){
                onCarpet46Update(carpetBar[3][5]);
            }
        }

        //5
        if(carpetBar[4].size()>=1){
            if(onCarpet51Update){
                onCarpet51Update(carpetBar[4][0]);
            }
        }
        if(carpetBar[4].size()>=2){
            if(onCarpet52Update){
                onCarpet52Update(carpetBar[4][1]);
            }
        }
        if(carpetBar[4].size()>=3){
            if(onCarpet53Update){
                onCarpet53Update(carpetBar[4][2]);
            }
        }
        if(carpetBar[4].size()>=4){
            if(onCarpet54Update){
                onCarpet54Update(carpetBar[4][3]);
            }
        }
        if(carpetBar[4].size()>=5){
            if(onCarpet55Update){
                onCarpet55Update(carpetBar[4][4]);
            }
        }
        if(carpetBar[4].size()>=6){
            if(onCarpet56Update){
                onCarpet56Update(carpetBar[4][5]);
            }
        }
    }

    if(onHandUpdate){
        onHandUpdate(hand);
    }
}

bool Game::inputProcess(string command,int param,int paramW,std::string extraParam,bool& jumpInputJudge,bool& endRun,int& numSteps) {
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
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate(inboxBar.empty() ? "inbox为空" : "将"+hand+"从inbox取出");
            qDebug()<<(inboxBar.empty() ? "inbox为空" : "将"+QString::fromStdString(hand)+"从inbox取出");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="outbox") {
        if(hand.empty()) {
            qDebug()<<"Oops! HAND EMPTY!";
            return false;
        } else {
            qDebug()<<"Hoory! Not EMPTY!";
        }
        outboxBar.push_back(hand);
        hand="";

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("outbox");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("将"+outboxBar.back()+"放入outbox");
            qDebug()<<("将"+QString::fromStdString(outboxBar[0])+"放入outbox");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="copyto") {
        if(paramW<=0||paramW>carpetBar.size()) {
            qDebug()<<paramW<<" "<<param<<" "<<QString::fromStdString(extraParam)<<" "<<carpetBar.size();
            qDebug()<<"AAAAAA";
            return false;
        }
        if(param<=0||param>carpetBar[0].size()){
            qDebug()<<"BBBBB"<<param<<" "<<carpetBar[0].size();
            return false;
        }
        if(hand.empty()) {
            qDebug()<<"CCCCC";
            return false;
        }

        if(extraParam=="np"){
            carpetBar[paramW-1][param-1]=hand;
        } else if(extraParam=="c"){
            int tempParam;
            int tempParamW;
            string tempExtraParam;
            commandProcess(carpetBar[paramW-1][param-1],tempParam,tempParamW,tempExtraParam);
            qDebug()<<"COPYTOWHERE???"<<param<<" "<<paramW<<" "<<tempParam<<" "<<tempParamW;
            param=tempParam;
            paramW=tempParamW;

            if(paramW<=0||paramW>carpetBar.size()) {
                qDebug()<<"位置1报错"<<param<<" "<<paramW;
                return false;
            }
            if(param<=0||param>carpetBar[0].size()){
                qDebug()<<"位置2报错"<<param<<" "<<paramW;
                return false;
            }
            /* if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            } */
            carpetBar[paramW-1][param-1]=hand;
        } else if(extraParam=="p1"){
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                carpetBar[paramW-1][param-1]=hand+carpetBar[paramW-1][param-1].substr(carpetBar[paramW-1][param-1].find(';'));
            } else if(carpetBar.empty()){
                carpetBar[paramW-1][param-1]=hand;
            } else {
                carpetBar[paramW-1][param-1]=hand+";"+carpetBar[paramW-1][param-1];
            }
        } else if(extraParam=="p2"){
            qDebug()<<"被执行";
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                qDebug()<<"分支1被执行";
                carpetBar[paramW-1][param-1]=carpetBar[paramW-1][param-1].substr(0,1+carpetBar[paramW-1][param-1].find(';'))+hand;
            } else if(carpetBar[paramW-1][param-1].empty()){
                qDebug()<<"分支2被执行";
                carpetBar[paramW-1][param-1]=hand;
            } else {
                qDebug()<<"WHYNOTADD?";
                qDebug()<<QString::fromStdString(carpetBar[paramW-1][param-1])<<" "<<QString::fromStdString(hand);
                carpetBar[paramW-1][param-1]=carpetBar[paramW-1][param-1]+";"+hand;
            }
        } else {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("copyto");
            qDebug()<<QString::fromStdString(command);
            qDebug()<<"actionLog pushed";
            //qDebug()<<(string(extraParam=="c" ? "调用指针," : "")+"将"+QString::fromStdString(carpetBar[paramW-1][param-1])+"放入carpet["+std::to_string(paramW-1)+"]["+std::to_string(param-1)+"]");
            qDebug() << QString::fromStdString((extraParam == "c" ? "调用指针," : ""))
                            + "将"
                            + QString::fromStdString(carpetBar[paramW - 1][param - 1])
                            + "放入carpet["
                            + QString::number(paramW - 1)
                            + "]["
                            + QString::number(param - 1)
                            + "]";
            onLogbarUpdate(string(extraParam=="c" ? "调用指针," : "")+"将"+carpetBar[paramW-1][param-1]+"放入carpet["+std::to_string(paramW-1)+"]["+std::to_string(param-1)+"]");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="copyfrom"){
        if(paramW<=0||paramW>carpetBar.size()) {
            return false;
        }
        if(param<=0||param>carpetBar[0].size()){
            return false;
        }
        if(carpetBar[paramW-1][param-1].empty()) {
            return false;
        }

        if(extraParam=="np"){
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            hand=carpetBar[paramW-1][param-1];
        } else if(extraParam=="c"){
            int tempParam;
            int tempParamW;
            string tempExtraParam;
            commandProcess(carpetBar[paramW-1][param-1],tempParam,tempParamW,tempExtraParam);
            param=tempParam;
            paramW=tempParamW;
            if(paramW<=0||paramW>carpetBar.size()) {
                return false;
            }
            if(param<=0||param>carpetBar[0].size()){
                return false;
            }
            if(carpetBar[paramW-1][param-1].empty()) {
                return false;
            }
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            hand=carpetBar[paramW-1][param-1];
            qDebug()<<"WHATDIDICOPIED?"<<QString::fromStdString(hand);
        } else {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("copyfrom");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            //qDebug()<<(string(extraParam=="c" ? "调用指针," : "")+"将"+QString::fromStdString(carpetBar[paramW-1][param-1])+"从carpet["+QString::fromStdString(std::to_string(paramW-1))+"]["+QString::fromStdString(std::to_string(param-1))+"]复制到手中");
            qDebug() << QString::fromStdString((extraParam == "c" ? "调用指针," : ""))
                            + "将"
                            + QString::fromStdString(carpetBar[paramW - 1][param - 1])
                            + "从carpet["
                            + QString::number(paramW - 1)
                            + "]["
                            + QString::number(param - 1)
                            + "]复制到手中";
            onLogbarUpdate(string(extraParam=="c" ? "调用指针," : "")+"将"+carpetBar[paramW-1][param-1]+"从carpet["+std::to_string(paramW-1)+"]["+std::to_string(param-1)+"]复制到手中");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="add") {
        if(paramW<=0||paramW>carpetBar.size()) {
            return false;
        }
        if(param<=0||param>carpetBar[0].size()){
            return false;
        }
        if(hand.empty()) {
            return false;
        }
        if(carpetBar[paramW-1][param-1].empty()){
            return false;
        }

        if(extraParam=="np"){
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            hand=to_string(stoi(hand)+stoi(carpetBar[paramW-1][param-1]));
        } else if(extraParam=="c"){
            int tempParam;
            int tempParamW;
            string tempExtraParam;
            commandProcess(carpetBar[paramW-1][param-1],tempParam,tempParamW,tempExtraParam);
            param=tempParam;
            paramW=tempParamW;
            if(paramW<=0||paramW>carpetBar.size()) {
                return false;
            }
            if(param<=0||param>carpetBar[0].size()){
                return false;
            }
            if(carpetBar[paramW-1][param-1].empty()){
                return false;
            }
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            hand=to_string(stoi(hand)+stoi(carpetBar[paramW-1][param-1]));
        } else {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("add");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate(string(extraParam=="c" ? "调用指针," : "")+"将"+carpetBar[paramW-1][param-1]+"从carpet["+std::to_string(paramW-1)+"]["+std::to_string(param-1)+"]加入到手中");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="sub") {
        if(paramW<=0||paramW>carpetBar.size()) {
            return false;
        }
        if(param<=0||param>carpetBar[0].size()){
            return false;
        }
        if(hand.empty()) {
            return false;
        }
        if(carpetBar[paramW-1][param-1].empty()){
            return false;
        }

        if(extraParam=="np"){
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            hand=to_string(stoi(hand)-stoi(carpetBar[paramW-1][param-1]));
        } else if(extraParam=="c"){
            int tempParam;
            int tempParamW;
            string tempExtraParam;
            commandProcess(carpetBar[paramW-1][param-1],tempParam,tempParamW,tempExtraParam);
            param=tempParam;
            paramW=tempParamW;
            if(paramW<=0||paramW>carpetBar.size()) {
                return false;
            }
            if(param<=0||param>carpetBar[0].size()){
                return false;
            }
            if(carpetBar[paramW-1][param-1].empty()){
                return false;
            }
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            hand=to_string(stoi(hand)-stoi(carpetBar[paramW-1][param-1]));
        } else {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("sub");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate(string(extraParam=="c" ? "调用指针," : "")+"将"+carpetBar[paramW-1][param-1]+"从carpet["+std::to_string(paramW-1)+"]["+std::to_string(param-1)+"]在手中减去");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } if(command=="times") {
        if(paramW<=0||paramW>carpetBar.size()) {
            return false;
        }
        if(param<=0||param>carpetBar[0].size()){
            return false;
        }
        if(hand.empty()) {
            return false;
        }
        if(carpetBar[paramW-1][param-1].empty()){
            return false;
        }

        if(extraParam=="np"){
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            hand=to_string(stoi(hand)*stoi(carpetBar[paramW-1][param-1]));
        } else if(extraParam=="c"){
            qDebug()<<"WRONGTYPE 5";
            int tempParam;
            int tempParamW;
            string tempExtraParam;
            commandProcess(carpetBar[paramW-1][param-1],tempParam,tempParamW,tempExtraParam);
            param=tempParam;
            paramW=tempParamW;
            if(paramW<=0||paramW>carpetBar.size()) {
                return false;
            }
            if(param<=0||param>carpetBar[0].size()){
                return false;
            }
            if(carpetBar[paramW-1][param-1].empty()){
                return false;
            }
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            hand=to_string(stoi(hand)*stoi(carpetBar[paramW-1][param-1]));
        } else {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("times");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate(string(extraParam=="c" ? "调用指针," : "")+"把"+carpetBar[paramW-1][param-1]+"从carpet["+std::to_string(paramW-1)+"]["+std::to_string(param-1)+"]在手中乘上");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jump") {
        if(!(0<param&&param<=numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("jump");
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("跳转到"+std::to_string(param)+"步");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jumpifzero") {
        if(!(0<param&&param<=numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("zero");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中为零，跳转到"+std::to_string(param)+"步");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jumpifpos"){
        if(!(0<param&&param<=numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("pos");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中为正，跳转到"+std::to_string(param)+"步");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jumpifneg"){
        if(!(0<param&&param<=numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("neg");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中为负，跳转到"+std::to_string(param)+"步");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jumpifposzero"){
        if(!(0<=param && param<=numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("poszero");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中非负，跳转到"+std::to_string(param)+"步");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jumpifnegzero"){
        if(!(0<=param && param<=numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("negzero");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中非正，跳转到"+std::to_string(param)+"步");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="hand+"){
        if(hand.empty()){
            return false;
        }

        if(param==-1){
            hand=to_string(std::stoi(hand)+1);
        } else {
            hand=to_string(std::stoi(hand)+param);
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("hand+");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中加上"+std::to_string(param));
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="hand-"){
        if(hand.empty()){
            return false;
        }

        if(param==-1){
            hand=to_string(std::stoi(hand)-1);
        } else {
            hand=to_string(std::stoi(hand)-param);
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("hand-");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中减去"+std::to_string(param));
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="hand*"){
        if(hand.empty()){
            return false;
        }

        if(param==-1){
            return false;
        } else {
            hand=to_string(std::stoi(hand)*param);
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("hand*");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中乘上"+std::to_string(param));
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="hand="){
        if(hand.empty()){
            return false;
        }

        if(param==-1){
            return false;
        } else {
            hand=to_string(param);
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("hand=");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中变为"+std::to_string(param));
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="hand/"){
        if(hand.empty()){
            return false;
        }

        if(param<=0){
            return false;
        } else {
            hand=to_string(std::stoi(hand)/param);
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("hand/");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中除以"+std::to_string(param));
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="hand0"){
        if(hand.empty()){
            return false;
        }

        hand=to_string(0);

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("hand-");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            onLogbarUpdate("手中变为0");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="copyifpos"){
        if(paramW<=0||paramW>carpetBar.size()) {
            return false;
        }
        if(param<=0||param>carpetBar[0].size()){
            return false;
        }
        if(carpetBar[param-1][paramW-1].empty()) {
            return false;
        }

        if(extraParam=="np"){
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            if(stoi(carpetBar[paramW-1][param-1])>0){
                hand=carpetBar[paramW-1][param-1];
            }
        } else if(extraParam=="c"){
            int tempParam;
            int tempParamW;
            string tempExtraParam;
            commandProcess(carpetBar[paramW-1][param-1],tempParam,tempParamW,tempExtraParam);
            param=tempParam;
            paramW=tempParamW;
            if(paramW<=0||paramW>carpetBar.size()) {
                return false;
            }
            if(param<=0||param>carpetBar[0].size()){
                return false;
            }
            if(carpetBar[param-1][paramW-1].empty()) {
                return false;
            }
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            if(stoi(carpetBar[paramW-1][param-1])>0){
                hand=carpetBar[paramW-1][param-1];
            }
        } else {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("copyifpos");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            if(stoi(carpetBar[paramW-1][param-1])>0){
                onLogbarUpdate(string(extraParam=="c" ? "调用指针," : "")+"carpet为正，将"+carpetBar[paramW-1][param-1]+"从carpet["+std::to_string(paramW-1)+"]["+std::to_string(param-1)+"]复制到手中");
            }
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="copyifneg"){
        if(paramW<=0||paramW>carpetBar.size()) {
            return false;
        }
        if(param<=0||param>carpetBar[0].size()){
            return false;
        }
        if(carpetBar[param-1][paramW-1].empty()) {
            return false;
        }

        if(extraParam=="np"){
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            if(stoi(carpetBar[paramW-1][param-1])<0){
                hand=carpetBar[paramW-1][param-1];
            }
        } else if(extraParam=="c"){
            int tempParam;
            int tempParamW;
            string tempExtraParam;
            commandProcess(carpetBar[paramW-1][param-1],tempParam,tempParamW,tempExtraParam);
            param=tempParam;
            paramW=tempParamW;
            if(paramW<=0||paramW>carpetBar.size()) {
                return false;
            }
            if(param<=0||param>carpetBar[0].size()){
                return false;
            }
            if(carpetBar[param-1][paramW-1].empty()) {
                return false;
            }
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            if(stoi(carpetBar[paramW-1][param-1])<0){
                hand=carpetBar[paramW-1][param-1];
            }
        } else {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("copyifneg");
            qDebug()<<"actionLog pushed";
            qDebug()<<QString::fromStdString(command);
            if(stoi(carpetBar[paramW-1][param-1])<0){
                onLogbarUpdate(string(extraParam=="c" ? "调用指针," : "")+"carpet为负，将"+carpetBar[paramW-1][param-1]+"从carpet["+std::to_string(paramW-1)+"]["+std::to_string(param-1)+"]复制到手中");
            }
        } else {
            qDebug()<<"回调函数未赋值";
        }
    }
    return true;
}

bool Game::playgame(istream& inputStream) {
    outboxBar.clear();
    for(auto& tempCarpetRow : carpetBar){
        fill(tempCarpetRow.begin(),tempCarpetRow.end(),"");
    }
    qDebug()<<"carpetsize"<<carpetBar.size();
    inboxBar=initialInbox;

    vector<string> command;
    vector<int> param;
    vector<int> paramW;
    vector<string> extraParam;

    string inputLine;

    while(std::getline(inputStream,inputLine)) {
        if (inputLine.empty()) {
            continue;
        }

        string cmd;
        string par;
        string extraPar;

        istringstream iss(inputLine);
        iss>>cmd;

        command.push_back(cmd);

        if(iss>>par){
            std::string tempInputPar;
            while(iss>>tempInputPar){
                par+=" ";
                par+=tempInputPar;
            }
            int tempParam;
            int tempParamW;
            string tempExtraParam;
            commandProcess(par,tempParam,tempParamW,tempExtraParam);

            qDebug()<<tempParam<<" "<<tempParamW<<" "<<QString::fromStdString(tempExtraParam);

            param.push_back(tempParam);
            paramW.push_back(tempParamW);
            extraParam.push_back(tempExtraParam);
        } else {
            param.push_back(-1);
            paramW.push_back(1);
            extraParam.push_back("np");
        }
    }

    int doStep=0;
    int numSteps=command.size();
    bool endRun=false;
    bool jumpInputJudge=false;

    while(doStep<numSteps&&!endRun) {
        //jump指令的处理
        if(command[doStep]=="jump"||command[doStep]=="jumpifzero"||command[doStep]=="jumpifpos"||command[doStep]=="jumpifneg") {
            if(!inputProcess(command[doStep],param[doStep],paramW[doStep],extraParam[doStep],jumpInputJudge,endRun,numSteps)) {
                qDebug()<<"Error on instruction "<<doStep+1;
                if(onLogbarUpdate) {
                    onLogbarUpdate("Error on instruction "+std::to_string(doStep+1));
                } else {
                    qDebug()<<"回调函数未赋值";
                }
                return false;
            }

            if(command[doStep]=="jump"||(command[doStep]=="jumpifzero"&&hand=="0") || (command[doStep]=="jumpifpos"&&std::stoi(hand)>0) || (command[doStep]=="jumpifneg"&&std::stoi(hand)<0) || (command[doStep]=="jumpifposzero"&&std::stoi(hand)>=0) || (command[doStep]=="jumpifnegzero"&&std::stoi(hand)<=0)) {
                if(command[doStep]=="jumpifpos"){
                    qDebug()<<"COOL! It's POSITIVE!";
                }

                jumpInputJudge=true;
                qDebug()<<"WHYJUMP? "<<QString::fromStdString(command[doStep]);
                qDebug()<<"JUMPTOWHERE? "<<param[doStep];
                doStep=param[doStep]-1;
            } else if(command[doStep]=="jumpifzero"||command[doStep]=="jumpifpos"||command[doStep]=="jumpifneg"||command[doStep]=="jumpifposzero"||command[doStep]=="jumpifnegzero") {
                ++doStep;
            }
        }
        else {
            if(!inputProcess(command[doStep],param[doStep],paramW[doStep],extraParam[doStep],jumpInputJudge,endRun,numSteps)) {
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
