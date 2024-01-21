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
		using AppStateMap = std::map<std::string, std::unique_ptr<AppState>>;
		AppStateMap _appStates;
		AppState* _currentState = nullptr;
		AppState* _nextState = nullptr;
		bool _isRunning = false;

	public:
		template<class StateType>
		void AddState(const std::string& stateName)
		{
			static_assert(std::is_base_of_v<AppState, StateType>, "App::AddState must be of type AppState");

			auto [iter, success] = _appStates.try_emplace(stateName, nullptr);
			if (success)
			{
				auto& ptr = iter->second;
				ptr = std::make_unique<StateType>();
				if (!_currentState)
				{
					LOG("App -- CurrentState: %s", iter->first.c_str());
					_currentState = ptr.get();
				}
			}
		}

		void ChangeState(const std::string& stateName);
		void Run(const AppConfig& config);
		void Quit();
	};
}

#endif // __XE_XEPHEINGINE_APP_H__
