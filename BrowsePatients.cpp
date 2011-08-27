#include <QDebug>

#include "BrowsePatients.h"

namespace Fizjoterapia {

BrowsePatients::BrowsePatients(QWidget *parent) 
	: Decorated(parent, "Pacjenci") {
	cont = new QWidget;
	layout = new QHBoxLayout(cont);
	pl = new PatientList;
	pi = new PatientInfo;

	close = new QPushButton("Zamknij");

	pl->selectFirst();

	layout->addWidget(pl);
	layout->addWidget(pi);

	connect(pl, SIGNAL(changed(int)), 
		pi, SLOT(change(int)));

	
	resize(900, 700);
	setContent(cont);
	addControl(close);
	connect(close, SIGNAL(clicked()), this, SLOT(closeClicked()));
}

void BrowsePatients::refill() {
	pl->refill();
}

void BrowsePatients::closeClicked() {
	accept();
}

}
