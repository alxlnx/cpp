#!/usr/bin/python3
from matplotlib import pyplot as plt
import numpy as np

# Build T(n) for merge sort, where
#   T - execution time
#   n - dataset length

# TASK:
# Draw three distinct graphs for each level of optimization (O0, O1, O2, O3)

filename = 'output.txt'

lines = []
with open(filename) as file_obj:
    lines = file_obj.readlines()

# Datafile structure (by line number):
#   1 Level of optimization
#   2 Amount of points
#   3 Amount of tests per point
#   'Amount of points' times:
#    Dataset length
#    Execution time 'amount of tests' times

opt_level = lines[0].rstrip('\n')
points_amount = int(lines[1].rstrip('\n'))
tests_amount = int(lines[2].rstrip('\n'))

dataset_lengths = []
execution_times = []

for dataset_num in range(points_amount):
    dataset_idx = 3 + (dataset_num * (tests_amount + 1))
    dataset_len = int(lines[dataset_idx])
    
    exec_times = []
    for test_num in range(tests_amount):
        exec_times.append( int(lines[dataset_idx + test_num + 1]) )
    avg_time = np.array(exec_times).mean()
    
    dataset_lengths.append(dataset_len)
    execution_times.append(avg_time)
    
    # print(f'Dataset length: {dataset_len}')
    # print(f'Execution times: {exec_times}')
    # print()

# print(len(dataset_lengths), len(execution_times))
plt.scatter(dataset_lengths, execution_times)
plt.xlabel('Dataset length')
plt.ylabel('Execution time, µs')
plt.grid('--', linewidth=0.6)
plt.minorticks_on()
plt.title('Execution time of the merge sort algorithm')

# print(opt_level, points_amount, tests_amount)

plt.show()