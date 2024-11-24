#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>
#include <string>

class GameWindow : public QWidget {
    Q_OBJECT
private:
    QTimer* timer;
    std::vector<std::string> playgameStates;
    int currentStep;
    QPushButton* pauseButton;
    QPushButton* resumeButton;

public:
    explicit GameWindow(QWidget* parent = nullptr);
    ~GameWindow();

    void startGame();

private slots:
    void updateState();
    void pauseGame();
    void resumeGame();

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // GAMEWINDOW_H
