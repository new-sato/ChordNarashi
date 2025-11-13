#include "DisplayCircleBlock.hpp"
#include "UI.hpp"

#include <cmath>

using namespace std;

void DisplayCircle::changeKey(int input)
{
    is_rotating = true;
    
    // 右回りが正なのでマイナス
    m_target_angle = -2*M_PI/NUM_OF_NOTE * input;
    m_rotation_angle = m_target_angle - m_current_angle;
    if(m_rotation_angle > M_PI)
    {
        m_rotation_angle -= M_PI*2;
    }
    else if(m_rotation_angle <= -M_PI)
    {
        m_rotation_angle += M_PI*2;
    }

    m_key = input;
    m_time_start_rotation = chrono::steady_clock::now();
}

DisplayCircle::DisplayCircle(const UI &ui, Model &model)
    : Block(1.0, 1.0, 0, 0), m_ui{ui}
{
    model.addKeyObserver([this](int key){this->changeKey(key);});
}

void DisplayCircle::updateBlock(std::chrono::milliseconds d_time)
{
    m_chara_to_display.clear();
    
    if(rotate_mode)
    {
        if(is_rotating)
        {
            if(chrono::steady_clock::now()-m_time_start_rotation > m_time_to_rotate)
            {
                m_current_angle = -m_key*2*M_PI/12;
                is_rotating = false;
            }
            else
            {m_current_angle += m_rotation_angle*(static_cast<double>(d_time.count())/m_time_to_rotate.count());}
        }
    }
    else
    {
        m_current_angle = 0;
    }

    for(int i=0; i<m_ui.get_key_str().size();i++)
    {
        m_chara_to_display.push_back(
            charaDataInBlock(
                m_majior_radius*sin(m_current_angle + i*2*M_PI/12),
                -m_majior_radius*cos(m_current_angle + i*2*M_PI/12),
                24,
                m_ui.get_key_str()[i]
            )
        );
        
        m_chara_to_display.push_back(
            charaDataInBlock(
                m_minor_radius*sin(m_current_angle + (i-3)*2*M_PI/12),
                -m_minor_radius*cos(m_current_angle + (i-3)*2*M_PI/12),
                20,
                m_ui.get_key_str()[i]+"m"
            )
        );

        m_chara_to_display.push_back(
            charaDataInBlock(
                m_dim_radius*sin(m_current_angle + (i-5)*2*M_PI/12),
                -m_dim_radius*cos(m_current_angle + (i-5)*2*M_PI/12),
                20,
                m_ui.get_key_str()[i]+"°"
            )
        );
    }
}
