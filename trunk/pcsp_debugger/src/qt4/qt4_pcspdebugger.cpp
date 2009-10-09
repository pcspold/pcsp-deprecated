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
#include "types.h"
#include "qt4_memorycursor.h"
#include "qt4_pcspdebugger.h"
#include "../debugger.h"

pcspdebugger::pcspdebugger(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{

	ui.setupUi(this);
	tabifyDockWidget(ui.memory_dock,ui.disassembly_dock);
    debugger.initialize();
		socket = new QLocalSocket(this);
 	connect(socket, SIGNAL(readyRead()), this, SLOT(onDataReceive()));
	connect(socket, SIGNAL(error(QLocalSocket::LocalSocketError)),this, SLOT(displayError(QLocalSocket::LocalSocketError)));
	connect(socket, SIGNAL(connected()), this, SLOT(onConnect()));

}

pcspdebugger::~pcspdebugger()
{
	
	debugger.finalize();
	delete socket;
}

void pcspdebugger::displayError(QLocalSocket::LocalSocketError socketError)
{

	ui.actionConnect->setText("Connect");
	ui.toolBar->setEnabled(false);

 switch (socketError) {
     case QLocalSocket::ServerNotFoundError:
         QMessageBox::information(this, tr("PCSP Debugger"),
                                  tr("The host was not found. Please check the "
                                     "host name and port settings."));
         break;
     case QLocalSocket::ConnectionRefusedError:
         QMessageBox::information(this, tr("PCSP Debugger"),
                                  tr("The connection was refused by the peer. "
                                     "Make sure the fortune server is running, "
                                     "and check that the host name and port "
                                     "settings are correct."));
         break;
    // case QLocalSocket::PeerClosedError:
    //     break;
     default:
         QMessageBox::information(this, tr("PCSP Debugger"),
                                  tr("The following error occurred: %1.")
                                  .arg(socket->errorString()));
     }
}


void pcspdebugger::onDataReceive()
{
	//TODO: Receive Data
}
void pcspdebugger::onActionConnectClick()
{


 if(ui.actionConnect->text().compare(QString("Connect"))==0)
 {
	 //TODO:Connection check
	
	ui.actionConnect->setText("Connecting...");
	socket->connectToServer("pcspserver");
	
 }
 else
 {
	socket->abort();
	ui.actionConnect->setText("Connect");
	ui.toolBar->setEnabled(false);
 }
 
 

}

void pcspdebugger::onConnect()
{
	ui.actionConnect->setText("Disconnect");
	ui.toolBar->setEnabled(true);
}