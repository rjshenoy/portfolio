#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

class Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}


double
applyFilter(class Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  output -> width = input -> width;
  output -> height = input -> height;
    
    int w = (input -> width) - 1;
    int l = (input -> height) - 1;
    
    int d = filter->getDivisor();
    
    int f1 = filter -> get(0,0);
    int f2 = filter -> get(0,1);
    int f3 = filter -> get(0,2);
    int f4 = filter -> get(1,0);
    int f5 = filter -> get(1,1);
    int f6 = filter -> get(1,2);
    int f7 = filter -> get(2,0);
    int f8 = filter -> get(2,1);
    int f9 = filter -> get(2,2);
   
    

// allows pc to use multi-threading
    // multi-threading splits a processor's avaliability to run a process
#pragma omp parallel for collapse(3)
for(int plane = 0; plane < 3; plane++) { // loop order 
    for(int row = 1; row < l; row = row + 1) { // did math on outside of loop
        for(int col = 1; col < w; col = col + 1) { // did math on outside of loop
//     output -> color[plane][row][col] = 0;
    int temp = input ->color[plane][row-1][col-1] * f1;
    temp += input ->color[plane][row-1][col] * f2;
    temp += input ->color[plane][row-1][col+1] * f3;
    temp += input ->color[plane][row][col-1] * f4;
    temp += input ->color[plane][row][col] * f5;
    temp += input ->color[plane][row][col+1] * f6;
    temp += input ->color[plane][row+1][col-1] * f7;
    temp += input ->color[plane][row+1][col] * f8;
    temp += input ->color[plane][row+1][col+1] * f9;
        
    temp = temp / d;
    
            
    if (temp < 0) {
        
         temp = 0;
    }        
    
            
    if (temp > 255) {
        
         temp = 255;
        
    }
            
    
//     temp = (temp > 255) ? 255 : temp; // if loop for 225, sets temp to 225
//     temp = (temp < 0) ? 0 : temp;
    output->color[plane][row][col] = temp;
        
      }
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}