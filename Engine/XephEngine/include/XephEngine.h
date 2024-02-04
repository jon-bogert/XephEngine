#ifndef __XE_XEPHENGINE_XEPHENGINE_H__
#define __XE_XEPHENGINE_XEPHENGINE_H__

#include "Common.h"

#include "App.h"
#include "AppState.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "TypeIDs.h"
#include "World.h"

//Components
#include "CameraComponent.h"
#include "Component.h"
#include "MeshComponent.h"
#include "ModelComponent.h"
#include "TransformComponent.h"

//Services
#include "CameraService.h"
#include "RenderService.h"
#include "Service.h"
#include "UpdateService.h"

namespace xe
{
	App& MainApp();
}

#endif // __XE_XEPHENGINE_XEPHENGINE_H__
