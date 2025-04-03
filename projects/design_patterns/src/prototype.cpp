#include "prototype.hpp"

#include <iostream>


Image* Image::findAndClone(imageType type)
{
    for (int i = 0; i < _nextSlot; i++)
        if (_prototypes[i]->returnType() == type)
            return _prototypes[i]->clone();
    return NULL;
}

void Image::addPrototype(Image* image) { _prototypes[_nextSlot++] = image; }

imageType LandSatImage::returnType() { return LSAT; }

void LandSatImage::draw() { std::cout << "LandSatImage::draw " << _id << std::endl; }

Image* LandSatImage::clone() { return new LandSatImage(1); }

LandSatImage::LandSatImage(int dummy) { _id = _count++; }

LandSatImage::LandSatImage() { addPrototype(this); }

imageType SpotImage::returnType() { return SPOT; }

void SpotImage::draw() { std::cout << "SpotImage::draw " << _id << std::endl; }

Image* SpotImage::clone() { return new SpotImage(1); }

SpotImage::SpotImage(int dummy) { _id = _count++; }

SpotImage::SpotImage() { addPrototype(this); }
