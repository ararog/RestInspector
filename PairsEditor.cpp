#include <QtWidgets>
#include <QEvent>

#include <boost/foreach.hpp>

#include "PairsEditor.h"

PairsEditor::PairsEditor(const QString &keyPlaceholder)
{
    mainLayout = new QVBoxLayout;
	this->placeholder = keyPlaceholder;
	mainLayout->addLayout(createFields());
    setLayout(mainLayout);
}

bool PairsEditor::eventFilter(QObject *target, QEvent *event)
{
	if (event->type() == QEvent::FocusIn)
	{
		QHBoxLayout* layout = target->property("managingLayout").value<QHBoxLayout*>();
		QLayoutItem* lastLayout = mainLayout->itemAt(mainLayout->count() - 1);
		if(lastLayout == layout)
			mainLayout->addLayout(createFields());
	}

	return false;
}

void PairsEditor::clear()
{
    BOOST_FOREACH(QObject* object, mainLayout->children())
	{
        delete object;
    }

    mainLayout->addLayout(createFields());
}

QList<QPair<QString, QString> > PairsEditor::pairs()
{
	QList<QPair<QString, QString> > pairs;

	BOOST_FOREACH(QObject* object, mainLayout->children())
	{
		QHBoxLayout* layout = qobject_cast<QHBoxLayout *>(object);

		QLineEdit* keyEdit = qobject_cast<QLineEdit *>(layout->itemAt(0)->widget());
		QLineEdit* valEdit = qobject_cast<QLineEdit *>(layout->itemAt(1)->widget());

		QString key = keyEdit->text();
		QString val = valEdit->text();
		if (! key.isEmpty())
		{
			pairs << QPair<QString, QString>(key, val);
		}
	}

	return pairs;
}

void PairsEditor::deletePair()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button != NULL)
	{
		QHBoxLayout* layout = button->property("managingLayout").value<QHBoxLayout*>();
		delete layout;
		if(mainLayout->children().count() == 0)
			mainLayout->addLayout(createFields());
	}
}

QHBoxLayout *PairsEditor::createFields()
{
    QHBoxLayout *pairLayout = new QHBoxLayout;

    QLineEdit *keyEdit = new QLineEdit;
    keyEdit->setPlaceholderText(placeholder);
	keyEdit->installEventFilter(this);
	keyEdit->setProperty("managingLayout", QVariant::fromValue(pairLayout));
    pairLayout->addWidget(keyEdit);

    QLineEdit *valueEdit = new QLineEdit;
    valueEdit->setPlaceholderText(tr("Value"));
	valueEdit->installEventFilter(this);
	valueEdit->setProperty("managingLayout", QVariant::fromValue(pairLayout));
    pairLayout->addWidget(valueEdit);

	QPushButton *deleteButton = new QPushButton("Delete");
	deleteButton->connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePair()));
	deleteButton->setProperty("managingLayout", QVariant::fromValue(pairLayout));
	pairLayout->addWidget(deleteButton);

    return pairLayout;
}
