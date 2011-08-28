#ifndef FIZJOTERAPIA_DELEGATES_H
#define FIZJOTERAPIA_DELEGATES_H

#include <QDebug>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QModelIndex>
#include <QAbstractItemModel>

namespace Fizjoterapia {

class ResComboBox : public QComboBox {
	Q_OBJECT

private:
	QPersistentModelIndex index;

public:
	ResComboBox(const QModelIndex& _index, QWidget *parent=0) 
       		: QComboBox(parent), index(_index) {}
	void commit(int val) {
		QAbstractItemModel *model = const_cast<QAbstractItemModel*>(
				index.model());
		model->setData(index, QVariant(val), Qt::DisplayRole);
       	}

};

class SexDelegate : public QStyledItemDelegate {
	Q_OBJECT

public:
	virtual QString displayText(const QVariant &value,
			const QLocale &locale) const;
};

class TreatDelegate : public QStyledItemDelegate {
};

class ResDelegate : public QStyledItemDelegate {
	Q_OBJECT

public:
	virtual QString displayText(const QVariant &value,
			const QLocale &locale) const;
//	virtual void paint(QPainter *painter,
//		       	const QStyleOptionViewItem &option, 
//			const QModelIndex &index) const;
	virtual QWidget* createEditor(QWidget *parent,
			const QStyleOptionViewItem &option,
			const QModelIndex &index) const;
protected slots:
	void valueChanged(int index);
};

}

#endif
