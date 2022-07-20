#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
struct node{
  int data, x, y, dist, par_x, par_y;
public:
  node (int data, int x, int y, int dist, int par_x, int par_y) {
    this->data = data;
    this->x = x;
    this->y = y;
    this->dist = dist;
    this->par_x = par_x;
    this->par_y = par_y;
  }
};

int upd_cnt = 0;
bool is_synchronized;
Avl::Avl *AvlTree;
Rb::RBTree *RBTree;
Kurevo::kurevo *KurevoTree;
Splay::SplayTree *SplayTree;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  AvlView = new MyGraphicView;
  RBView = new MyGraphicView;
  KurevoView = new MyGraphicView;
  SplayView = new MyGraphicView;

  ui->avlLayout->addWidget(AvlView);
  ui->rbLayout->addWidget(RBView);
  ui->kurevoLayout->addWidget(KurevoView);
  ui->splayLayout->addWidget(SplayView);

  AvlTree = NULL;
  RBTree = NULL;
  KurevoTree = NULL;
  SplayTree = NULL;
  scale = 1.1;
  dist_mult = 2;
  avl_scale = -1;
  rb_scale = -1;
  kurevo_scale = -1;
  splay_scale = -1;
  vert_w = 100;
  vert_h = 100;
  vert_dist_x = 200;
  vert_dist_y = 300;
  init_trees();
  update_trees();
  /*timer = new QTimer(this);
  timer->setInterval(10);
  timer->setSingleShot(false);
  connect(timer, SIGNAL(timeout()), this, SLOT(upd()));
  timer->start();*/
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::upd() {
  update_trees();
}

void MainWindow::on_pushButton_clicked()
{
  if (ui->tabWidget->currentIndex() == 0) {
      AvlView->scale(scale, scale);
      avl_scale += 1;
    }
  if (ui->tabWidget->currentIndex() == 1) {
      rb_scale += 1;
      RBView->scale(scale, scale);
    }
  if (ui->tabWidget->currentIndex() == 2) {
      KurevoView->scale(scale, scale);
      kurevo_scale += 1;
    }
  if (ui->tabWidget->currentIndex() == 3) {
      SplayView->scale(scale, scale);
      splay_scale += 1;
    }
  return;
}

void MainWindow::on_pushButton_2_clicked()
{
  scale = 1 / scale;
  if (ui->tabWidget->currentIndex() == 0) {
      AvlView->scale(scale, scale);
      avl_scale -= 1;
    }
  if (ui->tabWidget->currentIndex() == 1) {
      rb_scale -= 1;
      RBView->scale(scale, scale);
    }
  if (ui->tabWidget->currentIndex() == 2) {
      KurevoView->scale(scale, scale);
      kurevo_scale -= 1;
    }
  if (ui->tabWidget->currentIndex() == 3) {
      SplayView->scale(scale, scale);
      splay_scale -= 1;
    }
  scale = 1 / scale;
  return;
}


void MainWindow::on_pushButton_3_clicked()
{
  AvlView->Clear();
  RBView->Clear();
  KurevoView->Clear();
  SplayView->Clear();
  while (AvlTree)
    Avl::delete_elem(AvlTree, AvlTree->data);
  while (RBTree)
    Rb::del(RBTree, RBTree->data);
  while (KurevoTree)
    Kurevo::Delete(KurevoTree, KurevoTree->key);
  while (SplayTree)
    Splay::del(SplayTree, SplayTree->data);
  update_trees();
}


/*void MainWindow::on_pushButton_4_clicked()
{
  int x = ui->x->text().toInt();
  int y = ui->y->text().toInt();
  int data = ui->data->text().toInt();
  if (ui->synchronizeBox->isChecked()) {
      AvlView->addVertex(x, y, data, Qt::red);
      RBView->addVertex(x, y, data, Qt::red);
      KurevoView->addVertex(x, y, data, Qt::red);
      SplayView->addVertex(x, y, data, Qt::red);
      Avl::insert(this->AvlTree, data);
      Rb::insert(this->RBTree, data);
      Kurevo::Insert(this->KurevoTree, data);
    }
  if (ui->comboBox->currentText() == "Avl") {
      AvlView->addVertex(x, y, data, Qt::red);
      return;
    }
  if (ui->comboBox->currentText() == "Rb") {
      RBView->addVertex(x, y, data, Qt::red);
      return;
    }
  if (ui->comboBox->currentText() == "Kurevo") {
      KurevoView->addVertex(x, y, data, Qt::red);
      return;
    }
  if (ui->comboBox->currentText() == "Splay") {
      SplayView->addVertex(x, y, data, Qt::red);
      return;
    }
}*/

void MainWindow::init_trees() {
  AvlTree = NULL;
  RBTree = NULL;
  KurevoTree = NULL;
  SplayTree = NULL;
  is_synchronized = 0;
}

void MainWindow::update_trees() {
  qDebug() << "Update: " << upd_cnt++ << '\n';
  AvlView->Clear();
  RBView->Clear();
  KurevoView->Clear();
  SplayView->Clear();
  is_synchronized = ui->synchronizeBox->isChecked();
  draw_avl(AvlTree, 0, 0);
  draw_rb(RBTree, 0, 0);
  draw_kurevo(KurevoTree, 0, 0);
  draw_splay(SplayTree, 0, 0);
  if (ui->autoZoomBox->isChecked())
    enable_autozoom();
}

std::vector<int> MainWindow::draw_avl(Avl::Avl *Tree, int x_dif = 0, int y_dif = 0) {
  if (!Tree) {
      return std::vector<int>(5, 1);
    }

  std::vector<int> left = draw_avl(Tree->left, x_dif, y_dif + vert_dist_y);
  std::vector<int> right = draw_avl(Tree->right, x_dif + left[1] - left[0] + vert_w, y_dif + vert_dist_y);
  if (left[4] && right[4]) {
      AvlView->addVertex(x_dif, y_dif, x_dif + vert_w / 2, y_dif + vert_h / 2, x_dif + vert_w / 2, y_dif + vert_h / 2, Qt::black, Qt::black, vert_w, vert_h, Tree->data, 0);
      return {x_dif , x_dif + vert_w, x_dif + vert_w / 2, y_dif + vert_h / 2, 0};
    } else if (left[4]) {
      AvlView->addVertex(x_dif, y_dif, x_dif + vert_w / 2, y_dif + vert_h / 2, right[2], right[3], Qt::black, Qt::black, vert_w, vert_h, Tree->data, 0);
      return {x_dif, right[1], x_dif + vert_w / 2, y_dif + vert_h / 2, 0};
    } else if (right[4]) {
      AvlView->addVertex(left[1], y_dif, left[2], left[3], left[1] + vert_w / 2, y_dif + vert_h / 2, Qt::black, Qt::black, vert_w, vert_h, Tree->data, 0);
      return {left[0], left[1] + vert_w, left[1] + vert_w / 2, y_dif + vert_h / 2, 0};
    } else {
      AvlView->addVertex(left[1], y_dif, left[2], left[3], right[2], right[3], Qt::black, Qt::black, vert_w, vert_h, Tree->data, 0);
      return {left[0], right[1], left[1] + vert_w / 2, y_dif + vert_h / 2, 0};
    }
}


std::vector<int> MainWindow::draw_rb(Rb::RBTree *Tree, int x_dif = 0, int y_dif = 0) {
  if (!Tree) {
      return std::vector<int>(5, 1);
    }

  std::vector<int> left = draw_rb(Tree->left, x_dif, y_dif + vert_dist_y);
  std::vector<int> right = draw_rb(Tree->right, x_dif + left[1] - left[0] + vert_w, y_dif + vert_dist_y);
  if (left[4] && right[4]) {
      RBView->addVertex(x_dif, y_dif, x_dif + vert_w / 2, y_dif + vert_h / 2, x_dif + vert_w / 2, y_dif + vert_h / 2, Qt::black, (Tree->color ? Qt::red : Qt::black), vert_w, vert_h, Tree->data, 1);
      return {x_dif , x_dif + vert_w, x_dif + vert_w / 2, y_dif + vert_h / 2, 0};
    } else if (left[4]) {
      RBView->addVertex(x_dif, y_dif, x_dif + vert_w / 2, y_dif + vert_h / 2, right[2], right[3], Qt::black, (Tree->color ? Qt::red : Qt::black), vert_w, vert_h, Tree->data, 1);
      return {x_dif, right[1], x_dif + vert_w / 2, y_dif + vert_h / 2, 0};
    } else if (right[4]) {
      RBView->addVertex(left[1], y_dif, left[2], left[3], left[1] + vert_w / 2, y_dif + vert_h / 2, Qt::black, (Tree->color ? Qt::red : Qt::black), vert_w, vert_h, Tree->data, 1);
      return {left[0], left[1] + vert_w, left[1] + vert_w / 2, y_dif + vert_h / 2, 0};
    } else {
      RBView->addVertex(left[1], y_dif, left[2], left[3], right[2], right[3], Qt::black, (Tree->color ? Qt::red : Qt::black), vert_w, vert_h, Tree->data, 1);
      return {left[0], right[1], left[1] + vert_w / 2, y_dif + vert_h / 2, 0};
    }
}

std::vector<int> MainWindow::draw_kurevo(Kurevo::kurevo *Tree, int x_dif = 0, int y_dif = 0) {
  if (!Tree) {
      return std::vector<int>(5, 1);
    }

  std::vector<int> left = draw_kurevo(Tree->left, x_dif, y_dif + vert_dist_y);
  std::vector<int> right = draw_kurevo(Tree->right, x_dif + left[1] - left[0] + vert_w, y_dif + vert_dist_y);
  if (left[4] && right[4]) {
      KurevoView->addVertex(x_dif, y_dif, x_dif + vert_w / 2, y_dif + vert_h / 2, x_dif + vert_w / 2, y_dif + vert_h / 2, Qt::black, Qt::black, vert_w, vert_h, Tree->key, 2);
      return {x_dif , x_dif + vert_w, x_dif + vert_w / 2, y_dif + vert_h / 2, 0};
    } else if (left[4]) {
      KurevoView->addVertex(x_dif, y_dif, x_dif + vert_w / 2, y_dif + vert_h / 2, right[2], right[3], Qt::black, Qt::black, vert_w, vert_h, Tree->key, 2);
      return {x_dif, right[1], x_dif + vert_w / 2, y_dif + vert_h / 2, 0};
    } else if (right[4]) {
      KurevoView->addVertex(left[1], y_dif, left[2], left[3], left[1] + vert_w / 2, y_dif + vert_h / 2, Qt::black, Qt::black, vert_w, vert_h, Tree->key, 2);
      return {left[0], left[1] + vert_w, left[1] + vert_w / 2, y_dif + vert_h / 2, 0};
    } else {
      KurevoView->addVertex(left[1], y_dif, left[2], left[3], right[2], right[3], Qt::black, Qt::black, vert_w, vert_h, Tree->key, 2);
      return {left[0], right[1], left[1] + vert_w / 2, y_dif + vert_h / 2, 0};
    }
}

std::vector<int> MainWindow::draw_splay(Splay::SplayTree *Tree, int x_dif = 0, int y_dif = 0) {
  if (!Tree) {
      return std::vector<int>(5, 1);
    }

  std::vector<int> left = draw_splay(Tree->left, x_dif, y_dif + vert_dist_y);
  std::vector<int> right = draw_splay(Tree->right, x_dif + left[1] - left[0] + vert_w, y_dif + vert_dist_y);
  if (left[4] && right[4]) {
      SplayView->addVertex(x_dif, y_dif, x_dif + vert_w / 2, y_dif + vert_h / 2, x_dif + vert_w / 2, y_dif + vert_h / 2, Qt::black, Qt::black, vert_w, vert_h, Tree->data, 3);
      return {x_dif , x_dif + vert_w, x_dif + vert_w / 2, y_dif + vert_h / 2, 0};
    } else if (left[4]) {
      SplayView->addVertex(x_dif, y_dif, x_dif + vert_w / 2, y_dif + vert_h / 2, right[2], right[3], Qt::black, Qt::black, vert_w, vert_h, Tree->data, 3);
      return {x_dif, right[1], x_dif + vert_w / 2, y_dif + vert_h / 2, 0};
    } else if (right[4]) {
      SplayView->addVertex(left[1], y_dif, left[2], left[3], left[1] + vert_w / 2, y_dif + vert_h / 2, Qt::black, Qt::black, vert_w, vert_h, Tree->data, 3);
      return {left[0], left[1] + vert_w, left[1] + vert_w / 2, y_dif + vert_h / 2, 0};
    } else {
      SplayView->addVertex(left[1], y_dif, left[2], left[3], right[2], right[3], Qt::black, Qt::black, vert_w, vert_h, Tree->data, 3);
      return {left[0], right[1], left[1] + vert_w / 2, y_dif + vert_h / 2, 0};
    }
}


void MainWindow::on_insertButton_clicked()
{
  int data = ui->data->text().toInt();
  if (is_synchronized) {
      Avl::insert(AvlTree, data);
      Rb::insert(RBTree, data);
      Kurevo::Insert(KurevoTree, data);
      Splay::insert(SplayTree, data);
      update_trees();
      return;
    }
  if (ui->tabWidget->currentIndex() == 0)
    Avl::insert(AvlTree, data);
  if (ui->tabWidget->currentIndex() == 1)
    Rb::insert(RBTree, data);
  if (ui->tabWidget->currentIndex() == 2)
    Kurevo::Insert(KurevoTree, data);
  if (ui->tabWidget->currentIndex() == 3)
    Splay::insert(SplayTree, data);
  update_trees();
}

void MainWindow::on_synchronizeBox_stateChanged(int arg1)
{
  is_synchronized = ui->synchronizeBox->isChecked();
  return;
}

void MainWindow::on_autoZoomBox_stateChanged(int arg1)
{
  update_trees();
  return;
}

void MainWindow::enable_autozoom() {
  AvlView->fitInView(this->AvlView->scene->sceneRect(), Qt::KeepAspectRatio);
  RBView->fitInView(this->RBView->scene->sceneRect(), Qt::KeepAspectRatio);
  KurevoView->fitInView(this->KurevoView->scene->sceneRect(), Qt::KeepAspectRatio);
  SplayView->fitInView(this->SplayView->scene->sceneRect(), Qt::KeepAspectRatio);
  return;
}

void MainWindow::on_randBUtton_clicked()
{

  int num = ui->randLine->text().toInt();
  QSet<int> st;
  while (st.size() != num) {
      st.insert(mersenne());
    }
  auto it = st.begin();
  for(; it != st.end(); ++it) {
      int data = *it;
      if (is_synchronized) {
          Avl::insert(AvlTree, data);
          Rb::insert(RBTree, data);
          Kurevo::Insert(KurevoTree, data);
          Splay::insert(SplayTree, data);
          continue;
        }
      if (ui->tabWidget->currentIndex() == 0)
        Avl::insert(AvlTree, data);
      if (ui->tabWidget->currentIndex() == 1)
        Rb::insert(RBTree, data);
      if (ui->tabWidget->currentIndex() == 2)
        Kurevo::Insert(KurevoTree, data);
      if (ui->tabWidget->currentIndex() == 3)
        Splay::insert(SplayTree, data);
    }
  update_trees();
}

void MainWindow::on_deleteButton_clicked()
{
    int data = ui->deleteLine->text().toInt();
    if (is_synchronized) {
        Avl::delete_elem(AvlTree, data);
        Rb::del(RBTree, data);
        Kurevo::Delete(KurevoTree, data);
        Splay::del(SplayTree, data);
        update_trees();
        return;
      }
    if (ui->tabWidget->currentIndex() == 0)
      Avl::delete_elem(AvlTree, data);
    if (ui->tabWidget->currentIndex() == 1)
      Rb::del(RBTree, data);
    if (ui->tabWidget->currentIndex() == 2)
      Kurevo::Delete(KurevoTree, data);
    if (ui->tabWidget->currentIndex() == 3)
      Splay::del(SplayTree, data);
    update_trees();

}
