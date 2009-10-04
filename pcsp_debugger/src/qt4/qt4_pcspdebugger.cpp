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
	connect(socket, SIGNAL(error()),this, SLOT(onSocketError()));
	
	socket->connectToServer("127.0.0.1:7277");
}

pcspdebugger::~pcspdebugger()
{
	debugger.finalize();
	delete socket;
}

void pcspdebugger::onSocketError()
{
	QMessageBox::information(this, tr("Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(socket->errorString()));
}


void pcspdebugger::onDataReceive()
{
	//TODO: Receive Data
}