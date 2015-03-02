#Author: Robert Grossman
#CMSC471- Spring 2015

import sys
from operator import itemgetter

inputFile = sys.argv[1]
searchType = sys.argv[2]
start = sys.argv[3]
goal = sys.argv[4]
outputFile = sys.argv[5]

def getPath(paths):
    path = list()
    current = goal
    while(current is not -1):
        path.append(current)
        current = paths[current]
    path.reverse()
    return path


def outputPath(path):
    f = open(outputFile, 'w')
    for node in path:
        f.write(node + "\n")
    f.close()
    return

def bfs(graph):
    q = list()
    q.append([start])
    visited = list()
    while q:
        #first pop the first item in the list
        currentPath = q.pop(0)
        #then get the node at the end of the popped path
        currentNode = currentPath[-1]
        #add the node so that you don't revisit it later
        visited.append(currentNode)
        #output the path if it's successful
        if(currentNode == goal):
            outputPath(currentPath)
            return
        #if the current node exists as a key, then add it's adjacent nodes to the list
        elif currentNode in graph.keys():
            for node in graph[currentNode]:
                #check to see if the node was visited first before you add it
                if(node not in visited):
                    nextPath = list(currentPath)
                    #add each node to the end of the path and add it to the queue
                    nextPath.append(node[0])
                    q.append(nextPath)
    #if no path was found then output that it didn't find anything
    f = open(outputFile, 'w')
    f.write("No path was found!\n")
    f.close()
    return

def dfs(graph, q, visted):
    #first get the current node
    currentPath = q.pop(0)
    currentNode = currentPath[-1]
    #if it's the goal node then output it's path to the correct file
    #and mark it as visited
    if(currentNode == goal):
        f = open(outputFile, 'w')
        for node in currentPath:
            f.write(node + "\n")
        f.close()
        visited.append(goal)
        return
    elif currentNode in graph.keys():
        for node in graph[currentNode]:
            #don't add nodes that have already been visited so that we don't
            #have an infinite loop
            if(node not in visited):
                visited.append(node)
                nextPath = list(currentPath)
                nextPath.append(node[0])
                q.append(nextPath)
                dfs(graph, q, visited)
                if goal in visited:
                    return
    return

def findMin(dist, unvisited):
    min = sys.maxsize
    v = unvisited[0]
    for node in unvisited:
        if(dist[node] < min):
            min = dist[node]
            v = node
    return v

def dijkstra(graph):
    dist = dict()
    paths = dict()
    unvisited = list()
    unvisited.append(start)
    dist[start] = 0
    paths[start] = -1

    #first need to get all vertices in the graph
    #and set their paths to undefined and their
    #distances to infinity.
    for node in graph:
        if(node not in unvisited):
            dist[node] = sys.maxsize
            paths[node] = -1

        for v in graph[node]:
            if(v[0] not in unvisited):
                unvisited.append(v[0])
                dist[v[0]] = sys.maxsize
                paths[v[0]] = -1

    #need to sort the list of unvisited for tie alphabetical tie-breaking
    unvisited = sorted(unvisited)
    while unvisited: #while there are still unvisited nodes
        v = findMin(dist, unvisited)
        unvisited.remove(v)

        if(v == goal):
            path = getPath(paths)
            f = open(outputFile, 'w')
            for node in path:
                f.write(node + "\n")
            f.close()
            return
        elif v in graph:
            for u in graph[v]:
                d = dist[v] + int(u[1])
                if d < dist[u[0]]:
                    dist[u[0]] = d
                    paths[u[0]] = v

    #if you get to this point, you didn't find what you're looking for,
    #so output an appropriate message.
    f = open(outputFile, 'w')
    f.write("No path was found!\n")
    f.close()
    return

def printGraph(graph):
    for p in graph:
        for t in graph[p]:
            print(p, ": ", t[0], ": ", t[1])
    return
"""
First need to read in the contents of the input and convert it to a graph.
A graph can be represented by a dictionary of vertex 'keys' mapped to a list of tuples 'values',
where each tuple consists of a vertex name and an edge weight.
"""
file = open(inputFile)
edges = file.readlines()
graph = {}
for line in edges:
    parent, child, weight = line.split()
    if parent in graph:
        graph[parent].append((child, weight))
    else:
        graph[parent] = [(child, weight)]

#Need to order each list for each vertex in the graph so
#that the searches work correctly. Sort by weight and then
#alphabetical order.
for v in graph:
    graph[v] = sorted(graph[v])

if (searchType == "Breadth"):
    bfs(graph)
elif (searchType == "Depth"):
    for v in graph:
        graph[v] = sorted(graph[v], reverse = True)
    q = list()
    q.append([start])
    visited = list()
    visited.append(start)
    dfs(graph, q, visited)
    if(goal not in visited):
        f = open(outputFile, 'w')
        f.write("No path was found!\n")
        f.close()

elif (searchType == "Uniform"):
    dijkstra(graph)
else:
    print("Invalid search type!")

