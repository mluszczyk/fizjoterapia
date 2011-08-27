#ifndef FIZJOTERAPIA_DECORATED_H
#define FIZJOTERAPIA_DECORATED_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLayout>
#include <QLabel>

namespace Fizjoterapia {

class Decorated : public QDialog {
	Q_OBJECT

protected:
	QLabel *title;
	QLabel *subtitle;
	QVBoxLayout *header;
	QStackedWidget *content;
	QHBoxLayout *controls;
	QVBoxLayout *main;

	QLayout *current_content;

public:
	Decorated(QWidget *parent, const QString &title=QString::null);

	void setTitle(const QString &title);

	void setContent(QWidget *layout);
	void addControl(QWidget* control);

};

}

#endif 
