#include <QSqlQuery>
#include <QString>

#include "DB.h"
#include "PatientInfo.h"
#include "PatientForm.h"

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

	modify = new QPushButton("Modyfikuj dane");
	history = new QPushButton(QString::fromUtf8("Historia chorób"));
	control->addWidget(modify);
	control->addWidget(history);
	modify->setEnabled(false);
	history->setEnabled(false);

	connect(modify, SIGNAL(clicked()), this, SLOT(modifyClicked()));
	connect(history, SIGNAL(clicked()), this, SLOT(historyClicked()));
}

void PatientInfo::change(int _patient) {
	patient = _patient;

	if(patient==-1) {
		modify->setEnabled(false);
		history->setEnabled(false);
		return;
	}

	modify->setEnabled(true);
	history->setEnabled(true);

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

QSize PatientInfo::sizeHint() const {
	return QSize(300, -1);
}

void PatientInfo::historyClicked() {
}

void PatientInfo::modifyClicked() {
	PatientForm form(this, patient);
	form.exec();
}

}
