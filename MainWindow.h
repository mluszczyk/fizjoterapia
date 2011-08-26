#ifndef FIZJOTERAPIA_MAINWINDOW_H
#define FIZJOTERAPIA_MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QPushButton>
#include <QBoxLayout>

namespace Fizjoterapia {

class MainWindow : public QDialog {
	Q_OBJECT

private:
	QBoxLayout *mainLayout;

public:
	MainWindow();

private slots:
	void clickedNewVisit();
	void clickedHistory();
	void clickedNewPatient();

private:
	void createButton(const QString &title, const QString &desc, const char slot[]);
};

}

#endif
