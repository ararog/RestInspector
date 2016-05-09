#ifndef TABRESPONSECOOKIES_H
#define TABRESPONSECOOKIES_H

#include <QPixmap>
#include <QWidget>

class QTableWidget;
class QNetworkCookie;

class TabResponseCookies : public QWidget
{
    Q_OBJECT

public:
    TabResponseCookies();
    void clear();
    void processCookies(const QList<QNetworkCookie>& cookies);

private:
    void createCookiesTable();
    QTableWidget *cookiesTable;
};

#endif // TABRESPONSECOOKIES_H
