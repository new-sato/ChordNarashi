#include "SDLButtonChecker.hpp"

SDLButtonChecker::SDLButtonChecker(Idisplay& display)
    : m_display(display)
{
}

bool SDLButtonChecker::checkButton(SDL_Scancode key)
{
    return m_display.isKeyPressed(key);
}

void SDLButtonChecker::updateChordButtons()
{
    const auto& virtual_buttons = m_display.getVirtualChordButtons();

    // Major
    auto& cb_Major = m_real_buttons.chordButtons.at(ChordButtonType::Major);
    for (int i = 0; i < 12; i++) {
        cb_Major[i] = virtual_buttons[0][i];
    }
    cb_Major[static_cast<int>(Note::C)] = cb_Major[static_cast<int>(Note::C)] || checkButton(SDL_SCANCODE_E);
    cb_Major[static_cast<int>(Note::G)] = cb_Major[static_cast<int>(Note::G)] || checkButton(SDL_SCANCODE_R);
    cb_Major[static_cast<int>(Note::D)] = cb_Major[static_cast<int>(Note::D)] || checkButton(SDL_SCANCODE_T);
    cb_Major[static_cast<int>(Note::F)] = cb_Major[static_cast<int>(Note::F)] || checkButton(SDL_SCANCODE_W);

    // minor
    auto& cb_minor = m_real_buttons.chordButtons.at(ChordButtonType::minor);
    for (int i = 0; i < 12; i++) {
        cb_minor[i] = virtual_buttons[1][i];
    }
    cb_minor[static_cast<int>(Note::C)] = cb_minor[static_cast<int>(Note::C)] || checkButton(SDL_SCANCODE_D);
    cb_minor[static_cast<int>(Note::G)] = cb_minor[static_cast<int>(Note::G)] || checkButton(SDL_SCANCODE_F);
    cb_minor[static_cast<int>(Note::D)] = cb_minor[static_cast<int>(Note::D)] || checkButton(SDL_SCANCODE_G);
    cb_minor[static_cast<int>(Note::F)] = cb_minor[static_cast<int>(Note::F)] || checkButton(SDL_SCANCODE_S);
    
    // dim
    auto& cb_dim = m_real_buttons.chordButtons.at(ChordButtonType::dim);
    for (int i = 0; i < 12; i++) {
        cb_dim[i] = virtual_buttons[2][i];
    }
    cb_dim[static_cast<int>(Note::C)] = cb_dim[static_cast<int>(Note::C)] || checkButton(SDL_SCANCODE_C);
    cb_dim[static_cast<int>(Note::G)] = cb_dim[static_cast<int>(Note::G)] || checkButton(SDL_SCANCODE_V);
    cb_dim[static_cast<int>(Note::D)] = cb_dim[static_cast<int>(Note::D)] || checkButton(SDL_SCANCODE_B);
    cb_dim[static_cast<int>(Note::F)] = cb_dim[static_cast<int>(Note::F)] || checkButton(SDL_SCANCODE_X);

    // arg
    auto& cb_arg = m_real_buttons.chordButtons.at(ChordButtonType::arg);
    for (int i = 0; i < 12; i++) {
        cb_arg[i] = false;
    }
    cb_arg[static_cast<int>(Note::C)] = checkButton(SDL_SCANCODE_3);
    cb_arg[static_cast<int>(Note::G)] = checkButton(SDL_SCANCODE_4);
    cb_arg[static_cast<int>(Note::D)] = checkButton(SDL_SCANCODE_5);
    cb_arg[static_cast<int>(Note::F)] = checkButton(SDL_SCANCODE_2);
}

void SDLButtonChecker::updateShiftButtons()
{
    m_real_buttons.tempShihftButtons[9] = checkButton(SDL_SCANCODE_Z);
    m_real_buttons.tempShihftButtons[3] = checkButton(SDL_SCANCODE_A);
    m_real_buttons.tempShihftButtons[6] = checkButton(SDL_SCANCODE_Q);
}

void SDLButtonChecker::updateKeyButtons()
{
    m_keyButtons[1].setState(checkButton(SDL_SCANCODE_RIGHT) || checkButton(SDL_SCANCODE_L));
    m_keyButtons[11].setState(checkButton(SDL_SCANCODE_LEFT) || checkButton(SDL_SCANCODE_J));
    m_keyButtons[7].setState(checkButton(SDL_SCANCODE_UP) || checkButton(SDL_SCANCODE_O));
    m_keyButtons[5].setState(checkButton(SDL_SCANCODE_DOWN) || checkButton(SDL_SCANCODE_M));
    m_keyButtons[3].setState(checkButton(SDL_SCANCODE_SEMICOLON));
    m_keyButtons[9].setState(checkButton(SDL_SCANCODE_H));
}

void SDLButtonChecker::updateModeButtons()
{
    m_signature_mode_button.setState(checkButton(SDL_SCANCODE_0));
}

bool SDLButtonChecker::isRingButtonPressed()
{
    return checkButton(SDL_SCANCODE_K) || m_display.isVirtualRingButtonPressed();
}

bool SDLButtonChecker::isSustainButtonPressed()
{
    return checkButton(SDL_SCANCODE_SPACE) || m_display.isVirtualSustainButtonPressed();
}

bool SDLButtonChecker::isExitButtonPressed()
{
    return checkButton(SDL_SCANCODE_ESCAPE);
}
