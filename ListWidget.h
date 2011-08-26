#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QModelIndex>

namespace Fizjoterapia {

class PatientList : public QWidget {
	Q_OBJECT

protected:
	int patient;
	bool wide;

	QStandardItemModel *model;
	QTableView *view;
	QVBoxLayout *layout;

public:
	PatientList();

	void refill();

private slots:
	void selectedPatient(const QItemSelection &current, 
			const QItemSelection &previous);

signals:
	void changed(int current);

	
};

}

#endif
