#include <QtWidgets>
#include <QStringList>
#include <QDomDocument>

#include "PairsEditor.h"
#include "RequestView.h"

RequestView::RequestView()
{
    createFormmatLayout();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    formEditor = new PairsEditor("Key");
    requestEditor = new QTextEdit;
    mainLayout->addLayout(formatLayout);
    mainLayout->addWidget(formEditor);
    mainLayout->addWidget(requestEditor);
    setLayout(mainLayout);
}

void RequestView::formatAsJson(const QString &content)
{
    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    QString formattedString = doc.toJson(QJsonDocument::Indented);
    requestEditor->setPlainText(formattedString);
}

void RequestView::formatAsXml(const QString &content)
{
    QDomDocument doc("xml");
    doc.setContent(content);
    QString formattedString = doc.toString(4);
    requestEditor->setPlainText(formattedString);
}

void RequestView::formBody()
{
    requestEditor->setPlainText(requestContent);
    formButton->setChecked(false);
    rawButton->setChecked(true);
    requestEditor->show();
    formEditor->hide();
}

void RequestView::rawBody()
{
    formButton->setChecked(true);
    rawButton->setChecked(false);
    requestEditor->hide();
    formEditor->show();
}

void RequestView::formatChanged(const QString &text)
{
    if(text == "JSON")
    {
        formatAsJson(requestContent);
    }
    else if(text == "XML")
    {
        formatAsXml(requestContent);
    }
    else {
        requestEditor->setPlainText(requestContent);
    }
}

void RequestView::createFormmatLayout()
{
    formButton = createButton(tr("x-www-form-urlencoded"), this, SLOT(formBody()));
    rawButton = createButton(tr("raw"), this, SLOT(rawBody()));

    QStringList formats;
    formats << "JSON" << "XML" << "HTML" << "TEXT";
    formatsCombo = new QComboBox;
    formatsCombo->addItems(formats);
    formatsCombo->connect(formatsCombo, SIGNAL(currentTextChanged(const QString &)), this, SLOT(formatChanged(const QString &)));

    formatLayout = new QHBoxLayout;
    formatLayout->addWidget(formButton);
    formatLayout->addWidget(rawButton);
    formatLayout->addWidget(formatsCombo);
    formatLayout->addStretch();
}

QPushButton *RequestView::createButton(const QString &text, QWidget *receiver,
                                      const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->connect(button, SIGNAL(clicked()), receiver, member);
    return button;
}
