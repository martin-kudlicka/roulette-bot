#ifndef MARTINGALESTATISTICSWIDGET_H
#define MARTINGALESTATISTICSWIDGET_H

#include "ui_martingalestatisticswidget.h"

class MartingaleStatisticsWidget : public QWidget
{
	Q_OBJECT

	public:
		enum eColorCounter {
			BlackCount,
			RedCount
		}; // eColorCounter
		enum eMaxCounter {
			MaxBlackInRow,
			MaxRedInRow
		}; // eMaxCounter

		MartingaleStatisticsWidget(QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

		const void Increment(const eColorCounter &pCounter) const;
		const void SetMaxSameInRow(const eMaxCounter &pCounter, const int &pValue) const;

	private:
		Ui::qwMartingaleStatisticsWidget _qwmswWidget;

		const void Increment(QLabel *pLabel) const;
		const void SetMaxSameInRow(QLabel *pLabel, const int &pValue) const;
}; // MartingaleStatisticsWidget

#endif // MARTINGALESTATISTICSWIDGET_H