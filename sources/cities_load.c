#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cities.h"
#include "pipes.h"
#include "solution.h"

/*
*permet de sauter les informations inintéressantes à propos d'une ville dans le fichier d'entée
*/
static char* skip_file_columns(size_t amount)
{
	char* get = NULL;

	for (size_t i = 0; i < amount; ++i)
		get = strtok(NULL, ",");
	return get;
}

/*
*lis et prépare les informations d'une ville depuis le fichier d'entrée (resources/cities.csv)
*/
static int parse_file_line(char** name, size_t* pop, size_t min_population,
	float* longitude, float* latitude)
{
	char* tmp;

	*name = strdup(skip_file_columns(3));
	tmp = skip_file_columns(11);
	*pop = atoi(tmp);
	if (*pop < min_population)
	{
		free(*name);
		return 1;
	}
	tmp = skip_file_columns(5);
	*longitude = atof(tmp);
	tmp = skip_file_columns(1);
	*latitude = atof(tmp);
	return 0;
}

/*
*ajoute une nouvelle instance city_t à la liste des villes chargées
*/
static int append_city(solution_t *s, city_t* new)
{
	city_t* last = s->cities;
	city_grp_t* grp = new->group;

	if (last == NULL)
	{
		s->cities = new;
		s->groups = grp;
		return 0;
	}
	while (last->next != NULL)
	{
		if (pipe_two_cities(s, last, new))
			return 1;
		last = last->next;
	}
	last->group->next = grp;
	if (pipe_two_cities(s, last, new))
		return 1;
	last->next = new;
	return 0;
}

/*
*charge et instancie les villes avec la bonne taille de population
*/
int load_cities(size_t min_population, solution_t *s)
{
	char line[512];
	char* name;
	size_t pop;
	float longitude, latitude;
	city_t* new;
	int count = 0;
	FILE* file = fopen(INPUT_FILE, "r");

	if (file == NULL)
	{
		dprintf(1, "Error: File '%s' not found", INPUT_FILE);
		return -1;
	}
	printf("== Reading cities with population >= %lu from '%s' ==\n", min_population, INPUT_FILE);
	while (fgets(line, 512, file) != NULL)
	{
		strtok(line, ",");
		if (parse_file_line(&name, &pop, min_population, &longitude, &latitude))
			continue;
		new = city_create(name, pop, longitude, latitude);
		if (new == NULL || append_city(s, new))
			return -1;
		++count;
	}
	fclose(file);
	return count;
}

/*
*libère la mémoire utilisé par les instances city_t tout en remplissant le fichier de réponse (output/output_city.dat)
*/
int end_cities(city_t* cities, size_t population, double lenght)
{
	FILE* output = fopen(OUTPUT_CITIES_FILE, "w");
	city_t* city = cities;

	if (output == NULL)
	{
		dprintf(1, "Cannot open output file\n");
		return 1;
	}
	printf("== Writing cities with population >= %lu in '%s' ==\n", population, OUTPUT_CITIES_FILE);
	while (city != NULL)
	{
		cities = city->next;
		printf("%s %lu %f %f\n", city->name, city->population, city->longitude, city->latitude);
		fprintf(output, "%lu %f %f\n", city->population, city->longitude, city->latitude);
		city_destroy(city);
		city = cities;
	}
	printf("Longeur du réseau = %f km\n", lenght);
	fclose(output);
	return 0;
}
