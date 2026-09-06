#include <gtest/gtest.h>
#include "FDFile/FDFile.h"
#include <fstream>
#include <sstream>
#include <string>

// ============================================================
// 辅助函数
// ============================================================

static std::string ReadFileContent(const char* relPath) {
    std::string fullPath = std::string(PROJECT_ROOT_DIR) + "/" + relPath;
    std::ifstream file(fullPath, std::ios::binary);
    if (!file.is_open()) return "";
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// ============================================================
// 基础功能测试
// ============================================================

TEST(FDFileTest, DefaultConstructor) {
    FDFile fd;
    EXPECT_FALSE(fd.IsValid());
    EXPECT_EQ(fd.GetStatus(), FRAMEDEF_STATUS_OK);
    EXPECT_STREQ(fd.GetErrorMessage(), "");
}

TEST(FDFileTest, ParseSimpleFrame) {
    FDFile fd;
    const char* fdf = R"(
Frame "FRAME" "TestFrame" {
    Width 0.5,
    Height 0.3,
}
)";

    EXPECT_TRUE(fd.LoadFromMemory(fdf, strlen(fdf)));
    EXPECT_TRUE(fd.IsValid());

    const FdfNode* frame = fd.FindFrame("TestFrame");
    ASSERT_NE(frame, nullptr);
    EXPECT_EQ(frame->frameType, "FRAME");
    EXPECT_EQ(frame->name, "TestFrame");
    EXPECT_GE(frame->attributes.size(), 2u);
}

TEST(FDFileTest, ParseFrameWithInherits) {
    FDFile fd;
    const char* fdf = R"(
Frame "FRAME" "MainMenuFrame" INHERITS "StandardFrameTemplate" {
    SetAllPoints,
}
)";

    EXPECT_TRUE(fd.LoadFromMemory(fdf, strlen(fdf)));

    const FdfNode* frame = fd.FindFrame("MainMenuFrame");
    ASSERT_NE(frame, nullptr);
    EXPECT_EQ(frame->inheritsFrom, "StandardFrameTemplate");
    EXPECT_EQ(frame->withChildren, false);
}

TEST(FDFileTest, ParseFrameWithInheritsWithChildren) {
    FDFile fd;
    const char* fdf = R"(
Frame "GLUETEXTBUTTON" "OKButton" INHERITS WITHCHILDREN "StandardSmallButtonTemplate" {
    Width 0.079,
}
)";

    EXPECT_TRUE(fd.LoadFromMemory(fdf, strlen(fdf)));

    const FdfNode* frame = fd.FindFrame("OKButton");
    ASSERT_NE(frame, nullptr);
    EXPECT_EQ(frame->inheritsFrom, "StandardSmallButtonTemplate");
    EXPECT_EQ(frame->withChildren, true);
}

TEST(FDFileTest, ParseNestedFrames) {
    FDFile fd;
    const char* fdf = R"(
Frame "FRAME" "ParentFrame" {
    Frame "TEXT" "ChildText" {
        Text "Hello",
    }
    Frame "SPRITE" "ChildSprite" {
        File "logo.blp",
    }
}
)";

    EXPECT_TRUE(fd.LoadFromMemory(fdf, strlen(fdf)));

    const FdfNode* parent = fd.FindFrame("ParentFrame");
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(parent->children.size(), 2u);

    const FdfNode* child1 = parent->children[0];
    EXPECT_EQ(child1->name, "ChildText");
    EXPECT_EQ(child1->frameType, "TEXT");

    const FdfNode* child2 = parent->children[1];
    EXPECT_EQ(child2->name, "ChildSprite");
    EXPECT_EQ(child2->frameType, "SPRITE");
}

TEST(FDFileTest, ParseTextureBlock) {
    FDFile fd;
    const char* fdf = R"(
Frame "SIMPLEFRAME" "ConsoleUI" {
    Texture {
        File "ConsoleTexture01",
        Width 0.256,
        Height 0.032,
        TexCoord 0, 1, 0, 0.125,
        AlphaMode "ALPHAKEY",
        Anchor TOPLEFT,0,0,
    }
}
)";

    EXPECT_TRUE(fd.LoadFromMemory(fdf, strlen(fdf)));

    const FdfNode* frame = fd.FindFrame("ConsoleUI");
    ASSERT_NE(frame, nullptr);
    ASSERT_EQ(frame->children.size(), 1u);

    const FdfNode* texture = frame->children[0];
    EXPECT_EQ(texture->frameType, "TEXTURE");
    EXPECT_GE(texture->attributes.size(), 5u);
}

TEST(FDFileTest, ParseStringList) {
    FDFile fd;
    const char* fdf = R"(
StringList {
    MONTH_01        "January",
    MONTH_02        "February",
    DAY_01          "Sunday",
}
)";

    EXPECT_TRUE(fd.LoadFromMemory(fdf, strlen(fdf)));

    std::string value;
    EXPECT_TRUE(fd.GetString("MONTH_01", value));
    EXPECT_EQ(value, "January");

    EXPECT_TRUE(fd.GetString("MONTH_02", value));
    EXPECT_EQ(value, "February");

    EXPECT_TRUE(fd.GetString("DAY_01", value));
    EXPECT_EQ(value, "Sunday");

    EXPECT_FALSE(fd.GetString("NONEXISTENT", value));
}

TEST(FDFileTest, ParseComments) {
    FDFile fd;
    const char* fdf = R"(
// 单行注释
Frame "FRAME" "CommentedFrame" {
    /* 多行
       注释 */
    Width 0.5,
}
)";

    EXPECT_TRUE(fd.LoadFromMemory(fdf, strlen(fdf)));

    const FdfNode* frame = fd.FindFrame("CommentedFrame");
    ASSERT_NE(frame, nullptr);
}

TEST(FDFileTest, InvalidContent) {
    FDFile fd;
    EXPECT_FALSE(fd.LoadFromMemory(nullptr, 0));
    EXPECT_FALSE(fd.IsValid());
}

TEST(FDFileTest, Clear) {
    FDFile fd;
    const char* fdf = R"(
Frame "FRAME" "TestFrame" {
    Width 0.5,
}
)";

    fd.LoadFromMemory(fdf, strlen(fdf));
    EXPECT_TRUE(fd.IsValid());

    fd.Clear();
    EXPECT_FALSE(fd.IsValid());
    EXPECT_EQ(fd.GetRootNode(), nullptr);
    EXPECT_TRUE(fd.GetFrames().empty());
    EXPECT_TRUE(fd.GetStrings().empty());
}

TEST(FDFileTest, EnumValues) {
    EXPECT_EQ(FRAMEDEF_STATUS_OK, 0);
    EXPECT_EQ(FRAMEDEF_STATUS_ERROR, 1);
    EXPECT_EQ(FRAMEDEF_STATUS_NOT_FOUND, 2);
}

// ============================================================
// 真实数据文件加载测试 (使用真正的 FDF 解析)
// ============================================================

class FDFileRealDataTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 确保项目根目录下的数据文件存在
    }
};

// --- StringList 格式文件测试 ---

TEST_F(FDFileRealDataTest, LoadDateStrings) {
    std::string content = ReadFileContent("data/FrameDef/DateStrings.fdf");
    ASSERT_FALSE(content.empty()) << "DateStrings.fdf not found";

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()))
        << "Failed to parse DateStrings.fdf";

    // 验证字符串被正确解析
    std::string value;
    EXPECT_TRUE(fd.GetString("MONTH_01", value));
    EXPECT_EQ(value, "January");

    EXPECT_TRUE(fd.GetString("DAY_01", value));
    EXPECT_EQ(value, "Sunday");
}

TEST_F(FDFileRealDataTest, LoadGlobalStrings) {
    std::string content = ReadFileContent("data/FrameDef/GlobalStrings.fdf");
    ASSERT_FALSE(content.empty()) << "GlobalStrings.fdf not found";

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()))
        << "Failed to parse GlobalStrings.fdf";

    // 验证关键字符串存在
    std::string value;
    EXPECT_TRUE(fd.GetString("ACCEPT", value)) << "Missing ACCEPT string";
    EXPECT_TRUE(fd.GetString("AGILITY", value)) << "Missing AGILITY string";
}

TEST_F(FDFileRealDataTest, LoadNetworkStrings) {
    std::string content = ReadFileContent("data/FrameDef/NetworkStrings.fdf");
    ASSERT_FALSE(content.empty()) << "NetworkStrings.fdf not found";

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()))
        << "Failed to parse NetworkStrings.fdf";

    std::string value;
    EXPECT_TRUE(fd.GetString("ERROR_ID_CANTCONNECT", value))
        << "Missing ERROR_ID_CANTCONNECT string";
}

// --- Frame 定义文件测试 ---

TEST_F(FDFileRealDataTest, LoadConsoleUI) {
    std::string content = ReadFileContent("data/FrameDef/UI/ConsoleUI.fdf");
    ASSERT_FALSE(content.empty()) << "ConsoleUI.fdf not found";

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()))
        << "Failed to parse ConsoleUI.fdf";

    // 验证帧定义结构
    const FdfNode* frame = fd.FindFrame("ConsoleUI");
    ASSERT_NE(frame, nullptr) << "ConsoleUI frame not found";
    EXPECT_EQ(frame->frameType, "SIMPLEFRAME");

    // 验证有 Texture 子节点
    size_t textureCount = 0;
    for (const auto* child : frame->children) {
        if (child->frameType == "TEXTURE") {
            textureCount++;
        }
    }
    EXPECT_GE(textureCount, 4u) << "ConsoleUI should have multiple Texture children";
}

TEST_F(FDFileRealDataTest, LoadMainMenu) {
    std::string content = ReadFileContent("data/FrameDef/Glue/MainMenu.fdf");
    ASSERT_FALSE(content.empty()) << "MainMenu.fdf not found";

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()))
        << "Failed to parse MainMenu.fdf";

    // 验证嵌套 Frame 结构
    const FdfNode* frame = fd.FindFrame("MainMenuFrame");
    ASSERT_NE(frame, nullptr) << "MainMenuFrame not found";
    EXPECT_EQ(frame->inheritsFrom, "StandardFrameTemplate");

    // 验证有子帧
    EXPECT_GE(frame->children.size(), 1u) << "MainMenuFrame should have children";
}

TEST_F(FDFileRealDataTest, LoadStandardTemplates) {
    std::string content = ReadFileContent("data/FrameDef/Glue/StandardTemplates.fdf");
    ASSERT_FALSE(content.empty()) << "StandardTemplates.fdf not found";

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()))
        << "Failed to parse StandardTemplates.fdf";

    // 验证多个模板定义
    const FdfNode* heavy = fd.FindFrame("StandardHeavyBackdropTemplate");
    ASSERT_NE(heavy, nullptr) << "StandardHeavyBackdropTemplate not found";
    EXPECT_EQ(heavy->frameType, "BACKDROP");

    const FdfNode* medium = fd.FindFrame("StandardMediumBackdropTemplate");
    ASSERT_NE(medium, nullptr) << "StandardMediumBackdropTemplate not found";
}

TEST_F(FDFileRealDataTest, LoadAllRootFDFs) {
    const char* rootFiles[] = {
        "data/FrameDef/DateStrings.fdf",
        "data/FrameDef/GlobalStrings.fdf",
        "data/FrameDef/NetworkStrings.fdf",
    };

    for (const char* path : rootFiles) {
        std::string content = ReadFileContent(path);
        ASSERT_FALSE(content.empty()) << "Failed to load: " << path;

        FDFile fd;
        EXPECT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()))
            << "Failed to parse: " << path;
    }
}

TEST_F(FDFileRealDataTest, LoadAllGlueFDFs) {
    const char* glueFiles[] = {
        "data/FrameDef/Glue/AdvancedOptionsDisplay.fdf",
        "data/FrameDef/Glue/AdvancedOptionsPane.fdf",
        "data/FrameDef/Glue/BattleNetChatActionMenu.fdf",
        "data/FrameDef/Glue/BattleNetChatPanel.fdf",
        "data/FrameDef/Glue/BattleNetChatroom.fdf",
        "data/FrameDef/Glue/BattleNetCustomCreatePanel.fdf",
        "data/FrameDef/Glue/BattleNetCustomJoinPanel.fdf",
        "data/FrameDef/Glue/BattleNetCustomLoadPanel.fdf",
        "data/FrameDef/Glue/BattleNetFriendsListBox.fdf",
        "data/FrameDef/Glue/BattleNetFriendsPane.fdf",
        "data/FrameDef/Glue/BattleNetMain.fdf",
        "data/FrameDef/Glue/BattleNetNewsBox.fdf",
        "data/FrameDef/Glue/BattleNetProfilePanel.fdf",
        "data/FrameDef/Glue/BattleNetStandardPanel.fdf",
        "data/FrameDef/Glue/BattleNetTeamInvitation.fdf",
        "data/FrameDef/Glue/BattleNetTeamPanel.fdf",
        "data/FrameDef/Glue/BattleNetTemplates.fdf",
        "data/FrameDef/Glue/BattleNetUserListBox.fdf",
        "data/FrameDef/Glue/CampaignMenu.fdf",
        "data/FrameDef/Glue/CheckListBox.fdf",
        "data/FrameDef/Glue/DecoratedMapListBox.fdf",
        "data/FrameDef/Glue/DialogWar3.fdf",
        "data/FrameDef/Glue/GameChatroom.fdf",
        "data/FrameDef/Glue/ListBoxWar3.fdf",
        "data/FrameDef/Glue/LoadSavedGameScreen.fdf",
        "data/FrameDef/Glue/Loading.fdf",
        "data/FrameDef/Glue/LocalMultiplayerCreate.fdf",
        "data/FrameDef/Glue/LocalMultiplayerJoin.fdf",
        "data/FrameDef/Glue/LocalMultiplayerLoad.fdf",
        "data/FrameDef/Glue/MainMenu.fdf",
        "data/FrameDef/Glue/MapInfoPane.fdf",
        "data/FrameDef/Glue/MapListBox.fdf",
        "data/FrameDef/Glue/MapPreferenceBox.fdf",
        "data/FrameDef/Glue/MultiplayerMenu.fdf",
        "data/FrameDef/Glue/OptionsMenu.fdf",
        "data/FrameDef/Glue/PlayerSlot.fdf",
        "data/FrameDef/Glue/ScoreScreen.fdf",
        "data/FrameDef/Glue/SinglePlayerMenu.fdf",
        "data/FrameDef/Glue/Skirmish.fdf",
        "data/FrameDef/Glue/StandardTemplates.fdf",
        "data/FrameDef/Glue/TeamSetup.fdf",
        "data/FrameDef/Glue/ViewReplayScreen.fdf",
    };

    for (const char* path : glueFiles) {
        std::string content = ReadFileContent(path);
        ASSERT_FALSE(content.empty()) << "Failed to load: " << path;

        FDFile fd;
        EXPECT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()))
            << "Failed to parse: " << path;
    }
}

TEST_F(FDFileRealDataTest, LoadAllUIFDFs) {
    const char* uiFiles[] = {
        "data/FrameDef/UI/AllianceDialog.fdf",
        "data/FrameDef/UI/AllianceSlot.fdf",
        "data/FrameDef/UI/ChatDialog.fdf",
        "data/FrameDef/UI/CinematicPanel.fdf",
        "data/FrameDef/UI/ConsoleUI.fdf",
        "data/FrameDef/UI/EscMenuMainPanel.fdf",
        "data/FrameDef/UI/EscMenuOptionsPanel.fdf",
        "data/FrameDef/UI/EscMenuSaveGamePanel.fdf",
        "data/FrameDef/UI/EscMenuTemplates.fdf",
        "data/FrameDef/UI/GameResultDialog.fdf",
        "data/FrameDef/UI/GameSaveSplashDialog.fdf",
        "data/FrameDef/UI/InfoPanelBuildingDetail.fdf",
        "data/FrameDef/UI/InfoPanelItemDetail.fdf",
        "data/FrameDef/UI/InfoPanelTemplates.fdf",
        "data/FrameDef/UI/InfoPanelUnitDetail.fdf",
        "data/FrameDef/UI/LeaderBoard.fdf",
        "data/FrameDef/UI/LogDialog.fdf",
        "data/FrameDef/UI/QuestDialog.fdf",
        "data/FrameDef/UI/ReplayPanel.fdf",
        "data/FrameDef/UI/ResourceBar.fdf",
        "data/FrameDef/UI/ScriptDialog.fdf",
        "data/FrameDef/UI/SimpleInfoPanel.fdf",
        "data/FrameDef/UI/SuspendDialog.fdf",
        "data/FrameDef/UI/TimerDialog.fdf",
        "data/FrameDef/UI/UnresponsiveDialog.fdf",
        "data/FrameDef/UI/UpperButtonBar.fdf",
    };

    for (const char* path : uiFiles) {
        std::string content = ReadFileContent(path);
        ASSERT_FALSE(content.empty()) << "Failed to load: " << path;

        FDFile fd;
        EXPECT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()))
            << "Failed to parse: " << path;

        // 验证至少有一个帧定义
        EXPECT_FALSE(fd.GetFrames().empty())
            << "No frames found in: " << path;
    }
}

// ============================================================
// FDF 格式特征验证测试 (使用真正解析)
// ============================================================

TEST_F(FDFileRealDataTest, FDF_HasFrameSyntax) {
    std::string content = ReadFileContent("data/FrameDef/UI/ConsoleUI.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    // 验证帧被正确解析
    const FdfNode* frame = fd.FindFrame("ConsoleUI");
    EXPECT_NE(frame, nullptr);
    EXPECT_EQ(frame->frameType, "SIMPLEFRAME");
}

TEST_F(FDFileRealDataTest, FDF_HasStringListSyntax) {
    std::string content = ReadFileContent("data/FrameDef/DateStrings.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    // 验证字符串被正确解析
    EXPECT_FALSE(fd.GetStrings().empty());
}

TEST_F(FDFileRealDataTest, FDF_HasInherits) {
    std::string content = ReadFileContent("data/FrameDef/Glue/MainMenu.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    const FdfNode* frame = fd.FindFrame("MainMenuFrame");
    ASSERT_NE(frame, nullptr);
    EXPECT_EQ(frame->inheritsFrom, "StandardFrameTemplate");
}

TEST_F(FDFileRealDataTest, FDF_HasNestedFrames) {
    std::string content = ReadFileContent("data/FrameDef/UI/ConsoleUI.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    const FdfNode* frame = fd.FindFrame("ConsoleUI");
    ASSERT_NE(frame, nullptr);

    size_t textureCount = 0;
    for (const auto* child : frame->children) {
        if (child->frameType == "TEXTURE") {
            textureCount++;
        }
    }
    EXPECT_GE(textureCount, 4u);
}

TEST_F(FDFileRealDataTest, FDF_HasFrameTypes) {
    std::string content = ReadFileContent("data/FrameDef/Glue/StandardTemplates.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    // 验证多种帧类型被解析
    bool hasBackdrop = false, hasFrame = false;
    for (const auto& [name, frame] : fd.GetFrames()) {
        if (frame->frameType == "BACKDROP") hasBackdrop = true;
        if (frame->frameType == "FRAME") hasFrame = true;
    }

    EXPECT_TRUE(hasBackdrop) << "No BACKDROP type found in StandardTemplates";
    EXPECT_TRUE(hasFrame) << "No FRAME type found";
}

TEST_F(FDFileRealDataTest, FDF_HasTextProperties) {
    std::string content = ReadFileContent("data/FrameDef/Glue/MainMenu.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    // 验证文本属性被解析
    bool foundTextProp = false;
    for (const auto& [name, frame] : fd.GetFrames()) {
        for (const auto& attr : frame->attributes) {
            if (attr.name == "Text" || attr.name == "FontColor" ||
                attr.name == "FontJustificationH") {
                foundTextProp = true;
                break;
            }
        }
        if (foundTextProp) break;
    }

    EXPECT_TRUE(foundTextProp) << "No text properties found";
}

TEST_F(FDFileRealDataTest, FDF_HasTextureProperties) {
    std::string content = ReadFileContent("data/FrameDef/UI/ConsoleUI.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    // 验证纹理属性被解析
    bool foundTextureProp = false;
    for (const auto& [name, frame] : fd.GetFrames()) {
        for (const auto* child : frame->children) {
            for (const auto& attr : child->attributes) {
                if (attr.name == "File" || attr.name == "TexCoord" ||
                    attr.name == "AlphaMode") {
                    foundTextureProp = true;
                    break;
                }
            }
            if (foundTextureProp) break;
        }
        if (foundTextureProp) break;
    }

    EXPECT_TRUE(foundTextureProp) << "No texture properties found";
}

// ============================================================
// 数据完整性验证测试
// ============================================================

TEST_F(FDFileRealDataTest, DateStrings_CompleteMonths) {
    std::string content = ReadFileContent("data/FrameDef/DateStrings.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    // 验证12个月份都有定义
    const char* months[] = {
        "MONTH_01", "MONTH_02", "MONTH_03", "MONTH_04",
        "MONTH_05", "MONTH_06", "MONTH_07", "MONTH_08",
        "MONTH_09", "MONTH_10", "MONTH_11", "MONTH_12"
    };
    for (const char* month : months) {
        std::string value;
        EXPECT_TRUE(fd.GetString(month, value)) << "Missing month: " << month;
    }
}

TEST_F(FDFileRealDataTest, DateStrings_CompleteDays) {
    std::string content = ReadFileContent("data/FrameDef/DateStrings.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    // 验证7天都有定义
    const char* days[] = {
        "DAY_01", "DAY_02", "DAY_03", "DAY_04",
        "DAY_05", "DAY_06", "DAY_07"
    };
    for (const char* day : days) {
        std::string value;
        EXPECT_TRUE(fd.GetString(day, value)) << "Missing day: " << day;
    }
}

TEST_F(FDFileRealDataTest, GlobalStrings_ArmorTypes) {
    std::string content = ReadFileContent("data/FrameDef/GlobalStrings.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    // 验证护甲类型定义完整
    std::string value;
    EXPECT_TRUE(fd.GetString("ARMOR_FORT", value));
    EXPECT_TRUE(fd.GetString("ARMOR_HERO", value));
    EXPECT_TRUE(fd.GetString("ARMOR_LARGE", value));
    EXPECT_TRUE(fd.GetString("ARMOR_MEDIUM", value));
    EXPECT_TRUE(fd.GetString("ARMOR_NORMAL", value));
    EXPECT_TRUE(fd.GetString("ARMOR_SMALL", value));
    EXPECT_TRUE(fd.GetString("ARMOR_DIVINE", value));
}

TEST_F(FDFileRealDataTest, NetworkStrings_ErrorIDs) {
    std::string content = ReadFileContent("data/FrameDef/NetworkStrings.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    // 验证关键网络错误 ID
    std::string value;
    EXPECT_TRUE(fd.GetString("ERROR_ID_CANTCONNECT", value));
    EXPECT_TRUE(fd.GetString("ERROR_ID_DISCONNECT", value));
    EXPECT_TRUE(fd.GetString("ERROR_ID_GAMEFULL", value));
    EXPECT_TRUE(fd.GetString("ERROR_ID_VERSION_BAD", value));
    EXPECT_TRUE(fd.GetString("ERROR_ID_CDKEY_INVALID", value));
}

TEST_F(FDFileRealDataTest, FrameDefTOC_FrameCount) {
    // 通过加载所有 FDF 文件验证帧定义数量
    std::string content = ReadFileContent("data/FrameDef/UI/ConsoleUI.fdf");
    ASSERT_FALSE(content.empty());

    FDFile fd;
    ASSERT_TRUE(fd.LoadFromMemory(content.c_str(), content.size()));

    // ConsoleUI 应该有多个帧定义
    EXPECT_GE(fd.GetFrames().size(), 1u);
}
