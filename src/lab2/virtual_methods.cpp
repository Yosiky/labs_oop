#include <iostream>

using namespace std;

class Figure {
public:
    virtual void showInfo() const {
        cout << "Base class Figure" << endl;
    }
};

class Circle : public Figure {
public:
    void showInfo() const override { /* You don’t need to write virtual if you write override */
        /* Implementation for Circle */
        cout << "Derived class Circle" << endl;
    }
};

class Square : public Figure {
public:
    void showInfo() const override {
        /* implementation for Square */
        cout << "Derived class Square" << endl;
    }
};

int main() {
	{
		Figure *anonim = new Figure(/* parameters */);
		anonim->showInfo();
	}
    {
        Figure *anonim = new Circle(/* parameters */);
        anonim->showInfo(); /* What will we see? */
    }
    {
        Figure *anonim = new Square(/* parameters */);
        anonim->showInfo(); /* What will we see? */
    }
    
    return (0);
}
