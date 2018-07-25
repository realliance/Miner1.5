#include <glm/gtc/matrix_transform.hpp>
#include "gamecamera.h"
#include "madd.h"
#include "assets/freecam.h"
#include "eventhandler.h"
GameCamera::GameCamera(Madd* context):context(context){
    cameraObj = new FreeCam(context);
    cameraObj->MovePosition(glm::vec3(0.0f,1.0f,-3.0f));
    context->SetMainCamera(cameraObj);
}

GameCamera::~GameCamera(){
   delete cameraObj;
   context->SetMainCamera(NULL);
}

bool GameCamera::Update(){
    cameraObj->Update();
    return true;
}

bool GameCamera::ReloadShaders(){return true;}
bool GameCamera::Render(){return true;}
