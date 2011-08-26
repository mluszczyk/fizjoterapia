#include "PatientForm.h"
#include "NewVisit.h"
#include "MainWindow.h"
#include "DB.h"

namespace Fizjoterapia {

MainWindow::MainWindow() {
	mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	setWindowTitle("Fizjoterapia");

	createButton("Nowa wizyta", "Rozpocznij tworzenie nowej wizyty", 
			SLOT(clickedNewVisit()));
	createButton("Pacjenci i choroby", "Przeglądaj pacjentów i historię chorób", 
			SLOT(clickedHistory()));
	createButton("Dodaj pacjenta", "Dodaj nowego pacjenta do bazy", 
			SLOT(clickedNewPatient()));
}

void MainWindow::createButton(const QString &title, const QString &desc, const char slot[]) {
	QPushButton *button = new QPushButton(title, this);
	connect(button, SIGNAL(clicked()), this, slot);
	mainLayout->addWidget(button);
}

void MainWindow::clickedNewVisit() {
    NewVisit nw(this);
    nw.exec();
}

void MainWindow::clickedHistory() {}
void MainWindow::clickedNewPatient() {
	PatientForm pf(this);
	pf.exec();
}

}
