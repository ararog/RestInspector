#include <QtWidgets>
#include <QStringList>

#include "RestInspector.h"
#include "ResponseView.h"

RestInspector::RestInspector()
{
    createHistoryLayout();
    createFieldsLayout();
    createCommandsLayout();

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
    resize(300, 200);
}

void RestInspector::resizeEvent(QResizeEvent * /* event */)
{
    /*
    QSize scaledSize = originalPixmap.size();
    scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
    if (!screenshotLabel->pixmap() || scaledSize != screenshotLabel->pixmap()->size())
        updateScreenshotLabel();
    */
}

void RestInspector::sendRequest()
{
    clientLayout->takeAt(3);
    responseView->show();
}

void RestInspector::resetRequest()
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
    showHeadersButton = createButton(tr("Reset"), this, SLOT(toggleHeaders()));

    fieldsLayout = new QHBoxLayout;
    fieldsLayout->addWidget(urlEdit);
    fieldsLayout->addWidget(httpMethodsCombo);
    fieldsLayout->addWidget(showUrlParamsButton);
    fieldsLayout->addWidget(showHeadersButton);
}

void RestInspector::createCommandsLayout()
{
    sendRequestButton = createButton(tr("Send"), this, SLOT(sendRequest()));
    resetRequestButton = createButton(tr("Reset"), this, SLOT(resetRequest()));

    commandsLayout = new QHBoxLayout;
    commandsLayout->addWidget(sendRequestButton);
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
