#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H

#include <QWidget>
#include "ListWidget.h"
#include "Delegates.h"

namespace Fizjoterapia {

class PatientList : public ListWidget {
	Q_OBJECT


public:
	PatientList();
	SexDelegate delegate;

protected:
	QSqlQuery buildQuery();
	void prepareHeaders();
	
};

}

#endif
