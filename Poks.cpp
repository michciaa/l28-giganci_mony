#include <Poks.hpp>

using namespace std;

const int TEXTURE_WIDTH = 350;
const int TEXTURE_HEIGHT = 400;

// Lista inicjalizacyjna (rodzaj konstruktora) klasy Poks, wczytująca obrazek pokemona
Poks::Poks(string name, int hp, int ad, int def, Element el, const char *path) : 
_name(name),
_base_hp(hp),
_hp(hp),
_ad(ad),
_def(def),
_element(el)
{
    Image image = LoadImage(path);
    ImageResize(&image, TEXTURE_WIDTH, TEXTURE_HEIGHT);
    _texture = LoadTextureFromImage(image);

    UnloadImage(image);
}

// Metoda z klasy Poks, wyświetlająca kartę pokemona na ekranie 
void Poks::render(float x, float y)
{
    DrawTexture(_texture, x, y, WHITE);
    DrawText(_name.c_str(), x + TEXTURE_WIDTH / 2 - 15, y + TEXTURE_HEIGHT + 20, 30, BLACK);
}

void Poks::attack(Poks &target, string &out_text)
{
    target.take_dm(_ad);
    out_text = this->get_name() + " attacked " + target.get_name() + " for: " + to_string(_ad);
}

void Poks::defend(string &out_text)
{
    _def += _base_def / 2;
    out_text = this->get_name() + " defends for: " + to_string(_base_def / 2);
}

void Poks::special(Poks &target, string &out_text)
{
    if(!used_special)
    {
        target.take_dm(_ad * 2);
        out_text = this->get_name() + "attacked " + target.get_name() + " for: " + to_string(_ad * 2);
        used_special = true;
    }
    else
    {
        out_text = this->get_name() + "has already used special";
    }
}