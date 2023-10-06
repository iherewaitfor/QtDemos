- [QtMocDemo](#qtmocdemo)
- [How to run](#how-to-run)
  - [修改CMakeLists.txt设置Qt路径](#修改cmakeliststxt设置qt路径)
  - [生成项目](#生成项目)
- [查看moc生成的内容](#查看moc生成的内容)
  - [生成类的元数据](#生成类的元数据)
  - [signals 给对应的信号生成方法](#signals-给对应的信号生成方法)
  - [slots的宏定义](#slots的宏定义)
  - [Q\_INVOKABLE](#q_invokable)
  - [Q\_PROPERTY](#q_property)
  - [Q\_OBJECT](#q_object)
- [基础知识](#基础知识)
  - [元对象系统（The Meta-Object System）](#元对象系统the-meta-object-system)
  - [QObject](#qobject)
  - [QObjectPrivate](#qobjectprivate)
  - [QMetaObject](#qmetaobject)
- [信号和槽的实现细节(to do)](#信号和槽的实现细节to-do)
  - [Connect](#connect)
  - [SLOT和SIGNAL宏](#slot和signal宏)
  - [信号与曹连接时的的参数检查checkConnectArgs](#信号与曹连接时的的参数检查checkconnectargs)
- [参考](#参考)



# QtMocDemo
该例主要用于综合展示Qt的moc生成的内容，主要用于理解Qt核心的信号槽。

# How to run
先安装Qt。本例安装的版本是Qt5.14.2
## 修改CMakeLists.txt设置Qt路径
修改项目中CMakeLists.txt文件中的Qt路径。修改为你自己本地的路径。分别对应32位和64位。
```c
#选择64位还是32位的Qt
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(Qt5HOMEDIR D:/Qt/Qt5.14.2/5.14.2/msvc2017_64)
else()
	set(Qt5HOMEDIR D:/Qt/Qt5.14.2/5.14.2/msvc2017)
endif()
```
## 生成项目
在项目源码目录中新建build文件夹，然后命令行进入到build目录，
生成32位项目是运行命令cmake .. -G "Visual Studio 16 2019" -A Win32
```
D:\srccode\QtDemos\QtMocDemo\build>cmake .. -G "Visual Studio 16 2019" -A Win32
```
。然后打开生成的sln文件，将Demo项目设置为启动项即可。 cmake使用可参考本github项目[cmakevisualstudio](https://github.com/iherewaitfor/cmakevisualstudio)

如果你安装的是其他版本的Visual Studio，可以通过以下命令，查看对应的Visual Studio版本。
```
cmake -G help
```

```
 Visual Studio 17 2022        = Generates Visual Studio 2022 project files.
                                 Use -A option to specify architecture.
  Visual Studio 16 2019        = Generates Visual Studio 2019 project files.
                                 Use -A option to specify architecture.
  Visual Studio 15 2017 [arch] = Generates Visual Studio 2017 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 14 2015 [arch] = Generates Visual Studio 2015 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 12 2013 [arch] = Generates Visual Studio 2013 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 11 2012 [arch] = Deprecated.  Generates Visual Studio 2012
                                 project files.  Optional [arch] can be
                                 "Win64" or "ARM".
  Visual Studio 9 2008 [arch]  = Generates Visual Studio 2008 project files
```

比如你安装的是Visual studio 2017，需要构建Win64项目,可以将构建命令改成
```
cmake .. -G "Visual Studio 15 2017 Win64"
```
若需要使用Visual Studio 2017，需要构建win32项目，则可以将构建命令改成
```
cmake .. -G "Visual Studio 15 2017"
```

其他版本Visual Studeio命令可参考以下示例。
```
cmake .. -G "Visual Studio 17 2022"
cmake .. -G "Visual Studio 17 2022" -A Win32
cmake .. -G "Visual Studio 16 2019" -A Win32
cmake .. -G "Visual Studio 16 2019"
cmake .. -G "Visual Studio 15 2017"
cmake .. -G "Visual Studio 15 2017 Win64"
```

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
    Q_INVOKABLE void addCount(qint32 i); // can be invoked via the meta-object system
    void nornmalAddCount(qint32 i);
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

生成的moc文件。
```C++
/****************************************************************************
** Meta object code from reading C++ file 'numberlogic.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../numberlogic.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'numberlogic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NumberLogic_t {
    QByteArrayData data[9];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NumberLogic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NumberLogic_t qt_meta_stringdata_NumberLogic = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NumberLogic"
QT_MOC_LITERAL(1, 12, 14), // "counterChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "counter"
QT_MOC_LITERAL(4, 36, 18), // "counterChangedText"
QT_MOC_LITERAL(5, 55, 10), // "strCounter"
QT_MOC_LITERAL(6, 66, 10), // "onIncreace"
QT_MOC_LITERAL(7, 77, 8), // "addCount"
QT_MOC_LITERAL(8, 86, 1) // "i"

    },
    "NumberLogic\0counterChanged\0\0counter\0"
    "counterChangedText\0strCounter\0onIncreace\0"
    "addCount\0i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NumberLogic[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   40,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    1,   41,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int,    8,

 // properties: name, type, flags
       3, QMetaType::Int, 0x00095103,

       0        // eod
};

void NumberLogic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NumberLogic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->counterChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->counterChangedText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->onIncreace(); break;
        case 3: _t->addCount((*reinterpret_cast< qint32(*)>(_a[1]))); break;
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

void *NumberLogic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NumberLogic.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NumberLogic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

```

## 生成类的元数据
编译看可以查看生成的moc文件。
其中qt_meta_stringdata_NumberLogic和qt_meta_data_NumberLogic，记录了该类的元数据信息。
生成的位置为
\build\Demo_autogen\include_Debug\EWIEGA46WW\moc_numberlogic.cpp

这些类的元信息包括：
- 类名
- 信号，实际是一个函数。
- 槽
- Q_PROPERTY声明的属性及其读写方法
- Q_INVOKABLE的函数，没有使用Q_INVOKABLE的函数没有在元数据信息。
```C++
struct qt_meta_stringdata_NumberLogic_t {
    QByteArrayData data[9];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NumberLogic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NumberLogic_t qt_meta_stringdata_NumberLogic = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NumberLogic"
QT_MOC_LITERAL(1, 12, 14), // "counterChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "counter"
QT_MOC_LITERAL(4, 36, 18), // "counterChangedText"
QT_MOC_LITERAL(5, 55, 10), // "strCounter"
QT_MOC_LITERAL(6, 66, 10), // "onIncreace"
QT_MOC_LITERAL(7, 77, 8), // "addCount"
QT_MOC_LITERAL(8, 86, 1) // "i"

    },
    "NumberLogic\0counterChanged\0\0counter\0"
    "counterChangedText\0strCounter\0onIncreace\0"
    "addCount\0i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NumberLogic[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   40,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    1,   41,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int,    8,

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
        case 3: _t->addCount((*reinterpret_cast< qint32(*)>(_a[1]))); break;
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
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
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
## signals 给对应的信号生成方法
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
每个信号都生成了对应的方法。

Qt5.14.2\5.14.2\Src\qtbase\src\corelib\kernel\qobjectdefs.h
另外查看signals的宏定义。看出来，signals最终是被换成了public。signals关键字主要是给moc去生成对应的方法，并且这些方法都是public的。
同时还会生成一些元数据到qt_meta_stringdata_NumberLogic和qt_meta_data_NumberLogic。

看到有
- 信号的字符串名字，可能有类型名字等
- 信号的个数
- 信号函数
- 信号函数的各个参数的类型，名字
```       C++
  2,       // signalCount

// signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   40,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    1,   41,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
```

signals的宏定义

```C++
// The following macros can be defined by tools that understand Qt
// to have the information from the macro.
# define QT_ANNOTATE_ACCESS_SPECIFIER(x)
// The following macros are our "extensions" to C++
// They are used, strictly speaking, only by the moc.
# define Q_SIGNALS public QT_ANNOTATE_ACCESS_SPECIFIER(qt_signal)
#define signals Q_SIGNALS
```

emit的宏定义。其实是空的。便于理解信号。
```C++
// The following macros are our "extensions" to C++
// They are used, strictly speaking, only by the moc.
# define emit
```

## slots的宏定义
slots宏，主要用于moc读取 生成相关信息。最终宏定义是空的。
```C++
// The following macros can be defined by tools that understand Qt
// to have the information from the macro.
# define QT_ANNOTATE_ACCESS_SPECIFIER(x)
// The following macros are our "extensions" to C++
// They are used, strictly speaking, only by the moc.
# define Q_SLOTS QT_ANNOTATE_ACCESS_SPECIFIER(qt_slot)
#define slots Q_SLOTS
```
## Q_INVOKABLE
Q_INVOKABLE宏，主要用于moc读取 生成对应的方法元数据。最终宏定义是空的。
```C++
// The following macros can be defined by tools that understand Qt
// to have the information from the macro.
# define QT_ANNOTATE_FUNCTION(x)
// The following macros are our "extensions" to C++
// They are used, strictly speaking, only by the moc.
#define Q_INVOKABLE  QT_ANNOTATE_FUNCTION(qt_invokable)
```
## Q_PROPERTY
Q_PROPERTY宏，主要用于moc读取 生成对应的方法元数据。最终宏定义是空的。
```C++
// The following macros can be defined by tools that understand Qt
// to have the information from the macro.
# define QT_ANNOTATE_CLASS(type, ...)
// The following macros are our "extensions" to C++
// They are used, strictly speaking, only by the moc.
#define Q_PROPERTY(...) QT_ANNOTATE_CLASS(qt_property, __VA_ARGS__)
```
## Q_OBJECT

```C++
/* qmake ignore Q_OBJECT */
#define Q_OBJECT \
public: \
    QT_WARNING_PUSH \
    Q_OBJECT_NO_OVERRIDE_WARNING \
    static const QMetaObject staticMetaObject; \
    virtual const QMetaObject *metaObject() const; \
    virtual void *qt_metacast(const char *); \
    virtual int qt_metacall(QMetaObject::Call, int, void **); \
    QT_TR_FUNCTIONS \
private: \
    Q_OBJECT_NO_ATTRIBUTES_WARNING \
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **); \
    QT_WARNING_POP \
    struct QPrivateSignal {}; \
    QT_ANNOTATE_CLASS(qt_qobject, "")
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

信号连接
[connect](https://codebrowser.dev/qt6/qtbase/src/corelib/kernel/qobject.cpp.html#2825)

```C++
QMetaObject::Connection QObject::connect(const QObject *sender, const char *signal,
                                         const QObject *receiver, const char *method,
                                         Qt::ConnectionType type)
```

## QObjectPrivate

线程相关数据
[threadData](https://codebrowser.dev/qt6/qtbase/src/corelib/kernel/qobject_p.h.html#189)


```C++
 QAtomicPointer<QThreadData> threadData; // id of the thread that owns the object
 using ConnectionDataPointer = QExplicitlySharedDataPointer<ConnectionData>;
 QAtomicPointer<ConnectionData> connections;
```

[QMetaObjectPrivate::connect](https://codebrowser.dev/qt6/qtbase/src/corelib/kernel/qobject.cpp.html#_ZN18QMetaObjectPrivate7connectEPK7QObjectiPK11QMetaObjectS2_iS5_iPi)
```C++
QObjectPrivate::Connection *QMetaObjectPrivate::connect(const QObject *sender,
                                 int signal_index, const QMetaObject *smeta,
                                 const QObject *receiver, int method_index,
                                 const QMetaObject *rmeta, int type, int *types
```

[QObjectPrivate::addConnection](https://codebrowser.dev/qt6/qtbase/src/corelib/kernel/qobject.cpp.html#_ZN14QObjectPrivate13addConnectionEiPNS_10ConnectionE)
```C++
inline void QObjectPrivate::addConnection(int signal, Connection *c)
```

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

# 信号和槽的实现细节(to do)
## Connect
```C++
    static QMetaObject::Connection connect(const QObject *sender, const char *signal,
                        const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);

    static QMetaObject::Connection connect(const QObject *sender, const QMetaMethod &signal,
                        const QObject *receiver, const QMetaMethod &method,
                        Qt::ConnectionType type = Qt::AutoConnection);

    inline QMetaObject::Connection connect(const QObject *sender, const char *signal,
                        const char *member, Qt::ConnectionType type = Qt::AutoConnection) const;
```
其中业务常用的是
```C++
    static QMetaObject::Connection connect(const QObject *sender, const char *signal,
                        const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
```
具体实际可以查看源码\Src\qtbase\src\corelib\kernel\qobject.cpp

该方法主要逻辑：
- 判断参数的一些合法性
- 根据信号的字符串（2名字和参数类型），从sender对象的元数据中找到该信号的索引位置。
- 根据槽的字符串（1名字和参数类型），从receiver对象的元数据中找到该槽的索引位置
- 然后返回以下QMetaObject::Connection。
```C++
    QMetaObject::Connection handle = QMetaObject::Connection(QMetaObjectPrivate::connect(
        sender, signal_index, smeta, receiver, method_index_relative, rmeta ,type, types));
    return handle;
```
其中QMetaObjectPrivate::connect原型如下。
```C++
QObjectPrivate::Connection *QMetaObjectPrivate::connect(const QObject *sender,
                                 int signal_index, const QMetaObject *smeta,
                                 const QObject *receiver, int method_index,
                                 const QMetaObject *rmeta, int type, int *types)
```
## SLOT和SIGNAL宏
```C++
# define SLOT(a)     qFlagLocation("1"#a QLOCATION)
# define SIGNAL(a)   qFlagLocation("2"#a QLOCATION)

# define QLOCATION "\0" __FILE__ ":" QT_STRINGIFY(__LINE__)
```
qFlagLocation函数位于Src\qtbase\src\corelib\kernel\qobject.cpp文件
```C++
const char *qFlagLocation(const char *method)
{
    QThreadData *currentThreadData = QThreadData::current(false);
    if (currentThreadData != 0)
        currentThreadData->flaggedSignatures.store(method);
    return method;
}
```

通过该宏可以看出，在本线程中，SIGNAL宏就是把信号的签名前面加上字符2,比如信号nameChange(QString)
```C++
 QObject::connect(&student, SIGNAL(nameChange(QString)), &studentView, SLOT(onNameChange(Qstring)));
```
就是转出"2nameChange(QString)"。
## 信号与曹连接时的的参数检查checkConnectArgs
Src\qtbase\src\corelib\kernel\qmetaobject.cpp
从源码中可以看出，
- 信号的参数个数>=槽的参数
- 槽的参数个数可以比信号的参数的数量少，但存在的参数类型必须依次与信号的一致。


```C++
bool QMetaObjectPrivate::checkConnectArgs(int signalArgc, const QArgumentType *signalTypes,
                                          int methodArgc, const QArgumentType *methodTypes)
{
    if (signalArgc < methodArgc)
        return false;
    for (int i = 0; i < methodArgc; ++i) {
        if (signalTypes[i] != methodTypes[i])
            return false;
    }
    return true;
}
```

# 参考
[https://doc.qt.io/qt-5.15/qmetaobject.html#details](https://doc.qt.io/qt-5.15/qmetaobject.html#details)

[https://doc.qt.io/qt-5.15/metaobjects.html](https://doc.qt.io/qt-5.15/metaobjects.html)