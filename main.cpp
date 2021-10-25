/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: bulat
 *
 * Created on 9 октября 2021 г., 21:04
 */
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
const int WIDTH = 1680;
const int HEIGHT = 1050;
int m_p_x = 0, m_p_y = 0;
int l_m_p_x = 0, l_m_p_y = 0;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT, 1), "3D Game", sf::Style::Fullscreen);
//clock time
sf::Clock cl;
sf::Time t;
sf::Font font;
sf::Text fps;
int fps_n = 0;
float player_x_pos = 100, player_y_pos = 100;
float speed = 100.0f;
const int map_x_size = 10, map_y_size = 10;
float p_rotate = 0.0f;
int map[map_x_size][map_y_size] = {
    {1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void init() {
    //fps text
    fps.setPosition(600, 0);
    if (!font.loadFromFile("font.ttf")) {
    }
    fps.setFont(font);
    fps.setCharacterSize(48);
    fps.setColor(sf::Color(255, 255, 0));
    //window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
}

int main() {
    init();
    //window is open while
    while (window.isOpen()) {

        //events
        sf::Event event;


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved) {

                m_p_x = sf::Mouse::getPosition().x;
                m_p_y = sf::Mouse::getPosition().y;
                l_m_p_x = m_p_x;
                p_rotate += (l_m_p_x - 840);
                p_rotate -= (l_m_p_x - 840) / 1.01;
            }
        }
        sf::Mouse::setPosition(sf::Vector2i(840.0f, 840.0f));
        window.clear(sf::Color(0, 255, 255));
        //time=clock.restart();
        t = cl.restart();

        sf::RectangleShape floor_r(sf::Vector2f(WIDTH, HEIGHT / 2));
        floor_r.setPosition(0, HEIGHT / 2);
        floor_r.setFillColor(sf::Color(255, 100, 50));
        window.draw(floor_r);
        
        
        for (float angle = -30; angle < 30; angle++) {
            sf::Vector2f position = sf::Vector2f(player_x_pos, player_y_pos);

            sf::Vector2f direction = sf::Vector2f(sin((p_rotate + angle) * M_PI / 180), cos((p_rotate + angle) * M_PI / 180));
            int distance = 0;
            bool cast = true;
            while (cast) {
                position += direction;

                int x_map = floor(position.x / 50);
                int y_map = floor(position.y / 50);

                if (map[x_map][y_map] == 1) {
                    //distance*=cos((angle-p_rotate)*M_PI/180);
                    sf::RectangleShape quad(sf::Vector2f(28, HEIGHT - distance));
                    quad.setPosition((angle+30) * 28, distance / 2);
                    int color = 255 - distance / 1.5;
                    if (color > 255) {
                        color = 255;
                    }
                    if (color < 0) {
                        color = 0;
                    }
                    quad.setFillColor(sf::Color(color, color, color));
                    window.draw(quad);
                    cast = false;
                }
                //distance = sqrt((player_x_pos - position.x)*(player_x_pos - position.x)+(player_y_pos - position.y)*(player_y_pos - position.y));
                distance++;
                

                if (distance >= HEIGHT) {
                    cast=false;
                }
            }

            //window.draw(lines);

        }
        sf::RectangleShape player(sf::Vector2f(50, 50));
        player.setFillColor(sf::Color::Cyan);
        player.setPosition(player_x_pos, player_y_pos);
        //window.draw(player);
        //fps text creating
        fps_n = 1 / t.asSeconds();
        fps.setString("fps: " + std::to_string(fps_n));
        window.draw(fps);
        //display
        window.display();


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player_y_pos -= speed * t.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player_y_pos += speed * t.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player_x_pos -= speed * t.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player_x_pos += speed * t.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.setMouseCursorVisible(true);
        }
    }
    return 0;
}
