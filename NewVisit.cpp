#include <Qt>
#include <QDebug>
#include <QWidget>
#include <QSize>
#include <QHeaderView>
#include <QSqlError>

#include "config.h"
#include "DB.h"
#include "NewVisit.h"
#include "PatientForm.h"

namespace Fizjoterapia {

NewVisit::NewVisit(QDialog *parent) : Guide(parent), 
	patient_id(-1), therapy_id(-1), visit_id(-1), success(false) {
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
	connect(newPatient, SIGNAL(clicked()),
			this, SLOT(newPatientClicked()));
	
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
	connect(newTherapy, SIGNAL(clicked()),
			this, SLOT(newTherapyClicked()));
	
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
	control_edit = new QPushButton(QString::fromUtf8("Edytuj"));
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
	control_buttons->addWidget(control_edit);
	connect(control_edit, SIGNAL(clicked()), this,
			SLOT(controlEditClicked()));

	connect(control, SIGNAL(rowsRemoved(const QModelIndex &, int, int)),
		this, SLOT(controlDcr(const QModelIndex &, int, int)));
	connect(control, SIGNAL(rowsInserted(const QModelIndex &, int, int)),
		this, SLOT(controlInc(const QModelIndex &, int, int)));
	connect(control, 
		SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
		this,
		SLOT(controlCh(const QModelIndex &, const QModelIndex &)));


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
	treat_buttons = new QHBoxLayout;//(treat_buttons_wrap);
	treat = new QStandardItemModel;
	treat_view = new QTableView;
	treat_del = new QPushButton(QString::fromUtf8("Usuń"));
	treat_add = new QPushButton("Dodaj");
	treat_edit = new QPushButton("Edytuj");

	treat_delegate = new TreatDelegate;
	res_delegate = new ResDelegate;

	treat_view->setModel(treat);
	QList<QStandardItem *> list;
	treat->appendColumn(list);
	treat->setHeaderData(0, Qt::Horizontal, "Rodzaj zabiegu"); 

	treat_buttons->addWidget(treat_add);
	treat_buttons->addWidget(treat_del);
	treat_buttons->addWidget(treat_edit);

	connect(treat_add, SIGNAL(clicked()), this, 
			SLOT(treatAddClicked()));
	connect(treat_del, SIGNAL(clicked()), this,
			SLOT(treatDelClicked()));
	connect(treat_edit, SIGNAL(clicked()), this,
			SLOT(treatEditClicked()));

	treat_view->verticalHeader()->hide();
	treat_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	treat_view->setSelectionMode(QAbstractItemView::SingleSelection);
	treat_view->setItemDelegate(res_delegate);
	treat_view->setItemDelegateForColumn(0, treat_delegate);
	
	lay4->addWidget(treat_view, 1);
	lay4->addLayout(treat_buttons);
	lay4->setAlignment(treat_buttons, Qt::AlignCenter);

	Step step4 = {QString::fromUtf8("Zabiegi"), wid4, true};
	append(step4);

	// Step 5
	wid5 = new QWidget;
	lay5 = new QVBoxLayout(wid5);
	auto_label = new QLabel("Autoterapia");
	autotherapy = new QTextEdit;

	autotherapy->setTabChangesFocus(true);
	lay5->addWidget(auto_label);
	lay5->addWidget(autotherapy);
	
	Step step5 = {"Autoterapia", wid5, true};	
	append(step5);

	// Step 6 - confirm
	confirm_label = new QLabel(QString::fromUtf8(
		"<b>Tworzenie wizyty zakończone!</b><br/><br/>Kliknij "
		"<i>Dalej</i> aby zatwierdzić wizytę i zapisać ją w bazie. "
		"Możesz też wrócić się, aby poprawić "
		"wprowadzone dane klikając <i>Wstecz</i> "
		"lub wybrać <i>Przerwij</i>, aby "
		"zrezygnować z tworzonej wizyty."));
	confirm_label->setWordWrap(true);

	Step step6 = {QString::fromUtf8("Potwierdzenie wizyty"), 
		confirm_label, true};
	append(step6);

	// Last step
	label_last = new QLabel(QString::fromUtf8("<b>Gratulacje! Wizyta "
		"została zapisana!</b><br/><br/> "
		"Możesz już bezpiecznie zamknąć to okno. "
		"Możesz też wybrać jedną z poniższych opcji:"));

	Step step_last = {QString::fromUtf8("Wizyta zapisana"), label_last,
		false};
	append(step_last);
}

void NewVisit::exec() {
	bool res;
	res = database.transaction();
	if(!res) {
		// TODO: ERROR
		qDebug() << "NewVisit: couldn't open transaction";
		return;
	}

	Guide::exec();
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
		therapy_id = 0;
	} else {
		setReady(1, true);
		therapy_id = id;
	}
}

void NewVisit::goTo(const int step) {
	if(step == 0) {
		patientList->refill();
		patientList->selectId(patient_id);
	} else if(step == 1) {
		therapyList->setPatient(patient_id);
		therapyList->refill();
		if(therapyList->isEmpty()) {
			newTherapyClicked();
			return;
		} else {
			therapyList->selectId(therapy_id);
		}
	} else if(step == steps.count()-1) {
		visit_id = toDb();
		if(visit_id>0)
			success = database.commit();
		else {
			database.rollback();
			qDebug() << "NewVisit::goTo() toDb failed";
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

void NewVisit::controlEditClicked() {
	QModelIndexList list = control_view->selectionModel()->selectedRows();
	if(list.size()==0) return;

	int row = list[0].row();
	control_view->edit(control->index(row));
}

void NewVisit::treatAddClicked() {
	QList<QStandardItem *> list;
	list.append(new QStandardItem(""));
	for(int i=0; i<treat->columnCount()-1; ++i) {
		list.append(new QStandardItem("0"));
	}
	treat->appendRow(list);
	
	int row = treat->rowCount()-1;
	treat_view->edit(treat->index(row, 0));
}

void NewVisit::treatDelClicked() {
	QModelIndexList list = treat_view->selectionModel()->selectedRows();
	if(list.size()==0) return;

	int row = list[0].row();
	treat->removeRow(row);
}

void NewVisit::treatEditClicked() {
	QModelIndexList list = treat_view->selectionModel()->selectedRows();
	if(list.size()==0) return;

	int row = list[0].row();
	treat_view->edit(treat->index(row, 0));
}


void NewVisit::controlInc(const QModelIndex &, int, int) {
	QList<QStandardItem *> list;
	for(int i=0; i<treat->rowCount(); ++i)
		list.append(new QStandardItem("0"));
	treat->appendColumn(list);
}

void NewVisit::controlDcr(const QModelIndex &, int start, int) {
	treat->removeColumn(start+1);
}

void NewVisit::controlCh(const QModelIndex &tl, const QModelIndex &) {
	int row = tl.row();
	QString label = tl.data().toString();
	treat->setHeaderData(row+1, Qt::Horizontal, label);
}

void NewVisit::reject() {
	bool res = database.rollback();
	if(!res) qDebug() << "Rollback failed";
	Guide::reject();
}

void NewVisit::newPatientClicked() {
	PatientForm pf(this);
	int res = pf.exec();

	if(res==QDialog::Accepted) {
		patient_id = pf.getPatient();
		goTo(1);
	}
}
void NewVisit::newTherapyClicked() {
	therapy_id = database.addTherapy(patient_id);
	if(therapy_id<=0) {
		qDebug() << "addTherapy failed";
		return;
	}

	goTo(2);
}

int NewVisit::toDb() {
	// Getting number
	QSqlQuery q(database);
	q.prepare("SELECT max(number) from visit where therapy_id=?");
	q.addBindValue(therapy_id);
	q.exec();
	q.next();

	int number = q.value(0).toInt();
	if(number == 0) number = 1;

	// Inserting base
	q.prepare("INSERT INTO visit (therapy_id, date, place, interview, "
		"test_res, autotherapy, number) "
		"VALUES (?, ?, ?, ?, ?, ?, ?)");
	q.addBindValue(therapy_id);
	q.addBindValue(date->date());
	q.addBindValue(city->text());
	q.addBindValue(interview->toPlainText());
	q.addBindValue(test_res->toPlainText());
	q.addBindValue(autotherapy->toPlainText());
	q.addBindValue(number);

	bool res = q.exec();
	if(!res) {
		qDebug() << "NewVisit::toDb() insertion into visit failed";
		qDebug() << q.lastError();
		return -1;
	}

	visit_id = q.lastInsertId().toInt();

	// Inserting control tests and treatment names
	QList<int> control_ids, treat_ids;
	for(int i=0; i<control->rowCount(); ++i) {
		q.prepare("INSERT INTO control (visit_id, number, name) "
				"values (?, ?, ?)");
		q.addBindValue(visit_id);
		q.addBindValue(i);
		q.addBindValue(control->index(i).data());

		res = q.exec();
		if(!res) {
			qDebug() << "NewVisit::toDb() insertion "
				"into control failed";
			qDebug() << q.lastError();
			return -1;
		}

		control_ids.append(q.lastInsertId().toInt());
	}

	for(int i=0; i<treat->rowCount(); ++i) {
		q.prepare("INSERT INTO treatment (visit_id, number, name) "
				"values (?, ?, ?)");
		q.addBindValue(visit_id);
		q.addBindValue(i);
		q.addBindValue(treat->index(i, 0).data());

		res = q.exec();
		if(!res) {
			qDebug() << "NewVisit::toDb() insertion "
				"into treatment failed";
			qDebug() << q.lastError();
			return -1;
		}

		treat_ids.append(q.lastInsertId().toInt());
	}

	/*
	q.prepare("INSERT INTO control_result (control_id, treatment_id, "
			"result) VALUES (?, ?, ?)");

	QVariantList bind_cids, bind_tids, bind_res;

	for(int i=0; i<treat->rowCount(); ++i) {
		for(int j=0; j<treat->columnCount()-1; ++j) {
			bind_tids.append(treat_ids[i]);
			bind_cids.append(control_ids[j]);
			bind_res.append(treat->index(i, j+1).data().toInt());
		}
	}

	if(!q.execBatch()) {
		qDebug() << q.lastError();
		qDebug() << "NewVisit::toDb() insertion into res failed";
		return -1;
	}*/


	q.prepare("INSERT INTO control_result (control_id, treatment_id, "
			"result) VALUES (?, ?, ?)");

	QVariantList bind_cids, bind_tids, bind_res;

	for(int i=0; i<treat->rowCount(); ++i) {
		for(int j=0; j<treat->columnCount()-1; ++j) {
			bind_tids.append(treat_ids[i]);
			bind_cids.append(control_ids[j]);
			bind_res.append(treat->index(i, j+1).data().toInt());
		}
	}

	q.addBindValue(bind_cids);
	q.addBindValue(bind_tids);
	q.addBindValue(bind_res);

	if(!q.execBatch()) {
		qDebug() << q.lastError();
		qDebug() << "NewVisit::toDb() insertion into res failed";
		return -1;
	}

	return visit_id;
}

}
