#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#define MAX_POINTS 20

// Point on a flat surface
// Decart's coordinates
struct Point
{
	double x;
	double y;
};

// Simple expression:
// Multiplier*x^power
struct Monom
{
    int power;          // power for x
    double multiplier;  // float point multiplier
};

// Sum of two monoms:
// Multiplier1*x^power1 + Multiplier2*x^power2
struct Dinom
{
    Monom m1;
    Monom m2;
};

#endif // ENTITY_H_INCLUDED
