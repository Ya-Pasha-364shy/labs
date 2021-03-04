#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>

// защита.
// делаем бинарный поиск, hanoi tower, числа Фибоначчи - динамическими
// Kruskala - a*: та же задача, но другой алгоритм поиска

std::mutex mutex;

void print_array(std::vector<double>& arr)
{
    for (const auto item : arr)
    {
        std::cout << item << " | ";
    }
    std::cout << std::endl;
}

void mySort(std::vector<double>& my_array) {

    int length = static_cast<int>(my_array.size());
    for (int i{ 0 }; i < length; i++)
    {
        int smlIdx = i;
        for (int j = smlIdx + 1; j < length; j++)
        {
            if (my_array[smlIdx] > my_array[j]) { smlIdx = j; }
        }

        std::swap(my_array[i], my_array[smlIdx]);
    }

    for (int i(0); i < static_cast<int>(my_array.size()); i++)
    {
        if (my_array[i] > 10)
            my_array[i] = 10;
        else
            continue;
    }
}

// Binary search with recursion
int binary_search_rec(std::vector<double>& current, int low, int high, int key)
{
    if (low > high) return -1;

    int mid = (low + high) / 2;
    if (key < current[mid])
        return binary_search_rec(current, low, mid - 1, key);
    else if (key > current[mid])
        return binary_search_rec(current, mid + 1, high, key);
    else
        return current[mid];
}

// Binary search without recursion
int binary_search(std::vector<double>& current_array, int key, int left, int right)
{
    int middle;
    while (true)
    {
        middle = (left + right) / 2;

        if (key < current_array[middle])
            right = middle - 1;
        else if (key > current_array[middle])
            left = middle + 1;
        else
            return middle;

        if (left > right)
            std::cout << "Product with that appetizing not found" << std::endl;
    }
}

// Fibonachi's numbers without recursion
// Many threads there
int generated_list(int number)
{
    std::atomic<bool> done(true);
    int a = 1, b = 1, c;
    
    std::thread my_thread([=, &done]() {
        std::lock_guard<std::mutex> lock(mutex);
        if (done) {
            if (number <= 2)
            {
                std::cout << a << std::endl;
            }
            else
                done = false;
        }});

    my_thread.join();
    atomic_thread_fence(std::memory_order_acquire);

    std::thread worked_thread([=, &done, &c, &a, &b]() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!done)
        {
            for (int i(3); i <= number; i++)
            {
                c = a + b;
                a = b;
                b = c;
            }
            std::cout << "It's equals:" << b << std::endl;
        }});

    worked_thread.join();

    return b;
}

// Fibonachi's numbers with recursion ( doesn't worked )
// Many threads there
int for_generated_list(int number)
{
    std::atomic<bool> done(true);
    int spam(0);


    std::thread first_thread([=, &spam, &done] () {
        std::lock_guard<std::mutex> lock(mutex);
        if (done) {
            if (number == 0)
            {
                spam = 0;
            }
            else if (number == 1)
            {
                spam = 1;
            }
            else
            {
                done = false;
            }
        }
        });

    first_thread.join();

    std::thread second_thread([=, &done, &spam] () {
        std::lock_guard<std::mutex> lock(mutex);
        if (!done) {
            spam = for_generated_list(number - 2) + for_generated_list(number - 1);
        }
        else
        {
            done = true;
        }
        });

    second_thread.join();

    return spam;
}


// Dynamic Fibonachi's numbers
std::vector<double> generated_lst(int number)
{
    std::vector<double> f;
    f[0] = 0, f[1] = 1; f[2] = 1;

    for (int i(3); i < number; i++)
    {
        f[i] = f[i - 1] + f[i - 2];
        std::cout << f[i] << std::endl;
    }
}


// Hanoi Towers
void hanoi_towers(int n, char Sour, char Aux, char Des)
{
    if (n == 1)
    {
        std::cout << "Move points " << n << " from " << Sour << " to " << Des << std::endl;
        return;
    }

    hanoi_towers(n - 1, Sour, Des, Aux);
    std::cout << "Move points " << n << " from " << Sour << " to " << Des << std::endl;
    hanoi_towers(n - 1, Aux, Sour, Des);
}

// Алгоритм на идее hanoi_towers.
// Здесь мы будем сортировать продукты по аппетитности
void hanoi_towers_new(int n, char Sour, char Aux, char Des, std::vector<double>& mass)
{
    int len = static_cast<int>(mass.size());
    for (int i(0); i < len; i++) {
        // сортируем только то, что наиболее аппетитнее/свежее
        if (mass[i] > 5)
        {
            hanoi_towers(n - 1, Sour, Des, Aux);
            std::cout << "Move points " << n << " from " << Sour << " to " << Des << std::endl;
        }
    }
}


// Объявляем структуру Ребро, 
// которой будем пользоваться для построения графа и дерева

// For Kruskal start
struct edge
{
    int x, y, w;
    edge() 
    {
        x = 0;
        y = 0;
        w = 0;
    }
    edge(int x, int y, int w) : x(x), y(y), w(w) {}
};

void print_edge(const edge& var)
{
    std::cout << "I searched a smallest edge!" <<
        "X: " << var.x << "\n" <<
        "Y: " << var.y << "\n" <<
        "Weight" << var.w << "\n";
}

bool cmp(const edge& a, const edge& b)
{
    return a.w < b.w;
}

std::vector<double> leader;

int getLeader(int x)
{
    if (x == leader[x])
        return x;

    return leader[x] = getLeader(leader[x]);
}

bool unite(int x, int y)
{
    x = getLeader(x);
    y = getLeader(y);

    if (x == y)
        return false;

    if (rand() % 2 == 0)
        std::swap(x, y);

    leader[x] = y;
    return true;
}
// For Kruskal stop

// Алгоритм Крускала 
// ( на защите переделал данный алгоритм под алгоритм a*)
void a_with_star()
{
    int n, m;
    // размерность графа и количество вершин
    std::cin >> n >> m;

    std::vector<edge> e(m);

    for (int i = 0; i < m; i++)
    {
        std::cout << "Enter a coordinats of current graph and his weight: ";
        std::cin >> e[i].x >> e[i].y >> e[i].w;
        e[i].x--;
        e[i].y--;
    }

    std::sort(e.begin(), e.end(), cmp);

    // устанавливаем id каждого из узла
    leader.resize(n);
    for (int i = 0; i < n; i++)
        leader[i] = i;

    std::vector<edge> ans;

    for (int i = 0; i < m; i++)
    {
        int x = e[i].x, y = e[i].y;

        if (unite(x, y))
            ans.push_back(e[i]);
    }
    
    edge remember_edge(1, 2, 3);
    for (int i(0); i < m; i++)
    {
        if (e[i].w < remember_edge.w)
        {
            remember_edge.x = e[i].x;
            remember_edge.y = e[i].y;
            remember_edge.w = e[i].w;
        }
        else
            continue;
    }
    print_edge(remember_edge);

}


int main()
{
    std::vector<double> array_of_fruits;

    std::cout << "Hi!\nGive me fruits with some appetinig (1..10)\n" <<
        "OR, you can skip this step and generate the list with the Fibonacci algorithm." <<
        "\nU want to exit? - press 0" << std::endl;

    int counter = 0;
    while (true)
    {

        int appetizing;
        std::cout << "Appetizing of " << counter << " fruit: ";
        std::cin >> appetizing;

        // заполняем массив
        if (appetizing == 0)
            break;
        else
            array_of_fruits.push_back(appetizing);

        counter++;
    }
    // сортируем
    mySort(array_of_fruits);

    // выводим
    print_array(array_of_fruits);
    std::cout << std::endl;


    // menu
    // можно завернуть в цикл, 
    // чтобы в одном окне можно было просмотреть работу более одного кейса.

    int choise;
    std::cout << "I must:\n1-binary search position in list\n2-generated fibonachi list\n" <<
        "3-Check products\n" <<
        "4-For food couriers! Find the shortest and cheapest way\n" <<
        "Your choise: ";
    std::cin >> choise;

    int lenght = static_cast<int>(array_of_fruits.size());
    int var_from_cmd;
    std::vector<double> n;

    switch (choise)
    {
    case 1:
        std::cout << "Ok, we have a list of your fruits.\n" <<
             "Please, give me some appetizing\n and i search his number in list: ";
        std::cin >> var_from_cmd;
        std::cout << "\nHis number is: " << binary_search(array_of_fruits, 0, lenght, var_from_cmd);
        break;

    case 2:
        std::cout << "Give me numbers of appetizing with Fibbonachi's Algorithm: ";
        std::cin >> var_from_cmd;
        
        n = generated_lst(var_from_cmd);
        /*
        std::cout << s;
        for (int i(s); i > 0; i-=5)
        {
            array_of_fruits.push_back(s);
        }
        */
        mySort(n);
        print_array(n);

        break;

    case 3:
        std::cout << "In Our list of products may be rot products.\n" <<
            "Let's check this with Hanoi algorihm!" << std::endl;
        std::cout << "Enter a number of points: ";
        std::cin >> var_from_cmd;
        hanoi_towers_new(var_from_cmd, 'A', 'B', 'C', array_of_fruits);
        break;

    case 4:
        a_with_star();
        break;

    default:
        std::cout << "I don't know this point, try again!" <<
            "\nChoise 1-4" << std::endl;
        break;
    }

    return 0;
}
