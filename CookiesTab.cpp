#include <QtWidgets>
#include <QStringList>
#include <QNetworkCookie>

#include <boost/foreach.hpp>

#include "CookiesTab.h"

CookiesTab::CookiesTab()
{
    createCookiesTable();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(cookiesTable);
    setLayout(mainLayout);
}

void CookiesTab::clear()
{
    cookiesTable->setRowCount(2);
    cookiesTable->setColumnCount(2);
}

void CookiesTab::processCookies(const QList<QNetworkCookie>& cookies)
{
    cookiesTable->setRowCount(cookies.count());

    int row = 0;
    BOOST_FOREACH(QNetworkCookie cookie, cookies)
    {
        QString content = QString::fromUtf8(cookie.name().data());
        QTableWidgetItem *nameItem = new QTableWidgetItem(content);
        cookiesTable->setItem(row, 0, nameItem);

        content = QString::fromUtf8(cookie.value().data());
        QTableWidgetItem *valueItem = new QTableWidgetItem(content);
        cookiesTable->setItem(row, 1, valueItem);

        row++;
    }

    cookiesTable->resizeColumnsToContents();
}

void CookiesTab::createCookiesTable()
{
    QStringList columns;
    columns << "name" << "value";

    cookiesTable = new QTableWidget();
    cookiesTable->verticalHeader()->setVisible(false);
    cookiesTable->setShowGrid(false);
    cookiesTable->setRowCount(2);
    cookiesTable->setColumnCount(2);
    cookiesTable->setHorizontalHeaderLabels(columns);
}
