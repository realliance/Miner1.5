#pragma once
#include <glm/glm.hpp>
#include <assets/freecamcomponent.h>
#include <components/keyboardeventcomponent.h>
#include <components/mouseeventcomponent.h>
class Madd;
class GameCamera{
public:
  GameCamera();
  void Unregister();
  static void HandleEvent(Component* c, WindowComponent* window, int key, int action);
  FreecamComponent camera;
private:
  KeyboardEventComponent mouselockEvent;
  MouseEventComponent mouseMovementEvent;
  KeyboardEventComponent keyboardMovementEvent[6];
  
};

