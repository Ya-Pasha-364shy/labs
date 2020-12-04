#include "myClass.h"
#include <string>
#include <stdexcept>
#include <vector>

// отнаследовать как минимум два класса
// и обработать исключения
// при обнаружении ошибки записывать информацию о ней в соответствующий типу ошибки класс
// и реализовать функцию print_error_list(vector<Ierror> err),
// которая будет выводить список всех ошибок 

class Ierror {
private:
	static int generator;

protected:
    string texterror;
	int count;

public:
    Ierror()
    {
        texterror = "";
    }

    Ierror(const string& name) {
        texterror = name;
		++generator;
		count = generator;
    }

    virtual void printError()
    {
        cout << texterror << endl;
    }

    int get_count()
    {
		return count;
    }

	friend void print_error_list(vector<Ierror> lst);

};

class Ierror1 : public Ierror {
public:
    Ierror1() : Ierror("Error1: Wrong size of new matrix!") {}
};

class Ierror2 : public Ierror {
public:
    Ierror2() : Ierror("Error2: No element with such indices exists!") {}
};

class Ierror3 : public Ierror {
public:
	Ierror3() : Ierror("Error3: Matrices must be of the same size!") {}
};


void print_error_list(vector<Ierror> erlst)
{	
	Ierror item = erlst.back();
	int len = item.get_count();

	for (int i{ 0 }; i < len; i++) {
		static_cast<Ierror*>(&erlst[i])->printError();
	}
}

int Ierror::generator = 0;

int main()
{   
	int n;
	Matrix m1, m2;

	Ierror1 err1;
	Ierror2 err2;
	Ierror3 err3;

	vector<Ierror> errLst;

	
	bool flag = true;
	while (flag)
	{
		cout << "0 - exit" << endl;
		cout << "1 - addition matrices" << endl;
		cout << "2 - subtract matrices" << endl;
		cout << "3 - multiply matrices " << endl;
		cout << "4 - transponce matrix " << endl;
		cout << "5 - resize matrix" << endl;
		cout << "6 - output matrix element" << endl;
		cout << "7 - change matrix element" << endl;
		cout << "8 - list of errors in full time of work" << endl;

		cin >> n;

		switch (n)
		{
			case 0:
			{
				flag = false;
				break;
			}
			case 1:
			{
				try
				{
					cout << "Enter a first matrix" << endl;
					cin >> m1;
					cout << "Enter a second matrix" << endl;
					cin >> m2;

					if ((m1.getRows() != m2.getRows()) || (m1.getColumns() != m2.getColumns()))
					{
						throw err3;
					}
				}
				catch (Ierror3 err3)
				{
					errLst.push_back(err3);
					continue;
				}
				cout << m1 + m2 << endl;
				break;
			}
			case 2:
			{
				try
				{
					cout << "Enter a first matrix" << endl;
					cin >> m1;
					cout << "Enter a second matrix" << endl;
					cin >> m2;

					if ((m1.getRows() != m2.getRows()) || (m1.getColumns() != m2.getColumns()))
					{
						throw err3;
					}
				}
				catch (Ierror3 err3)
				{
					errLst.push_back(err3);
					continue;
				}
				cout << m1 - m2 << endl;
				break;
			}
			case 3:
			{
				cout << "Enter a first matrix" << endl;
				cin >> m1;
				cout << "Enter a second matrix" << endl;
				cin >> m2;
				cout << m1 * m2 << endl;
				break;
			}
			case 4:
			{
				cout << "Enter a matrix for transponce" << endl;
				cin >> m1;
				m1.transpose();
				cout << m1 << endl;
				break;
			}
			case 5:
			{
				cout << "Enter a new matrix" << endl;
				cin >> m1;
				cout << "Choise a new size of matrix for resize!" << endl;
				int a, b;
				try
				{
					cin >> a >> b;
					if (a < 0 || b < 0) {
						throw err1;
					}
				}
				catch (Ierror1 err1)
				{
					errLst.push_back(err1);
					continue;
				}

				m1.setSize(a, b);
				cout << m1;

				break;
			}
			case 6:
			{
				int a, b;
				cout << "Enter a matrix" << endl;
				cin >> m1;
				cout << "Enter a number of matrix element" << endl;
				try
				{
					cin >> a >> b;
					if ((a < 0 || b < 0) || ((a - 1) >= m1.getRows() || (b - 1) >= m1.getColumns())) {
						throw err2;
					}
				}
				catch (Ierror2 err2)
				{
					errLst.push_back(err2);
					continue;
				}

				cout << m1.getItem(a, b) << endl;

				break;
			}
			case 7:
			{
				int a, b, c;
				cout << "Enter a matrix" << endl;
				cin >> m1;
				cout << "Enter item number and replacement value" << endl;
				cin >> a >> b >> c;
				*m1.getLink(a, b) = c;
				cout << m1 << endl;
				break;
			}
			case 8:
			{
				cout << "I have this errors now: ";
				print_error_list(errLst);
				break;
			}
		}
	}
    return 0;
}