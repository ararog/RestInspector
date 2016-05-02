#ifndef BODYTAB_H
#define BODYTAB_H

#include <QPixmap>
#include <QWidget>

class QTextEdit;

class BodyTab : public QWidget
{
    Q_OBJECT

public:
    BodyTab();
    void clear();
    void processBody(QByteArray body, QString mimeType);

private:

    QTextEdit *responseEditor;
};

#endif // BODYTAB_H
