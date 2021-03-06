#pragma once

#include "Helpers/NonCopyable.hpp"
#include "Maths/Time.hpp"
#include "ModuleManager.hpp"
#include "ModuleUpdater.hpp"
#include "Log.hpp"
#include "Game.hpp"

/// <summary>
/// The base Acid namespace.
/// </summary>
namespace acid
{
	/// <summary>
	/// Main class for Acid, manages modules and updates. After creating your Engine object call <seealso cref="#Run()"/> to start.
	/// </summary>
	class ACID_EXPORT Engine :
		public NonCopyable
	{
	public:
		/// <summary>
		/// Gets the engines instance.
		/// </summary>
		/// <returns> The current engine instance. </returns>
		static Engine *Get() { return INSTANCE; }

		/// <summary>
		/// Carries out the setup for basic engine components and the engine. Call <seealso cref="#Run()"/> after creating a instance.
		/// </summary>
		/// <param name="argv0"> The first argument passed to main. </param>
		/// <param name="emptyRegister"> If the module register will start empty. </param>
		explicit Engine(std::string argv0, const bool &emptyRegister = false);

		/// <summary>
		/// The update function for the updater.
		/// </summary>
		/// <returns> EXIT_SUCCESS or EXIT_FAILURE. </returns>
		int32_t Run();

		/// <summary>
		/// Gets the module manager used by the engine instance. The manager can be used to register/deregister modules.
		/// </summary>
		/// <returns> The engines module manager. </returns>
		ModuleManager &GetModuleManager() { return m_moduleManager; }

		/// <summary>
		/// Gets the current game.
		/// </summary>
		/// <returns> The renderer manager. </returns>
		Game *GetGame() const { return m_game.get(); }

		/// <summary>
		/// Sets the current game to a new game.
		/// </summary>
		/// <param name="game"> The new game. </param>
		void SetGame(Game *game) { m_game.reset(game); }

		/// <summary>
		/// Gets the current time of the engine instance.
		/// </summary>
		/// <returns> The current engine time. </returns>
		static Time GetTime();

		/// <summary>
		/// Gets the current date time as a string. "%d-%m-%Y %I:%M:%S"
		/// </summary>
		/// <returns> The date time as a string. </returns>
		static std::string GetDateTime();

		/// <summary>
		/// Gets the first argument passed to main.
		/// </summary>
		/// <returns> The first argument passed to main. </returns>
		const std::string &GetArgv0() const { return m_argv0; };

		/// <summary>
		/// Gets the added/removed time for the engine.
		/// </summary>
		/// <returns> The time offset. </returns>
		const Time &GetTimeOffset() const { return m_timeOffset; }

		/// <summary>
		/// Sets the time offset for the engine.
		/// </summary>
		/// <param name="timeOffset"> The new time offset. </param>
		void SetTimeOffset(const Time &timeOffset) { m_timeOffset = timeOffset; }

		/// <summary>
		/// Gets the fps limit.
		/// </summary>
		/// <returns> The fps limit. </returns>
		const float &GetFpsLimit() const { return m_fpsLimit; }

		/// <summary>
		/// Sets the fps limit. -1 disables limits.
		/// </summary>
		/// <param name="fpsLimit"> The new fps limit. </param>
		void SetFpsLimit(const float &fpsLimit) { m_fpsLimit = fpsLimit; }

		/// <summary>
		/// Gets if the engine is running.
		/// </summary>
		/// <returns> If the engine is running. </returns>
		const bool &IsRunning() const { return m_running; }

		/// <summary>
		/// Gets the delta (seconds) between updates.
		/// </summary>
		/// <returns> The delta between updates. </returns>
		const Time &GetDelta() const { return m_moduleUpdater.GetDelta(); }

		/// <summary>
		/// Gets the delta (seconds) between renders.
		/// </summary>
		/// <returns> The delta between renders. </returns>
		const Time &GetDeltaRender() const { return m_moduleUpdater.GetDeltaRender(); }

		/// <summary>
		/// Gets the average UPS over a short interval.
		/// </summary>
		/// <returns> The UPS. </returns>
		const uint32_t &GetUps() const { return m_moduleUpdater.GetUps(); }

		/// <summary>
		/// Gets the average FPS over a short interval.
		/// </summary>
		/// <returns> The FPS. </returns>
		const uint32_t &GetFps() const { return m_moduleUpdater.GetFps(); }

		/// <summary>
		/// Requests the engine to delete and stop the game-loop.
		/// </summary>
		/// <param name="error"> If a bad error occurred. </param>
		void RequestClose(const bool &error);
	private:
		static ACID_STATE Engine *INSTANCE;

		ModuleManager m_moduleManager;
		ModuleUpdater m_moduleUpdater;

		std::unique_ptr<Game> m_game;

		std::string m_argv0;
		Time m_timeOffset;
		float m_fpsLimit;
		bool m_running;
		bool m_error;
	};
}
