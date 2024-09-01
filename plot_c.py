import matplotlib.pyplot as plt

# Function to read hit and miss rates from the file
def read_rates(file_path):
    data = {
        "gcc": {"hit_rates": [], "miss_rates": [], "block_sizes": []},
        "gzip": {"hit_rates": [], "miss_rates": [], "block_sizes": []},
        "mcf": {"hit_rates": [], "miss_rates": [], "block_sizes": []},
        "swim": {"hit_rates": [], "miss_rates": [], "block_sizes": []},
        "twolf": {"hit_rates": [], "miss_rates": [], "block_sizes": []}
    }

    current_trace = None

    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            if line.strip().endswith('.trace'):
                current_trace = line.strip().replace('.trace', '')
            else:
                hit_rate, miss_rate, _, block_size, _ = map(float, line.split(','))
                data[current_trace]["hit_rates"].append(hit_rate)
                data[current_trace]["miss_rates"].append(miss_rate)
                data[current_trace]["block_sizes"].append(int(block_size))

    return data

# Path to the text file containing the data
file_path = 'Q3Ans.txt'

# Read rates from the file
data = read_rates(file_path)

# Plotting for each trace
for trace, values in data.items():
    # Plot Block Size vs Miss Rate
    plt.figure(figsize=(8, 6))
    plt.plot(values["block_sizes"], values["miss_rates"], marker='o')
    plt.xlabel('Block Size (B)')
    plt.ylabel('Miss Rate')
    plt.title(f'Block Size vs Miss Rate for {trace}')
    plt.ylim(min(values["miss_rates"]) - 0.01, max(values["miss_rates"]) + 0.01)  # Adjusting y-axis for precision
    plt.grid(True)
    plt.show()

# # Plotting Block Size vs Miss Rate for all traces on the same graph
# plt.figure(figsize=(12, 8))
# for trace, values in data.items():
#     plt.plot(values["block_sizes"], values["miss_rates"], marker='o', label=trace)

# plt.xlabel('Block Size (B)')
# plt.ylabel('Miss Rate')
# plt.title('Block Size vs Miss Rate for All Traces')
# plt.grid(True)
# plt.legend()
# plt.ylim(0, max(max(values["miss_rates"]) for values in data.values()) + 0.01)  # Adjust y-axis for all traces
# plt.show()
