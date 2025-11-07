#pragma once
#include "Model.hpp"
#include "View.hpp"

#include "IButtonChecker.hpp"

#include <chrono>

class Controler
{
    Model& m_model;
    View& m_view;
    IButtonChecker& m_button_checker;
    std::chrono::steady_clock::time_point loop_start;
    
    bool has_ring_button_pressed;
    bool continue_loop = true;
    void processRingButton();
    
    /// @brief ループ1回で行われる処理
    void mainOneLoop();
    
public:
    Controler(Model&, View&, IButtonChecker&);
    void startLoop();
};
