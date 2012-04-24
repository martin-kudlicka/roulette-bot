#ifndef PLAYCMN_H
#define PLAYCMN_H

#include <QtCore/QHash>

class PlayCmn
{
	public:
		enum eBetPosition {
			BetPositionNone,
			BetPosition0,
			BetPositionColorBlack,
			BetPositionColorRed,
			BetPositionColumn1,
			BetPositionColumn2,
			BetPositionColumn3,
			BetPositionDozen1,
			BetPositionDozen2,
			BetPositionDozen3
		}; // eBetPosition
		enum eSpinResultType {
			SpinResultTypeNone,
			SpinResultTypeNoBet,
			SpinResultTypeWon,
			SpinResultTypeLost = 4,
			SpinResultTypeProgression = 8
		}; // eSpinResultType
		Q_DECLARE_FLAGS(qfSpinResultTypes, eSpinResultType)

		struct sSpinResult {
			qfSpinResultTypes esrtType;
			quint8 qui8BetProfit;
		}; // sSpinResult

		typedef QHash<eBetPosition, quint8> tBetHash;
}; // PlayCmn

Q_DECLARE_OPERATORS_FOR_FLAGS(PlayCmn::qfSpinResultTypes)

#endif // PLAYCMN_H