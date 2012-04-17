#ifndef MARTINGALESTATISTICSWIDGET_H
#define MARTINGALESTATISTICSWIDGET_H

#include "ui_martingalestatisticswidget.h"

class MartingaleStatisticsWidget : public QWidget
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
			Counter8SameInRow,
			Counter9SameInRow,
			Counter10SameInRow,
			CounterMoreSameInRow
		}; // eCounter

		MartingaleStatisticsWidget(QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

		const void Increment(const eCounter &pCounter) const;
		const void SetMaxSameInRow(const int &pValue) const;

	private:
		Ui::qwMartingaleStatisticsWidget _qwmswWidget;

		const void Increment(QLabel *pLabel) const;
}; // MartingaleStatisticsWidget

#endif // MARTINGALESTATISTICSWIDGET_H