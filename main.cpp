#include <bits/stdc++.h>
using namespace std;

class Level;
class Menu;
class Gamestate;
class Game;

class Gamestate {
public:
    vector<string> inboxBar={"3","5","7","A"};
    vector<string> outboxBar;
    vector<string> carpetBar;
    vector<string> availableOps=vector<string>(4);
    string commands;

    bool goalReached(const string &goal) {
        string output;
        for(int i=0;i<outboxBar.size();++i) {
            output+=outboxBar[i];
        }
        return output==goal;
    }

    void displayState() {
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
            cout<<carpetBar[i]<<endl;
        }
    }

    bool inputProcess(const string &command,const int &param) {
        if(command=="inbox") {
            if(inboxBar.empty()) {
                cout<<"Inbox is empty"<<endl;
                return false;
            }
            string input=inboxBar.back();
            inboxBar.pop_back();
            commands=input;
            displayState();
        } else if(command=="outbox") {
            if(commands.empty()) {
                cout<<"No input"<<endl;
                return false;
            }
            outboxBar.push_back(commands);
            commands="";
            displayState();
        } else if(command=="copyto") {
            if(commands.empty()) {
                cout<<"Nothing to store"<<endl;
                return false;
            }
            //int index=(int)param[0]-32;
            if(param<0||param>=carpetBar.size()) {
                cout<<"Invalid index"<<endl;
                return false;
            }
            carpetBar[param]=commands;
        } else if(command=="copy from"){
            if(param<0 || param>=carpetBar.size()) {
                cout<<"Invalid index"<<endl;
                return false;
            }
            commands=carpetBar[param];
        }else if(command=="add") {
            if(commands.empty()) {
                cout<<"Nothing to add"<<endl;
                return false;
            }
            if(param<0 || param>=carpetBar.size()) {
                cout<<"Invalid index"<<endl;
                return false;
            }
            commands+=carpetBar[param];
        } else if(command=="jumpto") {
            if(!(1<=param && param<=carpetBar.size())) {
                cout<<"Invalid index"<<endl;
                return false;
            }
            if(inboxBar.empty()) {
            }
        }
        return true;
    }
};

class Level {
public:
    string description;
    string levelInfo;
    string goal;
    vector<string> hint;
    vector<string> operation;
    bool completed;

    Level(string desc, string goal, vector<string> hints, vector<string> ops)
       : description(desc), goal(goal), hint(hints), completed(false), operation(ops) {}

    void playGame() {
        cout<<"Level Information"<<levelInfo<<endl;
        cout<<"Goal:"<<goal<<endl;
        for (const auto &hint : hint) {
            cout<<hint<<" ";
        }cout<<endl;

        Gamestate gamestate;

        vector<string> inputCommand;
        int numSteps=0;
        int doStep=0;
        int actualSteps=0;
        vector<string> command;
        vector<int> param;
        bool startRun=false;

        while(!startRun) {
            getline(cin,inputCommand[numSteps]);
            istringstream iss(inputCommand[numSteps]);
            iss>>command[numSteps];
            iss>>param[numSteps];
            if(command[numSteps]=="start") {
                startRun=true;
            }
            numSteps++;
        }

        while(doStep<numSteps) {
            if(command[doStep]=="jumpto"||command[doStep]=="jumpifzero") {
                if(!gamestate.inputProcess(command[doStep],param[doStep])) {
                    cout<<"Invalid input"<<endl;
                    return;
                }
                doStep=param[doStep];
                ++actualSteps;
            } else {
                if(!gamestate.inputProcess(command[doStep],param[doStep])) {
                    cout<<"Invalid input"<<endl;
                    return;
                }
                ++doStep;
                ++actualSteps;
            }
        }

        if(!gamestate.goalReached(goal)) {
            cout<<"Wrong answer";
            return;
        }

        cout<<"Success:"<<endl;
        cout<<"Data:"<<endl;
        cout<<"Steps:"<<actualSteps<<endl;
        cout<<"Instructions:"<<numSteps<<endl;
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
                cout<<"Level #"<<i+1<<":"<<level[i].description<<" You've passed"<<endl;
            }else {
                cout<<"Level #"<<i+1<<": "<<level[i].description<<endl;
            }
        }
    }
};

class Game {
public:
    vector<Level> level;
    Menu menu;

    Game() {
        level.emplace_back("First Level", "A753", vector<string>{"Use inbox, outbox"}, vector<string>{"inbox", "outbox"});
        level.emplace_back("Second Level", "6", vector<string>{"Use add"}, vector<string>{"inbox", "outbox", "copyto", "add"});
    }

    void run() {
        menu.showMenu();

        int choice;
        cout<<"Enter your choice:";
        cin>>choice;

        if(choice == 1) {
            menu.showLeveltree(level);
            int levelChoice;
            cin>>levelChoice;
            if(levelChoice>0&&levelChoice<=level.size()) {
                level[levelChoice-1].playGame();
            } else {
                cout<<"Invalid Choice"<<endl;
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