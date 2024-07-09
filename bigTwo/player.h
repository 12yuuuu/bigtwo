#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <QString>
#include "card.h"
#include "mainwindow.h"
class Card;
class Mainwindow;

class Player 
{
public:
    Player();
    void setHand(const std::vector<Card>& cards);
    void removeCard(const Card& card);
    void displayHand() const;
    void addCard(const Card& card);
    void setPlayerNumber(int number);
    void setMainWindow(Mainwindow* window);
    int getHandSize();
    int getScore();  // 添加获取分数的方法
    std::vector<Card> hand;
    QPixmap avatar;  // 添加头像字段
    Mainwindow* mainwindow;
    int playerNumber;
    int score = 0;  // 添加分数字段
    int getNum();
    void addScore(int number);
    QString name = "";
    void setName(const QString& newName);
    QString getName();
    bool hasCardTwo();
};

#endif // PLAYER_H
