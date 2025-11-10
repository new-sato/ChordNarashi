#include "Controler.hpp"

using namespace std;

// TODO この処理をモデル側のクラスとして独立させたい
void Controler::processRingButton()
{
    
    if(has_ring_button_pressed)
    {
        // さっきから押されてた場合
        if(!m_button_checker.isRingButtonPressed())
        {
            // ちょうどはなされた場合
            has_ring_button_pressed = false;
            m_model.stopRingingNote();
        }
        else
        {
            m_model.continueRingingNote();
        }
    }
    else
    {
        if(m_button_checker.isRingButtonPressed())
        {
            // ちょうど今押され始めた場合
            has_ring_button_pressed = true;
            m_model.startRingingNote();
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
    while(!m_button_checker.isExitButtonPressed()&&!m_view.stopLoop())
    {
        mainOneLoop();
    }
}

void Controler::mainOneLoop()
{
    std::chrono::milliseconds d_time;
    do{
        auto now_time = std::chrono::steady_clock::now();
        d_time = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - loop_start);
    }while(d_time.count() < 5);
    m_button_checker.checkButtons();
    auto hoge = m_button_checker.getChordRelatedButtons();
    m_model.updateChord(hoge);
    m_view.updateView(d_time);
    processRingButton();
}
