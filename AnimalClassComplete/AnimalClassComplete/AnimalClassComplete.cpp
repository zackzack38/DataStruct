/* Week 2 Live Coding Content Outline
Classes
	Members
	Methods
	Public/Private/Protected
	    Friend function/class
	Instantiation
Inheritance
    Call Animal Class methods from Dog object
Static Class Member/Function
Polymorphism
	Virtual function - speak()
	Pure Virtual function (Abstract class)
Multiple Files
	Driver, header (include guards), implementation
    Makefile
*/

#include<string>
#include<iostream>
#include<vector>

class Animal {
    private:
        int height;
        int weight;
        std::string name;
        static int count;
    public:
        // Initializer list
        Animal(int _height = 0, int weight = 0, std::string name = "Default") :
            height(_height), weight(weight), name(name) { count++; }
        static void getCount() { std::cout << "There are " << count << " animals." << std::endl;}
        static void setCount(int c) { count = c; }
        int getHeight() const { return height; }
        int getWeight() const { return weight; }
        std::string getName() const { return name; }
        virtual void speak() const { std::cout << "Generic Animal sound" << std::endl; }
        // Pure virtual function, if I want to make Animal an abstract class
        //virtual void speak() const = 0;
};

// Initialize static variable
int Animal::count = 0;

class Dog : public Animal {
    private:
        std::string sound = "Woof";
        // If Animal private data members are changed to protected, the following works
        //std::string sound = "Woof, I weigh " + std::to_string(weight) + " pounds.";
    public:
        // Animal class constructed first. Initializer list.
        Dog(int h, int w, std::string n) : Animal(h, w, n) {}
        void speak() const { std::cout << sound << std::endl;}
};

class Cat : public Animal {
    private:
        std::string sound = "Meow";
        bool litterTrained;
    public:
        Cat(int h, int w, std::string n, bool litterTrained) : Animal(h, w, n) {
            this->litterTrained = litterTrained;
        }
        void speak() const {
            std::string sentence = sound;
            sentence += ". I am ";
            if (!litterTrained)
                sentence += "not ";
            sentence += "litter trained.";
            std::cout << sentence << std::endl;
        }
        // Friend function - not implemented in class, but elsewhere
        friend void setLitterTrained(Cat &c);
};

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