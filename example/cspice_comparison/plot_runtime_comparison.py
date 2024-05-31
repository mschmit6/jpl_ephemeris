import matplotlib.pyplot as plt

def plot_scatter(title, x_label, y_label, cspice_file, jpl_ephem_file, error_file):
    # Read data from files
    with open(cspice_file, 'r') as f1:
        cspice_data = [float(line) for line in f1.readlines()]

    with open(jpl_ephem_file, 'r') as f2:
        jpl_ephem_data = [float(line) for line in f2.readlines()]

    with open(error_file, 'r') as f2:
        error_data = [float(line) for line in f2.readlines()]

    ind = [k+1 for k in range(len(cspice_data))]

    # Create a scatter plot
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 8))
    fig.suptitle("Comparison Between CSpice and JPL Ephem Libraries")

    # Plot runtimes
    ax1.set_title(title)
    ax1.scatter(ind, jpl_ephem_data, color='green', label="JPL Ephem")
    ax1.scatter(ind, cspice_data, color='blue', label="cspice")
    ax1.set_yscale('log')  # Set the y-axis to log scale
    ax1.set_xlabel(x_label)
    ax1.set_ylabel(y_label)
    ax1.legend()
    ax1.grid()

    # Plot errors
    ax2.set_title("Error (m)")
    ax2.scatter(ind, error_data, color='red', label="JPL Ephem")
    ax2.set_yscale('log')  # Set the y-axis to log scale
    ax2.set_xlabel(x_label)
    ax2.set_ylabel("Error (m)")
    ax2.grid()

    # Show the plot
    plt.show()

# Example usage:
cspice_file = 'runtime_cspice.txt'  # Replace with your first data file path
jpl_ephem_file = 'runtime_jpl_ephem.txt'  # Replace with your second data file path
error_file = 'computed_error.txt'
title = 'Runtime Comparison'  # Replace with your desired plot title
x_label = 'Run Index'  # Replace with your desired x-label
y_label = 'Runtime (sec)'  # Replace with your desired y-label

plot_scatter(title, x_label, y_label, cspice_file, jpl_ephem_file, error_file)