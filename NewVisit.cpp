#include <Qt>
#include <QDebug>
#include <QWidget>
#include <QSize>

#include "config.h"
#include "NewVisit.h"

namespace Fizjoterapia {

NewVisit::NewVisit(QDialog *parent) : Guide(parent) {
	resize(QSize(700, 500));

	// Step 0
	patientList = new PatientList;
	newPatient = new QPushButton("Nowy pacjent");
	wid0 = new QWidget;
	lay0 = new QVBoxLayout(wid0);
	lay0->addWidget(patientList, 1);
	lay0->addWidget(newPatient, 0, Qt::AlignCenter);

	connect(patientList, SIGNAL(changed(int)),
			this, SLOT(patientChanged(int)));
	
	Step step0 = {"Wybierz pacjenta", wid0, false};
	append(step0);

	// Step 1
	therapyList = new TherapyList;
	newTherapy = new QPushButton("Nowa terapia");
	wid1 = new QWidget;
	lay1 = new QVBoxLayout(wid1);
	lay1->addWidget(therapyList, 1);
	lay1->addWidget(newTherapy, 0, Qt::AlignCenter);

	connect(therapyList, SIGNAL(changed(int)),
			this, SLOT(therapyChanged(int)));
	
	Step step1 = {QString::fromUtf8("Wybierz terapię"), wid1, false};
	append(step1);

	// Step 2
	wid2 = new QWidget;
	info = new QFormLayout(wid2);
	
	date = new QDateEdit;
	city = new QLineEdit(QString::fromUtf8(DEFAULT_CITY));
	info->addRow("Data wizyty:", date);
	info->addRow(QString::fromUtf8("Miejscowość:"), city);

	Step step2 = {QString::fromUtf8("Ogólne informacje"), wid2, true};
	append(step2);

	// Step 3
	wid3 = new QWidget;
	lay3 = new QGridLayout(wid3);

	interview_label = new QLabel("Wywiad");
	interview = new QTextEdit;
	test_res_label = new QLabel("Badania");
	test_res = new QTextEdit;
	control_label = new QLabel("Testy kontrolne");
	control = new QStringListModel;
	control_view = new QListView;
	control_add = new QPushButton("Dodaj");
	control_del = new QPushButton(QString::fromUtf8("Usuń"));
	control_buttons = new QHBoxLayout;

	interview->setTabChangesFocus(true);
	test_res->setTabChangesFocus(true);
	control_view->setModel(control);
	control_buttons->addWidget(control_add);
	connect(control_add, SIGNAL(clicked()), this,
			SLOT(controlAddClicked()));
	control_buttons->addWidget(control_del);
	connect(control_del, SIGNAL(clicked()), this,
			SLOT(controlDelClicked()));

	lay3->addWidget(interview_label, 0, 0);
	lay3->addWidget(interview, 1, 0);
	lay3->addWidget(test_res_label, 0, 1);
	lay3->addWidget(test_res, 1, 1);
	lay3->addWidget(control_label, 2, 0, 1, 2);
	lay3->addWidget(control_view, 3, 0, 1, 2);
	lay3->addLayout(control_buttons, 4, 0, 1, 2, Qt::AlignCenter);

	Step step3 = {QString::fromUtf8("Wywiad i testy kontrolne"),
		wid3, true};
	append(step3);

	// Step	4
	wid4 = new QWidget;
	treat_buttons_wrap = new QWidget;
	lay4 = new QVBoxLayout(wid4);
	treat_buttons = new QHBoxLayout(treat_buttons_wrap);
	treat = new QStandardItemModel;
	treat_view = new QTableView;
	treat_del = new QPushButton(QString::fromUtf8("Usuń"));
	treat_add = new QPushButton("Dodaj");

	treat_buttons->addWidget(treat_add);
	treat_buttons->addWidget(treat_del);
	
	lay4->addWidget(treat_view, 1);
	lay4->addWidget(treat_buttons_wrap, 0, Qt::AlignCenter);

	Step step4 = {QString::fromUtf8("Zabiegi"), wid4, true};
	append(step4);

	// Last step
	label_last = new QLabel("Gratulacje");

	Step step_last = {QString::fromUtf8("Wizyta zapisana"), label_last,
		false};
	append(step_last);
}

void NewVisit::patientChanged(int id) {
	if(id==-1) {
		setReady(0, false);
		patient_id = 0;
	} else {
		setReady(0, true);
		patient_id = id;
	}
}

void NewVisit::therapyChanged(int id) {
	if(id==-1) {
		setReady(1, false);
		patient_id = 0;
	} else {
		setReady(1, true);
		patient_id = id;
	}
}

void NewVisit::goTo(int step) {
	if(step == 0) {
		patientList->refill();
	} else if(step == 1) {
		therapyList->setPatient(patient_id);
		therapyList->refill();
		if(therapyList->isEmpty()) {
			if(current<step) goTo(2);
			else goTo(0);

			return;
		}
	}

	Guide::goTo(step);
}

void NewVisit::controlAddClicked() {
	int num = control->rowCount();
	QString label = QString("Test ") + QString::number(num+1);
	control->insertRows(num, 1);
	control->setData(control->index(num), label);

	control_view->edit(control->index(num));
}

void NewVisit::controlDelClicked() {
	QModelIndexList list = control_view->selectionModel()->selectedRows();
	if(list.size()==0) return;

	int row = list[0].row();
	control->removeRows(row, 1);
}

}
