#include "system63statisticswidget.h"

const void System63StatisticsWidget::Increment(QLabel *pLabel) const
{
	pLabel->setText(QString::number(pLabel->text().toUInt() + 1));
} // Increment

const void System63StatisticsWidget::Increment(const eCounter &pCounter) const
{
	switch (pCounter) {
		case Counter1SameInRow:
			Increment(_qws63swWidget.ql1SameDozenColumnInRow);
			break;
		case Counter2SameInRow:
			Increment(_qws63swWidget.ql2SameDozenColumnInRow);
			break;
		case Counter3SameInRow:
			Increment(_qws63swWidget.ql3SameDozenColumnInRow);
			break;
		case Counter4SameInRow:
			Increment(_qws63swWidget.ql4SameDozenColumnInRow);
			break;
		case Counter5SameInRow:
			Increment(_qws63swWidget.ql5SameDozenColumnInRow);
			break;
		case Counter6SameInRow:
			Increment(_qws63swWidget.ql6SameDozenColumnInRow);
			break;
		case Counter7SameInRow:
			Increment(_qws63swWidget.ql7SameDozenColumnInRow);
	} // switch
} // Increment

const void System63StatisticsWidget::Reset() const
{
	_qws63swWidget.ql1SameDozenColumnInRow->setText("0");
	_qws63swWidget.ql2SameDozenColumnInRow->setText("0");
	_qws63swWidget.ql3SameDozenColumnInRow->setText("0");
	_qws63swWidget.ql4SameDozenColumnInRow->setText("0");
	_qws63swWidget.ql5SameDozenColumnInRow->setText("0");
	_qws63swWidget.ql6SameDozenColumnInRow->setText("0");
	_qws63swWidget.ql7SameDozenColumnInRow->setText("0");
	_qws63swWidget.qlMaxSameDozenColumnInRow->setText("0");
} // Reset

const void System63StatisticsWidget::SetMaxSameInRow(const quint8 &pValue) const
{
	_qws63swWidget.qlMaxSameDozenColumnInRow->setText(QString::number(pValue));
} // SetMaxSameInRow

System63StatisticsWidget::System63StatisticsWidget(QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QWidget(pParent, pFlags)
{
	_qws63swWidget.setupUi(this);
} // System63StatisticsWidget