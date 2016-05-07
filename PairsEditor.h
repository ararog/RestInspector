#ifndef PAIRSEDITOR_H
#define PAIRSEDITOR_H

#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;

class PairsEditor : public QWidget
{
    Q_OBJECT

public:
	PairsEditor();

private:
	QHBoxLayout *createFields(const QString &keyPlaceholder);

    QVBoxLayout *mainLayout;
};

#endif // PAIRSEDITOR_H
