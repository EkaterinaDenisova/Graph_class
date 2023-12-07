#include "pch.h"
#include "../ConsoleApplication_Graph/Graph.h"


using namespace std;
// тестирование вставки вершин
TEST(TestGraph, TestInsertVertex) {

	Graph<int> g1(2);
	EXPECT_EQ(g1.NumberOfVertices(),0);
	EXPECT_EQ(g1.GetMaxSize(), 2);

	g1.InsertVertex(1);
	g1.InsertVertex(5);

	EXPECT_EQ(g1.NumberOfVertices(), 2);
	EXPECT_EQ(g1.GetMaxSize(), 2);

	g1.InsertVertex(8);
	EXPECT_EQ(g1.NumberOfVertices(), 3);
	EXPECT_EQ(g1.GetMaxSize(), 4);

	// проверяем список вершин
	vector<int> v1 = {1, 5, 8};
	vector<int> v2 = g1.GetVertexList();
	EXPECT_EQ(v1, v2);
  
}

// тестирование вставки рёбер и получения веса
TEST(TestGraph, TestInsertEdge) {

	Graph<int> g1(2);
	

	g1.InsertVertex(1); g1.InsertVertex(5); g1.InsertVertex(8);
	
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);

	// проверяем вес рёбер
	EXPECT_EQ(20, g1.GetWeight(1,5));
	EXPECT_EQ(12, g1.GetWeight(5, 1));
	EXPECT_EQ(45, g1.GetWeight(5, 8));
	EXPECT_EQ(0, g1.GetWeight(1, 8)); // 0 означает,  что ребра нет, но обе вершины существуют

	// проверка веса ребра несуществующей вершины
	try {
		g1.GetWeight(5, 9);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}
}

// тестирование удаления вершины
TEST(TestGraph, TestDeleteVertex) {
	Graph<int> g1(2);
	
	// удаление из пустого графа
	try {
		g1.DeleteVertex(13);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}
	//g1.DeleteVertex(13);

	g1.InsertVertex(1); g1.InsertVertex(5); g1.InsertVertex(8);
	g1.InsertVertex(2); g1.InsertVertex(13);

	// удаление вершины без связей
	g1.DeleteVertex(2);
	vector<int> v1 = { 1, 5, 8, 13 };
	EXPECT_EQ(v1, g1.GetVertexList());


	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(13, 1, 49);

	// удаление вершины, у которой были соседи
	g1.DeleteVertex(5);

	v1 = { 13 }; 
	EXPECT_EQ(v1, g1.GetNeighbors(1));
	EXPECT_EQ(v1, g1.GetNeighbors(8));
	v1 = {1, 8};
	EXPECT_EQ(v1, g1.GetNeighbors(13));

}

// тестирование удаления ребра
TEST(TestGraph, TestDeleteEdge) {
	Graph<int> g1(2);

	// удаление из пустого графа
	try {
		g1.DeleteEdge(13,1);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}
	//g1.DeleteVertex(13);

	g1.InsertVertex(1); g1.InsertVertex(5); g1.InsertVertex(8);
	g1.InsertVertex(2); g1.InsertVertex(13);

	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// удаление несуществующего ребра
	g1.DeleteEdge(5,13);
	
	EXPECT_EQ(0, g1.GetWeight(5, 13));

	// удаление ребра
	EXPECT_EQ(20, g1.GetWeight(1,5));
	g1.DeleteEdge(1, 5);
	EXPECT_EQ(0, g1.GetWeight(1, 5));

}

// проверка соседей
TEST(TestGraph, TestNeighbors) {
	Graph<int> g1(2);


	g1.InsertVertex(1); g1.InsertVertex(5); g1.InsertVertex(8);
	g1.InsertVertex(2); g1.InsertVertex(13); 

	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// проверка соседей для вершины 1
	vector<int> v1 = {5, 13};
	vector<int> v2 = {5};
	EXPECT_EQ(v1, g1.GetNeighbors(1));
	EXPECT_EQ(v2, g1.GetFolowers(1));

	// для вершины 5
	v1 = { 1, 8, 2 }; v2 = { 1, 8 };
	EXPECT_EQ(v1, g1.GetNeighbors(5));
	EXPECT_EQ(v2, g1.GetFolowers(5));

	// для вершины 8
	v1 = {5, 13}; v2 = {13};
	EXPECT_EQ(v1, g1.GetNeighbors(8));
	EXPECT_EQ(v2, g1.GetFolowers(8));

	// для вершины 2
	v1 = { 5, 13 }; v2 = { 5, 13 };
	EXPECT_EQ(v1, g1.GetNeighbors(2));
	EXPECT_EQ(v2, g1.GetFolowers(2));

	// для вершины 13
	v1 = { 1, 8, 2 }; v2 = { 1 };
	EXPECT_EQ(v1, g1.GetNeighbors(13));
	EXPECT_EQ(v2, g1.GetFolowers(13));

	// для несуществующей вершины
	try {
		v1 = g1.GetNeighbors(9);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}

	// для несуществующей вершины
	try {
		v1 = g1.GetFolowers(9);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}

	
}

// Тестирование обходов в глубину и ширину
TEST(TestGraph, TestSearch) {
	Graph<int> g1(2);

	g1.InsertVertex(1); g1.InsertVertex(5); g1.InsertVertex(8);
	g1.InsertVertex(2); g1.InsertVertex(13);

	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// для вершины 5
	vector<int> v = {5, 8, 13, 1};
	vector<int> v1 = g1.DepthFirstSearch(5);
	EXPECT_EQ(v1,v);
	v = {5, 1, 8, 13};
	v1 = g1.BreadthFirstSearch(5);
	EXPECT_EQ(v1, v);

	// для вершины 2
	v = { 2, 13, 1, 5, 8};
	v1 = g1.DepthFirstSearch(2);
	EXPECT_EQ(v1, v);
	v = { 2, 5, 13, 1, 8 };
	v1 = g1.BreadthFirstSearch(2);
	EXPECT_EQ(v1, v);
}
