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
#ifndef PCSPFRONTEND_H
#define PCSPFRONTEND_H

#include <QtGui/QMainWindow>


#include "ui_qt4_pcsp-xmb.h"

class pcspfrontend : public QMainWindow
{
    Q_OBJECT

public:
    pcspfrontend(QWidget *parent = 0, Qt::WFlags flags = 0,QString path = "");
    ~pcspfrontend();
    void refreshBrowser();
    void clearFormComponents();

private slots:
    void menu_changeUmdPath();
private:
    Ui::pcspfrontendClass ui;
    QString m_umdisospath;
};

#endif // PCSPFRONTEND_H
