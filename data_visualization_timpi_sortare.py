import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt


data = {
    'Algoritm': ['Heapsort', 'Mergesort', 'Quicksort(pivot la final)', 'Quicksort(pivot la mijloc)', 'Counting Sort', 'std::sort'],
    'Test 1': [0.119, 0.053, 0.039, 0.036, 0.009, 0.056],
    'Test 2': [0.169, 0.088, 0.061, 0.062, 0.013, 0.068],
    'Test 3': [0.159, 0.068, 0.051, 0.045, 0.011, 0.081]
}

sns.set_style("whitegrid")

# asta face ploturile liniar
def linear_plot():
    df = pd.DataFrame(data)
    colors = sns.color_palette("husl", 6)
    fig, axes = plt.subplots(3, 2, figsize=(14, 10))
    axes = axes.flatten()
    for i, ax in enumerate(axes):
        if i < len(df): 
            sort_algorithm = df.iloc[i]['Algoritm']
            times = df.iloc[i][1:].values  
            linestyle = ['-', '--', '-.', ':'][i % 4]  
            marker = ['o', 's', '^', 'd'][i % 4]  
            color = colors[i]
            ax.plot(range(1, 4), times, marker=marker, color=color, linestyle=linestyle,linewidth = 2, markersize=8)
            ax.set_title(sort_algorithm, fontsize=14, fontweight='bold', pad=20)  
            ax.set_xlabel('Test', fontsize=12)
            ax.set_ylabel('Time (s)', fontsize=12)
            ax.set_xticks(range(1, 4))  
            ax.tick_params(axis='both', labelsize=10)
            ax.grid(True, linestyle='--', alpha=0.7)  
    plt.tight_layout()
    plt.savefig("visualization.png", dpi=300) 
    plt.show()

# ploturile sunt polinomiale
def polynomial_plot():
    df = pd.DataFrame(data)
    colors = sns.color_palette("husl", 6)
    fig, axes = plt.subplots(3, 2, figsize=(14, 10))
    axes = axes.flatten()
    for i, ax in enumerate(axes):
        if i < len(df):  
            sort_algorithm = df.iloc[i]['Algoritm']
            times = df.iloc[i][1:].sort_values().values.astype(float) 
            x = np.arange(1, 4)
            y = times
            z = np.polyfit(x, y,2)  
            p = np.poly1d(z)
            ax.plot(x, y, marker='o', color=colors[i], linestyle='')
            ax.plot(x, p(x), color='skyblue', linestyle='-', linewidth=2)
            ax.set_title(sort_algorithm, fontsize=14, fontweight='bold', pad=20)  
            ax.set_xlabel('Test', fontsize=12)
            ax.set_ylabel('Time (s)', fontsize=12)
            ax.set_xticks(range(1, 4)) 
            ax.tick_params(axis='both', labelsize=10)
            ax.grid(True, linestyle='--', alpha=0.7)  
    plt.tight_layout()
    plt.savefig("visualization.png", dpi=300)  
    plt.show()

polynomial_plot()