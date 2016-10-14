# Bin packing closed beta kaggle competition

By [Andrew Noble](http://andrewnoble.com)

## About

The co-founders of a startup company invited 16 experts in machine learning and optimization to participate in a closed-beta competition to test a kaggle-type platform aimed at harnessing the best of human and artificial intelligence to create optimal solutions.  The challenge was to formulate a heuristic solution to the optimal packing of 144 floats into 12 bins such that the difference between the largest and smallest bin sums (the "maximum difference") is minimized. Participants were provided with the sample set of 144 floats in ```sample_numbers```.  Submitted solutions were run on >10 sample sets.  Solutions scores were calculated as the sum of maximum differences across all sample sets.  The soution here took 3rd place with a score ~3 times higher than the top two entries, both submitted by postdocs in quantum computing at ETH Zurich, but ~100 better than 4th place entry.  

![alt text](https://github.com/andrewenoble/closed-beta-kaggle/top_three_scores.png "Final scoreboard for top 3 entries.")


## Requirements

* C++ compiler

## Usage

Clone the repo.
```
git clone https://github.com/andrewenoble/closed-beta-kaggle.git
cd closed-beta-kaggle
```
Compile.
```
clang++ -std=c++11 -O3 bin_packing_heuristic.cpp
```
Run on test sample.
```
./a.out sample_numbers.txt 
```
The output lists the numbers placed in each of the 12 bins as well as the sum of the numbers in each bin and the difference between the largest and smallest sum.   

