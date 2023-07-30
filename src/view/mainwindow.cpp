#include "mainwindow.h"
#include "ui_mainwindow.h"


namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
    this->setWindowTitle("MLP");


    scene_ = new PaintScene();
    ui_->graphicsView->setScene(scene_);

}

MainWindow::~MainWindow() {
    delete ui_;
}

//  tab learning

void MainWindow::on_check_cross_validation_stateChanged(int arg1) {
    if (arg1 > 0) {
        ui_->label_k->setEnabled(true);
        ui_->spin_k_groups->setEnabled(true);
    } else {
        ui_->label_k->setEnabled(false);
        ui_->spin_k_groups->setEnabled(false);
    }
}


void MainWindow::on_button_learning_clicked() {
    //  TO_DO()
}

void MainWindow::on_button_delete_learning_clicked() {
    //  TO_DO()
}

void MainWindow::on_button_load_weights_clicked() {
    QString fileName = QFileDialog::getOpenFileName();

}

void MainWindow::on_button_save_weights_clicked() {
    //  TO_DO()
}


//  tab testing

void MainWindow::on_button_load_weights_test_clicked() {

}

void MainWindow::on_button_load_file_test_clicked() {

}

void MainWindow::on_button_run_test_clicked() {

}


//  tab manual testing


void MainWindow::on_button_load_image_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose image"), QDir::currentPath(), tr("*.bmp"));

    if (!fileName.isEmpty()) {
        QImage img(fileName);
        qDebug() << fileName << " " << img;
        if (img.isNull() || img.width() > 512 || img.height() > 512) {
            QMessageBox::information(this, "Image Viewer", "Error image");
        } else {
            QPixmap temp = QPixmap::fromImage(img.scaled(300, 300));
            scene_->addPixmap(temp);
            ui_->graphicsView->setScene(scene_);
        }
    }
}

void MainWindow::on_button_process_clicked() {

}


void MainWindow::on_button_clear_clicked() {
    scene_->clear();
}

std::vector<double> GetDataFromImg(const QImage &img) {
    std::vector<double> input;
    for (int i = 0; i < 28; i++) {
      for (int j = 0; j < 28; j++) {
        QColor current_color = img.pixel(i, j);
        int red, green, black;
        current_color.getRgb(&red, &green, &black);
        input.push_back((double)(red + green + black) / 3);
      }
    }
    return input;
}

}  //  namespace s21
