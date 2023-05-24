
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

## 生成类的元数据
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

生成的元对象相关方法：

```C++
QT_INIT_METAOBJECT const QMetaObject NumberLogic::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NumberLogic.data,
    qt_meta_data_NumberLogic,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NumberLogic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}
```
生成的元调用 相关方法

qt_static_metacall 和 qt_metacall
```C++
void NumberLogic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NumberLogic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->counterChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->counterChangedText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->onIncreace(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NumberLogic::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NumberLogic::counterChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NumberLogic::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NumberLogic::counterChangedText)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<NumberLogic *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qint32*>(_v) = _t->counter(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<NumberLogic *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCounter(*reinterpret_cast< qint32*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

int NumberLogic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
```
## 给对应的信号生成方法
```C++
signals:
    void counterChanged(int counter);
    void counterChangedText(QString strCounter);
```
以上两个信号生成的代码。
```C++
// SIGNAL 0
void NumberLogic::counterChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NumberLogic::counterChangedText(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
```
# 基础知识
## 元对象系统（The Meta-Object System）
Qt的元对象系统 提供了信号和槽用的内部通信机制，运行时类型信息，动态属性系统。

元对象系统基于以下三个方面：
- Object类：为可以复用元对象系统的对象提供了一个基类。
- Q_OBJECT宏：类声明私有部分中的Q_OBJECT宏用于启用元对象功能，如动态属性、信号和槽。
- moc(Meta-Object Compiler):给每个QObject子类生成实现元对象功能的必要代码。

moc工具读取一个C++源文件。如果它找到一个或多个包含Q_OBJECT宏的类声明，它将生成另一个C++源文件，该文件包含这些类中每个类的元对象代码。这个生成的源文件要么被#包含到类的源文件中，要么更常见的是，被编译并与类的实现链接。

除了为对象之间的通信提供信号和插槽机制（引入该系统的主要原因）外，元对象代码还提供了以下附加功能：

- QObject::metaObject()返回该类关联的元对象。
- QMetaObject::className() 在运行时以字符串形式返回类名，而不需要通过C++编译器支持本机运行时类型信息（RTTI）。
- QObject:：inherits（）函数返回对象是否是继承QObject继承树中指定类的类的实例。
- QObject::tr() 和 QObject::trUtf8() 为国际化翻译字符串。
- QObject::setProperty() 和 QObject::property()按名称动态设置和获取属性。
- QMetaObject::newInstance() 构造类的一个新实例。

还可以使用qobject_cast（）对qobject类执行动态强制转换。qobject_cast（）函数的行为与标准C++ dynamic_cast（）类似，其优点是不需要RTTI支持，并且可以跨动态库边界工作。它试图将其参数强制转换为尖括号中指定的指针类型，如果对象的类型正确（在运行时确定），则返回非零指针，如果对象类型不兼容，则返回nullptr。

例如， 假设 MyWidget继承 QWidget，并声明了Q_OBJECT宏:
```C++
    QObject *obj = new MyWidget;
```
类型为QObject *的obj变量，实际上指向一个MyWidget对象，因此我们可以适当的强制转换它
The obj variable, of type QObject *, actually refers to a MyWidget object, so we can cast it appropriately:
```C++
    QWidget *widget = qobject_cast<QWidget *>(obj);
```

可以从 QObject强制转换到 QWidget，因为这个对象实际上是一个MyWidget，MyWidaget是QWidget的子类。既然我们知道obj是一个MyWidget，我们也可以将其强制转换为MyWidget *。
```C++
    MyWidget *myWidget = qobject_cast<MyWidget *>(obj);
```
转换到MyWidget是成功的，因为qobject_cast（）没有区分内置的Qt类型和自定义类型。
```C++
    QLabel *label = qobject_cast<QLabel *>(obj);
    // label is 0
```
另一方面，对QLabel的强制转换失败。然后指针被设置为0。这使得可以在运行时根据类型不同地处理不同类型的对象：
```C++
    if (QLabel *label = qobject_cast<QLabel *>(obj)) {
        label->setText(tr("Ping"));
    } else if (QPushButton *button = qobject_cast<QPushButton *>(obj)) {
        button->setText(tr("Pong!"));
    }
```
## QObject

## QMetaObject
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


# 参考
[https://doc.qt.io/qt-5.15/qmetaobject.html#details](https://doc.qt.io/qt-5.15/qmetaobject.html#details)

[https://doc.qt.io/qt-5.15/metaobjects.html](https://doc.qt.io/qt-5.15/metaobjects.html)