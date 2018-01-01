#include <QString>
#include <QtTest>
#include "../super_enum.h"

class MyEnum: public SuperEnum<MyEnum>
{
public:
    MyEnum() {}
    explicit MyEnum(const int &value): SuperEnum(value) {}

    static const MyEnum element1;
    static const MyEnum element2;
};

const MyEnum MyEnum::element1{1};
const MyEnum MyEnum::element2{2};

class MyEnum1: public MyEnum
{
public:
    MyEnum1() {}
    explicit MyEnum1(const int &value): MyEnum(value) {}

    static const MyEnum1 element3;
    static const MyEnum1 element4;
};

const MyEnum1 MyEnum1::element3{3};
const MyEnum1 MyEnum1::element4{4};

class MyEnum2: public SuperEnum<MyEnum2>
{
public:
    MyEnum2() = default;
    explicit MyEnum2(const int &value): SuperEnum(value) {}
};

class SuperEnumTest : public QObject
{
    Q_OBJECT

public:
    SuperEnumTest();

private Q_SLOTS:
    void testMyEnumElement();
    void testMyEnumElement2();
    void testDeleting();
};

SuperEnumTest::SuperEnumTest()
{
}

void SuperEnumTest::testMyEnumElement()
{
    MyEnum e5;
    MyEnum e6;
    MyEnum e7;
    QVERIFY(MyEnum::element1 == 1);
    QVERIFY(MyEnum::element2 == 2);
    QVERIFY(e5 == 5);
    QVERIFY(e6 == 6);
    QVERIFY(e7 == 7);
    QVERIFY(MyEnum::size() == 7);
    QVERIFY(e5.size() == 7);
    QVERIFY(&MyEnum::element1 == MyEnum::object(1));
    QVERIFY(&MyEnum::element1 == e5.object(1));

    const MyEnum *e1 = &MyEnum1::element1;
    const MyEnum &e3 = MyEnum1::element3;

    QVERIFY(*e1 == 1);
    QVERIFY(e3 == 3);
}

void SuperEnumTest::testMyEnumElement2()
{
    MyEnum2 e0;
    MyEnum2 e1;
    MyEnum2 e2;
    MyEnum2 e3{3};
    MyEnum2 e4;
    MyEnum2 e10{10};
    MyEnum2 e11;
    MyEnum2 em20{-20};
    MyEnum2 e12;

    QVERIFY(e0 == 0);
    QVERIFY(e1 == 1);
    QVERIFY(e2 == 2);
    QVERIFY(e4 == 4);
    QVERIFY(e3 == 3);
    QVERIFY(e10 == 10);
    QVERIFY(e11 == 11);
    QVERIFY(em20 == -20);
    QVERIFY(e12 == 12);
    QVERIFY(&e0 == MyEnum2::object(0));
    QVERIFY(&em20 == MyEnum2::object(-20));
}

void SuperEnumTest::testDeleting()
{
    MyEnum *e500 = new MyEnum{500};
    MyEnum *e501 = new MyEnum{};
    QVERIFY(*e500 == 500);
    QVERIFY(*e501 == 501);
    delete e501;
    e501 = new MyEnum{};
    QVERIFY2(*e501 == 501, qPrintable(QString{"%1"}.arg(*e501)));

    delete e501;
    delete e500;
}

QTEST_APPLESS_MAIN(SuperEnumTest)

#include "super_enum_test.moc"
