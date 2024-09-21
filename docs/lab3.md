# ООП лабораторная №3

## Перегрузка операторов

```c++
struct Point {
    float x;
    float y;

    Point(float x, float y)
        : x(x), y(y)
    {}

    Point(std::pair<float, float> pair)
        : x(pair.first), y(pair.second)
    {}

    Point()
        : x(0), y(0)
    {}

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

Point operator *(float factor, Point other) {
    return Point(other.x * factor, other.y * factor);
}
```

При перегрузке бинарного оператора оператора указывается только второй (правый) аргумент, первый (левый) подставляется неявно как this.	
Если необходимо чтобы объект класса выступал левым аргументом, то оператор перегружается вне класса. Тогда оба аргумента (и левый и правый) указываются явно

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
