#ifndef FIZJOTERAPIA_PATIENTINFO_H
#define FIZJOTERAPIA_PATIENTINFO_H

#include <QWidget>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QVariant>

namespace Fizjoterapia {

class PatientInfo : public QWidget {
	Q_OBJECT

private:
	int patient;
	QFormLayout *form;
	QHBoxLayout *control;
	QVBoxLayout *layout;

	QLabel *name;
	QLabel *surname;
	QLabel *birth;
	QLabel *sex;
	QLabel *job;
	QLabel *phone;
	QLabel *email;

public:
	PatientInfo();

public slots:
	void change(int);

};

}

#endif
