#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // constructors
    Button(QString name, QGraphicsItem* parent=NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QGraphicsTextItem* getText() {return text;};
    int getIndex() {return _index;};
    void setIndex(int i) {_index = i;};
    std::string get_text() {return text->toPlainText().toStdString();};
signals:
    void clicked();
private:
    QGraphicsTextItem* text;
    int _index;
};

#endif // BUTTON_H
