#include "utilitaires.h"

double randomNumber() {
    
        // Define the set of possible values
        std::vector<double> values = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.7, 1.8, 2.2, 2.5, 2.7, 2.9, 3.1 };

        // Initialize a random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Create a uniform distribution to select an index between 0 and 4
        std::uniform_int_distribution<> dis(0, values.size() - 1);

        // Return a random value from the set
        return values[dis(gen)];
    

}

