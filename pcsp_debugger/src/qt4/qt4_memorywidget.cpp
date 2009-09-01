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