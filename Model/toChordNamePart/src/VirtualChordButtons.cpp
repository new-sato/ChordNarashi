#include "VirtualChordButton.hpp"

// HACK ラムダ式ではなくヘルパー関数として実装したほうがテストしやすくて無難か
VirtualChordButton::VirtualChordButton(ChordButtonType type,int button_num, int key)
    :note
    (
        static_cast<Note>
        (
            [=]() -> int
            {
                enum FifthLocDiff
                {
                    Major = 0,
                    minor = 3,
                    dim = 5,
                    arg = 0,
                    sus = 0
                };

                // 五度円上のどこにいるか
                int loc = (button_num + key) % NUM_OF_NOTE;
                switch (type)
                {
                case ChordButtonType::Major:
                    return (loc + FifthLocDiff::Major)%12;
                    break;
                case ChordButtonType::minor:
                    return (loc + FifthLocDiff::minor)%12;
                case ChordButtonType::dim:
                    return (loc + FifthLocDiff::dim)%12;
                default:
                    return loc;
                    break;
                }
            }()
        )
    )
    ,cbt(type)
{    
}

VirtualChordButton VirtualChordButton::shift(unsigned int shift_diff)
{
    int note_int = static_cast<int>(note);
    Note shifted_note = static_cast<Note>((note_int + shift_diff)%12);
    return VirtualChordButton(cbt, shifted_note);
}

int VirtualChordButton::ButtonNum()const
{
    return static_cast<int>(cbt)*12 + static_cast<int>(note);
}