#include "pch.h"
#include "Config.h"

#include <fstream>

using namespace Scanner3DFirmware;

static const auto s_configFilePath = "config.con";

static void TryLoadConfig()
{
    std::ifstream file{ s_configFilePath, std::ifstream::in | std::ifstream::binary };

    if (file.good())
    {
        Config::Config config;
        file.read(reinterpret_cast<char*>(&config), sizeof(config));
        ApplyConfig(std::move(config));
    }

    file.close();
}

bool Config::Initialize()
{
    TryLoadConfig();
    return true;
}

static void SaveConfig()
{
    std::ofstream file{ s_configFilePath, std::ifstream::out | std::ofstream::binary };

    FIRMWARE_ASSERT(file.good());
    if (file.good())
    {
        const auto config = Config::GetConfig();
        file.write(reinterpret_cast<const char*>(&config), sizeof(config));
    }

    file.close();
}

void Config::Finalize()
{
    SaveConfig();
}

void Config::ApplyConfig(Config&& config)
{
    Camera::ApplyConfig(config.CameraConfig);
    Scanner::ApplyConfig(std::move(config.ScannerConfig));

    SaveConfig();
}

Config::Config Config::GetConfig()
{
    return { Camera::GetConfig(), Scanner::GetConfig() };
}