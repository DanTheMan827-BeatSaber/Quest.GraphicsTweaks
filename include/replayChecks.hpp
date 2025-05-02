/**
 * @file replayChecks.hpp
 * @brief Provides utility functions to check the replay and render states using conditional dependencies.
 */

#include <optional>
#include "conditional-dependencies/shared/main.hpp"

/**
* @brief Checks if the application is currently in a replay state.
*
* This function uses conditional dependencies to check if the game is in a
* replay state according to the Replay mod. It retrieves a function pointer
* to the "IsInReplay" function from the Replay mod and invokes it if
* available.
*
* @return true if the application is in a replay state, false otherwise.
*/
static inline bool IsInReplay() {
  static std::optional<bool (*)()> isInReplayFunc  = CondDeps::Find<bool>("replay", "IsInReplay");

  if (isInReplayFunc.has_value())
  {
    return isInReplayFunc.value()();
  }

  return false;
}

/**
* @brief Checks if the application is currently in a rendering state.
*
* This function uses conditional dependencies to check if the game is in a
* rendering state according to the Replay mod. It retrieves a function pointer
* to the "IsInRender" function from the Replay mod and invokes it if
* available.
*
* @return true if the application is in a replay state, false otherwise.
*/
static inline bool IsInRender() {
  static std::optional<bool (*)()> isInRenderFunc  = CondDeps::Find<bool>("replay", "IsInRender");

  if (isInRenderFunc.has_value())
  {
    return isInRenderFunc.value()();
  }

  return false;
}

#define RENDER_GUARD(callback) \
  if (IsInRender()) { \
    INFO("In render, skipping..."); \
    return callback; \
  }
