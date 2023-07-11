#ifndef __ANIMAL_H_
#define __ANIMAL_H_

#include<iostream>
#include<string>

class Animal {
    private:
        int height;
        int weight;
        std::string name;
        static int count;
    public:
        // Initializer list
        Animal(int _height, int weight, std::string name);
        static void getCount();
        static void setCount(int c);
        int getHeight() const;
        int getWeight() const;
        std::string getName() const;
        virtual void speak() const;
        // Pure virtual function, if I want to make Animal an abstract class
        //virtual void speak() const = 0;
};

#endif