#ifndef RESTINSPECTOR_H
#define RESTINSPECTOR_H

#include <QPixmap>
#include <QWidget>

class QGridLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QVBoxLayout;
class ResponseView;
class QNetworkReply;
class QNetworkRequest;
class QNetworkAccessManager;

class RestInspector : public QWidget
{
    Q_OBJECT

public:
    RestInspector();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void sendRequest();
    void resetRequest();
    void toggleUrlParams();
    void toggleHeaders();
    void replyFinished(QNetworkReply* reply);

private:
    void createHistoryLayout();
    void createFieldsLayout();
    void createCommandsLayout();
    QPushButton *createButton(const QString &text, QWidget *receiver, const char *member);

    QNetworkAccessManager *manager; 

    QLineEdit *urlEdit;
    QComboBox *httpMethodsCombo;

    QPushButton *sendRequestButton;
    QPushButton *resetRequestButton;
    QPushButton *showUrlParamsButton;
    QPushButton *showHeadersButton;

    ResponseView *responseView;

    QHBoxLayout *mainLayout;
    QVBoxLayout *historyLayout;
    QVBoxLayout *clientLayout;
    QHBoxLayout *fieldsLayout;
    QHBoxLayout *commandsLayout;
};

#endif // RESTINSPECTOR_H
