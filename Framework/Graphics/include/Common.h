#ifndef __XE_GRAPHICS_COMMON_H__
#define __XE_GRAPHICS_COMMON_H__

#include <Core/include/Core.h>
#include <Math/include/XEMath.h>

#include <d3d11_1.h>
#include <d3dcompiler.h>

#include <ImGui/Inc/imgui.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

template <class T>
inline void SafeRelease(T*& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = nullptr;
	}
}

#endif