#pragma once
#include "Block.hpp"
#include "Model.hpp"

#include <chrono>

class UI;

class DisplayCircle: public Block
{
    const UI& m_ui;
    void changeKey(int input);
    int m_key = 0;
    
    std::chrono::steady_clock::time_point m_time_start_rotation;
    std::chrono::milliseconds m_time_to_rotate = std::chrono::milliseconds(300);
    
    /// @brief 現在の角度（-PiからPiの範囲で正規化）
    double m_current_angle = 0;
    /// @brief 目標とする角度（-PiからPiの範囲で正規化）
    double m_target_angle;
    
    double m_rotation_angle;
    
    bool rotate_mode = true;
    bool is_rotating = false;

    double m_majior_radius =0.8;
    double m_minor_radius = 0.6;
public: 
    DisplayCircle(const UI&, Model&);
    void updateBlock(std::chrono::milliseconds)override;
};
