
make.x: MakeTree.o TreeNode.o GraphNode.o Reader.o DepGraph.o soln_main.o systemInterface.o
	g++ -std=c++11 -ggdb MakeTree.o TreeNode.o GraphNode.o Reader.o DepGraph.o  soln_main.o systemInterface.o -o make.x

MakeTree.o: MakeTree.cpp MakeTree.hpp TreeNode.hpp GraphNode.hpp
	g++ -std=c++11 -ggdb MakeTree.cpp -o MakeTree.o -c

TreeNode.o: TreeNode.cpp TreeNode.hpp
	g++ -std=c++11 -ggdb TreeNode.cpp -o TreeNode.o -c

GraphNode.o: GraphNode.cpp GraphNode.hpp
	g++ -std=c++11 -ggdb GraphNode.cpp -o GraphNode.o -c

Reader.o: Reader.cpp Reader.hpp Token.hpp
	g++ -std=c++11 -ggdb Reader.cpp -o Reader.o -c

DepGraph.o: DepGraph.cpp DepGraph.hpp GraphNode.hpp TreeNode.hpp systemInterface.hpp
	g++ -std=c++11 -ggdb DepGraph.cpp -o DepGraph.o -c

soln_main.o: soln_main.cpp DepGraph.hpp
	g++ -std=c++11 -ggdb soln_main.cpp -o soln_main.o -c

systemInterface.o: systemInterface.hpp systemInterface.cpp
	g++ -std=c++11 -c systemInterface.cpp -o systemInterface.o

clean:
	rm -f *.o make.x *~
