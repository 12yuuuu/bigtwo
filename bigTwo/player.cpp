#include "player.h"
#include <QDebug>

Player::Player() {}

void Player::setHand(const std::vector<Card>& cards) {
    hand = cards;
}

void Player::removeCard(const Card& card) {
    // 在這裡實現移除手牌的邏輯
    // 你可以使用向量的相關函數，如erase()，來移除手牌中的特定卡片
}

void Player::displayHand() const 
{
    QString remainingText = QString::number(hand.size());

    if (playerNumber == 1) {
        mainwindow->remainingCardsLabel1->setText(remainingText);
    } else if (playerNumber == 2) {
        mainwindow->remainingCardsLabel2->setText(remainingText);
    } else if (playerNumber == 3) {
        mainwindow->remainingCardsLabel3->setText(remainingText);
    } else if (playerNumber == 4) {
        mainwindow->remainingCardsLabel4->setText(remainingText);
    }
}

void Player::setPlayerNumber(int number) {
    playerNumber = number;
    // 根据编号设置对应的图片路径
    if (playerNumber == 1) {
        if (!avatar.load("./dataset/images/player.png")) {
            qDebug() << "Failed to load player.png";
        }
    } else if (playerNumber == 2) {
        if (!avatar.load("./dataset/images/friend_1.png")) {
            qDebug() << "Failed to load friend_1.png";
        }
    } else if (playerNumber == 3) {
        if (!avatar.load("./dataset/images/friend_2.png")) {
            qDebug() << "Failed to load friend_2.png";
        }
    } else if (playerNumber == 4) {
        if (!avatar.load("./dataset/images/friend_3.png")) {
            qDebug() << "Failed to load friend_3.png";
        }
    }
}

void Player::addCard(const Card& card) {
    hand.push_back(card);
}

void Player::setMainWindow(Mainwindow* window) {
    mainwindow = window;
}

int Player::getHandSize() {
    return hand.size();
}

int Player::getScore() {
    return score;
}

QString Player::getName() {
    return name;
}

void Player::setName(const QString& newName) {
    name = newName;
}

int Player::getNum() {
    return playerNumber;
}

void Player::addScore(int number){
    score += number;
}

bool Player::hasCardTwo(){
    for (int i = 0; i < hand.size(); i++)
    {
        if (hand[i].getRank() == 12)
            return true;
    }
    return false;
}