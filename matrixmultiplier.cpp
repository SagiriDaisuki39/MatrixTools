#include "MatrixMultiplier.h"

MatrixMultiplier::Matrix MatrixMultiplier::multiply(const Matrix &A, const Matrix &B)
{
    size_t m = A.size();
    if (m == 0) return {};
    size_t n = A[0].size();
    // 验证 B 的行数是否等于 A 的列数
    if (B.size() != n) return {};
    size_t p = B[0].size();

    // 结果矩阵尺寸 m × p，初始化为 0
    Matrix C(m, std::vector<double>(p, 0.0));

    // 三重循环完成乘法
    for (size_t i = 0; i < m; ++i) {
        for (size_t k = 0; k < n; ++k) {
            double a = A[i][k];
            for (size_t j = 0; j < p; ++j) {
                C[i][j] += a * B[k][j];
            }
        }
    }
    return C;
}
