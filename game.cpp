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

void Game::commandProcess(string& commandToProcess,int& param,int& paramW,string& extraParam) {
    istringstream iss(commandToProcess);
    size_t tempPos=commandToProcess.find(';');
    if(tempPos!=std::string::npos){
        string token;
        getline(iss,token,';');
        cout<<token<<endl;
        param=stoi(token);
        getline(iss,token,' ');
        cout<<token<<endl;
        paramW=stoi(token);
    } else {
        string token;
        getline(iss,token,' ');
        param=stoi(token);
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

/*
 * TODO
 * 针对二维carpet逻辑进行修改
 */

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

    if(onHandUpdate){
        onHandUpdate(hand);
    }
}

bool Game::inputProcess(string &command,int& param,int& paramW,std::string extraParam,bool& jumpInputJudge,bool& endRun,int& numSteps) {
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
        if(paramW<=0||paramW>carpetBar.size()) {
            return false;
        }
        if(param<=0||param>carpetBar[0].size()){
            return false;
        }
        if(hand.empty()) {
            return false;
        }
        if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
            return false;
        }

        if(extraParam=="np"){
            carpetBar[paramW-1][param-1]=hand;
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
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            carpetBar[paramW-1][param-1]=hand;
        } else if(extraParam=="p1"){
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
            if(carpetBar[paramW-1][param-1].find(';')==std::string::npos){
                carpetBar[paramW-1][param-1]=hand;
            } else {
                carpetBar[paramW-1][param-1]=hand+carpetBar[paramW-1][param-1].substr(carpetBar[paramW-1][param-1].find(';'));
            }
        } else if(extraParam=="p2"){
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
            if(carpetBar[paramW-1][param-1].find(';')==std::string::npos){
                carpetBar[paramW-1][param-1]+=(";"+hand);
            } else {
                carpetBar[paramW-1][param-1]=carpetBar[paramW-1][param-1].substr(0,1+carpetBar[paramW-1][param-1].find(';'))+hand;
            }
        } else {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("copyto");
            qDebug()<<"actionLog pushed";
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
        if(hand.empty()) {
            return false;
        }

        if(extraParam=="np"){
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
            if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
                return false;
            }
            hand=carpetBar[paramW-1][param-1];
        } else {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("copyfrom");
            qDebug()<<"actionLog pushed";
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
            onLogbarUpdate(string(extraParam=="c" ? "调用指针," : "")+"将"+carpetBar[paramW-1][param-1]+"从carpet["+std::to_string(paramW-1)+"]["+std::to_string(param-1)+"]在手中减去");
        } else {
            qDebug()<<"回调函数未赋值";
        }
    } else if(command=="jump") {
        if(!(0<=param&&param<numSteps)) {
            return false;
        }

        updateState();
        if(onLogbarUpdate) {
            actionLog.push("jump");
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
        if(!(0<=param&&param<numSteps)) {
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

        if(extraParam=="np"){
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
            if(stoi(carpetBar[paramW-1][param-1])>0){
                onLogbarUpdate(string(extraParam=="c" ? "调用指针," : "")+"carpet为，将"+carpetBar[paramW-1][param-1]+"从carpet["+std::to_string(paramW-1)+"]["+std::to_string(param-1)+"]复制到手中");
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
        if(carpetBar[paramW-1][param-1].find(';')!=std::string::npos){
            return false;
        }

        if(extraParam=="np"){
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
            int tempParam;
            int tempParamW;
            string tempExtraParam;
            commandProcess(par,tempParam,tempParamW,tempExtraParam);
            param.push_back(tempParam);
            paramW.push_back(tempParam);
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

            if(command[doStep]=="jump"||(command[doStep]=="jumpifzero"&&hand=="0") || (command[doStep]=="jumpifpos"&&std::stoi(hand)>0) || (command[doStep]=="jumpifneg"&&std::stoi(hand)<0)) {
                jumpInputJudge=true;
                doStep=param[doStep]-1;
            } else if(command[doStep]=="jumpifzero") {
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
