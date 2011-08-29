#include <QTextDocument>
#include <QTextCursor>
#include "Export.h"

namespace Fizjoterapia {

const char VISIT_HTML[] = 
"<table>%1</table>"
"<h2>Wywiad</h2><p>%2</p>"
"<h2>Wyniki badań</h2><p>%3</p>"
"<h2>Testy kontrolne</h2>%4"
"<h2>Zabiegi</h2>%5"
"<h2>Autoterapia</h2>%6";

const char VISIT_TABLE[] = 
"<tr><th>Numer</th><td>%1</td></tr>"
"<tr><th>Data</th><td>%2</td></tr>"
"<tr><th>Miejscowość</th><td>%3</td></tr>";

const char INTERVIEW_EMPTY[] = "<p><i>Wywiad jest pusty</i></p>";
const char TEST_RES_EMPTY[] = "<p><i>Brak badań</i></p>";
const char AUTOTHERAPY_EMPTY[] = "<p><i>Brak zaleceń do autoterapii</i></p>";
const char CONTROLS_EMPTY[] = "<p><i>Brak</i></p>";
const char TREATMENTS_EMPTY[] = "<p><i>Nie wykonano żadnych badań</i></p>";

QString resToStr(int val) {
	if(val == -1) return "-";
	else if(val == 0) return "0";
	else return "+";
}

void visitToDoc(Visit &visit, QTextDocument &doc) {
	doc.clear();
	QString html = QString::fromUtf8(VISIT_HTML);
	QString controls, treatments;

	if(visit.controls.isEmpty()) controls = CONTROLS_EMPTY;
	else {
		controls = "<ol>";
		QString str;
		foreach(str, visit.controls)
			controls+=QString("<li>%1</li>").arg(str);
		controls += "</ol>";
	}

	if(visit.treatments.isEmpty()) 
		treatments = QString::fromUtf8(TREATMENTS_EMPTY);
	else {
		QList<QList<int> >::iterator it = visit.results.begin();
		treatments = "<table>";
		QString row = "<tr><th>Zabieg:</th>";
		for(int i=0; i<visit.controls.size(); ++i)
			row += QString("<td>Test %1</td>").arg(i+1);
		treatments += row + "</tr>";
		foreach(QString str, visit.treatments) {
			row = QString("<tr><th>%1</th>").arg(str);
			foreach(int val, *it) 
				row += QString("<td>%1</td>").arg(
						resToStr(val));
			it++;
			treatments += row;
		}
		treatments += "</table>";
	}
	
	
	html = html.arg(QString::fromUtf8(VISIT_TABLE)
			.arg(visit.number)
			.arg(visit.date.toString("yyyy-MM-dd"))
			.arg(visit.place))
		.arg(!visit.interview.isEmpty()? 
				visit.interview : INTERVIEW_EMPTY)
		.arg(!visit.test_res.isEmpty()? 
				visit.test_res : 
				QString::fromUtf8(TEST_RES_EMPTY))
		.arg(controls).arg(treatments)
		.arg(!visit.autotherapy.isEmpty()? visit.autotherapy :
				QString::fromUtf8(AUTOTHERAPY_EMPTY));

	doc.setHtml(html);
}


}
