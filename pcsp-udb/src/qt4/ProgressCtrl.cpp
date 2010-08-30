#include "ProgressCtrl.h"
#include <QtGui>

ProgressCtrl::ProgressCtrl(QWidget *parent)
: QDialog(parent)
{
  progressBar = new QProgressBar;
  nameLabel = new QLabel ("Name");

  stopButton = new QPushButton("&Cancel");

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addStretch(1);
  buttonLayout->addWidget(stopButton);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(nameLabel);
  vbox->addWidget(progressBar);
  vbox->addLayout(buttonLayout);
  setLayout(vbox);
  this->setMinimumWidth(333);
}

ProgressCtrl::~ProgressCtrl()
{
}
