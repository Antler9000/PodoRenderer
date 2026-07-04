#include <string>
#include <cstdio>
#include <fstream>
#include "Sodo.h"

void Sodo::OptionSave()
{
	std::ofstream fout("SavedSettingsTemp.txt", std::ios::out | std::ios::trunc);

	if (!fout)
	{
		return;
	}

	fout << "FullScreen" << " " << (m_optionFullScreen.userEnabled ? "Yes" : "No") << '\n';
	fout << "HDR" << " " << (m_optionHDR.userEnabled ? "Yes" : "No") << '\n';
	fout << "Tearing" << " " << (m_optionTearing.userEnabled ? "Yes" : "No") << '\n';
	fout << "RayTracing" << " " << (m_optionRayTracing.userEnabled ? "Yes" : "No") << '\n';
	fout << "MeshShader" << " " << (m_optionMeshShader.userEnabled ? "Yes" : "No") << '\n';
	fout << "SoundMasterVolume" << " " << m_optionSound.masterVolume << '\n';
	fout << "SoundUIVolume" << " " << m_optionSound.uiVolume << '\n';
	fout << "SoundUnitVolume" << " " << m_optionSound.unitVolume << '\n';
	fout << "SoundEffectVolume" << " " << m_optionSound.effectVolume << '\n';
	fout << "SoundMusicVolume" << " " << m_optionSound.musicVolume << '\n';

	fout.close();

	int removeResult = std::remove("SavedSettings.txt");
	if (removeResult != 0)
	{
		return;
	}

	int renameResult = std::rename("SavedSettingsTemp.txt", "SavedSettings.txt");
	if (renameResult != 0)
	{
		return;
	}
}

void Sodo::OptionRestore()
{
	std::ifstream fin("SavedSettings.txt", std::ios::in);

	if (!fin)
	{
		return;
	}

	bool result = true;

	bool fullScreenEnabledTemp = false;
	bool hdrEnabledTemp = false;
	bool tearingEnabledTemp = false;
	bool rayTracingEnabledTemp = false;
	bool meshShaderEnabledTemp = false;
	int soundMasterVolumeTemp = 0;
	int soundUIVolumeTemp = 0;
	int soundUnitVolumeTemp = 0;
	int soundEffectVolumeTemp = 0;
	int soundMusicVolumeTemp = 0;

	result &= OptionReadBool(fin, "FullScreen", fullScreenEnabledTemp);
	result &= OptionReadBool(fin, "HDR", hdrEnabledTemp);
	result &= OptionReadBool(fin, "Tearing", tearingEnabledTemp);
	result &= OptionReadBool(fin, "RayTracing", rayTracingEnabledTemp);
	result &= OptionReadBool(fin, "MeshShader", meshShaderEnabledTemp);
	result &= OptionReadInt(fin, "SoundMasterVolume", soundMasterVolumeTemp);
	result &= OptionReadInt(fin, "SoundUIVolume", soundUIVolumeTemp);
	result &= OptionReadInt(fin, "SoundUnitVolume", soundUnitVolumeTemp);
	result &= OptionReadInt(fin, "SoundEffectVolume", soundEffectVolumeTemp);
	result &= OptionReadInt(fin, "SoundMusicVolume", soundMusicVolumeTemp);

	if (result == false)
	{
		return;
	}

	m_optionFullScreen.userEnabled = fullScreenEnabledTemp;
	m_optionHDR.userEnabled = hdrEnabledTemp;
	m_optionTearing.userEnabled = tearingEnabledTemp;
	m_optionRayTracing.userEnabled = rayTracingEnabledTemp;
	m_optionMeshShader.userEnabled = meshShaderEnabledTemp;
	m_optionSound.masterVolume = soundMasterVolumeTemp;
	m_optionSound.uiVolume = soundUIVolumeTemp;
	m_optionSound.unitVolume = soundUnitVolumeTemp;
	m_optionSound.effectVolume = soundEffectVolumeTemp;
	m_optionSound.musicVolume = soundMusicVolumeTemp;
}

bool Sodo::OptionReadBool(std::ifstream& fin, std::string optionName, bool& outOptionEnabled)
{
	std::string buffer;

	fin >> buffer;
	if (buffer != optionName)
	{
		return false;
	}

	fin >> buffer;
	if (buffer == "Yes")
	{
		outOptionEnabled = true;
	}
	else if (buffer == "No")
	{
		outOptionEnabled = false;
	}
	else
	{
		return false;
	}

	return true;
}

bool Sodo::OptionReadInt(std::ifstream& fin, std::string optionName, int& outOptionValue)
{
	std::string buffer;

	fin >> buffer;
	if (buffer != optionName)
	{
		return false;
	}
	fin >> outOptionValue;

	return true;
}