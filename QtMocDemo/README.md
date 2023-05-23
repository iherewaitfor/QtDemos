
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
