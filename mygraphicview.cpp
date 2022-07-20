#include "mygraphicview.h"
#include "myelipseitem.h"
MyGraphicView::MyGraphicView(QWidget *parent)
    : QGraphicsView(parent)
{

    this->setAlignment(Qt::AlignTop);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    QPen penBlack(Qt::black);
    QBrush brushRed(Qt::red);

    scene = new QGraphicsScene();
    this->setScene(scene);
}

MyGraphicView::~MyGraphicView()
{

}

void MyGraphicView::Clear() {
  for (QGraphicsItem* it: scene->items()) {
      delete(it);
    }
}

void MyGraphicView::addVertex(int x, int y, int x_l, int y_l, int x_r, int y_r, QColor bordCol, QColor fillCol, int w, int h, int data, int tree_type) {
  MyElipseItem* elipse = new MyElipseItem(x, y, x_l, y_l, x_r, y_r, w, h, QPen(bordCol), QBrush(fillCol), data, tree_type);
  scene->addItem(elipse->line_r);
  scene->addItem(elipse->line_l);
  scene->addItem(elipse);
  scene->addItem(elipse->txt);
  return;
}

