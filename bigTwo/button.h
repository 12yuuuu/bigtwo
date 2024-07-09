#ifndef BUTTON_H
#define BUTTON_H

#include "mainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>
 
class Button: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // constructors
    Button(const char * = "", const char * = "", int = 300, int = 150, QGraphicsItem * parent = NULL);
    // public methods (events)
    QPixmap imgs[2];
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
signals:
    void clicked();
};
 
#endif // BUTTON_H