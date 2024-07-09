#include "carditem.h"
#include <QDebug>

CardItem::CardItem(Mainwindow* window, const QPixmap &pixmap, Card card) 
: QGraphicsPixmapItem(pixmap), parentWindow(window), card(card)
{
    setAcceptHoverEvents(true);
}

void CardItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isRaised) {
        setPos(pos().x(), 570); // 将卡片的y坐标减少30
    }
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

void CardItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isRaised) {
        setPos(pos().x(), 620); // 恢复卡片的y坐标
    }
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}

void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (parentWindow) {
            if (!isRaised && parentWindow->getClickedCardsCount() < 5) {
                isRaised = true;
                parentWindow->addClickedCard(this);
            } else if (isRaised) {
                isRaised = false;
                setPos(pos().x(), 620);
                parentWindow->removeClickedCard(this);
            }
            event->accept(); // 阻止事件的进一步传播
        }
    }
    // 只有当事件没有被接受时，才会调用基类的处理函数
    if (!event->isAccepted())
        QGraphicsPixmapItem::mousePressEvent(event);
}

void CardItem::setCardItem()
{
    isRaised = false;
    setPos(pos().x(), 620);
}

void CardItem::setupCardItem()
{
    isRaised = true;
    setPos(pos().x(), 570);
}





