#include <iostream>
#include "Poks.hpp"
#include "moves.hpp"
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <queue>

using namespace std;

void draw_gui(float selected_index);  // Prototyp funkcji, która będzie nam wyświetlała na ekranie sekcje menu i konsoli

int main()
{

    const int screenWidth = 1400;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "GigantMony");

    float selected_idx{}; // zmienna do wyboru opcji na ekranie
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        
        

        
        BeginDrawing(); // MIEJSCE "START" WYŚWIETLANIA CONTENTU NA EKRANIE

        ClearBackground(SKYBLUE);

        draw_gui(selected_idx);

        EndDrawing(); // MIEJSCE "STOP" WYŚWIETLANIA CONTENTU NA EKRANIE
    }
    CloseWindow();
    return 0;
}

void draw_gui(float selected)
{
    Rectangle menu{-2, 810, 800, 310}; 
    /* 
    -2 -> wsp. x punktu w lewym górnym rogu (początek prostokąta)
    810 -> wsp. y punktu w lewym górnym rogu (początek prostokąta)
    800 -> szerokość prostokąta (w px)
    310 -> wysokość prostokąta (w px)
     */
    DrawRectangleLinesEx(menu, 4, BLACK); 
    // Parametry: menu -> rozmieszczenie prostokąta na ekranie, 4 -> grubość obramowania (w px); BLACK -> kolor obramowania
    
    /* Funkcja, która w oparciu o obiekt "menu" rysuje prostokąt, ALE TYLKO SAMO OBRAMOWANIE.
    Prostokąt z wypełnieniem rysujemy przez funkcję: DrawRectangle() */

    DrawText("Attack", 15, 850, 30, BLACK); 
    // Funkcja rysująca tekst: 
    // DrawText(Tekst do wyświetlenia, pozycja x, pozycja y, wielkość czcionki, kolor czcionki)

    DrawText("Defend", 15, 900, 30, BLACK); 
    DrawText("Special attack", 15, 950, 30, BLACK);

    Rectangle selection{10, 830 + selected * 50, 400, 60};
    DrawRectangleLinesEx(selection, 4, BLACK);

    Rectangle console{906, 810, 600, 310};

    DrawRectangleLinesEx(console, 4, BLACK);
}
