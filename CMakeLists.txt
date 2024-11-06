cmake_minimum_required(VERSION 3.16)

project(NaxiStudio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Multimedia Core)

set(TS_FILES ./lang/NaxiStudio_pt_BR.ts)

set(PROJECT_SOURCES
        main.cpp
        ./UI/player.cpp
        ./UI/player.h
        ./UI/player.ui
        ${TS_FILES}
)

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/UI/resources/icons/NaxiStudio.rc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NaxiStudio
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${app_icon_resource_windows}
        UI/resources/player.qrc
        UI/widgets/playerwidget.h UI/widgets/playerwidget.cpp UI/widgets/playerwidget.ui
        backend/audio/audioplayer.h backend/audio/audioplayer.cpp
        UI/widgets/folderswidget.h UI/widgets/folderswidget.cpp
        backend/files/folderslist.h backend/files/folderslist.cpp
        backend/files/fileslist.h backend/files/fileslist.cpp
        UI/widgets/fileslistwidget.h UI/widgets/fileslistwidget.cpp
        UI/widgets/filewidget.h UI/widgets/filewidget.cpp

    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

else()
    add_executable(NaxiStudio
        ${PROJECT_SOURCES}
    )
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


target_link_libraries(NaxiStudio PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(NaxiStudio PRIVATE Qt6::Multimedia Qt6::Core)


if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER br.dev.NaxiStudio.Player)
endif()


set_target_properties(NaxiStudio PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


include(GNUInstallDirs)
install(TARGETS NaxiStudio
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NaxiStudio)
endif()
