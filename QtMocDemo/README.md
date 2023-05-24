
# 查看moc生成的内容
本示例中numberlogic.h的内容如下。
```C++
#ifndef NUMBERLOGIC_H
#define NUMBERLOGIC_H
#include <QWidget>
class NumberLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 counter READ counter WRITE setCounter)

public:
    NumberLogic(QObject*parent = nullptr);
    qint32 counter();
    void setCounter(qint32 counter);
public slots:
    void onIncreace();
signals:
    void counterChanged(int counter);
    void counterChangedText(QString strCounter);
private:
    qint32 m_counter;
};
#endif
```

## 生成内容
编译看可以查看逢恶导非的moc文件。
其中qt_meta_stringdata_NumberLogic和qt_meta_data_NumberLogic，记录了该类的元数据信息。

\build\Demo_autogen\include_Debug\EWIEGA46WW\moc_numberlogic.cpp
```C++
static const qt_meta_stringdata_NumberLogic_t qt_meta_stringdata_NumberLogic = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NumberLogic"
QT_MOC_LITERAL(1, 12, 14), // "counterChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "counter"
QT_MOC_LITERAL(4, 36, 18), // "counterChangedText"
QT_MOC_LITERAL(5, 55, 10), // "strCounter"
QT_MOC_LITERAL(6, 66, 10) // "onIncreace"

    },
    "NumberLogic\0counterChanged\0\0counter\0"
    "counterChangedText\0strCounter\0onIncreace"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NumberLogic[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       1,   36, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::Int, 0x00095103,

       0        // eod
};
```

# QMetaObject
Qt中的Qt元对象系统（The Qt Meta-Object System）负责信号和插槽之间的对象通信机制、运行时类型信息和Qt属性系统。为应用程序中使用的每个QObject子类创建一个QMetaObject实例，该实例存储QObject个子类的所有元信息。此对象可用作QObject:：metaObject（）。

常用到的方法
- className() 返回类的名字
- superClass() 返回父类的元对象（QMetaObject *）
- method()和methodCount()提供了关于类的元方法(信号、槽和其他可调用 的成员函数)的信息
- enumerator() and enumeratorCount() 提供关于该类的枚举器的信息。
- propertyCount() and property() 提供关于该类的属性的信息。
- constructor() and constructorCount() 提供该类元构建函数的信息。QMetaMethod 。

索引函数：indexOfConstructor(), indexOfMethod(), indexOfEnumerator(), and indexOfProperty()，映射 constructors, member functions, enumerators, or properties 的名字到元对象中的索引。比如，当你连接一个信号到槽的时候，Qt内部使用indexOfMethod() 。

类还可以有一个附加类信息的名称-值对列表，存储在QMetaClassInfo对象中。对的数量由classInfoCount（）返回，单个对由classInfo（）返回。您可以使用indexOfClassInfo（）搜索对。

相相关的信息还可以去查看：QMetaClassInfo, QMetaEnum, QMetaMethod, QMetaProperty, QMetaType, and Meta-Object System.

# 元对象系统（The Meta-Object System）
Qt的元对象系统 提供了信号和槽用的内部通信机制，运行时类型信息，动态属性系统。

元对象系统基于以下三个方面：
- Object类：为可以复用元对象系统的对象提供了一个基类。
- Q_OBJECT宏：类声明私有部分中的Q_OBJECT宏用于启用元对象功能，如动态属性、信号和槽。
- moc(Meta-Object Compiler):给每个QObject子类生成实现元对象功能的必要代码。


# 参考
[https://doc.qt.io/qt-5.15/qmetaobject.html#details](https://doc.qt.io/qt-5.15/qmetaobject.html#details)

[https://doc.qt.io/qt-5.15/metaobjects.html](https://doc.qt.io/qt-5.15/metaobjects.html)