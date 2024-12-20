#include "gamestatewindow.h"
#include <QDebug>
#include <QMessageBox>

GameWindow::GameWindow(QWidget* parent)
    : QWidget(parent), timer(new QTimer(this)), currentStep(0) {
    // 初始化状态
    playgameStates = {"开始游戏", "加载地图", "玩家移动", "完成"};

    // 布局设置
    QVBoxLayout* layout = new QVBoxLayout(this);
    pauseButton = new QPushButton("暂停游戏", this);
    resumeButton = new QPushButton("继续游戏", this);

    layout->addWidget(pauseButton);
    layout->addWidget(resumeButton);

    connect(pauseButton, &QPushButton::clicked, this, &GameWindow::pauseGame);
    connect(resumeButton, &QPushButton::clicked, this, &GameWindow::resumeGame);

    connect(timer, &QTimer::timeout, this, &GameWindow::updateState);
}

GameWindow::~GameWindow() {
    delete timer;
}

void GameWindow::startGame() {
    currentStep = 0;
    timer->start(1000); // 每秒更新状态
}

void GameWindow::updateState() {
    if (currentStep < playgameStates.size()) {
        qDebug() << "当前状态：" << QString::fromStdString(playgameStates[currentStep]);
        update(); // 触发重绘
        currentStep++;
    } else {
        timer->stop();
        QMessageBox::information(this, "游戏结束", "所有步骤已完成！");
    }
}

void GameWindow::pauseGame() {
    if (timer->isActive()) {
        timer->stop();
        qDebug() << "游戏已暂停";
    }
}

void GameWindow::resumeGame() {
    if (!timer->isActive()) {
        timer->start();
        qDebug() << "游戏已继续";
    }
}

void GameWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    if (currentStep < playgameStates.size()) {
        painter.drawText(50, 50, QString::fromStdString(playgameStates[currentStep]));
    }
    painter.drawText(50, 100, "绘制小人和状态栏...");
}
