#ifndef FIZJO_BROWSEHISTORY_H
#define FIZJO_BROWSEHISTORY_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

#include "Decorated.h"
#include "TherapiesTree.h"
#include "VisitInfo.h"

namespace Fizjoterapia {

class BrowseHistory : public Decorated {
	Q_OBJECT

private:
	int patient;
	QWidget *wid;
	QHBoxLayout *lay;
	TherapiesTree *tree;
	VisitInfo *info;
	QPushButton *close;

public:
	BrowseHistory(int _patient, QWidget *parent=0);
	
public slots:
	void refill();
	void clickedClose();

};

}

#endif
