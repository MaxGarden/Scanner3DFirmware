CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Scanner3DFirmware)

SET(CMAKE_CXX_STANDARD 17)

IF(UNIX)
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
    
    Source/Scanner3DFirmware/Services/Camera/CameraService.h
    Source/Scanner3DFirmware/Services/Camera/CameraService.cpp
    
    Source/Scanner3DFirmware/Services/Config/ConfigService.h
    Source/Scanner3DFirmware/Services/Config/ConfigService.cpp
)

ADD_SUBDIRECTORY(Dependencies/RemoteServices)

ADD_EXECUTABLE(Scanner3DFirmware ${SCANNER_3D_FIRMWARE_SOURCES})

ADD_DEPENDENCIES(Scanner3DFirmware RemoteServices)

TARGET_INCLUDE_DIRECTORIES(Scanner3DFirmware PRIVATE Source Source/Scanner3DFirmware Dependencies/RemoteServices/Include Dependencies/RemoteServices/Dependencies/Networking/Include)

IF(UNIX)
    TARGET_LINK_LIBRARIES(Scanner3DFirmware RemoteServices raspicam)
ELSE()
    TARGET_LINK_LIBRARIES(Scanner3DFirmware RemoteServices)
ENDIF()

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
