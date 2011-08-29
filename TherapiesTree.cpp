#include <QDebug>

#include "TherapiesTree.h"
#include "DB.h"

namespace Fizjoterapia {

TherapiesTree::TherapiesTree(int _patient, 
		QWidget *parent) : QWidget(parent), patient(_patient) {
	layout = new QVBoxLayout(this);
	model = new QStandardItemModel;
	view = new QTreeView;

	layout->addWidget(view);

	view->setModel(model);
	view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	view->setColumnHidden(1, true);
	view->setHeaderHidden(true);
	view->setSelectionMode(QAbstractItemView::SingleSelection);
	view->setSelectionBehavior(QAbstractItemView::SelectRows);

	connect(view->selectionModel(),
		SIGNAL(selectionChanged(const QItemSelection &,
			const QItemSelection &)),
		this, SLOT(selectionChanged(const QItemSelection &,
			const QItemSelection &)));
}

void TherapiesTree::refill() {
	QHash<int, QStandardItem *> hash;
	QSqlQuery q;
	q = database.listTherapies(patient);
//	QStandardItem *parent = model->invisibleRootItem();
	QString format = "yyyy-MM-dd";

	model->clear();

	while(q.next()) {
		int id = q.value(0).toInt();
		QDate first = q.value(1).toDate();
		QDate second = q.value(2).toDate();
		int count = q.value(3).toInt();
		
		QStandardItem *tid = new QStandardItem(
				QString::number(-1));
		QString label;

		if(count==0)
			label = QString("Nigdy");
		else if (count==1)
			label = QString("%1 (1 wizyta)")
					.arg(first.toString(format));
		else
			label = QString("%1 - %2 (%3 %4)")
					.arg(first.toString(format))
					.arg(second.toString(format))
					.arg(count)
					.arg(conjugateVisit(count));

		QStandardItem *item = new QStandardItem(label);

		QList<QStandardItem *> list;
		list.append(item);
		list.append(tid);
		
		hash[id] = item;
		model->appendRow(list);
	}

	q = database.listVisitsOfPatient(patient);
	while(q.next()) {
		int visit_id = q.value(0).toInt();
		int therapy_id = q.value(1).toInt();
		QDate date = q.value(2).toDate();
		int number = q.value(3).toInt();
		
		QStandardItem *id = new QStandardItem(
				QString::number(visit_id));
		QString label = QString("Nr %1. %2")
			.arg(number)
			.arg(date.toString(format));
		QStandardItem *item = new QStandardItem(label);

		QList<QStandardItem *> list;
		list.append(item);
		list.append(id);

		hash[therapy_id]->appendRow(list);
	}

	view->expandAll();
	view->setColumnHidden(1, true);
}

void TherapiesTree::selectionChanged(const QItemSelection &current,
		const QItemSelection &) {
	QModelIndexList list = current.indexes();

	if(list.isEmpty()) {
		emit changed(-1);
		return;
	} else {
		emit changed(list[1].data().toInt());
	}
}

QString TherapiesTree::conjugateVisit(int count) {
	if(count==1) return "wizyta";
	if(count%10>=1 && count%10<=5 && (count/10)%10!=1) return "wizyty";
	else return "wizyt";
}

QSize TherapiesTree::sizeHint() const {
	return QSize(250, -1);
}

}


