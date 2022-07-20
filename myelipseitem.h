#ifndef MYELIPSEITEM_H
#define MYELIPSEITEM_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QTextCursor>
#include "mygraphicview.h"
#include "mainwindow.h"
#include "avl.h"
#include "kurevo.h"
#include "rbtree.h"

class MyElipseItem : public QGraphicsEllipseItem
{
public:
  MyElipseItem(int x, int y, int x_l, int y_l, int x_r, int y_r, int w, int h, QPen pen, QBrush brush, int data, int tree_type);
  int data;
  int tree_type;
  QGraphicsTextItem *txt;
  QGraphicsLineItem *line_l, *line_r;
private:
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYELIPSEITEM_H
