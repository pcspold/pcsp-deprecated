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
#ifndef QT4_PIC1LABEL_H
#define QT4_PIC1LABEL_H

#include <QLabel>
#include<QListWidgetItem>

class pic1labelclass : public QLabel
{
	Q_OBJECT

public:
	pic1labelclass(QWidget *parent);
	~pic1labelclass();

public slots:
    void displaypic(QListWidgetItem *);
private:
	
};

#endif // QT4_PIC1LABEL_H
