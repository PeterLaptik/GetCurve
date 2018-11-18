# GetCurve

A GUI program for polynomial interpolation. Computes up to 20 data points.
Displays linear and logarithmic scales.
Data points can be inputed by hand or mouse picking
(an external image can be scaled and underlaid on screen).
The interpolation is implemented in the Lagrange form.

Outputs results as:
 - PNG image of curent curve;
 - CSV table of a polynomial coefficients;
 - C-function for calculating any polynomial values;
 - ODT text document with tables and images.
 
![github-small](https://user-images.githubusercontent.com/32104993/48665206-a69ea980-eabb-11e8-8816-2b1ab57ff509.png)

## Installation (Windows)
The program has no installer: just download and unpack [release archive](https://github.com/PeterLaptik/GetCurve/releases).
It includes binary file and all necessary libraries.

## Assembling
### Windows
Replace the Makefile in root directory by the appropriate one from Makefiles folder.
Open it with notepad, and change variables CC, CRES, LIBINCLUDE, LIBDLL, LIBA 
to the right compiler and wxWidgets-library paths. 

Use your compiler's make utility.

### FreeBSD
Use make utility with the Makefile in root directory (the copy is kept in Makefiles folder).

Note: wxWidgets (wxLib-3.0) has to be installed and configured before use make.
