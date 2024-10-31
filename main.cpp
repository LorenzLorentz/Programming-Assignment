//#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <ios>

using namespace std;

class Level;
class Menu;
class Gamestate;
class Game;

class Gamestate {
public:
    int numOfAvailableCarpet;
    vector<string> initialInbox; //保持不变的inbox
    vector<string> inboxBar;
    vector<string> outboxBar;
    vector<string> carpetBar;
    vector<string> availableOps; //可以使用的操作
    string hand;

    Gamestate(vector<string> inboxBarSet,vector<string> availableOpsSet,int numCarpet)
       : initialInbox(inboxBarSet),availableOps(availableOpsSet),numOfAvailableCarpet(numCarpet),carpetBar(numCarpet) {}//初始化函数设定

    //目标是否完成的判断
    bool goalReached(const vector<string> &goalJudge) {
        vector<string> output;
        for(int i=0;i<outboxBar.size();++i) {
            output.push_back(outboxBar[i]);
        }
        return output==goalJudge;
    }

    //每一步执行后展示状态
    void displayState() {
        cout<<"Hand:"<<endl<<hand<<endl;
        cout<<"InboxBar:"<<endl;
        for(int i=0;i<inboxBar.size();++i) {
            cout<<inboxBar[i]<<endl;
        }
        cout<<"OutboxBar:"<<endl;
        for(int i=0;i<outboxBar.size();++i) {
            cout<<outboxBar[i]<<endl;
        }
        cout<<"CarpetBar:"<<endl;
        if(carpetBar.size()==0) {
            cout<<"No carpet available"<<endl;
        } else {
            for(int i=0;i<carpetBar.size();++i) {
                if(carpetBar[i].empty()) {
                    cout<<"*"<<" ";
                } cout<<carpetBar[i]<<" ";
            } cout<<endl;
        }
    }

    //判断操作是否合法
    bool isLegalOperation(const string& command, const vector<string>& availableOps) {
        if(command=="") return true;
        for(int i=0;i<availableOps.size();++i) {
            if(command==availableOps[i]) return true;
        }
        return false;
    }

    //对操作进行处理，对操作范围进行判断
    bool inputProcess(const string &command,const int &param,bool &jumpInputJudge, bool &endRun,const int &numSteps) {
        //判断操作是否合法
        if(!isLegalOperation(command,availableOps)) {
            cout<<"Unavailable command"<<endl;
            return false;
        }

        //对操作进行处理
        if(command=="inbox") {
            if(!jumpInputJudge) {
                if(inboxBar.empty()) {
                    cout<<"Inbox is empty"<<endl;
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
            displayState();
        } else if(command=="outbox") {
            if(hand.empty()) {
                cout<<"Nothing in hand"<<endl;
                return false;
            }
            outboxBar.push_back(hand);
            hand="";
            displayState();
        } else if(command=="copyto") {
            if(param<=0||param>carpetBar.size()) {
                cout<<"Invalid parameter"<<endl;
                return false;
            }
            if(hand.empty()) {
                cout<<"Nothing to store"<<endl;
                return false;
            }
            carpetBar[param-1]=hand;
            displayState();
        } else if(command=="copyfrom"){
            if(param<=0||param>carpetBar.size()) {
                cout<<"Invalid parameter"<<endl;
                return false;
            }
            if(carpetBar[param-1].empty()) {
                cout<<"Nothing to copy"<<endl;
                return false;
            }
            hand=carpetBar[param-1];
            displayState();
        } else if(command=="add") {
            if(param<=0||param>carpetBar.size()) {
                cout<<"Invalid parameter"<<endl;
                return false;
            }
            if(hand.empty()) {
                cout<<"Nothing to add"<<endl;
                return false;
            }
            if(carpetBar[param-1].empty()) {
                cout<<"Nothing to add"<<endl;
            }
            hand=to_string(stoi(hand)+stoi(carpetBar[param-1]));
            displayState();
        } else if(command=="sub") {
            if(param<=0||param>carpetBar.size()) {
                cout<<"Invalid parameter"<<endl;
                return false;
            }
            if(hand.empty()) {
                cout<<"Nothing to add"<<endl;
                return false;
            }
            if(carpetBar[param-1].empty()) {
                cout<<"Nothing to add"<<endl;
            }
            hand=to_string(stoi(hand)-stoi(carpetBar[param-1]));
            displayState();
        } else if(command=="jump") {
            if(!(0<=param&&param<numSteps)) {
                cout<<"Invalid parameter"<<endl;
                return false;
            }
        } else if(command=="jumpifzero") {
            if(!(0<=param&&param<numSteps)) {
                cout<<"Invalid parameter"<<endl;
                return false;
            }
        }
        return true;
    }
};

class Level {
public:
    string description; //关卡描述
    string levelInfo; //关卡信息
    string originState;
    string goal;
    vector<string> goalJudge;
    string hint;
    bool completed;
    Gamestate* gamestate;

    Level(string levelName, string desc, string ori,string goal, vector<string>gj, string hints, Gamestate* gs, bool complete)
       : levelInfo(levelName), description(desc), originState(ori), goal(goal), goalJudge(gj), hint(hints), gamestate(gs), completed(complete){}

    void playGame() {
        gamestate->outboxBar.clear();
        gamestate->hand="";
        gamestate->inboxBar=gamestate->initialInbox;

        cout<<"Level Information:"<<levelInfo<<endl;
        cout<<"Description:"<<description<<endl;
        cout<<"Original State:"<<originState<<endl;
        cout<<"Goal:"<<goal<<endl;
        cout<<"Hint:"<<hint<<endl;

        int numSteps=0; //指令数目
        int doStep=0; //实际运行的指令是第几条
        int actualSteps=0; //运行过几条指令

        vector<string> command; //存储指令
        vector<int> param; //存储参数
        bool startRun=false; //开始运行
        bool jumpInputJudge=false; //jump指令可以空input
        bool endRun=false;

        //输入解析
        while(!startRun) {
            //临时输入变量
            string inputLine;
            string cmd;
            int par;

            //读取输入，并解析出指令
            getline(cin,inputLine);
            if (inputLine.empty()&&numSteps!=0) {
                continue;
            }
            istringstream iss(inputLine);
            iss>>cmd;

            //读取参数
            command.push_back(cmd);
            if(iss>>par) {
                param.push_back(par);
            } else {
                param.push_back(-1);
            }

            //读取开始运行指令
            if(cmd=="start") {
                startRun=true;
            }

            //对指令计数
            numSteps++;

            if(cmd!="") {

            }
        }

        while(doStep<numSteps&&!endRun) {
            //jump指令的处理
            if(command[doStep]=="jump"||command[doStep]=="jumpifzero") {
                if(!gamestate->inputProcess(command[doStep],param[doStep],jumpInputJudge,endRun,numSteps)) {
                    cout<<"Invalid input"<<endl;
                    return;
                }

                if(command[doStep]=="jump"||command[doStep]=="jumpifzero"&&gamestate->hand=="0") {
                    jumpInputJudge=true;
                    doStep=param[doStep]; //跳跃至传输的参数指定的位置
                } else if(command[doStep]=="jumpifzero") {
                    cout<<"notzero"<<endl;
                    ++doStep;
                }

                ++actualSteps;
            }

            //非jump指令的处理
            else {
                if(!gamestate->inputProcess(command[doStep],param[doStep],jumpInputJudge,endRun,numSteps)) {
                    cout<<"Invalid input"<<endl;
                    return;
                }
                ++doStep;
                ++actualSteps;
            }
        }

        if(!gamestate->goalReached(goalJudge)) {
            cout<<"Wrong answer"<<endl;
            return;
        }

        cout<<"Success!"<<endl;
        cout<<"Data:"<<endl;
        cout<<"Steps:"<<actualSteps-2<<endl;
        cout<<"Instructions:"<<numSteps-2<<endl;
        completed=true;
    }
};

class Menu {
public:
    void showMenu() {
        cout<<"-----Menu-----"<<endl;
        cout<<"1.Normal Mode"<<endl;
        cout<<"2.Level Selection Mode(Key Required)"<<endl;
        cout<<"3.Exit"<<endl;
    };

    void showLeveltree(const vector<Level> &level){
        cout<<"-----LevelTree-----"<<endl;
        for(int i=0;i<level.size();++i) {
            if(level[i].completed) {
                cout<<"Level #"<<i+1<<": "<<level[i].levelInfo<<" You've passed"<<endl;
            }else {
                cout<<"Level #"<<i+1<<": "<<level[i].levelInfo<<endl;
            }
        }
    }
};

class Game {
public:
    //实例化三个类，用于文件读写
    ofstream archiveFile;
    ifstream archiveRead;
    ifstream levelInfomationRead;

    //实例化游戏类矢量
    vector<Level> level;
    vector<Gamestate> gamestates;
    Menu menu;

    //关卡读取变量
    vector<bool> levelCompleted;
    vector<vector<string>> inboxBarSetRead;
    vector<vector<string>> availableOpRead;
    vector<string> levelInfoRead;
    vector<string> descriptionRead;
    vector<string> oriRead;
    vector<string> goalRead;
    vector<string> hintsRead;
    vector<vector<string>> goalJudgeRead;
    vector<int> numOfCarpet;

    //分隔存档信息并储存的函数
    void parselArchiveLevel(const string& line,vector<bool>& levelCompleted) {
        stringstream ss(line);
        string segment;
        getline(ss, segment);

        size_t pos=segment.find(':');

        if(pos!=string::npos) {
            string key=segment.substr(0,pos);
            string value=segment.substr(pos+1);

            key.erase(0, key.find_first_not_of(" "));
            key.erase(key.find_last_not_of(" ") + 1);
            value.erase(0, value.find_first_not_of(" "));
            value.erase(value.find_last_not_of(" ") + 1);

            if(value=="Passed") {
                levelCompleted.push_back(true);
            } else if(value=="NotPassed") {
                levelCompleted.push_back(false);
            } else {
                levelCompleted.push_back(false);
            }
        }
    }

    //分隔游戏关卡信息并储存的函数
    void parselLevelInfo(const string& line,vector<string>& levelInfoRead,vector<string>& descriptionRead,vector<string>& oriRead,vector<string>& goalRead,vector<string>& hintsRead,vector<vector<string>>& inboxBarSetRead,vector<vector<string>>& availableOpRead,vector<vector<string>>& goalJudgeRead,vector<int>&numOfCarpet) { //从关卡信息文档中读取关卡信息
        //信息按照这样的格式，提示信息+：（分隔提示）+关卡信息+｜（分隔不同部分）
        //LevelInfo: first level | Description: it's very easy | Original State: 0 1 2 | Goal: 0 1 | Hints: use inbox | InboxBar: 0 1 2 | AvailableOps: inbox | GoalJudge: 0 1 2
        //信息分别存入levelInfoRead,descriptionRead,oriRead,goalRead,hintsRead,inboxBarSetRead,availableOpRead

        //将读取的line信息重新转化为流对象进行输入操作
        stringstream ss(line);
        string segment;

        while(getline(ss,segment,'|')) {
            //按照|为分隔将信息存储进segment
            size_t pos=segment.find(':');

            if(pos!=string::npos) { //表示如果不是“不存在:”
                //将信息按照空格分隔储存进入提示信息key和关卡信息value（键值对）
                string key=segment.substr(0,pos);
                string value=segment.substr(pos+1);

                //删除空格
                key.erase(0, key.find_first_not_of(" "));
                key.erase(key.find_last_not_of(" ") + 1);
                value.erase(0, value.find_first_not_of(" "));
                value.erase(value.find_last_not_of(" ") + 1);

                //根据提示信息，储存相应关卡参数
                if(key=="LevelInfo") {
                    levelInfoRead.push_back(value);
                } else if(key=="Description") {
                    descriptionRead.push_back(value);
                } else if(key=="Original State") {
                    oriRead.push_back(value);
                } else if(key=="Goal") {
                    goalRead.push_back(value);
                } else if(key=="Hints") {
                    hintsRead.push_back(value);
                } else if(key=="InboxBar") {
                    //实例化inbox流对象，按空格分隔，存储进inboxBarSetRead
                    istringstream inboxStream(value);
                    string item;
                    vector<string> parts;
                    while(inboxStream>>item) {
                        parts.push_back(item);
                    }
                    inboxBarSetRead.push_back(parts);
                } else if(key=="AvailableOps") {
                    //实例化ops流对象，按空格分隔，存储进availableOpsRead
                    istringstream opStream(value);
                    string item;
                    vector<string> parts;
                    while(opStream>>item) {
                        parts.push_back(item);
                    }
                    availableOpRead.push_back(parts);
                }else if(key=="AvailableCarpet") {
                    numOfCarpet.push_back(stoi(value));
                }else if(key=="GoalJudge") {
                    //实例化gj流对象，按空格分隔，存储进availableOpsRead
                    istringstream gjStream(value);
                    string item;
                    vector<string> parts;
                    while(gjStream>>item) {
                        parts.push_back(item);
                    }
                    goalJudgeRead.push_back(parts);
                }
            }
        }
    }

    //读取游戏存档以及游戏关卡信息
    void fileRead() {
        string line; //临时读取变量
        cout<<line<<endl;

        archiveRead.open("archive.txt");
        if (!archiveRead.is_open()) { //如果读取失败
            cout<<"Error: Could not open the archive file for reading!"<<endl;
            return;
        }
        while(getline(archiveRead,line)) {
            parselArchiveLevel(line,levelCompleted);
        }
        archiveRead.close();

        levelInfomationRead.open("levelInfo.txt");
        if(!levelInfomationRead.is_open()) {
            cout<<"Error: Could not open the levelInfo file for reading!"<<endl;
            return;
        }
        while(getline(levelInfomationRead,line)) {
            parselLevelInfo(line,levelInfoRead,descriptionRead,oriRead,goalRead,hintsRead,inboxBarSetRead,availableOpRead,goalJudgeRead,numOfCarpet);
        }
        levelInfomationRead.close();
    }

    Game() {
        fileRead();

        //使用之前读取到的信息进行初始化操作
        for(int i=0;i<levelInfoRead.size();++i) {
            gamestates.emplace_back(inboxBarSetRead[i],availableOpRead[i],numOfCarpet[i]);
        }

        for(int i=0;i<levelInfoRead.size();++i) {
            level.emplace_back(levelInfoRead[i],descriptionRead[i],oriRead[i],goalRead[i],goalJudgeRead[i],hintsRead[i],&gamestates[i],levelCompleted[i]);
        }
    }

    void run() {
        menu.showMenu();

        int choice;
        cout<<"Enter your choice:";

        while (true) {
            cin>>choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Invalid input. Please enter a valid number."<< endl;
            } else if (choice != 1 && choice != 2 && choice != 3) {
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
            } else {
                break;
            }
        }

        if(choice == 1) {
            while(true) {
                char ifContinue;
                cout<<"Do you want to continue?(y/n):";
                cin>>ifContinue;
                if(ifContinue == 'n') {
                    archiveFile.open("archive.txt");
                    for(int i=0;i<level.size();++i) {
                        archiveFile<<level[i].levelInfo<<":";
                        if(level[i].completed) {
                            archiveFile<<"Passed"<<endl;
                        } else {
                            archiveFile<<"NotPassed"<<endl;
                        }
                    }
                    archiveFile.close();
                    break;
                } else if(ifContinue == 'y') {
                    menu.showLeveltree(level);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    int levelChoice;

                    while (true) {
                        cin>>levelChoice;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout<<"Invalid input. Please enter a valid number."<< endl;
                        } else if (!(levelChoice>0&&levelChoice<=level.size())) {
                            cout << "Invalid choice. Please enter a valid number." << endl;
                        } else {
                            break;
                        }
                    }

                    level[levelChoice-1].playGame();
                } else {
                    cout<<"Invalid input"<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
            }
        } else if(choice == 3) {
            exit(0);
        } else {
            cout<<"Invalid Choice"<<endl;
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}