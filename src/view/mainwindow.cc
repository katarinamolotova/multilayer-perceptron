#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  this->setWindowTitle("MLP");

  scene_ = new PaintScene();
  ui_->graphicsView->setScene(scene_);
  controller_ = new Controller();
  ConnectSlots();
}

MainWindow::~MainWindow() {
  delete movie_;
  delete scene_;
  delete controller_;
  delete ui_;
}

//  tab learning

void MainWindow::on_check_cross_validation_stateChanged(int arg1) {
  EnabledMainMenu(arg1 > 0);
}

void MainWindow::EnabledMainMenu(bool enabled) {
  ui_->label_k->setEnabled(enabled);
  ui_->spin_k_groups->setEnabled(enabled);
  ui_->label_epochs->setEnabled(!enabled);
  ui_->spin_count_epochs->setEnabled(!enabled);
  ui_->check_build_graph->setEnabled(!enabled);
}

void MainWindow::on_check_default_weights_stateChanged(int arg1) {
  if (arg1 == 0) {
    ui_->button_load_weights->setEnabled(true);
    ui_->button_learning->setEnabled(false);
  } else {
    ui_->button_load_weights->setEnabled(false);
    if (controller_->DataSetIsLoaded()) ui_->button_learning->setEnabled(true);
  }
}

void MainWindow::on_button_load_file_for_learning_clicked() {
  if (LoadDataSets()) {
    if (ui_->check_default_weights->isChecked() ||
        controller_->WeightsIsLoaded())
      ui_->button_learning->setEnabled(true);
  } else {
    ui_->button_learning->setEnabled(false);
  }
}

void MainWindow::on_button_learning_clicked() {
  movie_ = new QMovie(":/resources/two-hours-later.gif");
  movie_->setScaledSize(ui_->label_gif->size());
  ui_->label_gif->setMovie(movie_);
  movie_->start();
  ui_->tabWidget->setEnabled(false);
  Training();
}

void MainWindow::Training() {
  thread_ = std::thread([this]() {
    NeuralNetType type = ui_->matrix_mode->isChecked() ? NeuralNetType::MATRIX
                                                       : NeuralNetType::GRAPH;
    if (ui_->check_cross_validation->isChecked())
      training_info_ =
          controller_->Training(ui_->check_default_weights->isChecked(),
                                ui_->spin_count_layers->value(), type, 0,
                                ui_->spin_k_groups->value());
    else
      training_info_ =
          controller_->Training(ui_->check_default_weights->isChecked(),
                                ui_->spin_count_layers->value(), type,
                                ui_->spin_count_epochs->value(), 0);
    emit CompleteTraining();
  });
}

void MainWindow::CheckTraining() {
  if (thread_.joinable()) thread_.join();
  movie_->stop();
  ui_->tabWidget->setEnabled(true);
  ui_->label_gif->clear();
  if (controller_->GetErrorTrain()) {
    QMessageBox::critical(this, "Training neural net", "Training is failed");
  } else {
    PrintInfoAboutTraining(training_info_);
    if (ui_->check_build_graph->isChecked()) PrintGraph(training_info_);

    ui_->button_save_weights->setEnabled(true);
    ui_->check_now_realization->setEnabled(true);
  }
}

void MainWindow::on_button_load_weights_clicked() {
  if (LoadWeights()) {
    if (controller_->DataSetIsLoaded()) ui_->button_learning->setEnabled(true);
  } else {
    ui_->button_learning->setEnabled(false);
    ui_->check_now_realization->setEnabled(false);
    ui_->button_save_weights->setEnabled(false);
  }
}

void MainWindow::on_button_save_weights_clicked() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Choose file"), QDir::currentPath(), tr("weights (*.txt)"));
  bool success = controller_->SaveWeight(fileName.toStdString());
  if (!success)
    QMessageBox::critical(this, "Saving weights", "Something went wrong!");
}

void MainWindow::on_check_build_graph_stateChanged(int arg1) {
  if (arg1 > 0 && training_info_.size() > 1) PrintGraph(training_info_);
}

void MainWindow::PrintGraph(const vector<Trainer::TrainingInfo> &info) {
  ui_->graph->clearGraphs();
  if (!info.empty()) {
    double x_start = 0.5, x_end = (double)info.size() + 0.5;
    double y_start = info.front().error + 0.1, y_end = info.back().error - 0.1;
    ui_->graph->xAxis->setRange(x_start, x_end);
    ui_->graph->yAxis->setRange(y_start, y_end);
    QVector<double> x, y;

    for (int i = 0; i < (int)info.size(); i++) {
      x.push_back(i + 1);
      y.push_back(info[i].error);
    }

    ui_->graph->addGraph();
    ui_->graph->graph(0)->setData(x, y);
    ui_->graph->replot();
  }
}

void MainWindow::PrintInfoAboutTraining(vector<Trainer::TrainingInfo> info) {
  ui_->text_browser->clear();
  ui_->text_browser->insertPlainText("Обучение завершено");
  for (int i = 0; i < (int)info.size(); i++) {
    if (info.size() > 1)
      ui_->text_browser->insertPlainText("\nЭпоха " + QString::number(i + 1));

    ui_->text_browser->insertPlainText(
        "\nСредняя ошибка: " + QString::number(info[i].error) +
        "\nТочность: " + QString::number(info[i].accuracy) +
        "\nПериод: " + QString::number(info[i].time));
    if (i != (int)info.size() - 1)
      ui_->text_browser->insertPlainText("\n----------------------");
  }
}

//  tab testing

void MainWindow::on_button_load_weights_test_clicked() {
  if (LoadWeights()) {
    ui_->button_load_file_test->setEnabled(true);
    ui_->button_process->setEnabled(true);
    NeuralNetType type = ui_->perceptron_matrix_mode_test->isChecked()
                             ? NeuralNetType::MATRIX
                             : NeuralNetType::GRAPH;
    controller_->MakeNeuralNet(false, 2, type);
  } else {
    ui_->button_load_file_test->setEnabled(false);
    ui_->button_process->setEnabled(false);
  }
}

void MainWindow::on_button_load_file_test_clicked() {
  if (LoadDataSets()) {
    ui_->button_run_test->setEnabled(true);
  } else {
    ui_->button_run_test->setEnabled(false);
  }
}

void MainWindow::on_button_run_test_clicked() {
  ui_->doubleSpinBox->setValue(ui_->doubleSpinBox->value());
  Testing();
  ui_->tabWidget->setEnabled(false);
}

void MainWindow::Testing() {
  thread_ = std::thread([this]() {
    testing_info_ = controller_->AutomationTest(ui_->doubleSpinBox->value());
    emit CompleteTesting();
  });
}

void MainWindow::CheckTesting() {
  if (thread_.joinable()) thread_.join();
  ui_->tabWidget->setEnabled(true);
  if (controller_->GetErrorTest()) {
    QMessageBox::critical(this, "Testing neural net", "Test is failed");
  } else {
    ui_->lineEdit_average_accuracy->setText(
        QString::number(testing_info_.accuracy));
    ui_->lineEdit_average_mse->setText(QString::number(testing_info_.error));
    ui_->lineEdit_f_mesaure->setText(QString::number(testing_info_.f_measure));
    ui_->lineEdit_precision->setText(QString::number(testing_info_.precision));
    ui_->lineEdit_recall->setText(QString::number(testing_info_.recall));
    ui_->lineEdit_spent_time->setText(QString::number(testing_info_.time));
  }
}

void MainWindow::on_check_now_realization_stateChanged(int arg1) {
  EnabledTestMenu(arg1 == 0);
}

void MainWindow::EnabledTestMenu(bool enabled) {
  ui_->label_realization_test->setEnabled(enabled);
  ui_->perceptron_graph_mode_test->setEnabled(enabled);
  ui_->perceptron_matrix_mode_test->setEnabled(enabled);
  ui_->button_load_weights_test->setEnabled(enabled);
  ui_->button_load_file_test->setEnabled(!enabled);
  ui_->button_process->setEnabled(!enabled);
}

//  tab manual testing

void MainWindow::on_button_load_image_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Choose image"), QDir::currentPath(), tr("*.bmp"));

  if (!fileName.isEmpty()) {
    QImage img(fileName);
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
  QPixmap pixmap =
      ui_->graphicsView->grab(ui_->graphicsView->sceneRect().toRect());
  QImage img = pixmap.scaled(28, 28).toImage();
  vector<double> data = GetDataFromImg(img);
  char result = controller_->ManualTest(data);
  ui_->label_answer->setText(QString(result));
}

void MainWindow::on_button_clear_clicked() { scene_->clear(); }

vector<double> MainWindow::GetDataFromImg(const QImage &img) {
  vector<double> input;
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

//  common

bool MainWindow::LoadWeights() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Choose file"), QDir::currentPath(), tr("*.txt"));
  bool success = controller_->LoadWeights(fileName.toStdString());
  if (!success)
    QMessageBox::critical(this, "Loading weights", "Something went wrong!");
  return success;
}

bool MainWindow::LoadDataSets() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Choose file"), QDir::currentPath(), tr("*.csv"));
  bool error = controller_->LoadDataSet(fileName.toStdString());
  if (error)
    QMessageBox::critical(this, "Loading datasets", "Something went wrong!");
  return !error;
}

void MainWindow::ConnectSlots() {
  connect(this, &MainWindow::CompleteTraining, this,
          &MainWindow::CheckTraining);
  connect(this, &MainWindow::CompleteTesting, this, &MainWindow::CheckTesting);
}

void MainWindow::closeEvent(QCloseEvent *p_event) {
  if (thread_.joinable())
    p_event->ignore();
  else
    p_event->accept();
}

}  //  namespace s21
