- [QtRemoteObjectdemos](#qtremoteobjectdemos)
- [QVarint](#qvarint)
  - [Q\_DECLARE\_METATYPE](#q_declare_metatype)
  - [QMetaType](#qmetatype)
  - [qRegisterMetaType](#qregistermetatype)

# QtRemoteObjectdemos

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

