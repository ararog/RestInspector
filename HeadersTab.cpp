#include <QtWidgets>
#include <QStringList>

#include "HeadersTab.h"

HeadersTab::HeadersTab()
{
    createHeaderTable();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(headersTable);
    setLayout(mainLayout);
}

void HeadersTab::clear()
{
    headersTable->setRowCount(2);
    headersTable->setColumnCount(2);
}

void HeadersTab::processHeaders(const QList<QNetworkReply::RawHeaderPair>& pairs)
{
    headersTable->setRowCount(pairs.count());
    for(int i = 0; i < pairs.count(); i++)
    {
        QNetworkReply::RawHeaderPair pair = pairs.value(i);

        QString content = QString::fromUtf8(pair.first.data());
        QTableWidgetItem *nameItem = new QTableWidgetItem(content);
        headersTable->setItem(i, 0, nameItem);

        content = QString::fromUtf8(pair.second.data());
        QTableWidgetItem *valueItem = new QTableWidgetItem(content);
        headersTable->setItem(i, 1, valueItem);
    }
}

void HeadersTab::createHeaderTable() {

    QStringList columns;
    columns << "name" << "value";

    headersTable = new QTableWidget();
    headersTable->verticalHeader()->setVisible(false);
    headersTable->setShowGrid(false);
    headersTable->setRowCount(2);
    headersTable->setColumnCount(2);
    headersTable->setHorizontalHeaderLabels(columns);    
}
