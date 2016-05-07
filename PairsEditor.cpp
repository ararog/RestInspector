#include <QtWidgets>

#include "PairsEditor.h"

PairsEditor::PairsEditor()
{
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
}

QHBoxLayout *PairsEditor::createFields(const QString &keyPlaceholder)
{
    QHBoxLayout *pairLayout = new QHBoxLayout;

    QLineEdit *keyEdit = new QLineEdit;
    keyEdit->setPlaceholderText(keyPlaceholder);
    pairLayout->addWidget(keyEdit);

    QLineEdit *valueEdit = new QLineEdit;
    valueEdit->setPlaceholderText(tr("Value"));
    pairLayout->addWidget(valueEdit);

    return pairLayout;
}
