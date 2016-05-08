#ifndef PAIRSEDITOR_H
#define PAIRSEDITOR_H

#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;
template class QPair<QString, QString>;

class PairsEditor : public QWidget
{
    Q_OBJECT

public:
	PairsEditor(const QString &keyPlaceholder);
	QList<QPair<QString, QString> > pairs();

private slots:
	void deletePair();

private:
	bool eventFilter(QObject *target, QEvent *event);
	QHBoxLayout *createFields();

	QString placeholder;
    QVBoxLayout *mainLayout;
};

#endif // PAIRSEDITOR_H
