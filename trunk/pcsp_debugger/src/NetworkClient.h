#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>


class NetworkClient : public QObject
{
public:
	NetworkClient();
	~NetworkClient();
	void ConnectToHost(QString address,quint16 port);
	void DisconnectFromHost();

	int BytesAvaible();
	qint64 Receive(char* buffer,qint64 maxlen);
	qint64 Send(char* buffer,qint64 len);

	
public slots:
	void OnConnect();
	void OnDisconnect();

private:
	QTcpSocket client;
};