#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include "QGraphicsSceneWheelEvent"
#include "avl.h"
#include "kurevo.h"
#include "rbtree.h"

class MyGraphicView : public QGraphicsView
{
  Q_OBJECT
public:
  explicit MyGraphicView(QWidget *parent = 0);
  void addVertex(int x, int y, int x_l, int y_l, int x_r, int y_r, QColor bordCol, QColor fillCol, int w, int h, int data, int tree_type);
  void addLine(int x1, int y1, int x2, int y2);
  void Clear();
  QGraphicsScene      *scene;
  ~MyGraphicView();


private:

};

#endif // MYGRAPHICVIEW_H
