#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPushButton>
#include <QPixmap>
#include <QList>
#include <QAction>
#include <QLabel>
#include <QTimer>
#include <QEvent>
#include <Qvector>
#include <QPen>
#include <QPainterPath>
#include <QGraphicsEllipseItem>
#include <QGraphicsProxyWidget>
#include <chrono>
#include <QMouseEvent>
#include <QTextDocument>
#include <QTextCursor>
#include <QMainWindow>
#include "card.h"
#include "button.h"
#include "carditem.h"
#include "player.h"
class Button;
class Card;
class CardItem;
class Player;

bool compareCards(const Card &a, const Card &b); 
class Mainwindow: public QGraphicsView
{
public:
    Mainwindow();
    int newWidth, newHeight;  
    QGraphicsScene * scene;
    Button * playButton, * exitButton, * setplayerButton, * setmodeButton, * setplayerButtonchoose, * settingButton;
    Button * player2Button, * player3Button, * player4Button, * pvpButton;
    //Btnitem * hintButton, *playCardsButton, *passButton;
    QPixmap* img[52];
    QList<Card> deck;       // 撲克牌堆
    QList<Card> pile1;      // 堆1
    QList<Card> pile2;      // 堆2
    QList<Card> pile3;      // 堆3
    QList<Card> pile4;      // 堆4
    bool showPile1 = false; // 是否顯示堆1
    bool showPile2 = false; // 是否顯示堆2
    bool showPile3 = false; // 是否顯示堆3
    bool showPile4 = false; // 是否顯示堆4
    Player* player1;
    Player* player2;
    Player* player3;
    Player* player4;
    void changePileVisibility();
    int getCardImageIndex(const Card& card);
    void addCardToScene(const Card& card, int x, int y);
    void addRemoveCardToScene(const Card& card, int x, int y);
    void updateVisible();
    QList<CardItem*> clickedCards;
    void addClickedCard(CardItem *card);
    void removeClickedCard(CardItem *card);
    int getClickedCardsCount() const;
    bool isCardClicked(CardItem* card);
    QLabel* remainingCardsLabel1;
    QLabel* remainingCardsLabel2;
    QLabel* remainingCardsLabel3;
    QLabel* remainingCardsLabel4;
    void setCards(int n, int x, int y, int numCards);
    void updateCards();
    void drawAvatarAndScore();
    void drawPlayerAvatarAndScore(Player* player, int x, int y);
    void playCards2(Player * player);
    std::vector<CardItem*> playedCardItems;
    std::vector<Player*> players;
    void movePlayersClock();
    void movePlayersClockwise();
    Player* currentPlayer;
    QPushButton *playCardsButton, *passButton, *hintButton;
    std::vector<Card> cardsToRemove;
    std::vector<Card> lastPlayed;
    int roundCount = 0;
    int numberOfPlayer = 4;
    void countTheScore(Player* player);
    void winGame(Player * winner);
    void deletePlayerGraphicsItems();
    QList<QGraphicsItem*> itemsToRemove;
    QList<QGraphicsItem*> listitemsToRemove;
    bool someoneWin = false;
    void setButton();
    bool isSelectionValid(const std::vector<Card>& selectedCards);
    void reGame();
    bool isPutValid(const std::vector<Card>& selectedCards, const std::vector<Card>& lastPlayed);
    int lasttype, presenttype;
    int passPlayerCount = 0;
    bool first = true;
    void showScore();
    std::vector<CardItem*> manycards;
    QVector<QPushButton*> buttonList;
public slots:
    void startplay();
    void endgame();
    void setmode();
    void setplayer();
    void chooseplayer();
    void choosemode();
    void playCards();
    void pass();
    void settingmode();
    void playertwo();
    void playerthree();
    void playerfour();
    void recommandCard();
};

#endif