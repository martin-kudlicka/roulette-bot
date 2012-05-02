#include "systeminterface.h"

const bool SystemInterface::BetContains(const PlayCmn::tBetHash &pBet, const PlayCmn::qfBetPositions &pPosition) const
{
	for (PlayCmn::tBetHash::const_iterator ciBet = pBet.constBegin(); ciBet != pBet.constEnd(); ciBet++) {
		if (ciBet.key() & pPosition) {
			return true;
		} // if
	} // for

	return false;
} // BetContains

const quint8 SystemInterface::BetValue(const PlayCmn::tBetHash &pBet, const PlayCmn::qfBetPositions &pPosition) const
{
	quint8 qui8Value = 0;

	for (PlayCmn::tBetHash::const_iterator ciBet = pBet.constBegin(); ciBet != pBet.constEnd(); ciBet++) {
		if (ciBet.key() & pPosition) {
			qui8Value += ciBet.value();
		} // if
	} // for

	return qui8Value;
} // BetValue

const PlayCmn::qfBetPositions SystemInterface::GetSpinPosition(const quint8 &pSpin) const
{
	PlayCmn::qfBetPositions qfbpPositions;

	if (pSpin == 0) {
		qfbpPositions |= PlayCmn::BetPosition0;
	} else {
		if (pSpin == 2 || pSpin == 4 || pSpin == 6 || pSpin == 8 || pSpin == 10 || pSpin == 11 || pSpin == 13 || pSpin == 15 || pSpin == 17 || pSpin == 20 || pSpin == 22 || pSpin == 24 || pSpin == 26 || pSpin == 28 || pSpin == 29 || pSpin == 31 || pSpin == 33 || pSpin == 35) {
			qfbpPositions |= PlayCmn::BetPositionColorBlack;
		} else {
			qfbpPositions |= PlayCmn::BetPositionColorRed;
		} // if else

		if (pSpin == 1 || pSpin == 4 || pSpin == 7 || pSpin == 10 || pSpin == 13 || pSpin == 16 || pSpin == 19 || pSpin == 22 || pSpin == 25 || pSpin == 28 || pSpin == 31 || pSpin == 34) {
			qfbpPositions |= PlayCmn::BetPositionColumn1;
		} else {
			if (pSpin == 2 || pSpin == 5 || pSpin == 8 || pSpin == 11 || pSpin == 14 || pSpin == 17 || pSpin == 20 || pSpin == 23 || pSpin == 26 || pSpin == 29 || pSpin == 32 || pSpin == 35) {
				qfbpPositions |= PlayCmn::BetPositionColumn2;
			} else {
				qfbpPositions |= PlayCmn::BetPositionColumn3;
			} // if else
		} // if else

		if (pSpin < 13) {
			qfbpPositions |= PlayCmn::BetPositionDozen1;
		} else {
			if (pSpin < 25) {
				qfbpPositions |= PlayCmn::BetPositionDozen2;
			} else {
				qfbpPositions |= PlayCmn::BetPositionDozen3;
			} // if else
		} // if else
	} // if else

	return qfbpPositions;
} // GetSpinPosition

const bool SystemInterface::LastBetContains(const PlayCmn::qfBetPositions &pPosition) const
{
	return BetContains(_tbhLastBet, pPosition);
} // LastBetContains

const quint8 SystemInterface::LastBetValue(const PlayCmn::qfBetPositions &pPosition) const
{
	return BetValue(_tbhLastBet, pPosition);
} // LastBetValue