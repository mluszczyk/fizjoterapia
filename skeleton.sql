CREATE TABLE patient ( name text not null, surname text not null, birth timestamp not null,  sex int not null, phone text null, job text null, email text null);
CREATE TABLE therapy ( patient_id int, constraint cons_patient foreign key ( patient_id ) references patient ( rowid ) on delete cascade );
CREATE TABLE visit ( therapy_id int, date timestamp not null, place text not null, number int not null, interview text not null, test_res text not null, autotherapy text not null, constraint con_therapy foreign key (therapy_id) references therapy ( rowid ) on delete cascade );
-- TODO: results of additional examination
CREATE TABLE control ( visit_id int, number int not null, name text not null, constraint con_visit foreign key ( visit_id ) references visit (rowid) on delete cascade );
CREATE TABLE treatment ( visit_id int, number int not null, name text not null, constraint con_visit foreign key (visit_id) references visit (rowid) on delete cascade );
CREATE TABLE control_result ( control_id int, treatment_id, result int not null, constraint con_control foreign key (control_id) references control(rowid) on delete cascade, constraint con_treatment foreign key (treatment_id) references treatment (rowid) on delete cascade );

CREATE VIEW view_list_patients as select  patient.rowid as patient_id, patient.name, patient.surname, patient.sex, patient.birth, min(visit.date) as first_visit, max(visit.date) as last_visit from  Patient left join Therapy left join Visit on therapy.patient_id=patient.rowid and therapy.rowid = visit.therapy_id group by patient.rowid;
CREATE VIEW view_list_therapies as select therapy.rowid as therapy_id, patient_id, min(date) as first_visit, max(date) as last_visit, count(number) as count from therapy left join visit on therapy_id=therapy.rowid group by therapy.rowid;
CREATE VIEW view_list_visits as select patient_id, therapy_id, visit.rowid as visit_id, date, interview, number from visit, therapy on therapy_id=therapy.rowid order by therapy_id, number;

