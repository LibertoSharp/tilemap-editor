#include <gtest/gtest.h>
#include "GUI/GuiElement.h"
#include <SFML/Graphics.hpp>

using namespace gui;

TEST(GuiElementTest, CreationAndVisibility) {
    GuiElement elem(sf::Vector2f(100, 50));
    EXPECT_FALSE(elem.isHidden());
    elem.hide();
    EXPECT_TRUE(elem.isHidden());
    elem.show();
    EXPECT_FALSE(elem.isHidden());
}

TEST(GuiElementTest, ChildrenManagement) {
    GuiElement parent(sf::Vector2f(100, 50));
    GuiElement* child = new GuiElement(sf::Vector2f(10, 10));
    parent.append(child);
    auto children = parent.getChildren();
    ASSERT_EQ(children->size(), 1);
    EXPECT_EQ(children->at(0), child);
    parent.removeChildren(child);
    EXPECT_EQ(children->size(), 1);
    EXPECT_EQ(children->at(0), nullptr);
    delete child;
}

TEST(GuiElementTest, PositionAndAnchor) {
    GuiElement elem(sf::Vector2f(100, 50));
    elem.setAnchor(AnchorType::MiddleCenter);
    elem.setRelativePosition(sf::Vector2f(10, 20));
    EXPECT_EQ(elem.getRelativePosition(), sf::Vector2f(10, 20));
}

TEST(GuiElementTest, BoundingBoxScaleAndOffset) {
    GuiElement elem(sf::Vector2f(100, 50));
    elem.setBoundingBoxScale(sf::Vector2f(2, 2));
    elem.setBoundingBoxOffset(sf::Vector2f(10, 5));
    sf::FloatRect bbox = elem.getBoundingBox(elem.getActiveSprite());

    EXPECT_FLOAT_EQ(bbox.position.x, 0);
    EXPECT_FLOAT_EQ(bbox.position.y, 0);
    EXPECT_FLOAT_EQ(bbox.size.x, 100);
    EXPECT_FLOAT_EQ(bbox.size.y, 50);
}

TEST(GuiElementTest, IsInsideBoundingBoxWithScaleAndOffset) {
    GuiElement elem(sf::Vector2f(100, 50));
    elem.setBoundingBoxScale(sf::Vector2f(2, 2));
    elem.setBoundingBoxOffset(sf::Vector2f(10, 5));

    EXPECT_TRUE(elem.isInsideBoundingBox(sf::Vector2i(109, 54)));

    EXPECT_FALSE(elem.isInsideBoundingBox(sf::Vector2i(9, 4)));
}

TEST(GuiElementTest, ShaderSetAndGet) {
    GuiElement elem(sf::Vector2f(100, 50));
    sf::Shader* shader = new sf::Shader();
    elem.setShader(shader);
    EXPECT_EQ(elem.getShader(), shader);
}
