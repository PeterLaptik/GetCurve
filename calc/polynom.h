#ifndef POLINOM_H_INCLUDED
#define POLINOM_H_INCLUDED

#include "entity.h"
#include "stddef.h"

#define MAX_POINTS 20

class Polynom
{
	public:
		Polynom();
		~Polynom();
		bool SetPoint(double x, double y, int pos);
		int GetCount(void) const;
		Point* GetPointArray(void);
		double* GetPolynomialArray(void);
		Point GetPoint (int pos) const;
		void SetCount(int number);
		// Coefficients calculating
		// Make virtual function
		bool CheckPoints(void);
		void Calculate(void);
		double GetMaxX(void);
		double GetMinX(void);

	protected:

	private:
	    int CalculateSingleMultiply(Dinom a, Monom *result, size_t n);
	    void CalculateNumberMultiply(double number, Monom *result, size_t n);

		Point m_points[MAX_POINTS];             // points list
		double m_polynomial[MAX_POINTS];        // result polynomial
		double m_coeffitients[MAX_POINTS];
		int m_counter;


};

#endif // POLINOM_H_INCLUDED
