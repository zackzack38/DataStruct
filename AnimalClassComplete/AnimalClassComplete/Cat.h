#ifndef __CAT_H_
#define __CAT_H_

#include<iostream>
#include<string>
#include "Animal.h"

class Cat : public Animal {
    private:
        std::string sound = "Meow";
        bool litterTrained;
    public:
        Cat(int h, int w, std::string n, bool litterTrained);
        void speak() const;
        // Friend function - not implemented in class, but elsewhere
        friend void setLitterTrained(Cat &c);
};

#endif