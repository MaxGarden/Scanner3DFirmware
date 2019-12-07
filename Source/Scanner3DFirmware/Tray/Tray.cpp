#include "pch.h"
#include "Tray.h"

#if !defined(WIN32)
#include <wiringPi.h>
#include <chrono>
#endif

using namespace Scanner3DFirmware;

static Tray::Config s_config;
static const auto s_motorStepAngleInDegrees = 0.05625f;

void Tray::ApplyConfig(Config&& config)
{
    config.MotorStepAngleInDegrees = s_motorStepAngleInDegrees;
    s_config = std::move(config);
}

Tray::Config Tray::GetConfig()
{
    return s_config;
}

#if !defined(WIN32)

static const auto s_enablePin = 12;
static const auto s_directionPin = 13;
static const auto s_stepPin = 19;
static auto s_lastStepTimePoint = std::chrono::steady_clock::now();

bool Tray::Initialize()
{
    if(wiringPiSetupGpio() < 0)
        return false;
        
    pinMode(s_enablePin, OUTPUT);
    pinMode(s_directionPin, OUTPUT);
    pinMode(s_stepPin, OUTPUT);
    
    return true;
}

void Tray::Finalize()
{
}

void Tray::Update()
{
    const auto nowTimePoint = std::chrono::steady_clock::now();
    const auto resetTimeStep = std::min(200, 2 * GetConfig().MotorStepDelayInMiliseconds);

    if(std::chrono::duration_cast<std::chrono::milliseconds>(nowTimePoint - s_lastStepTimePoint) > resetTimeStep)
        digitalWrite(s_enablePin, 1);
}

bool Step(bool forward)
{
    digitalWrite(s_enablePin, 0);
        
    if(forward) 
        digitalWrite(s_directionPin, 0);
    else
        digitalWrite(s_directionPin, 1);
    
    const auto& config = Tray::GetConfig();
    
    for(auto i = 0; i < config.MotorStepsPerTrayStep; ++i)
    {
        digitalWrite(s_stepPin, 1);
        delay(config.MotorStepDelayInMiliseconds);
        digitalWrite(s_stepPin, 0);
        
        if(i != config.MotorStepsPerTrayStep - 1)
            delay(config.MotorStepDelayInMiliseconds);
    }
    
    s_lastStepTimePoint = std::chrono::steady_clock::now();
    return true;
}

bool Tray::StepForward()
{
    return Step(true);
}

bool Tray::StepBackward()
{
    return Step(false);
}

#else

bool Tray::Initialize()
{
    return true;
}

void Tray::Finalize()
{
}

void Tray::Update()
{
}

bool Tray::StepForward()
{
    return true;
}

bool Tray::StepBackward()
{
    return true;
}

#endif
