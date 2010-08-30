#if !defined(PROGRESSCTRL_INCLUDED_)
#define PROGRESSCTRL_INCLUDED_

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

class ProgressCtrl : public QDialog  
{
  Q_OBJECT
public:
  ProgressCtrl(QWidget *parent=0);
  virtual ~ProgressCtrl();

  QLabel *label() const {return nameLabel;}
  QProgressBar *progress() const {return progressBar;}
  QPushButton *stop() const {return stopButton;}
private:
  QPushButton *stopButton;
  QLabel *nameLabel;
  QProgressBar *progressBar;
};

#endif // !defined(PROGRESSCTRL_INCLUDED_)
