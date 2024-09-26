# ООП лабораторная 1

> **ООП** - объектно ориентированное программирование.  
> **Атрибуты** класса - это переменные, объявленные внутри класса.  

## Общая информация

```c++
/* Discuss about structure size */
struct S {
    int x;
    double d;
}; /* sizeof(S) == 16 */

struct S {
    int a, b, c;
}; /* sizeof(S) == 12 */

/* Which size is here? */
struct S {
    int x;
    int y;
    double d;
}; /* sizeof(S) == 16 */

struct tree {
    struct node {
        node *left;
        node *right;
        void *data;
   }; /* sizeof(node) == 24 */
   
   node root;
   long size;
}; /* sizeof(tree) == 32 */
/* P.S.: here we are defining a sub-class, and using it as class member. */
```

## Выравнивание

```c++
struct S {
    long x; /* bytes: [0 .. 7] */
    short y; /* bytes: [8 .. 9] */
    char z; /* bytes: [10] */
    /* gap from [11 .. 15] */
}; /* sizeof(S) == 16 */
```

Размер структуры всегда кратен наибольшему элементу структуры. В данном случае -  после `char z` нет других полей, а значит размер структуры будет увеличен с 11 байт до ближайшего числа кратного восьми - 16 байт.

Поле стукткры должно начинаться с байта, кратного его размеру, для этого между полями структуры компилятор может вставлять пропуски, т.к. менять местами поля по стандарту компилятор не имеет права.

```c++
struct S {
    char a; /* byte: [0] */
    /* gap byte: [1] */
    short b; /* bytes: [2 .. 3] */
    /* gap bytes: [4 .. 7] */
    long d; /* bytes: [8 .. 15] */
}; /* sizeof(S) == 16 */
```

## Обращение к элементам класса

Обращение ко всем атрибутам и методам осуществляется с помощью `"."` или `"->"`.
Выбор зависит от того является ли это объектом или указателем на объект.

### Пример простого класса

```c++
class Circle {
public:
    double x;
    double y;
    double radius;
    std::string color;
};

void show_info(const Circle *circle) {
    /* circle is a pointer so we use "->" */
    std::cout << "Circle's info:" << std::endl;
    std::cout << "\tCoordinate: x = " << circle->x << ", y = " << circle->y << std::endl;
    std::cout << "\tRadius = " << circle->radius << std::endl;
    std::cout << "\tColor =  " << circle->color << std::endl;
}

int main()
{
    // Circle c{0, 0, 3, "blue"}; /* Aggregate initialization */
    Circle c;

    c.x = 0; /* c is an object so we use "." */
    c.y = 0;
    c.radius = 3;
    c.color = "Blue";

    show_info(&c);
}
```

## Методы, ключевое слово this

> **Методы** - это функции, объявленные внутри класса.  

Что разрешено:
- Объявление в любом порядке в теле класса. 
- Внутри методов можно вызывать другие методы, принадлежащие этому классу.
- Определние методов можно делать вне тела класса (но объявление по прежнему должно быть внутри).
- Создание других классов и структур внутри. А также `union`, `enum`.
- Нельзя создавать новые `namespace` внутри классов.

Что запрещено:
- Нельзя объявлять `namespace` внутри класса.

```c++
class Circle {
    /* ... */

public:
    double area() {
        return M_PI * radius * radius;
    }

    double length() {
        return 2 * M_PI * this->radius;
    }

    void showInfo(); /* Declaration */
};

void Circle::showInfo() { /* Definition */
    std::cout << "Circle's info:" << std::endl;
    std::cout << "\tCoordinate: x = " << x << ", y = " << y << std::endl;
    std::cout << "\tRadius = " << radius << std::endl;
    std::cout << "\tColor =  " << color << std::endl;
}
```


> `this` - Ключевое слово, доступное внутри определения класса, которое 
> имеет тип указателя на текущий экземпляр класса. В константных 
> методах - тип указателя константный.

## Инкапсуляция

> **Инкапсуляция** – это способ сокрытия информации от внешнего мира.

Подробнее рассмотрим на примере.

## Модификаторы доступа public and private, геттеры, сеттеры

> `public` - говорит, что всё, объявленное ниже может быть доступно 
> из вне класса.  
> `private` - говорит, что всё, объявленное ниже может быть использовано 
> только внутри класса.  

> **Геттеры (getters)** - так называются методы, возвращающие значения 
> имеющихся в классе атрибутов.  
> **Сеттеры (setters)** - так называются методы, устанавливающие значения
> в имеющиеся в классе атрибуты.

```c++
class Circle {
public:
    std::string color;

private:
    double x;
    double y;
    double radius;

public:

    double getx(void) { return x; }
    double gety(void) { return y; }

    void setx(double new_x) { x = new_x; }
    void sety(double new_y) { y = new_y; }

};

int main()
{
    Circle c;

    c.color = "Black"; /* ok, color is public */
    // c.x = 123; /* error, x is private */
}
```


## Друзья

> Это функции или классы, которые не являются членом класса, но имеют доступ 
> ко всем элементам класса.  
> Зачастую **дружба** ведет к плохому **code-style**.

```c++
class Circle {
    /* … */

    /* Declaration */
    friend void helloCircle(const Circle &circle);
};

/* Definition */
void helloCircle(const Circle &circle) {
    circle.showInfo();
}
```

## Конструкторы, деструкторы

> **Конструктор** - это блок инструкций, вызываемых при создании объекта класса. 

Компилятор по умолчанию создает:
- Пустой конструктор (заполняет все поля нулями)
- Конструктор и оператор копирования
- Конструктор и оператор перемещения (с С++11)

*P.S.: о операторах будет рассказано позднее.*

Компилятор создает все эти конструкторы, только если они не созданы явно. Если же опеделить хоть один конструктор самому - остальные придется определять тоже самому.

> **Деструкторы** - это блок интсрукций, вызываемые при уничтожении объекта класса.

Компилятор по умолчанию создает пустой **деструктор** (который не делает ничего).

> **Конструкторов** у класса может быть сколько угодно, но **деструктор** 
> всегда только один.

> **Список инициализиации (initializaion list)** - синтаксическая возможность
> языка, позволяющая инициализировать переменные до создания самого объекта.

```c++
class Circle {
    /* ... */

public:

    Circle(); 								/* Default constructor */
    
    Circle(const Circle &); 				/* Copy constructor */
    Circle &operator=(const Circle &);		/* Copy operator */
    
    Circle(const Circle &&);				/* Move constructor */
    Circle &operator=(const Circle &&);		/* Move operator */

    /* 
     * You can have many constructors 
     * But if you declare default/copy/move constructors 
     * compiler doesn't create them
     */
    Circle() : x(0), y(0), radius(1), color("green") {
        std::cout << "Default constructor without arguments\n" << std::endl;
    }

    Circle(double x, double y, double radius, std::string color="White")
        : x(x), y(y) /* initialization list */
    {
        std::cout << "Custom constructor with arguments\n" << std::endl;

        radius = radius; /* recommend to use initialization list */
        this->color = color;
    }

    /* But u always have only one destructor */
    ~Circle() {
        std::cout << "Circle " << color<< " destroyed" << std::endl;
    }
};
```

## Объект и класс - инстанцирование

```c++
int main()
{
    Circle c1, c2(0, 0, 10, "yellow");
    // Circle cn = new Circle(...);

    c1.showInfo();
    c2.showInfo();

    // delete cn;
}
```
> `Circle` - класс (тип)
> `c1`, `c2` - экземпляры / объекты / инстансы этого класса

## Константность, ссылки
ключевое слово `const` позволяет помечать **переменные**, **указатели** и **методы классов** как неизменяемые / не изменяющие.

Переменные, помеченные ключевым словом `const`, не могут быть изменены во время работы программы, им можно задать тольео значение при инициализации. 

Методы класса, помеченные ключевым словом `const`, не могут менять поля класса, а так же вызывать другие методы без модификатора `const`.

У константных объектов можно вызывать тольео константные методы. Это относится к константным экземплярам класса, константным ссылкам и указателям на экземпляры классов.

```c++
class Circle {
    /* ... */

public:
    double getx(void) const {
        /* 
         * here "this" will have "const Circle *" type 
         * we cannot modify any of attributes of object
         */
        return this->x;
    }

    void setx(double new_x) {
        /* here "this" will have "Circle *" type */
        x = new_x;
    }
};

void get_by_value(Circle circle)
{
    // local copy. outside no changes
    double x = circle.getx();
    circle.setx(x * 2);
}

void get_by_ptr(Circle *pcircle)
{
    // pointer to original object
    double x = circle->getx();
    circle->setx(x * 2);
}

void get_by_const_ptr(const Circle *pcircle)
{
    // pointer to original object, but not modifiable
    double x = circle->getx();
    // circle->setx(x * 2);  /* error, cannot call non const method from const pointer */
}

void get_by_ref(Circle &rcircle)
{
    // same as pointer, but cannot be nullptr, syntax as "by value"
    // original object will be changed
    double x = circle.getx();
    circle.setx(x * 2);
}

void get_by_cref(const Circle &rcircle)
{
    // reference to original object but can not be modified
    double x = circle.gex();
    // double x = rcircle.setx(); /* error, cannot call non const method from const reference */
}
```

# Задания

## 1. Zombie

Реализуйте класс `Zombie`, содержащий следующие атрибуты `type`, `name`, и метод `announce()`, который будет печатать в консоль строку следующего вида:
```
<name> (<type>): Braiiiiinnnssss...
```
Пример:
```
Jim (without legs): Braiiiiinnnssss...
```

После создания класса `Zombie`, напишите класс `ZombieEvent`, позволяющий создавать новых зомби. Класс должен содержать методы:
 - `void setZombieType(type)`, который сохраняет `type` для последующих создаваемых зомби.
 - `Zombie *newZombie(name)`, который и будет создавать новых `Zombie` с установленным ранее полем `typе`, называть их именем `name`, а затем возвращать указатель на созданного зомби.

После этого Вам следует написать функцию `randomChump()`, создающую объект типа `Zombie` со случайным именем, а затем вызывающий метод `announce()` от нового зомби. Способ рандомизации Вам предстоит выбрать самим.

Для проверки напиши полноценную программу, содержащую функцию `main()`.

При выполнении задания можете создавать переменные как на стеке, так и на куче. Выбирайте наиболее подходящий в Вашей ситуации способ.

## 2. ZombieHorde

Для выполнения задания используйте написанные ранее классы и фукции.

Реализуйте класс `ZombieHorde`. Он должен иметь конструктор, принимающий число `N`, обозначающее кол-во объектов типа `Zombie`. При создании класса `ZombieHorde`, должно создаваться `n` объектов `Zombie`, имеющих случайные имена.

Добавьте в новый класс метод `announce()`, вызывающий `announce()` для каждого созданного ранее `Zombie`. Всех `Zombie` необходимо создавать одним вызовом. По завершении работы с объектом `ZombieHorde` *(т.е. когда будет вызван деструктор `ZombieHorde`)* необходимо уничтожить всех ранее созданных `Zombie`.

Для проверки работы напишите тест с функцией `main()`.

## 3. Brains

Реализуйте класс `Brain`, с необходимыми атрибутами (на Ваш выбор). К нему необходимо добавить метод `identify()`, который будет возвращать строку содержащую адрес объекта `Brain` в памяти в 16-ричной системе счисления с префиксом "0x". *(Например, "0xdeadbeaf")*.

После этого напишите класс `Human`, содержащий const атрибут `Brain` с соответствующей областью жизни *(lifetime)*. Добавьте в класс `Human` метод `identify()`, вызывающий `identify()` его `Brain` и возвращающий полученный результат.

## 4. Weapons of Human

Реализуйте класс `Weapon` атрибут которого - строка `type`. Добавьте этому классу метод `getType()`, возвращающий **const ссылку** на строку `type`. И соответственно метод `setType()` для инициализации. 

Затем создайте два класса `HumanA` и `HumanB`. Оба класса должны иметь атрибуты `Weapon` и `name`, и метод `attack()`, печатающий следующее сообщение:
```
<name> attacks with his <weapon_type>.
```
Пример:
```
Jim attacks with his knife.
```

Реализуйте классы `HumanA` и `HumanB` так, чтобы следующий код печатал сначала `"crude spiked club"`, а затем `"some other type of club"` **(и не иначе!)** в обоих случаях.

```c++
int main()
{
    /* 1 */
    {
        Weapon club = Weapon("crude spiked club");

        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club");
        bob.attack();
    }

    /* 2 */
    {
        Weapon club = Weapon("crude spiked club");

        HumanB jim("Jim", club);
        jim.attack();
        club.setType("some other type of club");
        jim.attack();
    }
}
```

Подумайте над тем в каком случае лучше хранить `Weapon` как **указатель**, а в каком как **ссылку**. Постарайтесь обосновать свой выбор прежде чем приступить к заданию.
