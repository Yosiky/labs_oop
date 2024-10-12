# ООП лабораторная №3

Данная лабораторная работа будет посвещная изучению перегрузки операторов 
и методов в классе.

## Перегрузка конструкторов и операторов

Если мы хотим несколькими свособами создавать объекты, то можно определить 
несколько конструкторов с разными аргументами.

В примере мы перегрузили конструкторы таким образом, что бы наш класс
принимал два аргумента типа `float`, `std::pair`, состоящий из двух `float`
и пустой, устанавливающий значения равным `0`.

```c++
class Point {
    float x, y;
public:

    Point(float x, float y) /* Перегрузка конструктора */
        : x(x), y(y)
    { }

    Point(std::pair<float, float> pair)
        : x(pair.first), y(pair.second)
    { }

    Point()
        : x(0), y(0)
    { }
};
```

## Перегрузка операторов

### Список операторов доступных для перегрузки

Бинарные операторы:
+ - * / % ^ & | 
~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= <=>(since C++20) && || ++ -- , ->* -> ( ) [ ]

/* TODO: нужно подумать как лучше описать */

Когда появляется оператор в выражении и хотя бы один из его операндов
имеет тип класса или тип перечисления, то используется разрешение перегрузки 
для определения определяемой пользователем функции, которая должна 
быть вызвана, среди всех функций, сигнатуры которых соответствуют следующим:

| Expression | As member function | As non-member function | Example |
| :--------: | :----------------: | :--------------------: | :----- |
| @a         | (a).operator@( )   |	operator@(a)           | `!std::cin` calls `std::cin.operator!()` |
| a@b        | (a).operator@(b)   |	operator@(a, b)        | `std::cout << 42` calls `std::cout.operator<<(42)` |
| a=b        | (a).operator=(b)   | cannot be non-member   | Given `std::string s;`, `s = "abc";` calls `s.operator=("abc")` |
| a(b...)    | (a).operator()(b...) | cannot be non-member | Given `std::random_device r;`, `auto n = r();` calls `r.operator()()` |
| a[b...]    | (a).operator[](b...) | cannot be non-member | Given `std::map<int, int> m;`, `m[1] = 2;` calls `m.operator[](1)` |
| a->        | (a).operator->( )    | cannot be non-member | Given `std::unique_ptr<S> p;`, `p->bar()` calls `p.operator->()` |
| a@         | (a).operator@(0)     | operator@(a, 0)      | Given `std::vector<int>::iterator i;`, `i++` calls `i.operator++(0)` |

В этой таблице, @ - это заполнитель, представлюящий соответсвующие операторы:
- все префиксные операторы в `@a`
- все постфиксные операторы кроеме `->` в `a@`
- все инфиксные операторы в кроме `=` в `a@b`

Перегрузка операторов позволяет упростить работу с нашими классами.
Таким образом, перегрузка следующих операторов: `+`, `-`, `/`, `*` 
позволит нам использовать математические операции.

#### Перегрузка бинарных операторов как элемент класса

В случае перегрузки бинарного оператора внутри класса указывается
только второй (правый) аргумент, первый (левый) подставляется неявно
как `this`.

```c++
class Point {
    /* ... */ 
public:
    Point operator +(const Point &other) {
        return Point(x + other.x, y + other.y);
    }

    Point &operator +=(const Point &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point operator *(float factor) {
        return Point(x * factor, y * factor);
    }

    float operator *(const Point &other) {
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
}
```

#### Перегрузка бинарных операторов как не элемент класса

Если необходимо чтобы объект класса выступал левым аргументом, то оператор
перегружается вне класса. Тогда оба аргумента (и левый и правый)
указываются явно. Это единственный оправданный пример использования
`friend` (чтобы перегружаемый оператор имел доступ к полям класса,
если нет геттеров и сеттеров).

```c++
class Point {
    /* Declared variables */
public:
    float getX() const { return x; }
    float getY() const { return y; }
};

Point operator +(const Point &lft, const Point &rht) {
    return Point(lft.getX() + rht.getX(), lft.getY() + rht.getY());
}

Point operator *(const Point &lft, float rht) {
    return Point(lft.getX() * rht, lft.getY() * rht);
}

float operator *(const Point &lft, const Point &rht) {
    /* dot product */
    return lft.getX() * rht.getX() + lft.getY() * rht.getY();
}

int main()
{
    Point a(1, 2);
    Point b;

    Point s = a + b;
    Point t = s * 4;
}
```

#### Перегрузка унарных операторов как элемент класса

```c++
class Iterator {
private:
    int *ptr;

public:
    Iterator(int *ptr)
        : ptr(ptr)
    {}

    /* ++iter */
    Iterator &operator ++() {
        /* notiсe: return type is reference, we do not need to create new object */
        ptr++;
        return *this;
    }

    /* iter++ */
    Iterator operator ++(int) {
        /* notice: return type is value itself, we return new object */
        Iterator ret(ptr);
        ptr++;
        return ret;
    }
};
```

/* TODO: нужно перечитать */

Обратите внимание, в случае перегрузки унарного плюса нам не нужно
выполнять никаких действий и создавать новые объекты, поэтому просто
вернем ссылку на себя же без изменений. Но в таком случае возникает проблема:
 - если вернем не константную ссылку, то не сможем вызвать оператор
от константных объектов.
 - если вернем константную ссылку, то не сможем изменять полученый объект,
а это нелогиченое поведение оператора.

Поэтому реализуем оба варианта, это частая прктика делать отдельные
реализации пререгрузки операторов для константных и не константных объектов.

```c++
class Point {
public:
    float x;
    float y;

    /* ... */

    Point(float x, float y)
        : x(x), y(y)
    {}

    /* a = -b */
    Point operator -() const {
        return Point(-x, -y);
    }

    /* a = +b */
    const Point &operator +() const {
        return *this;
    }

    /* a = +b */
    Point &operator +() {
        return *this;
    }
};
```

## Конструктор копирования, оператор присваивания

```c++
class IntArray {
private:
    int *data;
    int size;

public:
    IntArray(int s) {
        data = new int[n]; /* allocate array of n integers */
    }

    ~IntArray() {
        delete data[]; /* free allocated memory */
    }

    /* create object as copy of other existing object */
    IntArray(const IntArray &other) {
        data = new int[other.size]; /* allocate array */

        for (int i = 0; i < other.size; i++) { /* copy contents */
            data[i] = other[i];
        }
    }

    /* assign currnet object to other existing object */
    IntArray &operator =(const IntArray &other) {
        delete data[]; /* we already have allocated memory, first free it */

        data = new int[other.size];
        for (int i = 0; i < other.size; i++) { /* copy contents */
            data[i] = other[i];
        }
    }
};
```

Что произойдет, если присвоить `IntArray` самому себе? Как это исправить?

## Перегрузка вывода в консоль

Для вывода данных в консоль стандартная бибилиотека c++ предоставляет поток
`std::cout` - высокоуровневую обертку над дескриптором стандартного вывода.

Поток перегружен для работы с основными типами языка:

```c++
#include <iostream>

int main()
{
    int i = 123;
    double d = 3.14;
    const char *s = "hello";

    std::cout << i << d << s << '\n';
}
```

Если необходимо печатать пользовательские классы в консоль - нужно перегрузить
оператор `<<` чтобы левый аргумент имел тип потока, а правый - тип пользовательского
класса. Возвращать из оператора принято ссылкк на поток, чтобы можно было использовть
печать в консоль по цепочке.
```c++
#include <iostream>

class Point {
private:
    float x;
    float y;

    /* ... */
}

std::ostream &operator <<(std::ostream &out, const Point &point)
{
    out << "(" << point.x << ", " << point.y << ")";
    return out;
}
```

Здесь используется базовый класс потоков `std::ostream`. Глобальная переменная
`std::cout` как раз имеет данный тип. Полученный оператор будет печатать в консоль
класс `Point` в формате `(123.34, 567.89)`

# Задание

В этой лабораторной работе Вы реализуете тип переменных с фиксированной точкой.
Для тестирования рекомендуется самостоятельно написать тесты, для проверки
Вашей работы. При желании можете использовать уже готовые библиотеки для этого.
Например: googletest(gtest) или любой другой фреймворк.

## 1. Класс Fixed

Файлы для реализации:
1. *fixed.hpp* - будет содержать объявление класса.
2. *fixed.cpp* - реализация методов и функции, объявленных в *fixed.hpp*.
3. *main.cpp* - место для Ваших тестов.

До сегодняшенго дня, все числа, используемые в Вашей программе, были
`int` и `float` или их варианты (`short`, `char`, `long`, `double` и т.д.).

Но сегодня, Вы изучите новый и замечательный числовой тип: числа с
фиксированной точкой. Данный тип отсутсвует в большинстве языках.
Тип с фиксированной точкой предоставляет драгоценный баланс межд
производительностью, точностью, диапазоном доступных чисел и кол-вом знаков
после запятой. Поэтому этот тип зачастую используется в графичесих, звуковых
или научных приложениях.

Сделайте канонический класс, реализующий числа с фиксированной точкой.

Имя класса: `Fixed`

Приватные поля:
- Переменная типа `int`, в нее будет сохранятся значение.
- Статическая константная переменая типа `int`, содержащая
кол-во бит отводимых под дробную часть.

Публичные поля:
- Конструктор по умолчанию, инициализирующий значением 0
- Деструктор
- Конструктор копирования
- Перегрузить оператор присваивания
- Метод `int getRawBits(void) const;`, возвращающий число в "сыром" виде,
  то есть как оно напрямую хранится в аттрибуте класса
- Метод `void setRawBits(const int);`, устанвлющий "сырое" значение напрямую в
  аттрибут класса.

### Мини тест
```c++
#include <iostream>

int main( void ) {
    Fixed a;
    Fixed b( a );
    Fixed c;

    c = b;
    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    std::cout << c.getRawBits() << std::endl;
    return 0;
}
```

### Результат должен напоминатиь что-то похожее
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
```

## 2. Дополнительные способы инициализации

Первое задание было хорошим стартом, но наш класс все еще бесполезен, т.к.
инициализировать его можем только занчениме `0.0`. Добавьте следующие
публичные конструкторы и методы в Ваш класс:

- Констукртор, принимающий константное целочисленное *(int)* число как параметр и
конвертирует его в соответствующее число с фиксированной точкой. Значение
дробных битов заполняйте так же как и в предыдущем задании.

- Конструктор, принимающий константное число с плавающей точкой *(float)* как параметр
и конвертирует его в соответсвтующее число с фиксированной точкой. Значение
дробных битов заполняйте так же как и в предыдущем задании.

- Метод `float toFloat(void) const;`, преобразовывающий число с фиксированной
точкой в число с плавающей точкой.

- Метод `int toInt(void) const;`, преобразовывающий число с фиксированной
точкой в целочисленное число.

Кроме этого Вам необходимо перегрузить следущий оператор в Ваших файлах.

- Перегрузите оператор `<<`, вставляющий в поток вывода число
с плавающей точкой, полученное с помощью метода `float toFloat(void) const`.

### Мини тест
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

### Результат
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

## 3. Больше возможностей

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

## 4. Калькулятор*

> Это задание со звездочкой. Можете не делать это задание, но оно будет
> полезным для выполнения.

Напиши програму вычисляющая простые арифметические выражения с помощью
чисел с фиксированной точкой.

> Пожалуйства, используйте `string`, `istream`, `ostream`, `istringstream` и
> `ostreamstring` как можно больше. Это поможет вам сохранить **МНОГО** времени
> при выполнении.

```c++
$> clang++ -Wall -Wextra -Werror -o eval_expr Fixed.class.cpp {your files}
$> ./eval_expr "( 18.18 + 3.03 ) * 2"
42.4219
$>
```