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
#ifndef QPcspXmb_H
#define QPcspXmb_H

#include <QtCore>
#include <QtGui>

#include "ui_qpcspxmb.h"

#include "qumdmodel.h"
class MainWindowThread;
class ProgressCtrl;

class QPcspXmb : public QMainWindow, private Ui::PcspXmbUi
{
    Q_OBJECT

signals:
  void range(int, int);
  void label(const QString &);
  void progress(int);
public:
    QPcspXmb(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~QPcspXmb();
    void refresh();
	void run();
	void runInSeparateThread(QString text);
	MainWindowThread *thisThread;
	ProgressCtrl *progressCtrl;
	

protected:
    QRegion visualRegionForSelection(QItemSelection const &) const { return QRegion(); }

private slots:
    void onChangeUmdPath();
    void onModelReset();
    void onCurrentChanged(QModelIndex const &index);
    void onDoubleClicked(QModelIndex const &index);
    void onPressedButton();
	void textFilterChanged(QString text);
	void filterRegExpChanged(int column);
	void thisThreadStarted();
	void thisThreadFinished();
	void setStop();
	


private:
    QString                m_umdisospath;
    QUmdTableModel        *m_sourceModel;
    QSortFilterProxyModel *m_model;
    QDataWidgetMapper     *m_mapper;
    QItemSelectionModel   *m_selectionModel;
    QSystemTrayIcon       *m_systray;
    QSettings              m_ini;
	bool m_stop;
};
#include <QThread>
class MainWindowThread : public QThread  
{
  Q_OBJECT
public:
  MainWindowThread(QPcspXmb *mainWindow)
    : mainWindow(mainWindow){};
  virtual ~MainWindowThread(){};
 
  void run() {mainWindow->run();}
protected:
  QPcspXmb *mainWindow;
};

#endif // QPcspXmb_H
