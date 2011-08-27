#include <QSqlRecord>
#include <QHeaderView>
#include <QDebug>
#include <QModelIndex>
#include <QItemSelection>
#include "PatientList.h"
#include "DB.h"

namespace Fizjoterapia {

PatientList::PatientList() {}

QSqlQuery PatientList::buildQuery() {
	return database.listPatients();
}

void PatientList::prepareHeaders() {
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

}
