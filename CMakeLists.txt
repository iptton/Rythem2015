cmake_minimum_required(VERSION 3.8)

project(Rythem2015 VERSION 2015.09)


# Include Qt basic functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(QtCommon)


# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

set(COMPANY "iptton")
set(COPYRIGHT "Copyright (c) 2015 iptton. All rights reserved.")
set(IDENTIFIER "cn.pan2017.Rythem")

add_project_meta(META_FILES_TO_INCLUDE)
set(CMAKE_INCLUDE_CURRENT_DIR  ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/res/rule.js ${CMAKE_CURRENT_SOURCE_DIR}/res/common.js  ${CMAKE_CURRENT_SOURCE_DIR}/res/index.html ${CMAKE_CURRENT_SOURCE_DIR}/res/index.js )

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#查找Qt的库
find_package(Qt5 REQUIRED Core Widgets UiTools Network WebEngineWidgets)

set(SOURCE_FILES main.cpp Core/ProxyServer.cpp Core/ProxyServer.h Rythem.cpp Rythem.h Core/Pipe.cpp Core/Pipe.h Core/PipeData.cpp Core/PipeData.h Core/RuleManager.cpp Core/RuleManager.h  GUI/RythemWindow.cpp GUI/RythemWindow.h Core/PACParser.cpp Core/PACParser.h Core/PACExtObject.cpp Core/PACExtObject.h Core/Rule.cpp Core/Rule.h Core/RuleParserJSExt.cpp Core/RuleParserJSExt.h)


add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
        ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
        )
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Network Qt5::WebEngineWidgets)

SET_SOURCE_FILES_PROPERTIES(${RESOURCE_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

# copy config page files to destination
if(APPLE)
    file(COPY ${CMAKE_SOURCE_DIR}/res/rule/ DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.app/Contents/Resources/rule)
    message("copy file to .app/Contents/Resources")
elseif(WIN32)
    file(COPY ${CMAKE_SOURCE_DIR}/res/rule/ DESTINATION {CMAKE_BINARY_DIR}/rule)
endif()