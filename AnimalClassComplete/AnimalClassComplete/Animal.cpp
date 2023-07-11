#include "Animal.h"

Animal::Animal(int _height, int weight, std::string name = "Default") :
    height(_height), weight(weight), name(name) {
        count++;
    }

void Animal::getCount() {
    std::cout << "There are " << count << " animals." << std::endl;
}

void Animal::setCount(int c) {
    count = c;
}

int Animal::getHeight() const {
    return height;
}

int Animal::getWeight() const {
    return weight;
}

std::string Animal::getName() const {
    return name;
}

void Animal::speak() const {
    std::cout << "Generic Animal sound" << std::endl;
}

// Initialize static variable
int Animal::count = 0;