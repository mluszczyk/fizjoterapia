#ifndef THERAPY_LIST_H
#define THERAPY_LIST_H

#include <QWidget>
#include "ListWidget.h"

namespace Fizjoterapia {

class TherapyList : public ListWidget {
	Q_OBJECT

protected:
	int patient;

public:
	TherapyList();
	void setPatient(int _patient);

protected:
	QSqlQuery buildQuery();
	void prepareHeaders();
	
};

}

#endif
