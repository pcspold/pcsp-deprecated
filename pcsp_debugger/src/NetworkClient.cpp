#include "NetworkClient.h"

NetworkClient::NetworkClient():client()
{
	connect(&client, SIGNAL(connected()),this, SLOT(OnConnect()));
	connect(&client, SIGNAL(disconnected()),this, SLOT(OnDisconnect()));
}

NetworkClient::~NetworkClient()
{

}

void NetworkClient::ConnectToHost(QString address,quint16 port)
{
	QHostAddress addr(address);
	client.connectToHost(addr, port);
}

void NetworkClient::DisconnectFromHost()
{
	client.disconnectFromHost();
}

int NetworkClient::BytesAvaible()
{
	return client.bytesAvailable();
}

qint64 NetworkClient::Receive(char* buffer, qint64 maxlen)
{
	return client.read(buffer,maxlen);
}

qint64 NetworkClient::Send(char* buffer, qint64 len)
{
	return client.write(buffer,len);
}