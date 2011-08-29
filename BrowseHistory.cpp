#include "BrowseHistory.h"
#include "Decorated.h"
#include "TherapiesTree.h"
#include "VisitInfo.h"

namespace Fizjoterapia {

BrowseHistory::BrowseHistory(int _patient, QWidget *parent)
		: Decorated(parent, QString::fromUtf8("Historia chorób")),
		   	patient(_patient) {
	tree = new TherapiesTree(patient);
	info = new VisitInfo;
	wid = new QWidget;
	close = new QPushButton("Zamknij");

	lay = new QHBoxLayout(wid);
	lay->addWidget(tree, 0);
	lay->addWidget(info, 1);

	connect(tree, SIGNAL(changed(int)), info, SLOT(setVisit(int)));
	connect(close, SIGNAL(clicked()), this, SLOT(clickedClose()));

	setContent(wid);
	addControl(close);

	resize(900, 700);
}

void BrowseHistory::refill() {
	tree->refill();
}

void BrowseHistory::clickedClose() {
	accept();
}

}
