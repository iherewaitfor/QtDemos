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
    if (m_callwathcer) {
        delete m_callwathcer;
        m_callwathcer = NULL;
    }
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

   //QRemoteObjectPendingCall call;
   QString retVal;
   bool success = QMetaObject::invokeMethod(reptr.data(), "addCount", Qt::AutoConnection,
	   Q_RETURN_ARG(QRemoteObjectPendingCall, call),
       Q_ARG(int, 5)
   );
   m_callwathcer = new QRemoteObjectPendingCallWatcher(call);
   QObject::connect(m_callwathcer, SIGNAL(finished(QRemoteObjectPendingCallWatcher*)), this, SLOT(pendingCallResult(QRemoteObjectPendingCallWatcher*)));

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
}
void DynamicClient::timerOut() {
    QRemoteObjectPendingCall call;

  
    QString retVal;
    bool success = QMetaObject::invokeMethod(reptr.data(), "addCount", Qt::AutoConnection,
        Q_RETURN_ARG(QRemoteObjectPendingCall, call),
        //Q_ARG(int, 3),
        Q_ARG(int, 5)
    );
    QRemoteObjectPendingCallWatcher* callwathcer = new QRemoteObjectPendingCallWatcher(call);
    QMetaObject::Connection c = QObject::connect(callwathcer, SIGNAL(finished(QRemoteObjectPendingCallWatcher*)), this, SLOT(pendingCallResult(QRemoteObjectPendingCallWatcher*)));

    //bool isCalled = call.isFinished();
    //m_callwathcer->error();

    success = QMetaObject::invokeMethod(reptr.data(), "onIncreace", Qt::AutoConnection,
        Q_RETURN_ARG(QRemoteObjectPendingCall, call)
        //Q_ARG(int, 3),
        //Q_ARG(int, 5)
    );
}
