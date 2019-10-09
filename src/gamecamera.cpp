#include <glm/gtc/matrix_transform.hpp>
#include <gamecamera.h>
#include <madd.h>
#include <assets/freecamsystem.h>
#include <components/windowcomponent.h>
#include <keyboardeventsystem.h>
#include <mouseeventsystem.h>
#include <keycodes.h>

GameCamera::GameCamera() {
  camera = FreeCamSystem::Construct();

  mouseMovementEvent = MouseEventComponent{};
  mouseMovementEvent.c = &camera;
  mouseMovementEvent.callback = [](Component* c, WindowComponent* window, float posX, float posY){
    dynamic_cast<FreecamComponent*>(c)->cursor = glm::vec2(posX,posY);
  };
  MouseEventSystem::GetInstance().Register(&mouseMovementEvent);

  mouselockEvent = KeyboardEventComponent{};
  mouselockEvent.c = &camera;
  mouselockEvent.callback = [](Component* c, WindowComponent* window, int key, int action){
    FreeCamSystem::ToggleMouseLock(*dynamic_cast<FreecamComponent*>(c), window, key, action);
  };
  mouselockEvent.code = KEY_TAB;
  KeyboardEventSystem::GetInstance().Register(&mouselockEvent);
  std::vector codes = {KEY_W,KEY_A,KEY_S,KEY_D,KEY_LEFT_SHIFT,KEY_LEFT_CONTROL};
  for(int i = 0; i < 6; i++){
    keyboardMovementEvent[i] = KeyboardEventComponent{};
    keyboardMovementEvent[i].c = &camera;
    keyboardMovementEvent[i].callback = GameCamera::HandleEvent;
    keyboardMovementEvent[i].code = codes[i];
    KeyboardEventSystem::GetInstance().Register(&keyboardMovementEvent[i]);
  }
  Madd::GetInstance().GetSystem("FreeCamSystem")->Register(&camera);
}

void GameCamera::HandleEvent(Component* _c, WindowComponent* window, int key, int action){
  FreecamComponent* c = dynamic_cast<FreecamComponent*>(_c);
  switch (action){
  case KEY_PRESS:
    action = 1;
    break;
  case KEY_REPEAT:
    return;
  break;
  case KEY_UP:
    action = 0;
  break;
  default:
    break;
  }
  switch (key){
  case KEY_W:
    c->movVector.z = action;
    break;
  case KEY_S:
    c->movVector.z = -action;
    break;
  case KEY_A:
    c->movVector.x = -action;
    break;
  case KEY_D:
    c->movVector.x = action;
    break;
  case KEY_LEFT_SHIFT:
    c->movVector.y = action;
    break;
  case KEY_LEFT_CONTROL:
    c->movVector.y = -action;
    break;
  default:
    break;
  }
}

void GameCamera::Unregister(){
  MouseEventSystem::GetInstance().Unregister(&mouseMovementEvent);
  KeyboardEventSystem::GetInstance().Unregister(&mouselockEvent);
  for(int i = 0; i < 6; i++){
    KeyboardEventSystem::GetInstance().Unregister(&keyboardMovementEvent[i]);
  }
}
