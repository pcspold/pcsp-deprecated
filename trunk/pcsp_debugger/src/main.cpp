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
