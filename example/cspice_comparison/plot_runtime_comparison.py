import matplotlib.pyplot as plt

def plot_scatter(title, x_label, y_label, file1, file2):
    # Read data from files
    with open(file1, 'r') as f1:
        data1 = [float(line) for line in f1.readlines()]

    with open(file2, 'r') as f2:
        data2 = [float(line) for line in f2.readlines()]

    ind = [k+1 for k in range(len(data1))]

    # Create a scatter plot
    plt.scatter(ind, data1, label="cspice")
    plt.scatter(ind, data2, label="JPL Ephem")
    plt.yscale('log')  # Set the y-axis to log scale

    # Set title, x-label, and y-label
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)

    # Show the plot
    plt.grid()
    plt.legend()
    plt.show()

# Example usage:
file1 = 'runtime_cspice.txt'  # Replace with your first data file path
file2 = 'runtime_jpl_ephem.txt'  # Replace with your second data file path
title = 'Runtime Comparison'  # Replace with your desired plot title
x_label = 'Run Index'  # Replace with your desired x-label
y_label = 'Runtime (sec)'  # Replace with your desired y-label

plot_scatter(title, x_label, y_label, file1, file2)