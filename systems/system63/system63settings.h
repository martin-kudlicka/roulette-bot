#ifndef SYSTEM63SETTINGS_H
#define SYSTEM63SETTINGS_H

#include "../common/systemsettings.h"

class System63Settings
{
	public:
		enum eBetOn {
			BetOnDozenColumn,
			BetOnRandom
		}; // eBetOn
		enum eDozenColumnType {
			DozenColumnTypeDozen = 1,
			DozenColumnTypeColumn,
			DozenColumnTypeBoth
		}; // eDozenColumnType
		enum eProgressionType {
			ProgressionTypeAuto,
			ProgressionTypeManual
		}; // eProgressionType

		System63Settings();

		const eBetOn GetBetOn() const;
		const bool GetColumn3x() const;
		const bool GetDozen3x() const;
		const eDozenColumnType GetDozenColumnType() const;
		const quint8 GetProgressionAutoValue() const;
		const bool GetProgressionDozenColumnNotChanged() const;
		const QString GetProgressionManualSequence() const;
		const eProgressionType GetProgressionType() const;
		const quint8 GetSameDozenColumnBeforeBet() const;
		const quint8 GetSameDozenColumnProgression() const;
		const void SetBetOn(const eBetOn &pBetOn);
		const void SetColumn3x(const bool &pEnabled);
		const void SetDozen3x(const bool &pEnabled);
		const void SetDozenColumnType(const eDozenColumnType &pType);
		const void SetProgressionAutoValue(const quint8 &pValue);
		const void SetProgressionDozenColumnNotChanged(const bool &pValue);
		const void SetProgressionManualSequence(const QString &pSequence);
		const void SetProgressionType(const eProgressionType &pType);
		const void SetSameDozenColumnBeforeBet(const quint8 &pCount);
		const void SetSameDozenColumnProgression(const quint8 &pCount);

	private:
		SystemSettings _ssSettings;
}; // System63Settings

#endif // SYSTEM63SETTINGS_H