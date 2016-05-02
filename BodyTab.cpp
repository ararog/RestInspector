#include <QtWidgets>
#include <QStringList>

#include "BodyTab.h"

BodyTab::BodyTab()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    responseEditor = new QTextEdit;
    mainLayout->addWidget(responseEditor);
    setLayout(mainLayout);
}

void BodyTab::clear()
{
    responseEditor->setPlainText("");
}

void BodyTab::processBody(QByteArray body, QString mimeType)
{
    QString content = QString::fromUtf8(body.data());
    responseEditor->setPlainText(content);
}
