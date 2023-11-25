- [QtRemoteObjectdemos](#qtremoteobjectdemos)
- [registryconnected\_obejcts\_server](#registryconnected_obejcts_server)
- [registryconnected\_obejcts\_client](#registryconnected_obejcts_client)
- [QVarint](#qvarint)
  - [Q\_DECLARE\_METATYPE](#q_declare_metatype)
    - [Q\_DECLARE\_METATYPE宏展开](#q_declare_metatype宏展开)
  - [QMetaType](#qmetatype)
  - [qRegisterMetaType](#qregistermetatype)

# QtRemoteObjectdemos
# registryconnected_obejcts_server

- QRemoteObjectRegistryHost
- QRemoteObjectHost
  - enableRemoting
# registryconnected_obejcts_client

# QVarint

- Q_DECLARE_METATYPE
- QMetaType
- qRegisterMetaType
- qRegisterMetaTypeStreamOperators
  - Qt6废弃
- typeId()
  
## Q_DECLARE_METATYPE
该宏用于让QmetaType识别自定义的类型。只要该类型提供public的默认构造函数、拷贝构造函数和析构函数。使用该宏定义之后，对应的类型就可以在QVariant中使用了。

```C++
struct MyStruct
{
    int i;
    ...
};

Q_DECLARE_METATYPE(MyStruct)
```

带名字空间
```C++
namespace MyNamespace
{
    ...
}

Q_DECLARE_METATYPE(MyNamespace::MyStruct)
```
在QVariant中使用
```C++
MyStruct s;
QVariant var;
var.setValue(s); // copy s into the variant

...

// retrieve the value
MyStruct s2 = var.value<MyStruct>();
```

### Q_DECLARE_METATYPE宏展开
从以下看到Q_DECLARE_METATYPE的宏展开，有调用 qRegisterMetaType.
```C++
#define Q_DECLARE_METATYPE(TYPE) Q_DECLARE_METATYPE_IMPL(TYPE)
#define Q_DECLARE_METATYPE_IMPL(TYPE)                                   \
    QT_BEGIN_NAMESPACE                                                  \
    template <>                                                         \
    struct QMetaTypeId< TYPE >                                          \
    {                                                                   \
        enum { Defined = 1 };                                           \
        static int qt_metatype_id()                                     \
            {                                                           \
                static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
                if (const int id = metatype_id.loadAcquire())           \
                    return id;                                          \
                const int newId = qRegisterMetaType< TYPE >(#TYPE,      \
                              reinterpret_cast< TYPE *>(quintptr(-1))); \
                metatype_id.storeRelease(newId);                        \
                return newId;                                           \
            }                                                           \
    };                                                                  \
    QT_END_NAMESPACE
```

## QMetaType
QMetaType用于辅助在QVariant  或在queued信号槽 中 序列反序列化各数据类型。其关联一个名字和一个类型，以例该类型可以在运行时被创建或析构。
可以使用qRegisterMetaType()(或registerType()，该方法Qt6.5引入)注册一个类型的名字，到QMetaType中。大多数操作都不需要注册，只有在那些需要从一个字符名字转换回QMetaType或类型ID的操作才需要。比如一些使用QObject::connect的老风格的信号槽连接，从QDataStream读用户类型到QVariant，或绑定到其他语言或IPC机制：如QML、D-BUS、JavaScritpt等。

以下代码通过类型名字创建和析构Myclass实例，这需要MyClass类型被注册好。

```C++
QMetaType type = QMetaType::fromName("MyClass");
if (type.isValid()) {
    void *myClassPtr = type.create();
    ...
    type.destroy(myClassPtr);
    myClassPtr = nullptr;
}
```
如果需要存储自定义类型的QVariant上可以使用Stream操作符<<和>>，那就让自定义类型蜜必须实现操作符<<()和>>()。

QtRemotObject中，若使用自定义的类型，就需要这样操作。
## qRegisterMetaType
```C++
template <typename T> int qRegisterMetaType()
```
调用该函数去注册类型T。并返回元类型id。
```C++
int id = qRegisterMetaType<MyStruct>();
```
该函数需要在调用函数的时候，T是已经被完全定义的。对于指针类型，该函数也要要求被指向的类型是完全定义的。

在QMetaType,QVariant或QObject::property()API使用类型T时，注册不是必须的。
在queued信号槽连接中使用类型T，则必须在第一个连接建立前调用 qRegisterMetaType<T>()。标准的做法是在使用T的类的构造函数，或在main()函数里完成该调用 。

