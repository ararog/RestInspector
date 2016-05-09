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
class TabResponseBody;
class TabResponseHeaders;
class TabResponseCookies;

class ResponseView : public QWidget
{
    Q_OBJECT

public:
    ResponseView();
    void clear();
    void processResponse(QNetworkReply* reply);

private:

    QTabWidget *tabs;
    TabResponseBody *tabBody;
    TabResponseHeaders *tabHeaders;
    TabResponseCookies *tabCookies;
    int statusCode;

};

#endif // RESPONSEVIEW_H
