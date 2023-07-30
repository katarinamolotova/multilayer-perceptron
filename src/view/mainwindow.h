#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <thread>

#include "../controller/controller.h"
#include "paintscene.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 signals:
  void CompleteTraining();
  void CompleteTesting();

 private slots:
  void on_check_cross_validation_stateChanged(int arg1);
  void on_check_default_weights_stateChanged(int arg1);
  void on_button_learning_clicked();
  void on_button_load_weights_clicked();
  void on_button_save_weights_clicked();
  void on_button_load_file_for_learning_clicked();
  void on_check_build_graph_stateChanged(int arg1);

  void on_button_load_weights_test_clicked();
  void on_button_load_file_test_clicked();
  void on_button_run_test_clicked();
  void on_check_now_realization_stateChanged(int arg1);

  void on_button_load_image_clicked();
  void on_button_process_clicked();
  void on_button_clear_clicked();
  void closeEvent(QCloseEvent *p_event) override;

 private:
  Ui::MainWindow *ui_;
  Controller *controller_ = nullptr;
  vector<Trainer::TrainingInfo> training_info_;
  Tester::TestingInfo testing_info_;
  std::thread thread_{};
  QMovie *movie_;

  void Training();
  void CheckTraining();
  void PrintGraph(const vector<Trainer::TrainingInfo> &info);
  void PrintInfoAboutTraining(vector<Trainer::TrainingInfo> info);

  void EnabledTestMenu(bool enabled);
  void EnabledMainMenu(bool enabled);
  void Testing();
  void CheckTesting();

  PaintScene *scene_;
  vector<double> GetDataFromImg(const QImage &img);

  bool LoadWeights();
  bool LoadDataSets();
  void ConnectSlots();
};

}  // namespace s21

#endif  // MAINWINDOW_H
