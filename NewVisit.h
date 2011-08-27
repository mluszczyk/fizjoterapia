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
	QWidget *wid3;

	QVBoxLayout *lay4;
	QWidget *treat_buttons_wrap;
	QHBoxLayout *treat_buttons;
	QStandardItemModel *treat;
	QTableView *treat_view;
	QPushButton *treat_add;
	QPushButton *treat_del;
	QWidget *wid4;

	QLabel *label_last;

	int patient_id;

public:
	NewVisit(QDialog *parent);

	virtual void goTo(int step);

private slots:
	void patientChanged(int id);
	void therapyChanged(int id);

	void controlDelClicked();
	void controlAddClicked();

};

}

#endif 
