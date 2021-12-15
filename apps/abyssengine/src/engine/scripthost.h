#ifndef ABYSS_SCRIPTHOST_H
#define ABYSS_SCRIPTHOST_H

// This must be first for some reason---
#include <sol/sol.hpp>
// -------------------------------------

#include "../node/button.h"
#include "../node/label.h"
#include "../node/sprite.h"
#include "provider.h"
#include "../node/maprenderer.h"
#include <filesystem>

namespace AbyssEngine {

class Engine;

class ScriptHost {
  public:
    explicit ScriptHost(Engine *engine);
    void ExecuteString(std::string_view code);
    void ExecuteFile(std::string_view path);
    void GC();

  private:
    Engine *_engine;

    sol::state _lua;
    sol::environment _environment;

    std::tuple<sol::object, sol::object> LuaLoadString(std::string_view str, std::string_view chunkName);
    std::tuple<sol::object, sol::object> LuaLoadFile(std::string_view pathStr);
    sol::object LuaDoFile(std::string_view path);

    // Script Functions -------------------

    void LuaFuncShutdown();
    std::string_view LuaGetConfig(std::string_view category, std::string_view value);
    void LuaShowSystemCursor(bool show);
    void LuaLog(std::string_view level, std::string_view message);
    void LuaAddLoaderProvider(std::string_view providerType, std::string_view providerPath);
    void LuaCreatePalette(std::string_view paletteName, std::string_view path);
    bool LuaFileExists(std::string_view fileName);
    void LuaResetMouseState();
    void LuaPlayBackgroundMusic(std::string_view fileName);
    std::string LuaLoadText(std::string_view filePath);
    std::unique_ptr<Sprite> LuaCreateSprite(std::string_view spritePath, std::string_view paletteName);
    std::unique_ptr<Button> LuaCreateButton(Sprite &sprite);
    std::unique_ptr<SpriteFont> LuaCreateSpriteFont(std::string_view fontPath, std::string_view paletteName);
    std::unique_ptr<TtfFont> LuaCreateTtfFont(std::string_view fontPath, int size, std::string_view hinting);
    std::unique_ptr<Label> LuaCreateLabel(IFont &font);
    std::unique_ptr<SoundEffect> LuaCreateSoundEffect(std::string_view fileName);
    std::unique_ptr<MapRenderer> LuaCreateMapRenderer();
    std::unique_ptr<LibAbyss::Zone> LuaCreateZone();
    void LuaSetCursor(Sprite &sprite, int offsetX, int offsetY);
    void LuaPlayVideo(std::string_view videoPath, const sol::safe_function& callback);
    void LuaPlayVideoAndAudio(std::string_view videoPath, std::string_view audioPath, const sol::safe_function& callback);
    Node &LuaGetRootNode();
    template <class T, typename X>
    sol::basic_usertype<T, sol::basic_reference<false>> CreateLuaObjectType(sol::table &module, std::string_view name, X &&constructor);
};

} // namespace AbyssEngine

#endif // ABYSS_SCRIPTHOST_H