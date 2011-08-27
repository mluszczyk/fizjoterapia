#ifndef FIZJOTERAPIA_DB_H
#define FIZJOTERAPIA_DB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QString>
#include <QObject>
#include "config.h"

namespace Fizjoterapia {

class DB : public QObject, public QSqlDatabase {
	Q_OBJECT

public:
	DB(const char *_filename = DB_FILENAME, QObject *parent=0);

	int addPatient(const QString &name, const QString &surname, 
		const QDate &birth, bool sex, 
		const QString &job, const QString &phone, 
		const QString &email);
	bool updatePatient(int patient_id,
		const QString &name, const QString &surname, 
		const QDate &birth, bool sex, 
		const QString &job, const QString &phone, 
		const QString &email);
	QSqlQuery getPatient(int patient_id);

	QSqlQuery listPatients();
	QSqlQuery listTherapies(int patient=-1);

	int addTherapy(int patient_id);

signals:
	void modified();

};

extern DB database;

}
#endif
