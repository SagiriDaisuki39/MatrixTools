#ifndef MATRIXMULTIPLIER_H
#define MATRIXMULTIPLIER_H

#include <vector>

class MatrixMultiplier
{
public:
    MatrixMultiplier();
    using Matrix = std::vector<std::vector<double>>;

    /**
     * @brief 矩阵相乘
     * @param A 矩阵 A，尺寸 m×n
     * @param B 矩阵 B，尺寸 n×p
     * @return 返回矩阵 C = A×B，尺寸 m×p；若维度不匹配则返回空矩阵
     */
    static Matrix multiply(const Matrix &A, const Matrix &B);

};

#endif // MATRIXMULTIPLIER_H
