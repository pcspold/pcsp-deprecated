#include "qt4_pcspdebugger.h"
#include "../debugger.h"

pcspdebugger::pcspdebugger(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	tabifyDockWidget(ui.memory_dock,ui.disassembly_dock);
    debugger.initialize();
}

pcspdebugger::~pcspdebugger()
{
	debugger.finalize();
}
