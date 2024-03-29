CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Scanner3DFirmware)

SET(CMAKE_CXX_STANDARD 17)

IF(NOT WIN32)
    FIND_PACKAGE(raspicam REQUIRED)
ENDIF()

SET(SCANNER_3D_FIRMWARE_SOURCES
    Source/pch.h
    Source/pch.cpp
    
    Source/Scanner3DFirmware/main.cpp
    Source/Scanner3DFirmware/Scanner3DFirmware.h
    
    Source/Scanner3DFirmware/Services/ServerServicesBuilder.h
    Source/Scanner3DFirmware/Services/ServerServicesBuilder.cpp  
    
    Source/Scanner3DFirmware/Camera/Camera.h
    Source/Scanner3DFirmware/Camera/Camera.cpp
    
    Source/Scanner3DFirmware/Scanner/Scanner.h
    Source/Scanner3DFirmware/Scanner/Scanner.cpp
    
    Source/Scanner3DFirmware/Config/Config.h
    Source/Scanner3DFirmware/Config/Config.cpp
    
    Source/Scanner3DFirmware/Tray/Tray.h
    Source/Scanner3DFirmware/Tray/Tray.cpp
    
    Source/Scanner3DFirmware/Services/Camera/CameraService.h
    Source/Scanner3DFirmware/Services/Camera/CameraService.cpp
    
    Source/Scanner3DFirmware/Services/Config/ConfigService.h
    Source/Scanner3DFirmware/Services/Config/ConfigService.cpp
    
    Source/Scanner3DFirmware/Services/Scanner/ScannerService.h
    Source/Scanner3DFirmware/Services/Scanner/ScannerService.cpp
    
    Source/Scanner3DFirmware/Services/Tray/TrayService.h
    Source/Scanner3DFirmware/Services/Tray/TrayService.cpp
)

ADD_SUBDIRECTORY(Dependencies/RemoteServices)

ADD_EXECUTABLE(Scanner3DFirmware ${SCANNER_3D_FIRMWARE_SOURCES})

ADD_DEPENDENCIES(Scanner3DFirmware RemoteServices)

TARGET_INCLUDE_DIRECTORIES(Scanner3DFirmware PRIVATE Source Source/Scanner3DFirmware Dependencies/RemoteServices/Include Dependencies/RemoteServices/Dependencies/Networking/Include)

IF(WIN32)
    TARGET_LINK_LIBRARIES(Scanner3DFirmware RemoteServices)
ELSE()
    TARGET_LINK_LIBRARIES(Scanner3DFirmware RemoteServices raspicam wiringPi)
ENDIF()

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
