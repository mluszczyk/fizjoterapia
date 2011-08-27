#ifndef FIZJOTERAPIA_PATIENTFORM_H
#define FIZJOTERAPIA_PATIENTFORM_H

#include <QLineEdit>
#include <QDateEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFormLayout>
#include <QLabel>

#include "Decorated.h"

namespace Fizjoterapia {

class PatientForm : public Decorated {
	Q_OBJECT

private:
	int patient_id;
	int last_added_row;
	QFormLayout *form;

	QWidget *wrap;
	QLineEdit *name;
	QLineEdit *surname;
	QDateEdit *birth;
	QVBoxLayout *sex_layout;
	QButtonGroup *sex_group;
	QRadioButton *sex_male;
	QRadioButton *sex_female;
	QLineEdit *phone;
	QLineEdit *job;
	QLineEdit *email;

public:
	PatientForm(QWidget *parent=0, int patient_id=0);
	int getPatient();

private slots:
	void clickedCommit();
	void clickedCancel();

private:

	void addRowCommon(const QString &title);
	void addRow(const QString &title, QWidget *widget);
	void addRow(const QString &title, QLayout *widget);

	bool commit();
	void fillFields();

};

}

#endif
