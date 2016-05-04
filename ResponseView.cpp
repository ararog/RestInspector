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
    cookiesTab = new CookiesTab();
    headersTab = new HeadersTab();

    tabs = new QTabWidget;
    tabs->addTab(bodyTab, tr("Body"));
    tabs->addTab(cookiesTab, tr("Cookies"));
    tabs->addTab(headersTab, tr("Headers"));

    mainLayout->addWidget(tabs);
    setLayout(mainLayout);
}

void ResponseView::clear()
{
    bodyTab->clear();
    cookiesTab->clear();
    headersTab->clear();
}

void ResponseView::processResponse(QNetworkReply *reply)
{
    QVariant mimeTypeHeader = reply->header(QNetworkRequest::ContentTypeHeader);
    QVariant cookiesHeader = reply->header(QNetworkRequest::CookieHeader);
    QVariant attribute = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    statusCode = attribute.toInt();
    QByteArray responseArray = reply->readAll();
    QList<QNetworkCookie> cookies = cookiesHeader.value<QList<QNetworkCookie> >()

    bodyTab->processBody(responseArray, mimeTypeHeader.toString());
    cookiesTab->processCookies(cookies);
    headersTab->processHeaders(reply->rawHeaderPairs());
}
