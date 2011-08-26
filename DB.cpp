#include <QDate>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include "DB.h"

namespace Fizjoterapia {

DB database;

DB::DB(const char *_filename) : QSqlDatabase("QSQLITE") {
	setDatabaseName(_filename);
}

bool DB::addPatient(const QString &name, const QString &surname, 
	const QDate &birth, bool sex, 
	const QString &job, const QString &phone, 
	const QString &email) {
	QSqlQuery q(Fizjoterapia::database);
	q.prepare("INSERT INTO patient (name, surname, birth, sex, phone, "
		"job, email) VALUES (?, ?, ?, ?, ?, ?, ?)");
	q.addBindValue(name);
	q.addBindValue(surname);
	q.addBindValue(birth);
	q.addBindValue(sex);
	q.addBindValue(phone);
	q.addBindValue(job);
	q.addBindValue(email);

	bool res = q.exec();

	return res;
}

QSqlQuery DB::getPatient(int patient_id) {
	QSqlQuery q(Fizjoterapia::database);
	q.prepare("SELECT name, surname, birth, sex, phone, job, email "
		"FROM patient WHERE id = ?");
	q.addBindValue(patient_id);

	q.exec();

	return q;
}

QSqlQuery DB::listPatients() {
	QSqlQuery q(Fizjoterapia::database);
	q.prepare("SELECT patient_id, name, surname, sex, birth, first_visit, "
		"last_visit from view_list_patients");
	q.exec();

	return q;
}

}
