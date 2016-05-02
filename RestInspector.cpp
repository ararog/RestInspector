#include <QtWidgets>
#include <QStringList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include "RestInspector.h"
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

    responseView = new ResponseView;
    responseView->hide();

    clientLayout = new QVBoxLayout;
    clientLayout->addLayout(fieldsLayout);
    clientLayout->addLayout(commandsLayout);
    clientLayout->addWidget(responseView);
    clientLayout->addStretch();

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
    clientLayout->takeAt(3);
    responseView->processResponse(reply);
    responseView->show();
}

void RestInspector::sendRequest()
{
    QNetworkRequest request = QNetworkRequest(QUrl(urlEdit->text()));
    QString method = httpMethodsCombo->currentText();
    QByteArray verb;
    verb.append(method);
    manager->sendCustomRequest(request, verb);
}

void RestInspector::resetRequest()
{
    urlEdit->setText("");
    httpMethodsCombo->setCurrentIndex(0);
    responseView->clear();
    responseView->hide();
    clientLayout->addStretch();
}

void RestInspector::saveRequest()
{

}

void RestInspector::toggleUrlParams()
{

}

void RestInspector::toggleHeaders()
{

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
