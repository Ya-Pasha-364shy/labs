#include "myClass.h"

Matrix::Matrix()
{
	m_row = 0; m_col = 0;
	m_data = nullptr;
}

Matrix::Matrix(int row, int col)
{

	m_row = row;
	m_col = col;

	m_data = new int* [row];
	for (int i = 0; i < row; ++i)
	{
		m_data[i] = new int[col];

		for (int j = 0; j < col; ++j)
			m_data[i][j] = 0;
	}
}


int Matrix::getItem(int row, int col)
{

	assert((row - 1 >= 0) && (col - 1 >= 0) && (row - 1 <= m_row) && (col - 1 <= m_col));

	return m_data[row - 1][col - 1];

}

void Matrix::print()

{

	cout << "Rows: " << m_row << " Columns: " << m_col << endl;

}


void Matrix::clear()
{
	for (int i = 0; i < m_row; i++)
	{
		delete[] m_data[i];
	}

	delete[] m_data;

	m_row = 0;

	m_col = 0;

}

void Matrix::setSize(int row, int col)

{
	// выдкеляем память для новой матрицы
	int** data;

	data = new int* [row];

	for (int i = 0; i < row; ++i)

	{
		// заполняем новую матрицу значениями из основной матрицы
		data[i] = new int[col];

		for (int j = 0; j < col; ++j)
			// следим за тем, чтобы значения из основной не терялись
			if ((m_col > j) && (m_row > i))
				data[i][j] = m_data[i][j];
		// как только значения (i,j) становятся больше, инициализируем их нулём 
			else
				data[i][j] = 0;

	}
	for (int i = 0; i < m_row; i++) // Удаляем основную матрицу
	{
		delete[] m_data[i]; // сначала память под столбцы
	}
	delete[] m_data;	// затем под строки

	m_col = col;
	m_row = row;
	// Переносим элементы из запасной в основную
	m_data = new int* [row];
	for (int i = 0; i < row; ++i)
	{
		m_data[i] = new int[col];
		for (int j = 0; j < col; ++j)
			m_data[i][j] = data[i][j];
	}
	// Удаляем запасную
	for (int i = 0; i < m_row; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}

int* Matrix::getLink(int row, int col)
{
	assert((row - 1 >= 0) && (col - 1 >= 0) && (row - 1 <= m_row) && (col - 1 <= m_col));
	return  &m_data[row - 1][col - 1];
}

void Matrix::transpose()
{
	Matrix tmp(this->m_row, this->m_col);

	for (int i = 0; i < tmp.m_row; ++i)
		for (int j = 0; j < tmp.m_col; ++j)
			tmp.m_data[i][j] = this->m_data[i][j];

	this->clear();
	this->m_row = tmp.m_col;
	this->m_col = tmp.m_row;

	this->m_data = new int* [tmp.m_col];
	for (int i = 0; i < tmp.m_col; ++i)
	{
		this->m_data[i] = new int[tmp.m_row];
		for (int j = 0; j < tmp.m_row; ++j)
			this->m_data[i][j] = tmp.m_data[j][i];
	}

}

Matrix::~Matrix()
{
	for (int i = 0; i < m_row; i++)
	{
		delete[] m_data[i];
	}
	delete[] m_data;
}


ostream& operator<<(ostream& out, const Matrix& mrx)
{
	out << "\n";
	for (int i = 0; i < mrx.m_row; ++i)
	{
		for (int j = 0; j < mrx.m_col; ++j)
			out << mrx.m_data[i][j] << " ";
		out << endl;
	}
	out << "\n";
	return out;
}

istream& operator>>(istream& in, Matrix& m)
{
	m.clear();

	in >> m.m_row;
	in >> m.m_col;

	m.m_data = new int* [m.m_row];
	for (int i = 0; i < m.m_row; ++i)
	{
		m.m_data[i] = new int[m.m_col];
		for (int j = 0; j < m.m_col; ++j)
			try
			{
			in >> m.m_data[i][j];
			if (cin.fail())
			{
				cin.ignore(32767, '\n');
				cout << "Invalid input";
				exit(0);
			}
		}
		catch (...)
		{
			cout << "Error" << endl;
		}
	}
	return in;
}

Matrix& Matrix::operator+(const Matrix& m1)
{
	assert((this->m_col == m1.m_col) && (this->m_row == m1.m_row));

	for (int i = 0; i < m1.m_row; ++i)
		for (int j = 0; j < m1.m_col; ++j)
			this->m_data[i][j] += m1.m_data[i][j];

	return *this;
}

Matrix& Matrix::operator-(const Matrix& m1)
{
	assert((this->m_col == m1.m_col) && (this->m_row == m1.m_row));

	for (int i = 0; i < m1.m_row; ++i)
		for (int j = 0; j < m1.m_col; ++j)
			this->m_data[i][j] -= m1.m_data[i][j];

	return *this;
}

Matrix& Matrix::operator* (const Matrix& m1)
{
	assert((this->m_col == m1.m_row));
	Matrix m(this->m_row, m1.m_col);
	int tmp = 0;

	for (int i = 0; i < this->m_row; ++i)
		for (int j = 0; j < m1.m_col; ++j)
			for (int k = 0; k < m1.m_row; ++k)
				m.m_data[i][j] += this->m_data[i][k] * m1.m_data[k][j];

	this->m_col = m1.m_col;

	for (int i = 0; i < this->m_row; ++i)
		for (int j = 0; j < m1.m_col; ++j)
			this->m_data[i][j] = m.m_data[i][j];

	return *this;
}

