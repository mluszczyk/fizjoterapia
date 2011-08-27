#include "Guide.h"
#include <QString>
#include <QHBoxLayout>
#include <QWidget>

namespace Fizjoterapia {

void Step::clickedNext() {}
void Step::clickedPrev() {}
void Step::displayed() {}

Guide::Guide(QDialog *parent) : Decorated(parent), current(-1) {
	next = new QPushButton("Dalej");
	prev = new QPushButton("Wstecz");
	cancel = new QPushButton("Przerwij");
	finish = new QPushButton(QString::fromUtf8("Zakończ"));

	controls->addWidget(cancel);
	controls->addWidget(prev);
	controls->addWidget(next);
	controls->addWidget(finish);

	connect(next, SIGNAL(clicked()), this, SLOT(clickedNext()));
	connect(prev, SIGNAL(clicked()), this, SLOT(clickedPrev()));
	connect(cancel, SIGNAL(clicked()), this, SLOT(clickedCancel()));
	connect(finish, SIGNAL(clicked()), this, SLOT(clickedFinish()));
}

void Guide::append(const Step& step) {
	steps.append(step);
	if(current == -1) {
		goTo(0);
	} else if(steps.size()==2) {
		finish->setVisible(false);
		cancel->setVisible(true);
		next->setVisible(true);
	}
}

void Guide::clickedCancel() {
	reject();
}

void Guide::clickedFinish() {
	accept();
}

void Guide::clickedNext() {
	steps[current].clickedNext();
	goTo(current+1);
}

void Guide::clickedPrev() {
	steps[current].clickedPrev();
	goTo(current-1);
}

void Guide::goTo(int step) {
	current = step;
	setContent(steps[step].content);

	next->setVisible(step<steps.count()-1);
	prev->setVisible(step>0 && step<steps.count()-1);
	cancel->setVisible(step<steps.count()-1);
	finish->setVisible(step==steps.count()-1);

	next->setEnabled(steps[step].ready);

	setTitle(steps[step].title);

	steps[current].displayed();
}

void Guide::setReady(int step, bool ready) {
	steps[step].ready = ready;
	if(step == current) {
		next->setEnabled(ready);
	}
}

}
