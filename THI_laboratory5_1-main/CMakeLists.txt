cmake_minimum_required(VERSION 3.19)
project(programm5_lab4 LANGUAGES CXX)

# Устанавливаем стандарты компилятора, как в лабораторной 7
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

include_directories("C:/THI/laboratory4/programm_lab4")
include_directories("C:/THI/music_lib3")
link_directories("C:/THI/laboratory4/programm_lab4/build")
link_directories("C:/THI/music_lib3/music_lib3/build/music_lib3.dll")

qt_add_executable(programm5_lab4
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    sec_window.h
    sec_window.cpp
    sec_window.ui
    C:/THI/music_lib3/music_lib3.h
    C:/THI/music_lib3/music_lib3.cpp
    C:/THI/laboratory4/programm_lab4/trackfactorymethod.h
)
target_link_libraries(programm5_lab4 PRIVATE Qt::Core Qt::Widgets)

include(CTest)
enable_testing()

add_executable(run_unit_tests
    tests/test_musiclib.cpp
    C:/THI/music_lib3/music_lib3.cpp
)

target_link_libraries(run_unit_tests PRIVATE GTest::gtest GTest::gtest_main)

add_test(NAME MusicLibraryGoogleTests COMMAND run_unit_tests)

include(GNUInstallDirs)
install(TARGETS programm5_lab4
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
qt_generate_deploy_app_script(
    TARGET programm5_lab4
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
