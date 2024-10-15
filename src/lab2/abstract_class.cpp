#include <iostream>

class Figure {
public:
    virtual void printInfo(void) const = 0; /* You must to mark a function "<func> = 0" */
};

/*
 * If you don't say a type of inheritance, then the type will be used default:
 * - public for structs
 * - private for classes
 */
struct Circle : Figure {
    void printInfo(void) const override {
        std::cout << "It's Circle" << std::endl;
    }
};

struct Square : Figure {

    /* If function will be uncommented we don't get error in main() */
    void printInfo(void) const override {
        std::cout << "It's Square" << std::endl;
    }
};

int main() {
    Circle circle;
    Square square; /* We get error because printInfo() isn't overrided in Square */
    circle.printInfo();
    square.printInfo();
}
