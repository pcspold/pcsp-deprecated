#include "qt4\qt4_pcspdebugger.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	pcspdebugger w;
	w.show();
	return a.exec();
}
