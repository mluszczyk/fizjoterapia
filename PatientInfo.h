#ifndef FIZJOTERAPIA_PATIENTINFO_H
#define FIZJOTERAPIA_PATIENTINFO_H

#include <QSize>
#include <QWidget>
#include <QPushButton>
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

	QPushButton *history;
	QPushButton *modify;

public:
	PatientInfo();

	virtual QSize sizeHint() const;

public slots:
	void change(int);

	void historyClicked();
	void modifyClicked();

};

}

#endif
