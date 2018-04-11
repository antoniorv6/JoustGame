#pragma once

#include <SFML/Graphics.hpp>
#include "Juego.hpp"


namespace Anto
{
    class Huevo
    {
        public:
            Huevo(EstructuraJuegoData l_datos, sf::Vector2f l_firstPos);
            void Update(float dt);
            void Draw();
            void TrataColision(sf::Sprite sprite_plat);
            bool Colision(std::vector<sf::Sprite> plataforma);
            bool ColisionPlayer(const sf::Sprite &player);
        private:
            EstructuraJuegoData m_data;
            sf::Sprite m_mainSprite;
            int m_eggState;
    };
}