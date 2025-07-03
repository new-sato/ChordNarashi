#include "button.hpp"

/// @brief 連続で押されたとき、一度だけ押されたと返すボタンのクラス
class OnceButton:public Button
{
    mutable bool is_first_press = true;

    public:
    bool getIsPressed() const override;
    void setIsPressed(bool new_state)override;
};
