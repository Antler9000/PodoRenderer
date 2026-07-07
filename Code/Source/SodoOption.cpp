#include <algorithm>
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

	fout << "FullScreen"		<< " " << (m_optionFullScreen.userEnabled	? "Yes" : "No") << '\n';
	fout << "HDR"				<< " " << (m_optionHDR.userEnabled			? "Yes" : "No") << '\n';
	fout << "Tearing"			<< " " << (m_optionTearing.userEnabled		? "Yes" : "No") << '\n';
	fout << "RayTracing"		<< " " << (m_optionRayTracing.userEnabled	? "Yes" : "No") << '\n';
	fout << "MeshShader"		<< " " << (m_optionMeshShader.userEnabled	? "Yes" : "No") << '\n';
	fout << "GUIMasterSize"		<< " " << m_optionGUI.masterSize		<< '\n';
	fout << "SoundMasterVolume" << " " << m_optionSound.masterVolume	<< '\n';
	fout << "SoundUIVolume"		<< " " << m_optionSound.uiVolume		<< '\n';
	fout << "SoundUnitVolume"	<< " " << m_optionSound.unitVolume		<< '\n';
	fout << "SoundEffectVolume"	<< " " << m_optionSound.effectVolume	<< '\n';
	fout << "SoundMusicVolume"	<< " " << m_optionSound.musicVolume		<< '\n';

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

	bool fullScreenEnabledTemp	= false;
	bool hdrEnabledTemp			= false;
	bool tearingEnabledTemp		= false;
	bool rayTracingEnabledTemp	= false;
	bool meshShaderEnabledTemp	= false;
	int guiMasterSizeTemp		= 0;
	int soundMasterVolumeTemp	= 0;
	int soundUIVolumeTemp		= 0;
	int soundUnitVolumeTemp		= 0;
	int soundEffectVolumeTemp	= 0;
	int soundMusicVolumeTemp	= 0;

	result &= OptionReadBool(fin, "FullScreen", fullScreenEnabledTemp);
	result &= OptionReadBool(fin, "HDR", hdrEnabledTemp);
	result &= OptionReadBool(fin, "Tearing", tearingEnabledTemp);
	result &= OptionReadBool(fin, "RayTracing", rayTracingEnabledTemp);
	result &= OptionReadBool(fin, "MeshShader", meshShaderEnabledTemp);
	result &= OptionReadInt(fin, "GUIMasterSize", guiMasterSizeTemp);
	result &= OptionReadInt(fin, "SoundMasterVolume", soundMasterVolumeTemp);
	result &= OptionReadInt(fin, "SoundUIVolume", soundUIVolumeTemp);
	result &= OptionReadInt(fin, "SoundUnitVolume", soundUnitVolumeTemp);
	result &= OptionReadInt(fin, "SoundEffectVolume", soundEffectVolumeTemp);
	result &= OptionReadInt(fin, "SoundMusicVolume", soundMusicVolumeTemp);

	if (result == false)
	{
		return;
	}

	m_optionFullScreen.userEnabled	= fullScreenEnabledTemp;
	m_optionHDR.userEnabled			= hdrEnabledTemp;
	m_optionTearing.userEnabled		= tearingEnabledTemp;
	m_optionRayTracing.userEnabled	= rayTracingEnabledTemp;
	m_optionMeshShader.userEnabled	= meshShaderEnabledTemp;
	m_optionGUI.masterSize			= std::clamp(guiMasterSizeTemp, 50, 150);
	m_optionSound.masterVolume		= std::clamp(soundMasterVolumeTemp, 0, 100);
	m_optionSound.uiVolume			= std::clamp(soundUIVolumeTemp, 0, 100);
	m_optionSound.unitVolume		= std::clamp(soundUnitVolumeTemp, 0, 100);
	m_optionSound.effectVolume		= std::clamp(soundEffectVolumeTemp, 0, 100);
	m_optionSound.musicVolume		= std::clamp(soundMusicVolumeTemp, 0, 100);
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