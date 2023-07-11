#ifndef __DOG_H_
#define __DOG_H_

#include<string>
#include<iostream>
#include "Animal.h"

class Dog : public Animal {
    private:
        std::string sound = "Woof";
        // If Animal private data members are changed to protected, the following works
        //std::string sound = "Woof, I weigh " + std::to_string(weight) + " pounds.";
    public:
        // Animal class constructed first. Initializer list.
        Dog(int h, int w, std::string n);
        void speak() const;
};

#endif