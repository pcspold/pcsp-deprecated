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
#include "qt4_memorywidget.h"  
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QProgressDialog>
#include <QPainter>
#include <QPixmap>
#include <QFocusEvent>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>
#include <QStyle>
#include <QStyleOption>

qt4_MemoryWidget::qt4_MemoryWidget(QWidget *parent)
: QWidget(parent)
{

}

qt4_MemoryWidget::~qt4_MemoryWidget()
{

}
void qt4_MemoryWidget::paintEvent(QPaintEvent *e)
{
  QStyleOption option;
  option.initFrom(this);
  option.state = hasFocus() ? QStyle::State_HasFocus : QStyle::State_Enabled;

  QPainter p(this);

  p.setFont(font());
  p.setBrush(qApp->palette().base());

  style()->drawPrimitive(QStyle::PE_FrameLineEdit, &option, &p, this);
}