# ООП лабораторная №3

## Перегрузка операторов, конструкторов

```c++
struct Point {
    float x;
    float y;
};
```
Если мы хотим несколько свособов создать объект - можно определить несколько конструкторов с разными аргументами.

```c++
struct Point {
    /* ... */

    Point(float x, float y)
        : x(x), y(y)
    {}

    Point(std::pair<float, float> pair)
        : x(pair.first), y(pair.second)
    {}

    Point()
        : x(0), y(0)
    {}
};
```

Перегрузка операторов позволяет применять математические операторы к пользовательским классам
```c++
struct Point {
    /* ... */

    Point operator +(Point other) {
        return Point(x + other.x, y + other.y);
    }

    Point &operator +=(Point other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point operator *(float factor) {
        return Point(x * factor, y * factor);
    }

    /* … */

    float operator *(Point other) {
        /* dot product */
        return x * other.x + y * other.y;
    }
};

int main()
{
    Point a(1, 2);
    Point b;

    Point s = a + b;
    Point t = s * 4;
    float f = t * 2.0;
}
```

При перегрузке бинарного оператора оператора указывается только второй (правый) аргумент, первый (левый) подставляется неявно как `this`.	
Если необходимо чтобы объект класса выступал левым аргументом, то оператор перегружается вне класса. Тогда оба аргумента (и левый и правый) указываются явно. Это единственный оправданный пример использования `friend` (чтобы перегружаемый оператор имел доступ к полям класса).

```c++
struct Point {
private:
    float x;
    float y;
    
    /* ... */

public:
    friend Point operator *(float factor, Point other);
};

Point Point::operator *(float factor, Point other) {
    return Point(other.x * factor, other.y * factor);
}
```

template <class T>
class Iterator {
    T *ptr;

public:
    Iterator(T *ptr)
        : ptr(ptr)
    {}

    T &operator ++() {
        /* ++iter */
        ptr++;
        return *this;
    }

    T operator ++(int) {
        /* iter++ */
        Iterator ret(ptr);
        ptr++;
        return ret;
    }
};

Перегрузка унарных операторов и инкремента/декремента происходит особым образом.



# Задания

В этой лабораторной работе мы реализуем тип переменных с фиксированной точкой.
