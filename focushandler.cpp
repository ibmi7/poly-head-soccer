#include "focushandler.h"


FocusHandler::FocusHandler()
{

}

void FocusHandler::keyPressEvent(QKeyEvent *event)
{
    if (!liste.empty()){
        for (auto i : liste){
            if (i->getLeft() == event->key() || i->getUp() == event->key() || i->getRight() == event->key() || i->getDown() == event->key() ){
                i->keyPressEvent(event->key());
            }
        }
    }
}
