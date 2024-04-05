// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <cassert>
#include <iomanip>
#include <array>

constexpr int MatrixSize = 3;
typedef std::array<double, MatrixSize> Vector3;
typedef std::array<Vector3, MatrixSize> Matrix3x3;

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

void PrintMatrix3x3(const Matrix3x3& matrix)
{
	for (const Vector3 &r : matrix)
	{
		for (double item : r)
		{
			std::cout.setf(std::ios::fixed);
			std::cout << std::setprecision(3) << std::setw(8) << item;
		}
		std::cout << '\n';
	}
}

double GetMinorElement(const Matrix3x3& matrix, size_t row, size_t col)
{
	size_t rows[2], cols[2];
	rows[0] = row == 1 || row == 2 ? 0 : 1;
	cols[0] = col == 1 || col == 2 ? 0 : 1;
	rows[1] = row == 1 || row == 0 ? 2 : 1;
	cols[1] = col == 1 || col == 0 ? 2 : 1;
	return (matrix[rows[0]][cols[0]] * matrix[rows[1]][cols[1]] - matrix[rows[0]][cols[1]] * matrix[rows[1]][cols[0]])
		* ((row + col) % 2 ? -1 : 1);
}

Matrix3x3 GetMatrixMinor(const Matrix3x3& matrix)
{
	Matrix3x3 matrixMinor;
	for (size_t r = 0; r < MatrixSize; r++)
	{
		for (size_t c = 0; c < MatrixSize; c++)
		{
			matrixMinor[r][c] = GetMinorElement(matrix, r, c);
		}
	}
	return matrixMinor;
}

double GetMatrixDet(const Matrix3x3& matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2] +
		matrix[1][0] * matrix[2][1] * matrix[0][2] +
		matrix[0][1] * matrix[1][2] * matrix[2][0] -
		matrix[2][0] * matrix[1][1] * matrix[0][2] -
		matrix[1][0] * matrix[0][1] * matrix[2][2] -
		matrix[0][0] * matrix[1][2] * matrix[2][1];
}

Matrix3x3 GetMatrixTransp(const Matrix3x3& matrix)
{
	Matrix3x3 matrixTransp;
	for (size_t r = 0; r < MatrixSize; r++)
	{
		for (size_t c = 0; c < MatrixSize; c++)
		{
			matrixTransp[r][c] = fabs(matrix[c][r]) < DBL_EPSILON ? 0.0 : matrix[c][r];
		}
	}
	return matrixTransp;
}

Matrix3x3 GetMatrixMulConst(const Matrix3x3& matrix, double mul)
{
	Matrix3x3 matrixMul;
	for (size_t r = 0; r < MatrixSize; r++)
	{
		for (size_t c = 0; c < MatrixSize; c++)
		{
			matrixMul[r][c] = matrix[r][c] * mul;
		}
	}
	return matrixMul;
}

Matrix3x3 ReadMatrixFromFile(const std::string& fileName)
{
	std::ifstream input;
	input.open(fileName);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open '" + fileName + "' for reading");
	}

	Matrix3x3 matrix;
	for (Vector3 &r : matrix)
	{
		std::string line;
		if (!std::getline(input, line))
		{
			throw std::runtime_error("Failed to read data from input file");
		}

		std::istringstream lineStream(line);

		for (double &item : r)
		{
			if (!(lineStream >> item)) {
				throw std::runtime_error("Incorrect data type for matrix element in input file");
			}
		}
	}
	return matrix;
}

static Matrix3x3 InvertMatrix(const std::string& fileName)
{
	auto matrixSrc = ReadMatrixFromFile(fileName);

	auto det = GetMatrixDet(matrixSrc);
	if (fabs(det) < DBL_EPSILON)
	{
		throw std::runtime_error("Unable to calculate invert matrix, because matrix determinant equal to zero");
	}

	auto matrixMinor = GetMatrixMinor(matrixSrc);
	auto matrixTransp = GetMatrixTransp(matrixMinor);
	return GetMatrixMulConst(matrixTransp, 1.0 / det);
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	try
	{
		Matrix3x3 matrixInv = InvertMatrix(args->fileName);
		PrintMatrix3x3(matrixInv);
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what() << '\n';
		return 1;
	}
	return 0;
}
