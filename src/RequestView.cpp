#include <QtWidgets>
#include <QStringList>
#include <QDomDocument>
#include <QUrlQuery>

#include <boost/foreach.hpp>

#include "PairsEditor.h"
#include "RequestView.h"

RequestView::RequestView()
{
    createFormmatLayout();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    formEditor = new PairsEditor("Key");
    rawEditor = new QTextEdit;
    mainLayout->addLayout(formatLayout);
    mainLayout->addWidget(formEditor);
    mainLayout->addWidget(rawEditor);

    formButton->setChecked(true);
    rawButton->setChecked(false);
    formEditor->show();
    rawEditor->hide();

    setLayout(mainLayout);
}

void RequestView::clear()
{
    formEditor->clear();
    rawEditor->setPlainText("");
}

QByteArray RequestView::body()
{
    if(formButton->isChecked())
    {
        QUrlQuery postParams = encodePairs(formEditor->pairs());
        return postParams.toString(QUrl::FullyEncoded).toUtf8();
    }
    else
    {
        QString body = rawEditor->toPlainText();
        return QByteArray().append(body);
    }
}


void RequestView::formatAsJson(const QString &content)
{
    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    QString formattedString = doc.toJson(QJsonDocument::Indented);
    rawEditor->setPlainText(formattedString);
}

void RequestView::formatAsXml(const QString &content)
{
    QDomDocument doc("xml");
    doc.setContent(content);
    QString formattedString = doc.toString(4);
    rawEditor->setPlainText(formattedString);
}

void RequestView::formBody()
{
    formButton->setChecked(true);
    rawButton->setChecked(false);
    rawEditor->hide();
    formEditor->show();
}

void RequestView::rawBody()
{
    rawEditor->setPlainText(requestContent);
    formButton->setChecked(false);
    rawButton->setChecked(true);
    rawEditor->show();
    formEditor->hide();
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
        rawEditor->setPlainText(requestContent);
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

QUrlQuery RequestView::encodePairs(QList<QPair<QString, QString> > pairs)
{
    QPair<QString, QString> pair;
    QUrlQuery query;

    BOOST_FOREACH(pair, pairs)
    {
        query.addQueryItem(pair.first, pair.second);
    }

    return query;
}

QPushButton *RequestView::createButton(const QString &text, QWidget *receiver,
                                      const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->connect(button, SIGNAL(clicked()), receiver, member);
    button->setCheckable(true);
    return button;
}
