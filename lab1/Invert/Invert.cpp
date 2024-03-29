// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <cassert>
#include <iomanip>

constexpr int MatrixSize = 3;
typedef double matrix3x3[MatrixSize][MatrixSize];

struct MatrixWrap {
	matrix3x3 items;
};

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

void PrintMatrix3x3(const MatrixWrap& matrix)
{
	for (size_t r = 0; r < MatrixSize; r++)
	{
		for (size_t c = 0; c < MatrixSize; c++)
		{
			std::cout.setf(std::ios::fixed);
			std::cout << std::setprecision(3) << std::setw(8) << matrix.items[r][c];
		}
		std::cout << '\n';
	}
}

double GetMinorElement(const MatrixWrap& matrix, size_t row, size_t col)
{
	size_t rows[2], cols[2];
	rows[0] = row == 1 || row == 2 ? 0 : 1;
	cols[0] = col == 1 || col == 2 ? 0 : 1;
	rows[1] = row == 1 || row == 0 ? 2 : 1;
	cols[1] = col == 1 || col == 0 ? 2 : 1;
	return (matrix.items[rows[0]][cols[0]] * matrix.items[rows[1]][cols[1]] - matrix.items[rows[0]][cols[1]] * matrix.items[rows[1]][cols[0]])
		* ((row + col) % 2 ? -1 : 1);
}

MatrixWrap GetMatrixMinor(const MatrixWrap& matrix)
{
	MatrixWrap matrixMinor;
	for (size_t r = 0; r < MatrixSize; r++)
	{
		for (size_t c = 0; c < MatrixSize; c++)
		{
			matrixMinor.items[r][c] = GetMinorElement(matrix, r, c);
		}
	}
	return matrixMinor;
}

double GetMatrixDet(const MatrixWrap& matrix)
{
	return matrix.items[0][0] * matrix.items[1][1] * matrix.items[2][2] +
		matrix.items[1][0] * matrix.items[2][1] * matrix.items[0][2] +
		matrix.items[0][1] * matrix.items[1][2] * matrix.items[2][0] -
		matrix.items[2][0] * matrix.items[1][1] * matrix.items[0][2] -
		matrix.items[1][0] * matrix.items[0][1] * matrix.items[2][2] -
		matrix.items[0][0] * matrix.items[1][2] * matrix.items[2][1];
}

MatrixWrap GetMatrixTransp(const MatrixWrap& matrix)
{
	MatrixWrap matrixTransp;
	for (size_t r = 0; r < MatrixSize; r++)
	{
		for (size_t c = 0; c < MatrixSize; c++)
		{
			matrixTransp.items[r][c] = matrix.items[c][r];
		}
	}
	return matrixTransp;
}

MatrixWrap GetMatrixMulConst(const MatrixWrap& matrix, double mul)
{
	MatrixWrap matrixMul;
	for (size_t r = 0; r < MatrixSize; r++)
	{
		for (size_t c = 0; c < MatrixSize; c++)
		{
			matrixMul.items[r][c] = matrix.items[r][c] * mul;
			matrixMul.items[r][c] = fabs(matrixMul.items[r][c]) < 0.000000001 ? 0.0 : matrixMul.items[r][c];
		}
	}
	return matrixMul;
}

MatrixWrap ReadMatrixFromFile(const std::string& fileName)
{
	std::ifstream input;
	input.open(fileName);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open '" + fileName + "' for reading");
	}

	MatrixWrap matrix;
	for (size_t r = 0; r < MatrixSize; r++)
	{
		std::string line;
		if (!std::getline(input, line))
		{
			throw std::runtime_error("Failed to read data from input file");
		}

		std::istringstream lineStream(line);

		for (size_t c = 0; c < MatrixSize; c++)
		{
			lineStream >> matrix.items[r][c];
			if (lineStream.fail()) {
				throw std::runtime_error("Incorrect data type for matrix element in input file");
			}
		}
	}
	return matrix;
}

static MatrixWrap InvertMatrix(const std::string& fileName)
{
	auto matrixSrc = ReadMatrixFromFile(fileName);

	auto det = GetMatrixDet(matrixSrc);
	if (fabs(det) < 0.000000001)
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
		MatrixWrap matrixInv = InvertMatrix(args->fileName);
		PrintMatrix3x3(matrixInv);
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what() << '\n';
		return 1;
	}
	return 0;
}
