#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H

#include <QWidget>
#include "ListWidget.h"

namespace Fizjoterapia {

class PatientList : public ListWidget {
	Q_OBJECT

public:
	PatientList();

protected:
	QSqlQuery buildQuery();
	void prepareHeaders();
	
};

}

#endif
