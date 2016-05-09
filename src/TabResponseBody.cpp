#include <QtWidgets>
#include <QStringList>
#include <QDomDocument>

#include "TabResponseBody.h"

TabResponseBody::TabResponseBody()
{
    createFormmatLayout();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    responseEditor = new QTextEdit;
    mainLayout->addLayout(formatLayout);
    mainLayout->addWidget(responseEditor);
    setLayout(mainLayout);
}

void TabResponseBody::clear()
{
    responseEditor->setPlainText("");
}

void TabResponseBody::processBody(QByteArray body, QString mimeType)
{
    responseMimeType = mimeType;
    responseContent = QString::fromUtf8(body.data());
    this->prettyFormat();
}

void TabResponseBody::formatAsJson(const QString &content)
{
    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    QString formattedString = doc.toJson(QJsonDocument::Indented);
    responseEditor->setPlainText(formattedString);
}

void TabResponseBody::formatAsXml(const QString &content)
{
    QDomDocument doc("xml");
    doc.setContent(content);
    QString formattedString = doc.toString(4);
    responseEditor->setPlainText(formattedString);
}

void TabResponseBody::prettyFormat()
{
    if(responseMimeType.contains("application/json"))
    {
        formatAsJson(responseContent);
    }
    else if(responseMimeType.contains("text/xml"))
    {
        formatAsXml(responseContent);
    }
    else
    {
        responseEditor->setPlainText(responseContent);
    }

    prettyButton->setChecked(true);
    rawButton->setChecked(false);
}

void TabResponseBody::rawFormat()
{
    responseEditor->setPlainText(responseContent);
    prettyButton->setChecked(false);
    rawButton->setChecked(true);
}

void TabResponseBody::formatChanged(const QString &text)
{
    if(text == "JSON")
    {
        formatAsJson(responseContent);
    }
    else if(text == "XML")
    {
        formatAsXml(responseContent);
    }
    else {
        responseEditor->setPlainText(responseContent);
    }
}

void TabResponseBody::createFormmatLayout()
{
    prettyButton = createButton(tr("Pretty"), this, SLOT(prettyFormat()));
    rawButton = createButton(tr("Raw"), this, SLOT(rawFormat()));

    QStringList formats;
    formats << "JSON" << "XML" << "HTML" << "TEXT";
    formatsCombo = new QComboBox;
    formatsCombo->addItems(formats);
    formatsCombo->connect(formatsCombo, SIGNAL(currentTextChanged(const QString &)), this, SLOT(formatChanged(const QString &)));

    formatLayout = new QHBoxLayout;
    formatLayout->addWidget(prettyButton);
    formatLayout->addWidget(rawButton);
    formatLayout->addWidget(formatsCombo);
    formatLayout->addStretch();
}

QPushButton *TabResponseBody::createButton(const QString &text, QWidget *receiver,
                                      const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->connect(button, SIGNAL(clicked()), receiver, member);
    button->setMinimumWidth(100);
    button->setCheckable(true);
    button->setChecked(false);
    return button;
}
