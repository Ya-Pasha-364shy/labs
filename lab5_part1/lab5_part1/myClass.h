#pragma once
#include <iostream>
#include <cassert>
using namespace std;

class Matrix
{
private:
	int m_row;	// число строк
	int m_col;  // число столбцов
	int** m_data; // динамическое выделение памяти под матрицу

	void clear();	// удаление матрицы

public:
	// параметризованный конструктор
	Matrix(int row, int col);

	// конструктор по умолчанию
	Matrix();

	int getRows() const {
		return m_row;
	}

	int getColumns() const {
		return m_col;
	}

	// метод получения элемента
	int getItem(int row, int col);

	// распечатка параметров матрицы
	void print();

	// изменение размеров матрицы
	void setSize(int row, int col);

	// получение ссылки на элемент
	int* getLink(int row, int col);

	// транспонирование матрицы
	void transpose();

	~Matrix();

	// перегрузка оператора вывода для матрицы
	friend ostream& operator<< (ostream& out, const Matrix& m);

	// перегрузка оператора ввода для матрицы
	friend istream& operator>> (istream& in, Matrix& m);

	// Перегрузка операторов сложения/вычитания/умножения
	// для выполнения арифм. операций с матрицами
	Matrix& operator+ (const Matrix& m1);
	Matrix& operator- (const Matrix& m1);
	Matrix& operator* (const Matrix& m1);
};

ostream& operator<<(ostream& out, const Matrix& mrx);
istream& operator>>(istream& in, Matrix& m);
