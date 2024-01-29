import heapq


def dijkstra(graph, start):
    # Initialize the distance and parent dictionaries and heap
    distances = {vertex: float('inf') for vertex in graph}
    distances[start] = 0
    parents = {vertex: None for vertex in graph}
    heap = [(0, start)]
    # O(ElogV)
    while heap:
        # Get the vertex with the shortest distance from the heap
        current_distance, current_vertex = heapq.heappop(heap)      # VlogV -> extractMin

        # Skip the vertex if we have already found a shorter path
        if current_distance > distances[current_vertex]:
            continue

        # Update the distances and parents of the neighboring vertices
        for neighbor, weight in graph[current_vertex].items():     # ElogV -> relax
            distance = current_distance + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                parents[neighbor] = current_vertex
                heapq.heappush(heap, (distance, neighbor))

    return distances, parents


def print_shortest_path(distances, parents, destination):
    path = []
    vertex = destination
    while vertex:
        path.append(vertex)
        vertex = parents[vertex]
    path.reverse()
    print(' -> '.join(path), f'(distance: {distances[destination]})')


def check_negative_edge(g):
    # detect if there is a negative edge
    for i in g:
        for j in g[i]:
            if g[i][j] < 0:
                return False
    return True


graph = {
    'A': {'B': 2, 'C': 5},
    'B': {'D': 3},
    'C': {'D': 1, 'E': 6},
    'D': {'E': 2},
    'E': {}
}

if check_negative_edge(graph):
    start = 'A'
    for i in graph:
        if i != 'A':
            distances, parents = dijkstra(graph, start)
            print_shortest_path(distances, parents, i)
else:
    print("Error! There is a negative edge, Cannot be solved using Dijkstra's Algorithm")