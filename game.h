#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <regex>
#include <queue>

class Game {
public:
    std::vector<std::string> initialInbox;
    std::vector<std::string> inboxBar;
    std::vector<std::string> outboxBar;
    std::vector<std::vector<std::string>> carpetBar;
    std::vector<std::string> availableOps;
    std::string hand;
    std::vector<std::string> goal;
    std::string descrip;
    bool passed;

    std::queue<std::string> actionLog;
    std::function<void(const std::string&)> onLogbarUpdate;
    std::function<void(const std::string&)> onInboxbarUpdate;
    std::function<void(const std::string&)> onOutboxbarUpdate;
    std::function<void(const std::string&)> onCarpet1Update;
    std::function<void(const std::string&)> onCarpet2Update;
    std::function<void(const std::string&)> onCarpet3Update;
    std::function<void(const std::string&)> onCarpet4Update;
    std::function<void(const std::string&)> onHandUpdate;

    std::function<void(const std::string&)> onCarpet11Update;
    std::function<void(const std::string&)> onCarpet12Update;
    std::function<void(const std::string&)> onCarpet13Update;
    std::function<void(const std::string&)> onCarpet14Update;
    std::function<void(const std::string&)> onCarpet15Update;
    std::function<void(const std::string&)> onCarpet16Update;

    std::function<void(const std::string&)> onCarpet21Update;
    std::function<void(const std::string&)> onCarpet22Update;
    std::function<void(const std::string&)> onCarpet23Update;
    std::function<void(const std::string&)> onCarpet24Update;
    std::function<void(const std::string&)> onCarpet25Update;
    std::function<void(const std::string&)> onCarpet26Update;

    std::function<void(const std::string&)> onCarpet31Update;
    std::function<void(const std::string&)> onCarpet32Update;
    std::function<void(const std::string&)> onCarpet33Update;
    std::function<void(const std::string&)> onCarpet34Update;
    std::function<void(const std::string&)> onCarpet35Update;
    std::function<void(const std::string&)> onCarpet36Update;

    std::function<void(const std::string&)> onCarpet41Update;
    std::function<void(const std::string&)> onCarpet42Update;
    std::function<void(const std::string&)> onCarpet43Update;
    std::function<void(const std::string&)> onCarpet44Update;
    std::function<void(const std::string&)> onCarpet45Update;
    std::function<void(const std::string&)> onCarpet46Update;

    std::function<void(const std::string&)> onCarpet51Update;
    std::function<void(const std::string&)> onCarpet52Update;
    std::function<void(const std::string&)> onCarpet53Update;
    std::function<void(const std::string&)> onCarpet54Update;
    std::function<void(const std::string&)> onCarpet55Update;
    std::function<void(const std::string&)> onCarpet56Update;

    Game(std::vector<std::string> initialInboxSet,
         std::vector<std::string> availableOpsSet,
         std::vector<std::string> goalSet,
         int numOfCarpetSet,
         int numOfCarpet2DSet,
         std::string descripSet);

    bool goalReached();
    bool isLegalOperation(std::string& command);
    bool inputProcess(std::string &command,int& param,int& paramW,std::string extraParam,bool& jumpInputJudge,bool& endRun,int& numSteps);
    void updateState();
    bool playgame(std::istream& inputStream);
    void commandProcess(std::string& commandToProcess,int& param,int& paramW,std::string& extraParam);
    bool isValidInteger(std::string& input);
};

#endif // GAME_H
