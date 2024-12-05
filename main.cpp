#include "mainwindow.h"
#include "game.h"
#include <vector>

#include <QApplication>

std::vector<Game> games;

int main(int argc, char *argv[]) {
    games.push_back(Game(std::vector<std::string>{"1", "2"},std::vector<std::string>{"inbox", "outbox"},std::vector<std::string>{"1", "2"},0));
    games.push_back(Game(std::vector<std::string>{"3", "9", "5", "1", "-2", "-2", "9", "-9"},std::vector<std::string>{"inbox", "outbox", "copyfrom", "copyto", "add", "sub", "jump", "jumpifzero"},std::vector<std::string>{"-6", "6", "4", "-4", "0", "0", "18", "-18"},4));
    games.push_back(Game(std::vector<std::string>{"6", "2", "7", "7", "-9", "3", "-3", "-3"},std::vector<std::string>{"inbox", "outbox", "copyfrom", "copyto", "add", "sub", "jump", "jumpifzero"},std::vector<std::string>{"7", "-3"},3));

    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
