#ifndef __CITIES_H_
#define __CITIES_H_

#include <stddef.h>

#include "binary.h"

/*
** Represente un groupe de villes
*/
typedef struct city_grp_s {
	size_t				size;
	struct city_grp_s*	next;
} city_grp_t;

/*
** struct contenant toutes les donnees utiles sur une ville
*/
typedef struct city_s {
	size_t		id;
	char		*name;
	size_t		population;
	float		longitude;
	float		latitude;
	city_grp_t* group;
	struct city_s* next;
} city_t;


// cities.c
city_grp_t* city_grp_create();
city_t* city_create(char* name, size_t population, float longitude, float latitude);
void city_grp_destroy_all(city_grp_t* grp);
void city_destroy(city_t* city);

// cities_action.c
void city_leave_grp(city_t* city);
void city_join_grp(city_t* city, city_grp_t* grp);
void city_merge_grp(city_t* cities, city_grp_t* leave, city_grp_t* join);
void city_dump_all(city_t* cities);
void city_grp_append(city_grp_t* grp, city_t* city, city_t* all);

#endif // !__CITIES_H_
