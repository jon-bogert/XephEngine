#ifndef __XE_XEPHENGINE_COMMON_H__
#define __XE_XEPHENGINE_COMMON_H__

#include <Core/include/Core.h>
#include <Graphics/include/Graphics.h>
#include <Math/include/XEMath.h>
#include <Physics/include/Physics.h>
#include <Audio/include/Audio.h>

#include "XephInput/include/XephInput/InputSystem.h"
#include "XephInput/include/XephInput/Enums.h"

#define YAML_CPP_STATIC_DEFINE
#include <yaml-cpp/yaml.h>
using yaml_val = YAML::iterator::value_type;

#endif // XE_XEPHENGINE_COMMON_H