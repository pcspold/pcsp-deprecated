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
#include "qt4_psflineedit.h"
#include "types.h"
#include "../loaders.h"
#include <stdio.h>
#include "../UmdImageLoader.h"
#include "../isodrv.h"
#include "../isolib.h"
#include "psf.h"
psfLineEdit::psfLineEdit(QWidget *parent)
:   QLineEdit(parent)
{

}

psfLineEdit::~psfLineEdit()
{

}

void psfLineEdit::setpsfInfo(QListWidgetItem *item)
{
	QLineEdit::clear();
	QString text =item->data(Qt::UserRole).toString();
    
	umdimageloader::reboot(text.toLatin1().data());
  	u8 *psf = new u8[ISOFS_getfilesize("PSP_GAME/PARAM.SFO")];
    int f=ISOFS_open("PSP_GAME/PARAM.SFO", 1);
    ISOFS_read(f, (char*)psf, ISOFS_getfilesize("PSP_GAME/PARAM.SFO"));
    ISOFS_close(f);
    psf::load_psf(psf);
	if(objectName()=="gameNameEdit")
	{
		QLineEdit::setText(QString::fromUtf8(psfinfo.title));
	}
	if(objectName()=="discIdEdit")
	{
		QLineEdit::setText(psfinfo.disc_id);
	}
	if(objectName()=="firmwareEdit")
	{
        QLineEdit::setText(psfinfo.psp_system_version);
	}
}
void psfLineEdit::checkbootbin(QListWidgetItem *item)
{
	QLineEdit::clear();
   	QString text =item->data(Qt::UserRole).toString();
    u32 bootheader;
	umdimageloader::reboot(text.toLatin1().data());
	int bootbinsize = ISOFS_getfilesize("PSP_GAME/SYSDIR/BOOT.BIN");
	if(bootbinsize!=0)
	{
  	   u8 *bootbin = new u8[bootbinsize];
       int f=ISOFS_open("PSP_GAME/SYSDIR/BOOT.BIN", 1);
       ISOFS_read(f, (char*)bootbin, bootbinsize);
       ISOFS_close(f);
	   bootheader = *(u32*)bootbin;
	   if(bootheader==0x464c457f)
	   {
		 QLineEdit::setText("Not encrypted ELF");
		 return;
	   }
	   if(bootheader==0x5053507E)
	   {
          QLineEdit::setText("Encrypted BOOT.BIN(PSP~)");
		  return;
	   }
	   if(bootheader==0x4543537E)
	   {
         QLineEdit::setText("Encrypted BOOT.BIN(~SCE)");
		 return;
	   }
	   if(bootheader!=0)
	   {
         QLineEdit::setText("Unsupported Header on BOOT.BIN");
		 return;
	   }
	}

	if((bootbinsize ==0)||(bootheader==0))//probably encryption redirect to EBOOT.BIN
	{
	   int ebootbinsize = ISOFS_getfilesize("PSP_GAME/SYSDIR/EBOOT.BIN");
 	   u8 *ebootbin = new u8[ebootbinsize];
       int f=ISOFS_open("PSP_GAME/SYSDIR/EBOOT.BIN", 1);
       ISOFS_read(f, (char*)ebootbin, ebootbinsize);
       ISOFS_close(f);
       u32 ebootheader= *(u32*)ebootbin;
	   if(ebootheader==0x5053507E) //PSP~ header
	   {
		   QLineEdit::setText("Encrypted EBOOT.BIN (PSP~)");
		   return;
	   }
	   if(bootheader==0x4543537E)
	   {
         QLineEdit::setText("Encrypted EBOOT.BIN(~SCE)");
		 return;
	   }
	   else
	   {
         QLineEdit::setText("Unsupported Header on EBOOT.BIN");
		 return;
	   }
	}
	
}