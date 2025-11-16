#include "Block.hpp"

using namespace std;

vector<charaData> Block::getCharaToDisplay() const
{
    vector<charaData> ans;
    
    // block全体の座標のずれを計算
    double x_offset = x*base_size;
    double y_offset = y*base_size;

    for(auto data: m_chara_to_display)
    {
        double x_ans = data.x*base_size + x_offset;
        double y_ans = data.y*base_size + y_offset;
        charaData d(x_ans, y_ans, data.font_size, data.str);
        ans.push_back(d);
    }
    return ans;
}
