#include <bits/stdc++.h>
using namespace std;

class Level;
class Menu;
class Gamestate;
class Game;

class Gamestate {
public:
    vector<string> initialInbox; //保持不变的inbox
    vector<string> inboxBar;
    vector<string> outboxBar;
    vector<string> carpetBar;
    vector<string> availableOps; //可以使用的操作
    string hand;

    Gamestate(vector<string> inboxBarSet,vector<string> availableOpsSet)
       : initialInbox(inboxBarSet),availableOps(availableOpsSet) {} //初始化函数设定

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
        for(int i=0;i<carpetBar.size();++i) {
            if(carpetBar[i].empty()) {
                cout<<"*"<<" ";
            } cout<<carpetBar[i]<<" ";
        } cout<<endl;
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
            hand.clear();
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

    Level(string levelName, string desc, string ori,string goal, vector<string>gj, string hints, Gamestate* gs)
       : levelInfo(levelName), description(desc), originState(ori), goal(goal), goalJudge(gj), hint(hints), completed(false), gamestate(gs) {}

    void playGame() {
        gamestate->outboxBar.clear();
        gamestate->carpetBar={"","","",""};
        gamestate->hand="";
        gamestate->inboxBar=gamestate->initialInbox;

        cout<<"Level Information:"<<levelInfo<<endl;
        cout<<"Description:"<<description<<endl;
        cout<<"Inputbar State:"<<originState<<endl;
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
            if (inputLine.empty()&&numSteps!=0)
                continue;
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
                cout<<"Level #"<<i+1<<": "<<level[i].levelInfo<<"You've passed"<<endl;
            }else {
                cout<<"Level #"<<i+1<<": "<<level[i].levelInfo<<endl;
            }
        }
    }
};

class Game {
public:
    vector<Level> level;
    vector<Gamestate> gamestates;
    Menu menu;

    Game() {
        gamestates.emplace_back(vector<string>{"1","2"},vector<string>{"inbox","outbox","start"});
        gamestates.emplace_back(vector<string>{"3","9","5","1","-2","-2","9","-9"},vector<string>{"start","inbox","outbox","copyfrom","copyto","add","sub","jump","jumpifzero","start"});
        gamestates.emplace_back(vector<string>{"6","2","7","7","-9","3","-3","-3"},vector<string>{"start","inbox","outbox","copyfrom","copyto","add","sub","jump","jumpifzero","start"});
        //game.emplace_back("","");

        level.emplace_back("First Level","", "1,2", "1,2", vector<string>{"1","2"}, "Use inbox, outbox", &gamestates[0]);
        level.emplace_back("Second Level","", "3,9,5,1,-2,-2,9,-9", "-6,6,4,-4,0,0,18,-18", vector<string>{"-6","6","4","-4","0","0","18","-18"}, "Use sub", &gamestates[1]);
        level.emplace_back("Third Level","","6,2,7,7,-9,3,-3,-3", "7,-3", vector<string>{"7","-3"}, "Use sub and jumpifzero", &gamestates[2]);
        //level.emplace_back("Fourth Level","","");
    }

    void run() {
        menu.showMenu();

        int choice;
        while (true) {
            cout<<"Enter your choice: ";
            cin>>choice;

            //判断输入有效性
            if (cin.fail()) {
                // 检查cin是否进入错误状态
                cin.clear(); // 清除错误状态
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃无效输入
                cout<<"Invalid input. Please enter a valid number." << endl;
            } else if(!(choice == 1 || choice == 2 || choice == 3)) {
                cout<<"Invalid input. Please enter 1, 2, 3." << endl;
            } else {
                break;
            }
        }

        if(choice == 1) {
            while(true) {
                char ifContinue;
                cout<<"Do you want to continue?(y/n):";
                cin>>ifContinue;
                if(ifContinue=='n') {
                    break;
                } else if(ifContinue=='y') {
                    menu.showLeveltree(level);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    int levelChoice;
                    while (true) {
                        cout<<"Enter level choice: ";
                        cin>>levelChoice;

                        //判断输入有效性
                        if (cin.fail()) {
                            // 检查cin是否进入错误状态
                            cin.clear(); // 清除错误状态
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃无效输入
                            cout<<"Invalid input. Please enter a valid number." << endl;
                        } else if(!(levelChoice>0&&levelChoice<=level.size())){
                            cout<<"Invalid input. Please enter a valid level." << endl;
                        } else{
                            break;
                        }
                    }
                    level[levelChoice-1].playGame();
                } else {
                    cout<<"Invalid input. Please enter y/n."<<endl;
                    continue;
                }
            }
        } else if(choice==3||choice==2) {
            exit(0);
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}