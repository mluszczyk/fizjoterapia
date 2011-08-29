#ifndef FIZJOTERAPIA_DB_H
#define FIZJOTERAPIA_DB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QString>
#include <QObject>
#include "config.h"
#include "Export.h"

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
	QSqlQuery listVisitsOfPatient(int patient);

	bool fillVisit(int visit_id, Visit& visit);

	int addTherapy(int patient_id);

	int saveNewVisit(int therapy_id, Visit&);
	int getVisitNumber(int visit_id);

signals:
	void modified();

};

extern DB database;

}
#endif
