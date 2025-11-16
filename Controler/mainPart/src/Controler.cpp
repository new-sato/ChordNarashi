#include "Controler.hpp"

using namespace std;

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
    
    // ループが終わったので処理を止める
    m_model.stopRingingNote();
}

void Controler::mainOneLoop()
{
    std::chrono::milliseconds d_time;
    do{
        auto now_time = std::chrono::steady_clock::now();
        d_time = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - loop_start);
    }while(d_time.count() < 5);
    loop_start = std::chrono::steady_clock::now();
    m_button_checker.checkButtons();
    m_model.updateKey(m_button_checker.getKeyButtonState());
    m_model.updateChord(m_button_checker.getChordRelatedButtons());
    m_model.processRingButtonState(m_button_checker.isRingButtonPressed(), m_button_checker.isSustainButtonPressed());

    if(m_button_checker.getSignatureModeButtonState())m_view.toggleSharpFlat();

    m_view.updateView(d_time);
}
