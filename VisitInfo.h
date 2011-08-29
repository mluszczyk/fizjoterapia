#ifndef FIZJO_VISITINFO_H
#define FIZJO_VISITINFO_H

#include <QWidget>
#include <QLabel>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QTextEdit>

#include "Export.h"

namespace Fizjoterapia {

class VisitInfo : public QWidget {
	Q_OBJECT

private:
	QStackedLayout *layout;
//	QWidget *nothing;
	QLabel *nothing_label;
	QWidget *visit_wid;
	QVBoxLayout *visit_layout;
	QTextEdit *edit;

	int pos_nothing, pos_visit;

	Visit visit;
	QTextDocument doc;

public:
	VisitInfo(QWidget *parent=0);

private:
	void refill(int visit_id);

public slots:
	void setVisit(int visit);
};

}

#endif
