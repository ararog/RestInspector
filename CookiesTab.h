#ifndef COOKIESTAB_H
#define COOKIESTAB_H

#include <QPixmap>
#include <QWidget>

class QTableWidget;
class QNetworkCookie;

class CookiesTab : public QWidget
{
    Q_OBJECT

public:
    CookiesTab();
    void clear();
    void processCookies(const QList<QNetworkCookie>& cookies);

private:
    void createCookiesTable();
    QTableWidget *cookiesTable;
};

#endif // COOKIESTAB_H
