#include "stdafx.h"

#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QMapIterator>
#include "nidgenerator.h"
#include "psplibxmlparser.h"
NIDgenerator::NIDgenerator(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

NIDgenerator::~NIDgenerator()
{

}
void NIDgenerator::ChooseXML()
{
      QString fileName = QFileDialog::getOpenFileName(this,
                                 tr("Choose a file to open"),
                                 "",
                                 tr("xml Files (*.xml);;xml Files (*.xml)"));


	if(fileName.isEmpty())
		return;
	ReadXML(fileName);
}
int NIDgenerator::ReadXML(QString filename)
{
  psplibxmlparser handler;
  handler.readFile(filename);
  QMap<QString,NIDrec>::const_iterator iter;
  for(iter = handler.NIDmap.begin(); iter !=handler.NIDmap.end(); ++iter) 
  {
	  QString lib = iter.key();
	  ui.infoTextEdit->appendHtml(lib);
  }
  return 0;
}
