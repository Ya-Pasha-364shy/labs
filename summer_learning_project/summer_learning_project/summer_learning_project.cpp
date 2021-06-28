#include <iostream>

class Elementary
{
private:
    int m_len;
    int* m_list;
    int m_element;
    int count;

public:
    Elementary(const int& element, const int& l): m_element(element), m_len(l) {
        this->count = 0;
        this->m_list = new int[m_len] {0};

        m_list[count] = m_element;
    }

    bool push_element(int new_element) {
        this->m_element = new_element;
        this->count++;

        if (count != m_len) {
            std::cout << "***\nMessage: For full massiv " << (m_len- 1) - count << " elements\n***";
            m_list[count] = this->m_element; return true;
        }
        else { std::cout << "Full massiv!\n"; this->print_massiv(); return false; }
    }

    bool pop_element(int elem) {
        this->count--;

        for (int i(0); i != m_len; i++)
            if (m_list[i] == elem) {
                m_list[i] = 0; return true;
            }
        return false;
    }

    void print_massiv() {
        std::cout << "[";

        for (int i(0); i != (m_len - 1); i++)
            std::cout << m_list[i] << "; ";

        std::cout << m_list[m_len - 1] << "]" << std::endl;
    }

    ~Elementary() {
        delete[] m_list;
    }
};


int main()
{
    std::cout << "Welcome to the list creator!" << "\n" << "Enter a lenght of your list: ";
    int first;
    std::cin >> first;

    std::cout << "Choose first integer element: ";
    int item;
    std::cin >> item;

    Elementary my_workspace(item, first);

    bool flag = true;
    while (flag)
    {
        std::cout << "Chose the option:\n1-Continue push elements\n2-Print the massiv\n3-Delete element\nYour choise:";
        std::cin >> first;

        switch (first)
        {
        case 1:
        {
            try {
                std::cout << "Enter an integer value: ";
                std::cin >> item;

                flag = my_workspace.push_element(item);

                break;
            }
            catch (...) { return 1; }
        }
        case 2:
        {
            my_workspace.print_massiv();
            break;
        }

        case 3:
        {
            std::cout << "Okay, now, we have massiv: "; my_workspace.print_massiv();
            std::cout << "Choise element for pop instruction: "; std::cin >> item;
            
            if (my_workspace.pop_element(item))
                std::cout << "Success !" << std::endl;
            else std::cout << "This value is not valid !" << std::endl;
            break;
        }

        default:
            break;
        }
    }

    std::cout << "Goodbye!\nHave a nice day!";
    return 0;
}


