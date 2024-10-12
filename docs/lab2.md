# ООП лабораторная 2

## Наследование

Это один из ключевых принципов ООП, позволяющий использовать перменные и
методы другого класса как свои собственные.

> Класс **родитель (базовый)** - это класс, от которого будут наследоваться 
> данные и методы.  
> **Дочерний** класс **(производный)** - это класс, который наследует данные из
> класса родителя.

### Атрибут доступа protected

> Ключевое слово **protected** - говорит, что всё объявленное ниже данного 
> слова будет недоступно из вне класса, но дочерние классы могут использовать.

#### Пример наследования

```c++
class Figure {
protected:
    string name;

    void showInfo() const {
        cout << "Figure: " << name << endl;
    }

public:
    Figure(const string &n="figure") : name(n) { }
    ~Figure() = default; /* TODO */ 
};

class Circle : public Figure {
public:
    Circle() : Figure("circle")
    {
        swowInfo(); /* It works */
    }
};

int main() {
    Figure f;
    f.name;
    f.showInfo(); /* doesn't work because this method is marked as protected */

    Circle c;
    c.name;
    c.showInfo(); /* doesn't work too because this method is marked as protected */
}
```

### Преобразование доступа в зависимости от способа наследования

При наследование атрибуты и методы изменяют свои права доступа в зависимости
от способа наследования. Ниже в таблицах приведены преобразования. 

> Подробнее Вы посмотреть и поэксперемнтировать можете в файле 
"[src/lab2/base_inheritance.cpp](../src/lab2/base_inheritance.cpp)".

#### Public наследование
| Тип в классе родителя -> Тип в классе ребенке |
| :-------------------------------------------: |
|               private -> private              |
|             protected -> protected            |
|                public -> public               |

#### Private наследование
| Тип в классе родителя -> Тип в классе ребенке |
| :-------------------------------------------: |
|               private -> private              |
|             protected -> private              |
|                public -> private              |

#### Protected наследование
| Тип в классе родителя -> Тип в классе ребенке |
| :-------------------------------------------: |
|               private -> private              |
|             protected -> protected            |
|                public -> protected            |

## Полиморфизм

Это способность кода работать с разными классами используя один интерфейс.

### Виртуальные методы (`virtual`, `override`, `final`)

> `virtual` - говорит, что функция может быть перегружена в дочерних классах.  
> `override` - говорит, что функция перегружает родительскую. И что эта функция
> может быть тоже перегружена в дочерних классах.  
> `final`  - говорит, что функция перегружает родительскую, но в дочерних классах
> уже нельзя будет это сделать. TODO.

**НИКОГДА** не используйте виртуальные методы внутри конструктора, это ведето к 
**UB (Undefine Behavior)**.  
Cсылка: [докумнетация почему нельзя вызывать виртуальный методв внутри конструктора](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html#Rc-ctor-virtual)  
Ссылка: [как все-таки можно вызвать виртуальный метод внутри конструктора](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html#Rc-factory)

#### Пример динамического полиморфизма

> В динамическом полиморфизме используют принципы наследования совместно с
> виртуальными функциями.

```c++
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
}
```

Помимо динамического полиморфизма существует еще и статический в его основе
лежити спользование шаблонов.

#### Пример статического полиморфизма

> Про шаблоны мы будем говорить в последующих лабораторных. Здесь они 
> используются исключительно в качестве примера.

```c++
template <class S>
void printContainer(S &container) {
    for (const auto &it : container) {
        std::cout << it << std::endl;
    }
}

int main() {
    vector<int> v({1, 2, 3});
    list<int> l({4, 5, 6});

    printContainer(v);
    printContainer(l);
}
```

### Абстрактные классы

> **Абстрактные классы** - TODO

## Преобразование типов

Для явного преобразования типов в C++ принято использовать следующие операторы:
- static_cast
- dynamic_cast
- const_cast
- reinterpret_cast

### static_cast

> `static_cast` - используется, когда вы знаете тип приводимого объекта.

### dynamic_cast

> `dynamic_cast` - использутеся, когда вы точно не знаете тип приводимого объекта.

### const_cast

> `const_cast` - используется, когда вы хотите снять или добавить модификатор `const`.

**НЕ ИСПОЛЬЗУЙТЕ** `const_cast` для снятия `const` у объекта.  
Ссылка: [почему не стоит так делать](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html#es50-dont-cast-away-const)

### reinterpret_cast

> `reinterpret_cast` - тоже самое что и **C-style**.

### Преобразование в C-style

Данные преобразование **НЕ** рекомендуется для использовать при написании на **С++**.

```c++
int main() {
	/* My machine use LITTLE ENDIAN */
    long long a = 0x0000'0000'414c'4f48; /* HOLA */
    char *str = (char *)&a; /* C-style cast */

    printf("%s\n", str);
}
```

## Задания