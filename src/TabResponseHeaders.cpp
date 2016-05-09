#include <QtWidgets>
#include <QStringList>

#include <boost/foreach.hpp>

#include "TabResponseHeaders.h"

TabResponseHeaders::TabResponseHeaders()
{
    createHeaderTable();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(headersTable);
    setLayout(mainLayout);
}

void TabResponseHeaders::clear()
{
    headersTable->setRowCount(2);
    headersTable->setColumnCount(2);
}

void TabResponseHeaders::processHeaders(const QList<QNetworkReply::RawHeaderPair>& pairs)
{
    headersTable->setRowCount(pairs.count());
    int row = 0;
    BOOST_FOREACH(QNetworkReply::RawHeaderPair pair, pairs)
    {
        QString content = QString::fromUtf8(pair.first.data());
        QTableWidgetItem *nameItem = new QTableWidgetItem(content);
        headersTable->setItem(row, 0, nameItem);

        content = QString::fromUtf8(pair.second.data());
        QTableWidgetItem *valueItem = new QTableWidgetItem(content);
        headersTable->setItem(row, 1, valueItem);

        row++;
    }

    headersTable->resizeColumnsToContents();
}

void TabResponseHeaders::createHeaderTable()
{
    QStringList columns;
    columns << "name" << "value";

    headersTable = new QTableWidget();
    headersTable->verticalHeader()->setVisible(false);
    headersTable->setShowGrid(false);
    headersTable->setRowCount(2);
    headersTable->setColumnCount(2);
    headersTable->setHorizontalHeaderLabels(columns);
}
