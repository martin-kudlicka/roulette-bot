#include "martingalestatisticswidget.h"

const void MartingaleStatisticsWidget::Increment(QLabel *pLabel) const
{
	pLabel->setText(QString::number(pLabel->text().toUInt() + 1));
} // Increment

const void MartingaleStatisticsWidget::Increment(const eCounter &pCounter) const
{
	switch (pCounter) {
	case Counter1SameInRow:
		Increment(_qwmswWidget.ql1SameColorInRow);
		break;
	case Counter2SameInRow:
		Increment(_qwmswWidget.ql2SameColorInRow);
		break;
	case Counter3SameInRow:
		Increment(_qwmswWidget.ql3SameColorInRow);
		break;
	case Counter4SameInRow:
		Increment(_qwmswWidget.ql4SameColorInRow);
		break;
	case Counter5SameInRow:
		Increment(_qwmswWidget.ql5SameColorInRow);
		break;
	case Counter6SameInRow:
		Increment(_qwmswWidget.ql6SameColorInRow);
		break;
	case Counter7SameInRow:
		Increment(_qwmswWidget.ql7SameColorInRow);
		break;
	case Counter8SameInRow:
		Increment(_qwmswWidget.ql8SameColorInRow);
		break;
	case Counter9SameInRow:
		Increment(_qwmswWidget.ql9SameColorInRow);
		break;
	case Counter10SameInRow:
		Increment(_qwmswWidget.ql10SameColorInRow);
	} // switch
} // Increment

const void MartingaleStatisticsWidget::Reset() const
{
	_qwmswWidget.ql1SameColorInRow->setText("0");
	_qwmswWidget.ql2SameColorInRow->setText("0");
	_qwmswWidget.ql3SameColorInRow->setText("0");
	_qwmswWidget.ql4SameColorInRow->setText("0");
	_qwmswWidget.ql5SameColorInRow->setText("0");
	_qwmswWidget.ql6SameColorInRow->setText("0");
	_qwmswWidget.ql7SameColorInRow->setText("0");
	_qwmswWidget.ql8SameColorInRow->setText("0");
	_qwmswWidget.ql9SameColorInRow->setText("0");
	_qwmswWidget.ql10SameColorInRow->setText("0");
	_qwmswWidget.qlMaxSameColorInRow->setText("0");
} // Reset

const void MartingaleStatisticsWidget::SetMaxSameInRow(const quint8 &pValue) const
{
	_qwmswWidget.qlMaxSameColorInRow->setText(QString::number(pValue));
} // SetMaxSameInRow

MartingaleStatisticsWidget::MartingaleStatisticsWidget(QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QWidget(pParent, pFlags)
{
	_qwmswWidget.setupUi(this);
} // MartingaleStatisticsWidget