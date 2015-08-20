#Description: This file includes implementation of local search algorithms:
#               1. Hill Climbing
#               2. Simulated Annealing
#               3. Genetic Algorithms


import math
import sys
import random #for use in simulated annealing
from random import randint


#functions for testing the local search algorithms
def easy(var):
    x = var[0]
    y = var[1]
    z = var[2]
    k = var[3]
    return ((x-10)**2 + (y+8)**2 + z**2 + k**2)

def medium(var):
    x = var[0] + 100
    y = var[1] + 100
    r = x**2 + y**2
    firstPart = (math.sin(x**2+(3 * y**2))/ (.1 + r))
    secondPart = (x**2 + 5 * (y**2)) * (( math.e ** (1-r))/2)
    return -(firstPart + secondPart)



def hard(var):
    a = int(var[0])
    b = int(var[1])
    c = int(var[2])
    d = int(var[3])
    e = int(var[4])
    f = int(var[5])
    g = int(var[6])
    h = int(var[7])
    i = int(var[8])
    j = int(var[9])
    penalty = 0
    if(a < 1 or a > 3):
        penalty += abs(a-1) * 100
    if(b < 1 or b > 3):
        penalty += abs(b-1) * 100
    if(c < 1 or c > 3):
        penalty += abs(c-1) * 100
    if(d < 1 or d > 3):
        penalty += abs(d-1) * 100
    if(e < 1 or e > 3):
        penalty += abs(e-1) * 100
    if(f < 1 or f > 3):
        penalty += abs(f-1) * 100
    if(g < 1 or g > 3):
        penalty += abs(g-1) * 100
    if(h < 1 or h > 3):
        penalty += abs(h-1) * 100
    if(j < 1 or j > 3):
        penalty += abs(j-1) * 100
    if(i < 1 or i > 3):
        penalty += abs(i-1) * 100

    if(a == b):
        penalty += 1
    if(a == c):
        penalty += 1
    if(c == d):
        penalty += 1
    if(b == c):
        penalty += 1
    if(d == e):
        penalty += 1
    if(d == f):
        penalty += 1
    if(f == g):
        penalty += 1
    if(e == g):
        penalty += 1
    if(g == h):
        penalty += 1
    if(h == i):
        penalty += 1
    if(h == j):
        penalty += 1
    if(i == j):
        penalty += 1

    return penalty


#function pointers
algPointers = {"easy": easy, "medium": medium, "hard": hard}

def hillClimbing(var):
    size = int(var[1])
    values = [0] * size #initializing a list of zeros to start with
    current = algPointers[var[0]](values) #get the initial function value
    neighbor = -sys.maxsize

    iter = 1
    while(neighbor < current):
        #need to force the algorithm to look around at least once
        if(iter > 1):
            current = neighbor
        neighbor = sys.maxsize
        newValues = values.copy()

        for i in range(size):
            #increment
            tempValues = values.copy() #need to store the array of values
            tempValues[i] += 2
            tempNeighbor = algPointers[var[0]](tempValues) #get the current value
            if(tempNeighbor < neighbor):
                neighbor = tempNeighbor
                newValues = tempValues.copy()

            #decrement
            tempValues = values.copy() #need to store the array of values
            tempValues[i] -= 2
            tempNeighbor = algPointers[var[0]](tempValues) #get the current value
            if(tempNeighbor < neighbor):
                neighbor = tempNeighbor
                newValues = tempValues.copy()

        iter += 1
        values = newValues.copy()

    #print("Min achieved at: " + str(values))
    return current

def simulatedAnnealing(var):
    size = int(var[1])
    values = [0] * size #initializing a list of zeros to start with

    current = algPointers[var[0]](values) #get the initial function value

    temp = 50 #the temperature that yields the most random results in this case
    change = .00001 #cooling rate
    while(temp > 1):

        #generate a random successor to current
        tempValues = values.copy()
        index = random.randint(0, size - 1)
        tempValues[index] += random.choice([-1, 1])
        successor = algPointers[var[0]](tempValues)

        delta = current - successor #flipped since we're minimizing
        #keep the successor if it's better
        if(delta > 0):
            current = successor
            values = tempValues.copy()
        #let probability decide whether or not to keep it if it's not
        else:
            if(math.e ** (delta/temp) > random.random()):
                current = successor
                values = tempValues.copy()
        temp -= change

    return current

def geneticAlgorithm(var):
    size = int(var[1])
    values = [0] * size
    fittest = algPointers[var[0]](values) #get the initial fittest

    popSize = 100
    population = list()
    fitnessValues = list()
    pool = list() #pool of possible members to be selected for crossover


    #first need to generate a random population
    for i in range(popSize):
        tempValues = values.copy()
        for j in range(size):
            tempValues[j] += randint(-10, 10)

        population.append(tempValues)

    generations = 600 # number of generations
    for generation in range(generations):
        pool.clear()
        fitnessValues.clear()

        sumFitness = 0 #store the total fitness sum to be used in random selection

        #generate the fitness values for each member of the population
        #keep track of the current fittest value
        tempFittest = algPointers[var[0]](population[0])
        for i in range(popSize):
            fitLevel = algPointers[var[0]](population[i])
            fitness = fittest - fitLevel
            if(fitLevel < tempFittest):
                tempFittest = fitLevel
            fitnessValues.append(fitness)
            sumFitness += fitness

        #update the current fittest value
        fittest = tempFittest
        if(sumFitness <= 0):
            sumFitness = 1

        #prepare the population for random selection
        for i in range(popSize):
            #calculate number of insertions to list of possible values
            insertions = int((fitnessValues[i]/sumFitness) * 100)

            #only add member's that don't improve fittest value once
            if(insertions < 1):
                pool.append(population[i])
            else:
                for j in range(insertions):
                    pool.append(population[i])

        newPopulation = list()
        for i in range(popSize):
            x = pool[randint(0, len(pool) - 1)]
            y = pool[randint(0, len(pool) - 1)]
            #choose a random point to crossover
            crossoverPoint = random.randint(0, size - 1)
            child = x[:crossoverPoint] + y[crossoverPoint:]

            #2% chance of mutation
            if(random.random() <= 0.10):
                child[random.randint(0, size - 1)] = random.randint(-10, 10)

            newPopulation.append(child) #add the child to the new population

        population = newPopulation.copy()

    return fittest








# vars = ["easy", 4]
# print("Hill climbing min for easy: " + str(hillClimbing(vars)))
#
# vars = ["medium", 2]
# print("Hill climbing min for medium: " + str(hillClimbing(vars)))
#
# vars = ["hard", 10]
# print("Hill climbing min for hard: " + str(hillClimbing(vars)) + "\n")
#
# vars = ["easy", 4]
# print("Simulated annealing min for easy: " + str(simulatedAnnealing(vars)))

# vars = ["medium", 2]
# print("Simulated annealing min for medium: " + str(simulatedAnnealing(vars)))

# vars = ["hard", 10]
# print("Simulated annealing min for hard: " + str(simulatedAnnealing(vars)) + "\n")

# vars = ["easy", 4]
# print("Genetic algorithm min for easy: " + str(geneticAlgorithm(vars)))
#
vars = ["medium", 2]
print("Genetic algorithm min for medium: " + str(geneticAlgorithm(vars)))
#
# vars = ["hard", 10]
# print("Genetic algorithm min for hard: " + str(geneticAlgorithm(vars)))
