#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Juego.hpp"
namespace Anto
{
    class Terodactile
    {
    public:
        Terodactile(EstructuraJuegoData l_datos);
        void Update(float dt);
        void Draw();
        bool ColisionPlayer(const sf::Sprite &player);
        void CalculateY();
        void Animate();
        void ChangeState(int value);
        void Reposition();
    private:
        EstructuraJuegoData m_datos;
        sf::Sprite mainSprite;
        sf::Clock moveTime;
        sf::Clock aniClock;
        std::vector<sf::IntRect> animationSprites;
        int _iteradorAnimacion;
        int xPeriodTimes;
        float y;
        int terodactileState;
        sf::SoundBuffer terodactileBuffer;
        sf::Sound terodactileSound;
    };
}