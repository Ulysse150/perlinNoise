#include "utilitaires.h"
#include <cstdlib> 


class Vecteur {
	public:
		double x;
		double y;
		Vecteur(double x, double y);
		Vecteur(double theta);
		friend ostream& operator<<(std::ostream& os, const Vecteur& v);
		
};	
/*Returns a Vector going from (x1, y1) to (x2, y2)
 *
 */
Vecteur offsetVector(double x1, double y1, double x2, double y2);

/** Lerp between a0 and a1
 *
 */
double lerp(double a0, double a1, double w);


/* @param u un Vecteur v un Vecteur
 * renvoie le produit scalaire entre u et v
 */
double dotProduct(Vecteur u, Vecteur v);
using Grid = std::vector<std::vector<Vecteur>>;

using Octave = std::vector<std::vector<double>>;
/* Returns the noise value of position (x,y)
* From the pointeur grid
 */
double noiseValue(double x, double y, Grid* grid);

double ln(double x);

double smoothstep(double w);
/* Returns a vector dimension 2 containing random vectors
*  Necessary for the perlin generation
*/
Grid initGrid(int width, int height);

/* Returns a vector of vector containing the perlins values for an octave
 * @param width, @paramheight the dimension of the grid, 
 * @param grid the pointer to it
 * @param subdivisions is the number of subdivisions per unit
 * @param aplha is the number by wich you divide every noise value.
 */
Octave createOctave(int width, int height, int subdivisions, double alpha);

/** Returns the list of successives octaves needed
 * @param width the width of the grid
 * @param height the height of the grid
 * @param grid the pointer to the vector grid
 * @param subDivisions the number of subDivisions
 * @param nbOctaves the number of octaves needed
 */
vector<Octave> createOctaves(int width, int height, int subdivisions, int nbOctaves);


Octave addOctaves(vector<Octave>* octaves, int numberOctaves, int subDivisions);

Octave totalOctaves(int width, int height, int subdivisions, int nbOctaves);