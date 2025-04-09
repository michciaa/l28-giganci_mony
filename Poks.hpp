#pragma once

#include <string>
#include <iostream>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <functional>
#include <tuple>
#include <deque>

using namespace std;

enum Element
{
    Fire,
    Nature,
    Air,
    Earth,
    Water,
    last
};

/* 
Klasa, przetwarzająca nazwę i ścieżkę do karty z wizerunkiem pokemona oraz wyświetlająca je na ekranie
Jest to jednak tylko SZKIELEKT klasy, obsługę metody render() realizujemy w pliku źródłowym Poks.cpp
 */
class Poks
{
    public:
        Poks(string name, int hp, int ad, int def, Element _el, const char *path, function<void(Poks &, Poks &, string &)> special);

        void render(float x, float y);

        inline string get_name()
        {
            return _name;
        }

        inline int get_hp()
        {
            return _hp;
        }

        inline void take_dm(int dmg)
        {
            if(dmg < _def)
            {
                return;
            }
            _hp -= (dmg - _def);
        }

        void attack(Poks &target, string &out_text);
        void defend(string &out_text);
        void special(Poks &target, string &out_text);

        inline void reset()
        {
            this->_def = this->_base_def;
        }

        pair<int, int> calculate_attack_dmg(Poks const &target);

        void change_ad(int change);
        void change_def(int change);
        void change_hp(int change);

    private:
        int _base_hp, _base_ad, _base_def, _hp, _ad, _def;

        bool is_special, used_special;
        
        string _name;
        Element _element;
        Texture2D _texture;

        function<void(Poks &, Poks &, string &)> special_fun;
};
