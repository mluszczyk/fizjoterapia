#include <QSqlRecord>
#include <QHeaderView>
#include <QDebug>
#include <QModelIndex>
#include <QItemSelection>
#include "ListWidget.h"
#include "DB.h"

namespace Fizjoterapia {

ListWidget::ListWidget() {
	layout = new QVBoxLayout(this);
	model = new QStandardItemModel(7, 0);
	view = new QTableView;

	view->setModel(model);
	view->setSortingEnabled(true);
	view->verticalHeader()->hide();
	view->horizontalHeader()->show();
	view->setSelectionBehavior(QAbstractItemView::SelectRows);
	view->setSelectionMode(QAbstractItemView::SingleSelection);
	view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(view->selectionModel(), 
		SIGNAL(selectionChanged(const QItemSelection &,
			const QItemSelection &)), 
		this,
		SLOT(selectionChanged(const QItemSelection &,
			const QItemSelection &)));

	// Layout
	layout->addWidget(view, 1);

	connect((QObject*)&database, SIGNAL(modified()),
		this, SLOT(refill()));
}

void ListWidget::refill() {
	QSqlQuery q = buildQuery();
	model->clear();

	while(q.next()) {
		QList<QStandardItem *> row;
		for(int i=0; i<q.record().count(); ++i)
			row.append(new QStandardItem(q.value(i).toString()));
		model->appendRow(row);
	}

	prepareHeaders();
}

void ListWidget::selectionChanged(const QItemSelection &current,
		const QItemSelection &) {
	QModelIndexList list = current.indexes();
	if(list.size()<1) {
		emit changed(-1);
		return;
	}
	int row = list[0].row();
	int id = model->data(model->index(row, 0)).toInt();

	emit changed(id);
}

bool ListWidget::isEmpty() {
	return model->rowCount()==0;
}

void ListWidget::selectFirst() {
	view->selectRow(1);
}

void ListWidget::selectId(int id) {
	int row = -1;
	for(int i=0; i<model->rowCount(); ++i) {
		if(model->data(model->index(i, 0)).toInt() == id) {
			row = i;
			break;
		}
	}
	view->selectRow(row);
}

}
