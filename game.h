#ifndef GAME_H
#define GAME_H

#include <iostream>    // cin, cout, cin.ignore
#include <vector>      // vector
#include <string>      // string, stoi, to_string, getline
#include <sstream>     // istringstream
#include <algorithm>   // fill
#include <functional>

class Game {
public:
    std::vector<std::string> initialInbox;
    std::vector<std::string> inboxBar;
    std::vector<std::string> outboxBar;
    std::vector<std::string> carpetBar;
    std::vector<std::string> availableOps;
    std::string hand;
    std::vector<std::string> goal;
    bool passed;

    std::function<void(const std::string&)> onLogbarUpdate;
    std::function<void(const std::string&)> onInboxbarUpdate;
    std::function<void(const std::string&)> onOutboxbarUpdate;
    std::function<void(const std::string&)> onCarpetbarUpdate;
    std::function<void(const std::string&)> onHandUpdate;

    Game(std::vector<std::string> initialInboxSet,
         std::vector<std::string> availableOpsSet,
         std::vector<std::string> goalSet,
         int numOfCarpetSet);

    bool goalReached();
    bool isLegalOperation(std::string& command);
    bool inputProcess(std::string &command,int& param,bool& jumpInputJudge,bool& endRun,int& numSteps);
    void updateState();
    bool playgame(std::istream& inputStream);
};

#endif // GAME_H
