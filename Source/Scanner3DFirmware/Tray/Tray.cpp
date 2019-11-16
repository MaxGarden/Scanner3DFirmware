#include "pch.h"
#include "Tray.h"

#if !defined(WIN32)
#endif

using namespace Scanner3DFirmware;

static Tray::Config s_config;

void Tray::ApplyConfig(const Config& config)
{
    s_config = config;
}

Tray::Config Tray::GetConfig()
{
    return s_config;
}

#if !defined(WIN32)
#else

bool Tray::Initialize()
{
    return true;
}

void Tray::Finalize()
{
}

void Tray::StepForward()
{
}

void Tray::StepBackward()
{
}

#endif
