#ifndef FIZJOTERAPIA_ADDVISIT_H
#define FIZJOTEARPIA_ADDVISIT_H

#include <QPushButton>
#include "Guide.h"
#include "PatientList.h"

namespace Fizjoterapia {

class NewVisit : public Guide {
	Q_OBJECT

private:
	PatientList *patientList;
	QPushButton *newPatient;
	QVBoxLayout *lay0;

	int patient_id;

public:
	NewVisit(QDialog *parent);

private slots:
	void patientChanged(int id);

};

}

#endif 
