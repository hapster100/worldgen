#include "city.h"

void ggs_doctor_heal(ggstate* ggs, int heal, int cost)
{
  ggs->h->st->HP += heal;
  ggs->h->gold -= cost;
}