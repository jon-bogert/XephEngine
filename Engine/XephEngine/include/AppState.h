#ifndef __XE_XEPHEINGINE_APPSTATE_H__
#define __XE_XEPHEINGINE_APPSTATE_H__

namespace xe
{
	class AppState
	{
	public:
		virtual ~AppState() = default;
		virtual void Initialize() {}
		virtual void Terminate() {}
		virtual void Update(const float& deltaTime) {}
		virtual void Draw() {}
		virtual void DebugUI() {}
	};
}

#endif