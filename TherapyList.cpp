#include <QSqlRecord>
#include <QHeaderView>
#include <QDebug>
#include <QModelIndex>
#include <QItemSelection>
#include "TherapyList.h"
#include "DB.h"

namespace Fizjoterapia {

TherapyList::TherapyList() : patient(0) {}

QSqlQuery TherapyList::buildQuery() {
	return database.listTherapies(patient);
}

void TherapyList::setPatient(int _patient) {
	patient = _patient;
}

void TherapyList::prepareHeaders() {
	model->setHeaderData(0, Qt::Horizontal, "ID");
	model->setHeaderData(1, Qt::Horizontal, "Pierwsza wizyta");
	model->setHeaderData(2, Qt::Horizontal, "Ostatnia wizyta");
	model->setHeaderData(3, Qt::Horizontal, 
			QString::fromUtf8("Ilość wizyt"));

	view->setColumnHidden(0, true);
	view->resizeColumnsToContents();
}

}
