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
#include "qt4_runButton.h"
#include "types.h"
#include "psf.h"
#include <qprocess.h>

runButtonclass::runButtonclass(QWidget *parent)
	: QPushButton(parent)
{
     templist= new QListWidgetItem();
}

runButtonclass::~runButtonclass()
{

}
void runButtonclass::enableRunButton(QListWidgetItem* list)
{
	QPushButton::setEnabled(true);
	templist=list;
}
void runButtonclass::click()
{
   
   QString umdpath = templist->data(Qt::UserRole).toString();
   QString discID = psfinfo.disc_id;
   //QString constructcommand = "pcsp-" + discID + " -f " + umdpath;
   QProcess *RunExe=new QProcess(this);
   QStringList arguments;
   arguments << "/f" << umdpath;
   RunExe->start("pcsp-" + discID,arguments);

}