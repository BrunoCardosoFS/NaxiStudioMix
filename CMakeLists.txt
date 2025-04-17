cmake_minimum_required(VERSION 3.16)

project(NaxiStudioMix VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Multimedia Core)

set(TS_FILES ./lang/NaxiStudioMix_pt_BR.ts)

set(PROJECT_SOURCES
        main.cpp
        ./ui/player.cpp
        ./ui/player.h
        ./ui/player.ui
        ${TS_FILES}
)

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/ui/resources/NaxiStudioMix.rc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NaxiStudioMix
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${app_icon_resource_windows}
        ui/resources/player.qrc
        ui/widgets/player/playerwidget.h ui/widgets/player/playerwidget.cpp ui/widgets/player/playerwidget.ui
        backend/audio/audioplayer.h backend/audio/audioplayer.cpp
        ui/widgets/files/folderswidget.h ui/widgets/files/folderswidget.cpp
        backend/files/folderslist.h backend/files/folderslist.cpp
        backend/files/fileslist.h backend/files/fileslist.cpp
        ui/widgets/files/fileslistwidget.h ui/widgets/files/fileslistwidget.cpp
        ui/widgets/files/filewidget.h ui/widgets/files/filewidget.cpp
        ui/widgets/playlist/hourlist.h ui/widgets/playlist/hourlist.cpp
        ui/widgets/playlist/hourwidget.h ui/widgets/playlist/hourwidget.cpp
        backend/playlist/openplaylist.h backend/playlist/openplaylist.cpp
        ui/widgets/playlist/playlistlist.h ui/widgets/playlist/playlistlist.cpp
        ui/widgets/playlist/playlistitemwidget.h ui/widgets/playlist/playlistitemwidget.cpp

    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

else()
    add_executable(NaxiStudioMix
        ${PROJECT_SOURCES}
    )
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


target_link_libraries(NaxiStudioMix PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(NaxiStudioMix PRIVATE Qt6::Multimedia Qt6::Core)


if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.NaxiStudio.Mix)
endif()


set_target_properties(NaxiStudioMix PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


include(GNUInstallDirs)
install(TARGETS NaxiStudioMix
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NaxiStudioMix)
endif()
