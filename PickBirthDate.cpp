#include "PickBirthDate.h"

namespace Fizjoterapia {

PickBirthDate::PickBirthDate(QDate date) {
	layout = new QHBoxLayout(this);
	day = new QSpinBox;
	month = new QSpinBox;
	year = new QSpinBox;

	layout->addWidget(day, 1);
	layout->addWidget(month, 1);
	layout->addWidget(year, 2);

	day->setRange(1, 31);
	month->setRange(1, 12);
	year->setRange(1800, 2100);

	setDate(date);
}

QDate PickBirthDate::date() const {
	return QDate(year->value(), month->value(),
			day->value());
}

void PickBirthDate::setDate(const QDate &date) {
	day->setValue(date.day());
	month->setValue(date.month());
	year->setValue(date.year());
}

}
