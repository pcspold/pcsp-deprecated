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
#include "qt4_pcspfrontend.h"
#include <qdir.h>
#include<QListWidgetItem>
#include <QDirModel>
#include <QBuffer>
#include <QFileDialog>
#include "types.h"
#include "../loaders.h"
#include <stdio.h>
#include <QSettings>
pcspfrontend::pcspfrontend(QWidget *parent, Qt::WFlags flags,QString path)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	 

	umdisospath=path;
    refreshBrowser();
}

pcspfrontend::~pcspfrontend()
{

	
		 
}
void pcspfrontend::clearFormComponents()
{
  	 ui.icon0list->clear();//clear list
	 ui.gameNameEdit->clear();
     ui.discIdEdit->clear();
	 ui.firmwareEdit->clear();
	 ui.lineEdit->clear();
	 ui.pic1label->clear();
	 ui.runButton->setEnabled(false); //and disable button

}
void pcspfrontend::refreshBrowser()
{
	//get the isos
	QDir d(umdisospath);
	d.setFilter(QDir::Files);
     QFileInfoList list = d.entryInfoList();
     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
		 QString suffix = fileInfo.suffix().toUpper();
		 if (((suffix != "CSO") && (suffix != "ISO")))//no iso found
			 continue;
		  QString fullpath = umdisospath + "/" + fileInfo.fileName();
		  loaders::load_file(fullpath.toLatin1().data());
		 QListWidgetItem *lst1 =new QListWidgetItem(ui.icon0list );
		 lst1->setData(Qt::UserRole,fullpath);
         QImage image;
		 bool ok = image.loadFromData(loaders::icon0,loaders::icon0size);
         lst1->setIcon(QIcon(QPixmap::fromImage(image)));
		 ui.icon0list->insertItem(i+1,lst1);
	 }
}
void pcspfrontend::menu_changeUmdPath()
{
     QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
     QString directory = QFileDialog::getExistingDirectory(0,
                                 "Select the umd isos folder",
                                 "umdimages/",
                                 options);
	 umdisospath=directory;//change the directory to the new one
	 QSettings settings("settings.ini", QSettings::IniFormat);//save the new path
	 settings.setValue("umdpath",umdisospath);
     clearFormComponents();
	 refreshBrowser();
}
