#include <QDate>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include "DB.h"

namespace Fizjoterapia {

DB database;

DB::DB(const char *_filename, QObject *) : QSqlDatabase("QSQLITE") {
	setDatabaseName(_filename);
}

int DB::addPatient(const QString &name, const QString &surname, 
	const QDate &birth, bool sex, 
	const QString &job, const QString &phone, 
	const QString &email) {
	QSqlQuery q(Fizjoterapia::database);
	q.prepare("INSERT INTO patient (name, surname, birth, sex, "
		"job, phone, email) VALUES (?, ?, ?, ?, ?, ?, ?)");
	q.addBindValue(name);
	q.addBindValue(surname);
	q.addBindValue(birth);
	q.addBindValue(sex);
	q.addBindValue(job);
	q.addBindValue(phone);
	q.addBindValue(email);

	bool res = q.exec();
	if(res) {
		emit modified();
		return q.lastInsertId().toInt();
	} else {
		return 0;
	}
}

QSqlQuery DB::getPatient(int patient_id) {
	QSqlQuery q(Fizjoterapia::database);
	q.prepare("SELECT name, surname, birth, sex, job, phone, email "
		"FROM patient WHERE rowid = ?");
	q.addBindValue(patient_id);

	q.exec();
	q.next();

	return q;
}

bool DB::updatePatient(int patient_id, const QString &name, 
	const QString &surname, 
	const QDate &birth, bool sex, 
	const QString &job, const QString &phone, 
	const QString &email)
{
	QSqlQuery q(Fizjoterapia::database);
	q.prepare("UPDATE patient SET name=?, surname=?, birth=?, "
		"sex=?, job=?, phone=?, email=? WHERE rowid=?");
	q.addBindValue(name);
	q.addBindValue(surname);
	q.addBindValue(birth);
	q.addBindValue(sex);
	q.addBindValue(job);
	q.addBindValue(phone);
	q.addBindValue(email);
	q.addBindValue(patient_id);

	bool res = q.exec();

	if(res) emit modified();

	return res;
}

QSqlQuery DB::listPatients() {
	QSqlQuery q(Fizjoterapia::database);
	q.prepare("SELECT patient_id, name, surname, sex, birth, "
		"first_visit, last_visit from view_list_patients");
	q.exec();

	return q;
}

QSqlQuery DB::listTherapies(int patient) {
	QSqlQuery q(Fizjoterapia::database);
	QString limit = "";

	if(patient!=-1) limit = " WHERE patient_id = ?";
	q.prepare("SELECT therapy_id, first_visit, last_visit, count "
		"from view_list_therapies" + limit);

	if(patient!=-1) q.addBindValue(patient);
	q.exec();

	return q;
}

int DB::addTherapy(int patient_id) {
	QSqlQuery q(Fizjoterapia::database);
	
	q.prepare("INSERT INTO therapy (patient_id) VALUES (?)");
	q.addBindValue(patient_id);

	bool res = q.exec();
	if(!res) return -1;

	return q.lastInsertId().toInt();
}

}
