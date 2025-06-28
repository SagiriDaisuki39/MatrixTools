#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidget>
#include <QSpinBox>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 绑定行列数改变信号
    connect(ui->spinBox_NumRow1, SIGNAL(valueChanged(int)),
            this, SLOT(on_spinSizeChanged()));
    connect(ui->spinBox_NumCol1, SIGNAL(valueChanged(int)),
            this, SLOT(on_spinSizeChanged()));
    connect(ui->spinBox_NumRow2, SIGNAL(valueChanged(int)),
            this, SLOT(on_spinSizeChanged()));
    connect(ui->spinBox_NumCol2, SIGNAL(valueChanged(int)),
            this, SLOT(on_spinSizeChanged()));

    // 初始调整表格大小
    on_spinSizeChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinSizeChanged()
{
    // 根据 SpinBox 的值设置 tableA 和 tableB 的行/列数
    ui->tableMatrix_1->setRowCount(ui->spinBox_NumRow1->value());
    ui->tableMatrix_1->setColumnCount(ui->spinBox_NumCol1->value());
    ui->tableMatrix_2->setRowCount(ui->spinBox_NumRow2->value());
    ui->tableMatrix_2->setColumnCount(ui->spinBox_NumCol2->value());
    // 结果表格清空
    ui->tableResult->clear();
    ui->lblStatus->clear();
}

bool MainWindow::readMatrix(QTableWidget *table, MatrixMultiplier::Matrix &out)
{
    int rows = table->rowCount();
    int cols = table->columnCount();
    out.assign(rows, std::vector<double>(cols, 0.0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            auto item = table->item(i, j);
            if (!item) {
                ui->lblStatus->setText("请完整填写矩阵元素！");
                return false;
            }
            bool ok;
            double v = item->text().toDouble(&ok);
            if (!ok) {
                ui->lblStatus->setText("矩阵元素必须是数字！");
                return false;
            }
            out[i][j] = v;
        }
    }
    return true;
}

void MainWindow::showMatrix(QTableWidget *table, const MatrixMultiplier::Matrix &mat)
{
    int rows = static_cast<int>(mat.size());
    int cols = rows ? static_cast<int>(mat[0].size()) : 0;
    table->setRowCount(rows);
    table->setColumnCount(cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            table->setItem(i, j, new QTableWidgetItem(QString::number(mat[i][j])));
        }
    }
}

void MainWindow::on_pushButtonCulculate_clicked()
{
    // 读取 A、B 矩阵
    MatrixMultiplier::Matrix A, B;
    if (!readMatrix(ui->tableMatrix_1, A) || !readMatrix(ui->tableMatrix_2, B))
        return;

    // 检查乘法维度
    if (A[0].size() != B.size()) {
        ui->lblStatus->setText("矩阵维度不匹配：A 列数 必须 等于 B 行数");
        return;
    }

    // 计算结果
    auto C = MatrixMultiplier::multiply(A, B);

    // 显示结果
    showMatrix(ui->tableResult, C);
    ui->labelShowNumRow3->setText(QString::number(ui->spinBox_NumRow1->value()));
    ui->labelShowNumCol3->setText(QString::number(ui->spinBox_NumCol2->value()));
    ui->lblStatus->setText("计算完成！");
}

void MainWindow::on_pushButtonClear_clicked()
{
    ui->tableMatrix_1->clear();
    ui->tableMatrix_2->clear();
    ui->tableResult->clear();
}

