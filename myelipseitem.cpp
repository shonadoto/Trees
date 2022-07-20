#include "myelipseitem.h"
#include "QDebug"

MyElipseItem::MyElipseItem(int x, int y, int x_l, int y_l, int x_r, int y_r, int w, int h, QPen pen, QBrush brush, int data, int tree_type)
{
  this->data = data;
  this->tree_type = tree_type;
  this->setRect(x, y, w, h);
  this->setPen(pen);
  this->setBrush(brush);
  QFont fnt=QFont("Arial", 11, QFont::Bold);
  txt = new QGraphicsTextItem(QString::number(data));
  txt->setFont(fnt);
  txt->setPos(x, y + 40);
  txt->setDefaultTextColor(QColor(255,255,255));
  txt->setTextWidth(w);
  QTextBlockFormat format;
  format.setAlignment(Qt::AlignCenter);
  QTextCursor cursor = txt->textCursor();
  cursor.select(QTextCursor::Document);
  cursor.mergeBlockFormat(format);
  cursor.clearSelection();
  txt->setTextCursor(cursor);
  line_l = new QGraphicsLineItem(x + w / 2, y + h / 2, x_l, y_l);
  line_r = new QGraphicsLineItem(x + w / 2, y + h / 2, x_r, y_r);
  line_l->setPen(QPen(Qt::black));
  line_r->setPen(QPen(Qt::black));
  line_l->setZValue(-1);
  line_r->setZValue(-1);
}

void MyElipseItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
  if (is_synchronized) {
      Avl::delete_elem(AvlTree, this->data);
      Rb::del(RBTree, this->data);
      Kurevo::Delete(KurevoTree, this->data);
      Splay::del(SplayTree, this->data);
      delete(this->line_l);
      delete(this->line_r);
      delete(this->txt);
      delete(this);
      wnd->update_trees();
      return;
    }
  if (this->tree_type == 0)
    Avl::delete_elem(AvlTree, this->data);
  if (this->tree_type == 1)
    Rb::del(RBTree, this->data);
  if (this->tree_type == 2)
    Kurevo::Delete(KurevoTree, this->data);
  if (this->tree_type == 3)
    Splay::del(SplayTree, this->data);
  delete(this->line_l);
  delete(this->line_r);
  delete(this->txt);
  delete(this);
  wnd->update_trees();
  return;
}
