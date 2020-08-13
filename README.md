# Succinct BWT-Based Sequence Prediction (Subseq)

## What is it ?

This project is a c++ implementation with a python wrapper of the `Succinct BWT-Based Sequence Prediction` model.

Subseq is a sequence prediction model in a finite alphabet.
It is a lossless model (does not discard information while training) and utilizes the succinct Wavelet Tree data structure and the Burrows-Wheeler Transform to compactly store and eﬃciently access training sequences for prediction.

This implementation is based on the following research paper:

- https://www.researchgate.net/publication/335231805_Succinct_BWT-Based_Sequence_Prediction

## Installation

Installation from the sources.
On Linux and mac, you can easilly install it via `make build`.

For Windows users, the installation is trickier.

## Simple example

You can test the model with the following code:

```python
from subseq.subseq import Subseq
model = Subseq(1)

model.fit([['hello', 'world']])

model.predict(['hello'])
# Output: ['world']
```

## Features
### Train

The model can be trained with the `fit` method.

### Tuning

Subseq has only 1 meta parameter that need to be tuned. `threshold_query`, the number of similar queries that needs to be retrieved to make a confident prediction.

A `threshold_query` at 0 does not limit the number of query.

## Benchmark

The benchmark has been made on the FIFA dataset, the data can be found on the [SPMF website][1].

Details on the benchmark can be found [here](benchmark).

[1]: https://www.philippe-fournier-viger.com/spmf/index.php?link=datasets.php
