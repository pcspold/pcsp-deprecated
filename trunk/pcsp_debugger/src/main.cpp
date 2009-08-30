#include "qt4\qt4_pcspdebugger.h"
#include <QtGui/QApplication>
#include "memory.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	pcspdebugger w;
	w.show();

	//unsigned int test = Memory::memw(0x89000e4); //TEST! 
    
	return a.exec();
}
