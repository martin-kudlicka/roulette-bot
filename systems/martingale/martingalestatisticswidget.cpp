#include "martingalestatisticswidget.h"

const void MartingaleStatisticsWidget::Increment(QLabel *pLabel) const
{
	pLabel->setText(QString::number(pLabel->text().toInt() + 1));
} // Increment

const void MartingaleStatisticsWidget::Increment(const eColorCounter &pCounter) const
{
	switch (pCounter) {
		case BlackCount:
			Increment(_qwmswWidget.qlBlackCount);
			break;
		case RedCount:
			Increment(_qwmswWidget.qlRedCount);
	} // switch
} // Increment

const void MartingaleStatisticsWidget::SetMaxSameInRow(QLabel *pLabel, const int &pValue) const
{
	pLabel->setText(QString::number(pValue));
} // SetMaxSameInRow

const void MartingaleStatisticsWidget::SetMaxSameInRow(const eMaxCounter &pCounter, const int &pValue) const
{
	switch (pCounter) {
		case MaxBlackInRow:
			SetMaxSameInRow(_qwmswWidget.qlMaxBlackInRow, pValue);
			break;
		case MaxRedInRow:
			SetMaxSameInRow(_qwmswWidget.qlMaxRedInRow, pValue);
	} // switch
} // SetMaxSameInRow

MartingaleStatisticsWidget::MartingaleStatisticsWidget(QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QWidget(pParent, pFlags)
{
	_qwmswWidget.setupUi(this);
} // MartingaleStatisticsWidget