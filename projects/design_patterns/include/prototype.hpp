#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP

#include <iostream>

/*
	Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.
*/

enum imageType { LSAT, SPOT };

class Image
{
public:
    virtual void draw() = 0;
    static Image* findAndClone(imageType);   /// Client calls this public static member function when it needs an instance of an Image subclass

protected:
    virtual imageType returnType() = 0;
    virtual Image* clone() = 0;
    static void addPrototype(Image* image);   /// As each subclass of Image is declared, it registers its prototype

private:
    // addPrototype() saves each registered prototype here
    static Image* _prototypes[10];
    static int _nextSlot;
};

Image* Image::_prototypes[];
int Image::_nextSlot;

class LandSatImage : public Image
{
public:
    imageType returnType();
    void draw();
    Image* clone();   // When clone() is called, call the one-argument ctor with a dummy arg

protected:
    LandSatImage(int dummy);   // This is only called from clone()

private:
    static LandSatImage _landSatImage;   // Mechanism for initializing an Image subclass - this causes the default ctor to be called, which registers the subclass's prototype

    LandSatImage();   // This is only called when the private static data member is initiated

    // Nominal "state" per instance mechanism
    int _id;
    static int _count;
};

// Register the subclass's prototype
LandSatImage LandSatImage::_landSatImage;

// Initialize the "state" per instance mechanism
int LandSatImage::_count = 1;

class SpotImage : public Image
{
public:
    imageType returnType();
    void draw();
    Image* clone();

protected:
    SpotImage(int dummy);

private:
    SpotImage();

    static SpotImage _spotImage;
    int _id;
    static int _count;
};

SpotImage SpotImage::_spotImage;
int SpotImage::_count = 1;

// Simulated stream of creation requests
const int NUM_IMAGES = 8;
imageType input[NUM_IMAGES] = { LSAT, LSAT, LSAT, SPOT, LSAT, SPOT, SPOT, LSAT };

int test_prototype()
{
    Image* images[NUM_IMAGES];

    // Given an image type, find the right prototype, and return a clone
    for (int i = 0; i < NUM_IMAGES; i++)
        images[i] = Image::findAndClone(input[i]);

    // Demonstrate that correct image objects have been cloned
    for (int i = 0; i < NUM_IMAGES; i++)
        images[i]->draw();

    // Free the dynamic memory
    for (int i = 0; i < NUM_IMAGES; i++)
        delete images[i];
}

#endif