#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include <vector>
#include <QTableWidget>
#include "MatrixMultiplier.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinSizeChanged();      // 当行/列数 SpinBox 改变时，调整表格大小

    void on_pushButtonCulculate_clicked(); // 点击“相乘”按钮

    void on_pushButtonClear_clicked();

private:
    Ui::MainWindow *ui;

    /// 从 QTableWidget 读取矩阵数据
    bool readMatrix(QTableWidget *table, MatrixMultiplier::Matrix &out);

    /// 在 QTableWidget 中显示矩阵数据
    void showMatrix(QTableWidget *table, const MatrixMultiplier::Matrix &mat);
};
#endif // MAINWINDOW_H
