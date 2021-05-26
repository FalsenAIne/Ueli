import numpy as np
import time

print("NumPy")

v1 = np.random.uniform(low=0.0, high=2.0, size=(256 * 1024,))
v2 = np.random.uniform(low=0.0, high=2.0, size=(256 * 1024,))

start = time.perf_counter_ns()

result = np.dot(v1, v2)

stop = time.perf_counter_ns()
# print("Dot product is equal ", result)

print("Calculation has taken: {0} us".format((stop - start) * 0.001))

start = time.perf_counter_ns()

array = np.zeros((1000, 1000))

stop = time.perf_counter_ns()
# print("Dot product is equal ", result)

print("Filling with 0 has taken: {0} us".format((stop - start) * 0.001))