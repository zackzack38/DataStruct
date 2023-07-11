#include "Cat.h"

Cat::Cat(int h, int w, std::string n, bool litterTrained) : Animal(h, w, n) {
    this->litterTrained = litterTrained;
}
void Cat::speak() const {
    std::string sentence = sound;
    sentence += ". I am ";
    if (!litterTrained)
        sentence += "not ";
    sentence += "litter trained.";
    std::cout << sentence << std::endl;
}

