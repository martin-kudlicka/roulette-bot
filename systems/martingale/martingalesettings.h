#ifndef MARTINGALESETTINGS_H
#define MARTINGALESETTINGS_H

#include "../common/systemsettings.h"

class MartingaleSettings
{
	public:
		enum eBetStyle {
			BetStyleKeepColor,
			BetStyleRandom
		}; // eBetStyle
		enum eProgressionType {
			ProgressionTypeAuto,
			ProgressionTypeManual
		}; // eProgressionType

		MartingaleSettings();

		const eBetStyle GetBetStyle() const;
		const int GetProgressionAutoValue() const;
		const bool GetProgressionColorNotChanged() const;
		const QString GetProgressionManualSequence() const;
		const eProgressionType GetProgressionType() const;
		const int GetSameColorBeforeBet() const;
		const int GetSameColorProgression() const;
		const void SetBetStyle(const eBetStyle &pBetStyle);
		const void SetProgressionAutoValue(const int &pValue);
		const void SetProgressionColorNotChanged(const bool &pValue);
		const void SetProgressionManualSequence(const QString &pSequence);
		const void SetProgressionType(const eProgressionType &pType);
		const void SetSameColorBeforeBet(const int &pCount);
		const void SetSameColorProgression(const int &pCount);

	private:
		SystemSettings _ssSettings;
}; // MartingaleSettings

#endif // MARTINGALESETTINGS_H