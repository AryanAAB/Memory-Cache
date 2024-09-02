import matplotlib.pyplot as plt

# Function to read hit rates and associativities from the file
def read_rates(file_path):
    data = {
        "gcc": {"hit_rates": [], "num_ways": []},
        "gzip": {"hit_rates": [], "num_ways": []},
        "mcf": {"hit_rates": [], "num_ways": []},
        "swim": {"hit_rates": [], "num_ways": []},
        "twolf": {"hit_rates": [], "num_ways": []}
    }

    current_trace = None

    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            if line.strip().endswith('.trace'):
                current_trace = line.strip().replace('.trace', '')
            else:
                hit_rate, _, _, _, num_ways = map(float, line.split(','))
                data[current_trace]["hit_rates"].append(hit_rate)
                data[current_trace]["num_ways"].append(int(num_ways))

    return data

# Path to the text file containing the data
file_path = 'Q4Ans.txt'

# Read rates from the file
data = read_rates(file_path)

# Plotting for each trace
for trace, values in data.items():
    plt.figure(figsize=(8, 6))
    plt.plot(values["num_ways"], values["hit_rates"], marker='o')
    plt.xlabel('Associativity (Number of Ways)')
    plt.ylabel('Hit Rate')
    plt.title(f'Hit Rate vs Associativity (Number of Ways) for {trace}')
    plt.grid(True)
    plt.show()

# # Plotting Hit Rate vs Associativity (Number of Ways) for all traces
# plt.figure(figsize=(12, 8))
# for trace, values in data.items():
#     plt.plot(values["num_ways"], values["hit_rates"], marker='o', label=trace)

# plt.xlabel('Associativity (Number of Ways)')
# plt.ylabel('Hit Rate')
# plt.title('Hit Rate vs Associativity (Number of Ways) for All Traces')
# plt.grid(True)
# plt.legend()
# plt.show()
