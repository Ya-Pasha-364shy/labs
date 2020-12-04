#include <map>
#include <sstream>
#include <fstream>
#include "myTestClass.h"

// Этот тестовый класс нигде не используется пока что
class ErrorTestClass1 : public ErrorTestClass {
public:
    ErrorTestClass1() : ErrorTestClass("Invalid lenght") {}
};

class ErrorTestClass2 : public ErrorTestClass {
public:
    ErrorTestClass2() : ErrorTestClass("Its impossible!") {}
};

using namespace std;


class Stack {
public:
    // Числовой стек
    vector<double> stck;
    // Словарь
    map<string, double> commands_with_data;

    Stack() {}

    // положить значение на вверх в стеке
    void push(double var1)
    {
        stck.push_back(var1);
    }

    // забрать значение с вершины стека
    void pop() { stck.pop_back(); }

    // забрать определённое значение в стеке
    void pop(string key)
    {
        commands_with_data[key] = stck.back();
        stck.pop_back();
    }

    // распечатываем верхний элемент в стеке
    void print() {
        int current_elem = size(stck) - 1;
        cout << "Result equals: " << stck[current_elem] << endl;
    }

    ~Stack() {}

};

// создаем возможность сохранять данные из консоли

class CommandsFrom
{
protected:
    // вектор, который будет представлять собой набор элементов, составляющих команду
    vector<string> cmds;

public:
    virtual void inputCommands() {}
    virtual void getCommandsFromFile(char* fName) {}

    // создаем массив из команд
    vector<string>& splitCommand(const string& s, char delim, vector<string>& elems) {

        // используем поток stringstream, так как он отлично подходит для того, чтобы 
        // записывать элементы в конец
        stringstream ss;
        ss << s;

        string item;
        // используя поток stringstream, записываем
        while (getline(ss, item, delim)) {
            // благодаря функционалу stringstream, в переменную
            // item запишется i-ый (i = {0, 1, 2, ...}) элемент строки пока не начнется пробел
            // и перейдёт к следующему
            elems.push_back(item);
        }

        return elems;
    }
};


class Calculator : public CommandsFrom
{
private:
    Stack current_stack;
    vector<ErrorTestClass> errLst;

public:
    Calculator() {}

    // ввод команд с консоли
    void inputCommands()
    {
        string cmd;
        do
        {
            getline(cin, cmd, '\n');
            cmds.push_back(cmd);

        } while (cmd != "0");
    }

    // берем список команд с файла и записываем их в вектор, построчно
    void getCommandsFromFile(char* fName)
    {
        ifstream file(fName);
        string cmd;

        // открываем файл и записываем строки в cmd, после чего
        // вставляем их в список cmds
        while (getline(file, cmd, '\n'))
        {
            cmds.push_back(cmd);
        }
    }

    void start()
    {
        for (auto cmd : cmds)
        {
            vector<string> elems;
            // создаем вектрор из элементов, составляющих синтаксис введённой/полученной команды
            elems = splitCommand(cmd, ' ', elems);
            // for example: vector<string> elems { 'DEFINE', 'a', '4' }

            int len = elems.size();
            int len_of_stack = current_stack.stck.size();

            if ((elems[0] == "DEFINE"))
            {
                try
                {
                    if (len == 3) {
                        // создаем пару ключ - значение
                        // ключ - строка; значение - число с плавающей точкой
                        current_stack.commands_with_data[elems[1]] = atof(elems[2].c_str());
                    }
                    else
                    {
                        ErrorTestClass2 err2;
                        throw err2;
                    }
                }
                catch (ErrorTestClass2 err2)
                {
                    errLst.push_back(err2);
                }


            }
            else if ((elems[0] == "PRINT") && current_stack.commands_with_data.size() > 0)
            {
                current_stack.print();
            }
            else if ((elems[0] == "PUSH") && (len == 2))
            {
                // если аргумент PUSH - строка, то 
                if (atof(elems[1].c_str()) == NULL)
                    current_stack.push(current_stack.commands_with_data[elems[1]]);
                // иначе, если число, то 
                else (current_stack.push(atof(elems[1].c_str())));

            }
            else if ((elems[0] == "POP") && (len_of_stack > 0))
            {
                if (len == 2)
                {
                    map<string, double>::iterator it;
                    for (it = current_stack.commands_with_data.begin(); it != current_stack.commands_with_data.end(); it++)
                        if (elems[1] == it->first)
                            current_stack.pop(elems[1]);
                }
                else current_stack.pop();
            }
            else if ((elems[0] == "+") && (len_of_stack >= 2))
            {
                current_stack.push(current_stack.stck[len_of_stack - 1] + current_stack.stck[len_of_stack - 2]);
            }
            else if ((elems[0] == "-") && len_of_stack >= 2)
            {
                current_stack.push(current_stack.stck[len_of_stack - 1] - current_stack.stck[len_of_stack - 2]);
            }
            else if ((elems[0] == "*") && len_of_stack >= 2)
            {
                current_stack.push(current_stack.stck[len_of_stack - 1] * current_stack.stck[len_of_stack - 2]);
            }
            else if ((elems[0] == "/") && len_of_stack >= 2)
            {
                current_stack.push(current_stack.stck[len_of_stack - 1] / current_stack.stck[len_of_stack - 2]);
            }
            else if ((elems[0] == "SQRT") && len_of_stack >= 1)
            {
                current_stack.push(sqrt(current_stack.stck[len_of_stack - 1]));
            }
            else if (elems[0] == "0")
            {
                exit(0);
            }
            else if (elems[0] == "1")
            {
                cout << "I have this errors now: ";
                print_error_list(errLst);
                exit(0);
            }
        }
    }
    ~Calculator() {}
};

int ErrorTestClass::generator = 0;

int main()
{
    Calculator calc;
    char* choise = new char[1];


    cout << "Hi!\nIt's a stack calculator\nHere you can enter data from the console\nor use a prepared template\n" <<
        "1 - use the manual way\n" << "2 - use the commands1.txt or commands2.txt template:";

    cin.getline(choise, 12);

    if (*choise == '1')
    {
        calc.inputCommands();
        calc.start();
    }
    else if (*choise == '2')
    {
        char name[256];
        cout << "Okay, now enter name of using text file: ";
        cin.getline(name, 256, '\n');

        calc.getCommandsFromFile(name);
        calc.start();
    }

    choise = nullptr;
    return 0;
}
