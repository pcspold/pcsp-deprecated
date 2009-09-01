#ifndef QMEMORYVIEWER_H
#define QMEMORYVIEWER_H

#include <QtGui/QWidget>
#include "ui_qt4_memoryviewer.h"

class qt4_MemoryViewer : public QWidget
{
    Q_OBJECT

  public:
    qt4_MemoryViewer(QWidget *parent = 0);
    ~qt4_MemoryViewer();


  private:
	  Ui::memoryform ui;
};

#endif // QMEMORYVIEWER_H