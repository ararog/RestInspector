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
class HeadersTab;
class CookiesTab;

class ResponseView : public QWidget
{
    Q_OBJECT

public:
    ResponseView();
    void clear();
    void processResponse(QNetworkReply* reply);

private:

    QTabWidget *tabs;
    BodyTab *bodyTab;
    HeadersTab *headersTab;
    CookiesTab *cookiesTab;

};

#endif // RESPONSEVIEW_H
