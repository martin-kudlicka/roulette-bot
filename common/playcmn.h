#ifndef PLAYCMN_H
#define PLAYCMN_H

#include <QtCore/QHash>

class PlayCmn
{
	Q_ENUMS(eBetPosition)
	Q_ENUMS(eSpinResultType)

	public:
		enum eBetPosition {
			BetPositionNone,
			BetPosition0,
			BetPositionNumbers		= BetPosition0,
			BetPositionColorBlack,
			BetPositionColorRed		= 4,
			BetPositionColumn1		= 8,
			BetPositionColumn2		= 16,
			BetPositionColumn3		= 32,
			BetPositionDozen1			= 64,
			BetPositionDozen2			= 128,
			BetPositionDozen3			= 256
		}; // eBetPosition
		Q_DECLARE_FLAGS(qfBetPositions, eBetPosition)
		enum eSpinResultType {
			SpinResultTypeNone,
			SpinResultTypeNoBet,
			SpinResultTypeWon,
			SpinResultTypeLost			= 4,
			SpinResultTypeProgression	= 8
		}; // eSpinResultType
		Q_DECLARE_FLAGS(qfSpinResultTypes, eSpinResultType)

		struct sSpinResult {
			qfSpinResultTypes esrtType;
			quint8 qui8BetProfit;
		}; // sSpinResult

		typedef QHash<eBetPosition, quint8> tBetHash;
}; // PlayCmn

Q_DECLARE_OPERATORS_FOR_FLAGS(PlayCmn::qfBetPositions)
Q_DECLARE_OPERATORS_FOR_FLAGS(PlayCmn::qfSpinResultTypes)

#endif // PLAYCMN_H