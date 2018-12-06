#include "gameview.h"
#include "ui_gameview.h"
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QtGui>


GameView::GameView(QWidget *parent) :
    ui(new Ui::GameView)
{
    ui->setupUi(this);
    lib.startRound();
    lib.updateFrame();
    initGameObjects(lib.getGameObject());

    hitIdx = 0;
    fireSound.setMedia(QUrl("qrc:/src/Sound/gun.wav"));
    textVector.push_front("this");
    textVector.push_front("is");
    textVector.push_front("some");
    textVector.push_front("body");
    textVector.push_front("speaking");

    for(int i=0; i< 10; i++)
    {
        texts[i].setString("random");
        texts[i].setFont(font);
        texts[i].setCharacterSize(18);
        texts[i].setFillColor(sf::Color::White);
    }

    texture.create(720, 800);

    // For running and debugging on mac
    if(QSysInfo::productType() == "osx") {
        sprite_texture.loadFromFile("../../../../src/Images/cute_turtle.png");
        font.loadFromFile("../../../../src/Fonts/PTZ56F.ttf");
    }
    else {
        sprite_texture.loadFromFile("../src/Images/cute_turtle.png");
        font.loadFromFile("../src/Fonts/PTZ56F.ttf");
    }

    sprite_texture.setSmooth(true);
    // Create the sprite
    sprite.setTexture(sprite_texture);
    sprite.setPosition(pXpos,pYpos);

    x_pos = rand() % 720;

    count = 0;
    firedms = 0;
    fired = false;



    timer2 = new QTimer(this);
    timer2->start(1000);
    connect(timer2, &QTimer::timeout, this, &GameView::addWord);
}

GameView::~GameView()
{
    delete ui;
}

void GameView::renderTexture() {
    text = texts[text_idx];


    texture.clear(sf::Color::Black);
    texture.draw(sprite);  // sprite is a sf::Sprite


    //change initial position by a random number
    text.setPosition(x_pos, count++);
    texture.draw(text);

    if (fired)
    {
        if (firedms++<6)
        {
            fire(pXpos, pYpos, text.getPosition().x, text.getPosition().y + 20);
        }
        else
        {
            fired = false;
            firedms = 0;
        }
    }
    // We're done drawing to the texture
    texture.display();

    // Set to a QImage
    sf::Texture rt = texture.getTexture();
    sf::Image irt = rt.copyToImage();
    const uint8_t *pp = irt.getPixelsPtr();


    QImage qi(pp, 720, 800, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();

    ui->label->setPixmap(QPixmap::fromImage(qi));
}

void GameView::addWord()
{
    text_idx++;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameView::renderTexture);
    timer->start(10);
}


void GameView::initGameObjects(std::vector<GameObjects::GameObject *> v)
{
    for (auto *obj : v)
    {
        // use obj to determine what type of obj it is and
        // update their pos, image...etc
        if (obj->getTypeString() == "player")
        {
            pXpos = std::get<0>(obj->getPos());
            pYpos = std::get<1>(obj->getPos());
        }

    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    char ch = static_cast<char>(event->key()+32);

    for(int i=0; i<10; i++)
    {
        if (!texts[i].getString().find(ch))
        {
            fire(pXpos, pYpos, texts[i].getPosition().x, texts[i].getPosition().y + 20);
            texts[i].setString(texts[i].getString().substring(1));
        }
    }

    if (event->key() == Qt::Key_Escape)
    {
        endGame();
    }
}

void GameView::fire(float x1, float y1, float x2, float y2)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };

    fired = true;
    texture.draw(line, 2, sf::Lines);
    fireSound.play();
}

void GameView::endGame()
{
    qDebug()<< "End game signaled!";
    emit homeClicked();
}
