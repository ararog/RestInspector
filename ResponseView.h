#ifndef RESPONSEVIEW_H
#define RESPONSEVIEW_H

#include <QPixmap>
#include <QWidget>

class QGridLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QVBoxLayout;

class ResponseView : public QWidget
{
    Q_OBJECT

public:
    ResponseView();

private:

    QTabWidget *tabs;

};

#endif // RESPONSEVIEW_H
