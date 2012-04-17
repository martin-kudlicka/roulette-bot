#ifndef SYSTEM63STATISTICSWIDGET_H
#define SYSTEM63STATISTICSWIDGET_H

#include "ui_system63statisticswidget.h"

class System63StatisticsWidget : public QWidget
{
	Q_OBJECT

	public:
		enum eCounter {
			Counter1SameInRow = 1,
			Counter2SameInRow,
			Counter3SameInRow,
			Counter4SameInRow,
			Counter5SameInRow,
			Counter6SameInRow,
			Counter7SameInRow,
			CounterMoreSameInRow
		}; // eCounter

		System63StatisticsWidget(QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

		const void Increment(const eCounter &pCounter) const;
		const void Reset() const;
		const void SetMaxSameInRow(const int &pValue) const;

	private:
		Ui::qwSystem63StatisticsWidget _qws63swWidget;

		const void Increment(QLabel *pLabel) const;
}; // System63StatisticsWidget

#endif // SYSTEM63STATISTICSWIDGET_H