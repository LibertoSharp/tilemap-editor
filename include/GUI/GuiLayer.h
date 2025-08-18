#ifndef GUILAYER_H
#define GUILAYER_H
#include "GUI/GuiElement.h"
#include "AnchorsType.h"
namespace gui {
  struct GuiEventContext {
    sf::Vector2i mousePos;
    bool f_hovering = false;
    bool f_clickDown = false;
    bool f_clickUp = false;
    bool f_mouseDown = false;
    bool is_inside_window = false;
    float mouse_wheel_delta = 0;
    char32_t textEntered;
    Keyboard::Key keyPressed;

    void Reset() {
      mousePos = {};
      f_hovering = false;
      f_clickDown = false;
      f_clickUp = false;
      f_mouseDown = false;
      is_inside_window = false;
      mouse_wheel_delta = 0;
      textEntered = -1;
      keyPressed = Keyboard::Key::Unknown;
    }
  };

  class GuiLayer : public Drawable{
  public:
    explicit GuiLayer(int reserveAmount = 3);
    explicit GuiLayer(Window* window, int reserveAmount = 3);
    ~GuiLayer() override {removeAllElements();}
    void addElement(GuiElement* element, bool keepWorldPos);
    void removeElement(GuiElement* element);
    void removeAllElements();
    Vector2f getPositionRelativeToAnchor(AnchorType anchor);

    void draw(RenderTarget& target, RenderStates states) const override;

    bool callEvents();

    GuiEventContext ctx;
  private:
    std::vector<GuiElement*> elements;
    Window* window;
  };
}


#endif //GUILAYER_H
