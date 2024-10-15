#include <iostream>

class Figure {
public:
    virtual void figureInfo() const = 0;
};

class Circle : public Figure {
public:
    void figureInfo() const override {
        std::cout << "Type is class Circle" << std::endl;
    }
};

class Square : public Figure {
public:
    void figureInfo() const override {
        std::cout << "Type is class Square" << std::endl;
    }
};

class Rectangle : public Figure {
    void figureInfo() const override {
        std::cout << "Type is class Rectangle" << std::endl;
    }
};

template <class T>
T *createFigure() {
    return new T;
}

int main() {
    Figure *ptr_circle = dynamic_cast<Figure *>(createFigure<Circle>());
    Figure *ptr_square = dynamic_cast<Figure *>(createFigure<Square>());
    Figure *ptr_rectangle = dynamic_cast<Figure *>(createFigure<Rectangle>());

    ptr_circle->figureInfo();
    ptr_square->figureInfo();
    ptr_rectangle->figureInfo();
}
