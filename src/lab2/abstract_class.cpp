#include <iostream>

class Figure {
public:
    virtual void printInfo(void) const = 0; /* You must to mark a function "<func> = 0" */
};

class Circle : Figure {
public:
    void printInfo(void) const override {
        std::cout << "It's Circle" << std::endl;
    }
};

class Square : Figure {
public:
    
    /* If function will be uncommented we don't get error in main() */
    // void printInfo(void) const override {
    //     std::cout << "It's Square" << std::endl;
    // }
};

int main() {
    Circle circle;
    Square square; /* We get error because printInfo() isn't overrided in Square */
}
