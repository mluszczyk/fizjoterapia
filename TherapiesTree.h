#ifndef FIZJO_THERAPIESTREE_H
#define FIZJO_THERAPIESTREE_H

#include <QWidget>
#include <QDebug>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QListView>
#include <QTableView>

namespace Fizjoterapia {

class TherapiesTree : public QWidget {
	Q_OBJECT

private:
	int patient;

	QStandardItemModel *model;
	QTreeView *view;	
	QVBoxLayout *layout;
//	QListView *list_view;
//	QTableView *table_view;

public:
	TherapiesTree(int patient, QWidget *parent=0);
	static QString conjugateVisit(int count);

	QSize sizeHint() const;

public slots:
	void refill();

private slots:
	void selectionChanged(const QItemSelection &current,
			const QItemSelection &previous);

signals:
	void changed(int current);
		
};

}

#endif
