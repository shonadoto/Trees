#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"
#include "QGraphicsView"
#include <mygraphicview.h>
#include "avl.h"
#include "kurevo.h"
#include "rbtree.h"
#include "splay.h"
#include "queue"
#include "map"
#include "QEvent"

extern bool is_synchronized;
extern Avl::Avl *AvlTree;
extern Rb::RBTree *RBTree;
extern Kurevo::kurevo *KurevoTree;
extern Splay::SplayTree * SplayTree;
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  void update_trees();
  ~MainWindow();

public slots:
  void upd();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  //void on_pushButton_4_clicked();

  void on_insertButton_clicked();

  void on_synchronizeBox_stateChanged(int arg1);

  void on_autoZoomBox_stateChanged(int arg1);

  void on_randBUtton_clicked();

  void on_deleteButton_clicked();


private:
  Ui::MainWindow  *ui;
  QTimer *timer;
  MyGraphicView *AvlView, *RBView, *KurevoView, *SplayView;
  double scale, dist_mult;
  int avl_scale, rb_scale, kurevo_scale, splay_scale;
  int vert_w, vert_h, vert_dist_x, vert_dist_y;
  void init_trees();
  void enable_autozoom();
  std::vector<int> draw_avl(Avl::Avl* Tree, int x_dif, int y_dif);
  std::vector<int> draw_rb(Rb::RBTree* Tree, int x_dif, int y_dif);
  std::vector<int> draw_kurevo(Kurevo::kurevo* Tree, int x_dif, int y_dif);
  std::vector<int> draw_splay(Splay::SplayTree* Tree, int x_dif, int y_dif);
};


extern MainWindow *wnd;
#endif // MAINWINDOW_H
