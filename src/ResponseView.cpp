#include <QtWidgets>
#include <QStringList>
#include <QNetworkReply>
#include <QNetworkCookie>

#include "ResponseView.h"
#include "TabResponseBody.h"
#include "TabResponseCookies.h"
#include "TabResponseHeaders.h"

ResponseView::ResponseView()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    tabBody = new TabResponseBody();
    tabCookies = new TabResponseCookies();
    tabHeaders = new TabResponseHeaders();

    tabs = new QTabWidget;
    tabs->addTab(tabBody, tr("Body"));
    tabs->addTab(tabCookies, tr("Cookies"));
    tabs->addTab(tabHeaders, tr("Headers"));

    mainLayout->addWidget(tabs);
    setLayout(mainLayout);
}

void ResponseView::clear()
{
    tabBody->clear();
    tabCookies->clear();
    tabHeaders->clear();
}

void ResponseView::processResponse(QNetworkReply *reply)
{
    QVariant mimeTypeHeader = reply->header(QNetworkRequest::ContentTypeHeader);
    QVariant cookiesHeader = reply->header(QNetworkRequest::CookieHeader);
    QVariant attribute = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    statusCode = attribute.toInt();
    QByteArray responseArray = reply->readAll();
    QList<QNetworkCookie> cookies = cookiesHeader.value<QList<QNetworkCookie> >();

    tabBody->processBody(responseArray, mimeTypeHeader.toString());
    tabCookies->processCookies(cookies);
    tabHeaders->processHeaders(reply->rawHeaderPairs());
}
