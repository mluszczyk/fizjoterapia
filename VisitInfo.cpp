#include <QDebug>
#include "VisitInfo.h"
#include "DB.h"

namespace Fizjoterapia {

VisitInfo::VisitInfo(QWidget *parent) : QWidget(parent) {
	layout = new QStackedLayout(this);
	nothing_label = new QLabel(QString::fromUtf8("Wybierz wizytę"));
	visit_wid = new QWidget;
	visit_layout = new QVBoxLayout(visit_wid);
	edit = new QTextEdit;

	edit->setDocument(&doc);
	visit_layout->addWidget(edit);

	pos_nothing = layout->addWidget(nothing_label);
	pos_visit = layout->addWidget(visit_wid);

	layout->setAlignment(nothing_label, Qt::AlignCenter);
}

void VisitInfo::setVisit(int visit_id) {
	if(visit_id==-1)
		layout->setCurrentWidget(nothing_label);
	else {
		refill(visit_id);
		layout->setCurrentWidget(visit_wid);
	}
}

void VisitInfo::refill(int visit_id) {
	bool res = database.fillVisit(visit_id, visit);
	if(!res) {
		qDebug() << "VisitInfo::refill() fillVisit() failed";
		return;
	}
	visitToDoc(visit, doc);
}

}
