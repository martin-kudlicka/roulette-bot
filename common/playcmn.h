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
		enum eSpinResult {
			SpinResultNoBet = 1,
			SpinResultWon = 2,
			SpinResultLost = 4,
			SpinResultProgression = 8
		}; // eSpinResult
		Q_DECLARE_FLAGS(qfSpinResults, eSpinResult)

		typedef QHash<eBetPosition, int> tBetHash;
}; // PlayCmn

Q_DECLARE_OPERATORS_FOR_FLAGS(PlayCmn::qfSpinResults)

#endif // PLAYCMN_H