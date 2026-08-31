cmake_minimum_required(VERSION 3.27)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include Qt basic functions
include(QtCommon)

project(warden)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DWIN32_LEAN_AND_MEAN)
if (WIN32 AND MSVC)
    add_compile_options(/wd4819)
endif ()

file(GLOB_RECURSE dir_src
        # 原有模块
        "Agile/*.h"
        "Agile/*.cpp"
        "Common/*.h"
        "Common/*.cpp"
        "NIpse/*.h"
        "NIpse/*.cpp"
        "NTempest/*.h"
        "NTempest/*.cpp"
        "Graphic/*.h"
        "Graphic/*.cpp"
        "Graphic/gll/.h"
        "Graphic/gll/.cpp"
        "Storm/*.h"
        "Storm/*.cpp"
        "include/*.h"
        "Anim/*.h"
        "Anim/*.cpp"
        "Services/*.h"
        "Services/*.cpp"
        "Scrn/*.h"
        "Scrn/*.cpp"
        "Glue/*.h"
        "Glue/*.cpp"
        "Event/*.h"
        "Event/*.cpp"
        "Net/*.h"
        "Net/*.cpp"
        "UI/*.h"
        "UI/*.cpp"
        "Game/*.h"
        "Game/*.cpp"
        "Sound/*.h"
        "Sound/*.cpp"
        # 基于 IDA 分析新增的模块
        "WorldEdit/*.h"
        "WorldEdit/*.cpp"
        "Unit/*.h"
        "Unit/*.cpp"
        "Engine/*.h"
        "Engine/*.cpp"
        "StormMac/*.h"
        "StormMac/*.cpp"
        "System/*.h"
        "System/*.cpp"
        "Win32/*.h"
        "Win32/*.cpp"
        "IOUnit/*.h"
        "IOUnit/*.cpp"
        "Mac/*.h"
        "Mac/*.cpp"
        "Data/*.h"
        "Data/*.cpp"
        "BLPFile/*.h"
        "BLPFile/*.cpp"
        "BLPFile/IJG/*.h"
        "BLPFile/IJG/*.cpp"
)

link_directories(${CMAKE_SOURCE_DIR}/build/Debug/)
find_package(Qt6 REQUIRED COMPONENTS Gui Widgets OpenGL)
qt_standard_project_setup()
qt_add_executable(warden main.cpp external/glad/src/glad.c ${dir_src})
target_link_libraries(warden PRIVATE Qt6::Gui Qt6::Widgets Qt6::OpenGL)
set_target_properties(warden PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)
add_custom_command(TARGET warden POST_BUILD
        COMMAND ${QT_INSTALL_DIR}/bin/windeployqt "$<TARGET_FILE:warden>"
)

target_include_directories(warden PRIVATE "/")
target_include_directories(warden PRIVATE "external/freetype-2.0.9/include")
target_include_directories(warden PRIVATE "external/")
#target_include_directories(warden PRIVATE "external/glew-2.1.0/include")
target_include_directories(warden PRIVATE "external/lua-5.1.3/src")
target_include_directories(warden PRIVATE "external/glad/include" )
#target_compile_options(warden PRIVATE "/Zc:offsetof-")
#include_directories(${OPENGL_INCLUDE_DIRS})
#add_subdirectory(${PROJECT_SOURCE_DIR}/external/glew-2.1.0/build/cmake)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/freetype-2.0.9)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/lua-5.1.3)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/expat-2.0.1)
#add_definitions(
#        -DGLEW_STATIC
#)
message("${CMAKE_SOURCE_DIR}/build/lib/Debug/")
# target_link_libraries(warden PUBLIC ${OPENGL_LIBRARIES})
# glew32d
#
target_link_libraries(warden PUBLIC freetype-2.0 ws2_32 lua-5.1 wsock32 expat-2.0)
target_compile_definitions(expat-2.0 PUBLIC -DXML_STATIC)
set_target_properties(warden PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(freetype-2.0 PROPERTIES LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(freetype-2.0 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew PROPERTIES LIBRARY_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew PROPERTIES RUNTIME_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew_s PROPERTIES LIBRARY_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew_s PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)

# Option to enable tests
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    # Google Test - use local copy
    if(EXISTS "${CMAKE_SOURCE_DIR}/external/googletest/CMakeLists.txt")
        add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest)
    else()
        message(WARNING "Google Test not found in external/googletest. Tests will not be built.")
        set(BUILD_TESTS OFF)
    endif()

    if(BUILD_TESTS)
        enable_testing()

        # NTempest test library (header-only + source)
        add_library(ntempest_lib STATIC
                NTempest/C2Vector.cpp
                NTempest/C3Vector.cpp
                NTempest/C4Vector.cpp
                NTempest/C4Quaternion.cpp
                NTempest/C33Matrix.cpp
                NTempest/C44Matrix.cpp
                NTempest/C4Plane.cpp
                NTempest/CRect.cpp
                NTempest/CMathi.cpp
                NTempest/CiRect.cpp
                NTempest/C22uMatrix.cpp
                NTempest/CAaSphere.cpp
                Storm/Error.cpp
                Storm/Debug.cpp
                Storm/thread/SCritSect.cpp
                Storm/thread/CCritSect.cpp
                Storm/thread/SSyncObject.cpp
                Storm/thread/SEvent.cpp
                Common/Hashkey.cpp
                Agile/CStatus.cpp
                Agile/Float.cpp
                Agile/Integer.cpp
                Agile/Position.cpp
                Anim/Type.cpp
                BLPFile/blp.cpp
                BLPFile/IJG/jmemstorm.cpp
                Base/CDataStore.cpp
                Base/MsgBuffer.cpp
                Base/Status.cpp
                Base/RCString.cpp
                FDFile/FDFile.cpp
        )

        target_include_directories(ntempest_lib PRIVATE ${CMAKE_SOURCE_DIR})

        # NTempest tests
        add_executable(ntempest_tests
                tests/NTempest/TestC2Vector.cpp
                tests/NTempest/TestC3Vector.cpp
                tests/NTempest/TestC4Vector.cpp
                tests/NTempest/TestC4Quaternion.cpp
                tests/NTempest/TestC33Matrix.cpp
                tests/NTempest/TestC44Matrix.cpp
                tests/NTempest/TestC4Plane.cpp
                tests/NTempest/TestCRect.cpp
                tests/NTempest/TestCMath.cpp
        )

        target_link_libraries(ntempest_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(ntempest_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(ntempest_tests)

        # Agile tests
        add_executable(agile_tests
                tests/Agile/TestCStatus.cpp
                tests/Agile/TestFloat.cpp
                tests/Agile/TestInteger.cpp
                tests/Agile/TestPosition.cpp
        )

        target_link_libraries(agile_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(agile_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(agile_tests)

        # Common tests
        add_executable(common_tests
                tests/Common/TestTRefCnt.cpp
                tests/Common/TestTRefCntPtr.cpp
                tests/Common/TestTSLink.cpp
        )

        target_link_libraries(common_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(common_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(common_tests)

        # Event tests
        add_executable(event_tests
                tests/Event/TestEvtMessage.cpp
                tests/Event/TestEvtHandler.cpp
                tests/Event/TestEvtTimer.cpp
                tests/Event/TestEventTypes.cpp
        )

        target_link_libraries(event_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(event_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(event_tests)

        # Storm tests
        add_executable(storm_tests
                tests/Storm/TestSCritSect.cpp
                tests/Storm/TestCCritSect.cpp
                tests/Storm/TestDebug.cpp
                tests/Storm/TestError.cpp
        )

        target_link_libraries(storm_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(storm_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(storm_tests)

        # UI tests
        add_executable(ui_tests
                tests/UI/TestUITypes.cpp
                tests/UI/TestFrameScript.cpp
        )

        target_link_libraries(ui_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(ui_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(ui_tests)

        # NIpse tests
        add_executable(nipse_tests
                tests/NIpse/TestCPoReal.cpp
                tests/NIpse/TestCRlAgent.cpp
                tests/NIpse/TestCRlAgentDef.cpp
        )

        target_link_libraries(nipse_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(nipse_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(nipse_tests)

        # Graphic tests
        add_executable(graphic_tests
                tests/Graphic/TestGraphicTypes.cpp
                tests/Graphic/TestC4Pixel.cpp
        )

        target_link_libraries(graphic_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(graphic_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(graphic_tests)

        # Game tests
        add_executable(game_tests
                tests/Game/TestGameTypes.cpp
                tests/Game/TestCBoundingBox.cpp
        )

        target_link_libraries(game_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(game_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(game_tests)

        # Anim tests
        add_executable(anim_tests
                tests/Anim/TestFixed16.cpp
        )

        target_link_libraries(anim_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(anim_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(anim_tests)

        # WorldEdit tests
        add_executable(worldedit_tests
                tests/WorldEdit/TestTerrainVertex.cpp
        )

        target_link_libraries(worldedit_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(worldedit_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(worldedit_tests)

        # FDFile tests
        add_executable(fdfile_tests
                tests/FDFile/TestFDFile.cpp
        )

        target_link_libraries(fdfile_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(fdfile_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(fdfile_tests)

        # Net tests
        add_executable(net_tests
                tests/Net/TestNetTypes.cpp
        )

        target_link_libraries(net_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(net_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(net_tests)

        # Sound tests
        add_executable(sound_tests
                tests/Sound/TestSI2.cpp
        )

        target_link_libraries(sound_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(sound_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(sound_tests)

        # Glue tests
        add_executable(glue_tests
                tests/Glue/TestCGlueMgr.cpp
        )

        target_link_libraries(glue_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(glue_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(glue_tests)

        # BLPFile tests
        add_executable(blp_tests
                tests/BLPFile/TestBLPFile.cpp
        )

        target_link_libraries(blp_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(blp_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(blp_tests)

        # Base tests
        add_executable(base_tests
                tests/Base/TestCDataStore.cpp
                tests/Base/TestMsgBuffer.cpp
                tests/Base/TestStatus.cpp
                tests/Base/TestRCString.cpp
        )

        target_link_libraries(base_tests PRIVATE ntempest_lib GTest::gtest_main)
        target_include_directories(base_tests PRIVATE ${CMAKE_SOURCE_DIR})

        include(GoogleTest)
        gtest_discover_tests(base_tests)
    endif()
endif()