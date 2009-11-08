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
#pragma once
#include <QObject>
#include <QtNetwork>
#include <qlocalsocket.h>
#include <QtGui/QMainWindow>
#include <QtGui>

#define CLIENT_LOG              2
#define CLIENT_UPDATE_ALL       3
#define CLIENT_UPDATE_REGISTERS 5

class qt4_debugClient: public QObject
{
	Q_OBJECT
public:
	static qt4_debugClient& Instance() { static qt4_debugClient client; return client; }
private:
	qt4_debugClient(void);
	~qt4_debugClient(void);
	 QLocalSocket *socket;
	 QMainWindow *parentwindow;
public:
	void loadClient(QMainWindow *parent);
	void closeClient();
private slots:
	void displayError(QLocalSocket::LocalSocketError socketError);
	void onDataReceive();
	void onConnect();
};

#define client qt4_debugClient::Instance()
