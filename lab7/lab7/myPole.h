#pragma once
#include <iostream>
#include <cassert>

class Pole
{
private:
    int m_col;
    int m_row;

    char** m_data;

    void clear();

public:
    Pole();

    Pole(int col, int row);

    int getRows() const {
        return m_row;
    }

    int getColumns() const {
        return m_col;
    }

    // получение ссылки на элемент
    char* getLink(int row, int col);

    friend std::ostream& operator<<(std::ostream& out, const Pole& m);

    friend std::istream& operator>>(std::istream& in, Pole& m);

    ~Pole()
    {
        clear();
    }
};