#include <SDL.h>
#include <iostream>
#include <SDL_timer.h>

#include "perlin.h"

using namespace std;

void renderSquare(int x, int y, int width, int height, int grey, SDL_Renderer* renderer) {
   
    SDL_SetRenderDrawColor(renderer, grey, grey, grey, 255
    );
  //SDL_Rect rect{ x, y, width, height };
  //SDL_RenderFillRect(renderer, &rect);
   for (int posX = x; posX < x + width; posX++) {
        for (int posY = y; posY < y + height; posY++) {
            SDL_RenderDrawPoint(renderer, posX, posY);
        }
    }

}

void renderOctave(Octave octave, SDL_Renderer* renderer, int screenHeight, int screenWidth, double mini, double maxi) {
   
    int octaveHeight = octave.size();    int octaveWidth = octave[0].size();
    

    for (int i = 0; i < screenHeight; i++) {
        for (int j = 0; j < screenWidth; j++) {
            

            double posY = ((double)octaveHeight / (double)screenHeight) * (double)i;
            double posX = ((double)octaveWidth / (double)screenWidth) * (double)j;

            int grey = (int)((((1.2* octave[(int)posY][(int)posX]) + 1.0) * 0.5) * 255);
            SDL_SetRenderDrawColor(renderer, grey, grey, grey, 255
            );
            SDL_RenderDrawPoint(renderer, i, j);
          
        }
    }


}



int main(int argc, char* argv[])
{
    //Ligne importante
    //Allows randomness to be used
    int width, height, numberOctaves, subDivisions;
    srand(time(0));
    if (argc == 5){
      
         width = atoi(argv[1]); 
         height = atoi(argv[2]);
         numberOctaves = atoi(argv[4]);
         subDivisions = atoi(argv[3]);
       

    

    }else{
        width = 7;
        height =7;
        subDivisions = 7;
        numberOctaves = 3;
    }

    Grid grid = initGrid(width, height);
    //cout << "Grid generated" << endl;
    
    
    
    
    //vector<Octave> octaves =
   


    Octave octave = totalOctaves(width, height, subDivisions, numberOctaves);

    cout << octave.size() << " , " << (octave[0]).size();
    double mini = octave[0][0];
    int windowWidth = 2*octave[0].size();
    int windowHeight = 2*octave.size();

    double maxi = mini;
    
    for (auto ligne : octave) {
        for (auto v : ligne) {
            if (v > maxi) {
                maxi = v;
            }
            if (v < mini) {
               mini = v;
            }
        }
    }
    cout << "Mini : " << mini << " Maxi : " << maxi << endl;
   


if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return 0;
    }
    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
         windowWidth,windowHeight , 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

    // creates a surface to load an image into the main memory


    // please provide a path for your image

    // loads image to our graphics hardware memory.


    // clears main-memory


    // let us control our image position
    // so that we can move it with our keyboard.


    // controls animation loop
    int close = 0;
    //for (int i = 0; i < octave.size(); i++) {
    //    for (int j = 0; j < octave[i].size(); j++) {
    //        double value = (octave[i][j]-mini)/(maxi - mini);
    //        

    //        int grey = (int)((value) * 255);
    //        if (grey < 0) { grey = abs(grey); }
    //        if (grey > 256) { grey = 255; }
    //        //cout << value << endl;

    //        
    //        //cout << grey << endl;
    //        renderSquare(j, i, 1, 1, grey, rend);
    //    }
    //}
    renderOctave(octave, rend, windowHeight, windowWidth, mini, maxi);
   /* SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            SDL_RenderDrawLine(rend, 3 * j*20, 60 * i, 60 * j + grid[i][j].x*30 , 60 * i + grid[i][j].y *30);
        }
    }*/


    // speed of box
   /* for (int i = 0; i < windowHeight; i++) {
        for (int j = 0; j < windowWidth; j++) {
            renderSquare( j, i, 1, 1, (int)(randomNumber()*255), rend);

        }
    }*/
    SDL_RenderPresent(rend);
    // animation loop
    while (!close) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;



                // clears the screen
               
            }
        }

        //SDL_RenderClear(rend);

        

        // triggers the double buffers
        // for multiple rendering
        

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

            // destroy texture


            // destroy renderer
            SDL_DestroyRenderer(rend);

            // destroy window
            SDL_DestroyWindow(win);

            // close SDL
            SDL_Quit();


    return 0;
}
