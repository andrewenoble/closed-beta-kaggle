# Bin packing closed beta kaggle competition

By [Andrew Noble](http://andrewnoble.com)

## About

The co-founders of a startup company invited 16 experts in machine learning and optimization to participate in a closed-beta competition to test a kaggle-type platform aimed at harnessing the best of human and artificial intelligence to create optimal solutions.  The challenge was to formulate a heuristic solution to the optimal packing of 144 floats into 12 bins such that the difference between the largest and smallest bin sums (the "maximum difference") is minimized. Participants were provided with the sample set of 144 floats listsed in ```sample_numbers.txt```.  Submitted solutions were run on >100 undisclosed sample sets.  Solutions were rejected if any single run took longer than 10 seconds to run on a Docker instance.  Solutions scores were calculated as the sum of maximum differences across all sample sets.  The soution here took 3rd place with a score ~3 times higher than the top two entries, both submitted by postdocs in quantum computing at ETH Zurich, but a score ~100 better than the 4th place entry.  

![Alt text](top_three_scores.png?raw=true)


## Requirements

* C++ compiler
* Docker (optional)

## Usage

Clone the repo.
```
git clone https://github.com/andrewenoble/closed-beta-kaggle
cd closed-beta-kaggle
```
Compile.
```
clang++ -std=c++11 -O3 bin_packing_heuristic.cpp
```
Run on sample set of 144 floats.
```
./a.out sample_numbers.txt 
```
The output displays an approximate solution to the bin packing packing problem.   

## Docker submission

The following assumes that your local clone contains the Dockerfile listed above.  If so, start by creating and pushing the container.
```
docker build -t andrewenoble/bp:test
docker push andrewenoble/bp:test
```
Then perform a local test to check that the C++ code compiles and runs on a Docker instance.
```
docker run -t -v $PWD:/input andrewenoble/bp:test /input/sample_numbers.txt
```
Permissions can be set to make the container accesssible only to you and your collaborations.

