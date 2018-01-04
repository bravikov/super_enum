# Expandable Enumeration

Read this in other languages: [Russian](README.ru.md).

The project provides a class SuperEnum.

```SuperEnum``` is a C++ template class which allows to make expandable enumeration.

The enumeration is created by inheritance of the SuperEnum. A type of expandable enumeration is a class, and enumeration elements are objects of this class.

A classic enumeration is created as follows:

```cpp
enum MyEnum {Element1, Element2, Element3};
```

C++ does not allow adding elements to an enumeration outside this expression. But in some tasks it would be useful to have an enumeration with mandatory elements and an ability to add user elements.

There are different [ways](https://stackoverflow.com/questions/644629/base-enum-class-inheritance) to make an extendable or inheritable enumeration.


## Features of ```SuperEnum```

* Automatic numbering of elements.
* Manual numbering of elements.
* Negative element numbers.
* Restriction on creation of elements with identical numbers.

Numbering rules, as in the classic enumeration. The first element without an explicit number is assigned the number 0, the next one is 1, and so on. If you assign the number N to an element, then a next created element will have the number N + 1.

## Using

To use SuperEnum, only one super_enum.h file is needed. You should include it in your program:

```cpp
#include "super_enum.h"
```

In the header file my_enum.h, the class ```MyEnum``` is created, which inherits the class ```SuperEnum``` as follows:

```cpp
class MyEnum: public SuperEnum<MyEnum>
{
public:
    MyEnum() {}
    explicit MyEnum(const int &value): SuperEnum(value) {}

    static const MyEnum element1;
    static const MyEnum element2;
    static const MyEnum element3;
};
```

As a template parameter of ```SuperEnum```, the created class ```MyEnum``` is used: ```SuperEnum<MyEnum>```.

Two constructors are created: the first for automatic numbering of elements and the second for manual numbering.

Several enumeration elements are declared. An element is a static constant object of the same class.

The file my_enum.cpp defines the elements, and they are given the numbers as follows:

```cpp
const MyEnum MyEnum::element1(1);
const MyEnum MyEnum::element2;
const MyEnum MyEnum::element3;
```

An order of defining the elements affects their numbering. Numbering increases with the definition of the next element.

Accessing to the elements is done as follows:

```cpp
std::cout << MyEnum::element3;
// Output: 3
```

You can create new elements as usual variables:

``` cpp
const MyEnum element4;
const MyEnum element5;
````

or as members of a derived class:

```cpp
class MyEnum2: public MyEnum
{
public:
    MyEnum2() {}
    explicit MyEnum1(const int &value): MyEnum(value) {}

    static const MyEnum2 element4;
    static const MyEnum2 element5;
};

const MyEnum2 MyEnum2::element4;
const MyEnum2 MyEnum2::element5;
```

In last case, you can access to the elements of the base class through the derived class as follows:

```cpp
std::cout << MyEnum2::element3;
// Output: 3
```

You must pass the elements as references or pointers.

```
// Example 1
void fun(const MyEnum2 *element);
void fun(const MyEnum2 &element);

// Example 2
const MyEnum *e1 = &MyEnum2::element1;
const MyEnum &e2 = MyEnum2::element2;
```
