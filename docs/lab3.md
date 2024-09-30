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

В этой лабораторной работе Вы реализуете тип переменных с фиксированной точкой.
Для тестирования рекомендуется самостоятельно написать тесты, для проверки
Вашей работы. При желании можете использовать уже готовые библиотеки для этого.
Например: googletest(gtest) или любой другой фраемворк.

## Класс Fixed

Файлы для реализации:
1. *fixed.hpp* - будет содержать объявление класса.
2. *fixed.cpp* - реализация методов и функции, объявленных в *fixed.hpp*.
3. *main.cpp* - место для Ваших тестов.

До сегодняшенго дня, все числа, используемые в Вашей программе, были
`int` и `float` или их варианты (`short`, `char`, `long`, `double` и т.д.).

Но сегодня, Вы изучите новый и замечательный числовой тип: числа с фиксированной
запятой (fixed point). Данный тип отсутсвует в большинстве языках. Тип с
фиксированной запятой предоставляет драгоценный баланс между
производительностью, точностью, диапазоном, доступных чисел и кол-вом знаков
после запятой. Поэтому этот тип зачастую используется в графичесих, звуковых
или научных приложениях.

Сделайте канонический класс реализующий числа с фиксированной точкой.

Приватные поля:
- Переменная типа `int`, в нее будет сохранятся значение.
- Статическая константная переменая типа `int`, содержащая кол-во бит отводимых
под дробную часть.

Публичные поля:
- Конструктор по умолчанию, инициализирующий значением 0
- Деструктор
- Конструктор копирования
- Перегрузить конструктор присваивания
- Метод `int getRawBits(void) const;`, возвращающий число как оно хранится
/* TODO: надо подумать как лучше написать "that return the raw value of the
fixed point value" */
- Мектод `void setRawBits(const int);`, устанвлющий число в имеющуюся переменную

### Мини тест:
```c++
#include <iostream>

int main(void) {
    Fixed a;
    const Fixed b( 10 );
    const Fixed c( 42.42f );
    const Fixed d( b );

    a = Fixed( 1234.4321f );

    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;

    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;

    return 0;
}
```

### Результат:
```bash
$> clang++ -Wall -Wextra -Werror Fixed.class.cpp main.cpp
$> ./a.out
Default constructor called
Copy constructor called
Assignation operator called // <-- This line may be missing depending on your implementation
getRawBits member function called
Default constructor called
Assignation operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
$>
```

## Больше возможностей

Мы становимся все ближе к полноценному классу. /* TODO ... */
Перегрузите приведенные ниже операторы в вашем классе:

1. 6 операторов сравнения: `>`, `<`, `>=`, `<=`, `==`, `!=`
2. 4 арифметических операций: `+`, `-`, `*`, `/`
3. Операторы пре- и пост- инкремента, пре- и пост- декремента.
Можете увеличивать значение на удобное для вас значение, главное,
что бы `є` следовала следующему условию `2 > 1 + є > 1`

Также вам необходимо добавить функцию `min`, принмающую две ссылки
на объекты класса `FixedPoint` и возвращающее наименьшее из них.
Помимо этого, перегрузите эту функцию так, что бы она еще принимала
и константные объекты типа `FixedPoint` и константную ссылка на
наименьший элемент.

Тоже самое сделайте и для функции `max`, только вместо минимального
Вам следует возвращать максимальное значение.

### Небольшой тест для вашего кода:
```c++
#include <iostream>

int main( void ) {
    Fixed a;
    Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max( a, b ) << std::endl;
    return 0;
}
```

### Ваш вывод должен напоминать что-то похожее:
```bash
$> clang++ -Wall -Wextra -Werror Fixed.class.cpp main.cpp
$> ./a.out
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
$>
```

## Калькулятор

Напиши програму вычисляющая простые арифметические выражения с помощью
чисел с фиксированной точкой.

```c++
$> clang++ -Wall -Wextra -Werror -o eval_expr Fixed.class.cpp {your files}
$> ./eval_expr "( 18.18 + 3.03 ) * 2"
42.4219
$>
```