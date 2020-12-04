#include "myPole.h"

std::ostream& operator<<(std::ostream& out, const Pole& m)
{
    out << "\n";
    for (int i = 0; i < m.m_row; ++i)
    {
        for (int j = 0; j < m.m_col; ++j)
            out << m.m_data[i][j] << " ";
        out << std::endl;
    }
    out << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, Pole& m)
{
    in >> m.m_row;
    in >> m.m_col;

    m.m_data = new char* [m.m_row];

    for (int i{ 0 }; i < m.m_row; ++i)
    {
        m.m_data[i] = new char[m.m_col];

        for (int j{ 0 }; j < m.m_col; ++j)
        {
            try
            {
                in >> m.m_data[i][j];
                if (std::cin.fail())
                {
                    std::cin.ignore(32767, '\n');
                    std::cout << "Invalid input";
                    exit(0);
                }
            }
            catch (...)
            {
                std::cout << "Error" << std::endl;
            }
        }
    }
    return in;
}

Pole::Pole()
{
    m_row = 0; m_col = 0;
    m_data = nullptr;
}


Pole::Pole(int row, int col)
{

    m_row = row;
    m_col = col;

    m_data = new char* [row];
    for (int i = 0; i < row; ++i)
    {
        m_data[i] = new char[col];

        for (int j = 0; j < col; ++j)
            m_data[i][j] = '*';
    }
}


char* Pole::getLink(int row, int col)
{
    assert((row - 1 >= 0) && (col - 1 >= 0) && (row - 1 <= m_row) && (col - 1 <= m_col));
    return  &m_data[row - 1][col - 1];
}


void Pole::clear()
{
    for (int i{ 0 }; i < m_row; i++)
    {
        delete[] m_data[i];
    }

    delete[] m_data;

    m_row = 0;

    m_col = 0;

}