#ifndef BODYTAB_H
#define BODYTAB_H

#include <QPixmap>
#include <QWidget>

class QTextEdit;
class QHBoxLayout;
class QPushButton;
class QComboBox;

class BodyTab : public QWidget
{
    Q_OBJECT

public:
    BodyTab();
    void clear();
    void processBody(QByteArray body, QString mimeType);

private slots:
    void prettyFormat();
    void rawFormat();
    void formatChanged(const QString &text);

private:
    void createFormmatLayout();
    void formatAsJson(const QString &content);
    void formatAsXml(const QString &content);
    QPushButton *createButton(const QString &text, QWidget *receiver, const char *member);

    QTextEdit *responseEditor;
    QString responseContent;
    QString responseMimeType;

    QHBoxLayout *formatLayout;

    QPushButton *prettyButton;
    QPushButton *rawButton;
    QComboBox *formatsCombo;
};

#endif // BODYTAB_H
