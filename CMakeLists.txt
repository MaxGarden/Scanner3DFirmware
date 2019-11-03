CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Scanner3DFirmware)

SET(CMAKE_CXX_STANDARD 17)

SET(SCANNER_3D_FIRMWARE_SOURCES
    Source/pch.h
    Source/pch.cpp
    
    Source/Scanner3DFirmware/main.cpp
    
    Source/Scanner3DFirmware/Services/ServerServicesBuilder.h
    Source/Scanner3DFirmware/Services/ServerServicesBuilder.cpp  
    
    Source/Scanner3DFirmware/Services/Echo/EchoService.h
    Source/Scanner3DFirmware/Services/Echo/EchoService.cpp
)

ADD_SUBDIRECTORY(Dependencies/RemoteServices)

ADD_EXECUTABLE(Scanner3DFirmware ${SCANNER_3D_FIRMWARE_SOURCES})

ADD_DEPENDENCIES(Scanner3DFirmware RemoteServices)

TARGET_INCLUDE_DIRECTORIES(Scanner3DFirmware PRIVATE Source Dependencies/RemoteServices/Include Dependencies/RemoteServices/Dependencies/Networking/Include)
TARGET_LINK_LIBRARIES(Scanner3DFirmware RemoteServices)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)