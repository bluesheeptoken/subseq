# Benchmark

## Data

The benchmark has been realized on the [`FIFA`](https://www.philippe-fournier-viger.com/spmf/index.php?link=datasets.php) dataset.

You can get the dataset with `curl`: `curl http://www.philippe-fournier-viger.com/spmf/datasets/FIFA.txt --output FIFA.dat`.

The training has been made with 20_450 sequences with an average length of 34 and an alphabet of 2990 elements.

## Setup

The benchmark has been realized with a PC with 8 GB of ram, 8 cores and the `Intel(R) Core(TM) i7-6700HQ CPU @ 2.60GHz` CPU.

## Running the benchmark

With `FIFA.dat` in the data folder, you can run the benchmark from the benchmark folder: `python benchmark.py`.

## Results

`Subseq` predicted the entire dataset in approximatively 2 hours, which is an average of 330 ms per prediction.

This model takes relatively more time than [`CPT`](https://github.com/bluesheeptoken/CPT/tree/master/benchmark). This is mainly because `Subseq` is doing a lot of Full Text search.
