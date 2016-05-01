#include <QtWidgets>
#include <QStringList>

#include "ResponseView.h"
#include "BodyTab.h"
#include "CookiesTab.h"
#include "HeadersTab.h"

ResponseView::ResponseView()
{
    tabs = new QTabWidget;
    tabs->addTab(new BodyTab(), tr("Body"));
    tabs->addTab(new CookiesTab(), tr("Cookies"));
    tabs->addTab(new HeadersTab(), tr("Headers"));
}
