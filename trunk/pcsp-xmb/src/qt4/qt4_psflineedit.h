#ifndef QT4_PSFLINEEDIT_H
#define QT4_PSFLINEEDIT_H

#include <QLineEdit>
#include<QListWidgetItem>

class psfLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	psfLineEdit(QWidget *parent);
	~psfLineEdit();

public slots:
	void setpsfInfo(QListWidgetItem*);
	void checkbootbin(QListWidgetItem*);
};

#endif // QT4_PSFLINEEDIT_H
