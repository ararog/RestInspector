#include <QtWidgets>
#include <QStringList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include <boost/foreach.hpp>

#include "RestInspector.h"
#include "PairsEditor.h"
#include "ResponseView.h"

RestInspector::RestInspector()
{
    createHistoryLayout();
    createFieldsLayout();
    createCommandsLayout();

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(historyLayout);

    blankView = new QWidget;
    blankView->show();

    responseView = new ResponseView;
    responseView->hide();

    QVBoxLayout *editorsLayout = new QVBoxLayout;
    paramsEditor = new PairsEditor("URL Parameter Key");
    paramsEditor->hide();
	editorsLayout->addWidget(paramsEditor);

    headersEditor = new PairsEditor("Header");
    headersEditor->hide();
	editorsLayout->addWidget(headersEditor);

    QHBoxLayout *extrasLayout = new QHBoxLayout;
    extrasLayout->addLayout(editorsLayout);
    extrasLayout->addStretch();

    clientLayout = new QVBoxLayout;
    clientLayout->addLayout(fieldsLayout);
    clientLayout->addLayout(extrasLayout);
    clientLayout->addLayout(commandsLayout);
    clientLayout->addWidget(responseView);
    clientLayout->addWidget(blankView);

    mainLayout->addLayout(clientLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("RestInspector"));

    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    resize(width / 2, height / 2);
}

void RestInspector::resizeEvent(QResizeEvent * /* event */)
{

}

void RestInspector::replyFinished(QNetworkReply* reply)
{
    responseView->processResponse(reply);
    blankView->hide();
    responseView->show();
}

void RestInspector::sendRequest()
{
	QPair<QString, QString> pair;

	if (! urlEdit->text().isEmpty())
	{
		QUrl url = QUrl(urlEdit->text());
		QUrlQuery urlQuery;

        QList<QPair<QString, QString> > params = paramsEditor->pairs();
		BOOST_FOREACH(pair, params)
		{
			urlQuery.addQueryItem(pair.first, pair.second);
		}
		url.setQuery(urlQuery);

		QNetworkRequest request = QNetworkRequest(url);
		QString method = httpMethodsCombo->currentText();
		QByteArray verb;
		verb.append(method);

		QList<QPair<QString, QString> > headers = headersEditor->pairs();
		BOOST_FOREACH(pair, headers)
		{
			request.setRawHeader(QByteArray().append(pair.first), QByteArray().append(pair.second));
		}

		manager->sendCustomRequest(request, verb);
    }
}

void RestInspector::resetRequest()
{
    urlEdit->setText("");
    httpMethodsCombo->setCurrentIndex(0);
    paramsEditor->clear();
    headersEditor->clear();
    responseView->clear();
    responseView->hide();
    clientLayout->addStretch();
}

void RestInspector::saveRequest()
{

}

void RestInspector::toggleUrlParams()
{
    if(paramsEditor->isVisible())
        paramsEditor->hide();
    else
        paramsEditor->show();
}

void RestInspector::toggleHeaders()
{
    if(headersEditor->isVisible())
        headersEditor->hide();
    else
        headersEditor->show();
}

void RestInspector::createHistoryLayout()
{
    historyLayout = new QVBoxLayout;
}

void RestInspector::createFieldsLayout()
{
    urlEdit = new QLineEdit;
    urlEdit->setPlaceholderText(tr("Enter requested URL here"));

    QStringList methods;
    methods << "GET" << "POST" << "PUT" << "PATH" << "DELETE" << "COPY" << "HEAD" << "OPTIONS";
    httpMethodsCombo = new QComboBox;
    httpMethodsCombo->addItems(methods);

    showUrlParamsButton = createButton(tr("URL Params"), this, SLOT(toggleUrlParams()));
    showHeadersButton = createButton(tr("Headers"), this, SLOT(toggleHeaders()));

    fieldsLayout = new QHBoxLayout;
    fieldsLayout->addWidget(httpMethodsCombo);
    fieldsLayout->addWidget(urlEdit);
    fieldsLayout->addWidget(showUrlParamsButton);
    fieldsLayout->addWidget(showHeadersButton);
}

void RestInspector::createCommandsLayout()
{
    sendRequestButton = createButton(tr("Send"), this, SLOT(sendRequest()));
    saveRequestButton = createButton(tr("Save"), this, SLOT(saveRequest()));
    resetRequestButton = createButton(tr("Reset"), this, SLOT(resetRequest()));

    commandsLayout = new QHBoxLayout;
    commandsLayout->addWidget(sendRequestButton);
    commandsLayout->addWidget(saveRequestButton);
    commandsLayout->addStretch();
    commandsLayout->addWidget(resetRequestButton);
}

QPushButton *RestInspector::createButton(const QString &text, QWidget *receiver,
                                      const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->connect(button, SIGNAL(clicked()), receiver, member);
    return button;
}
