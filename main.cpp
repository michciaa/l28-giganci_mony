#include <iostream>
#include "Poks.hpp"
#include "moves.hpp"
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <queue>

using namespace std;

void draw_gui(float selected_index, deque<string> &output);  // Prototyp funkcji, która będzie nam wyświetlała na ekranie sekcje menu i konsoli

void update_output_queue(deque<string> &output, string line);

int main()
{

    const int screenWidth = 1400;
    const int screenHeight = 1000;
    deque<string> console_output(5);
    InitWindow(screenWidth, screenHeight, "GigantMony");

    Poks player("Fire",20,10,5,Element::Fire, "resources/Fire.png", PoksAttacks::Fireball);
    Poks enemy("Water",20,10,5,Element::Water, "resources/Water.png", PoksAttacks::WaterCannon);

    float selected_idx{}; // zmienna do wyboru opcji na ekranie
    bool win{}, lose{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if(!lose && !win)
        {
            if(player.get_hp() <= 0)
            {
                lose = true;
            }
            if(enemy.get_hp() <= 0)
            {
                win = true;
            }
        
        if(IsKeyPressed(KEY_UP))
        {
            selected_idx--;
            selected_idx = selected_idx < 0 ? 2 : selected_idx;
        }
        else if(IsKeyPressed(KEY_DOWN))
        {
            selected_idx++;
            selected_idx = selected_idx > 2 ? 0 : selected_idx;
        }

        if(IsKeyPressed(KEY_ENTER))
        {
            string text{};
            switch(int(selected_idx))
            {
                case 0:
                    player.attack(enemy, text);
                    update_output_queue(console_output, text);
                break;

                case 1:
                     player.defend(text);
                    update_output_queue(console_output, text);
                break;

                case 2:
                    player.special(enemy, text);
                    update_output_queue(console_output, text);  
                break;

                default:
                break;
            
                  enemy.attack(player, text);
                  update_output_queue(console_output, text);
            }
        }
        }

        
        BeginDrawing(); // MIEJSCE "START" WYŚWIETLANIA CONTENTU NA EKRANIE

        ClearBackground(SKYBLUE);

        draw_gui(selected_idx, console_output);

        if(!lose && !win)
        {
            player.render(screenWidth / 2 - 520, screenHeight / 2 - 220);
            enemy.render(screenWidth / 2 + 150, screenHeight / 2 - 350);
        }
        else if (win)
        {
            DrawText("You win!", 480, 300, 85, BLACK);
        }
        else if(lose)
        {
             DrawText("Game over", 480, 300, 85, BLACK);
        }
        EndDrawing(); // MIEJSCE "STOP" WYŚWIETLANIA CONTENTU NA EKRANIE
    }
    CloseWindow();
    return 0;
}

void draw_gui(float selected, deque<string> &output)
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

    int offset = 0;

    for(auto line : output)
    {
        DrawText(line.c_str(), 920, 920 - 25 * offset, 20, BLACK);
        offset++;
    }

}

void update_output_queue(deque<string> &output, string line)
{
    output.push_back(line);
    if(output.size() > 5)
    {
        output.pop_front();
    }
}