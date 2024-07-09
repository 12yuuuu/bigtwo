#include "mainwindow.h"
#include <QImage>
#include <QGraphicsView>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <algorithm>
#include <QSound>

Mainwindow::Mainwindow()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1920,1080);
    setScene(scene);
 
    QPixmap backgroundPixmap("./dataset/images/bg.png");
    scene->setBackgroundBrush(backgroundPixmap);

    playButton = new Button("./dataset/images/start_game0.png", "./dataset/images/start_game1.png", 300 , 150);
    playButton->setPos(600, 400);
    connect(playButton, &Button::clicked, this, &Mainwindow::startplay);
    scene->addItem(playButton);

    exitButton = new Button("./dataset/images/exit0.png", "./dataset/images/exit1.png", 300 , 150);
    exitButton->setPos(1000, 400);
    connect(exitButton, &Button::clicked, this, &Mainwindow::endgame);
    scene->addItem(exitButton);

    settingButton = new Button("./dataset/images/setting0.png", "./dataset/images/setting1.png", 300 , 150);
    settingButton->setPos(1400, 400);
    connect(settingButton, &Button::clicked, this, &Mainwindow::settingmode);
    scene->addItem(settingButton);

    img[0] = new QPixmap("./dataset/images/3_of_spades.png");
    img[1] = new QPixmap("./dataset/images/4_of_spades.png");
    img[2] = new QPixmap("./dataset/images/5_of_spades.png");
    img[3] = new QPixmap("./dataset/images/6_of_spades.png");
    img[4] = new QPixmap("./dataset/images/7_of_spades.png");
    img[5] = new QPixmap("./dataset/images/8_of_spades.png");
    img[6] = new QPixmap("./dataset/images/9_of_spades.png");
    img[7] = new QPixmap("./dataset/images/10_of_spades.png");
    img[8] = new QPixmap("./dataset/images/jack_of_spades.png");
    img[9] = new QPixmap("./dataset/images/queen_of_spades.png");
    img[10] = new QPixmap("./dataset/images/king_of_spades.png");
    img[11] = new QPixmap("./dataset/images/ace_of_spades.png");
    img[12] = new QPixmap("./dataset/images/2_of_spades.png");

    img[13] = new QPixmap("./dataset/images/3_of_hearts.png");
    img[14] = new QPixmap("./dataset/images/4_of_hearts.png");
    img[15] = new QPixmap("./dataset/images/5_of_hearts.png");
    img[16] = new QPixmap("./dataset/images/6_of_hearts.png");
    img[17] = new QPixmap("./dataset/images/7_of_hearts.png");
    img[18] = new QPixmap("./dataset/images/8_of_hearts.png");
    img[19] = new QPixmap("./dataset/images/9_of_hearts.png");
    img[20] = new QPixmap("./dataset/images/10_of_hearts.png");
    img[21] = new QPixmap("./dataset/images/jack_of_hearts.png");
    img[22] = new QPixmap("./dataset/images/queen_of_hearts.png");
    img[23] = new QPixmap("./dataset/images/king_of_hearts.png");
    img[24] = new QPixmap("./dataset/images/ace_of_hearts.png");
    img[25] = new QPixmap("./dataset/images/2_of_hearts.png");

    img[26] = new QPixmap("./dataset/images/3_of_diamonds.png");
    img[27] = new QPixmap("./dataset/images/4_of_diamonds.png");
    img[28] = new QPixmap("./dataset/images/5_of_diamonds.png");
    img[29] = new QPixmap("./dataset/images/6_of_diamonds.png");
    img[30] = new QPixmap("./dataset/images/7_of_diamonds.png");
    img[31] = new QPixmap("./dataset/images/8_of_diamonds.png");
    img[32] = new QPixmap("./dataset/images/9_of_diamonds.png");
    img[33] = new QPixmap("./dataset/images/10_of_diamonds.png");
    img[34] = new QPixmap("./dataset/images/jack_of_diamonds.png");
    img[35] = new QPixmap("./dataset/images/queen_of_diamonds.png");
    img[36] = new QPixmap("./dataset/images/king_of_diamonds.png");
    img[37] = new QPixmap("./dataset/images/ace_of_diamonds.png");
    img[38] = new QPixmap("./dataset/images/2_of_diamonds.png");
    
    img[39] = new QPixmap("./dataset/images/3_of_clubs.png");
    img[40] = new QPixmap("./dataset/images/4_of_clubs.png");
    img[41] = new QPixmap("./dataset/images/5_of_clubs.png");
    img[42] = new QPixmap("./dataset/images/6_of_clubs.png");
    img[43] = new QPixmap("./dataset/images/7_of_clubs.png");
    img[44] = new QPixmap("./dataset/images/8_of_clubs.png");
    img[45] = new QPixmap("./dataset/images/9_of_clubs.png");
    img[46] = new QPixmap("./dataset/images/10_of_clubs.png");
    img[47] = new QPixmap("./dataset/images/jack_of_clubs.png");
    img[48] = new QPixmap("./dataset/images/queen_of_clubs.png");
    img[49] = new QPixmap("./dataset/images/king_of_clubs.png");
    img[50] = new QPixmap("./dataset/images/ace_of_clubs.png");
    img[51] = new QPixmap("./dataset/images/2_of_clubs.png");
}

void Mainwindow::startplay()
{
    if(scene)
    {
        scene -> removeItem(playButton);
        delete playButton;
        playButton = nullptr;
        scene -> removeItem(exitButton);
        delete exitButton;
        exitButton = nullptr;
        scene -> removeItem(settingButton);
        delete settingButton;
        settingButton = nullptr;
        scene -> clear();
    }
   
    QPixmap backgroundPixmap("./dataset/images/table_1.png");
    scene->setBackgroundBrush(backgroundPixmap);
    setButton();
    
    for (int suit = Card::Clubs; suit <= Card::Spades; suit++) {
        for (int rank = Card::Three; rank <= Card::Two; rank++) {
            Card card(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank));
            deck.append(card);
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
    // 找梅花三
    int index = -1;
    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].getSuit() == Card::Clubs && deck[i].getRank() == 0) {
            index = i;
            break;
        }
    }
    if(index != -1)
    {
        deck.push_front(deck.takeAt(index));
    }

    if (numberOfPlayer == 4)
    {
        pile1 = deck.mid(0, 13);
        pile2 = deck.mid(13, 13);
        pile3 = deck.mid(26, 13);
        pile4 = deck.mid(39, 13);
    }
    else if (numberOfPlayer == 3)
    {
        pile1 = deck.mid(0, 17);
        pile2 = deck.mid(17, 17);
        pile3 = deck.mid(34, 0);
        pile4 = deck.mid(34, 18);
    }
    else if (numberOfPlayer == 2)
    {
        pile1 = deck.mid(0, 26);
        pile2 = deck.mid(26, 0);
        pile3 = deck.mid(26, 26);
        pile4 = deck.mid(52, 0);
    }

    std::vector<Card> stdPile1;
    stdPile1.reserve(pile1.size());
    for (const Card& card : pile1) {
        stdPile1.push_back(card);
    }
 
    std::vector<Card> stdPile2;
    stdPile2.reserve(pile2.size());
    for (const Card& card : pile2) {
        stdPile2.push_back(card);
    }
 
    std::vector<Card> stdPile3;
    stdPile3.reserve(pile3.size());
    for (const Card& card : pile3) {
        stdPile3.push_back(card);
    }
 
    std::vector<Card> stdPile4;
    stdPile4.reserve(pile4.size());
    for (const Card& card : pile4) {
        stdPile4.push_back(card);
    }

    player1 = new Player();
    player2 = new Player();
    player3 = new Player();
    player4 = new Player();
 
    player1->setMainWindow(this);
    player2->setMainWindow(this);
    player3->setMainWindow(this);
    player4->setMainWindow(this);

    player1->setHand(stdPile1);
    player2->setHand(stdPile2);
    player3->setHand(stdPile3);
    player4->setHand(stdPile4);
 
    player1->setPlayerNumber(1);
    player2->setPlayerNumber(2);
    player3->setPlayerNumber(3);
    player4->setPlayerNumber(4);

    player1->setName("Amy");
    player2->setName("Linda");
    player3->setName("Iris");
    player4->setName("Kelly");

    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);

    // 顯示初始撲克牌堆
    showPile1 = true;
    currentPlayer = player1;
    updateVisible();
    updateCards();
    drawAvatarAndScore();
}

void Mainwindow::setmode(){
    pvpButton = new Button("./dataset/images/pvp0.png", "./dataset/images/pvp1.png", 270 , 135);
    pvpButton->setPos(815, 720);
    connect(pvpButton, &Button::clicked, this, &Mainwindow::choosemode);
    scene->addItem(pvpButton);
}

void Mainwindow::playertwo(){
    numberOfPlayer = 2;
    chooseplayer();
}

void Mainwindow::playerthree(){
    numberOfPlayer = 3;
    chooseplayer();
}

void Mainwindow::playerfour(){
    numberOfPlayer = 4;
    chooseplayer();
}

void Mainwindow::setplayer(){
    player2Button = new Button("./dataset/images/player2_0.png", "./dataset/images/player2_1.png", 200, 200);
    player2Button->setPos(450, 720);
    connect(player2Button, &Button::clicked, this, &Mainwindow::playertwo);
    scene->addItem(player2Button);
    player3Button = new Button("./dataset/images/player3_0.png", "./dataset/images/player3_1.png", 200, 200);
    player3Button->setPos(450, 845);
    connect(player3Button, &Button::clicked, this, &Mainwindow::playerthree);
    scene->addItem(player3Button);
    player4Button = new Button("./dataset/images/player4_0.png", "./dataset/images/player4_1.png", 200, 200);
    player4Button->setPos(450, 970);
    connect(player4Button, &Button::clicked, this, &Mainwindow::playerfour);
    scene->addItem(player4Button);
}

void Mainwindow::chooseplayer()
{
    if(scene)
    {
        scene -> removeItem(player2Button);
        delete player2Button;
        player2Button = nullptr;
        scene -> removeItem(player3Button);
        delete player3Button;
        player3Button = nullptr;
        scene -> removeItem(player4Button);
        delete player4Button;
        player4Button = nullptr;
    }
}

void Mainwindow::choosemode(){
    if (scene)
    {
        scene -> removeItem(pvpButton);
        delete pvpButton;
        pvpButton = nullptr;
    }
}

void Mainwindow::endgame(){
    if(scene)
    {
        scene -> removeItem(playButton);
        delete playButton;
        playButton = nullptr;
        scene -> removeItem(exitButton);
        delete exitButton;
        exitButton = nullptr;
        scene -> removeItem(setplayerButton);
        delete setplayerButton;
        setplayerButton = nullptr;
        scene -> removeItem(setmodeButton);
        delete setmodeButton;
        setmodeButton = nullptr;
        scene -> clear();
    }
    QPixmap backgroundPixmap("./dataset/images/bg.png");
    scene->setBackgroundBrush(backgroundPixmap);
}

void Mainwindow::settingmode(){
    setplayerButton = new Button("./dataset/images/player_number0.png", "./dataset/images/player_number1.png", 300 , 150);
    setplayerButton->setPos(400, 580);
    connect(setplayerButton, &Button::clicked, this, &Mainwindow::setplayer);
    scene->addItem(setplayerButton);

    setmodeButton = new Button("./dataset/images/mode0.png", "./dataset/images/mode1.png", 300 , 150);
    setmodeButton->setPos(800, 580);
    connect(setmodeButton, &Button::clicked, this, &Mainwindow::setmode);
    scene->addItem(setmodeButton);
}

void Mainwindow::changePileVisibility()
{
    roundCount++;
    if (numberOfPlayer == 4)
    {
        if (showPile1) {
            showPile1 = false;
            showPile2 = true;
            currentPlayer = player2;
        } else if (showPile2) {
            showPile2 = false;
            showPile3 = true;
            currentPlayer = player3;
        } else if (showPile3) {
            showPile3 = false;
            showPile4 = true;
            currentPlayer = player4;
        } else if (showPile4) {
            showPile4 = false;
            showPile1 = true;
            currentPlayer = player1;
        }
    }
    else if (numberOfPlayer == 3)
    {
        if (showPile1) {
            showPile1 = false;
            showPile2 = true;
            currentPlayer = player2;
        } else if (showPile2) {
            showPile2 = false;
            showPile4 = true;
            currentPlayer = player4;
        } else if (showPile4) {
            showPile4 = false;
            showPile1 = true;
            currentPlayer = player1;
        }
    }
    else if (numberOfPlayer == 2)
    {
        if (showPile1) {
            showPile1 = false;
            showPile3 = true;
            currentPlayer = player3;
        } else if (showPile3) {
            showPile3 = false;
            showPile1 = true;
            currentPlayer = player1;
        }
    }

    for (QGraphicsItem* item : itemsToRemove) {
        scene->removeItem(item);
        delete item;
    }
    itemsToRemove.clear();
    manycards.clear();
    movePlayersClock();
    updateVisible();
    drawAvatarAndScore();
}


int Mainwindow::getCardImageIndex(const Card& card) {
    int suitOffset = 0;
    switch (card.getSuit()) {
        case Card::Spades:
            suitOffset = 0;
            break;
        case Card::Hearts:
            suitOffset = 13;
            break;
        case Card::Diamonds:
            suitOffset = 26;
            break;
        case Card::Clubs:
            suitOffset = 39;
            break;
    }
    return suitOffset + card.getRank();
}

void Mainwindow::addCardToScene(const Card& card, int x, int y) 
{
    int imageIndex = getCardImageIndex(card);   
    if (imageIndex >= 0 && imageIndex < 52) {
        CardItem* cardItem = new CardItem(this, *img[imageIndex], card);
        cardItem->setScale(0.25);
        cardItem->setPos(x, y);
        cardItem->setZValue(300);
        scene->addItem(cardItem);
        manycards.push_back(cardItem);
        itemsToRemove.append(cardItem);
        cardItem->setFocus();
    } else {
        qDebug() << "Invalid image index: " << imageIndex;
    }
}

bool compareCards(const Card &a, const Card &b) {
    if (a.getRank() == b.getRank()) {
        return a.getSuit() < b.getSuit();
    } else {
        return a.getRank() < b.getRank();
    }
}

void Mainwindow::updateVisible()
{
    scene->clear();
    int cardSpacing = 60; 
    int baseX = 480; 
    int baseY = 620; 
    if (numberOfPlayer == 4)
    {
        cardSpacing = 60; 
        baseX = 480; 
    }
    else if (numberOfPlayer == 3)
    {
        cardSpacing = 50; 
        baseX = 480; 
    }
    else if (numberOfPlayer == 2)
    {
        cardSpacing = 40; 
        baseX = 400; 
    }

    // 显示 pile
    if(currentPlayer = player1){
        std::sort(player1->hand.begin(), player1->hand.end(), compareCards);
        for (int i = 0; i < player1->hand.size(); i++) {
            addCardToScene(player1->hand[i], baseX + i * cardSpacing, baseY);
        }
    }
    else if(currentPlayer = player2){
        std::sort(player2->hand.begin(), player2->hand.end(), compareCards);
        for (int i = 0; i < player2->hand.size(); i++) {
            addCardToScene(player2->hand[i], baseX + i * cardSpacing, baseY);
        }
    }
    else if(currentPlayer = player3){
        std::sort(player3->hand.begin(), player3->hand.end(), compareCards);
        for (int i = 0; i < player3->hand.size(); i++) {
            addCardToScene(player3->hand[i], baseX + i * cardSpacing, baseY);
        }
    }
    else if(currentPlayer = player4){
        std::sort(player4->hand.begin(), player4->hand.end(), compareCards);
        for (int i = 0; i < player4->hand.size(); i++) {
            addCardToScene(player4->hand[i], baseX + i * cardSpacing, baseY);
        }
    }
    for (int i = 0; i<cardsToRemove.size(); i++)
    {
        addRemoveCardToScene(cardsToRemove[i], 500 + i*110, 350);
    }
    updateCards();
}

void Mainwindow::addClickedCard(CardItem *card)
{
    clickedCards.append(card);
    QSound::play("./dataset/sounds/dong.wav");
}

void Mainwindow::removeClickedCard(CardItem *card)
{
    clickedCards.removeOne(card);
    QSound::play("./dataset/sounds/dong.wav");
}

int Mainwindow::getClickedCardsCount() const
{
    return clickedCards.size();
}

bool Mainwindow::isCardClicked(CardItem* card) {
    for (CardItem* clickedCard : clickedCards) {
        if (clickedCard == card) {
            return true;
        }
    }
    return false;
}

void Mainwindow::setCards(int n, int x, int y, int numCards) 
{
    for(int i = 0; i < numCards; i++) {
        QGraphicsPixmapItem *cardImage = new QGraphicsPixmapItem();
        QPixmap cardPixmap = QPixmap("./dataset/images/card.png");
        if (numberOfPlayer == 4)
            cardPixmap = cardPixmap.scaled(cardPixmap.width()*0.15, cardPixmap.height()*0.15);
        else if (numberOfPlayer == 3)
            cardPixmap = cardPixmap.scaled(cardPixmap.width()*0.1, cardPixmap.height()*0.1);
        else if (numberOfPlayer == 2)
            cardPixmap = cardPixmap.scaled(cardPixmap.width()*0.07, cardPixmap.height()*0.07);
        if (n == 1) {
            cardImage->setPos(x, y + i * 30);
            cardImage->setRotation(-90);
        } else if (n == 2) {
            cardImage->setPos(x + i * 30, y);
        } else if (n == 3) {
            cardImage->setPos(x, y - i * 30);
            cardImage->setRotation(90);
        }
        cardImage->setPixmap(cardPixmap);
        // 如果是最后一张卡，则添加一个显示卡牌数量的文本项
        if (i == numCards - 1) {
            QGraphicsTextItem* cardCountText = new QGraphicsTextItem(QString::number(numCards));
            cardCountText->setDefaultTextColor(Qt::white);
            QFont font("Comic Sans MS", 15);
            cardCountText->setFont(font);

            // 根据堆的编号设置文本的位置
            if (n == 1) {
                QPointF textPos(cardImage->boundingRect().center().x() - cardCountText->boundingRect().width() / 2, cardImage->boundingRect().top()*0.6 - cardImage->boundingRect().height() / 2 - cardCountText->boundingRect().height() / 2);
                cardCountText->setPos(cardImage->pos() + textPos);
            } else if (n == 2) {
                QPointF textPos(cardImage->boundingRect().width() / 2 - cardCountText->boundingRect().width() / 2, cardImage->boundingRect().height() / 2 - cardCountText->boundingRect().height() / 2);
                cardCountText->setPos(cardImage->pos() + textPos);
            } else if (n == 3) {
                QPointF textPos(cardImage->boundingRect().center().x() - cardCountText->boundingRect().width() - 80, cardImage->boundingRect().top()*0.6 + cardImage->boundingRect().height() / 2 - cardCountText->boundingRect().height() / 2);
                cardCountText->setPos(cardImage->pos() + textPos);
            }

            // 添加圆形边框
            qreal radius = qMax(cardCountText->boundingRect().width(), cardCountText->boundingRect().height()) / 2.0;
            QGraphicsEllipseItem* borderItem = new QGraphicsEllipseItem(-radius, -radius, radius * 2, radius * 2);
            borderItem->setPen(QPen(Qt::white, 3));
            borderItem->setPos(cardCountText->pos() + QPointF(radius, radius)); // 调整边框的位置为文本的位置加上半径

            // 创建一个组合项，将卡片、文本和边框作为一个组合
            QGraphicsItemGroup* group = new QGraphicsItemGroup();
            group->addToGroup(cardImage);
            group->addToGroup(cardCountText);
            group->addToGroup(borderItem);
            scene->addItem(group);
            itemsToRemove.append(group);
        } else {
            scene->addItem(cardImage);
            itemsToRemove.append(cardImage);
        }
    }
}
 
// 在初始化或需要更新卡片数量的地方调用此函数
void Mainwindow::updateCards() 
{
    int numCards2 = player2->getHandSize();
    int numCards3 = player3->getHandSize();
    int numCards4 = player4->getHandSize();
    if (numberOfPlayer == 3)
    {
        setCards(1, 1500, 300, numCards2);
    }
    else
    {
        setCards(1, 1500, 350, numCards2);
    }
    if (numberOfPlayer == 2)
    {
        setCards(2, 400, 200, numCards3);
    }
    else
    {
        setCards(2, 600, 140, numCards3);
    }
    if (numberOfPlayer == 3)
    {
        setCards(3, 400, 750, numCards4);
    }
    else
    {
        setCards(3, 400, 620, numCards4);
    }
}

void Mainwindow::drawAvatarAndScore() {
    if (numberOfPlayer == 4)
    {
        drawPlayerAvatarAndScore(player1, 600, 900);
        drawPlayerAvatarAndScore(player2, 1720, 620);
        drawPlayerAvatarAndScore(player3, 1200, 20);
        drawPlayerAvatarAndScore(player4, 35, 300);
    }
    else if (numberOfPlayer == 3)
    {
        drawPlayerAvatarAndScore(player1, 600, 900);
        drawPlayerAvatarAndScore(player2, 1720, 620);
        drawPlayerAvatarAndScore(player4, 35, 300);
    }
    else if (numberOfPlayer == 2)
    {
        drawPlayerAvatarAndScore(player1, 600, 900);
        drawPlayerAvatarAndScore(player3, 1200, 20);
    }  
}

void Mainwindow::drawPlayerAvatarAndScore(Player* player, int x, int y) {
    // 添加頭像
    QGraphicsPixmapItem* avatarItem = new QGraphicsPixmapItem(player->avatar);
    avatarItem->setPos(x, y);
    avatarItem->setScale(0.6);
    scene->addItem(avatarItem);
    itemsToRemove.append(avatarItem);

    // 添加分數
    QGraphicsTextItem* scoreText = new QGraphicsTextItem;
    scoreText->setPlainText(QString::number(player->getScore()));
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setFont(QFont("Arial", 15));
    if ( y + player->avatar.height() + 50 > 1000)
    {
        scoreText->setPos(x + player->avatar.width()*0.6 + 150,  y + 15);
    }
    else
    {
        scoreText->setPos(x, y + player->avatar.height()*0.6 + 50);
    }
    scene->addItem(scoreText);
    itemsToRemove.append(scoreText);

    // 添加名字
    QGraphicsTextItem* nameText = new QGraphicsTextItem;
    nameText->setPlainText(player->getName());
    nameText->setDefaultTextColor(Qt::white);
    nameText->setFont(QFont("Arial", 15));
    if (y + player->avatar.height() + 10 > 1000)
    {
        nameText->setPos(x + player->avatar.width()*0.6 + 50, y + 15);
    }
    else
    {
        nameText->setPos(x, y + player->avatar.height()*0.6 + 10);
    }
    scene->addItem(nameText);
    itemsToRemove.append(nameText);

    QGraphicsTextItem* roundText = new QGraphicsTextItem;
    if (numberOfPlayer == 4)
    {
        roundText->setPlainText(QString::number(roundCount/4 + 1));
    }
    else if (numberOfPlayer == 3)
    {
        roundText->setPlainText(QString::number(roundCount/3 + 1));
    }
    else if (numberOfPlayer == 2)
    {
        roundText->setPlainText(QString::number(roundCount/2 + 1));
    }
    roundText->setDefaultTextColor(Qt::white);
    roundText->setFont(QFont("Comic Sans MS", 50));
    roundText->setPos(100, 50);
    scene->addItem(roundText);
    itemsToRemove.append(roundText);
}

void Mainwindow::playCards()
{
    playCards2(player1);
    qDebug()<<"hi";
}

void Mainwindow::playCards2(Player * player)
{
    cardsToRemove.clear();
    for (CardItem* cardItem : clickedCards) {
        cardsToRemove.push_back(cardItem->getCard());
    }
    std::vector<Card> selectedCards = cardsToRemove;
    bool isvalid = false;
    if(first){
        for(int i = 0; i < selectedCards.size(); i++){
            if(selectedCards[i].getRank() == 0 &&selectedCards[i].getSuit() == 0){
                if(selectedCards[i].getRank() == 0 &&selectedCards[i].getSuit() == 0){
                    if(lastPlayed.size() == 0){
                        isvalid = true;
                    } 
                }
            }
        }
        first = false;
    }
    else{
        if (isSelectionValid(selectedCards)) {
            if(isPutValid(selectedCards, lastPlayed) || lastPlayed.size() == 0){
                isvalid = true;
            }
        }
    }
    if (isvalid){
        for (const Card& card : cardsToRemove) {
            auto it = std::find(player->hand.begin(), player->hand.end(), card);
            if (it != player->hand.end()) {
                player->hand.erase(it);
            }
        }
        if (player->hand.size() == 0)
        {
            countTheScore(player);
        }
        else
        {
            changePileVisibility();
        }
        QSound::play("./dataset/sounds/shiu.wav");
        qDebug() << "push";
        lastPlayed = cardsToRemove;
        lasttype = presenttype;
        qDebug()<<"last"<<lasttype;
        clickedCards.clear();
        passPlayerCount = 0;
    }
    else{
        qDebug() << "delete";
        QSound::play("./dataset/sounds/dengdeng.wav");
        for(auto& card : clickedCards)
        {
            card->setCardItem();
        }
        cardsToRemove.clear();
        clickedCards.clear();
    }
}

void Mainwindow::movePlayersClock()
{
    if (numberOfPlayer == 4)
    {
        Player* temp = player1;
        player1 = player2;
        player2 = player3;
        player3 = player4;
        player4 = temp;
    }
    else if (numberOfPlayer == 3)
    {
        Player* temp = player1;
        player1 = player2;
        player2 = player4;
        player4 = temp;
    }
    else if (numberOfPlayer == 2)
    {
        Player* temp = player1;
        player1 = player3;
        player3 = temp;
    } 
    clickedCards.clear(); 
}

void Mainwindow::movePlayersClockwise()
{
    if (numberOfPlayer == 4)
    {
        Player* temp = player1;
        player1 = player4;
        player4 = player3;
        player3 = player2;
        player2 = temp;
    }
    else if (numberOfPlayer == 3)
    {
        Player* temp = player1;
        player1 = player4;
        player4 = player2;
        player2 = temp;
    }
    else if (numberOfPlayer == 2)
    {
        Player* temp = player1;
        player1 = player3;
        player3 = temp;
    } 
}

void Mainwindow::countTheScore(Player* player)
{
    someoneWin = true;
    setButton();
    someoneWin = false;
    int score = 0;
    for (int i = 0; i < players.size(); i++) {
        Player* otherPlayer = players[i];
        if (otherPlayer != player) {
            if (otherPlayer->hasCardTwo()) {
                score += otherPlayer->getHandSize()*2;
            }
            else
            {
                score += otherPlayer->getHandSize();
            }
        }
    }
    player->addScore(score);
    if (player->getScore() >= 50)
    {
        winGame(player);
    }
    else
    {    
        showScore();
    } 
}

void Mainwindow::winGame(Player * winner)
{
    someoneWin = true;
    setButton();

    if(scene)
    {
        scene->clear();
    }
    QPixmap backgroundPixmap("./dataset/images/win_bg.png");
    scene->setBackgroundBrush(backgroundPixmap);

    QGraphicsPixmapItem* avatarItem = new QGraphicsPixmapItem(winner->avatar);
    avatarItem->setScale(1.8);
    avatarItem->setPos(730, 390);
    avatarItem->setZValue(10);
    scene->addItem(avatarItem);

    QString winnerName = winner->getName();
    QString winnerText = "You are the winner <span style='color: red'>" + winnerName + "</span> !";
    QTextDocument* textDocument = new QTextDocument;
    QTextCursor textCursor(textDocument);
    textCursor.insertHtml(winnerText);
    QGraphicsTextItem* winText = new QGraphicsTextItem;
    winText->setDocument(textDocument);
    winText->setPos(400,200);
    winText->setFont(QFont("Comic Sans MS", 40));
    winText->setDefaultTextColor(Qt::white);  // 設置預設文字顏色為白色
    scene->addItem(winText);
}

void Mainwindow::setButton()
{
    QPushButton* playCardsButton = new QPushButton("",this);
    playCardsButton->setIcon(QIcon("./dataset/images/play0.png"));
    playCardsButton->setIconSize(QSize(150, 50));
    playCardsButton->setFlat(true);
    connect(playCardsButton, &QPushButton::clicked, this, &Mainwindow::playCards);
    playCardsButton->setGeometry(QRect(QPoint(980, 500), QSize(150, 50)));
    playCardsButton->show();
    buttonList.append(playCardsButton);

    QPushButton* passButton = new QPushButton("",this);
    passButton->setIcon(QIcon("./dataset/images/passbtn0.png"));
    passButton->setIconSize(QSize(150, 50));
    passButton->setFlat(true);
    connect(passButton, &QPushButton::clicked, this, &Mainwindow::changePileVisibility);
    connect(passButton, &QPushButton::clicked, this, &Mainwindow::pass);
    passButton->setGeometry(QRect(QPoint(1140, 500), QSize(150, 50)));
    passButton->show();
    buttonList.append(passButton);

    QPushButton* hintButton = new QPushButton("",this);
    hintButton->setIcon(QIcon("./dataset/images/hint0.png"));
    hintButton->setIconSize(QSize(125, 48));
    hintButton->setFlat(true);
    connect(hintButton, &QPushButton::clicked, this, &Mainwindow::recommandCard);
    hintButton->setGeometry(QRect(QPoint(1330, 500), QSize(125, 48)));
    hintButton->show();
    buttonList.append(hintButton);

    if (someoneWin)
    {
        for (QPushButton* button : buttonList) {
            delete button;
        }
        buttonList.clear();
    }
}

bool Mainwindow::isSelectionValid(const std::vector<Card>& selectedCards)
{
    
    if (selectedCards.empty()) {
        qDebug() << "empty"<< endl;
        return false;
    }

    std::vector<Card> sortedCards = selectedCards;
    std::sort(sortedCards.begin(), sortedCards.end(), [](const Card& card1, const Card& card2) {
        return card1.getRank() < card2.getRank();
    });

    std::map<Card::Rank, int> rankCount; 
    for (const Card& card : sortedCards) {
        rankCount[card.getRank()]++; 
    }

    switch (sortedCards.size()) {
        case 1:
            qDebug() << "only one card" << endl;
            presenttype = 0;
            return true;
        case 2: // 一对
        {
            bool hasPair = false;
            for (const auto& pair : rankCount) {
                if (pair.second == 2) {
                    qDebug() << "a pair" << endl;
                    hasPair = true; // 是否有两张相同点数的牌
                    presenttype = 1;
                    return true;
                } else {
                    qDebug() << "no pair" << endl;
                    return false;
                }
            }
            break;
        }
        case 3:
            qDebug() << "three cards wrong number" << endl;
            return false;
            break;
        case 4:
            qDebug() << "four cards wrong number" << endl;
            return false;
            break;
        case 5:
        {
            bool Valid = true;
            int suittest = sortedCards[0].getSuit();
            for(int i = 0; i < 5; i++){
                if(sortedCards[i].getSuit() != suittest){
                    Valid = false;
                }
            }
            if(Valid){
                int prevRank = sortedCards[0].getRank();
                if((prevRank == 0 )&&(sortedCards[1].getRank() == 1 )&& (sortedCards[2].getRank() == 2)&&( sortedCards[3].getRank() == 3)&&( sortedCards[4].getRank() == 12)){
                    qDebug() << "23456" << endl;
                    presenttype = 5;
                    qDebug() << "same_flower" << endl;
                    return true;
                }
                else if ((prevRank == 0)&&(sortedCards[1].getRank() == 1)&& (sortedCards[2].getRank() == 2)&&( sortedCards[3].getRank() == 11)&&( sortedCards[4].getRank() == 12)){
                    qDebug() << "A2345" << endl;
                    presenttype = 5;
                    qDebug() << "same_flower" << endl;
                    return true;
                }
                else if(prevRank >= 0 && prevRank <= 7){
                    bool valid = true;
                    for (int i = 1; i < sortedCards.size(); i++) {
                        int currentRank = sortedCards[i].getRank();
                        if (currentRank - prevRank != 1) {
                            valid = false; 
                        }
                        prevRank = currentRank;
                    }
                    if(valid){
                        presenttype = 5;
                        qDebug() << "same_flower" << endl;
                        return true;
                    }
                }
            }

            bool hasFourOfAKind = false;
            bool hasOneOfAKind = false;
            for (const auto& pair : rankCount) {
                if (pair.second == 4) {
                    hasFourOfAKind = true;
                } 
                else if (pair.second == 1) {
                    hasOneOfAKind = true;
                }
            }
            if (hasFourOfAKind && hasOneOfAKind) {
                presenttype = 4;
                qDebug() << "iron" << endl;
                return true;
            }

            bool hasThreeOfAKind = false;
            bool hasPair = false;
            for (const auto& pair : rankCount) {
                if (pair.second == 3) {
                    hasThreeOfAKind = true;
                } 
                else if (pair.second == 2) {
                    hasPair = true;
                }
            }
            if (hasThreeOfAKind && hasPair) {
                presenttype = 3;
                qDebug() << "circle" << endl;
                return true;
            }
            
            int prevRank = sortedCards[0].getRank();
            if((prevRank == 0 )&&(sortedCards[1].getRank() == 1 )&& (sortedCards[2].getRank() == 2)&&( sortedCards[3].getRank() == 3)&&( sortedCards[4].getRank() == 12)){
                qDebug() << "23456" << endl;
                presenttype = 2;
                return true;
            }
            else if ((prevRank == 0)&&(sortedCards[1].getRank() == 1)&& (sortedCards[2].getRank() == 2)&&( sortedCards[3].getRank() == 11)&&( sortedCards[4].getRank() == 12)){
                qDebug() << "A2345" << endl;
                presenttype = 2;
                return true;
            }
            else if(prevRank >= 0 && prevRank <= 7){
                qDebug() << "!!" << endl;
                for (int i = 1; i < sortedCards.size(); i++) {
                    int currentRank = sortedCards[i].getRank();
                    if (currentRank - prevRank != 1) {
                        return false; 
                    }
                    prevRank = currentRank;
                }
                qDebug() << "why" << endl;
                presenttype = 2;
                return true;
            }
            else{
                return false;
            }
        }
    }
}

bool Mainwindow::isPutValid(const std::vector<Card>& selectedCards, const std::vector<Card>& lastPlayed){
    //compare
    qDebug()<<"pre"<<presenttype;
    switch(presenttype){
        case 0:
            if(lasttype == 0){
                if(presenttype == 5 || presenttype == 4){
                    return true; 
                }
                if(lastPlayed[0].getRank() < selectedCards[0].getRank()){
                    qDebug() << "one card: rank bigger, true" << endl;
                    return true;
                }
                else if(lastPlayed[0].getRank() == selectedCards[0].getRank()){
                    if(lastPlayed[0].getSuit() < selectedCards[0].getSuit()){
                        qDebug() << "one card: suit bigger, true" << endl;
                        return true;
                    }
                    else{
                        qDebug() << "one card: suit smaller, false" << endl;
                        return false;
                    }
                }
                else{
                    qDebug() << "one card: rank smaller, false" << endl;
                    return false;
                }
            }
            else{
                qDebug() << "lasttype:" << lasttype << endl;
                qDebug() << "presenttype:" << presenttype << endl;
                qDebug() << "type wrong" << endl;
                return false;
            }
            break;
        case 1:
            if(lasttype == 1){
                if(presenttype == 5 || presenttype == 4){
                    return true; 
                }
                if(lastPlayed[0].getRank() < selectedCards[0].getRank()){
                    qDebug() << "two card: rank bigger, true" << endl;
                    return true;
                }
                else if (lastPlayed[0].getRank() == selectedCards[0].getRank()){
                    bool own;
                    for(int i = 0 ; i < 2; i++){
                        if(selectedCards[i].getSuit() == 3){
                            own = true;
                        }
                    }
                    if(own){
                        qDebug() << "two card: suit bigger, true" << endl;
                        return true;
                    }
                    else{
                        qDebug() << "two card: suit smaller, false" << endl;
                        return false;
                    }
                }
                else{
                    qDebug() << "two card: rank smaller, false" << endl;
                    return false;
                }
            }
            else{
                qDebug() << "lasttype:" << lasttype << endl;
                qDebug() << "presenttype:" << presenttype << endl;
                qDebug() << "type wrong" << endl;
                return false;
            }
            break;
        case 2:
            if(lasttype == 2){
                if(presenttype == 5 || presenttype == 4){
                    return true; 
                }
                std::vector<Card> sortedCards = selectedCards; // 创建副本
                std::sort(sortedCards.begin(), sortedCards.end(), [](const Card& card1, const Card& card2) {
                    return card1.getRank() < card2.getRank();
                });
                if(sortedCards[4].getRank() == 12 && sortedCards[3].getRank() == 3){//"23456"
                    if(lastPlayed[4].getRank() == 12 && lastPlayed[3].getRank() == 3){//"23456" & "23456"
                        if(lastPlayed[4].getSuit() < sortedCards[4].getSuit()){
                            qDebug() << "continuous card: suit bigger, true" << endl;
                            return true;
                        }
                        else{
                            qDebug() << "continuous card: suit smaller, false" << endl;
                            return false;
                        }
                    }
                    else {
                        qDebug() << "continuous card: rank bigger, true" << endl;
                        return true;
                    }
                }
                else if(sortedCards[4].getRank() == 12 && sortedCards[3].getRank() == 11){//"A2345"
                    if(lastPlayed[4].getRank() == 12 && lastPlayed[3].getRank() == 11){//"A2345" & "A2345"
                        if(lastPlayed[2].getSuit() < sortedCards[2].getSuit()){
                            qDebug() << "continuous card: suit bigger, true" << endl;
                            return true;
                        }
                        else{
                            qDebug() << "continuous card: suit smaller, false" << endl;
                            return false;
                        }
                    }
                    else {
                        qDebug() << "continuous card: rank smaller, false" << endl;
                        return false;
                    }
                }
                else{
                    if(lastPlayed[4].getRank() == sortedCards[4].getRank()){
                        if(lastPlayed[4].getSuit() < sortedCards[4].getSuit()){
                            qDebug() << "continuous card: suit bigger, true" << endl;
                            return true;
                        }
                        else{
                            qDebug() << "continuous card: suit smaller, false" << endl;
                            return false;
                        }
                    }
                    else if(lastPlayed[4].getRank() < sortedCards[4].getRank()){
                        qDebug() << "continuous card: rank bigger, true" << endl;
                        return true;
                    }
                    else{
                        qDebug() << "continuous card: rank smaller, false" << endl;
                        return false;
                    }
                }
            }
            break;
        case 3:
            if(lasttype == 3){
                if(presenttype == 5 || presenttype == 4){
                    return true; 
                }
                int pastThree;
                int presentThree;
                std::map<Card::Rank, int> rankCount; 
                for (const Card& card : lastPlayed) {
                    rankCount[card.getRank()]++; 
                }
                for (const auto& pair : rankCount) {
                    if (pair.second == 3) {
                        pastThree = pair.first;
                    }
                }
                rankCount.clear();
                for (const Card& card : selectedCards) {
                    rankCount[card.getRank()]++; 
                }
                for (const auto& pair : rankCount) {
                    if (pair.second == 3) {
                        presentThree = pair.first;
                    }
                }
                if(pastThree < presentThree){
                    qDebug() << "continuous card: rank bigger, true" << endl;
                    return true;
                }
                else{
                    qDebug() << "continuous card: rank smaller, false" << endl;
                    return false;
                }
            }
            break;
        case 4:
            if(presenttype == 5){
                    return true; 
                }
            if(lasttype == 5){
                qDebug() << "small type" << endl;
                return false;
            }
            else if (lasttype == 4){
                int pastFour;
                int presentFour;
                std::map<Card::Rank, int> rankCount; 
                for (const Card& card : lastPlayed) {
                    rankCount[card.getRank()]++; 
                }
                for (const auto& pair : rankCount) {
                    if (pair.second == 4) {
                        pastFour = pair.first;
                    }
                }
                rankCount.clear();
                for (const Card& card : selectedCards) {
                    rankCount[card.getRank()]++; 
                }
                for (const auto& pair : rankCount) {
                    if (pair.second == 3) {
                        presentFour = pair.first;
                    }
                }
                if(pastFour < presentFour){
                    qDebug() << "continuous card: rank bigger, true" << endl;
                    return true;
                }
                else{
                    qDebug() << "continuous card: rank smaller, false" << endl;
                    return false;
                }
            }
            else{
                qDebug() << "big type !" << endl;
                return true;
            }
            break;
        case 5:
            if(lasttype == 5){
                std::vector<Card> sortedCards = selectedCards; // 创建副本
                std::sort(sortedCards.begin(), sortedCards.end(), [](const Card& card1, const Card& card2) {
                    return card1.getRank() < card2.getRank();
                });
                if(sortedCards[4].getRank() == 12 && sortedCards[3].getRank() == 3){//"23456"
                    if(lastPlayed[4].getRank() == 12 && lastPlayed[3].getRank() == 3){//"23456" & "23456"
                        if(lastPlayed[4].getSuit() < sortedCards[4].getSuit()){
                            qDebug() << "continuous card: suit bigger, true" << endl;
                            return true;
                        }
                        else{
                            qDebug() << "continuous card: suit smaller, false" << endl;
                            return false;
                        }
                    }
                    else {
                        qDebug() << "continuous card: rank bigger, true" << endl;
                        return true;
                    }
                }
                else if(sortedCards[4].getRank() == 12 && sortedCards[3].getRank() == 11){//"A2345"
                    if(lastPlayed[4].getRank() == 12 && lastPlayed[3].getRank() == 11){//"A2345" & "A2345"
                        if(lastPlayed[2].getSuit() < sortedCards[2].getSuit()){
                            qDebug() << "continuous card: suit bigger, true" << endl;
                            return true;
                        }
                        else{
                            qDebug() << "continuous card: suit smaller, false" << endl;
                            return false;
                        }
                    }
                    else {
                        qDebug() << "continuous card: rank smaller, false" << endl;
                        return false;
                    }
                }
                else{
                    if(lastPlayed[4].getRank() == sortedCards[4].getRank()){
                        if(lastPlayed[4].getSuit() < sortedCards[4].getSuit()){
                            qDebug() << "continuous card: suit bigger, true" << endl;
                            return true;
                        }
                        else{
                            qDebug() << "continuous card: suit smaller, false" << endl;
                            return false;
                        }
                    }
                    else if(lastPlayed[4].getRank() < sortedCards[4].getRank()){
                        qDebug() << "continuous card: rank bigger, true" << endl;
                        return true;
                    }
                    else{
                        qDebug() << "continuous card: rank smaller, false" << endl;
                        return false;
                    }
                }
            }
            else{
                qDebug() << "big type !" << endl;
                return true;
            }
            break;
    }
    qDebug() << "nothing !" << endl;
    return false;
}        

void Mainwindow::reGame()
{
    if(scene)
    {
        scene -> clear();
    }
    setButton();
    pile1.clear();
    pile2.clear();
    pile3.clear();
    pile4.clear();
    itemsToRemove.clear();
    int passPlayerCount = 0;
    bool first = true;
    int roundCount = 0;

    for (int suit = Card::Clubs; suit <= Card::Spades; suit++) {
        for (int rank = Card::Three; rank <= Card::Two; rank++) {
            Card card(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank));
            deck.append(card);
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
    // 找梅花三
    int index = -1;
    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].getSuit() == Card::Clubs && deck[i].getRank() == 0) {
            index = i;
            break;
        }
    }
    if(index != -1)
    {
        deck.push_front(deck.takeAt(index));
    }

    if (numberOfPlayer == 4)
    {
        pile1 = deck.mid(0, 13);
        pile2 = deck.mid(13, 13);
        pile3 = deck.mid(26, 13);
        pile4 = deck.mid(39, 13);
    }
    else if (numberOfPlayer == 3)
    {
        pile1 = deck.mid(0, 17);
        pile2 = deck.mid(17, 17);
        pile3 = deck.mid(34, 0);
        pile4 = deck.mid(34, 17);
    }
    else if (numberOfPlayer == 2)
    {
        pile1 = deck.mid(0, 26);
        pile2 = deck.mid(26, 0);
        pile3 = deck.mid(26, 26);
        pile4 = deck.mid(52, 0);
    }

    std::vector<Card> stdPile1;
    stdPile1.reserve(pile1.size());
    for (const Card& card : pile1) {
        stdPile1.push_back(card);
    }
 
    std::vector<Card> stdPile2;
    stdPile2.reserve(pile2.size());
    for (const Card& card : pile2) {
        stdPile2.push_back(card);
    }
 
    std::vector<Card> stdPile3;
    stdPile3.reserve(pile3.size());
    for (const Card& card : pile3) {
        stdPile3.push_back(card);
    }
 
    std::vector<Card> stdPile4;
    stdPile4.reserve(pile4.size());
    for (const Card& card : pile4) {
        stdPile4.push_back(card);
    }

    player1->setHand(stdPile1);
    player2->setHand(stdPile2);
    player3->setHand(stdPile3);
    player4->setHand(stdPile4);

    updateVisible();
    updateCards();
    drawAvatarAndScore();
}

void Mainwindow::pass()
{
    QGraphicsPixmapItem *passImage = new QGraphicsPixmapItem();
    QPixmap passPixmap = QPixmap("./dataset/images/pass.png");
    passImage->setPixmap(passPixmap);
    passImage->setPos(150, 300);
    scene->addItem(passImage);
    QSound::play("./dataset/sounds/pass.wav");

    QTimer *timer = new QTimer(this);
    timer->setInterval(400);
    // 连接定时器的 timeout 信号到槽函数
    connect(timer, &QTimer::timeout, this, [=]() {
        timer->stop();
        scene->removeItem(passImage);
    });
    timer->start();

    passPlayerCount++;
    switch (numberOfPlayer)
    {
    case 2:
        if (passPlayerCount == 1) {
            passPlayerCount = 0;
            lastPlayed.clear();
            qDebug()<<"free";
        }
        else if (passPlayerCount == 2) {
            passPlayerCount = 0;
        }
        break;
    case 3:
        if (passPlayerCount == 2) {
            passPlayerCount = 0;
            lastPlayed.clear();
            qDebug()<<"free";
        }
        else if (passPlayerCount == 3) {
            passPlayerCount = 0;
        }
        break;
    case 4:
        if (passPlayerCount == 3) {
            passPlayerCount = 0;
            lastPlayed.clear();
            qDebug()<<"free";
        }
        else if (passPlayerCount == 4) {
            passPlayerCount = 0;
        }
        break;
    default:
        break;
    }
    for (int i = 0; i<lastPlayed.size(); i++)
        addRemoveCardToScene(lastPlayed[i], 500 + i*110, 350);
}

void Mainwindow::addRemoveCardToScene(const Card& card, int x, int y) 
{
    int imageIndex = getCardImageIndex(card);   
    // 检查图像索引是否有效
    if (imageIndex >= 0 && imageIndex < 52) {
        QGraphicsPixmapItem* cardPixmapItem = new QGraphicsPixmapItem(*img[imageIndex]);
        cardPixmapItem->setScale(0.2);
        cardPixmapItem->setPos(x, y);
        cardPixmapItem->setZValue(300);
        scene->addItem(cardPixmapItem);
        itemsToRemove.append(cardPixmapItem);
    } else {
        qDebug() << "Invalid image index: " << imageIndex;
    }
}

void Mainwindow::showScore()
{
    if (scene)
    {
        scene->clear();
    }
    for (int i = 0; i < players.size(); i++) {
        Player* theplayer = players[i];
        QGraphicsPixmapItem* listavatarItem = new QGraphicsPixmapItem(theplayer->avatar);
        listavatarItem->setScale(1);
        listavatarItem->setPos(250 + 400*i, 300);
        listavatarItem->setZValue(10);
        scene->addItem(listavatarItem);
        listitemsToRemove.append(listavatarItem);

        QGraphicsTextItem* listscoreText = new QGraphicsTextItem;
        listscoreText->setPlainText("Score: " + QString::number(theplayer->getScore()));
        listscoreText->setDefaultTextColor(Qt::white);
        listscoreText->setFont(QFont("Arial", 20));
        listscoreText->setPos(250 + 400*i, 700);
        scene->addItem(listscoreText);
        listitemsToRemove.append(listscoreText);
        
        QGraphicsTextItem* listnameText = new QGraphicsTextItem;
        listnameText->setPlainText(theplayer->getName());
        listnameText->setDefaultTextColor(Qt::white);
        listnameText->setFont(QFont("Arial", 20));
        listnameText->setPos(250 + 400*i, 600);
        scene->addItem(listnameText);
        listitemsToRemove.append(listnameText);
    }
    QTimer *timer = new QTimer(this);
    timer->setInterval(5000);
    // 连接定时器的 timeout 信号到槽函数
    connect(timer, &QTimer::timeout, this, [=]() {
        timer->stop();
        for (QGraphicsItem* item : listitemsToRemove) {
            scene->removeItem(item);
            delete item;
        }
        listitemsToRemove.clear();
        reGame();
    });
    timer->start();
}

void Mainwindow::recommandCard(){
    Card card; // initialize with actual values
    QPixmap pixmap; // initialize with actual values
    CardItem* newCardItem = new CardItem(this, pixmap, card);

    manycards.push_back(newCardItem);
    manycards.pop_back();
    std::vector<CardItem> com;
    std::vector<Card> com_copy;

    std::sort(manycards.begin(), manycards.end(),[](const CardItem* a, const CardItem* b) {
        return a->getCard().getRank() < b->getCard().getRank();
    });
    
    std::map<Card::Rank, int> rankCount; 
    for (int i = 0; i < manycards.size(); i++) {
        rankCount[manycards[i]->card.getRank()]++; 
    }
    qDebug()<<"many"<<manycards.size();
    switch(lasttype){
        case 0:
            for(int i = manycards.size() - 1; i >= 0 ; i--){
                com_copy.clear();
                com_copy.push_back(manycards[i]->getCard());
                if(isPutValid(com_copy, lastPlayed)){
                    qDebug() <<"in"<<endl;
                    manycards[i]->setupCardItem(); //修改位置
                    clickedCards.push_back(manycards[i]);
                    break;
                }
            }
        break;
        case 1:
            for(int i = manycards.size() - 1; i >= 0 ; i--){
                qDebug() << i ;
                com_copy.clear();
                com_copy.push_back(manycards[i]->getCard());
                com_copy.push_back(manycards[i - 1]->getCard());
                if(isPutValid(com_copy, lastPlayed)&&isSelectionValid(com_copy)){
                    qDebug() <<"in"<<endl;
                    manycards[i]->setupCardItem();
                    manycards[i - 1]->setupCardItem();
                    clickedCards.push_back(manycards[i]);
                    clickedCards.push_back(manycards[i - 1]);
                    break;
                }
            }
            break;
        case 2:
        {
            bool found = false; // Add this flag
            //A2345 23456
            for(int i = 7; i < manycards.size(); i++){
                if(manycards[i]->getCard().getRank() == 12){
                    if(i != manycards.size() - 1){
                        for(int j = 0;  j< manycards.size(); j++){
                            if(manycards[j]->getCard().getRank() == 0){
                                for(int k = 0; k < 7; k++){
                                    if(manycards[k]->getCard().getRank() == 1){
                                        for(int l = 0; l < 10; l++){
                                            if(manycards[l]->getCard().getRank() == 2){
                                                for(int m = 0; m < 12; m++){
                                                    if(manycards[m]->getCard().getRank() == 3){
                                                        com_copy.clear();
                                                        com_copy.push_back(manycards[i]->getCard());
                                                        com_copy.push_back(manycards[j]->getCard());
                                                        com_copy.push_back(manycards[k]->getCard());
                                                        com_copy.push_back(manycards[l]->getCard());
                                                        com_copy.push_back(manycards[m]->getCard());
                                                        if(isPutValid(com_copy, lastPlayed)&&isSelectionValid(com_copy)){
                                                            manycards[i]->setupCardItem();
                                                            clickedCards.push_back(manycards[i]);
                                                            manycards[j]->setupCardItem();
                                                            clickedCards.push_back(manycards[j]);
                                                            manycards[k]->setupCardItem();
                                                            clickedCards.push_back(manycards[k]);
                                                            manycards[l]->setupCardItem();
                                                            clickedCards.push_back(manycards[l]);
                                                            manycards[m]->setupCardItem();
                                                            clickedCards.push_back(manycards[m]);
                                                            found = true; // Set flag to true
                                                            break;
                                                        }
                                                    }
                                                    else if(manycards[m]->getCard().getRank() - manycards[l]->getCard().getRank() > 1 || found){
                                                        break;
                                                    }
                                                }
                                                if(found) break; // Check flag
                                            }
                                            else if(manycards[l]->getCard().getRank() - manycards[k]->getCard().getRank() > 1 || found){
                                                break;
                                            }
                                        }
                                        if(found) break; // Check flag
                                    }
                                    else if(manycards[k]->getCard().getRank() - manycards[j]->getCard().getRank() > 1 ||found){
                                        break;
                                    }
                                }
                                if(found) break; // Check flag
                            }
                            else if(found){
                                break;
                            }
                        }
                        if(found) break; // Check flag
                    }
                }
            }

            if(!found){
                for (int i = manycards.size() - 1; i >= 4; --i) {
                    for (int j = i - 1; j >= 3; --j) {
                        if (manycards[i]->getCard().getRank() - manycards[j]->getCard().getRank() == 1) {
                            for (int k = j - 1; k >= 2; --k) {
                                if (manycards[j]->getCard().getRank() - manycards[k]->getCard().getRank() == 1) {
                                    for (int l = k - 1; l >= 1; --l) {
                                        if (manycards[k]->getCard().getRank() - manycards[l]->getCard().getRank() == 1) {
                                            for (int m = l - 1; m >= 0; --m) {
                                                if (manycards[l]->getCard().getRank() - manycards[m]->getCard().getRank() == 1) {
                                                    com_copy.clear();
                                                    com_copy.push_back(manycards[i]->getCard());
                                                    com_copy.push_back(manycards[j]->getCard());
                                                    com_copy.push_back(manycards[k]->getCard());
                                                    com_copy.push_back(manycards[l]->getCard());
                                                    com_copy.push_back(manycards[m]->getCard());
                                                    if (isPutValid(com_copy, lastPlayed) && isSelectionValid(com_copy)) {
                                                        manycards[i]->setupCardItem();
                                                        clickedCards.push_back(manycards[i]);
                                                        manycards[j]->setupCardItem();
                                                        clickedCards.push_back(manycards[j]);
                                                        manycards[k]->setupCardItem();
                                                        clickedCards.push_back(manycards[k]);
                                                        manycards[l]->setupCardItem();
                                                        clickedCards.push_back(manycards[l]);
                                                        manycards[m]->setupCardItem();
                                                        clickedCards.push_back(manycards[m]);
                                                        found = true; 
                                                        break;
                                                    }
                                                }
                                            }
                                            if (found) break;
                                        }
                                    }
                                    if (found) break;
                                }
                            }
                            if (found) break;
                        }
                    }
                    if (found) break;
                }
            }
            if(!found){
                for(int i = 7; i < manycards.size(); i++){
                    if(manycards[i]->getCard().getRank() == 11){
                        if(i != manycards.size() - 1){
                            for(int j = i + 1;  j< manycards.size(); j++){
                                if(manycards[j]->getCard().getRank() == 12){
                                    for(int k = 0; k < 4; k++){
                                        if(manycards[k]->getCard().getRank() == 0){
                                            for(int l = 0; l < 8; l++){
                                                if(manycards[l]->getCard().getRank() == 1){
                                                    for(int m = 0; m < 10; m++){
                                                        if(manycards[m]->getCard().getRank() == 2){
                                                            com_copy.clear();
                                                            com_copy.push_back(manycards[i]->getCard());
                                                            com_copy.push_back(manycards[j]->getCard());
                                                            com_copy.push_back(manycards[k]->getCard());
                                                            com_copy.push_back(manycards[l]->getCard());
                                                            com_copy.push_back(manycards[m]->getCard());
                                                            if(isPutValid(com_copy, lastPlayed)&&isSelectionValid(com_copy)){
                                                                manycards[i]->setupCardItem();
                                                                clickedCards.push_back(manycards[i]);
                                                                manycards[j]->setupCardItem();
                                                                clickedCards.push_back(manycards[j]);
                                                                manycards[k]->setupCardItem();
                                                                clickedCards.push_back(manycards[k]);
                                                                manycards[l]->setupCardItem();
                                                                clickedCards.push_back(manycards[l]);
                                                                manycards[m]->setupCardItem();
                                                                clickedCards.push_back(manycards[m]);
                                                                found = true; // Set flag to true
                                                                break;
                                                            }
                                                        }
                                                        else if(manycards[m]->getCard().getRank() - manycards[l]->getCard().getRank() > 1 || found){
                                                            break;
                                                        }
                                                    }
                                                    if(found) break; // Check flag
                                                }
                                                else if(manycards[l]->getCard().getRank() - manycards[k]->getCard().getRank() > 1 || found){
                                                    break;
                                                }
                                            }
                                            if(found) break; // Check flag
                                        }
                                        else if(found){
                                            break;
                                        }
                                    }
                                    if(found) break; // Check flag
                                }
                                else if(manycards[j]->getCard().getRank() - manycards[i]->getCard().getRank() > 1 || found){
                                    break;
                                }
                            }
                            if(found) break; // Check flag
                        }
                    }
                }
            }
            
            break;
        }
        case 3:
        {
            int hasThreeOfAKind = -1;
            int hasPair = -1;
            for (const auto& pair : rankCount) {
                if (pair.second == 3) {
                    hasThreeOfAKind = pair.first;
                } 
                else if (pair.second == 2) {
                    hasPair = pair.first;
                }
            }
            int count = 0;
            for(const auto& pair : rankCount){
                if(pair.first < hasThreeOfAKind){
                    count += pair.second;
                }
                
            }
            int count2 = 0;
            for(const auto& pair : rankCount){
                if(pair.first < hasPair){
                    count2 += pair.second;
                }
                
            }
            if (hasThreeOfAKind != -1 && hasPair != -1) {
                com_copy.clear();
                com_copy.push_back(manycards[count]->getCard());
                com_copy.push_back(manycards[count + 1]->getCard());
                com_copy.push_back(manycards[count + 2]->getCard());
                com_copy.push_back(manycards[count2]->getCard());
                com_copy.push_back(manycards[count2 + 1]->getCard());
                if(isPutValid(com_copy, lastPlayed)&&isSelectionValid(com_copy)){
                    manycards[count]->setupCardItem();
                    clickedCards.push_back(manycards[count]);
                    manycards[count + 1]->setupCardItem();
                    clickedCards.push_back(manycards[count + 1]);
                    manycards[count + 2]->setupCardItem();
                    clickedCards.push_back(manycards[count + 2]);
                    manycards[count2]->setupCardItem();
                    clickedCards.push_back(manycards[count2]);
                    manycards[count2 + 1]->setupCardItem();
                    clickedCards.push_back(manycards[count2 + 1]);
                }
            }
            break;
        }     
    }
}
