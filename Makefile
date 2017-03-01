CC = g++ 
FLAGS = -Wall -O3 -std=c++11 -I.
FLOBJ = $(FLAGS) -c
FLEXE = $(FLAGS) -o $@ $^

TIE_BREAK_POLICY = neighbor_future_degree_tie_break_policy.o tie_break_policy.o
TRIANGULATION = $(TIE_BREAK_POLICY) triangulation.o tie_break_min_fill_triangulation.o tie_break_partial_min_fill_triangulation.o
FIRST_CLUSTER_HEURISTIC = max_min_fill_first_cluster_heuristic.o min_fill_first_cluster_heuristic.o
NEXT_VERTICES = tie_break_min_fill_next_vertices_heuristic.o
HEURISTIC_TREE_DECOMPOSITION = $(FIRST_CLUSTER_HEURISTIC) $(NEXT_VERTICES) connected_component.o enhanced_heuristic_tree_decomposition.o next_vertices_heuristic.o
TRIANGULATION_TREE_DECOMPOSITION = triangulation_tree_decomposition.o
FIRST_CLIQUE_HEURISTIC = 
TREE_DECOMPOSITION = $(HEURISTIC_TREE_DECOMPOSITION) $(FIRST_CLIQUE_HEURISTIC) $(TRIANGULATION_TREE_DECOMPOSITION) tree_decomposition.o

minfillbg_mrs: child_node.o cluster_node.o cluster_tree.o light_graph.o order.o signal_handler.o vertex_set.o $(TRIANGULATION) $(TREE_DECOMPOSITION) main.cpp 
	$(CC) $(FLEXE)

%.o: %.cpp %.h
	$(CC) $(FLOBJ) $<

clean:
	rm -f *.o
	rm -f minfillbg_mrs
