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
#include "types.h"
#include "../debugger.h"
#include "qt4_memorycursor.h"
#include "qt4_pcspdebugger.h"
#include "qt4_debugclient.h"

pcspdebugger *pcspdebugger::m_singleton = 0;
pcspdebugger::pcspdebugger(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
    m_singleton = this;
	ui.setupUi(this);
	tabifyDockWidget(ui.memory_dock,ui.disassembly_dock);
	tabifyDockWidget(ui.stdoutlog_dock,ui.logger_dock);
    debugger.initialize();	
	debugger.update_debugger();
}

pcspdebugger::~pcspdebugger()
{
	m_singleton = 0;
	debugger.finalize();

}
void debugger_s::update_debugger()
{
  	if (pcspdebugger::m_singleton)
	{
		pcspdebugger::m_singleton->ui.memorydockwidget->updateMemoryViewer();
	}
}
static const QColor tbl_color_codes[] = 
{
	Qt::black,
	Qt::red,
	Qt::green,
	Qt::yellow,
	Qt::blue,
	Qt::magenta,
	Qt::cyan,
	Qt::white,
	Qt::gray
};
void debugger_s::log(qint32 colorlevel,QString const &line)
{

   if (pcspdebugger::m_singleton->ui.loggerEditText) 
   {
	  /* QPalette p = pcspdebugger::m_singleton->ui.loggerEditText->palette();
       p.setColor(QPalette::Active, QPalette::Text, tbl_color_codes[colorlevel]);
	   p.setColor(QPalette::Inactive, QPalette::Text, tbl_color_codes[colorlevel]);
	   pcspdebugger::m_singleton->ui.loggerEditText->setPalette(p);*/
	/*   if(colorlevel==0)//another way
         pcspdebugger::m_singleton->ui.loggerEditText->setStyleSheet("color: blue");
	   if(colorlevel==1)
         pcspdebugger::m_singleton->ui.loggerEditText->setStyleSheet("color: red");*/
	   pcspdebugger::m_singleton->ui.loggerEditText->appendHtml(line);
   }
}
void debugger_s::logstdout(QString const &line)
{
   if (pcspdebugger::m_singleton->ui.stdoutEditText) 
   {
      pcspdebugger::m_singleton->ui.stdoutEditText->appendHtml(line);
   }
}
void pcspdebugger::onActionConnectClick()
{
	if(ui.actionConnect->text().compare(QString("Connect"))==0)
	{
		//TODO:Connection check
		ui.actionConnect->setText("Connecting...");
		client.loadClient(this);
		
	}
	else
	{
		client.closeClient();
		ui.actionConnect->setText("Connect");
		ui.toolBar->setEnabled(false);
	}
}
