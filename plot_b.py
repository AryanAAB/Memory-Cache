import matplotlib.pyplot as plt

# Function to read hit and miss rates from the file
def read_rates(file_path):
    data = {
        "gcc": {"hit_rates": [], "miss_rates": [], "cache_sizes": []},
        "gzip": {"hit_rates": [], "miss_rates": [], "cache_sizes": []},
        "mcf": {"hit_rates": [], "miss_rates": [], "cache_sizes": []},
        "swim": {"hit_rates": [], "miss_rates": [], "cache_sizes": []},
        "twolf": {"hit_rates": [], "miss_rates": [], "cache_sizes": []}
    }

    current_trace = None

    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            if line.strip().endswith('.trace'):
                current_trace = line.strip().replace('.trace', '')
            else:
                hit_rate, miss_rate, cache_size, _, _ = map(float, line.split(','))
                data[current_trace]["hit_rates"].append(hit_rate)
                data[current_trace]["miss_rates"].append(miss_rate)
                data[current_trace]["cache_sizes"].append(int(cache_size))

    return data

# Path to the text file containing the data
file_path = 'Q2Ans.txt'

# Read rates from the file
data = read_rates(file_path)

diff = 0.000001

# Plotting for each trace
for trace, values in data.items():
    # Plot Miss Rate vs Cache Size
    plt.figure(figsize=(8, 6))
    plt.plot(values["cache_sizes"], values["miss_rates"], marker='o')
    plt.xlabel('Cache Size (KB)')
    plt.ylabel('Miss Rate')
    plt.title(f'Miss Rate vs Cache Size for {trace}')
    plt.ylim(min(values["miss_rates"]) - diff, max(values["miss_rates"]) + diff)  # Adjusting y-axis for precision
    plt.grid(True)
    plt.show()

# # Plotting Miss Rate vs Cache Size for all traces on the same graph
# plt.figure(figsize=(12, 8))
# for trace, values in data.items():
#     plt.plot(values["cache_sizes"], values["miss_rates"], marker='o', label=trace)

# plt.xlabel('Cache Size (KB)')
# plt.ylabel('Miss Rate')
# plt.title('Miss Rate vs Cache Size for All Traces')
# plt.grid(True)
# plt.legend()
# plt.ylim(0, max(max(values["miss_rates"]) for values in data.values()) + 0.05)  # Adjust y-axis for all traces
# plt.show()

