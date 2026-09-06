#include <gtest/gtest.h>
#include "FDFile/FDFile.h"
#include <fstream>
#include <sstream>
#include <string>

// ============================================================
// 辅助函数
// ============================================================

static std::string ReadFileContent(const char* relPath) {
    // 从项目根目录读取文件
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

TEST(FDFileTest, ParseXMLSimple) {
    FDFile fd;
    const char* xml = "<Frame name=\"TestFrame\" width=\"100\" height=\"200\"></Frame>";

    EXPECT_TRUE(fd.ParseXML(xml));
    EXPECT_TRUE(fd.IsValid());
    EXPECT_EQ(fd.GetStatus(), FRAMEDEF_STATUS_OK);
}

TEST(FDFileTest, ParseXMLWithChildren) {
    FDFile fd;
    const char* xml = "<Frame>"
                       "<Button/>"
                       "<Texture/>"
                       "</Frame>";

    EXPECT_TRUE(fd.ParseXML(xml));
    EXPECT_TRUE(fd.IsValid());

    const FrameDefNode* root = fd.GetRootNode();
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root->name, "Frame");
    EXPECT_EQ(fd.GetChildCount(root), 2u);
}

TEST(FDFileTest, FindNode) {
    FDFile fd;
    const char* xml = "<Frame>"
                       "<Button/>"
                       "<Texture/>"
                       "</Frame>";

    fd.ParseXML(xml);

    EXPECT_NE(fd.FindNode("Button"), nullptr);
    EXPECT_NE(fd.FindNode("Texture"), nullptr);
    EXPECT_EQ(fd.FindNode("NonExistent"), nullptr);
}

TEST(FDFileTest, GetNodeAttribute) {
    FDFile fd;
    const char* xml = "<Frame width=\"100\" height=\"200\"></Frame>";

    fd.ParseXML(xml);
    const FrameDefNode* node = fd.GetRootNode();

    std::string value;
    EXPECT_TRUE(fd.GetNodeAttribute(node, "width", value));
    EXPECT_EQ(value, "100");

    EXPECT_TRUE(fd.GetNodeAttribute(node, "height", value));
    EXPECT_EQ(value, "200");

    EXPECT_FALSE(fd.GetNodeAttribute(node, "nonexistent", value));
}

TEST(FDFileTest, GetChildCount) {
    FDFile fd;
    const char* xml = "<Frame>"
                       "<Button/>"
                       "<Texture/>"
                       "</Frame>";

    fd.ParseXML(xml);
    const FrameDefNode* root = fd.GetRootNode();

    EXPECT_EQ(fd.GetChildCount(root), 2u);
    EXPECT_EQ(fd.GetChildCount(nullptr), 0u);
}

TEST(FDFileTest, GetChild) {
    FDFile fd;
    const char* xml = "<Frame>"
                       "<Button/>"
                       "<Texture/>"
                       "</Frame>";

    fd.ParseXML(xml);
    const FrameDefNode* root = fd.GetRootNode();

    EXPECT_NE(fd.GetChild(root, 0), nullptr);
    EXPECT_EQ(fd.GetChild(root, 0)->name, "Button");
    EXPECT_NE(fd.GetChild(root, 1), nullptr);
    EXPECT_EQ(fd.GetChild(root, 1)->name, "Texture");
    EXPECT_EQ(fd.GetChild(root, 2), nullptr);
    EXPECT_EQ(fd.GetChild(nullptr, 0), nullptr);
}

TEST(FDFileTest, InvalidXML) {
    FDFile fd;
    EXPECT_FALSE(fd.ParseXML(nullptr));
    EXPECT_FALSE(fd.IsValid());
}

TEST(FDFileTest, MalformedXML) {
    FDFile fd;
    EXPECT_FALSE(fd.ParseXML("Not valid XML"));
    EXPECT_FALSE(fd.IsValid());
}

TEST(FDFileTest, Clear) {
    FDFile fd;
    fd.ParseXML("<Frame name=\"Test\"></Frame>");
    EXPECT_TRUE(fd.IsValid());

    fd.Clear();
    EXPECT_FALSE(fd.IsValid());
    EXPECT_EQ(fd.GetRootNode(), nullptr);
}

TEST(FDFileTest, SelfClosingTag) {
    FDFile fd;
    const char* xml = "<Button width=\"100\"/>";

    EXPECT_TRUE(fd.ParseXML(xml));
    const FrameDefNode* node = fd.GetRootNode();
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->name, "Button");
    EXPECT_EQ(node->attributes.size(), 1u);
}

TEST(FDFileTest, NestedElements) {
    FDFile fd;
    const char* xml = "<Frame>"
                       "<Panel>"
                       "<Button/>"
                       "</Panel>"
                       "</Frame>";

    EXPECT_TRUE(fd.ParseXML(xml));

    const FrameDefNode* root = fd.GetRootNode();
    EXPECT_EQ(root->name, "Frame");
    EXPECT_EQ(fd.GetChildCount(root), 1u);

    const FrameDefNode* panel = fd.GetChild(root, 0);
    EXPECT_NE(panel, nullptr);
    EXPECT_EQ(panel->name, "Panel");
    EXPECT_EQ(fd.GetChildCount(panel), 1u);
}

TEST(FDFileTest, EnumValues) {
    EXPECT_EQ(FRAMEDEF_STATUS_OK, 0);
    EXPECT_EQ(FRAMEDEF_STATUS_ERROR, 1);
    EXPECT_EQ(FRAMEDEF_STATUS_NOT_FOUND, 2);
    EXPECT_EQ(NODE_TYPE_ELEMENT, 0);
    EXPECT_EQ(NODE_TYPE_ATTRIBUTE, 1);
    EXPECT_EQ(NODE_TYPE_TEXT, 2);
}

// ============================================================
// 真实数据文件加载测试
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

    // 验证文件包含预期的字符串定义
    EXPECT_NE(content.find("MONTH_01"), std::string::npos);
    EXPECT_NE(content.find("January"), std::string::npos);
    EXPECT_NE(content.find("DAY_01"), std::string::npos);
    EXPECT_NE(content.find("Sunday"), std::string::npos);
    EXPECT_NE(content.find("StringList"), std::string::npos);
}

TEST_F(FDFileRealDataTest, LoadGlobalStrings) {
    std::string content = ReadFileContent("data/FrameDef/GlobalStrings.fdf");
    ASSERT_FALSE(content.empty()) << "GlobalStrings.fdf not found";

    // 验证关键字符串存在
    EXPECT_NE(content.find("ACCEPT"), std::string::npos);
    EXPECT_NE(content.find("AGILITY"), std::string::npos);
    EXPECT_NE(content.find("ARMOR_HERO"), std::string::npos);
    EXPECT_NE(content.find("StringList"), std::string::npos);
}

TEST_F(FDFileRealDataTest, LoadNetworkStrings) {
    std::string content = ReadFileContent("data/FrameDef/NetworkStrings.fdf");
    ASSERT_FALSE(content.empty()) << "NetworkStrings.fdf not found";

    EXPECT_NE(content.find("ERROR_ID_CANTCONNECT"), std::string::npos);
    EXPECT_NE(content.find("Unable to connect"), std::string::npos);
    EXPECT_NE(content.find("StringList"), std::string::npos);
}

// --- Frame 定义文件测试 ---

TEST_F(FDFileRealDataTest, LoadConsoleUI) {
    std::string content = ReadFileContent("data/FrameDef/UI/ConsoleUI.fdf");
    ASSERT_FALSE(content.empty()) << "ConsoleUI.fdf not found";

    // 验证 Frame 定义结构
    EXPECT_NE(content.find("Frame"), std::string::npos);
    EXPECT_NE(content.find("ConsoleUI"), std::string::npos);
    EXPECT_NE(content.find("Texture"), std::string::npos);
    EXPECT_NE(content.find("File"), std::string::npos);
    EXPECT_NE(content.find("Width"), std::string::npos);
    EXPECT_NE(content.find("Height"), std::string::npos);
    EXPECT_NE(content.find("Anchor"), std::string::npos);
}

TEST_F(FDFileRealDataTest, LoadMainMenu) {
    std::string content = ReadFileContent("data/FrameDef/Glue/MainMenu.fdf");
    ASSERT_FALSE(content.empty()) << "MainMenu.fdf not found";

    // 验证嵌套 Frame 结构
    EXPECT_NE(content.find("MainMenuFrame"), std::string::npos);
    EXPECT_NE(content.find("INHERITS"), std::string::npos);
    EXPECT_NE(content.find("IncludeFile"), std::string::npos);
    EXPECT_NE(content.find("StandardFrameTemplate"), std::string::npos);
    EXPECT_NE(content.find("WarCraftIIILogo"), std::string::npos);
    EXPECT_NE(content.find("SetPoint"), std::string::npos);
}

TEST_F(FDFileRealDataTest, LoadEscMenuMainPanel) {
    std::string content = ReadFileContent("data/FrameDef/UI/EscMenuMainPanel.fdf");
    ASSERT_FALSE(content.empty()) << "EscMenuMainPanel.fdf not found";

    EXPECT_NE(content.find("Frame"), std::string::npos);
    EXPECT_NE(content.find("TEXT"), std::string::npos);
    EXPECT_NE(content.find("GLUETEXTBUTTON"), std::string::npos);
}

TEST_F(FDFileRealDataTest, LoadResourceBar) {
    std::string content = ReadFileContent("data/FrameDef/UI/ResourceBar.fdf");
    ASSERT_FALSE(content.empty()) << "ResourceBar.fdf not found";

    EXPECT_NE(content.find("Frame"), std::string::npos);
    EXPECT_NE(content.find("Texture"), std::string::npos);
}

TEST_F(FDFileRealDataTest, LoadAllianceDialog) {
    std::string content = ReadFileContent("data/FrameDef/UI/AllianceDialog.fdf");
    ASSERT_FALSE(content.empty()) << "AllianceDialog.fdf not found";

    EXPECT_NE(content.find("Frame"), std::string::npos);
    EXPECT_NE(content.find("AllianceDialog"), std::string::npos);
    EXPECT_NE(content.find("DIALOG"), std::string::npos);
    EXPECT_NE(content.find("DialogBackdrop"), std::string::npos);
}

// --- FrameDef.toc 目录文件测试 ---

TEST_F(FDFileRealDataTest, LoadFrameDefTOC) {
    std::string content = ReadFileContent("data/FrameDef/FrameDef.toc");
    ASSERT_FALSE(content.empty()) << "FrameDef.toc not found";

    // 验证 TOC 包含所有子目录的文件引用
    EXPECT_NE(content.find("GlobalStrings.fdf"), std::string::npos);
    EXPECT_NE(content.find("NetworkStrings.fdf"), std::string::npos);
    EXPECT_NE(content.find("DateStrings.fdf"), std::string::npos);
    EXPECT_NE(content.find("Glue\\"), std::string::npos);
    EXPECT_NE(content.find("UI\\"), std::string::npos);
}

// --- 批量加载所有 FDF 文件 ---

TEST_F(FDFileRealDataTest, LoadAllGlueFDFs) {
    // 测试所有 Glue 目录下的 FDF 文件可以被读取
    const char* glueFiles[] = {
        "data/FrameDef/Glue/MainMenu.fdf",
        "data/FrameDef/Glue/OptionsMenu.fdf",
        "data/FrameDef/Glue/SinglePlayerMenu.fdf",
        "data/FrameDef/Glue/Loading.fdf",
        "data/FrameDef/Glue/DialogWar3.fdf",
        "data/FrameDef/Glue/StandardTemplates.fdf",
        "data/FrameDef/Glue/ListBoxWar3.fdf",
        "data/FrameDef/Glue/MapListBox.fdf",
        "data/FrameDef/Glue/Skirmish.fdf",
        "data/FrameDef/Glue/TeamSetup.fdf",
        "data/FrameDef/Glue/ScoreScreen.fdf",
        "data/FrameDef/Glue/BattleNetMain.fdf",
        "data/FrameDef/Glue/BattleNetTemplates.fdf",
    };

    for (const char* path : glueFiles) {
        std::string content = ReadFileContent(path);
        EXPECT_FALSE(content.empty()) << "Failed to load: " << path;
        if (!content.empty()) {
            EXPECT_NE(content.find("Frame"), std::string::npos)
                << "No Frame definition in: " << path;
        }
    }
}

TEST_F(FDFileRealDataTest, LoadAllUIFDFs) {
    // 测试所有 UI 目录下的 FDF 文件可以被读取
    const char* uiFiles[] = {
        "data/FrameDef/UI/ConsoleUI.fdf",
        "data/FrameDef/UI/ResourceBar.fdf",
        "data/FrameDef/UI/SimpleInfoPanel.fdf",
        "data/FrameDef/UI/UpperButtonBar.fdf",
        "data/FrameDef/UI/EscMenuMainPanel.fdf",
        "data/FrameDef/UI/AllianceDialog.fdf",
        "data/FrameDef/UI/ChatDialog.fdf",
        "data/FrameDef/UI/LogDialog.fdf",
        "data/FrameDef/UI/QuestDialog.fdf",
        "data/FrameDef/UI/ReplayPanel.fdf",
        "data/FrameDef/UI/TimerDialog.fdf",
        "data/FrameDef/UI/SuspendDialog.fdf",
        "data/FrameDef/UI/UnresponsiveDialog.fdf",
        "data/FrameDef/UI/GameResultDialog.fdf",
        "data/FrameDef/UI/ScriptDialog.fdf",
    };

    for (const char* path : uiFiles) {
        std::string content = ReadFileContent(path);
        EXPECT_FALSE(content.empty()) << "Failed to load: " << path;
        if (!content.empty()) {
            EXPECT_NE(content.find("Frame"), std::string::npos)
                << "No Frame definition in: " << path;
        }
    }
}

// ============================================================
// FDF 格式特征验证测试
// ============================================================

TEST_F(FDFileRealDataTest, FDF_HasFrameSyntax) {
    // 验证 FDF 使用 Frame "TYPE" "NAME" { } 语法而非 XML
    std::string content = ReadFileContent("data/FrameDef/UI/ConsoleUI.fdf");
    ASSERT_FALSE(content.empty());

    // FDF 格式特征：Frame 关键字后跟引号包裹的类型和名称
    EXPECT_NE(content.find("Frame \""), std::string::npos)
        << "FDF should use Frame \"TYPE\" syntax";

    // 不应包含 XML 标签
    EXPECT_EQ(content.find("<Frame"), std::string::npos)
        << "FDF should not contain XML tags";
}

TEST_F(FDFileRealDataTest, FDF_HasStringListSyntax) {
    // 验证 StringList 使用自定义语法
    std::string content = ReadFileContent("data/FrameDef/DateStrings.fdf");
    ASSERT_FALSE(content.empty());

    EXPECT_NE(content.find("StringList {"), std::string::npos)
        << "StringList should use { } syntax";

    // 验证 KEY "VALUE", 格式
    EXPECT_NE(content.find("MONTH_01"), std::string::npos);
}

TEST_F(FDFileRealDataTest, FDF_HasIncludeFile) {
    // 验证 IncludeFile 指令
    std::string content = ReadFileContent("data/FrameDef/Glue/MainMenu.fdf");
    ASSERT_FALSE(content.empty());

    EXPECT_NE(content.find("IncludeFile"), std::string::npos)
        << "FDF should support IncludeFile directive";
}

TEST_F(FDFileRealDataTest, FDF_HasInherits) {
    // 验证 INHERITS 继承语法
    std::string content = ReadFileContent("data/FrameDef/Glue/MainMenu.fdf");
    ASSERT_FALSE(content.empty());

    EXPECT_NE(content.find("INHERITS"), std::string::npos)
        << "FDF should support INHERITS syntax";
}

TEST_F(FDFileRealDataTest, FDF_HasComments) {
    // 验证注释格式 (// 和 /* */)
    std::string content = ReadFileContent("data/FrameDef/DateStrings.fdf");
    ASSERT_FALSE(content.empty());

    EXPECT_NE(content.find("/*"), std::string::npos)
        << "FDF should support /* */ comments";
    EXPECT_NE(content.find("//"), std::string::npos)
        << "FDF should support // comments";
}

TEST_F(FDFileRealDataTest, FDF_HasNestedFrames) {
    // 验证嵌套 Frame 结构
    std::string content = ReadFileContent("data/FrameDef/UI/ConsoleUI.fdf");
    ASSERT_FALSE(content.empty());

    // ConsoleUI 有多个嵌套的 Texture Frame
    size_t textureCount = 0;
    size_t pos = 0;
    while ((pos = content.find("Texture {", pos)) != std::string::npos) {
        textureCount++;
        pos++;
    }
    EXPECT_GE(textureCount, 4u)
        << "ConsoleUI should have multiple nested Texture frames";
}

TEST_F(FDFileRealDataTest, FDF_HasFrameTypes) {
    // 验证多种 Frame 类型
    std::string content = ReadFileContent("data/FrameDef/Glue/MainMenu.fdf");
    ASSERT_FALSE(content.empty());

    EXPECT_NE(content.find("Frame \"FRAME\""), std::string::npos);
    EXPECT_NE(content.find("Frame \"TEXT\""), std::string::npos);
    EXPECT_NE(content.find("Frame \"SPRITE\""), std::string::npos);
    EXPECT_NE(content.find("Frame \"BACKDROP\""), std::string::npos);
    EXPECT_NE(content.find("Frame \"GLUETEXTBUTTON\""), std::string::npos);
}

TEST_F(FDFileRealDataTest, FDF_HasSetPoint) {
    // 验证 SetPoint 布局语法
    std::string content = ReadFileContent("data/FrameDef/Glue/MainMenu.fdf");
    ASSERT_FALSE(content.empty());

    EXPECT_NE(content.find("SetPoint"), std::string::npos);
    EXPECT_NE(content.find("TOPLEFT"), std::string::npos);
    EXPECT_NE(content.find("BOTTOMLEFT"), std::string::npos);
}

TEST_F(FDFileRealDataTest, FDF_HasTextProperties) {
    // 验证文本属性
    std::string content = ReadFileContent("data/FrameDef/Glue/MainMenu.fdf");
    ASSERT_FALSE(content.empty());

    EXPECT_NE(content.find("Text \""), std::string::npos);
    EXPECT_NE(content.find("FontColor"), std::string::npos);
    EXPECT_NE(content.find("FontJustificationH"), std::string::npos);
}

TEST_F(FDFileRealDataTest, FDF_HasTextureProperties) {
    // 验证纹理属性
    std::string content = ReadFileContent("data/FrameDef/UI/ConsoleUI.fdf");
    ASSERT_FALSE(content.empty());

    EXPECT_NE(content.find("File \""), std::string::npos);
    EXPECT_NE(content.find("TexCoord"), std::string::npos);
    EXPECT_NE(content.find("AlphaMode"), std::string::npos);
}

// ============================================================
// 数据完整性验证测试
// ============================================================

TEST_F(FDFileRealDataTest, DateStrings_CompleteMonths) {
    std::string content = ReadFileContent("data/FrameDef/DateStrings.fdf");
    ASSERT_FALSE(content.empty());

    // 验证12个月份都有定义
    const char* months[] = {
        "MONTH_01", "MONTH_02", "MONTH_03", "MONTH_04",
        "MONTH_05", "MONTH_06", "MONTH_07", "MONTH_08",
        "MONTH_09", "MONTH_10", "MONTH_11", "MONTH_12"
    };
    for (const char* month : months) {
        EXPECT_NE(content.find(month), std::string::npos)
            << "Missing month: " << month;
    }
}

TEST_F(FDFileRealDataTest, DateStrings_CompleteDays) {
    std::string content = ReadFileContent("data/FrameDef/DateStrings.fdf");
    ASSERT_FALSE(content.empty());

    // 验证7天都有定义
    const char* days[] = {
        "DAY_01", "DAY_02", "DAY_03", "DAY_04",
        "DAY_05", "DAY_06", "DAY_07"
    };
    for (const char* day : days) {
        EXPECT_NE(content.find(day), std::string::npos)
            << "Missing day: " << day;
    }
}

TEST_F(FDFileRealDataTest, GlobalStrings_ArmorTypes) {
    std::string content = ReadFileContent("data/FrameDef/GlobalStrings.fdf");
    ASSERT_FALSE(content.empty());

    // 验证护甲类型定义完整
    EXPECT_NE(content.find("ARMOR_FORT"), std::string::npos);
    EXPECT_NE(content.find("ARMOR_HERO"), std::string::npos);
    EXPECT_NE(content.find("ARMOR_LARGE"), std::string::npos);
    EXPECT_NE(content.find("ARMOR_MEDIUM"), std::string::npos);
    EXPECT_NE(content.find("ARMOR_NORMAL"), std::string::npos);
    EXPECT_NE(content.find("ARMOR_SMALL"), std::string::npos);
    EXPECT_NE(content.find("ARMOR_DIVINE"), std::string::npos);
}

TEST_F(FDFileRealDataTest, NetworkStrings_ErrorIDs) {
    std::string content = ReadFileContent("data/FrameDef/NetworkStrings.fdf");
    ASSERT_FALSE(content.empty());

    // 验证关键网络错误 ID
    EXPECT_NE(content.find("ERROR_ID_CANTCONNECT"), std::string::npos);
    EXPECT_NE(content.find("ERROR_ID_DISCONNECT"), std::string::npos);
    EXPECT_NE(content.find("ERROR_ID_GAMEFULL"), std::string::npos);
    EXPECT_NE(content.find("ERROR_ID_VERSION_BAD"), std::string::npos);
    EXPECT_NE(content.find("ERROR_ID_CDKEY_INVALID"), std::string::npos);
}

TEST_F(FDFileRealDataTest, FrameDefTOC_FileCount) {
    std::string content = ReadFileContent("data/FrameDef/FrameDef.toc");
    ASSERT_FALSE(content.empty());

    // 统计文件引用数量
    int lineCount = 0;
    std::istringstream stream(content);
    std::string line;
    while (std::getline(stream, line)) {
        if (!line.empty() && line[0] != '\r') {
            lineCount++;
        }
    }

    // FrameDef.toc 应该引用了大量文件
    EXPECT_GE(lineCount, 50)
        << "FrameDef.toc should reference at least 50 FDF files";
}
