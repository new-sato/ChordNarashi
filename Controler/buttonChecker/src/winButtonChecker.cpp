#include "winButtonChecker.hpp"

bool winButtonChecker::checkButton(int key)
{
    return (GetAsyncKeyState(key) & 0x8000);
}

void winButtonChecker::updateChordButtons()
{
    // HACK そのうちキーバインドを柔軟に変えられるようにしたいね
     
    // 長いので参照で書く
    auto& cb_Major = m_real_buttons.chordButtons.at(ChordButtonType::Major);
    cb_Major[static_cast<int>(Note::C)] = checkButton('E');
    cb_Major[static_cast<int>(Note::G)] = checkButton('R');
    cb_Major[static_cast<int>(Note::D)] = checkButton('T');
    cb_Major[static_cast<int>(Note::F)] = checkButton('W');

    auto& cb_minor = m_real_buttons.chordButtons.at(ChordButtonType::minor);
    cb_minor[static_cast<int>(Note::C)] = checkButton('D');
    cb_minor[static_cast<int>(Note::G)] = checkButton('F');
    cb_minor[static_cast<int>(Note::D)] = checkButton('G');
    cb_minor[static_cast<int>(Note::F)] = checkButton('S');
    
    auto& cb_dim = m_real_buttons.chordButtons.at(ChordButtonType::dim);
    cb_dim[static_cast<int>(Note::C)] = checkButton('C');
    cb_dim[static_cast<int>(Note::G)] = checkButton('V');
    cb_dim[static_cast<int>(Note::D)] = checkButton('B');
    cb_dim[static_cast<int>(Note::F)] = checkButton('X');

    auto& cb_arg = m_real_buttons.chordButtons.at(ChordButtonType::arg);
    cb_arg[static_cast<int>(Note::C)] = checkButton('3');
    cb_arg[static_cast<int>(Note::G)] = checkButton('4');
    cb_arg[static_cast<int>(Note::D)] = checkButton('5');
    cb_arg[static_cast<int>(Note::F)] = checkButton('2');
}

void winButtonChecker::updateShiftButtons()
{
    m_real_buttons.tempShihftButtons[9] = checkButton('Z');
    m_real_buttons.tempShihftButtons[3] = checkButton('A');
    m_real_buttons.tempShihftButtons[6] = checkButton('Q');
}

void winButtonChecker::updateKeyButtons()
{
    m_keyButtons[1].setState(checkButton(VK_RIGHT)||checkButton('L'));
    m_keyButtons[11].setState(checkButton(VK_LEFT)||checkButton('J'));
    m_keyButtons[7].setState(checkButton(VK_UP)||checkButton('O'));
    m_keyButtons[5].setState(checkButton(VK_DOWN)||checkButton('M'));
    m_keyButtons[3].setState(checkButton(VK_OEM_1));
    m_keyButtons[9].setState(checkButton('H'));
}

void winButtonChecker::updateModeButtons()
{
    m_signature_mode_button.setState(checkButton('0'));
}

bool winButtonChecker::isRingButtonPressed()
{
    return checkButton('K');
}

bool winButtonChecker::isSustainButtonPressed()
{
    return checkButton(VK_SPACE);
}

bool winButtonChecker::isExitButtonPressed()
{
    return checkButton(VK_ESCAPE);
}
