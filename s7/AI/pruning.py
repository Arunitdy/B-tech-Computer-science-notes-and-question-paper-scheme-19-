# Minimax and Alpha-Beta Pruning demonstration

# Counter to keep track of nodes visited
nodes_visited_minimax = 0
nodes_visited_alphabeta = 0


# Normal Minimax function
def minimax(depth, node_index, maximizing_player, values, max_depth):
    global nodes_visited_minimax
    nodes_visited_minimax += 1

    # Base case: leaf node
    if depth == max_depth:
        return values[node_index]

    if maximizing_player:
        return max(
            minimax(depth + 1, node_index * 2, False, values, max_depth),
            minimax(depth + 1, node_index * 2 + 1, False, values, max_depth),
        )
    else:
        return min(
            minimax(depth + 1, node_index * 2, True, values, max_depth),
            minimax(depth + 1, node_index * 2 + 1, True, values, max_depth),
        )


# Minimax with Alpha-Beta pruning
def alphabeta(depth, node_index, maximizing_player, values, max_depth, alpha, beta):
    global nodes_visited_alphabeta
    nodes_visited_alphabeta += 1

    if depth == max_depth:
        return values[node_index]

    if maximizing_player:
        best = float("-inf")
        for i in range(2):
            val = alphabeta(depth + 1, node_index * 2 + i, False, values, max_depth, alpha, beta)
            best = max(best, val)
            alpha = max(alpha, best)

            # Pruning condition
            if beta <= alpha:
                break
        return best
    else:
        best = float("inf")
        for i in range(2):
            val = alphabeta(depth + 1, node_index * 2 + i, True, values, max_depth, alpha, beta)
            best = min(best, val)
            beta = min(beta, best)

            # Pruning condition
            if beta <= alpha:
                break
        return best


# Example game tree leaf values
values = [3, 5, 6, 9, 1, 2, 0, -1]   # Example leaf nodes
max_depth = 3

# Run normal minimax
best_value_minimax = minimax(0, 0, True, values, max_depth)

# Run minimax with alpha-beta pruning
best_value_alphabeta = alphabeta(0, 0, True, values, max_depth, float("-inf"), float("inf"))

print("==============================================")
print("Results of Minimax vs Alpha-Beta Pruning")
print("==============================================")
print(f"Leaf Node Values: {values}")
print(f"Best Value (Normal Minimax): {best_value_minimax}")
print(f"Best Value (Alpha-Beta Pruning): {best_value_alphabeta}")
print("----------------------------------------------")
print(f"Nodes explored in Minimax: {nodes_visited_minimax}")
print(f"Nodes explored in Alpha-Beta Pruning: {nodes_visited_alphabeta}")
print("----------------------------------------------")
print(f"Pruning saved: {nodes_visited_minimax - nodes_visited_alphabeta} nodes!")
