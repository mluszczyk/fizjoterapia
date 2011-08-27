#include <QSqlQuery>
#include <QString>

#include "DB.h"
#include "PatientInfo.h"

namespace Fizjoterapia {

PatientInfo::PatientInfo() : patient(-1) {
	layout = new QVBoxLayout(this);

	form = new QFormLayout;
	control = new QHBoxLayout;

	layout->addLayout(form, 1);
	layout->addLayout(control, 0);
	layout->setAlignment(control, Qt::AlignCenter);

	name = new QLabel;
	surname = new QLabel;
	birth = new QLabel;
	sex = new QLabel;
	phone = new QLabel;
	job = new QLabel;
	email = new QLabel;

	form->addRow(QString::fromUtf8("Imię:"), name);
	form->addRow("Nazwisko:", surname);
	form->addRow("Data urodzenia:", birth);
	form->addRow(QString::fromUtf8("Płeć:"), sex);
	form->addRow(QString::fromUtf8("Zawód:"), job);
	form->addRow("Telefon:", phone);
	form->addRow("Email:", email);
}

void PatientInfo::change(int _patient) {
	patient = _patient;

	QSqlQuery q = database.getPatient(patient);

	name->setText(q.value(0).toString());
	surname->setText(q.value(1).toString());
	birth->setText(q.value(2).toString());
	sex->setText(q.value(3).toBool()?
			"Kobieta":QString::fromUtf8("Mężczyzna"));
	job->setText(q.value(4).toString());
	phone->setText(q.value(5).toString());
	email->setText(q.value(6).toString());
}

}
