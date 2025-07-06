#include "Button2Chord.hpp"
#include <set>

using note_set = std::set<int>;

class Chord2Note
{
    protected:
    Button2Chord& button_2_cohord;
    note_set Notes;

    public:
    Chord2Note(Button2Chord& arg):button_2_cohord(arg){};
    virtual void generateNote() = 0;
    
    /// @brief 最終的に決まったならすべき音符を返す。
    /// @return 
    note_set getNotes()const {return Notes;}
};