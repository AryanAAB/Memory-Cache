import matplotlib.pyplot as plt

# Function to read hit rates and associativity from a single file
def read_rates(file_path):
    hit_rates = []
    associativities = []

    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            # Split the line by commas and extract hit_rate and associativity
            hit_rate, _, _, _, num_ways = map(float, line.split(','))
            hit_rates.append(hit_rate)
            associativities.append(int(num_ways))

    return hit_rates, associativities

# Path to the text file containing hit rates for different associativities
file_path = 'Memory-Cache/test_d.txt'

# Read rates from the file
hit_rates, associativities = read_rates(file_path)

# Plotting Hit Rate vs Associativity
plt.figure(figsize=(10, 6))
plt.plot(associativities, hit_rates, marker='o')
plt.xlabel('Associativity (Number of Ways)')
plt.ylabel('Hit Rate')
plt.title('Hit Rate vs Associativity')
plt.grid(True)
plt.show()
