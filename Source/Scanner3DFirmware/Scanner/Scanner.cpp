#include "pch.h"
#include "Scanner.h"

using namespace Scanner3DFirmware;

static Scanner::Config s_config;

void Scanner::ApplyConfig(Config&& config)
{
    if (config.TresholdMax <= 0)
        config.TresholdMax = 1;

    if (config.TresholdMin > config.TresholdMax)
        config.TresholdMin = config.TresholdMax - 1;

    if (sin(config.CameraLaserAngleInRad) == 0.0f)
        config.CameraLaserAngleInRad = 3.14f / 2.0f;

    s_config = std::move(config);
}

const Scanner::Config& Scanner::GetConfig()
{
    return s_config;
}

void Scanner::PerformBinarization(Data& data)
{
    for (auto& current : data)
        current = current >= s_config.TresholdMin && current <= s_config.TresholdMax;
}

Scanner::PointsData Scanner::CalculateAveragePoints(const Data& binarizedData, unsigned short rowWidth)
{
    FIRMWARE_ASSERT(binarizedData.size() % rowWidth == 0);

    const auto rowsCount = binarizedData.size() / rowWidth;

    PointsData result;
    result.reserve(rowsCount);

    for (unsigned short rowNumber = 0; rowNumber < rowsCount; ++rowNumber)
    {
        const auto beginOfRow = rowNumber * rowWidth;
        const auto endOfRow = beginOfRow + rowWidth;

        auto value = 0u;
        auto count = 0u;

        for (auto i = beginOfRow; i < endOfRow; ++i)
        {
            if(binarizedData[i] == 0)
                continue;

            value += i - beginOfRow;
            ++count;
        }

        if(count == 0)
            continue;

        result.emplace_back(Point{ static_cast<unsigned short>(value / count), rowNumber });
    }

    return result;
}

Scanner::Points3DData Scanner::Calculate3DPoints(const PointsData& pointsData)
{
    Points3DData result;
    result.reserve(pointsData.size());

    for (const auto& point : pointsData)
    {
        const auto radius = (point.X - s_config.Origin.X) / sin(s_config.CameraLaserAngleInRad);
        const auto height = (point.Y - s_config.Origin.Y) * cos(s_config.AxisCameraAngleInRad);

        result.emplace_back(Point3D{ static_cast<float>(radius), static_cast<float>(height) });
    }

    return result;
}