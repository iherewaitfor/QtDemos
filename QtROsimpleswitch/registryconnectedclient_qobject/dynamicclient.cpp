#include "dynamicclient.h"
 #include <QMetaMethod>
#include <QRemoteObjectPendingCall>

// constructor
DynamicClient::DynamicClient(QSharedPointer<QRemoteObjectDynamicReplica> ptr) :
    QObject(nullptr), clientSwitchState(false), reptr(ptr)
{
    //connect signal for replica valid changed with signal slot initialization
    QObject::connect(reptr.data(), SIGNAL(initialized()), this, SLOT(initConnection_slot()));
}

//destructor
DynamicClient::~DynamicClient()
{

}

// Function to initialize connections between slots and signals
void DynamicClient::initConnection_slot()
{
    const QMetaObject* meta = reptr->metaObject();
    for (int i = 0; i < meta->methodCount(); i++) {
        QMetaMethod method = meta->method(i);
        qDebug() << " method " << i<< " " << 
            method.returnType()<< QMetaType::typeName(method.returnType()) << " " << method.methodSignature();
    }

    // connect source replica signal counterChanged()
   QObject::connect(reptr.data(), SIGNAL(counterChanged(int)), this, SLOT(onCounterChanged_slot(int)));
   // connect client's echoSwitchState(..) signal with replica's server_slot(..) to echo back received state
   QObject::connect(this, SIGNAL(makeSourceEmit()),reptr.data(), SLOT(onIncreace()));

    QObject::connect(&testTimer, SIGNAL(timeout()), this, SLOT(timerOut()));
    testTimer.setInterval(5000);
    testTimer.start();
   QRemoteObjectPendingCall call;
   QString retVal;
   bool success = QMetaObject::invokeMethod(reptr.data(), "addCount", Qt::AutoConnection,
	   Q_RETURN_ARG(QRemoteObjectPendingCall, call),
       Q_ARG(int, 5)
   );

   //to do:  how to free?   temply free at slot.
   QRemoteObjectPendingCallWatcher* callwathcer = new QRemoteObjectPendingCallWatcher(call);
   QObject::connect(callwathcer, SIGNAL(finished(QRemoteObjectPendingCallWatcher*)), this, SLOT(pendingCallResult(QRemoteObjectPendingCallWatcher*)));


   //带返回值，但不需要返回值时
   QMetaObject::invokeMethod(reptr.data(), "addQString", Qt::AutoConnection,
       Q_ARG(QString, "500")
   );

   //无返回值方法调用
   QMetaObject::invokeMethod(reptr.data(), "addNoReturn", Qt::AutoConnection,
       Q_ARG(int, 10)
   );

   Q_EMIT makeSourceEmit();
}


void DynamicClient::onCounterChanged_slot(int counter)
{
   int c = reptr->property("counter").toInt();
   qDebug() << "Replica property counter= " << c << " onCounterChanged_slot: counter=" << counter;

}

void DynamicClient::pendingCallResult(QRemoteObjectPendingCallWatcher* call) {

    qDebug() << "pendingCallResult call add : " << QMetaType::typeName(call->returnValue().type()) << call->returnValue().toString();
    sender()->deleteLater(); // 待优化。若无信号返回，则会造成内存泄漏
}
void DynamicClient::timerOut() {
    int c = reptr->property("counter").toInt();
    qDebug() << "timerOut Replica property counter= " << c;

}
