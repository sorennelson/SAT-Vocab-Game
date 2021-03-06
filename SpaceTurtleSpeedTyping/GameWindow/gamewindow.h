#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <SFML/Graphics.hpp>
#include <gameview.h>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    // Detect keyboard pressed event
    void keyPressEvent(QKeyEvent* event);

private slots:

    // Game Start button action in starting screen.
    // Press the button will take the user to game page.
    void on_gameStartButton_clicked();

    void on_tutorialButton_clicked();

    void moveHome();

    void on_pushButton_clicked();

signals:
    void signalGameStart();
    void satGame();

private:

    // This ui reference is composed of 2 pages enabled by the stackedWidget
    // by using stackedWidge's function - setCurrentIndex(index), we have a way
    // to navigate between these 2 pages.
    Ui::GameWindow *ui;
    GameView gameView;
    sf::RenderTexture texture;

    void createGameScreen();
};

#endif // GAMEWINDOW_H
