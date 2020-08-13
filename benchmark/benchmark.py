import os
import sys
import time
# Add subseq to python path
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from subseq.subseq import Subseq  # pylint: disable=wrong-import-position

with open("FIFA.dat") as file:
    data = list(map(lambda l: [int(x) for x in l.rstrip().split() if int(x) > -1], file.readlines()))

model = Subseq(1)
model.fit(data)

prediction_data = list(map(lambda x: x[-6:-2], data))

print("Training finished, starting predictions")
time1 = time.time()
for seq in prediction_data:
    print(model.predict(seq))
time2 = time.time()
print(f"time ellapsed {(time2-time1)*1000} ms")
