#ifndef FIZJOTERAPIA_ADDVISIT_H
#define FIZJOTEARPIA_ADDVISIT_H

#include <QPushButton>
#include <QFormLayout>
#include <QDateEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QTextEdit>
#include <QListView>
#include <QStringListModel>
#include <QCloseEvent>
#include <QStandardItem>

#include "Guide.h"
#include "PatientList.h"
#include "TherapyList.h"

namespace Fizjoterapia {

class NewVisit : public Guide {
	Q_OBJECT

private:
	PatientList *patientList;
	QPushButton *newPatient;
	QVBoxLayout *lay0;
	QWidget *wid0;

	TherapyList *therapyList;
	QPushButton *newTherapy;
	QVBoxLayout *lay1;
	QWidget *wid1;

	QFormLayout *info;
	QDateEdit *date;
	QLineEdit *city;
	QWidget *wid2;

	QGridLayout *lay3;
	QLabel *interview_label;
	QTextEdit *interview;
	QLabel *test_res_label;
	QTextEdit *test_res;
	QLabel *control_label;
	QStringListModel *control;
	QListView *control_view;
	QHBoxLayout *control_buttons;
	QPushButton *control_add;
	QPushButton *control_del;
	QPushButton *control_edit;
	QWidget *wid3;

	QVBoxLayout *lay4;
	QWidget *treat_buttons_wrap;
	QHBoxLayout *treat_buttons;
	QStandardItemModel *treat;
	TreatDelegate *treat_delegate;
	ResDelegate *res_delegate;
	QTableView *treat_view;
	QPushButton *treat_add;
	QPushButton *treat_del;
	QPushButton *treat_edit;
	QWidget *wid4;

	QVBoxLayout *lay5;
	QLabel *auto_label;
	QTextEdit *autotherapy;
	QWidget *wid5;

	QLabel *confirm_label;

	QLabel *label_last;

	int patient_id;
	int therapy_id;
	int visit_id;

	bool success;

public:
	NewVisit(QDialog *parent);

	virtual void goTo(int step);
	virtual void exec();

private:
	int toDb();

private slots:
	void patientChanged(int id);
	void therapyChanged(int id);

	void controlDelClicked();
	void controlAddClicked();
	void controlEditClicked();
	void controlInc(const QModelIndex &, int, int);
	void controlDcr(const QModelIndex &, int, int);
	void controlCh(const QModelIndex &, const QModelIndex &); 

	void treatDelClicked();
	void treatAddClicked();
	void treatEditClicked();

	virtual void reject();

	void newPatientClicked();
	void newTherapyClicked();

};

}

#endif 
