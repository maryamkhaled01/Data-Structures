# //////////////////////////Priority Queue Implementation////////////////////////
heapsize = 0
heapList = []


def shiftUp(i):
    global heapList
    parent = (i-1) // 2
    while i > 0 and heapList[parent][0] > heapList[i][0]:
        # Swap parent and current node
        (heapList[i], heapList[parent]) = (heapList[parent], heapList[i])
        # Update i to parent of i
        i = (i-1) // 2


def shiftDown(i):
    global heapList
    global heapsize
    mini = i
    l = 2 * i + 1
    r = 2 * i + 2
    if l < heapsize and heapList[i][0] > heapList[l][0]:
        mini = l
    if r < heapsize and heapList[mini][0] > heapList[r][0]:
        mini = r
    if mini != i:
        (heapList[i], heapList[mini]) = (heapList[mini], heapList[i])
        shiftDown(mini)


def buildHeap(arr):
    global heapsize
    global heapList
    n = len(arr)
    for i in range(n):
        #            priority, index
        heapList.append([arr[i], i])
        heapsize = heapsize + 1

    # for i in range(n):
        #heapsize = heapsize + 1


def deleteMin():
    global heapsize
    (heapList[heapsize - 1], heapList[0]) = (heapList[0], heapList[heapsize - 1])
    heapsize = heapsize - 1
    shiftDown(0)
    u = heapList[heapsize][1]
    return u


def isEmpty():
    if heapsize == 0:
        return True
    return False


def updatePriority(index, priority):
    global heapList
    heapList[index][0] = priority
    shiftUp(index)


# //////////////////////////// Prim's MST Algorithm ///////////////////////////////////
def printMST(graph, vertices):
    inf = 99999999999.9
    # array for vertices' parent
    parent = []
    # array to vertices' distance
    distance = []
    # array to check if the vertex is in the MST or not
    mstSet = []

    # initialize all distances as infinite
    for i in range(vertices):
        parent.append(-1)
        distance.append(inf)
        mstSet.append(False)
    # pick vertex r = first vertex and set its distance = 0, parent = null(-1)
    distance[0] = 0
    # insert all vertices in a priority queue (min heap)
    buildHeap(distance)   # V -> buildHeap

    # O(ElogV)
    while not isEmpty():     # VlogV -> deleteMin
        v = deleteMin()
        mstSet[v] = True
        for u in range(vertices):        # ElogV -> update edges
            if graph[v][u] != 0 and mstSet[u] == False and graph[v][u] < distance[u]:
                parent[u] = v
                distance[u] = graph[v][u]
                updatePriority(u, graph[v][u])

    print('Edges: Weight')
    for i in range(vertices):
        if i != distance[i]:   # in order not to print first vertex as it has no parent
            print(str(parent[i]), '-', str(i), ': ', str(distance[i]))


# /////////////////////// MAIN /////////////////////////
V = 5
G = [[0, 2, 0, 6, 0],
     [2, 0, 3, 8, 5],
     [0, 3, 0, 0, 7],
     [6, 8, 0, 0, 9],
     [0, 5, 7, 9, 0]]
printMST(G, V)
