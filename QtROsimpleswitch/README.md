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

