# ООП лабораторная 1

**ООП** - объектно ориентированное программирование

```c++
/* Обсудить размер структуры */
struct S {
	int x;
	double d;
}; /* sizeof(S) == 16 */

struct S {
	int a, b, c;
}; /* sizeof(S) == 12 */
```

## Обращение к элементам класса
`"." и "->"`

Пример простого класса

```c++
class Circle {
public:
	double x;
	double y;
	double radius;
	std::string color;
};

void show_info(const Circle *circle) {
	std::cout << "Circle's info:" << std::endl;
	std::cout << "\tCoordinate: x = " << circle->x << ", y = " << circle->y << std::endl;
	std::cout << "\tRadius = " << circle->radius << std::endl;
	std::cout << "\tColor =  " << circle->color << std::endl;
}

int main()
{
	// Circle c{0, 0, 3, "blue"}; /* Aggregate initialization */
	Circle c;

	c.x = 0;
	c.y = 0;
	c.radius = 3;
	c.color = "Blue";

	show_info(&c);
}
```

## Методы, ключевое слово this

```c++
class Circle {
    // ...

public:
	double area() {
		return M_PI * radius * radius;
	}

	double length() {
		return 2 * M_PI * this->radius;
	}

	void showInfo() {
	std::cout << "Circle's info:" << std::endl;
	std::cout << "\tCoordinate: x = " << x << ", y = " << y << std::endl;
	std::cout << "\tRadius = " << radius << std::endl;
	std::cout << "\tColor =  " << color << std::endl;
}

/* Can't init namespace */
/* Can to init in out of class */
/* Order of methods is not important */
};
```

> `this` - Ключевое слово, доступное внутри определения класса, которое имеет тип указателя на текущий экземпляр класса. В константных методах - тип указателя константный

## Инкапсуляция
> **Инкапсуляция** – это способ сокрытия информации от внешнего мира.

Подробнее рассмотрим на примере.

## Модификаторы доступа public and private, геттеры, сеттеры

```c++
class Circle {

public:
	std::string color;

private:
	double x;
	double y;
	double radius;


public:

	double getx(void) {
		return x;
	}

	double gety(void) {
		return y;
	}

	void setx(double new_x) {
		x = new_x;
	}

	void sety(double new_y) {
		y = new_y;
	}

};

int main()
{
	class c;

	c.color = "Black"; // ok, color is public
	// c.x = 123; // error, x is private
}
```


## Друзья
> Это функции или класса, которые не являются членом класса, но имеют доступ к private/protecte dэлементам класса. Дружба - это плохо. Ведет к плохому code-style.

```c++
class Circle {
	/* … */

	/* Declaration */
	friend void helloCircle();
};

/* Definition */
void helloCircle(const Circle &circle) {
	circle.showInfo();
}
```

## Конструкторы, деструкторы

```c++
class Circle {
    // ...

public:
	/* You can have many constructors */
	Circle() : x(0), y(0), radius(1), color("green") {
        std::cout << "Default constructor without arguments\n" << std::endl;
    }

	Circle(double x, double y, double radius, std::string color="White")
		: x(x), y(y) /* initialization list */
    {
		std::cout << "Custom constructor with arguments\n" << std::endl;

		radius = radius;
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
> `Circle` - класс (тип), `c1`, `c2` - объекты этого класса (инстансы)

## Константность, ссылки

```c++
class Circle {
    // ...

public:
	double getx(void) const {
		// here "this" will have "const Circle *" type
		// we cannot modify any of attributes of object
		return this->x;
	}

	void setx(double new_x) {
		// here "this" will have "Circle *" type
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

Реализуйте класс `Zombie`. Содержащий следующие атрибуты `type`, `name`, и метод `announce()`, который будет печатать в консоль строку следующего вида:
```
<name> (<type>): Braiiiiinnnssss...
```
Пример:
```
Jim (without legs): Braiiiiinnnssss...
```

После создания класса `Zombie`, напишите класс `ZombieEvent`, позволяющий создавать новых зомби. Для этого добавьте в него метод `setZombieType()`, который сохраняет `type` для последующих создаваемых зомби. И метод `Zombie *newZombie(std::string name)`, который и будет создавать новых `Zombie` с установленным ранее полем `typе`, называть их каким-то именем, а затем возвращать указатель на созданного зомби.

После этого Вам следует написать функцию `randomChump()`, создающую объект типа `Zombie` со случайным именем, а затем вызывающий метод `announce()` от нового зомби. Способ рандомизации Вам предстоит выбрать самим.

Для проверки напиши полноценную программу, содержащую функцию `main()`.

При выполнении задания можете создавать переменные как на стеке, так и на куче. Выбирайте наиболее подходящий в Вашей ситуации способ.

## 2. ZombieHorde

Для выполнения задания используйте написанные ранее классы и фукции.

Реализуйте класс `ZombieHorde`. Он должен иметь конструктор, принимающий целочисленное число **N**, обозначающее кол-во объектов типа `Zombie`. *(Уточнение: при создании класса `ZombieHorde`, должно создаваться **N** объектов `Zombie`, имеющих случайные имена)*

Добавьте в новый класс метод `announce()`, вызывающий `announce()` для каждого созданного ранее `Zombie`. Всех `Zombie` необходимо создавать одним вызовом. По завершении работы с объектом `ZombieHorde` необходимо уничтожать всех `Zombie`. *(Уточнение: когда будет вызван деструктор `ZombieHorde`)*

Для проверки работы напиши тест и `main()` функцию на Ваш выбор.

## 3. Brains

Реализуйте класс `Brain`, с необходимыми атрибутами (на Ваш выбор). К нему необходимо добавить метод `identify()`, который будет возвращать строку содержащую адрес объекта `Brain` в памяти в 16-ричной системе счисления с префиксом "0x". *(Например, "0xdeadbeaf")*.

После этого напишите класс `Human`, содержащий const атрибут `Brain` с соответствующей областью жизни *(lifetime)*. Добавьте в класс `Human` метод `identify()`, вызывающий `identify()` его `Brain` и возвращающий полученный результат.

## 4. Weapons of Human

Реализуйте класс `Weapon` атрибут которого - строка `type`. Добавьте этому классу метод `getType()`, возвращающий **const ссылку** на строку `type`. И соответственно `setType()` для инициализации. Затем создайте два класса `HumanA` и `HumanB`. Оба должны иметь атрибуты `Weapon`, `name` и метод `attack()`, печатающий следующее сообщение:
```
<name> attacks with his <weapon_type>.
```
Пример:
```
Jim attacks with his knife.
```

Реализуй классы `HumanA` и `HumanB` так, чтобы следующий код печатал сначала **"crude spiked club"**, а затем **"some other type of club"** (и не иначе!) в обоих случаях.

```c++
int main()
{
	{
		Weapon club = Weapon("crude spiked club");

		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
    }
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
