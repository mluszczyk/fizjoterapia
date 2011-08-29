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

QSqlQuery DB::listVisitsOfPatient(int patient_id) {
	QSqlQuery q(Fizjoterapia::database);
	q.prepare("SELECT visit_id, therapy_id, date, number "
		        "FROM view_list_visits "
			"WHERE patient_id = ?");
	q.addBindValue(patient_id);
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

bool DB::fillVisit(int visit_id, Visit& visit) {
	QSqlQuery q(Fizjoterapia::database);
	q.prepare("SELECT number, date, place, interview, test_res, "
			"autotherapy FROM visit WHERE rowid = ?");
	q.addBindValue(visit_id);
	if(!q.exec() || !q.next()) {
		qDebug() << "DB::fillVisit() selection from visit failed";
		qDebug() << q.lastError();
		return false;
	}
	visit.number = q.value(0).toInt();
	visit.date = q.value(1).toDate();
	visit.place = q.value(2).toString();
	visit.interview = q.value(3).toString();
	visit.test_res = q.value(4).toString();
	visit.autotherapy = q.value(5).toString();

	int tcount = 0, ccount = 0;

	visit.treatments.clear();
	q.prepare("SELECT name from treatment "
			"WHERE visit_id = ? ORDER BY number");
	q.addBindValue(visit_id);
	if(!q.exec()) {
		qDebug() << "DB::fillVisit() selection from treat failed";
		qDebug() << q.lastError();
		return false;
	}
	while(q.next()) {
		QString name = q.value(0).toString();
		visit.treatments.append(name);
		tcount+=1;
	}
	
	visit.controls.clear();
	q.prepare("SELECT name from control "
			"WHERE visit_id = ? ORDER BY number");
	q.addBindValue(visit_id);
	if(!q.exec()) {
		qDebug() << "DB::fillVisit() selection from control failed";
		qDebug() << q.lastError();
		return false;
	}
	while(q.next()) {
		QString name = q.value(0).toString();
		visit.controls.append(name);
		ccount +=1;
	}

	visit.results.clear();
	q.prepare("select result "
		"from control_result, control, treatment "
		"on (control.rowid = control_id and "
		"treatment.rowid = treatment_id) "
		"where control.visit_id = ?");
	q.addBindValue(visit_id);
	if(!q.exec()) {
		qDebug() << "DB::fillVisit selection from result failed";
		qDebug() << q.lastError();
		return false;
	}
	for(int i=0; i<tcount; ++i) {
		visit.results.append(QList<int>());
		QList<int > &list = visit.results.last();
		for(int j=0; j<ccount; ++j) {
			if(!q.next()) {
				qDebug() << "DB::fillVisit bad visit";
				return false;
			}
			list.append(q.value(0).toInt());
		}
	}

	return true;
}

int DB::saveNewVisit(int therapy_id, Visit& visit) {
	QSqlQuery q(Fizjoterapia::database);

	// Inserting base
	q.prepare("INSERT INTO visit (therapy_id, date, place, interview, "
		"test_res, autotherapy, number) "
		"SELECT ?, ?, ?, ?, ?, ?, "
		"CASE WHEN max(number) IS NULL THEN 1 ELSE number+1 END "
		"FROM view_list_visits WHERE therapy_id = ?");
	q.addBindValue(therapy_id);
	q.addBindValue(visit.date);
	q.addBindValue(visit.place);
	q.addBindValue(visit.interview);
	q.addBindValue(visit.test_res);
	q.addBindValue(visit.autotherapy);
	q.addBindValue(therapy_id);

	bool res = q.exec();
	if(!res) {
		qDebug() << "DB::saveNewVisit() insertion into visit failed";
		qDebug() << q.lastError();
		return -1;
	}

	int visit_id = q.lastInsertId().toInt();

	// Inserting control tests and treatment names
	QList<int> control_ids, treat_ids;
	for(int i=0; i<visit.controls.size(); ++i) {
		q.prepare("INSERT INTO control (visit_id, number, name) "
				"values (?, ?, ?)");
		q.addBindValue(visit_id);
		q.addBindValue(i);
		q.addBindValue(visit.controls[i]);

		res = q.exec();
		if(!res) {
			qDebug() << "NewVisit::toDb() insertion "
				"into control failed";
			qDebug() << q.lastError();
			return -1;
		}

		control_ids.append(q.lastInsertId().toInt());
	}

	for(int i=0; i<visit.treatments.size(); ++i) {
		q.prepare("INSERT INTO treatment (visit_id, number, name) "
				"values (?, ?, ?)");
		q.addBindValue(visit_id);
		q.addBindValue(i);
		q.addBindValue(visit.treatments[i]);

		res = q.exec();
		if(!res) {
			qDebug() << "NewVisit::toDb() insertion "
				"into treatment failed";
			qDebug() << q.lastError();
			return -1;
		}

		treat_ids.append(q.lastInsertId().toInt());
	}

	q.prepare("INSERT INTO control_result (control_id, treatment_id, "
			"result) VALUES (?, ?, ?)");

	QVariantList bind_cids, bind_tids, bind_res;

	for(int i=0; i<visit.treatments.size(); ++i) {
		for(int j=0; j<visit.controls.size(); ++j) {
			bind_tids.append(treat_ids[i]);
			bind_cids.append(control_ids[j]);
			bind_res.append(visit.results[i][j]);
		}
	}

	q.addBindValue(bind_cids);
	q.addBindValue(bind_tids);
	q.addBindValue(bind_res);

	if(!q.execBatch()) {
		qDebug() << q.lastError();
		qDebug() << "NewVisit::toDb() insertion into res failed";
		return -1;
	}

	return visit_id;
}

int DB::getVisitNumber(int visit_id) {
	QSqlQuery q(Fizjoterapia::database);
	q.prepare("SELECT number FROM visit WHERE visit_id=?");
	q.addBindValue(visit_id);
	if(!q.exec() || !q.next()) return -1;

	return q.value(0).toInt();

}

}
