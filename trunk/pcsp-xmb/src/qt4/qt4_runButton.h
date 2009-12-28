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
#ifndef QT4_RUNBUTTON_H
#define QT4_RUNBUTTON_H

#include<QPushButton>
#include<QListWidgetItem>

class runButtonclass : public QPushButton
{
	Q_OBJECT

public:
	runButtonclass(QWidget *parent);
	~runButtonclass();
    QListWidgetItem *m_item;
public slots:
	void enableRunButton(QListWidgetItem *);
	void click();
};

#endif // QT4_RUNBUTTON_H
