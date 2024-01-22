
import networkx as nx
import matplotlib.pyplot as plt
G = nx.random_lobster(75, 0.5, 0.5)   # 100
nx.draw(G, node_color="orange")
plt.savefig("random_lobster.png")
print(G)

