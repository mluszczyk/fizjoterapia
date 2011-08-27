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

bool ListWidget::isEmpty() {
	return model->rowCount()==0;
}

void ListWidget::selectFirst() {
	view->selectRow(0);
}

}
