#include <QtWidgets>

#include "PairsEditor.h"

PairsEditor::PairsEditor()
{
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
}

QHBoxLayout *RestInspector::createFields(const QString &keyPlaceholder)
{
    QHBoxLayout *pairLayout = new QHBoxLayout;

    QLineEdit *keyEdit = new QLineEdit;
    keyEdit->setPlaceholderText(tr(keyPlaceholder));
    pairLayout->addWidget(keyEdit);

    QLineEdit *valueEdit = new QLineEdit;
    valueEdit->setPlaceholderText(tr("Value"));
    pairLayout->addWidget(valueEdit);

    return pairLayout;
}
