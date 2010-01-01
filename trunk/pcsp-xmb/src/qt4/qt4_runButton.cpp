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
#include <qfile>
#include <qmessagebox.h>

runButtonclass::runButtonclass(QWidget *parent)
: QPushButton(parent)
{
     m_item = new QListWidgetItem();
}

runButtonclass::~runButtonclass()
{

}
void runButtonclass::enableRunButton(QListWidgetItem *item)
{
	QPushButton::setEnabled(true);
	m_item = item;
}
void runButtonclass::click()
{
   QString umdpath = m_item->data(Qt::UserRole).toString();
   QString discID = psfinfo.disc_id;  
   QProcess launcher(this);
   QStringList arguments;
   //figure out if we have a specific version of the game
   QFile spec("pcsp-"+discID+".exe");
   QFile gener("pcsp.exe");
   arguments << "/f" << umdpath;
   if(spec.exists())
   {
     launcher.start("pcsp-" + discID+".exe", arguments);
   }
   else if(gener.exists())
   {
     launcher.start("pcsp.exe", arguments);
   }
   else
   {
      QMessageBox::critical(0,"PCSP Frontend","Can't find an emulator exe!");
   }
   
   
}