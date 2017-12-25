#include <QString>
#include <QtTest>
#include "../super_enum.h"

class MyEnum: public SuperEnum<MyEnum>
{
public:
    MyEnum() = default;
    explicit MyEnum(const int &value): SuperEnum(value) {}

    static const MyEnum e1;
    static const MyEnum e2;
};

const MyEnum MyEnum::e1{1};
const MyEnum MyEnum::e2{2};

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
};

SuperEnumTest::SuperEnumTest()
{
}

void SuperEnumTest::testMyEnumElement()
{
    MyEnum e3;
    MyEnum e4;
    MyEnum e5;
    QVERIFY(MyEnum::e1 == 1);
    QVERIFY(MyEnum::e2 == 2);
    QVERIFY(e3 == 3);
    QVERIFY(e4 == 4);
    QVERIFY(e5 == 5);
    QVERIFY(MyEnum::size() == 5);
    QVERIFY(e3.size() == 5);
    QVERIFY(&MyEnum::e1 == MyEnum::object(1));
    QVERIFY(&MyEnum::e1 == e3.object(1));
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

QTEST_APPLESS_MAIN(SuperEnumTest)

#include "super_enum_test.moc"
