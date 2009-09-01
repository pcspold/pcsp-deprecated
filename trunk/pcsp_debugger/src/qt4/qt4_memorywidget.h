#ifndef QT4_MEMORYWIDGET_H
#define QT4_MEMORYWIDGET_H

#include <QtGui/QWidget>


class qt4_MemoryWidget : public QWidget
{
  Q_OBJECT

  public:
    qt4_MemoryWidget(QWidget *parent = 0);
    ~qt4_MemoryWidget();

  protected:
  void paintEvent(QPaintEvent *e);
};

#endif