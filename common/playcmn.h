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
			BetPositionColumn3
		}; // eBetPosition
		enum eSpinResultType {
			SpinResultTypeNoBet = 1,
			SpinResultTypeWon = 2,
			SpinResultTypeLost = 4,
			SpinResultTypeProgression = 8
		}; // eSpinResultType
		Q_DECLARE_FLAGS(qfSpinResultTypes, eSpinResultType)

		struct sSpinResult {
			qfSpinResultTypes esrtType;
			int iBetProfit;
		}; // sSpinResult

		typedef QHash<eBetPosition, int> tBetHash;
}; // PlayCmn

Q_DECLARE_OPERATORS_FOR_FLAGS(PlayCmn::qfSpinResultTypes)

#endif // PLAYCMN_H