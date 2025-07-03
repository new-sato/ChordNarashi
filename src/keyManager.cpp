#include "keyManager.hpp"

void KeyManager::setKey(unsigned int new_key)
{
    // ボタンが押されている間は入力を受け付けない
    if(!cbm.is_all_button_releaced()) return;

    key = new_key % 12;

}
