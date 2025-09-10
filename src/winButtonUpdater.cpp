#include "winButtonUpdater.hpp"
#include "keyButtonChecker.hpp"

void winButtonUpdater::checkButton(Button &button, int key)
{
    if(GetAsyncKeyState(key) & 0x8000)
    {
        button.setIsPressed(true);
    }
    else
    {
        button.setIsPressed(false);
    }
}

void winButtonUpdater::updateAllButtons()
{
    // メジャーコード
    checkButton(chordButtons[11], 'W');
    checkButton(chordButtons[0], 'E');
    checkButton(chordButtons[1], 'R');
    checkButton(chordButtons[2], 'T');
    checkButton(chordButtons[3], 'Y');

    // マイナーコード
    checkButton(chordButtons[23], 'S');
    checkButton(chordButtons[12], 'D');
    checkButton(chordButtons[13], 'F');
    checkButton(chordButtons[14], 'G');
    checkButton(chordButtons[15], 'H');

    // ディミニッシュコード
    checkButton(chordButtons[35], 'X');
    checkButton(chordButtons[24], 'C');
    checkButton(chordButtons[25], 'V');
    checkButton(chordButtons[26], 'B');
    checkButton(chordButtons[27], 'N');

    // オーギュメントコード
    checkButton(chordButtons[47], '2');
    checkButton(chordButtons[36], '3');
    checkButton(chordButtons[37], '4');
    checkButton(chordButtons[38], '5');
    checkButton(chordButtons[39], '6');
    
    // シフトボタン
    checkButton(shiftButtons[9], 'Z');
    checkButton(shiftButtons[3], 'A');
    checkButton(shiftButtons[6], 'Q');
    
    // キーボタン
    checkButton(keyButtons[static_cast<int>(keyButton::Dominant)],VK_RIGHT);
    checkButton(keyButtons[static_cast<int>(keyButton::Subdominant)],VK_LEFT);
    checkButton(keyButtons[static_cast<int>(keyButton::SemitoneUp)],VK_UP);
    checkButton(keyButtons[static_cast<int>(keyButton::SemitoneDown)],VK_DOWN);
    
    // 右手ボタン
    checkButton(rightButtons[0], 'K');

    // サステインボタン
    checkButton(sustainButton, 'J');
    
    // 終了ボタン
    checkButton(otherButtons[static_cast<int>(otherButton::EXIT)], VK_ESCAPE);
    
    checkButton(otherButtons[static_cast<int>(otherButton::DO_OFSET)], '7');
    checkButton(otherButtons[static_cast<int>(otherButton::TUGGLE_STROKE)], '8');
    checkButton(otherButtons[static_cast<int>(otherButton::TUGGLE_SUSTAIN)], '9');
    checkButton(otherButtons[static_cast<int>(otherButton::AUTO_SUSTAIN)], '0');
    
}