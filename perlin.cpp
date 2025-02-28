#include "perlin.h"

Vecteur::Vecteur(double x1, double y1) {
	(*this).x = x1; 
	(*this).y = y1;
}


ostream& operator<<(std::ostream& os, const Vecteur& v) {
	os << "(" << v.x << " , " << v.y << " )";
	return os;
}


Vecteur offsetVector(double x1, double y1, double x2, double y2) {
	return Vecteur(x2 - x1, y2 - y1);
}

double smoothstep(double w) {
	
	return w * w * (3.0 - 2.0 * w);
}


double lerp(double a0, double a1, double w) {
	//return ((a1 - a0) * (3.0 - w * 2.0) * w * w + a0);
	return a0 + (a1 - a0) * smoothstep(w);
}
double ln(double x) {
	//return log(2 + x);
	return x;
}


double noiseValue(double x, double y, Grid* grid) {
	
	int x1 = (int)x;
	int y1 = (int)y;
	int x2 = x1 + 1;
	int y2 = y1 + 1;

	Vecteur v1 = offsetVector(x1, y1, x, y); Vecteur v2 = offsetVector(x2, y1, x, y);
	Vecteur v3 = offsetVector(x1, y2, x, y); Vecteur v4 = offsetVector(x2, y2, x, y);

	double d1 = dotProduct((*grid)[y1][x1], v1);
	double d2 = dotProduct((*grid)[y1][x2], v2);
	double d3 = dotProduct((*grid)[y2][x1], v3);
	double d4 = dotProduct((*grid)[y2][x2], v4);

	double l1 = lerp(ln(d1), ln(d2), (double)((double)x - x1));
	double l2 = lerp(ln(d3), ln(d4), (double)((double)x - x1));

	return lerp(l1, l2, (double)((double)y - y1));

}



Vecteur::Vecteur(double theta) {

	x = cos(theta);
	y = sin(theta);
}

double dotProduct(Vecteur u, Vecteur v) {
	
	return u.x * v.x + u.y * v.y;
}


Grid initGrid(int width, int height) {
	Grid output;
	//vector<double> numbers = { pi / 4.0, (3.0*pi)/4.0, (- 3*pi)/4.0, -pi/4.0};
	for (int i = 0; i < height; i++) {
		vector<Vecteur> line;
		for (int j = 0; j < width; j++) {
		
			
			
			line.push_back(Vecteur(   randomNumber()   ));
			
		}
		output.push_back(line);
	}
	
	return output;
}

Octave createOctave(int width, int height, int subdivisions, double alpha) {
	
	
	Octave output;
	Grid grid = initGrid(width+1, height+1);
	for (int i = 0; i < height ; i++) {
		
		for (int subY = 0; subY < subdivisions; subY++) {
			vector<double> ligne;
			for (int j = 0; j < width; j++) {
				for (int subX = 0; subX < subdivisions; subX++) {
					double x = (double)j + ((double)subX / (double)subdivisions);
					double y = (double)i + ((double)subY / (double)subdivisions);
					double value = noiseValue(x, y, &grid) /  alpha;
					ligne.push_back(value);
				}

			}
			output.push_back(ligne);
		}

	}
	return output;
}


vector<Octave> createOctaves(int width, int height, int subdivisions, int nbOctaves) {
	vector<Octave> output;

	int subDiv = subdivisions;
	double alpha = 1.0;
	Octave octave;
	
	
	for (int numOctave = 0; numOctave < nbOctaves; numOctave++) {
		
		octave = createOctave(width, height, subDiv, alpha);
		
		alpha = alpha * 2.0;
		width = width * 2;
		height = height * 2;
		output.push_back(octave);
		
	}


	return output;
}
	
Octave addOctaves(vector<Octave>* octaves, int numberOctaves, int subDivisions) {
	if (numberOctaves == 1) {
		return (*octaves)[0];
	}
	Octave output = (*octaves)[numberOctaves - 1];
	int totalWidth = output[0].size(); int totalHeight = output.size();
	int currentWidth = totalWidth; int currentHeight = totalHeight;

	for (int i = 0; i < totalHeight; i++) {
		for (int j = 0; j < totalWidth; j++) {
			currentWidth = totalWidth / 2; currentHeight = totalHeight / 2;
			for (int numOctave = numberOctaves - 2; numOctave >= 0; numOctave--) {
				int x = (int)(((double)j / (double)totalWidth) * (double)currentWidth);

				int y = (int)(((double)i / (double)totalHeight) * (double)currentHeight);
				output[i][j] = output[i][j] + ((*octaves)[numOctave])[y][x];
				currentHeight /= 2;
				currentWidth /= 2;

			}
		}
	}
	
	



	return output;

}


Octave totalOctaves(int width, int height, int subdivisions, int nbOctaves) {
	
	vector<Octave> octaves = createOctaves(width, height, subdivisions, nbOctaves);
	//return octaves[2];
	return addOctaves(&octaves, nbOctaves, subdivisions);
}