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

#include <QtGui/QApplication>
#include <qfile.h>
#include <qmessagebox.h>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QSettings>
#include "qt4_pcspfrontend.h"

void center(QWidget &widget)
{
  int x, y;
  int screenWidth;
  int screenHeight;
  int width, height;
  QSize windowSize;

  QDesktopWidget *desktop = QApplication::desktop();

  width = widget.frameGeometry().width();
  height = widget.frameGeometry().height();  

  screenWidth = desktop->width();
  screenHeight = desktop->height();
 
  x = (screenWidth - width) / 2;
  y = (screenHeight - height) / 2;

  widget.move( x, y );
}

QString findDirectory()
{
	//TODO Create umdfolder if not exist
     QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
     QString directory = QFileDialog::getExistingDirectory(0,
                                 "Select the umd isos folder",
                                 "umdimages/",
                                 options);
	 
	 return directory;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    QSettings settings("settings.ini", QSettings::IniFormat);

    
    QString dir;
	QString readvalue = settings.value("umdpath","").toString();
	if(readvalue.isEmpty())
	{
      	QMessageBox::critical(0,"PCSP Frontend","Unable to find settings ini");
		dir = findDirectory();
	}
	else
	{
       dir=readvalue;
	}
	settings.setValue("umdpath",dir);
    
	pcspfrontend w(0,0,dir);
	center(w);
	w.show();
	
	return a.exec();
}
