#include "Poks.hpp"
#include <string>

using namespace std;

namespace PoksAttacks
{
    void Fireball(Poks &self, Poks &target, string &out_text)
    {
        self.change_ad(4);
            int base{}, bonus{};
            tie(base, bonus) = self.calculate_attack_dmg(target);
            int const total = base + bonus;
            out_text = self.get_name() + " used Fire Ball at " + target.get_name() + " for: " + to_string(total) + " with modifier of: " + to_string(bonus);
    }


    void WaterCannon(Poks &self, Poks &target, string &out_text)
    {
        target.change_ad(-2);
        target.change_def(-2);

        int base{}, bonus{};
        tie(base, bonus) = self.calculate_attack_dmg(target);
        int const total = base + bonus;
        out_text = self.get_name() + " used Water Cannon at " + target.get_name() + " for: " + to_string(total) + " with modifier of: " + to_string(bonus);
    }
}
