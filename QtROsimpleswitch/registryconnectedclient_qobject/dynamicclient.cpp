/****************************************************************************
**
** Copyright (C) 2017 Ford Motor Company
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtRemoteObjects module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "dynamicclient.h"
 #include <QMetaMethod>
#include <QRemoteObjectPendingCall>

// constructor
DynamicClient::DynamicClient(QSharedPointer<QRemoteObjectDynamicReplica> ptr) :
    QObject(nullptr), clientSwitchState(false), reptr(ptr)
{
    m_callwathcer = new QRemoteObjectPendingCallWatcher(call);
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

   // // connect source replica signal currStateChanged() with client's recSwitchState() slot to receive source's current state
   //QObject::connect(reptr.data(), SIGNAL(currStateChanged(bool)), this, SLOT(recSwitchState_slot(bool)));
   //// connect client's echoSwitchState(..) signal with replica's server_slot(..) to echo back received state
   //QObject::connect(this, SIGNAL(echoSwitchState(bool)),reptr.data(), SLOT(server_slot(bool)));

   
   // QRemoteObjectPendingCallWatcher callwathcer(call);
   QMetaObject::Connection c = QObject::connect(m_callwathcer, SIGNAL(finished(QRemoteObjectPendingCallWatcher*)), this, SLOT(pendingCallResult(QRemoteObjectPendingCallWatcher*)));

    QObject::connect(&testTimer, SIGNAL(timeout()), this, SLOT(timerOut()));
    testTimer.setInterval(5000);
    testTimer.start();

   QRemoteObjectPendingCall call;
   QString retVal;
   bool success = QMetaObject::invokeMethod(reptr.data(), "addCount", Qt::AutoConnection,
	   Q_RETURN_ARG(QRemoteObjectPendingCall, call),
	   //Q_ARG(int, 3),
       Q_ARG(int, 5)
   );
   bool isCalled = call.isFinished();
   m_callwathcer->error();

   success = QMetaObject::invokeMethod(reptr.data(), "onIncreace", Qt::AutoConnection,
       Q_RETURN_ARG(QRemoteObjectPendingCall, call)
       //Q_ARG(int, 3),
       //Q_ARG(int, 5)
   );


   auto e = call.error();// , QRemoteObjectPendingCall::InvalidMessage);

   call.waitForFinished();

   //QVERIFY(call.isFinished());
   //QCOMPARE(call.returnValue().type(), QVariant::String);
   qDebug()<< " call add : " << QMetaType::typeName(call.returnValue().type()) << call.returnValue().toString();

}


void DynamicClient::recSwitchState_slot(bool value)
{
   clientSwitchState = reptr->property("currState").toBool(); // use replica property to get "currState" from source
   qDebug() << "Received source state " << value << clientSwitchState;
   Q_EMIT echoSwitchState(clientSwitchState); // Emit signal to echo received state back to server
}

void DynamicClient::pendingCallResult(QRemoteObjectPendingCallWatcher* call) {

    qDebug() << " call add : " << QMetaType::typeName(call->returnValue().type()) << call->returnValue().toString();
}
void DynamicClient::timerOut() {
    QRemoteObjectPendingCall call;

    QRemoteObjectPendingCallWatcher* callwathcer = new QRemoteObjectPendingCallWatcher(call);
    QMetaObject::Connection c = QObject::connect(callwathcer, SIGNAL(finished(QRemoteObjectPendingCallWatcher*)), this, SLOT(pendingCallResult(QRemoteObjectPendingCallWatcher*)));

    QString retVal;
    bool success = QMetaObject::invokeMethod(reptr.data(), "addCount", Qt::AutoConnection,
        Q_RETURN_ARG(QRemoteObjectPendingCall, call),
        //Q_ARG(int, 3),
        Q_ARG(int, 5)
    );
    //bool isCalled = call.isFinished();
    //m_callwathcer->error();

    success = QMetaObject::invokeMethod(reptr.data(), "onIncreace", Qt::AutoConnection,
        Q_RETURN_ARG(QRemoteObjectPendingCall, call)
        //Q_ARG(int, 3),
        //Q_ARG(int, 5)
    );
}
