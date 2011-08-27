#ifndef WIDGET_LIST_H
#define WIDGET_LIST_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QModelIndex>
#include <QSqlQuery>

namespace Fizjoterapia {

class ListWidget : public QWidget {
	Q_OBJECT

protected:
	int selection;

	QStandardItemModel *model;
	QTableView *view;
	QVBoxLayout *layout;

public:
	ListWidget();

	void refill();
	bool isEmpty();

private slots:
	void selectionChanged(const QItemSelection &current, 
			const QItemSelection &previous);

protected:
	virtual QSqlQuery buildQuery() = 0;
	virtual void prepareHeaders() = 0;

signals:
	void changed(int current);

	
};

}

#endif
