#include <sstream>
#include <map>

#include "myPole.h"
#include "myAnimal.h"


void addStack(std::string& var,const char& delim, std::vector<int>& my_vector)
{
    std::stringstream ss;
    ss << var;

    std::string spam;
    // используя поток stringstream, записываем
    while (std::getline(ss, spam, delim)) {
        my_vector.push_back(static_cast<int>(atof(spam.c_str())));
    }

}


// начинаем игру
// первыми ходят травоядные, затем хищники
void start(std::map<std::string, int>& dict, std::vector<Animal>& array_of_animals, Pole& pole, const int& len)
{
    // пробуем разместить зверей по их координатам на карте ( x, y )

    static int c = 0;
    // вывод начальной карты
    for (std::map<std::string, int>::iterator it = dict.begin(); it != dict.end(); ++it)
    {
        if (it->first == "herbivores")
            for (int i{ 0 }; i < it->second; i++)
            {
                int x = array_of_animals[i].getX();
                int y = array_of_animals[i].getY();
                *pole.getLink(x, y) = 'r';
                c++;
            }
        if (it->first == "hunters")
            for (int j{ c }; j < (it->second+c); j++)
            {
                int x = array_of_animals[j].getX();
                int y = array_of_animals[j].getY();
                *pole.getLink(x, y) = 'w';
            }
    }

    int count_of_steps = dict["count_of_steps"];
    int* see_on_moving_herbivore = new int[dict["herbivores"]];
    int* see_on_moving_hunter = new int[dict["hunters"]];


    for (int i{ 0 }; i < count_of_steps; i++)
    {   // для того, чтобы следить за элементом в массиве указателей
        int cc = 0;
        for (std::map<std::string, int>::iterator it = dict.begin(); it != dict.end(); ++it)
        {
            if (it->first == "herbivores")
            {
                // чтобы успешно при выводе можно было выводить -k и +k в клетках,
                // где k - это число хищников и жертв соответственно в одной точке,
                // необходимо чтобы поле было создано из элементов, где каждый элемент это строка, а не символ,
                // как представленно в данной программе, то есть заменить всё с char на std::string

                // этот цикл нужен для того, чтобы мы смогли определить
                // число травоядных в одной точке карты
                int local_counter = 1;
                std::vector<Animal> local_arr;
                local_arr.resize(dict["herbivores"]);

                for (int i_1{ 0 }; i_1 < static_cast<int>(local_arr.size()); i_1++)
                {
                    local_arr[i_1] = array_of_animals[i_1];

                    if (i_1 > 0) {
                        if (array_of_animals[i_1].getX() == array_of_animals[i_1 - 1].getX() && array_of_animals[i_1].getY() == array_of_animals[i_1 - 1].getY())
                            local_counter += 1;
                    }
                }
                
                char local_c[] = { 'r', char(48 + local_counter) };

                // если число травоядных больше чем 1, то выведем это число в данной точке
                *pole.getLink(local_arr[0].getX(), local_arr[0].getY()) = local_c[1];
                // выведем игровое поле для наглядности
                std::cout << pole << std::endl;
                
                // основной цикл движения
                for (int j{ 0 }; j < it->second; j++)
                {
                    // сначала узнаем координаты текущего животного
                    int x = array_of_animals[j].getX();
                    int y = array_of_animals[j].getY();

                    // смена направления движения при k шагов
                    if (see_on_moving_herbivore[j] == array_of_animals[j].getСyclicality())
                    {
                        if (array_of_animals[j].getDirection() == 0)
                            array_of_animals[j].setDirection(2);

                        else if (array_of_animals[j].getDirection() == 1)
                            array_of_animals[j].setDirection(3);

                        else if (array_of_animals[j].getDirection() == 2)
                            array_of_animals[j].setDirection(0);

                        else if (array_of_animals[j].getDirection() == 3)
                            array_of_animals[j].setDirection(1);
                        // если введено значение, выходящее за допустимые, установим 0
                        else
                            array_of_animals[j].setDirection(0);
                    }
                    // нарисуем в текущей точке звёзду, так как подразумеваем, что мы уже перешли на новую позицию
                    *pole.getLink(x, y) = '*';

                    // в зависимости от направления, переходим на новую позицию
                    if (array_of_animals[j].getDirection() == 1) // вправо
                    {
                        y = array_of_animals[j].getY() + array_of_animals[j].getSpeed();
                        if (y > dict["col"]) 
                            y = 1;
                    }

                    else if (array_of_animals[j].getDirection() == 0) // вверх
                    {
                        x = array_of_animals[j].getX() - array_of_animals[j].getSpeed();
                        if (x <= 0)
                            x = dict["row"];
                    }
                    else if (array_of_animals[j].getDirection() == 2) // вниз
                    {
                        x = array_of_animals[j].getX() + array_of_animals[j].getSpeed();
                        if (x > dict["row"])
                            x = 1;
                    }

                    else if (array_of_animals[j].getDirection() == 3) // влево
                    {
                        y = array_of_animals[j].getY() - array_of_animals[j].getSpeed();
                        if (y <= 0)
                            y = dict["col"];
                    }
                    // устанавливаем новые координаты текущего животного
                    array_of_animals[j].setX(x);
                    array_of_animals[j].setY(y);

                    // увеличиваем счётчик, чтобы следить за его положением внутри массива животных
                    cc++;

                    // размножаем травоядных
                    see_on_moving_herbivore[j] += 1;
                    if ((see_on_moving_herbivore[j] % 4 == 1) && (see_on_moving_herbivore[j] != 0))
                    { 
                        ++dict["count_of_animals"];
                        array_of_animals.resize(dict["count_of_animals"]);
                        ++dict["herbivores"];

                        std::vector<int> for_herbivores = { dict["row"], dict["col"], 2, 5 };
                        array_of_animals.push_back(Herbivore(for_herbivores, 0));
                    }

                    // на этом этапе ход животного закончился и мы увеличиваем его возвраст на 1
                    array_of_animals[j].happy_birthday_for_animal();

                    *pole.getLink(x, y) = 'r';
                    // если травоядному 10 лет, то удаляем его
                    if (array_of_animals[j].getAge() == 10)
                    {
                        --dict["herbivores"];
                        --dict["count_of_animals"];

                        array_of_animals.erase(array_of_animals.begin() + j);
                        *pole.getLink(array_of_animals[j].getX(), array_of_animals[j].getY()) = '*';
                    }

                }

            }
            // аналогичные действия с охотниками
            if (it->first == "hunters")
            {
                int local_counter = 1;
                std::vector<Animal> local_arr;
                local_arr.resize(dict["hunters"]);

                for (int i_2{ 0 }; i_2 < static_cast<int>(local_arr.size()); i_2++)
                {
                    local_arr[i_2] = array_of_animals[i_2+cc];

                    if ((i_2) > 0) {
                        if (array_of_animals[i_2].getX() == array_of_animals[i_2 - 1].getX() && array_of_animals[i_2].getY() == array_of_animals[i_2 - 1].getY())
                            local_counter += 1;
                    }
                }
                // если у нас больше чем два волка в клетке, то скажем, что их там n-штук
                if (local_counter >= 2)
                    *pole.getLink(local_arr[0].getX(), local_arr[0].getY()) = 'n';
                else if (local_counter == 2)
                    *pole.getLink(local_arr[0].getX(), local_arr[0].getY()) = char(48+local_counter);
                else
                    *pole.getLink(local_arr[0].getX(), local_arr[0].getY()) = 'w';
                // выведем игровое поле для наглядности
                std::cout << pole << std::endl;

                for (int k{ cc }; k < (it->second + cc); k++)
                {
                    int x = array_of_animals[k].getX();
                    int y = array_of_animals[k].getY();

                    // смена направления движения при k шагов
                    if (see_on_moving_hunter[k - cc] == array_of_animals[k].getСyclicality())
                    {
                        if (array_of_animals[k].getDirection() == 0)
                            array_of_animals[k].setDirection(2);

                        else if (array_of_animals[k].getDirection() == 1)
                            array_of_animals[k].setDirection(3);

                        else if (array_of_animals[k].getDirection() == 2)
                            array_of_animals[k].setDirection(0);

                        else if (array_of_animals[k].getDirection() == 3)
                            array_of_animals[k].setDirection(1);
                    }

                    *pole.getLink(x, y) = '*';

                    if (array_of_animals[k].getDirection() == 1) // вправо
                    {
                        y = array_of_animals[k].getY() + array_of_animals[k].getSpeed();
                        if (y > dict["col"])
                            y = 1;
                    }
                    else if (array_of_animals[k].getDirection() == 0) // вверх
                    {
                        x = array_of_animals[k].getX() - array_of_animals[k].getSpeed();
                        if (x <= 0)
                            x = dict["row"];
                    }

                    else if (array_of_animals[k].getDirection() == 2) // вниз
                    {
                        x = array_of_animals[k].getX() + array_of_animals[k].getSpeed();
                        if (x > dict["row"])
                            x = 1;
                    }
                    else if (array_of_animals[k].getDirection() == 3) // влево
                    {
                        y = array_of_animals[k].getY() - array_of_animals[k].getSpeed();
                        if (y <= 0)
                            y = dict["col"];
                    }
                    array_of_animals[k].setX(x);
                    array_of_animals[k].setY(y);

                    see_on_moving_hunter[k - cc] += 1;
                    array_of_animals[k].happy_birthday_for_animal();

                    *pole.getLink(x, y) = 'w';

                    if (array_of_animals[k].getAge() == 10)
                    {
                        --dict["hunters"];
                        --dict["count_of_animals"];

                        array_of_animals.erase(array_of_animals.begin() + k);
                        *pole.getLink(array_of_animals[k].getX(), array_of_animals[k].getY()) = '*';

                    }
                }
            }
        }
        // если в какой-то точке встретились волк и заяц, то
        // волк съедает зайца
        for (int i{ 0 }; i < len; i++)
        {
            if (i + 1 < len) {
                // проверяем на типы, чтобы мы точно поняли, что точно встретились волк и заяц
                if (strlen(array_of_animals[i].getName().c_str()) != strlen(array_of_animals[i + 1].getName().c_str())) {

                    int x1 = array_of_animals[i].getX();
                    int x2 = array_of_animals[i + 1].getX();
                    int y1 = array_of_animals[i].getY();
                    int y2 = array_of_animals[i + 1].getY();

                    if (x1 == x2 && y1 == y2)
                    {
                        if (array_of_animals[i].getName() == "rabbit")
                        {
                            if (array_of_animals[i].damage(100) <= 0)
                            {
                                array_of_animals.erase(array_of_animals.begin() + i);
                                --dict["herbivores"];
                                --dict["count_of_animals"];
                                *pole.getLink(x1, y1) = '*';
                                // охотник убивает жертву и автоматически насыщается
                                array_of_animals[i + 1].kill_now();
                            }
                            else
                                continue; // у волка не получилось съесть зайца, поэтому он ещё живёт
                        }
                        else
                            continue; // волк не может тронуть волка, как и зайцы друг друга
                        // если мы достигнули значения кратного 2
                        if (array_of_animals[i+1].getSpreak() % 1 == 1 && array_of_animals[i+1].getSpreak() != 0) 
                        {
                            // то добавим место в массиве животных
                            ++dict["hunters"];
                            ++dict["count_of_animals"];
                            array_of_animals.resize(dict["count_of_animals"]);

                            // и добавим в него ребёнка охотника, предварительно проинициализировав его
                            std::vector<int> for_hunter = { 1, 1, 2, 5 };
                            array_of_animals.push_back(Hunter(for_hunter, 100));
                        }
                        continue;
                    }
                }
            }
        }
    }
    // вывод конечного игрового поля
    std::cout << pole;

    see_on_moving_herbivore = nullptr;
    see_on_moving_hunter = nullptr;
}

void reduction(std::vector<Animal>& array_of_animals,const std::string& name, const int& count_of_animals)
{
    static int counter{ 0 };

    for (int k{ 0 }; k < count_of_animals; k++)
    {
        std::vector<int> for_animal;

        std::cout << "Enter a data of " << k + 1 << " " << name << " :";
        std::string data;
        std::getline(std::cin, data, '\n');

        std::stringstream ssn;
        ssn << data;

        std::string spam;
        while (std::getline(ssn, spam, ' ')) {
            for_animal.push_back(static_cast<int>(atof(spam.c_str())));
        }

        // можете попробовать сделать так:
        // array_of_animals.push_back(Herbivore(for_animal, 0))
        // но будет интересная семантическая ошибка, но я пока не придумал как её обойти
        if (name == "herbivores")
            array_of_animals[counter] = Herbivore(for_animal, 0);

        else if (name == "hunters")
            array_of_animals[counter] = Hunter(for_animal, 100);

        ++counter;
    }

}


// создаём "настройки" для каждого животного
int main()
{
    std::cout << "Hello!\nIt's a zoo.\nNow we have a Herbivores and Hunters\nThey will fight and kill each other!\n" <<
        "Add some animals to the zoo and watch their activities!" << std::endl;

    std::string settings;
    std::map<std::string, int> dictionary;
    std::vector<int> arr;
    std::vector<std::string> names;

    names = { "col", "row", "count_of_steps", "herbivores", "hunters" };

    std::cout << "For start, set an size of zoo and number of moves of all animals: ";
    getline(std::cin, settings, '\n');

    addStack(settings, ' ', arr);

    Pole pole(arr[0], arr[1]);
    std::cout << pole;

    std::cout << "Now give me number of Herbivores and Hunters, separatly: ";
    getline(std::cin, settings, '\n');
    
    addStack(settings, ' ', arr);

    for (int i{ 0 }; i < static_cast<int>(arr.size()); i++)
    {
        dictionary[names[i]] = { arr[i] };
    }
    dictionary["count_of_animals"] = dictionary["herbivores"] + dictionary["hunters"];

    //Animal* array_of_animals = new Animal[dictionary["count_of_animals"]];
    std::vector<Animal> array_of_animals;
    array_of_animals.resize(dictionary["count_of_animals"]);

    std::cout << "Okay, now enter a coordinates of animals in zoo with size " << arr[0] << "x" << arr[1] << std::endl;

    for (std::map<std::string, int>::iterator it = dictionary.begin();
        it != dictionary.end(); ++it)
    {
        if (it->first == "herbivores")
            reduction(array_of_animals, it->first, it->second);

        else if (it->first == "hunters")
            reduction(array_of_animals, it->first, it->second);

    }
    // запускаем игру
    start(dictionary, array_of_animals, pole, dictionary["count_of_animals"]);

    std::cout << "The end." << std::endl;
    return 0;
}
