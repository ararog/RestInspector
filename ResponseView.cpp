#include <QtWidgets>
#include <QStringList>
#include <QNetworkReply>

#include "ResponseView.h"
#include "BodyTab.h"
#include "CookiesTab.h"
#include "HeadersTab.h"

ResponseView::ResponseView()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    bodyTab = new BodyTab();

    tabs = new QTabWidget;
    tabs->addTab(bodyTab, tr("Body"));
    tabs->addTab(new CookiesTab(), tr("Cookies"));
    tabs->addTab(new HeadersTab(), tr("Headers"));

    mainLayout->addWidget(tabs);
    setLayout(mainLayout);
}


void ResponseView::processResponse(QNetworkReply *reply)
{
  QVariant mimeType = reply->header(QNetworkRequest::ContentTypeHeader);
  QByteArray responseArray = reply->readAll();
  bodyTab->processBody(responseArray, mimeType.toString());
}
