#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    scene_ = new PaintScene();
    ui_->graphicsView->setScene(scene_);

}

MainWindow::~MainWindow() {
    delete ui_;
}


void MainWindow::on_check_cross_validation_stateChanged(int arg1) {
    if (ui_->check_cross_validation->isChecked()) {
        ui_->label_k->setEnabled(true);
        ui_->spin_k_groups->setEnabled(true);
    } else {
        ui_->label_k->setEnabled(false);
        ui_->spin_k_groups->setEnabled(false);
    }
}

