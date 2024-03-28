// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <vector>

constexpr int MatrixSize = 3;

void PrintMatrix3x3(const std::vector<std::vector<double>>& m)
{
    for (size_t r{}; r < MatrixSize; r++)
    {
        for (size_t c{}; c < MatrixSize; c++)
        {
            std::cout << std::setw(8) << m[r][c];
            //printf("%-8.3g", m[r][c]);
        }
        std::cout << '\n';
    }
}

double GetMinorElement(const std::vector<std::vector<double>> &m, size_t row, size_t col)
{
    std::vector<size_t> rows(2), cols(2);
    rows[0] = row == 1 || row == 2 ? 0 : 1;
    cols[0] = col == 1 || col == 2 ? 0 : 1;
    rows[1] = row == 1 || row == 0 ? 2 : 1;
    cols[1] = col == 1 || col == 0 ? 2 : 1;
    return (m[rows[0]][cols[0]] * m[rows[1]][cols[1]] - m[rows[0]][cols[1]] * m[rows[1]][cols[0]]) * ((row + col) % 2 ? -1 : 1);
}

std::vector<std::vector<double>> GetMatrixMinor(const std::vector<std::vector<double>>& m)
{
    std::vector<std::vector<double>> matrixMinor(3, std::vector<double>(3));
    for (size_t r{}; r < MatrixSize; r++)
    {
        for (size_t c{}; c < MatrixSize; c++)
        {
            matrixMinor[r][c] = GetMinorElement(m, r, c);
        }
    }
    return matrixMinor;
}

double GetMatrixDet(const std::vector<std::vector<double>>& m)
{
    return m[0][0] * m[1][1] * m[2][2] +
        m[1][0] * m[2][1] * m[0][2] +
        m[0][1] * m[1][2] * m[2][0] -
        m[2][0] * m[1][1] * m[0][2] -
        m[1][0] * m[0][1] * m[2][2] -
        m[0][0] * m[1][2] * m[2][1];
}

std::vector<std::vector<double>> GetMatrixInv(const std::vector<std::vector<double>> &m, double det)
{
    std::vector<std::vector<double>> matrixInv(3, std::vector<double>(3));
    for (size_t r{}; r < MatrixSize; r++)
    {
        for (size_t c{}; c < MatrixSize; c++)
        {
            matrixInv[r][c] = m[c][r] / det;
        }
    }
    return matrixInv;
}


std::vector<std::vector<double>> InvertMatrix(const std::vector<std::vector<double>> &m)
{
    auto det = GetMatrixDet(m);
    if (det == 0.0)
    {
        throw std::runtime_error("Unable to calculate invert matrix, because matrix determinant equal to zero");
    }

    auto matrixMinor = GetMatrixMinor(m);
    auto matrixInv = GetMatrixInv(matrixMinor, det);

    return matrixInv;
}

int main()
{
    std::vector<std::vector<double>> matrixSrc
    {
        {3.0, 4.0, 8.0},
        {2.4, -1.0, 11.0},
        {7.0, -3.2, 0.0}
    };

    std::cout.setf(std::ios::fixed);
    std::cout.precision(3);

    PrintMatrix3x3(matrixSrc);

    try
    {
        std::vector<std::vector<double>> matrixInv = InvertMatrix(matrixSrc);
        std::cout << '\n';
        PrintMatrix3x3(matrixInv);
    }
    catch (const std::runtime_error& ex)
    {
        std::cout << ex.what() << '\n';
        return 1;
    }
    return 0;
}
