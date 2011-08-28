#ifndef FIZJOTERAPIA_PICKBIRTHDATE_H
#define FIZJOTERAPIA_PICKBIRTHDATE_H

#include <QWidget>
#include <QDate>
#include <QHBoxLayout>
#include <QSpinBox>

namespace Fizjoterapia {

class PickBirthDate : public QWidget {
	Q_OBJECT
	Q_PROPERTY(QDate date 
		READ date
		WRITE setDate
		NOTIFY dateChanged)

	static const int AVERAGE_AGE = 37.3*365.25;

protected:
	QHBoxLayout *layout;
	QSpinBox *day, *month, *year;

public:
	PickBirthDate(QDate date=QDate::currentDate().addDays(
				-AVERAGE_AGE));

	QDate date() const;
	void setDate(const QDate &date);

signals:
	void dateChanged();
	
};

}

#endif
