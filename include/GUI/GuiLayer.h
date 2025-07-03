#ifndef GUILAYER_H
#define GUILAYER_H
#include "GUI/GuiElement.h"
#include "AnchorsType.h"

struct GuiEventContext {
  sf::Vector2i mousePos;
  bool clickDown = false;
  bool clickUp = false;
  bool mouseDown = false;
};

class GuiLayer : public Drawable{
public:
  explicit GuiLayer(int reserveAmount = 3);
  explicit GuiLayer(Window* window, int reserveAmount = 3);
  void AddElement(GuiElement* element);
  void RemoveElement(GuiElement* element);
  void RemoveAllElements();
  Vector2f GetPositionRelativeToAnchor(AnchorType anchor);

  void draw(RenderTarget& target, RenderStates states) const override;

  void callEvents(GuiEventContext ctx);

private:
  std::vector<GuiElement*> elements;
  Window* window;
};



#endif //GUILAYER_H
