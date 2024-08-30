import matplotlib.pyplot as plt

# Function to read hit and miss rates from a single file
def read_rates(file_path):
    miss_rates = []
    block_sizes = []

    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            # Split the line by commas and extract miss_rate and block_size
            _, miss_rate, _, block_size, _ = map(float, line.split(','))
            miss_rates.append(miss_rate)
            block_sizes.append(int(block_size))

    return miss_rates, block_sizes

# Path to the text file containing hit/miss rates for different block sizes
file_path = 'Memory-Cache/test_c.txt'

# Read rates from the file
miss_rates, block_sizes = read_rates(file_path)

# Plotting Miss Rate vs Block Size
plt.figure(figsize=(10, 6))
plt.plot(block_sizes, miss_rates, marker='o')
plt.xlabel('Block Size (Bytes)')
plt.ylabel('Miss Rate')
plt.title('Miss Rate vs Block Size')
plt.grid(True)
plt.show()
