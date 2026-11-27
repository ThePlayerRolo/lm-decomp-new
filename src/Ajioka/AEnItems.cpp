#include "Ajioka/AEnItems.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

AEnItemBomb::AEnItemBomb() {}
AEnItemBomb::~AEnItemBomb() {}

bool AEnItemBomb::onCaptureEnd(Koga::CharacterEvent* msg) { return true; }
void AEnItemBomb::doBehavior() {}
void AEnItemBomb::initItemParams() {}
void AEnItemBomb::EnItem_fn_800D00A8() {}
void AEnItemBomb::EnItem_fn_800D00AC() {}
void AEnItemBomb::onThrowUp() {}
void AEnItemBomb::EnItem_fn_800D00B0() {}
bool AEnItemBomb::EnFiniteItem_fn_800D1318() { return false; }

bool AEnItemBomb::onSprayedWithWater(Koga::CharacterEvent* msg) { return true; }
bool AEnItemBomb::onSprayedWithFire(Koga::CharacterEvent* msg) { return true; }

void AEnHeartItemEscape::onThrowUp() {}
void AEnNegativeItemRandom::onThrowUp() {}
