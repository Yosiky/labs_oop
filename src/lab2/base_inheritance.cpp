#include <iostream>
#include <string>

using namespace std;

class Figure {
private:
    string name;
protected:
    string type;
public:
    string color;

    void showInfo() const {
        cout << "NAME: " << name << endl;
        cout << "TYPE: " << type << endl;
        cout << "COLOR: " << color << endl;
    }

    Figure(const string &n="figure",
           const string &c="without",
           const string &t="default")
        :  name(n), color(c), type(t)
    {
        showInfo();
    } 

    ~Figure() = default; /* TODO */ 
};

class Circle : public Figure {
public:
    Circle() : Figure("circle") { 
        // name = "circle"; /* Can't use "name" because it's private attribute */
        color = "green";
        type = "public";
        showInfo();
    }
};

class Square : private Figure {
public:
    Square() : Figure("square") {
        // name = "square"; /* Can't use "name" because it's private attribute */
        color = "yellow";
        type = "private";
        showInfo();
    }
};

class Rectangle : protected Figure {
public:
    Rectangle() : Figure("rectangle") {
        // name = "Rectangle"; /* Can't use "name" because it's private attribute */
        color = "red";
        type = "protected";
        showInfo();
    }
};

/* templates will be studied in the future */
template <class T> 
void printInfo(const T *obj) {
    cout << "NAME: " << obj->name << endl;
    cout << "TYPE: " << obj->type << endl;
    cout << "COLOR: " << obj->color << endl;
}

int main() {
    Figure f;
    // printInfo(&f); /* uncomment this line and build with error in printInfo() */

    /* uncomment only these lines and build with error in printInfo() */
    // Circle c;
    // printInfo(&c); 

    /* uncomment only these lines and build with error in printInfo() */
    // Square s;
    // printInfo(&s);

    /* uncomment only these lines and build with error in printInfo() */
    // Rectangle r;
    // printInfo(&r);
}
