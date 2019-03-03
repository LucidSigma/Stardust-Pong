#pragma once
#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <tinyxml2.h>

#include <map>
#include <string>

#include "Config.h"

class ConfigReader
{
private:
	using ParserFunction = bool (ConfigReader::*)(Config&, tinyxml2::XMLElement*) noexcept;

	inline static const std::string s_configFilePath = "config.xml";
	inline static const std::string s_rootNodeName = "config";

	static const std::map<std::string, ParserFunction> s_configMappings;

	tinyxml2::XMLDocument m_configFile;

public:
	ConfigReader();

	Config ReadConfigFile();

private:
	bool CheckXMLResult(tinyxml2::XMLError result) noexcept;

	bool ParseTitle(Config& config, tinyxml2::XMLElement* configElement) noexcept;
	bool ParseWindowWidth(Config& config, tinyxml2::XMLElement* configElement) noexcept;
	bool ParseWindowHeight(Config& config, tinyxml2::XMLElement* configElement) noexcept;
	bool ParseFrameRate(Config& config, tinyxml2::XMLElement* configElement) noexcept;
	bool ParseEnableVsync(Config& config, tinyxml2::XMLElement* configElement) noexcept;
};

#endif