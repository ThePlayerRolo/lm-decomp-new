#ifndef EN_ROTATION_HPP
#define EN_ROTATION_HPP

#include "Koga/EnChase.hpp"

class EnRotationFar: public EnChase {
public:
    EnRotationFar();
    virtual ~EnRotationFar();
};

class EnRotationNear: public EnChase {
public:
    EnRotationNear();
    virtual ~EnRotationNear();
};

#endif
