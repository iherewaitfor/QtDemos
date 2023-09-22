
# QMetaType

void* retValPtr = QMetaType::create(typeId)

const char * QMetaType::typeName(int typeId)

QVariant(int typeId, const void *copy)

to do:

QVariant to void*

const void *QVariant::constData()
## Q_DECLARE_METATYPE(Type)
使用该宏定义之后，QMetaType就知道该类型了。
使用该宏的类的条件
- 有public的默认构造函数
- 有public的拷贝构建函数
- 有public的构建函数

自定义的类用该宏之后 ，就可以在QVariant中使用了。

另外，如果要在信号和槽中使用自定义类型，需要先使用q

# QMetaMethod

## QMetaMethod::invoke
```C++
bool QMetaMethod::invoke(QObject *object,
                         Qt::ConnectionType connectionType,
                         QGenericReturnArgument returnValue,
                         QGenericArgument val0,
                         QGenericArgument val1,
                         QGenericArgument val2,
                         QGenericArgument val3,
                         QGenericArgument val4,
                         QGenericArgument val5,
                         QGenericArgument val6,
                         QGenericArgument val7,
                         QGenericArgument val8,
                         QGenericArgument val9) const

```

# Q_ARG 及 Q_RETURN_ARG
## Q_ARG
参数Q_ARG
```C++
#define Q_ARG(type, data) QArgument<type >(#type, data)


template <class T>
class QArgument: public QGenericArgument
```
## Q_RETURN_ARG
返回值
```C++
#define Q_RETURN_ARG(type, data) QReturnArgument<type >(#type, data)

//QReturnArgument
template <typename T>
class QReturnArgument: public QGenericReturnArgument
{
public:
    inline QReturnArgument(const char *aName, T &aData)
        : QGenericReturnArgument(aName, static_cast<void *>(&aData))
        {}
};

//对应的QGenericReturnArgument
class Q_CORE_EXPORT QGenericReturnArgument: public QGenericArgument
{
public:
    inline QGenericReturnArgument(const char *aName = nullptr, void *aData = nullptr)
        : QGenericArgument(aName, aData)
        {}
};

```


