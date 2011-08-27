#include <QDebug>

#include "BrowsePatients.h"

namespace Fizjoterapia {

BrowsePatients::BrowsePatients(QWidget *parent) 
	: Decorated(parent, "Pacjenci") {
	cont = new QWidget;
	layout = new QHBoxLayout(cont);
	pl = new PatientList;
	pi = new PatientInfo;

	layout->addWidget(pl);
	layout->addWidget(pi);

	connect(pl, SIGNAL(changed(int)), 
		pi, SLOT(change(int)));

	
	setContent(cont);
}

void BrowsePatients::refill() {
	pl->refill();
}

}
