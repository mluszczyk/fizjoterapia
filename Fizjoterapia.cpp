#include <iostream>
#include <QtGui>
#include "MainWindow.h"
#include "DB.h"

using namespace Fizjoterapia;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	MainWindow main;

	if(!database.open()) {
		return 1;
	}
	main.show();

	return app.exec();
}
