#include <QPushButton>
#include <QDebug>
#include "PatientForm.h"
#include "DB.h"

namespace Fizjoterapia {

PatientForm::PatientForm(QWidget *parent, int _patient_id)
	: Decorated(parent), patient_id(_patient_id), last_added_row(-1) {
	
	form = new QFormLayout;
	name = new QLineEdit;
	surname = new QLineEdit;
	birth = new QDateEdit;
	sex_group = new QButtonGroup;
	sex_layout = new QVBoxLayout();
	   	sex_male = new QRadioButton(QString::fromUtf8("Mężczyzna"));
	sex_female = new QRadioButton("Kobieta");
	   	phone = new QLineEdit;
	job = new QLineEdit;
	email = new QLineEdit;

	sex_group->addButton(sex_male);
	sex_group->addButton(sex_female);
	sex_layout->addWidget(sex_male);
	sex_layout->addWidget(sex_female);

	sex_male->setDown(true);

	form->addRow(QString::fromUtf8("Imię"), name);
	form->addRow("Nazwisko", surname);
	form->addRow("Data urodzenia", birth);
	form->addRow(QString::fromUtf8("Płeć"), sex_layout);
	form->addRow("Telefon", phone);
	form->addRow(QString::fromUtf8("Zawód"), job);
	form->addRow("Email", email);

	fillFields();
	setContent(form);
	setModal(false);

	if(patient_id) setTitle("Modyfikacja danych pacjenta");
	else setTitle("Dodawanie pacjenta");

	QPushButton *commit = new QPushButton(QString::fromUtf8("Zatwierdź"));
	QPushButton *cancel = new QPushButton("Anuluj");

	addControl(commit);
	addControl(cancel);

	connect(commit, SIGNAL(clicked()), this, SLOT(clickedCommit()));
	connect(cancel, SIGNAL(clicked()), this, SLOT(clickedCancel()));
}

bool PatientForm::commit() {
	if(name->text().isEmpty()) {
		qDebug() << "Name empty";
		return false;
	}
	if(surname->text().isEmpty()) {
		qDebug() << "Surname empty";
		return false;
		// TODO: ERROR
	}

	bool res;

	if(patient_id) {
		res = false;
	} else {
		res = database.addPatient(name->text(), surname->text(), 
			birth->date(), sex_female->isDown(), phone->text(), 
			job->text(), email->text());
	}

	if(!res) {
		qDebug() << "PatientForm: Query failed";
		// TODO: ERROR
	}

	return res;
}

void PatientForm::clickedCommit() {
	if(commit())
		accept();
}

void PatientForm::clickedCancel() {
	reject();
}

void PatientForm::fillFields() {
	if(!patient_id) return;

	QSqlQuery q = database.getPatient(patient_id);

	if(q.size() != 1) return;  // błąd!

	name->setText(q.value(0).toString());
	surname->setText(q.value(1).toString());
	phone->setText(q.value(4).toString());
	job->setText(q.value(5).toString());
	email->setText(q.value(6).toString());
}

}
