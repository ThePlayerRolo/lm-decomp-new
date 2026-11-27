#ifndef  PLAYER_HPP
#define PLAYER_HPP

#include "Unsorted/character.hpp"
#include "Unsorted/PlayerInteraction.hpp"

class Player : public Character {
public:
    Player();

    s32 receiveInteraction(PlayerInteractionType type, PlayerInteractionInfo* pInteractionInfo);
};

#endif
