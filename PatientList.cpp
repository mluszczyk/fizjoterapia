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
	model = new QStandardItemModel(7, 0);
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
	model->setHeaderData(0, Qt::Horizontal, "ID");
	model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("Imię"));
	model->setHeaderData(2, Qt::Horizontal, "Nazwisko");
	model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("Płeć"));
	model->setHeaderData(4, Qt::Horizontal, "Data urodzenia");
	model->setHeaderData(5, Qt::Horizontal, "Pierwsza wizyta");
	model->setHeaderData(6, Qt::Horizontal, "Ostatnia wizyta");

	view->setColumnHidden(0, true);
	view->resizeColumnsToContents();
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
