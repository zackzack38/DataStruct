#include "Dog.h"

Dog::Dog(int h, int w, std::string n) : Animal(h, w, n) {

}

void Dog::speak() const {
    std::cout << sound << std::endl;
}