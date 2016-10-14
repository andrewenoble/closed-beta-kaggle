#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

const int NUM_FLOATS = 144;
const int NUM_BINS = 12;
const int NUM_FLOATS_PER_BIN = 12;

const double TOL = 4.75e-7;
const int NUM_ATTEMPTS = (int) 1e8; 
const double LARGE_FLOAT = 1e6;

const int SEED = 12345;

int main(int argc, char* argv[]) {

  int i, j, k, tmp_counter, diff_min_j, subset_counter = 0;
  double diff_min;
  vector<double> \
    a(NUM_FLOATS),
    sums(NUM_BINS);
  vector< vector<double> > \
    subsets(NUM_BINS, vector<double>(NUM_FLOATS_PER_BIN));

  knuth_b g(static_cast<uint32_t>(SEED));

  string file_name = argv[1]; 
  fstream f;
  f.open(file_name);
  for (i = 0; i < NUM_FLOATS; i++) {
      f >> a[i];
  }
  f.close();

 for (i = 0; i < NUM_BINS; i++) 
    for (j = 0; j < NUM_FLOATS_PER_BIN; j++) 
      subsets[i][j] = a[i * NUM_FLOATS_PER_BIN + j];  

  for (k = 0; k < NUM_ATTEMPTS; k++) {
 
    shuffle(a.begin(), a.end() - NUM_FLOATS_PER_BIN * subset_counter, g);

    for (j = 0; j < NUM_BINS - subset_counter; j++) {
      sums[j] = 0;
      for (i = NUM_FLOATS_PER_BIN * j; i < NUM_FLOATS_PER_BIN * (j+1); i++)
        sums[j] += a[i];
    }

    diff_min = LARGE_FLOAT;
    for (j = 0; j < NUM_BINS - subset_counter; j++) 
      if (abs(sums[j] - 1) < diff_min) {
        diff_min = abs(sums[j] - 1.0);
        diff_min_j = j;
      }

    if (diff_min < TOL) {
        ++subset_counter;
        tmp_counter = 0;
        for (i = NUM_FLOATS_PER_BIN * diff_min_j; i < NUM_FLOATS_PER_BIN * (diff_min_j+1); i++) {
          subsets[subset_counter - 1][tmp_counter++] = a[i]; 
          a[i] = a[NUM_FLOATS - NUM_FLOATS_PER_BIN * (subset_counter - 1) - tmp_counter];
        }         
      }   

    if (subset_counter == NUM_BINS - 1) 
      break;               
  }

  ++subset_counter;
  tmp_counter = 0;
  for (i = 0; i < NUM_FLOATS_PER_BIN; i++) {
    subsets[subset_counter - 1][tmp_counter++] = a[i];
  }

  double min_sum = LARGE_FLOAT;
  double max_sum = 0;
  double tmp = 0;
  double min_val_1, min_val_2;
  int subset_min, subset_max, min_index_1, min_index_2;
  for (k = 0; k < 1000; k++)
  for (subset_counter = 0; subset_counter < NUM_BINS; subset_counter++) {
    tmp = 0;
    for (i = 0; i < NUM_FLOATS_PER_BIN; i++) 
      tmp += subsets[subset_counter][i];
    if (tmp < min_sum) {
      subset_min = subset_counter;
      min_sum = tmp; 
    }
    if (tmp > max_sum) {
      subset_max = subset_counter;
      max_sum = tmp; 
    }

    min_val_1 = LARGE_FLOAT; 
    min_val_2 = LARGE_FLOAT; 
    for (i = 0; i < NUM_FLOATS_PER_BIN; i++) {
      if (subsets[subset_min][i] < min_val_1) {
        min_index_1 = i;
        min_val_1 = subsets[subset_min][i];
      }
      if (subsets[subset_max][i] < min_val_2) {
        min_index_2 = i;
        min_val_2 = subsets[subset_max][i];
      }
    }

    tmp = subsets[subset_min][min_index_1];
    subsets[subset_min][min_index_1] = subsets[subset_max][min_index_2];
    subsets[subset_max][min_index_2] = tmp;
  }

  for (subset_counter = 0; subset_counter < NUM_BINS; subset_counter++) {
    tmp = 0;
    for (i = 0; i < NUM_FLOATS_PER_BIN; i++) 
      tmp += subsets[subset_counter][i];
    printf("%d %0.15f\n", subset_counter, tmp);
  } 
  cout << endl << endl;

  for (subset_counter = 0; subset_counter < NUM_BINS; subset_counter++) {
    printf("b");
    for (i = 0; i < NUM_FLOATS_PER_BIN; i++) 
      printf(" %0.15f", subsets[subset_counter][i]);
    printf("\n");
  } 
  printf("\n");

  return 0;
}
