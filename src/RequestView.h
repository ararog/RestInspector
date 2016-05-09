#ifndef REQUESTVIEW_H
#define REQUESTVIEW_H

#include <QPixmap>
#include <QWidget>

class QHBoxLayout;
class QLabel;

class RequestView : public QWidget
{
    Q_OBJECT

public:
    RequestView();
    void clear();

private:

    int statusCode;

};

#endif // REQUESTVIEW_H
