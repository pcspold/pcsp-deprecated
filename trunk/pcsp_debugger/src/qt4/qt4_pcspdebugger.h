#ifndef PCSPDEBUGGER_H
#define PCSPDEBUGGER_H

#include <QtGui/QMainWindow>
#include "ui_qt4_pcspdebugger.h"

class pcspdebugger : public QMainWindow
{
	Q_OBJECT

public:
	pcspdebugger(QWidget *parent = 0, Qt::WFlags flags = 0);
	~pcspdebugger();

private:
	Ui::pcspdebuggerClass ui;
};

#endif // PCSPDEBUGGER_H
