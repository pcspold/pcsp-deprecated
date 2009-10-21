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
#include "stdafx.h"
#include "qt4_memoryspinbox.h"
#include "QtGui/QMessageBox"

qt4_MemorySpinBox::qt4_MemorySpinBox(QWidget *parent)
: QSpinBox(parent)
{
}

qt4_MemorySpinBox::~qt4_MemorySpinBox()
{
}

QValidator::State qt4_MemorySpinBox::validate(QString &input, int &pos) const
{
  if (isxdigit(input[pos].cell()))
  {
    if (input.size() < 8)
      return QValidator::Intermediate;
    else if (input.size() == 8)
      return QValidator::Acceptable;
  }
  return QValidator::Invalid;
}

QString qt4_MemorySpinBox::textFromValue(int value) const
{
  return QString("%1").arg((unsigned int)value, 8, 16, QChar('0')).toUpper();
}

int qt4_MemorySpinBox::valueFromText(const QString &text) const
{
  return text.toInt(0, 16);
}
