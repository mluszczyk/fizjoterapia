#include <QItemDelegate>
#include <QComboBox>

#include "Delegates.h"

namespace Fizjoterapia {

QString SexDelegate::displayText(const QVariant &value,
		const QLocale &) const {


	if(value.toBool() == 0) return QString::fromUtf8("Mężczyzna");
	else return QString::fromUtf8("Kobieta");
}

QString ResDelegate::displayText(const QVariant &value,
		const QLocale &) const {
	if(value.toInt() == 0) return "0";
	else if(value.toInt() == -1) return "-";
	else return "+";
}

/*
void ResDelegate::paint(QPainter *painter, 
		const QStyleOptionViewItem &option, 
		const QModelIndex &index) const {
	QStyleOptionViewItem newopt = option;
	newopt.decorationAlignment = Qt::AlignCenter;

	QStyledItemDelegate::paint(painter, newopt, index);
}
*/
QWidget* ResDelegate::createEditor(QWidget *parent,
		const QStyleOptionViewItem &option,
		const QModelIndex &index) const {
	ResComboBox *editor = new ResComboBox(index, parent);
	editor->addItem("-", -1);
	editor->addItem("0", 0);
	editor->addItem("+", 1);

	editor->setCurrentIndex(index.data().toInt()+1);

	connect(editor, SIGNAL(currentIndexChanged(int)),
			this, SLOT(valueChanged(int)));

	return editor;
}

void ResDelegate::valueChanged(int index) {
	ResComboBox *editor = qobject_cast<ResComboBox *>(sender());
	editor->commit(index-1);
	emit commitData(editor);
	emit closeEditor(editor);
}

}
