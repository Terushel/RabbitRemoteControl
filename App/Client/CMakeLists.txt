# Author: Kang Lin <kl222@126.com>

project(RabbitRemoteControlApp LANGUAGES CXX)

set(SOURCE_FILES
    main.cpp
    mainwindow.cpp
    FrmFullScreenToolBar.cpp
    ViewTable.cpp
    View.cpp
    ViewFrmScroll.cpp
    ParameterApp.cpp
    ParameterDlgSettings.cpp
    FavoriteView.cpp
    FavoriteMimeData.cpp
    )

set(HEADER_FILES
    mainwindow.h
    FrmFullScreenToolBar.h
    ViewTable.h
    View.h
    ViewFrmScroll.h
    ParameterApp.h
    ParameterDlgSettings.h
    FavoriteView.h
    FavoriteMimeData.h
    )

set(SOURCE_UI_FILES
    mainwindow.ui
    FrmFullScreenToolBar.ui
    ParameterDlgSettings.ui
    )

if(WIN32)
    set(RCC_FILES Resource/App.rc)
endif()
LIST(APPEND RCC_FILES Resource/Resource.qrc)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets)
    
ADD_TARGET(NAME ${PROJECT_NAME}
    ISEXE
    ISWINDOWS
    VERSION ${RabbitRemoteControl_VERSION}
    PRIVATE_DEFINITIONS RabbitRemoteControl_VERSION="${RabbitRemoteControl_VERSION}"
    SOURCE_FILES ${SOURCE_FILES} ${HEADER_FILES} ${SOURCE_UI_FILES} ${RCC_FILES}
    PRIVATE_LIBS Client)

if(NOT EXISTS ${CMAKE_BINARY_DIR}/etc/RabbitRemoteControl.conf)
    configure_file(${CMAKE_SOURCE_DIR}/etc/RabbitRemoteControl.debug.conf
        ${CMAKE_BINARY_DIR}/etc/RabbitRemoteControl.conf
        COPYONLY)
endif()
INSTALL(FILES ${CMAKE_SOURCE_DIR}/etc/RabbitRemoteControl.conf
    DESTINATION etc
        COMPONENT Runtime)

if(WIN32)
    install(FILES Resource/icons/green/ico/app.ico
        DESTINATION .
            COMPONENT Runtime)
endif()
if(UNIX AND NOT ANDROID)
    set(APP_ICON_NAME org.Rabbit.RemoteControl)
    configure_file(${CMAKE_SOURCE_DIR}/share/applications/org.Rabbit.RemoteControl.desktop.in
        ${CMAKE_BINARY_DIR}/org.Rabbit.RemoteControl.desktop)
    INSTALL(FILES ${CMAKE_BINARY_DIR}/org.Rabbit.RemoteControl.desktop
        DESTINATION share/applications
            COMPONENT Runtime)
    INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Resource/icons/green/svg/app.svg
        DESTINATION share/pixmaps
            COMPONENT Runtime
        RENAME ${APP_ICON_NAME}.svg)
endif()

# Install QIcon theme
INSTALL_ICON_THEME()
