#ifndef SYSTEM63SETTINGS_H
#define SYSTEM63SETTINGS_H

#include "../common/systemsettings.h"

class System63Settings
{
	public:
		enum eProgressionType {
			ProgressionTypeAuto,
			ProgressionTypeManual
		}; // eProgressionType

		System63Settings();

		const int GetProgressionAutoValue() const;
		const bool GetProgressionDozenColumnNotChanged() const;
		const QString GetProgressionManualSequence() const;
		const eProgressionType GetProgressionType() const;
		const int GetSameDozenColumnBeforeBet() const;
		const int GetSameDozenColumnProgression() const;
		const void SetProgressionAutoValue(const int &pValue);
		const void SetProgressionDozenColumnNotChanged(const bool &pValue);
		const void SetProgressionManualSequence(const QString &pSequence);
		const void SetProgressionType(const eProgressionType &pType);
		const void SetSameDozenColumnBeforeBet(const int &pCount);
		const void SetSameDozenColumnProgression(const int &pCount);

	private:
		SystemSettings _ssSettings;
}; // System63Settings

#endif // SYSTEM63SETTINGS_H