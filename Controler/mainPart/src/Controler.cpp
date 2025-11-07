#include "Controler.hpp"

using namespace std;

void Controler::processRingButton()
{
    if(has_ring_button_pressed)
    {
        // さっきから押されてた場合
        if(!m_button_checker.isRingButtonPressed())
        {
            // ちょうどはなされた場合
            has_ring_button_pressed = false;
            m_model.releaseRingButton();
        }
    }
    else
    {
        if(m_button_checker.isRingButtonPressed())
        {
            // ちょうど今押され始めた場合
            has_ring_button_pressed = true;
            m_model.pressRingButton();
        }
    }
}

Controler::Controler(Model &model, View &view, IButtonChecker &button_checker)
    : m_model(model), m_view(view), m_button_checker(button_checker)
{
    loop_start = chrono::steady_clock::now();
}

void Controler::startLoop()
{
    while(!m_button_checker.isExitButtonPressed())
    {
        mainOneLoop();
    }
}

void Controler::mainOneLoop()
{
    while(
        [=]() -> bool
        {
            auto now_time = std::chrono::steady_clock::now();
            auto d_time = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - loop_start).count();
            return (d_time < 5);
        }()
    );
    m_button_checker.checkButtons();
    auto hoge = m_button_checker.getChordRelatedButtons();
    m_model.updateChord(hoge);
    processRingButton();
}
