#ifndef NIDGENERATOR_H
#define NIDGENERATOR_H
#include <QDomDocument>
#include <QtGui/QMainWindow>
#include "ui_nidgenerator.h"

class NIDgenerator : public QMainWindow
{
	Q_OBJECT

public:
	NIDgenerator(QWidget *parent = 0, Qt::WFlags flags = 0);
	~NIDgenerator();
	int ReadXML(QString filename);
	public slots:
	void ChooseXML();
private:
	Ui::NIDgeneratorClass ui;
};

#endif // NIDGENERATOR_H
