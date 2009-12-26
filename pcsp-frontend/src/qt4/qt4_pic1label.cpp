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
#include "qt4_pic1label.h"

#include "types.h"
#include "../loaders.h"
#include <stdio.h>
#include "../UmdImageLoader.h"
#include "../isodrv.h"
#include "../isolib.h"
pic1labelclass::pic1labelclass(QWidget *parent)
	: QLabel(parent)
{

}

pic1labelclass::~pic1labelclass()
{
	
}
void pic1labelclass::displaypic(QListWidgetItem* list)
{
	QString text =list->data(Qt::UserRole).toString();

	umdimageloader::reboot(text.toLatin1().data());
	u8 *pic1 = new u8[ISOFS_getfilesize("PSP_GAME/PIC1.PNG")];
    int f=ISOFS_open("PSP_GAME/PIC1.PNG", 1);
	int pic1size =ISOFS_getfilesize("PSP_GAME/PIC1.PNG");
	ISOFS_read(f, (char*)pic1,pic1size );
    ISOFS_close(f);	
	QImage image;
	bool ok = image.loadFromData(pic1,pic1size);
	QLabel::clear();
	QLabel::setPixmap(QPixmap::fromImage(image));
}