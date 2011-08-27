#ifndef FIZJOTERAPIA_GUIDE_H
#define FIZJOTERAPIA_GUIDE_H

#include <QPushButton>
#include "Decorated.h"

namespace Fizjoterapia {

struct Step {
public:

	QString title;
	QWidget *content;
	bool ready;

public:
	void clickedNext();
	void clickedPrev();
	void displayed();
};

class Guide : public Decorated {
	Q_OBJECT
protected:
	QList<Step > steps;
	int current;

	QPushButton *next;
	QPushButton *prev;
	QPushButton *cancel;
	QPushButton *finish;

protected slots:
	void clickedNext();
	void clickedPrev();
	void clickedCancel();
	void clickedFinish();

public:
	Guide(QDialog *parent=0);
	void append(const Step& step);
	void setReady(int step, bool ready);

	virtual void goTo(int step);
};

}

#endif 
