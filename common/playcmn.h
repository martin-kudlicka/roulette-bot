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

		typedef QHash<eBetPosition, int> tBetHash;
}; // PlayCmn

#endif // PLAYCMN_H