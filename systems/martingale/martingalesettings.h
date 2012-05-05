#ifndef MARTINGALESETTINGS_H
#define MARTINGALESETTINGS_H

#include "../common/systemsettings.h"

class MartingaleSettings
{
	Q_ENUMS(eBetStyle)
	Q_ENUMS(eProgressionType)

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
		const quint8 GetProgressionAutoValue() const;
		const bool GetProgressionColorNotChanged() const;
		const QString GetProgressionManualSequence() const;
		const eProgressionType GetProgressionType() const;
		const quint8 GetSameColorBeforeBet() const;
		const quint8 GetSameColorProgression() const;
		const void SetBetStyle(const eBetStyle &pBetStyle);
		const void SetProgressionAutoValue(const quint8 &pValue);
		const void SetProgressionColorNotChanged(const bool &pValue);
		const void SetProgressionManualSequence(const QString &pSequence);
		const void SetProgressionType(const eProgressionType &pType);
		const void SetSameColorBeforeBet(const quint8 &pCount);
		const void SetSameColorProgression(const quint8 &pCount);

	private:
		SystemSettings _ssSettings;
}; // MartingaleSettings

#endif // MARTINGALESETTINGS_H