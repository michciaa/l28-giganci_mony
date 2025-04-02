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

/* 
Klasa, przetwarzająca nazwę i ścieżkę do karty z wizerunkiem pokemona oraz wyświetlająca je na ekranie
Jest to jednak tylko SZKIELEKT klasy, obsługę metody render() realizujemy w pliku źródłowym Poks.cpp
 */
class Poks
{
    public:
        Poks(string name, const char *path);

        void render(float x, float y);

    private:
        string _name;
        Texture2D _texture;
};
