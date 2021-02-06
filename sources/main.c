
#include <stdio.h>
#include <stdlib.h>

#include "solution.h"

static double export_solution(solution_t *s)
{
	FILE* output = fopen(OUTPUT_GRAPH_FILE, "w");
	sol_node_t* node = s->solution;
	pipe_t* pipe;
	double lenght = 0.0;

	if (output == NULL)
		dprintf(1, "Error: File '%s' cannot be opened", OUTPUT_GRAPH_FILE);
	while (node != NULL)
	{
		pipe = node->pipe;
		if (output != NULL)
			fprintf(output, "%lu %lu\n", pipe->left->id, pipe->right->id);
		lenght += (double)node->weight;
		pipe_destroy(pipe);
		node = node->next;
	}
	if (output != NULL)
		fclose(output);
	return lenght;
}

static int start_algo(solution_t *solution, size_t population)
{
	int count;

	count = load_cities(population, solution);
	if (count < 0)
	{
		dprintf(1, "No cities load\n");
		return 1;
	}
	solution->countdown = ((size_t) count) - 1;
	if (algo(solution))
	{
		dprintf(1, "Error: Algo failed");
		return 1;
	}
	return 0;
}

int main(int ac, char **av)
{
	size_t population;
	solution_t solution;
	double lenght;

	solution_init(&solution);
	if (ac <= 1)
		return dprintf(1, "Error: Please give a population size\n"), 84;
	population = (size_t)atol(av[1]);
	if (start_algo(&solution, population))
		return 84;
	lenght = export_solution(&solution);
	end_cities(solution.cities, population, lenght);
	solution_end(&solution);
	return (0);
}