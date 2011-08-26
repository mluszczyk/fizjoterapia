#ifndef FIZJOTERAPIA_DB_H
#define FIZJOTERAPIA_DB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QString>
#include "config.h"

namespace Fizjoterapia {

class DB : public QSqlDatabase {
public:
	DB(const char *_filename = DB_FILENAME);

	bool addPatient(const QString &name, const QString &surname, 
		const QDate &birth, bool sex, 
		const QString &job, const QString &phone, 
		const QString &email);
	QSqlQuery getPatient(int patient_id);

	QSqlQuery listPatients();

};

extern DB database;

}
#endif
