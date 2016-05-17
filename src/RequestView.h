#ifndef REQUESTVIEW_H
#define REQUESTVIEW_H

#include <QPixmap>
#include <QWidget>

class QHBoxLayout;
class QLabel;
class PairsEditor;
class QPushButton;
class QTextEdit;
class QComboBox;
class QUrlQuery;

class RequestView : public QWidget
{
    Q_OBJECT

public:
    RequestView();
    void clear();
    QByteArray body();

private slots:
    void formBody();
    void rawBody();
    void formatChanged(const QString &text);

private:
    void formatAsJson(const QString &content);
    void formatAsXml(const QString &content);
    void createFormmatLayout();
    QUrlQuery encodePairs(QList<QPair<QString, QString> > pairs);
    QPushButton *createButton(const QString &text, QWidget *receiver, const char *member);

    QTextEdit *rawEditor;
    QString requestContent;

	PairsEditor *formEditor;

    QHBoxLayout *formatLayout;

    QPushButton *formButton;
    QPushButton *rawButton;
    QComboBox *formatsCombo;
};

#endif // REQUESTVIEW_H
