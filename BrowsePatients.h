#ifndef FIZJOTERAPIA_BROWSEPATIENTS_H
#define FZIJOTERAPIA_BROWSEPATIENTS_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "Decorated.h"
#include "PatientForm.h"
#include "PatientList.h"
#include "PatientInfo.h"

namespace Fizjoterapia {

class BrowsePatients : public Decorated {
	Q_OBJECT

private:
	QHBoxLayout *layout;
	PatientList *pl;
	PatientInfo *pi;
	QWidget *cont;

	QPushButton *close;

public:
	BrowsePatients(QWidget* parent=0);
	void refill();

public slots:
	void closeClicked();

};

}

#endif
