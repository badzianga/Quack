#include "Quack/Core/Input.hpp"
#include "Quack/Core/Keyboard.hpp"
#include "Quack/Core/Mouse.hpp"
#include "Quack/Core/Time.hpp"
#include "Quack/Math/Vector3.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/ScriptComponent.hpp"
#include "Quack/Scene/Transform.hpp"
#include "Quack/Utils/Logger.hpp"

void ScriptComponent::start() {
    loadScript();

    if (m_onStart.valid()) {
        m_onStart();
    }
}

void ScriptComponent::update() {
    if (m_onUpdate.valid()) {
        m_onUpdate(Time::getDeltaTime());
    }
}

void ScriptComponent::loadScript() {
    m_lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);

    sol::load_result script = m_lua.load_file(scriptPath);
    if (!script.valid()) {
        sol::error err = script;
        Logger::error("Script error: " + std::string(err.what()));
        return;
    }

    m_lua.new_usertype<Vector3>("Vector3",
        sol::constructors<Vector3(), Vector3(float), Vector3(float, float, float)>(),
        "x", &Vector3::x,
        "y", &Vector3::y,
        "z", &Vector3::z
    );

    m_lua.new_usertype<Vector2>("Vector2",
        sol::constructors<Vector2(), Vector2(float), Vector2(float, float)>(),
        "x", &Vector2::x,
        "y", &Vector2::y
);

    m_lua.new_usertype<Transform>("Transform",
        sol::constructors<Transform()>(),
        "position", &Transform::position,
        "rotation", &Transform::rotation,
        "scale", &Transform::scale
    );

    m_lua.new_usertype<GameObject>("GameObject",
        "transform", &GameObject::transform
    );

    m_lua["MouseButton"] = m_lua.create_table_with(
        "Left",   Mouse::Button::Left,
        "Right",  Mouse::Button::Right,
        "Middle", Mouse::Button::Middle
    );

    m_lua["KeyboardKey"] = m_lua.create_table_with(
        "Space",        Keyboard::Key::Space,
        "Apostrophe",   Keyboard::Key::Apostrophe,
        "Comma",        Keyboard::Key::Comma,
        "Minus",        Keyboard::Key::Minus,
        "Period",       Keyboard::Key::Period,
        "Slash",        Keyboard::Key::Slash,
        "Num0",         Keyboard::Key::Num0,
        "Num1",         Keyboard::Key::Num1,
        "Num2",         Keyboard::Key::Num2,
        "Num3",         Keyboard::Key::Num3,
        "Num4",         Keyboard::Key::Num4,
        "Num5",         Keyboard::Key::Num5,
        "Num6",         Keyboard::Key::Num6,
        "Num7",         Keyboard::Key::Num7,
        "Num8",         Keyboard::Key::Num8,
        "Num9",         Keyboard::Key::Num9,
        "Semicolon",    Keyboard::Key::Semicolon,
        "Equal",        Keyboard::Key::Equal,
        "A",            Keyboard::Key::A,
        "B",            Keyboard::Key::B,
        "C",            Keyboard::Key::C,
        "D",            Keyboard::Key::D,
        "E",            Keyboard::Key::E,
        "F",            Keyboard::Key::F,
        "G",            Keyboard::Key::G,
        "H",            Keyboard::Key::H,
        "I",            Keyboard::Key::I,
        "J",            Keyboard::Key::J,
        "K",            Keyboard::Key::K,
        "L",            Keyboard::Key::L,
        "M",            Keyboard::Key::M,
        "N",            Keyboard::Key::N,
        "O",            Keyboard::Key::O,
        "P",            Keyboard::Key::P,
        "Q",            Keyboard::Key::Q,
        "R",            Keyboard::Key::R,
        "S",            Keyboard::Key::S,
        "T",            Keyboard::Key::T,
        "U",            Keyboard::Key::U,
        "V",            Keyboard::Key::V,
        "W",            Keyboard::Key::W,
        "X",            Keyboard::Key::X,
        "Y",            Keyboard::Key::Y,
        "Z",            Keyboard::Key::Z,
        "Escape",       Keyboard::Key::Escape,
        "Enter",        Keyboard::Key::Enter,
        "Tab",          Keyboard::Key::Tab,
        "Backspace",    Keyboard::Key::Backspace,
        "Insert",       Keyboard::Key::Insert,
        "Delete",       Keyboard::Key::Delete,
        "Right",        Keyboard::Key::Right,
        "Left",         Keyboard::Key::Left,
        "Down",         Keyboard::Key::Down,
        "Up",           Keyboard::Key::Up,
        "PageUp",       Keyboard::Key::PageUp,
        "PageDown",     Keyboard::Key::PageDown,
        "Home",         Keyboard::Key::Home,
        "End",          Keyboard::Key::End,
        "CapsLock",     Keyboard::Key::CapsLock,
        "ScrollLock",   Keyboard::Key::ScrollLock,
        "NumLock",      Keyboard::Key::NumLock,
        "PrintScreen",  Keyboard::Key::PrintScreen,
        "Pause",        Keyboard::Key::Pause,
        "F1",           Keyboard::Key::F1,
        "F2",           Keyboard::Key::F2,
        "F3",           Keyboard::Key::F3,
        "F4",           Keyboard::Key::F4,
        "F5",           Keyboard::Key::F5,
        "F6",           Keyboard::Key::F6,
        "F7",           Keyboard::Key::F7,
        "F8",           Keyboard::Key::F8,
        "F9",           Keyboard::Key::F9,
        "F10",          Keyboard::Key::F10,
        "F11",          Keyboard::Key::F11,
        "F12",          Keyboard::Key::F12,
        "LeftShift",    Keyboard::Key::LeftShift,
        "LeftControl",  Keyboard::Key::LeftControl,
        "LeftAlt",      Keyboard::Key::LeftAlt,
        "RightShift",   Keyboard::Key::RightShift,
        "RightControl", Keyboard::Key::RightControl,
        "RightAlt",     Keyboard::Key::RightAlt,
        "Menu",         Keyboard::Key::Menu
    );

    m_lua["Input"] = m_lua.create_table_with(
        "isKeyPressed", &Input::isKeyPressed,
        "isKeyReleased", &Input::isKeyReleased,
        "isKeyDown", &Input::isKeyDown,
        "isButtonPressed", &Input::isButtonPressed,
        "getMousePosition", &Input::getMousePosition
    );

    script();

    m_onStart = m_lua["onStart"];
    m_onUpdate = m_lua["onUpdate"];
    m_lua["gameObject"] = gameObject;
}
