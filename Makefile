prim.o: prim.c
	gcc -c prim.c
prim: prim.o
	gcc prim.o -o prim
kruskal.o: kruskal.c
	gcc -c kruskal.c
kruskal: kruskal.o
	gcc kruskal.o -o kruskal
