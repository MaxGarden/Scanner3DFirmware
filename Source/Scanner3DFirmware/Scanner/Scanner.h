#pragma once

namespace Scanner3DFirmware::Scanner
{
    using Data = std::vector<byte>;

    struct Point
    {
        unsigned short X;
        unsigned short Y;
    };
    using PointsData = std::vector<Point>;

    struct Point3D
    {
        float X;
        float Y;
        float Z;
    };
    using Points3DData = std::vector<Point3D>;

    struct Config
    {
        byte TresholdMin;
        byte TresholdMax;

        Point Origin;

        float CameraLaserInclinationInRadians;
        float AxisCameraInclinationInRadians;
    };

    void ApplyConfig(Config&& config);
    const Config& GetConfig();

    void PerformBinarization(Data& data);
    PointsData CalculateAveragePoints(const Data& binarizedData, unsigned short rowWidth);
    Points3DData Calculate3DPoints(const PointsData& pointsData, float trayAngle);

}