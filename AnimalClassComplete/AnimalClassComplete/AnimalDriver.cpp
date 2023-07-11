/* Week 2, Day 1 Live Coding Content Outline
Classes
	Members
	Methods
	Public/Private/Protected
	    Friend function/class
	Instantiation
Inheritance
    Call Animal Class methods from Dog object
Static Class Member/Function
*/

#include<string>
#include<iostream>
#include<vector>

#include "Animal.h"
#include "Dog.h"
#include "Cat.h"

// Demonstrate friend
void setLitterTrained(Cat &c) {
    // I have access to the private data member
    c.litterTrained = true;
    std::cout << c.getName() << " is now litter trained!" << std::endl;
};

std::vector<Animal*> pets;

void printPets() {
    std::cout << "Printing pets: " << std::endl;
    for(Animal* a : pets){
        // Showing Polymorphism
        std::cout << "My name is " << a->getName() << " and I say ";
        a->speak();
    }
}

int main() {

    // Instantiate the animals
    Dog d1(11, 20, "Fido");
    Dog d2(15, 28, "Lassy");
    Cat c1(9, 20, "Garfield", false);
    Animal a1(24, 50, "Generic Animal");

    // Cat is now litter trained using a function I defined
    c1.speak();
    setLitterTrained(c1);
    c1.speak();

    // Specific animal sounds
    //d1.speak();
    //c1.speak();
    //a1.speak();

    // Add the pets to the vector
    pets.push_back(&d1);
    pets.push_back(&d2);
    pets.push_back(&c1);
    pets.push_back(&a1);

    // Print the pets
    printPets();

    // Call static method
    Animal::getCount();

    // Inheritance
    // None of these methods are in the Dog class
    //std::cout << "Type is: " << typeid(d1).name() << std::endl;
    std::cout << "Hi, my name is " << d1.getName() << ". My height is: "
              << d1.getHeight() << " inches and my weight is "
              << d1.getWeight() << " pounds." << std::endl;

    return 0;
}