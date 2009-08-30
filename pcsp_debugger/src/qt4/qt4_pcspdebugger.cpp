#include "qt4_pcspdebugger.h"
#include "../debugger.h"

pcspdebugger::pcspdebugger(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
    debugger.initialize();
}

pcspdebugger::~pcspdebugger()
{
	debugger.finalize();
}
