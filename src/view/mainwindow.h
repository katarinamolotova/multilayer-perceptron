#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>

#include "qcustomplot.h"
#include "paintscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_check_cross_validation_stateChanged(int arg1);
    void on_button_learning_clicked();
    void on_button_delete_learning_clicked();
    void on_button_load_weights_clicked();
    void on_button_save_weights_clicked();

    void on_button_load_weights_test_clicked();
    void on_button_load_file_test_clicked();
    void on_button_run_test_clicked();

    void on_button_load_image_clicked();
    void on_button_process_clicked();
    void on_button_clear_clicked();

private:
    Ui::MainWindow *ui_;


    PaintScene *scene_;
    std::vector<double> GetDataFromImg(const QImage &img);

};

}

#endif // MAINWINDOW_H
