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
    checkButton(chordButtons[11], 'Q');
    checkButton(chordButtons[0], 'W');
    checkButton(chordButtons[1], 'E');
    checkButton(chordButtons[2], 'R');
    checkButton(chordButtons[3], 'T');

    // マイナーコード
    checkButton(chordButtons[23], 'A');
    checkButton(chordButtons[12], 'S');
    checkButton(chordButtons[13], 'D');
    checkButton(chordButtons[14], 'F');
    checkButton(chordButtons[15], 'G');

    // ディミニッシュコード
    checkButton(chordButtons[35], 'Z');
    checkButton(chordButtons[24], 'X');
    checkButton(chordButtons[25], 'C');
    checkButton(chordButtons[26], 'V');
    checkButton(chordButtons[27], 'B');

    // オーギュメントコード
    checkButton(chordButtons[47], '1');
    checkButton(chordButtons[36], '2');
    checkButton(chordButtons[37], '3');
    checkButton(chordButtons[38], '4');
    checkButton(chordButtons[39], '5');
    
    // シフトボタン
    checkButton(shiftButtons[9], VK_SHIFT);
    checkButton(shiftButtons[3], VK_CONTROL);
    checkButton(shiftButtons[6], VK_TAB);
    
    // キーボタン
    checkButton(keyButtons[static_cast<int>(keyButton::Dominant)],VK_RIGHT);
    checkButton(keyButtons[static_cast<int>(keyButton::Subdominant)],VK_LEFT);
    checkButton(keyButtons[static_cast<int>(keyButton::SemitoneUp)],VK_UP);
    checkButton(keyButtons[static_cast<int>(keyButton::SemitoneDown)],VK_DOWN);
    
    // 右手ボタン
    checkButton(rightButtons[0], 'K');
    
    // 終了ボタン
    checkButton(otherButtons[static_cast<int>(otherButton::EXIT)], VK_ESCAPE);
}