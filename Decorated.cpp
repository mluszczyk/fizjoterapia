#include <QDebug>
#include "Decorated.h"

namespace Fizjoterapia {

Decorated::Decorated(QWidget *parent, const QString &_title) : QDialog(parent) {
	main = new QVBoxLayout(this);
	header = new QVBoxLayout();
	content = new QVBoxLayout();
	controls = new QHBoxLayout();

	current_content = 0;

	title = new QLabel;
	subtitle = new QLabel;

	header->addWidget(title);

	main->addLayout(header);
	main->addLayout(content);
	main->addLayout(controls);

	controls->setAlignment(Qt::AlignRight);

	setTitle(_title);
}

void Decorated::setTitle(const QString &_title) {
	setWindowTitle(_title);
	title->setText("<span style=\"font-size: xx-large; font-weight: bold\">"+_title+"</span>");
}

void Decorated::setContent(QLayout *layout) {
	if(current_content) content->removeItem(current_content);
	current_content = layout;
	content->addLayout(layout);
}

void Decorated::addControl(QWidget *widget) {
	controls->addWidget(widget);
}

}
