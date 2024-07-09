#include "Button.h"

Button::Button(const char * img1, const char * img2, int newWidth, int newHeight, QGraphicsItem *)
{
    imgs[0].load(img1);
    imgs[1].load(img2);
    imgs[0] = imgs[0].scaled(newWidth, newHeight, Qt::KeepAspectRatio);
    imgs[1] = imgs[1].scaled(newWidth, newHeight, Qt::KeepAspectRatio);

    setPixmap(imgs[0]);
    // allow to detect mouse hover
    setAcceptHoverEvents(true);
}
 
void Button::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    setPixmap(imgs[1]);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    setPixmap(imgs[0]);
}