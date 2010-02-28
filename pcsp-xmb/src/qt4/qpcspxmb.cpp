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
#include "qpcspxmb.h"
#include <QtCore>
#include <QtGui>

#include "types.h"
#include "../loaders.h"
#include <stdio.h>

#include "qumdmodel.h"

QPcspXmb::QPcspXmb(QWidget *parent, Qt::WFlags flags, QString const &path)
:   QMainWindow(parent, flags)
,   Ui::PcspXmbUi()
,   m_selectionModel(0)
{
    setupUi(this);

    m_umdisospath = path;
    m_model  = new QUmdTableModel(path, this);
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);
    m_mapper->addMapping(discIdEdit,   1);
    m_mapper->addMapping(gameNameEdit, 2);
    m_mapper->addMapping(firmwareEdit, 4);
    m_mapper->addMapping(statusEdit,   5);
    m_mapper->addMapping(crc32Edit,    6);
    m_mapper->toFirst();

    m_selectionModel = icon0List->selectionModel();

    connect(m_model, SIGNAL(modelReset()), this, SLOT(onModelReset()));

    icon0List->setModel(m_model);
    icon0List->setModelColumn(0);

    QAction *action = new QAction(tr("Change UMD images folder"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(onChangeUmdPath()));
    icon0List->addAction(action);

    connect(icon0List, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onDoubleClicked(QModelIndex)));
    connect(runButton, SIGNAL(clicked()), this, SLOT(onPressedButton()));

    refresh();
}

QPcspXmb::~QPcspXmb()
{
}

void QPcspXmb::onModelReset()
{
    if (m_selectionModel)
    {
        delete m_selectionModel;
    }

    m_selectionModel = new QItemSelectionModel(m_model, this);
    icon0List->setSelectionModel(m_selectionModel);
    connect(m_selectionModel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(onCurrentChanged(QModelIndex)));
}

void QPcspXmb::onCurrentChanged(QModelIndex const &index)
{
    m_mapper->setCurrentModelIndex(index);
    pic1Label->setPixmap(qVariantValue<QPixmap>(index.sibling(index.row(), 3).data(Qt::DecorationRole)));
    icon0List->scrollTo(index, QAbstractItemView::PositionAtCenter);
}

void QPcspXmb::onDoubleClicked(QModelIndex const &index)
{
    QString umdpath = index.data(Qt::UserRole).toString();
    QString discID  = index.sibling(index.row(), 1).data(Qt::DisplayRole).toString();  
    QProcess launcher(this);
    QStringList arguments;
    arguments << "-umd" << umdpath;
    if (!launcher.startDetached("pcsp-" + discID, arguments))
    {
        if (!launcher.startDetached("pcsp", arguments))
        {
            QMessageBox::critical(0, tr("PCSP - XMB"), tr("Cannot find the emulator executable to play %1!").arg(index.sibling(index.row(), 2).data(Qt::DisplayRole).toString()));
        }
    }
}

void QPcspXmb::onPressedButton()
{
    QModelIndex index = m_selectionModel->currentIndex();
    onDoubleClicked(index);
}

void QPcspXmb::refresh()
{
    m_model->updateModel(m_umdisospath);
}

void QPcspXmb::onChangeUmdPath()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString newPath = QFileDialog::getExistingDirectory(0, tr("Select the umd images folder"), m_umdisospath, options);
    if (newPath.size())
    {
        m_umdisospath = newPath;
        QSettings("settings.ini", QSettings::IniFormat).setValue("umdpath", m_umdisospath);
        refresh();
    }
}
