#include "Ajioka/AEnItems.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

AEnItemBomb::AEnItemBomb() {}
AEnItemBomb::~AEnItemBomb() {}

bool AEnItemBomb::onCaptureEnd(Koga::CharacterEvent* msg) { return true; }
void AEnItemBomb::doBehavior() {}
void AEnItemBomb::EnItem_fn_800CFFD8() {}
void AEnItemBomb::EnItem_fn_800D00A8() {}
void AEnItemBomb::EnItem_fn_800D00AC() {}
void AEnItemBomb::EnItemThrowUp_fn_800D036C() {}
void AEnItemBomb::EnItem_fn_800D00B0() {}
bool AEnItemBomb::EnFiniteItem_fn_800D1318() { return false; }

bool AEnItemBomb::onSprayedWithWater(Koga::CharacterEvent* msg) { return true; }
bool AEnItemBomb::onSprayedWithFire(Koga::CharacterEvent* msg) { return true; }

void AEnHeartItemEscape::EnItemThrowUp_fn_800D036C() {}
void AEnNegativeItemRandom::EnItemThrowUp_fn_800D036C() {}
