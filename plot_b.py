# import matplotlib.pyplot as plt

# # Function to read hit and miss rates from a single file
# def read_rates(file_path):
#     miss_rates = []
#     cache_sizes = []
#     hit_rates = []


#     with open(file_path, 'r') as file:
#         lines = file.readlines()
#         for line in lines:
#             # Split the line by commas and extract miss_rate and cache_size
#             hit_rate, miss_rate, cache_size, _, _ = map(float, line.split(','))
#             hit_rates.append(hit_rate)
#             miss_rates.append(miss_rate)
#             cache_sizes.append(int(cache_size))

#     return hit_rates, miss_rates, cache_sizes

# # Path to the text file containing hit/miss rates for different cache sizes
# file_path = 'Memory-Cache/test.txt'

# # Read rates from the file
# hit_rates, miss_rates, cache_sizes = read_rates(file_path)

# # Plotting Miss Rate vs Cache Size
# plt.figure(figsize=(10, 6))
# plt.plot(cache_sizes, miss_rates, marker='o')
# plt.xlabel('Cache Size (KB)')
# plt.ylabel('Miss Rate')
# plt.title('Miss Rate vs Cache Size')
# plt.grid(True)
# plt.show()

# # Plotting Hit Rate vs Cache Size
# plt.figure(figsize=(10, 6))
# plt.plot(miss_rates, hit_rates, marker='o')
# plt.xlabel('Miss Rate')
# plt.ylabel('Hit Rate')
# plt.title('Hit Rate vs Miss Rate')
# plt.grid(True)
# plt.show()

import matplotlib.pyplot as plt

hit_rates = []
miss_rates = []
cache_sizes = []
# Function to read hit and miss rates from the text
def read_rates(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            # Split the line by commas and extract miss_rate and cache_size
            hit_rate, miss_rate, cache_size, _, _ = map(float, line.split(','))
            hit_rates.append(hit_rate)
            miss_rates.append(miss_rate)
            cache_sizes.append(int(cache_size))

    return hit_rates, miss_rates, cache_sizes

# Path to the text file containing hit/miss rates for different cache sizes
file_path = 'Q2Ans.txt'

# Read rates from the file
trace_data = read_rates(file_path)

# Plotting graphs for each trace file
for trace, data in trace_data.items():
    cache_sizes = data['cache_sizes']
    miss_rates = data['miss_rates']
    hit_rates = data['hit_rates']

    # Plotting Miss Rate vs Cache Size
    plt.figure(figsize=(10, 6))
    plt.plot(cache_sizes, miss_rates, marker='o')
    plt.xlabel('Cache Size (KB)')
    plt.ylabel('Miss Rate')
    plt.title(f'Miss Rate vs Cache Size for {trace}')
    plt.grid(True)
    plt.show()

    # Plotting Hit Rate vs Miss Rate
    plt.figure(figsize=(10, 6))
    plt.plot(miss_rates, hit_rates, marker='o')
    plt.xlabel('Miss Rate')
    plt.ylabel('Hit Rate')
    plt.title(f'Hit Rate vs Miss Rate for {trace}')
    plt.grid(True)
    plt.show()
