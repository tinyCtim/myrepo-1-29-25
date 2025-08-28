import matplotlib.pyplot as plt
import random

points = []
for i in range(6):
    new_element = [random.randint(-1, 9),random.randint(-1, 9)]
    points.append(new_element)
# Plot the points and lines
plt.figure(figsize=(10, 10))

# Draw lines between point 0-1, 1-2, ..., 4-5
tot = 0
for i in range(5):
    x_values = [points[i][0], points[i+1][0]]
    y_values = [points[i][1], points[i+1][1]]
    plt.plot(x_values, y_values, marker='o', label=f'Point {i} to {i+1}')
    tot += ((points[i+1][0]-points[i][0])**2 + (points[i+1][1]-points[i][1])**2)**.5
# 0,0 is bottom left 1,1 is top right
# Add labels and grid
plt.text(-.1, -.1, f'total length : {tot:.2f}', transform=plt.gca().transAxes, fontsize=12)
plt.title("Lines Between Consecutive Points")
plt.xlabel("X")
plt.ylabel("Y")
plt.grid(True)
plt.legend()
plt.axis('equal')

# Show the plot
plt.show()

