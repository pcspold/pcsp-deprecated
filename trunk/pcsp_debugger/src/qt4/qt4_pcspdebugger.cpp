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
	connect(&client, SIGNAL(connected()),this, SLOT(onClientConnect()));
	connect(&client, SIGNAL(connected()),this, SLOT(onClientDisconnect()));
}

pcspdebugger::~pcspdebugger()
{
	debugger.finalize();
}

void pcspdebugger::onactionConnectClick()
{
	client.ConnectToHost("morgoth90.dyndns.org",22);
}

void pcspdebugger::onClientConnect()
{
	ui.toolBar->setEnabled(true);
}

void pcspdebugger::onClientDisconnect()
{
	ui.toolBar->setEnabled(false);
}