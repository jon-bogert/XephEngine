#ifndef __XE_XEPHEINGINE_APP_H__
#define __XE_XEPHEINGINE_APP_H__

namespace xe
{
	class AppState;

	struct AppConfig
	{
		std::wstring appName = L"Window";
		uint32_t winWidth = 1280;
		uint32_t winHeight = 720;
		uint32_t debugDrawLimit = 1000000;
	};

	class App final
	{
	public:
		template<class StateType>
		void AddState(const std::string& stateName)
		{
			static_assert(std::is_base_of_v<AppState, StateType>, "App::AddState must be of type AppState");

			auto [iter, success] = m_appStates.try_emplace(stateName, nullptr);
			if (success)
			{
				auto& ptr = iter->second;
				ptr = std::make_unique<StateType>();
				if (!m_currentState)
				{
					LOG("App -- CurrentState: %s", iter->first.c_str());
					m_currentState = ptr.get();
				}
			}
		}

		void ChangeState(const std::string& stateName);
		void Run(const AppConfig& config);
		void Quit();

	private:
		using AppStateMap = std::map<std::string, std::unique_ptr<AppState>>;
		AppStateMap m_appStates;
		AppState* m_currentState = nullptr;
		AppState* m_nextState = nullptr;
		bool m_isRunning = false;
	};
}

#endif //!__XE_XEPHEINGINE_APP_H__
