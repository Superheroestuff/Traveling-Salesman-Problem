# Traveling-Salesman-Problem

Explanation of TSP -> https://en.wikipedia.org/wiki/Travelling_salesman_problem

This is a project for course Artifitial Intelligence. 
The project solves TSP problem using Genetic Algorithm.
(Explanation of GA -> https://en.wikipedia.org/wiki/Genetic_algorithm)

Helping notes:
<ul>
  <li>the Towns are represented as points in 2D coord. system;</li>
  <li>Chromosome is a set of all Towns;</li>
  <li>Population is a set of Chromosomes;</li>
  <li>every Chromosome has a fitness - the total distance between the towns (considering the arrangement; distance between last and first town included);</li>
  <li>the iteration in this algorithm are fixed (30);</li>
  <li>the size of the population is fixed (5000);</li>
</ul>
The Genetic Algorithm is used as it follows:
 1. The input is the number of towns;
 2. Generates the towns represented as points;
 3. Generate the first population;
 4. Sorts the population by their fitness;
 5. Takes the first halp of the population, and trows away the second half a.k.a. the Weak Chromosomes;
 6. Start Crossover process (terminates when the population size is restored):
    -takes two chromosomes of the population that make two children;
    -adds the children to the population;
 7. If there are more iterations left -> go to step 4;
 
