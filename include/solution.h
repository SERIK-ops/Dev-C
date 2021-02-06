#ifndef __ALGO_H_
#define __ALGO_H_

#include "cities.h"
#include "pipes.h"
#include "binary.h"


//Chemin vers le fichier d entree 
//Ce fichier doit contenir des données sur les villes
#ifndef INPUT_FILE
#define INPUT_FILE "resources/cities.csv"
#endif


// Chemin vers le fichier de sortie des villes 
//Dans ce fichier seront stockées des données sur les villes filtrées
#ifndef OUTPUT_CITIES_FILE
#define OUTPUT_CITIES_FILE "output/output_cities.dat"
#endif
//Chemin vers le fichier de sortie graphique
// Dans ces fichiers seront stockées des données sur la solution de chemin optimal
#ifndef OUTPUT_GRAPH_FILE
#define OUTPUT_GRAPH_FILE "output/output_graph.dat"
#endif
/*
* structure qui stocke un pipe validé de la solution optimale
*/
typedef struct sol_node_s {
	float weight;
	pipe_t* pipe;
	struct sol_node_s* next;
} sol_node_t;
/*
* structure contenant toutes les instances de villes
* et la solution validée
*/
typedef struct solution_s {
	size_t countdown;
	city_t* cities;
	city_grp_t* groups;
	bin_heap_t* pipes;
	sol_node_t* solution;
	sol_node_t* last;
} solution_t;

// cities_load.c
int load_cities(size_t population, solution_t* s);
int end_cities(city_t* cities, size_t population, double lenght);

// pipes.c
int pipe_two_cities(solution_t* s, city_t* first, city_t* second);

// solution.c
int algo(solution_t* solution);
void solution_init(solution_t* solution);
void solution_end(solution_t* solution);
void solution_dump(solution_t* solution);


#endif // !__ALGO_H_
