#ifndef RESPONSEVIEW_H
#define RESPONSEVIEW_H

#include <QPixmap>
#include <QWidget>

class QGridLayout;
class QHBoxLayout;
class QLabel;
class QTabWidget;
class QPushButton;
class QVBoxLayout;
class QNetworkReply;
class BodyTab;

class ResponseView : public QWidget
{
    Q_OBJECT

public:
    ResponseView();
    void processResponse(QNetworkReply* reply);

private:

    QTabWidget *tabs;
    BodyTab *bodyTab;

};

#endif // RESPONSEVIEW_H
