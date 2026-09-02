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
        # Source/Engine/Source 模块
        "Source/Engine/Source/Agile/*.h"
        "Source/Engine/Source/Agile/*.cpp"
        "Source/Engine/Source/Anim/*.h"
        "Source/Engine/Source/Anim/*.cpp"
        "Source/Engine/Source/Base/*.h"
        "Source/Engine/Source/Base/*.cpp"
        "Source/Engine/Source/BLPFile/*.h"
        "Source/Engine/Source/BLPFile/*.cpp"
        "Source/Engine/Source/BLPFile/IJG/*.h"
        "Source/Engine/Source/BLPFile/IJG/*.cpp"
        "Source/Engine/Source/BattleNet/*.h"
        "Source/Engine/Source/BattleNet/*.cpp"
        "Source/Engine/Source/Common/*.h"
        "Source/Engine/Source/Common/*.cpp"
        "Source/Engine/Source/Event/*.h"
        "Source/Engine/Source/Event/*.cpp"
        "Source/Engine/Source/FDFile/*.h"
        "Source/Engine/Source/FDFile/*.cpp"
        "Source/Engine/Source/FDFile/Handlers/*.h"
        "Source/Engine/Source/FDFile/Handlers/*.cpp"
        "Source/Engine/Source/Frame/*.h"
        "Source/Engine/Source/Frame/*.cpp"
        "Source/Engine/Source/FrameDef/*.h"
        "Source/Engine/Source/FrameDef/*.cpp"
        "Source/Engine/Source/Gx/**/*.h"
        "Source/Engine/Source/Gx/**/*.cpp"
        "Source/Engine/Source/Gxu/*.h"
        "Source/Engine/Source/Gxu/*.cpp"
        "Source/Engine/Source/Images/*.h"
        "Source/Engine/Source/Images/*.cpp"
        "Source/Engine/Source/Ipse/*.h"
        "Source/Engine/Source/Ipse/*.cpp"
        "Source/Engine/Source/Jass2/*.h"
        "Source/Engine/Source/Jass2/*.cpp"
        "Source/Engine/Source/Model/*.h"
        "Source/Engine/Source/Model/*.cpp"
        "Source/Engine/Source/Net/*.h"
        "Source/Engine/Source/Net/*.cpp"
        "Source/Engine/Source/Net/**/*.h"
        "Source/Engine/Source/Net/**/*.cpp"
        "Source/Engine/Source/Os/**/*.h"
        "Source/Engine/Source/Os/**/*.cpp"
        "Source/Engine/Source/SRP/*.h"
        "Source/Engine/Source/SRP/*.cpp"
        "Source/Engine/Source/Scrn/*.h"
        "Source/Engine/Source/Scrn/*.cpp"
        "Source/Engine/Source/Services/*.h"
        "Source/Engine/Source/Services/*.cpp"
        "Source/Engine/Source/Sound/*.h"
        "Source/Engine/Source/Sound/*.cpp"
        "Source/Engine/Source/Tempest/*.h"
        "Source/Engine/Source/Tempest/*.cpp"
        "Source/Engine/Source/WardenClient/*.h"
        "Source/Engine/Source/WardenClient/*.cpp"
        # Source/ 顶层模块
        "Source/AI/*.h"
        "Source/AI/*.cpp"
        "Source/Game/*.h"
        "Source/Game/*.cpp"
        "Source/Glue/*.h"
        "Source/Glue/*.cpp"
        "Source/Net/*.h"
        "Source/Net/*.cpp"
        "Source/StormMac/**/*.h"
        "Source/StormMac/**/*.cpp"
        "Source/System/**/*.h"
        "Source/System/**/*.cpp"
        "Source/UI/*.h"
        "Source/UI/*.cpp"
        "Source/Unit/*.h"
        "Source/Unit/*.cpp"
        "Source/World/*.h"
        "Source/World/*.cpp"
        "Source/WorldEdit/*.h"
        "Source/WorldEdit/*.cpp"
        # 顶层文件
        "Source/Data.h"
        "Source/Engine.cpp"
        "Source/main.cpp"
)

link_directories(${CMAKE_SOURCE_DIR}/build/Debug/)
find_package(Qt6 REQUIRED COMPONENTS Gui Widgets OpenGL)
qt_standard_project_setup()
qt_add_executable(warden Source/main.cpp external/glad/src/glad.c ${dir_src})
target_link_libraries(warden PRIVATE Qt6::Gui Qt6::Widgets Qt6::OpenGL)
set_target_properties(warden PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)
add_custom_command(TARGET warden POST_BUILD
        COMMAND ${QT_INSTALL_DIR}/bin/windeployqt "$<TARGET_FILE:warden>"
)

target_include_directories(warden PRIVATE "/")
target_include_directories(warden PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(warden PRIVATE ${CMAKE_SOURCE_DIR}/Source)
target_include_directories(warden PRIVATE ${CMAKE_SOURCE_DIR}/Source/Engine/Source)
target_include_directories(warden PRIVATE "external/freetype-2.0.9/include")
target_include_directories(warden PRIVATE "external/")
target_include_directories(warden PRIVATE "external/lua-5.1.3/src")
target_include_directories(warden PRIVATE "external/glad/include" )
add_subdirectory(${PROJECT_SOURCE_DIR}/external/freetype-2.0.9)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/lua-5.1.3)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/expat-2.0.1)
message("${CMAKE_SOURCE_DIR}/build/lib/Debug/")
target_link_libraries(warden PUBLIC freetype-2.0 ws2_32 lua-5.1 wsock32 expat-2.0)
target_compile_definitions(expat-2.0 PUBLIC -DXML_STATIC)
set_target_properties(warden PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(freetype-2.0 PROPERTIES LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(freetype-2.0 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)

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

        # Tempest test library
        add_library(tempest_lib STATIC
                Source/Engine/Source/Tempest/C2Vector.cpp
                Source/Engine/Source/Tempest/C3Vector.cpp
                Source/Engine/Source/Tempest/C4Vector.cpp
                Source/Engine/Source/Tempest/C4Quaternion.cpp
                Source/Engine/Source/Tempest/C33Matrix.cpp
                Source/Engine/Source/Tempest/C44Matrix.cpp
                Source/Engine/Source/Tempest/C4Plane.cpp
                Source/Engine/Source/Tempest/CRect.cpp
                Source/Engine/Source/Tempest/CMathi.cpp
                Source/Engine/Source/Tempest/CiRect.cpp
                Source/Engine/Source/Tempest/C22uMatrix.cpp
                Source/Engine/Source/Tempest/CAaSphere.cpp
                Source/Engine/Source/Tempest/CDynParms.cpp
                Source/Engine/Source/Tempest/CPresenceSys.cpp
                Source/Engine/Source/Tempest/CPresenceSysTagged.cpp
                Source/StormMac/Error.cpp
                Source/StormMac/Debug.cpp
                Source/StormMac/memory.cpp
                Source/StormMac/String.cpp
                Source/StormMac/string/bjhash.cpp
                Source/StormMac/thread/SCritSect.cpp
                Source/StormMac/big/BigBuffer.cpp
                Source/StormMac/big/BigStack.cpp
                Source/StormMac/big/BigData.cpp
                Source/StormMac/xml/XMLNode.cpp
                Source/StormMac/xml/XMLTree.cpp
                Source/StormMac/mempool/MemPool.cpp
                Source/StormMac/mempool/MemChunk.cpp
                Source/StormMac/thread/CCritSect.cpp
                Source/StormMac/thread/SSyncObject.cpp
                Source/StormMac/thread/SEvent.cpp
                Source/Engine/Source/Common/Hashkey.cpp
                Source/Engine/Source/Common/RCString.cpp
                Source/Engine/Source/Agile/CStringManager.cpp
                Source/Engine/Source/Agile/CStringMemory.cpp
                Source/Unit/CUnit.cpp
                Source/Unit/CItem.cpp
                Source/Unit/CWidget.cpp
                Source/WorldEdit/CTerrain.cpp
                Source/WorldEdit/CTerrainClickEvent.cpp
                Source/WorldEdit/CWeatherArea.cpp
                Source/WorldEdit/CRegion.cpp
                Source/WorldEdit/CWeatherEmitter.cpp
                Source/WorldEdit/CTerrainDeformation.cpp
                Source/WorldEdit/MapInfoFile.cpp
                Source/WorldEdit/CWorldObjects.cpp
                Source/WorldEdit/CWeatherEffects.cpp
                Source/WorldEdit/TextureUtilities.cpp
                Source/WorldEdit/CTerrainBlight.cpp
                Source/WorldEdit/CTerrainBounds.cpp
                Source/WorldEdit/CTerrainCliff.cpp
                Source/WorldEdit/CTerrainCliffDoodads.cpp
                Source/WorldEdit/CTerrainHeight.cpp
                Source/WorldEdit/CTerrainRamp.cpp
                Source/WorldEdit/CTerrainTextures.cpp
                Source/WorldEdit/CTerrainUberSplats.cpp
                Source/WorldEdit/CTerrainVertex.cpp
                Source/WorldEdit/CTerrainWater.cpp
                Source/WorldEdit/CWorldObjectsClippable.cpp
                Source/WorldEdit/TestGameFile.cpp
                Source/WorldEdit/WEPreferences.cpp
                Source/WorldEdit/WEUtilities.cpp
                Source/Engine/Source/Gxu/GxuFont.cpp
                Source/Engine/Source/Gxu/GxuFontUtil.cpp
                Source/Engine/Source/Gxu/GxuLight.cpp
                Source/Engine/Source/Gxu/IGxuFontGlyph.cpp
                Source/Engine/Source/Images/CWar3Image.cpp
                Source/Engine/Source/Images/CTgaTexture.cpp
                Source/Engine/Source/Images/CBlpTexture.cpp
                Source/Engine/Source/Images/funcs.cpp
                Source/Engine/Source/Images/tga.cpp
                Source/Engine/Source/FrameDef/FrameDef.cpp
                Source/Engine/Source/FrameDef/SetupFrame.cpp
                Source/Engine/Source/Agile/CStatus.cpp
                Source/Engine/Source/Agile/Float.cpp
                Source/Engine/Source/Agile/Integer.cpp
                Source/Engine/Source/Agile/Position.cpp
                Source/Engine/Source/Agile/CPresenceRef.cpp
                Source/Engine/Source/Agile/CAgentField.cpp
                Source/Engine/Source/Agile/CRelation.cpp
                Source/Engine/Source/Agile/CListener.cpp
                Source/Engine/Source/Agile/CModifier.cpp
                Source/Engine/Source/Agile/FloatListener.cpp
                Source/Engine/Source/Agile/FloatModifier.cpp
                Source/Engine/Source/Agile/IntegerListener.cpp
                Source/Engine/Source/Agile/IntegerModifier.cpp
                Source/Engine/Source/Agile/CAgent.cpp
                Source/Engine/Source/Agile/CObserver.cpp
                Source/Engine/Source/Agile/CEventTimer.cpp
                Source/Engine/Source/Agile/CLeaveEvent.cpp
                Source/Engine/Source/Agile/CAgentTimerEvent.cpp
                Source/Engine/Source/Agile/CEventTimerEvent.cpp
                Source/Engine/Source/Agile/CDatabaseBase.cpp
                Source/Engine/Source/Agile/CDBDatabase.cpp
                Source/Engine/Source/Agile/CSLKDatabase.cpp
                Source/Engine/Source/Agile/CHuffman.cpp
                Source/Engine/Source/Agile/CBitInput.cpp
                Source/Engine/Source/Agile/CAngle.cpp
                Source/Engine/Source/Agile/SmartPosition.cpp
                Source/Engine/Source/Agile/RangeListener.cpp
                Source/Engine/Source/Agile/MovementModifier.cpp
                Source/Engine/Source/Agile/ProjectilePosition.cpp
                Source/Engine/Source/Agile/TInstanceCache.cpp
                Source/Engine/Source/Agile/CAbility.cpp
                Source/Engine/Source/Agile/CAbilityInterfaced.cpp
                Source/Engine/Source/Agile/CAbilityBaseBuild.cpp
                Source/Engine/Source/Agile/CAbilityBaseSell.cpp
                Source/Engine/Source/Agile/CUnitRefList.cpp
                Source/Engine/Source/Agile/CAgentWar3.cpp
                Source/Engine/Source/Agile/AgentRefMini.cpp
                Source/Engine/Source/Agile/AgentRef.cpp
                Source/Engine/Source/Agile/CEvent.cpp
                Source/Engine/Source/Agile/CListenerEvent.cpp
                Source/Engine/Source/Anim/Type.cpp
                Source/Engine/Source/BLPFile/blp.cpp
                Source/Engine/Source/BLPFile/IJG/jmemstorm.cpp
                Source/Engine/Source/Base/CDataStore.cpp
                Source/Engine/Source/Base/CDataStoreChunked.cpp
                Source/Engine/Source/Base/CDataAllocator.cpp
                Source/Engine/Source/Base/CDataRecycler.cpp
                Source/Engine/Source/Base/FileCache.cpp
                Source/Engine/Source/Base/Param.cpp
                Source/Engine/Source/Base/MsgBuffer.cpp
                Source/Engine/Source/Base/Status.cpp
                Source/Engine/Source/Base/RCString.cpp
                Source/Engine/Source/FDFile/FDFile.cpp
        )

        target_include_directories(tempest_lib PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        # Tempest tests
        add_executable(tempest_tests
                tests/Tempest/TestC2Vector.cpp
                tests/Tempest/TestC3Vector.cpp
                tests/Tempest/TestC4Vector.cpp
                tests/Tempest/TestC4Quaternion.cpp
                tests/Tempest/TestC33Matrix.cpp
                tests/Tempest/TestC44Matrix.cpp
                tests/Tempest/TestC4Plane.cpp
                tests/Tempest/TestCRect.cpp
                tests/Tempest/TestCMath.cpp
                tests/Tempest/TestMoreTempestClasses.cpp
        )

        target_link_libraries(tempest_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(tempest_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(tempest_tests)

        # Agile tests
        add_executable(agile_tests
                tests/Agile/TestCStatus.cpp
                tests/Agile/TestFloat.cpp
                tests/Agile/TestInteger.cpp
                tests/Agile/TestPosition.cpp
                tests/Agile/TestAgileHierarchy.cpp
                tests/Agile/TestMoreClasses.cpp
                tests/Agile/TestAngleAndPosition.cpp
                tests/Agile/TestAbilityClasses.cpp
                tests/Agile/TestAgentClasses.cpp
        )

        target_link_libraries(agile_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(agile_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(agile_tests)

        # Common tests
        add_executable(common_tests
                tests/Common/TestTRefCnt.cpp
                tests/Common/TestTRefCntPtr.cpp
                tests/Common/TestTSLink.cpp
        )

        target_link_libraries(common_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(common_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(common_tests)

        # Event tests
        add_executable(event_tests
                tests/Event/TestEvtMessage.cpp
                tests/Event/TestEvtHandler.cpp
                tests/Event/TestEvtTimer.cpp
                tests/Event/TestEventTypes.cpp
        )

        target_link_libraries(event_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(event_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(event_tests)

        # StormMac tests
        add_executable(stormmac_tests
                tests/StormMac/TestSCritSect.cpp
                tests/StormMac/TestCCritSect.cpp
                tests/StormMac/TestDebug.cpp
                tests/StormMac/TestError.cpp
                tests/StormMac/TestMoreStormMacClasses.cpp
                tests/StormMac/TestXmlAndMempool.cpp
        )

        target_link_libraries(stormmac_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(stormmac_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(stormmac_tests)

        # UI tests
        add_executable(ui_tests
                tests/UI/TestUITypes.cpp
                tests/UI/TestFrameScript.cpp
        )

        target_link_libraries(ui_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(ui_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(ui_tests)

        # Ipse tests
        add_executable(ipse_tests
                tests/Ipse/TestCPoReal.cpp
                tests/Ipse/TestCRlAgent.cpp
                tests/Ipse/TestCRlAgentDef.cpp
        )

        target_link_libraries(ipse_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(ipse_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(ipse_tests)

        # Gx tests
        add_executable(gx_tests
                tests/Gx/TestGraphicTypes.cpp
                tests/Gx/TestC4Pixel.cpp
                tests/Gx/TestGxuClasses.cpp
                tests/Gx/TestGxComplete.cpp
        )

        target_link_libraries(gx_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(gx_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(gx_tests)

        # Game tests
        add_executable(game_tests
                tests/Game/TestGameTypes.cpp
                tests/Game/TestCBoundingBox.cpp
        )

        target_link_libraries(game_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(game_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(game_tests)

        # Anim tests
        add_executable(anim_tests
                tests/Anim/TestFixed16.cpp
        )

        target_link_libraries(anim_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(anim_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(anim_tests)

        # WorldEdit tests
        add_executable(worldedit_tests
                tests/WorldEdit/TestTerrainVertex.cpp
                tests/WorldEdit/TestWorldEditClasses.cpp
                tests/WorldEdit/TestMoreWorldEditClasses.cpp
                tests/WorldEdit/TestEvenMoreWorldEditClasses.cpp
                tests/WorldEdit/TestAllRemainingWorldEditClasses.cpp
        )

        target_link_libraries(worldedit_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(worldedit_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(worldedit_tests)

        # FDFile tests
        add_executable(fdfile_tests
                tests/FDFile/TestFDFile.cpp
        )

        target_link_libraries(fdfile_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(fdfile_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(fdfile_tests)

        # Net tests
        add_executable(net_tests
                tests/Net/TestNetTypes.cpp
        )

        target_link_libraries(net_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(net_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(net_tests)

        # Sound tests
        add_executable(sound_tests
                tests/Sound/TestSI2.cpp
        )

        target_link_libraries(sound_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(sound_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(sound_tests)

        # Glue tests
        add_executable(glue_tests
                tests/Glue/TestCGlueMgr.cpp
        )

        target_link_libraries(glue_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(glue_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(glue_tests)

        # BLPFile tests
        add_executable(blp_tests
                tests/BLPFile/TestBLPFile.cpp
        )

        target_link_libraries(blp_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(blp_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(blp_tests)

        # Images tests
        add_executable(images_tests
                tests/Images/TestImagesClasses.cpp
        )

        target_link_libraries(images_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(images_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(images_tests)

        # Base tests
        add_executable(base_tests
                tests/Base/TestMsgBuffer.cpp
                tests/Base/TestStatus.cpp
                tests/Base/TestRCString.cpp
                tests/Base/TestMoreBaseClasses.cpp
                tests/Base/TestPropAndParam.cpp
        )

        target_link_libraries(base_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(base_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(base_tests)

        # FrameDef tests
        add_executable(framedef_tests
                tests/FrameDef/TestFrameDefClasses.cpp
        )

        target_link_libraries(framedef_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(framedef_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(framedef_tests)

        # Unit tests
        add_executable(unit_tests
                tests/Unit/TestUnitClasses.cpp
        )

        target_link_libraries(unit_tests PRIVATE tempest_lib GTest::gtest_main)
        target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Source/Engine/Source)

        include(GoogleTest)
        gtest_discover_tests(unit_tests)
    endif()
endif()
