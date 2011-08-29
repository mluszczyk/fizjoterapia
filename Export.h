#ifndef FIZJO_EXPORT_H
#define FIZJO_EXPORT_H

#include <QTextDocument>
#include <QDate>
#include <QList>

namespace Fizjoterapia {

struct Visit {
	int number; // not used by saveNewVisit
  	QDate date;
   	QString place;
	QString interview;
   	QString test_res;
	QString autotherapy;
	QList<QString> controls;
   	QList<QString> treatments;
	QList<QList<int> > results;
};

void visitToDoc(Visit &visit, QTextDocument &doc);

}

#endif
