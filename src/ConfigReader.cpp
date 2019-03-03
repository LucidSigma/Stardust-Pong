#include "ConfigReader.h"

#include <stdexcept>

const std::map<std::string, ConfigReader::ParserFunction> ConfigReader::s_configMappings
{
	{ "title", &ParseTitle },
	{ "window-width", &ParseWindowWidth },
	{ "window-height", &ParseWindowHeight },
	{ "frame-rate", &ParseFrameRate },
	{ "enable-vsync", &ParseEnableVsync }
};

ConfigReader::ConfigReader()
{
	auto result = m_configFile.LoadFile(s_configFilePath.c_str());

	if (!CheckXMLResult(result))
	{
		throw std::runtime_error("The config XML file is corrupted or missing.");
	}
}

Config ConfigReader::ReadConfigFile()
{
	tinyxml2::XMLNode* configRoot = m_configFile.FirstChildElement(s_rootNodeName.c_str());

	if (configRoot == nullptr)
	{
		throw std::runtime_error("The config XML file is corrupted.");
	}

	Config config;

	for (const auto&[nodeName, parseFunction] : s_configMappings)
	{
		tinyxml2::XMLElement* configElement = configRoot->FirstChildElement(nodeName.c_str());

		if (configElement == nullptr)
		{
			throw std::runtime_error("The config XML file is corrupted.");
		}

		bool parseResult = (this->*parseFunction)(config, configElement);

		if (!parseResult)
		{
			throw std::runtime_error("The config XML file is corrupted.");
		}
	}

	return config;
}

bool ConfigReader::CheckXMLResult(tinyxml2::XMLError result) noexcept
{
	return result == tinyxml2::XML_SUCCESS;
}

bool ConfigReader::ParseTitle(Config& config, tinyxml2::XMLElement* configElement) noexcept
{
	config.title = configElement->GetText();

	return true;
}

bool ConfigReader::ParseWindowWidth(Config& config, tinyxml2::XMLElement* configElement) noexcept
{
	auto result = configElement->QueryUnsignedText(&config.windowWidth);

	return CheckXMLResult(result);
}

bool ConfigReader::ParseWindowHeight(Config& config, tinyxml2::XMLElement* configElement) noexcept
{
	auto result = configElement->QueryUnsignedText(&config.windowHeight);

	return CheckXMLResult(result);
}

bool ConfigReader::ParseFrameRate(Config& config, tinyxml2::XMLElement* configElement) noexcept
{
	auto result = configElement->QueryUnsignedText(&config.frameRate);

	return CheckXMLResult(result);
}

bool ConfigReader::ParseEnableVsync(Config& config, tinyxml2::XMLElement* configElement) noexcept
{
	auto result = configElement->QueryBoolText(&config.enableVsync);

	return CheckXMLResult(result);
}