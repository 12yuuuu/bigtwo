#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <card.h>
#include "mainwindow.h"
class Mainwindow;
class Card;

class CardItem : public QGraphicsPixmapItem
{
public:
    CardItem(Mainwindow* window, const QPixmap &pixmap, Card card);
    const Card getCard() const { return card; }
    void setCardItem();
    void setupCardItem();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    bool isRaised = false;
    Mainwindow* parentWindow;
    Card card;
};

#endif // CARDITEM_H

