#pragma once

#include "common/util/FileUtil.h"
#include "common/util/json_util.h"

#include "SDL3/SDL.h"
#include "game/system/hid/input_bindings.h"
#include "game/system/hid/sdl_util.h"
#include "game/tools/filter_menu/filter_menu.h"

namespace game_settings {

struct KeyWithModifiers {
  u32 key;
  InputModifiers modifiers;

  KeyWithModifiers() = default;
  KeyWithModifiers(u32 k, const InputModifiers& m) : key(k), modifiers(m) {}
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(KeyWithModifiers, key, modifiers)

struct DebugSettings {
  DebugSettings() = default;

  std::string current_version = "1.2";
  std::string version = current_version;

  bool show_imgui = false;
  int imgui_font_size = 16;
  bool monospaced_font = true;
  bool alternate_style = false;
  bool ignore_hide_imgui = false;
  bool treat_pad0_as_pad1 = false;

  std::vector<DebugTextFilter> text_filters = {};
  bool text_check_range = false;
  float text_max_range = 0;

  u32 hide_imgui_key = SDLK_LALT;

  KeyWithModifiers toggle_fullscreen_key =
      KeyWithModifiers(SDLK_RETURN, InputModifiers(SDL_KMOD_ALT));

  void load_settings();
  void save_settings();
};

void to_json(json& j, const DebugSettings& obj);
void from_json(const json& j, DebugSettings& obj);

struct DisplaySettings {
  enum class DisplayMode { Windowed = 0, Fullscreen = 1, Borderless = 2 };

  DisplaySettings();

  std::string current_version = "1.2";
  std::string version = current_version;

  int window_xpos = 50;
  int window_ypos = 50;
  int display_id = 0;
  DisplayMode display_mode = DisplayMode::Borderless;

  void load_settings();
  void save_settings();
};

void to_json(json& j, const DisplaySettings& obj);
void from_json(const json& j, DisplaySettings& obj);

struct InputSettings {
  InputSettings();

  std::string current_version = "1.0";
  std::string version = current_version;

  // NOTE - assumes only port 0
  std::string last_selected_controller_guid = "";
  std::unordered_map<std::string, int> controller_port_mapping;
  std::unordered_map<std::string, InputBindingGroups> controller_binds;
  InputBindingGroups keyboard_binds;
  InputBindingGroups mouse_binds;
  bool keyboard_enabled = false;
  bool enable_trigger_effects = false;
  bool enable_pressure_sensitivity = false;
  float axis_scale = 1.33f;     // multiplies analog stick axis input after reading from drivers.
  float pressure_scale = 1.0f;  // trigger and pressure sensitivity values.
  // not saved or restored, flips on if no controllers are detected
  bool _keyboard_temp_enabled = false;

  void load_settings();
  void save_settings();
};

void to_json(json& j, const InputSettings& obj);
void from_json(const json& j, InputSettings& obj);

}  // namespace game_settings
