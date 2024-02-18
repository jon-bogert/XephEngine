#ifndef __XE_XEPHENGINE_ANIMATORCOMPONENT_H__
#define __XE_XEPHENGINE_ANIMATORCOMPONENT_H__

#include "Component.h"

namespace xe
{
	class AnimatorComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::Animator);

		void Initialize() override;
		void Terminate() override;

		void Update(const float deltaTime) override;
		void DebugUI() override;

		bool Play(int index, bool looping = false);

		Graphics::Animator& GetAnimator() { return m_animator; }
		const Graphics::Animator& GetAnimator() const { return m_animator; }

	private:
		Graphics::Animator m_animator;
	};
}

#endif //!__XE_XEPHENGINE_ANIMATORCOMPONENT_H__
