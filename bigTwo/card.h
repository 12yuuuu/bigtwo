#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QMap>
#include <QList>
#include <QGraphicsSceneHoverEvent>
#include <algorithm>
#include <QGraphicsItem>
#include <random>
#include <Qimage>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QObject>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>

class Card {
public:
    enum Suit {
        Clubs = 0, Diamonds, Hearts, Spades
    };
    enum Rank {
        Three = 0, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace, Two
    };
    Card();
    Card(Suit suit, Rank rank);
    Suit getSuit() const;
    Rank getRank() const;
    QString getSuitString() const;
    QString getRankString() const;
    bool operator==(const Card other) const {
        // Replace with your own logic
        return this->card_rank == other.card_rank && this->card_suit == other.card_suit;
    }
    Suit card_suit; //花色
    Rank card_rank; //數字
    static const QMap<Suit, QString> suitMap;
    static const QMap<Rank, QString> rankMap;
};

#endif // CARD_H