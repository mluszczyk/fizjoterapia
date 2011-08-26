#include <Qt>
#include <QDebug>
#include <QWidget>
#include <QSize>
#include "NewVisit.h"

namespace Fizjoterapia {

NewVisit::NewVisit(QDialog *parent) : Guide(parent) {
	resize(QSize(700, 500));

	patientList = new PatientList;
	patientList->refill();
	newPatient = new QPushButton("Nowy pacjent");
	lay0 = new QVBoxLayout;
	lay0->addWidget(patientList, 1);
	lay0->addWidget(newPatient, 0, Qt::AlignCenter);

	connect(patientList, SIGNAL(changed(int)),
			this, SLOT(patientChanged(int)));
	
	Step step0 = {"Wybierz pacjenta", lay0, false};
	append(step0);
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

}
