#include <gtest/gtest.h>
#include "FDFile/FDFile.h"

TEST(FDFileTest, DefaultConstructor) {
    FDFile fd;
    // Default constructor doesn't parse any XML, so IsValid() returns false
    EXPECT_FALSE(fd.IsValid());
    EXPECT_EQ(fd.GetStatus(), FRAMEDEF_STATUS_OK);
    EXPECT_STREQ(fd.GetErrorMessage(), "");
}

TEST(FDFileTest, ParseXML) {
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

    const FrameDefNode* btn = fd.FindNode("Button");
    EXPECT_NE(btn, nullptr);
    EXPECT_EQ(btn->name, "Button");

    const FrameDefNode* tex = fd.FindNode("Texture");
    EXPECT_NE(tex, nullptr);
    EXPECT_EQ(tex->name, "Texture");

    const FrameDefNode* notFound = fd.FindNode("NonExistent");
    EXPECT_EQ(notFound, nullptr);
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

    const FrameDefNode* child0 = fd.GetChild(root, 0);
    EXPECT_NE(child0, nullptr);
    EXPECT_EQ(child0->name, "Button");

    const FrameDefNode* child1 = fd.GetChild(root, 1);
    EXPECT_NE(child1, nullptr);
    EXPECT_EQ(child1->name, "Texture");

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
    EXPECT_TRUE(fd.IsValid());

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
    EXPECT_TRUE(fd.IsValid());

    const FrameDefNode* root = fd.GetRootNode();
    EXPECT_EQ(root->name, "Frame");
    EXPECT_EQ(fd.GetChildCount(root), 1u);

    const FrameDefNode* panel = fd.GetChild(root, 0);
    EXPECT_NE(panel, nullptr);
    EXPECT_EQ(panel->name, "Panel");
    EXPECT_EQ(fd.GetChildCount(panel), 1u);
}

TEST(FDFileTest, FrameDefStatusValues) {
    EXPECT_EQ(FRAMEDEF_STATUS_OK, 0);
    EXPECT_EQ(FRAMEDEF_STATUS_ERROR, 1);
    EXPECT_EQ(FRAMEDEF_STATUS_NOT_FOUND, 2);
}

TEST(FDFileTest, FrameDefNodeTypeValues) {
    EXPECT_EQ(NODE_TYPE_ELEMENT, 0);
    EXPECT_EQ(NODE_TYPE_ATTRIBUTE, 1);
    EXPECT_EQ(NODE_TYPE_TEXT, 2);
}
