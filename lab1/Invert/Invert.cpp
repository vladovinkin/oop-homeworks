// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <cassert>
#include <iomanip>
#include <vector>

constexpr int MatrixSize = 3;

struct Args {
    std::string fileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: Invert.exe <source file>\n";
        return std::nullopt;
    }
    Args args;
    args.fileName = argv[1];
    return args;
}

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
    std::vector<std::vector<double>> matrixMinor(MatrixSize, std::vector<double>(MatrixSize));
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
    std::vector<std::vector<double>> matrixInv(MatrixSize, std::vector<double>(MatrixSize));
    for (size_t r{}; r < MatrixSize; r++)
    {
        for (size_t c{}; c < MatrixSize; c++)
        {
            matrixInv[r][c] = m[c][r] / det;
        }
    }
    return matrixInv;
}

std::vector<std::vector<double>> ReadMatrixFromFile(const std::string& fileName)
{
    std::ifstream input;
    input.open(fileName);
    if (!input.is_open())
    {
        throw std::runtime_error("Failed to open '" + fileName + "' for reading");
    }

    std::vector<std::vector<double>> matrix(MatrixSize, std::vector<double>(MatrixSize));
    for (size_t r{}; r < MatrixSize; r++)
    {
        std::string line;
        std::getline(input, line);
        if (input.bad())
        {
            throw std::runtime_error("Failed to read data from input file");
        }

        std::istringstream lineStream(line);

        lineStream >> matrix[r][0] >> matrix[r][1] >> matrix[r][2];
    }
    return matrix;
}

std::vector<std::vector<double>> InvertMatrix(const std::string& fileName)
{
    auto matrixSrc = ReadMatrixFromFile(fileName);

    PrintMatrix3x3(matrixSrc);

    auto det = GetMatrixDet(matrixSrc);
    if (det == 0.0)
    {
        throw std::runtime_error("Unable to calculate invert matrix, because matrix determinant equal to zero");
    }

    auto matrixMinor = GetMatrixMinor(matrixSrc);
    auto matrixInv = GetMatrixInv(matrixMinor, det);

    return matrixInv;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    std::cout.setf(std::ios::fixed);
    std::cout.precision(3);

    try
    {
        std::vector<std::vector<double>> matrixInv = InvertMatrix(args->fileName);
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
