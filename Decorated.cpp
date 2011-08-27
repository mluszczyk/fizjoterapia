#include <QDebug>
#include "Decorated.h"

namespace Fizjoterapia {

Decorated::Decorated(QWidget *parent, const QString &_title) : QDialog(parent) {
	main = new QVBoxLayout(this);
	header = new QVBoxLayout();
	content = new QStackedWidget();
	controls = new QHBoxLayout();

	current_content = 0;

	title = new QLabel;
	subtitle = new QLabel;

	header->addWidget(title);

	main->addLayout(header);
	main->addWidget(content);
	main->addLayout(controls);

	controls->setAlignment(Qt::AlignRight);

	setTitle(_title);
}

void Decorated::setTitle(const QString &_title) {
	setWindowTitle(_title);
	title->setText("<span style=\"font-size: xx-large; "
			"font-weight: bold\">"+_title+"</span>");
}

void Decorated::setContent(QWidget *widget) {
	int index = content->indexOf(widget);
	if(index==-1) {
		index = content->addWidget(widget);
	}
	content->setCurrentIndex(index);
}

void Decorated::addControl(QWidget *widget) {
	controls->addWidget(widget);
}

}
