/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *welcomePage;
    QPushButton *buttonWelcomePlaygame;
    QPushButton *buttonWelcomeLoadgame;
    QPushButton *buttonWelcomeExit;
    QLabel *labelWelcomepageCentralname;
    QWidget *page;
    QWidget *fail;
    QPushButton *buttonFailExit;
    QPushButton *buttonFailRestart;
    QPushButton *buttonFailBack;
    QLabel *labelFailCentral;
    QWidget *levelchoice;
    QPushButton *buttonLevelchoiceLevel1;
    QPushButton *buttonLevelchoiceLevel2;
    QPushButton *buttonLevelchoiceLevel3;
    QLabel *labelLevelchoiceCentrallevelchoice;
    QPushButton *buttonLevelchoiceBack;
    QWidget *loadgame;
    QPushButton *buttonLoadgameLoadlevelinfo;
    QPushButton *buttonLoadgameLoadarchive;
    QLabel *labelLoadgameCentral;
    QPushButton *buttonLoadgameBackandload;
    QPushButton *buttonLoadgameAutoload;
    QWidget *playgame;
    QTextEdit *inputPlaygameCommand;
    QPushButton *buttonPlaygameStart;
    QTextBrowser *showPlaygameLogbar;
    QLabel *labelPlaygameLogbar;
    QTextBrowser *showPlaygameInboxbar;
    QTextBrowser *showPlaygameOutboxbar;
    QTextBrowser *showPlaygameCarpet1;
    QTextBrowser *showPlaygameCarpet2;
    QTextBrowser *showPlaygameCarpet3;
    QTextBrowser *showPlaygameCarpet4;
    QLabel *labelPlaygameInboxbar;
    QLabel *labelPlaygameOutboxbar;
    QLabel *labelPlaygameCarpetbar;
    QPushButton *buttonPlaygameSkip;
    QWidget *success;
    QLabel *labelSuccessCentral;
    QPushButton *buttonSuccessBack;
    QPushButton *buttonSuccessExit;
    QMenuBar *menubar;
    QMenu *menuHuman_Resource_Machine;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 791, 531));
        welcomePage = new QWidget();
        welcomePage->setObjectName(QString::fromUtf8("welcomePage"));
        buttonWelcomePlaygame = new QPushButton(welcomePage);
        buttonWelcomePlaygame->setObjectName(QString::fromUtf8("buttonWelcomePlaygame"));
        buttonWelcomePlaygame->setGeometry(QRect(170, 350, 100, 32));
        buttonWelcomeLoadgame = new QPushButton(welcomePage);
        buttonWelcomeLoadgame->setObjectName(QString::fromUtf8("buttonWelcomeLoadgame"));
        buttonWelcomeLoadgame->setGeometry(QRect(330, 350, 100, 32));
        buttonWelcomeExit = new QPushButton(welcomePage);
        buttonWelcomeExit->setObjectName(QString::fromUtf8("buttonWelcomeExit"));
        buttonWelcomeExit->setGeometry(QRect(480, 350, 100, 32));
        labelWelcomepageCentralname = new QLabel(welcomePage);
        labelWelcomepageCentralname->setObjectName(QString::fromUtf8("labelWelcomepageCentralname"));
        labelWelcomepageCentralname->setGeometry(QRect(100, 210, 591, 71));
        stackedWidget->addWidget(welcomePage);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        fail = new QWidget();
        fail->setObjectName(QString::fromUtf8("fail"));
        buttonFailExit = new QPushButton(fail);
        buttonFailExit->setObjectName(QString::fromUtf8("buttonFailExit"));
        buttonFailExit->setGeometry(QRect(510, 320, 100, 32));
        buttonFailRestart = new QPushButton(fail);
        buttonFailRestart->setObjectName(QString::fromUtf8("buttonFailRestart"));
        buttonFailRestart->setGeometry(QRect(180, 320, 100, 32));
        buttonFailBack = new QPushButton(fail);
        buttonFailBack->setObjectName(QString::fromUtf8("buttonFailBack"));
        buttonFailBack->setGeometry(QRect(340, 320, 100, 32));
        labelFailCentral = new QLabel(fail);
        labelFailCentral->setObjectName(QString::fromUtf8("labelFailCentral"));
        labelFailCentral->setGeometry(QRect(320, 160, 121, 71));
        stackedWidget->addWidget(fail);
        levelchoice = new QWidget();
        levelchoice->setObjectName(QString::fromUtf8("levelchoice"));
        buttonLevelchoiceLevel1 = new QPushButton(levelchoice);
        buttonLevelchoiceLevel1->setObjectName(QString::fromUtf8("buttonLevelchoiceLevel1"));
        buttonLevelchoiceLevel1->setGeometry(QRect(130, 290, 121, 32));
        buttonLevelchoiceLevel2 = new QPushButton(levelchoice);
        buttonLevelchoiceLevel2->setObjectName(QString::fromUtf8("buttonLevelchoiceLevel2"));
        buttonLevelchoiceLevel2->setGeometry(QRect(320, 290, 121, 32));
        buttonLevelchoiceLevel3 = new QPushButton(levelchoice);
        buttonLevelchoiceLevel3->setObjectName(QString::fromUtf8("buttonLevelchoiceLevel3"));
        buttonLevelchoiceLevel3->setGeometry(QRect(510, 290, 121, 32));
        labelLevelchoiceCentrallevelchoice = new QLabel(levelchoice);
        labelLevelchoiceCentrallevelchoice->setObjectName(QString::fromUtf8("labelLevelchoiceCentrallevelchoice"));
        labelLevelchoiceCentrallevelchoice->setGeometry(QRect(240, 180, 291, 51));
        buttonLevelchoiceBack = new QPushButton(levelchoice);
        buttonLevelchoiceBack->setObjectName(QString::fromUtf8("buttonLevelchoiceBack"));
        buttonLevelchoiceBack->setGeometry(QRect(330, 350, 100, 32));
        stackedWidget->addWidget(levelchoice);
        loadgame = new QWidget();
        loadgame->setObjectName(QString::fromUtf8("loadgame"));
        buttonLoadgameLoadlevelinfo = new QPushButton(loadgame);
        buttonLoadgameLoadlevelinfo->setObjectName(QString::fromUtf8("buttonLoadgameLoadlevelinfo"));
        buttonLoadgameLoadlevelinfo->setGeometry(QRect(150, 270, 131, 32));
        buttonLoadgameLoadarchive = new QPushButton(loadgame);
        buttonLoadgameLoadarchive->setObjectName(QString::fromUtf8("buttonLoadgameLoadarchive"));
        buttonLoadgameLoadarchive->setGeometry(QRect(440, 270, 131, 32));
        labelLoadgameCentral = new QLabel(loadgame);
        labelLoadgameCentral->setObjectName(QString::fromUtf8("labelLoadgameCentral"));
        labelLoadgameCentral->setGeometry(QRect(270, 160, 191, 51));
        buttonLoadgameBackandload = new QPushButton(loadgame);
        buttonLoadgameBackandload->setObjectName(QString::fromUtf8("buttonLoadgameBackandload"));
        buttonLoadgameBackandload->setGeometry(QRect(310, 310, 100, 32));
        buttonLoadgameAutoload = new QPushButton(loadgame);
        buttonLoadgameAutoload->setObjectName(QString::fromUtf8("buttonLoadgameAutoload"));
        buttonLoadgameAutoload->setGeometry(QRect(310, 270, 100, 32));
        stackedWidget->addWidget(loadgame);
        playgame = new QWidget();
        playgame->setObjectName(QString::fromUtf8("playgame"));
        inputPlaygameCommand = new QTextEdit(playgame);
        inputPlaygameCommand->setObjectName(QString::fromUtf8("inputPlaygameCommand"));
        inputPlaygameCommand->setGeometry(QRect(600, 120, 141, 191));
        buttonPlaygameStart = new QPushButton(playgame);
        buttonPlaygameStart->setObjectName(QString::fromUtf8("buttonPlaygameStart"));
        buttonPlaygameStart->setGeometry(QRect(620, 70, 100, 32));
        showPlaygameLogbar = new QTextBrowser(playgame);
        showPlaygameLogbar->setObjectName(QString::fromUtf8("showPlaygameLogbar"));
        showPlaygameLogbar->setGeometry(QRect(0, 40, 141, 241));
        labelPlaygameLogbar = new QLabel(playgame);
        labelPlaygameLogbar->setObjectName(QString::fromUtf8("labelPlaygameLogbar"));
        labelPlaygameLogbar->setGeometry(QRect(40, 10, 51, 31));
        showPlaygameInboxbar = new QTextBrowser(playgame);
        showPlaygameInboxbar->setObjectName(QString::fromUtf8("showPlaygameInboxbar"));
        showPlaygameInboxbar->setGeometry(QRect(210, 40, 291, 71));
        showPlaygameOutboxbar = new QTextBrowser(playgame);
        showPlaygameOutboxbar->setObjectName(QString::fromUtf8("showPlaygameOutboxbar"));
        showPlaygameOutboxbar->setGeometry(QRect(210, 390, 291, 71));
        showPlaygameCarpet1 = new QTextBrowser(playgame);
        showPlaygameCarpet1->setObjectName(QString::fromUtf8("showPlaygameCarpet1"));
        showPlaygameCarpet1->setGeometry(QRect(340, 160, 71, 71));
        showPlaygameCarpet2 = new QTextBrowser(playgame);
        showPlaygameCarpet2->setObjectName(QString::fromUtf8("showPlaygameCarpet2"));
        showPlaygameCarpet2->setGeometry(QRect(430, 160, 71, 71));
        showPlaygameCarpet3 = new QTextBrowser(playgame);
        showPlaygameCarpet3->setObjectName(QString::fromUtf8("showPlaygameCarpet3"));
        showPlaygameCarpet3->setGeometry(QRect(430, 250, 71, 71));
        showPlaygameCarpet4 = new QTextBrowser(playgame);
        showPlaygameCarpet4->setObjectName(QString::fromUtf8("showPlaygameCarpet4"));
        showPlaygameCarpet4->setGeometry(QRect(340, 250, 71, 71));
        labelPlaygameInboxbar = new QLabel(playgame);
        labelPlaygameInboxbar->setObjectName(QString::fromUtf8("labelPlaygameInboxbar"));
        labelPlaygameInboxbar->setGeometry(QRect(310, 10, 81, 21));
        labelPlaygameOutboxbar = new QLabel(playgame);
        labelPlaygameOutboxbar->setObjectName(QString::fromUtf8("labelPlaygameOutboxbar"));
        labelPlaygameOutboxbar->setGeometry(QRect(310, 360, 91, 21));
        labelPlaygameCarpetbar = new QLabel(playgame);
        labelPlaygameCarpetbar->setObjectName(QString::fromUtf8("labelPlaygameCarpetbar"));
        labelPlaygameCarpetbar->setGeometry(QRect(390, 130, 61, 21));
        buttonPlaygameSkip = new QPushButton(playgame);
        buttonPlaygameSkip->setObjectName(QString::fromUtf8("buttonPlaygameSkip"));
        buttonPlaygameSkip->setGeometry(QRect(580, 410, 100, 32));
        stackedWidget->addWidget(playgame);
        success = new QWidget();
        success->setObjectName(QString::fromUtf8("success"));
        labelSuccessCentral = new QLabel(success);
        labelSuccessCentral->setObjectName(QString::fromUtf8("labelSuccessCentral"));
        labelSuccessCentral->setGeometry(QRect(290, 170, 201, 41));
        buttonSuccessBack = new QPushButton(success);
        buttonSuccessBack->setObjectName(QString::fromUtf8("buttonSuccessBack"));
        buttonSuccessBack->setGeometry(QRect(200, 350, 100, 32));
        buttonSuccessExit = new QPushButton(success);
        buttonSuccessExit->setObjectName(QString::fromUtf8("buttonSuccessExit"));
        buttonSuccessExit->setGeometry(QRect(460, 350, 100, 32));
        stackedWidget->addWidget(success);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 36));
        menuHuman_Resource_Machine = new QMenu(menubar);
        menuHuman_Resource_Machine->setObjectName(QString::fromUtf8("menuHuman_Resource_Machine"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuHuman_Resource_Machine->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        buttonWelcomePlaygame->setText(QCoreApplication::translate("MainWindow", "PLAYGAME", nullptr));
        buttonWelcomeLoadgame->setText(QCoreApplication::translate("MainWindow", "LOADGAME", nullptr));
        buttonWelcomeExit->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
        labelWelcomepageCentralname->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:48pt; font-weight:700;\">Human Resource Machine</span></p></body></html>", nullptr));
        buttonFailExit->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
        buttonFailRestart->setText(QCoreApplication::translate("MainWindow", "RESTART", nullptr));
        buttonFailBack->setText(QCoreApplication::translate("MainWindow", "BACK", nullptr));
        labelFailCentral->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:64pt; font-weight:700;\">FAIL</span></p></body></html>", nullptr));
        buttonLevelchoiceLevel1->setText(QCoreApplication::translate("MainWindow", "Level 1", nullptr));
        buttonLevelchoiceLevel2->setText(QCoreApplication::translate("MainWindow", "Level 2", nullptr));
        buttonLevelchoiceLevel3->setText(QCoreApplication::translate("MainWindow", "Level 3", nullptr));
        labelLevelchoiceCentrallevelchoice->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:48pt; font-weight:700;\">Level Choice</span></p></body></html>", nullptr));
        buttonLevelchoiceBack->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        buttonLoadgameLoadlevelinfo->setText(QCoreApplication::translate("MainWindow", "LOAD LEVELINFO", nullptr));
        buttonLoadgameLoadarchive->setText(QCoreApplication::translate("MainWindow", "LOAD ARCHIVE", nullptr));
        labelLoadgameCentral->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:36pt; font-weight:700;\">Load Game</span></p></body></html>", nullptr));
        buttonLoadgameBackandload->setText(QCoreApplication::translate("MainWindow", "BACK", nullptr));
        buttonLoadgameAutoload->setText(QCoreApplication::translate("MainWindow", "AUTO LOAD", nullptr));
        buttonPlaygameStart->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        labelPlaygameLogbar->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:700;\">LOG</span></p></body></html>", nullptr));
        labelPlaygameInboxbar->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">InboxBar</span></p></body></html>", nullptr));
        labelPlaygameOutboxbar->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">OutboxBar</span></p></body></html>", nullptr));
        labelPlaygameCarpetbar->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">Carpet</span></p></body></html>", nullptr));
        buttonPlaygameSkip->setText(QCoreApplication::translate("MainWindow", "SKIP", nullptr));
        labelSuccessCentral->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:64pt; font-weight:700; vertical-align:super;\">SUCCESS</span></p></body></html>", nullptr));
        buttonSuccessBack->setText(QCoreApplication::translate("MainWindow", "BACK", nullptr));
        buttonSuccessExit->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
        menuHuman_Resource_Machine->setTitle(QCoreApplication::translate("MainWindow", "Human Resource Machine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
