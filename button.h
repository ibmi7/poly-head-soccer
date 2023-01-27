/**
 * @file button.h
 * @brief The Button class
 * @version 1.0
 * @date 2023-01-27
 * @author Ibrahim Minthe & Youssef Skhiri
 * @version 1.0
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la classe Button
     * @param name Le nom du bouton
    */
    Button(QString name, QGraphicsItem* parent=NULL);
    /**
     * @brief mousePressEvent
     * @param event
     * @details Cette méthode permet de détecter le clic sur le bouton
    */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief hoverEnterEvent
     * @param event
     * @details Cette méthode permet de détecter le survol du bouton
    */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    /**
     * @brief hoverLeaveEvent
     * @param event
     * @details Cette méthode permet de détecter la sortie du survol du bouton
    */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QGraphicsTextItem* getText() {return text;};
    int getIndex() {return _index;};
    void setIndex(int i) {_index = i;};
    std::string get_text() {return text->toPlainText().toStdString();};
signals:
    /**
     * @brief clicked
     * @details Cette méthode permet de détecter le clic sur le bouton
    */
    void clicked();
private:
    QGraphicsTextItem* text;
    int _index;
};

#endif // BUTTON_H
