#ifndef COOKIESTAB_H
#define COOKIESTAB_H

#include <QPixmap>
#include <QWidget>

class CookiesTab : public QWidget
{
    Q_OBJECT

public:
    CookiesTab();
    void clear();
    void processCookies();
};

#endif // COOKIESTAB_H
