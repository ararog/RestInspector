#ifndef HEADERSTAB_H
#define HEADERSTAB_H

#include <QPixmap>
#include <QWidget>
#include <QNetworkReply>

class HeadersTab : public QWidget
{
    Q_OBJECT

public:
    HeadersTab();
    void clear();
    void processHeaders(const QList<QNetworkReply::RawHeaderPair>& pairs);
};

#endif // HEADERSTAB_H
