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

   // // connect source replica signal currStateChanged() with client's recSwitchState() slot to receive source's current state
   //QObject::connect(reptr.data(), SIGNAL(currStateChanged(bool)), this, SLOT(recSwitchState_slot(bool)));
   //// connect client's echoSwitchState(..) signal with replica's server_slot(..) to echo back received state
   //QObject::connect(this, SIGNAL(echoSwitchState(bool)),reptr.data(), SLOT(server_slot(bool)));

   
   // QRemoteObjectPendingCallWatcher callwathcer(call);
   //QMetaObject::Connection c = QObject::connect(m_callwathcer, SIGNAL(finished(QRemoteObjectPendingCallWatcher*)), this, SLOT(pendingCallResult(QRemoteObjectPendingCallWatcher*)));

    QObject::connect(&testTimer, SIGNAL(timeout()), this, SLOT(timerOut()));
    testTimer.setInterval(5000);
 //   testTimer.start();

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



   //bool isCalled = call.isFinished();
   //m_callwathcer->error();

   //success = QMetaObject::invokeMethod(reptr.data(), "onIncreace", Qt::AutoConnection);


   //auto e = call.error();// , QRemoteObjectPendingCall::InvalidMessage);

   //call.waitForFinished();

   ////QVERIFY(call.isFinished());
   ////QCOMPARE(call.returnValue().type(), QVariant::String);
   //qDebug()<< " result of call add : " << QMetaType::typeName(call.returnValue().type()) << call.returnValue().toString();

}


void DynamicClient::recSwitchState_slot(bool value)
{
   clientSwitchState = reptr->property("currState").toBool(); // use replica property to get "currState" from source
   qDebug() << "Received source state " << value << clientSwitchState;
   Q_EMIT echoSwitchState(clientSwitchState); // Emit signal to echo received state back to server
}

void DynamicClient::pendingCallResult(QRemoteObjectPendingCallWatcher* call) {

    qDebug() << "pendingCallResult call add : " << QMetaType::typeName(call->returnValue().type()) << call->returnValue().toString();
    sender()->deleteLater(); // 待优化。若无信号返回，则会造成内存泄漏
}
void DynamicClient::timerOut() {
    //有返回值
    QRemoteObjectPendingCall call;
    bool success = QMetaObject::invokeMethod(reptr.data(), "addCount", Qt::AutoConnection,
        Q_RETURN_ARG(QRemoteObjectPendingCall, call),
        Q_ARG(int, 5)
    );
    QRemoteObjectPendingCallWatcher* callwathcer = new QRemoteObjectPendingCallWatcher(call);
    QMetaObject::Connection c = QObject::connect(callwathcer, SIGNAL(finished(QRemoteObjectPendingCallWatcher*)), this, SLOT(pendingCallResult(QRemoteObjectPendingCallWatcher*)));

    //无返回值，直接调用
    QMetaObject::invokeMethod(reptr.data(), "onIncreace", Qt::AutoConnection);
}
