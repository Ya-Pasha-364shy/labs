#include <iostream>
#include <string>
// #include <vector>

/*
In this cpp file, i realize general principles of OOP.
Have a nice time there !
*/

class Fruits
{
private:
    int count_of_fruits;

protected:
    std::string name;

    // color of current fruit
    std::string color;

    // tasty: 0..10
    double tasty;

    // appetizing: 0..100
    double appetizing;

public:

    Fruits()
    {
        this->name = "some strange fruit";
        this->color = "some strange color";
        this->appetizing = 50;
        this->tasty = 5;
    }


    Fruits(std::string n, std::string cr, double t, double a)
    {
        this->name = n;
        this->color = cr;
        this->tasty = t;
        this->appetizing = a;
    }

    Fruits(const Fruits& fruit)
    {
        this->name = fruit.name;
        this->color = fruit.color;
        this->appetizing = fruit.appetizing;
        this->tasty = fruit.tasty;
    }


    virtual void print_current_fruit()
    {
        std::cout << "This current fruit has name: " << this->name << std::endl;
        std::cout << "With charactristics:  " << std::endl;
        std::cout << "Tasty: " << this->tasty << "\n" << "appetizing:" << this->appetizing << "\n" <<
            "And color: " << this->color;
    }

    virtual void setCount(int cc)
    {
        count_of_fruits = cc;
    }

    virtual int getCounter()
    {
        return count_of_fruits;
    }

    virtual ~Fruits()
    {
        std::cout << " Fruit was destructed :( " << std::endl;
    }
};

class Apple : public Fruits
{
public:
    Apple(std::string n, std::string cr, double t, double a)
        : Fruits(n, cr, t, a)
    {
        std::cout << "Apple has been constructed ! " << std::endl;
    }

    void print_current_fruit()
    {
        std::cout << "This is" << this->name << std::endl;
        std::cout << "With charactristics:  " << std::endl;
        std::cout << "Tasty: " << this->tasty << "\n" << "appetizing" << this->appetizing << "\n" <<
            "And color: " << this->color;
    }

    virtual ~Apple()
    {
    }
};

class Banana : public Fruits
{
private:


public:
    Banana(std::string n, std::string cr, double t, double a)
        : Fruits(n, cr, t, a)
    {
        std::cout << "Banana has been constructed ! " << std::endl;
    }

    void print_current_fruit()
    {
        std::cout << "This is" << this->name << std::endl;
        std::cout << "With charactristics:  " << std::endl;
        std::cout << "Tasty: " << this->tasty << "\n" << "appetizing" << this->appetizing << "\n" <<
            "And color: " << this->color;
    }

    virtual ~Banana()
    {
    }
};


int main()
{
    //std::vector<Fruits> lst(5);

    Fruits* lst = new Fruits[5];

    for (int i(0); i < 5; i++)
    {
        if (i % 2 == 0)
            lst[i] =
            Apple("my tasty apple", "red", 7.5, 99);
        else
            lst[i] =
            Banana("my tasty banana", "yellow", 10, 100);
        lst[i].setCount(i + 1);
    }

    for (int i(0); i < 5; i++)
    {
        lst[i].print_current_fruit();
        lst[i].getCounter();
    }
    /*
    lst[4].count_of_fruits;
    */
    return 0;
}



/* DEFENSE
   Here's more automated code above
*/

/*
    class Fruits
    {
    protected:
        std::string name;

        // color of current fruit
        std::string color;

        // tasty: 0..10
        int tasty;


    public:

        Fruits()
        {
            this->name = "some strange fruit";
            this->color = "some strange color";
            this->tasty = 5;
        }


        Fruits(std::string n, std::string cr, int t)
        {
            this->name = n;
            this->color = cr;
            this->tasty = t;
        }

        Fruits(std::string n, int t)
        {
            this->name = n;
            this->color = "green";
            this->tasty = t;
            //this->type = tof;
        }

        virtual void print_current_fruit()
        {
            std::cout << "This current fruit has name: " << this->name << std::endl;
            std::cout << "With charactristics:  " << std::endl;
            std::cout << "Tasty: " << this->tasty << "\n" <<
                "And color: " << this->color;
        }


        virtual ~Fruits()
        {
            std::cout << " Fruit was destructed :( " << std::endl;
        }
    };


    class Warehouse : public Fruits
    {
    protected:
        std::string type_of_fruit;

    public:
        Warehouse() {}

        Warehouse(std::string tof, std::string n, std::string cr, int t) :
            Fruits(n, cr, t)
        {
            this->type_of_fruit = tof;
        }

        Warehouse(std::string tof, std::string n, int t) :
            Fruits(n, t)
        {
            this->type_of_fruit = tof;
        }

        virtual void print_current_fruit()
        {
            std::cout << "This current fruit has name: " << this->name << std::endl;
            std::cout << "With charactristics:  " << std::endl;
            std::cout << "Tasty: " << this->tasty << "\n" <<
                "color: " << this->color << "\n" <<
                "type: " << this->type_of_fruit << "\n";
        }


    };


    class Price : public Warehouse
    {
    protected:
        int current_price_of_obj;

    public:
        Price(std::string tof, std::string n, std::string cr, int t)
            : Warehouse(tof, n, cr, t)
        {
        }

        void setPriceOnType()
        {
            for (int i(1); i < 11; i++)
            {
                if (this->tasty = i)
                {
                    this->current_price_of_obj = i + 5;
                }
                else
                {
                    continue;
                }
            }
        }

        virtual void print_current_fruit()
        {
            std::cout << "This current fruit has name: " << this->name << std::endl;
            std::cout << "---CHARACTERS---" << std::endl;
            std::cout << "Tasty: " << this->tasty << "\n" <<
                "type: " << this->type_of_fruit << "\n" <<
                "Price of this fruit" << this->current_price_of_obj << std::endl;
        }

    };

    class Trade : public Price
    {
    private:
        int result;

    public:
        Trade(std::string tof, std::string n, std::string cr, int t)
            : Price(tof, n, cr, t)
        {

        }

        virtual void print_current_fruit()
        {
            std::cout << "This current fruit has name: " << this->name << std::endl;
            std::cout << "------CHARACTERS------" << std::endl;
            std::cout << "color: " << this->color << "\n" <<
                "type: " << this->type_of_fruit << "\n" <<
                "Price of this fruit" << this->current_price_of_obj << std::endl;
        }
    };


    int main()
    {
        //std::vector<Fruits> lst(5);


        Trade instance("beautiful", "my apple", "red", 10);

        instance.print_current_fruit();


        return 0;
    }
*/