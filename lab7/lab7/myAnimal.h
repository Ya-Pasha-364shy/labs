#pragma once
#include <string>
#include <vector>

class Animal
{
private:
    // координаты
    int x = 1;
    int y = 1;
    // направление
    int d = 0;
    // число ходов, через которое зверь меняет свое направление
    int k = 5;

protected:
    int m_health;
    int m_speed;
    int m_age;

    int my_damage;
    std::string name_of_animal;

    int killing_streak{ 0 };
public:
    // обычный параметризованный конструктор
    Animal(const int& mdmg = 0, const int& ag = 0, const int& hlth = 100, const int& spd = 1)
    {
        this->m_health = hlth;
        this->m_age = ag;
        this->m_speed = spd;
        this->my_damage = mdmg;
    }

    // конструктор копирования для размножения животных
    Animal(const Animal& anml)
    {
        this->m_health = anml.m_health;
        this->m_speed = anml.m_speed;
        this->m_age = anml.m_age;
        this->my_damage = anml.my_damage;
    }

    // x y d k
    Animal(std::vector<int>& arr, const int& mdgm)
    {
        this->m_health = 100;
        this->m_age = 0;
        this->my_damage = mdgm;

        for (int i{ 0 }; i < static_cast<int>(arr.size()); i++)
        {
            switch (i)
            {
            case 0:
                this->x = arr[i];
                break;
            case 1:
                this->y = arr[i];
                break;
            case 2:
                this->d = arr[i];
                break;
            case 3:
                this->k = arr[i];
                break;
            }
        }
    }

    virtual void happy_birthday_for_animal() { this->m_age += 1; }

    virtual int getAge() { return m_age; }

    virtual int getX() { return x; }

    virtual void setX(const int& a) { this->x = a; }

    virtual int getY() { return y; }

    virtual int damage(const int& d = 100)
    {
        m_health -= d;
        if (m_health <= 0)
            return 0;
        return 1;
    }

    virtual void setY(const int& b) { this->y = b; }

    virtual int getSpeed() { return m_speed; }

    virtual int getDirection() { return d; }

    virtual void setDirection(const int& var) { this->d = var; }

    virtual int getСyclicality() { return k; }

    virtual void kill_now() {}

    virtual int getSpreak() { return 0; }

    virtual std::string getName() { return name_of_animal; }

    virtual ~Animal() {}
};

class Herbivore : public Animal
{
public:
    Herbivore(const std::string& name, const int& mdmg, const int& hlth = 100, const int& spd = 1) : Animal(hlth, spd)
    {
        name_of_animal = name;
    }

    Herbivore(const Herbivore& hrbvr) : Animal(hrbvr)
    {
        name_of_animal = hrbvr.name_of_animal;
    }

    Herbivore(std::vector<int>& arr, const int& mdgm = 0) : Animal(arr, mdgm)
    {
        name_of_animal = "rabbit";
        this->m_speed = 1;
    }

};


class Hunter : public Animal
{
protected:
    int killing_streak{ 0 };

public:
    Hunter(const std::string& name, const int& mdmg = 100, const int& hlth = 100, const int& spd = 2) : Animal(hlth, spd)
    {
        name_of_animal = name;
    }

    Hunter(const Hunter& hunter) : Animal(hunter) {
        name_of_animal = hunter.name_of_animal;
    }

    Hunter(std::vector<int>& arr, const int& mdgm = 100) : Animal(arr, mdgm)
    {
        name_of_animal = "wolf";
        this->m_speed = 2;
    }

    void attack_to_wolf() { this->m_health -= 5; }

    void kill_now()
    {
        killing_streak++;
        // насыщается он тем, что текущий волк "меньше стареет"
        this->m_age--;
        // но в ходе битвы, его здоровье уменьшилось на 5 единиц
        attack_to_wolf();
    }

    int getSpreak() { return killing_streak; }

};
