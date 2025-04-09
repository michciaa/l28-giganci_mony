#include <Poks.hpp>

using namespace std;

const int TEXTURE_WIDTH = 350;
const int TEXTURE_HEIGHT = 400;

// Lista inicjalizacyjna (rodzaj konstruktora) klasy Poks, wczytująca obrazek pokemona
Poks::Poks(string name, int hp, int ad, int def, Element el, const char *path, function<void(Poks &, Poks &, string &)> special) : 
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
    special_fun = special;
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
    int base{}, bonus{};

    tie(base, bonus) = this-> calculate_attack_dmg(target);
    int const total = base + bonus;
    out_text = this->get_name() + " attacked " + target.get_name() + " for: " + to_string(total) + " with modifier of: " + to_string(bonus);
    target.take_dm(base + bonus);
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
        this->special_fun(*this, target, out_text);
        used_special = true;
    }
    else
    {
        out_text = this->get_name() + "has already used special";
    }
}

pair<int, int>
Poks::calculate_attack_dmg(Poks const &target)
{
    int bonus{};

    auto dif = target._element - this->_element;

    switch(abs(dif))
    {
        case 1:
            bonus = dif > 0 ? this->_ad * 0.5f : this->_ad * -0.5f;
        break;

        case Element::last-1:
            bonus = dif < 0 ? this->_ad * 0.5f : this-> _ad * -0.5f;
        break;

        default:
            bonus = 0;
        break;
    }
    return make_pair(this->_ad, bonus);
}

void Poks::change_ad(int change)
{
    this->_ad += change;
}

void Poks::change_def(int change)
{
    this->_def += change;
}

void Poks::change_hp(int change)
{
    this->_hp += change;
}