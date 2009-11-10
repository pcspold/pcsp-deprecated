/*
This file is part of pcsp.

pcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pcsp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "stdafx.h"
#include "qt4_debugclient.h"
#include "qt4_pcspdebugger.h"
#include <qtgui>
#include <QMessageBox>
#include <vector>
#include "debugger.h"

using namespace std;

struct StatusMessage
{
	//unsigned int codeAddress;
	//vector <unsigned int> stack;
	unsigned int registers[35];		//gpr[0] to gpr[31] + pc + hi + lo
};

qt4_debugClient::qt4_debugClient(void)
{
}

qt4_debugClient::~qt4_debugClient(void)
{
}
void qt4_debugClient::loadClient(QMainWindow *parent)
{
    socket = new QTcpSocket(this);

    parentwindow=parent;	
    connect(socket, SIGNAL(readyRead()),this, SLOT(onDataReceive()));
	connect(socket, SIGNAL(error(QLocalSocket::LocalSocketError)),this, SLOT(displayError(QLocalSocket::LocalSocketError)));
	connect(socket, SIGNAL(connected()),this, SLOT(onConnect()));
	socket->connectToHost( QHostAddress::LocalHost, 55342, QIODevice::ReadWrite);
}
void qt4_debugClient::closeClient()
{
	if(socket!=NULL)
     socket->abort();
}
void qt4_debugClient::displayError(QLocalSocket::LocalSocketError socketError)
{
	pcspdebugger::m_singleton->ui.actionConnect->setText("Connect");
	pcspdebugger::m_singleton->ui.toolBar->setEnabled(false);

 switch (socketError) {
     case QLocalSocket::ServerNotFoundError:
         QMessageBox::information(parentwindow, tr("PCSP Debugger"),
                                  tr("The host was not found. Please check the "
                                     "host name and port settings."));
         break;
     case QLocalSocket::ConnectionRefusedError:
         QMessageBox::information(parentwindow, tr("PCSP Debugger"),
                                  tr("The connection was refused by the peer. "
                                     "Make sure the fortune server is running, "
                                     "and check that the host name and port "
                                     "settings are correct."));
         break;
    // case QLocalSocket::PeerClosedError:
    //     break;
     default:
         QMessageBox::information(parentwindow, tr("PCSP Debugger"),
                                  tr("The following error occurred: %1.")
                                  .arg(socket->errorString()));
     }
}

void qt4_debugClient::onDataReceive()
{
  forever {
       if (socket->bytesAvailable() < (int) sizeof(quint16))//if no bytes available not continue further
        break;

	 QDataStream in(socket);
     in.setVersion(QDataStream::Qt_4_5);
	 qint32 gettype;
	 in >> gettype;
	 if(gettype==0) break;
	 QString separator;
	 in >> separator; //normaly "|" should be after
	 switch(gettype)
	 {
	 case CLIENT_LOG:
		 {
		   QString getlog;
		   qint32 colorlevel;
		   in>>colorlevel;
		   in>>getlog;
		   debugger.log(colorlevel,getlog);
		   debugger.writelog(getlog);
		 }
		 break;
	 case CLIENT_UPDATE_ALL://update everything!
		 {
		   debugger.update_debugger();	
		   QString getmessage;
		   in >>getmessage;
		   parentwindow->statusBar()->showMessage(getmessage);
		 }
		 break;
     case CLIENT_UPDATE_REGISTERS:
		 {
         //  quint32 pcregister;
		 //  in >> pcregister;
		 //  printf("test");
		 }
		 break;
	 default:
      //  QMessageBox::information(parentwindow, tr("PCSP Debugger Fatal Error"), tr("server sent unsupported command!"));
        break;
	 }
  }

}
void qt4_debugClient::onConnect()
{
	pcspdebugger::m_singleton->ui.actionConnect->setText("Disconnect");
	pcspdebugger::m_singleton->ui.toolBar->setEnabled(true);
}

