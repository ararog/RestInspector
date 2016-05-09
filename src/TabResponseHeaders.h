#ifndef TABRESPONSEHEADERS_H
#define TABRESPONSEHEADERS_H

#include <QPixmap>
#include <QWidget>
#include <QNetworkReply>

class QTableWidget;

class TabResponseHeaders : public QWidget
{
    Q_OBJECT

public:
    TabResponseHeaders();
    void clear();
    void processHeaders(const QList<QNetworkReply::RawHeaderPair>& pairs);

private:
    void createHeaderTable();
    QTableWidget *headersTable;
};

#endif // TABRESPONSEHEADERS_H
