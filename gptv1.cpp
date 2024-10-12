#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// 游戏状态类
class GameState {
//游戏状态的private元素
private:
    vector<string> inputBar;
    vector<string> outputBar;
    vector<string> carpetBar;
    map<string, string> commands;
    vector<string> availableOperations;

public:
    GameState(vector<string> ops) : availableOperations(ops) {
        // 初始化栏位
        carpetBar.resize(4, "");
        // 初始化可用的操作
        for (const auto &op : ops) {
            commands[op] = "";
        }
        // 假设输入栏有一些初始数据
        inputBar = {"3", "5", "A", "7"};
    }

    bool processCommand(const string &command) {
        if (commands.find(command) == commands.end()) {
            cout << "Command not available in this level!" << endl;
            return false;
        }

        if (command == "get") {
            if (inputBar.empty()) {
                cout << "Input bar is empty!" << endl;
                return false;
            }
            string input = inputBar.back();
            inputBar.pop_back();
            commands["get"] = input;
            cout << "You got: " << input << endl;
        } else if (command == "put") {
            if (commands["get"].empty()) {
                cout << "No input to put!" << endl;
                return false;
            }
            outputBar.push_back(commands["get"]);
            cout << "You put: " << commands["get"] << " into output bar." << endl;
            commands["get"] = "";
        } else if (command == "memo") {
            if (commands["get"].empty()) {
                cout << "No input to memo!" << endl;
                return false;
            }
            for (int i = 0; i < 4; ++i) {
                if (carpetBar[i].empty()) {
                    carpetBar[i] = commands["get"];
                    cout << "You memoed: " << commands["get"] << " into carpet slot " << i + 1 << endl;
                    commands["get"] = "";
                    break;
                }
            }
        } else if (command == "add") {
            // 简单的加法操作
            if (commands["get"].empty()) {
                cout << "No input to add!" << endl;
                return false;
            }
            for (const auto &val : carpetBar) {
                if (!val.empty()) {
                    int result = stoi(val) + stoi(commands["get"]);
                    cout << "Added " << val << " + " << commands["get"] << " = " << result << endl;
                    commands["get"] = to_string(result);
                    break;
                }
            }
        } else if (command == "back") {
            // 返回上一个操作（简单的回退）
            cout << "Back operation is not implemented yet!" << endl;
        }

        return true;
    }

    bool isGoalReached(const string &goal) {
        // 简单判断输出栏是否达到目标
        string output;
        for (const auto &val : outputBar) {
            output += val;
        }
        return output == goal;
    }

    void displayState() {
        cout << "\nInput Bar: ";
        for (const auto &val : inputBar) {
            cout << val << " ";
        }
        cout << "\nOutput Bar: ";
        for (const auto &val : outputBar) {
            cout << val << " ";
        }
        cout << "\nCarpet Bar: ";
        for (const auto &val : carpetBar) {
            cout << val << " ";
        }
        cout << endl;
    }
};

// 游戏关卡类
class Level {
public:
    string description;
    string goal;
    vector<string> hints;
    bool completed;
    vector<string> operations;

    Level(string desc, string goal, vector<string> hints, vector<string> ops)
        : description(desc), goal(goal), hints(hints), completed(false), operations(ops) {}

    void play() {
        cout << description << endl;
        cout << "Goal: " << goal << endl;
        cout << "Hints: " << endl;
        for (const auto &hint : hints) {
            cout << "- " << hint << endl;
        }

        // 初始化游戏状态
        GameState state(operations);

        // 游戏核心逻辑
        while (!state.isGoalReached(goal)) {
            string command;
            cout << "\nEnter command: ";
            cin >> command;
            if (!state.processCommand(command)) {
                cout << "Invalid command! Game over!" << endl;
                return;
            }
        }

        cout << "Congratulations! You completed the level!" << endl;
        completed = true;
    }
};

// 菜单系统类
class Menu {
public:
    void showMainMenu() {
        cout << "----- Main Menu -----" << endl;
        cout << "1. Normal Mode" << endl;
        cout << "2. Level Selection Mode (Key Required)" << endl;
        cout << "3. Exit" << endl;
    }

    void showLevelTree(const vector<Level> &levels) {
        cout << "----- Level Tree -----" << endl;
        for (size_t i = 0; i < levels.size(); ++i) {
            if (levels[i].completed) {
                cout << "** Level " << i + 1 << ": " << levels[i].description << " **" << endl;
            } else {
                cout << "Level " << i + 1 << ": " << levels[i].description << endl;
            }
        }
    }

    bool verifyKey(const string &key) {
        const string validKey = "12345"; // 简单的验证逻辑
        return key == validKey;
    }
};

// 游戏主类
class Game {
private:
    vector<Level> levels;
    Menu menu;

public:
    Game() {
        // 初始化关卡
        levels.emplace_back("First Level", "357A", vector<string>{"Use get, put"}, vector<string>{"get", "put"});
        levels.emplace_back("Second Level", "6", vector<string>{"Use add"}, vector<string>{"get", "put", "memo", "add"});
    }

    void run() {
        while (true) {
            menu.showMainMenu();
            int choice;
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                menu.showLevelTree(levels);
                cout << "Enter level number to play: ";
                int levelNumber;
                cin >> levelNumber;
                if (levelNumber > 0 && levelNumber <= levels.size()) {
                    levels[levelNumber - 1].play();
                } else {
                    cout << "Invalid level number!" << endl;
                }
            } else if (choice == 2) {
                string key;
                cout << "Enter key: ";
                cin >> key;
                if (menu.verifyKey(key)) {
                    menu.showLevelTree(levels);
                    cout << "Enter level number to play: ";
                    int levelNumber;
                    cin >> levelNumber;
                    if (levelNumber > 0 && levelNumber <= levels.size()) {
                        levels[levelNumber - 1].play();
                    } else {
                        cout << "Invalid level number!" << endl;
                    }
                } else {
                    cout << "Invalid key!" << endl;
                }
            } else if (choice == 3) {
                cout << "Exiting game..." << endl;
                break;
            } else {
                cout << "Invalid choice!" << endl;
            }
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}