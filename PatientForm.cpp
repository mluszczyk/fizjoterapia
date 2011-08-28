#include <QPushButton>
#include <QDebug>

#include "PickBirthDate.h"
#include "PatientForm.h"
#include "DB.h"

namespace Fizjoterapia {

PatientForm::PatientForm(QWidget *parent, int _patient_id)
	: Decorated(parent), patient_id(_patient_id), last_added_row(-1) {

	wrap = new QWidget;
	
	form = new QFormLayout(wrap);
	name = new QLineEdit;
	surname = new QLineEdit;
	birth = new PickBirthDate;
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

	sex_male->setChecked(true);

	form->addRow(QString::fromUtf8("Imię:"), name);
	form->addRow("Nazwisko:", surname);
	form->addRow("Data urodzenia:", birth);
	form->addRow(QString::fromUtf8("Płeć:"), sex_layout);
	form->addRow(QString::fromUtf8("Zawód:"), job);
	form->addRow("Telefon:", phone);
	form->addRow("Email:", email);

	fillFields();
	setContent(wrap);
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
		res = database.updatePatient(patient_id,
			name->text(), surname->text(), birth->date(),
			sex_female->isChecked(), job->text(),
			phone->text(), email->text());
	} else {
		patient_id = database.addPatient(name->text(),
			surname->text(), 
			birth->date(), sex_female->isChecked(), 
			job->text(), phone->text(), email->text());
		res = (bool)patient_id;
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

	name->setText(q.value(0).toString());
	surname->setText(q.value(1).toString());
	birth->setDate(q.value(2).toDate());
	if(q.value(3).toBool()) sex_female->setChecked(true);
	else sex_male->setChecked(true);
	job->setText(q.value(4).toString());
	phone->setText(q.value(5).toString());
	email->setText(q.value(6).toString());
}

int PatientForm::getPatient() {
	return patient_id;
}

}
