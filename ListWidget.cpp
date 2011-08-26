#include <QSqlRecord>
#include <QHeaderView>
#include <QDebug>
#include <QModelIndex>
#include <QItemSelection>
#include "PatientList.h"
#include "DB.h"

namespace Fizjoterapia {

PatientList::PatientList() {
	layout = new QVBoxLayout(this);
	model = new QStandardItemModel;
	view = new QTableView;

	view->setModel(model);
	view->setSortingEnabled(true);
	view->verticalHeader()->hide();
	view->setSelectionBehavior(QAbstractItemView::SelectRows);
	view->setSelectionMode(QAbstractItemView::SingleSelection);
	view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(view->selectionModel(), 
		SIGNAL(selectionChanged(const QItemSelection &,
			const QItemSelection &)), 
		this,
		SLOT(selectedPatient(const QItemSelection &,
			const QItemSelection &)));

	// Layout
	layout->addWidget(view, 1);
}

void PatientList::refill() {
	QSqlQuery q = database.listPatients();
	model->clear();

	while(q.next()) {
		QList<QStandardItem *> row;
		for(int i=0; i<q.record().count(); ++i)
			row.append(new QStandardItem(q.value(i).toString()));
		model->appendRow(row);
	}
}

void PatientList::selectedPatient(const QItemSelection &current,
		const QItemSelection &previous) {
	QModelIndexList list = current.indexes();
	if(list.size()<1) {
		emit changed(-1);
		return;
	}
	int row = list[0].row();
	int id = model->data(model->index(row, 0)).toInt();

	emit changed(id);
}

}
