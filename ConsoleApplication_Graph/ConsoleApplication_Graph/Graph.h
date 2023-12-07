#pragma once
//author: Денисова Екатерина

#include <stdexcept> // для исключений
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>

#include "LinkedList.h"

using namespace std;

// класс Графа
template <typename T>
class Graph
{
private:
	// основные данные включают список вершин, матрицу смежности
	//и текущий размер (число вершин) графа
	LinkedList<T> vertexList; // список вершин
	int** edge;  // матрица смежности
	int graphsize; // число вершин в графе
	int maxGraphSize; // максимальное число вершин в графе

	// методы для поиска вершины и указания ее позиции в списке
	//int FindVertex(LinkedList<T>& L1, const T& vertex1);
	int GetVertexPos(const T& vertex1);

public:
	// конструктор с заданием максимального числа вершин maxsize
	Graph(int maxsize);

	// конструктор копирования и т.д

	// деструктор
	~Graph();

	// методы проверки графа
	bool GraphEmpty() const; // true, если граф пуст

	// методы обработки данных

	// количество вершин
	int NumberOfVertices() const;

	// количество рёбер
	int NumberOfEdges() const;

	// получение веса ребра
	int GetWeight(const T& vertex1, const T& vertex2);

	// получение списка из соседних вершин
	vector<T> GetNeighbors(const T& vertex);
	// получение соседних вершин, к которым есть путь
	vector<T> GetFolowers(const T& vertex);

	// методы модификации графа

	// вставка вершины
	void InsertVertex(const T& vertex);

	// вставка ребра
	void InsertEdge(const T& vertex1, const T& vertex2, int weight);

	// удаление вершины
	void DeleteVertex(const T& vertex);

	// удаление ребра
	void DeleteEdge(const T& vertex1, const T& vertex2);

	// утилиты
	//void ReadGraph(char* filename);
	//int MinimumPath(const T& sVertex, const T& sVertex);

	// обход в глубину
	vector<T> DepthFirstSearch(const T& beginVertex);

	// обход в ширину
	vector<T> BreadthFirstSearch(const T& beginVertex);

	// алгоритм Беллмана-Форда
	// возвращает вектор из кратчайших путей до каждой вершины
	vector<T> Bellman_Ford(const T& beginVertex);

	// итератор для обхода вершин
	//friend class VertexIterator<T>;

	// геттер максимального количества вершин
	int GetMaxSize() const;

	// получение списка вершин
	vector<T> GetVertexList();

	// получение матрицы смежности
	T** GetEdges();
};

// конструктор, обнуляет матрицу смежности и переменную graphsize
// выделяет память под матрицу смежности
template <typename T>
Graph<T>::Graph(int maxsize)
{
	edge = nullptr;

	// вместо cout выбрасывать исключения
	if (maxsize <= 0) {
		throw invalid_argument("Неправильное максимальное количество вершин");
		//std::cout << "Неправильная размерность массива";
	}
	maxGraphSize = maxsize;

	// выделение памяти под матрицу
	edge = new int* [maxGraphSize];

	for (int i = 0; i < maxGraphSize; i++) {
		edge[i] = new int [maxGraphSize];
	}

	// заполнение матрицы смежности нулями
	for (int i = 0; i < maxGraphSize; i++)
		for (int j = 0; j < maxGraphSize; j++)
			edge[i][j] = 0;
	// memset или memfill

	// фактическое количество вершин в графе = 0
	graphsize = 0;

}

// деструктор
template <typename T>
Graph<T>::~Graph() {
	// освободить память, выделенную под матрицу
	// если эта память была выделенна
	if (edge != nullptr) {

		for (int i = 0; i < maxGraphSize; i++) {
			delete[] edge[i];
		}

		delete[] edge;
	}

}

// метод проверки графа на отсутствие вершин, true, если граф пуст
template <typename T>
bool Graph<T>::GraphEmpty() const {
	if (graphsize == 0) {
		return true;
	}
	else return false;
}

// количество вершин
template <typename T>
int  Graph<T>::NumberOfVertices() const {
	return graphsize;
}

// количество рёбер
template <typename T>
int Graph<T>::NumberOfEdges() const {
	int res = 0;
	for (int i = 0; i < graphsize; i++) {
		for (int j = 0; j < graphsize; j++) {
			if (edge[i][j] != 0)
				res++;
		}
	}
	return res;
}

// максмальное количество вершин
template <typename T>
int Graph<T>::GetMaxSize() const {
	return maxGraphSize;
}

// получение списка вершин
template <typename T>
vector<T> Graph<T>::GetVertexList() {
	return vertexList.ListToVec();
}


// получение матрицы смежности
template <typename T>
T** Graph<T>::GetEdges() {
	return edge;
}

// получение индекса вершины в списке
// если вершины нет, то возвращает -1
template <typename T>
int Graph<T>::GetVertexPos(const T& vertex1) {

	return vertexList.searchNodeInd(vertex1);

	/*
	LinkedList<T>::LinkedListIterator<T> it1;
	bool vertex_found = false;
	int pos = 0;
	for (it1 = vertexList.begin(); it1 != vertexList.end(); ++it1) {
		if (*it1 == vertex1) {
			vertex_found = true;
			break;
		}
		else {
			pos++;
		}
		
	}
	LinkedList<T>::LinkedListIterator<T> liter = vertexList.begin();
	int pos = 0;
	while (!liter.EndOfList() && (*liter != vertex1))
	{
		pos++;
		liter.Next();
	}

	if (vertex_found) {
		return pos;
	}
	else return -1;*/
}

// получение веса ребра
template <typename T>
int Graph<T>::GetWeight(const T& vertex1, const T& vertex2) {

	int ver1 = GetVertexPos(vertex1);
	int ver2 = GetVertexPos(vertex2);

	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("Отсутствует требуемая вершина");
	}
	else
		return edge[ver1][ver2];

}

// получение соседей
template <typename T>
vector<T> Graph<T>::GetNeighbors(const T& vertex) {
	vector<T> v = {};
	int pos = GetVertexPos(vertex);

	if (pos <= -1) {
		throw invalid_argument("Отсутствует требуемая вершина");
	}
	else {
		for (int i = 0; i < graphsize; i++)
		{
			if (edge[pos][i] != 0)
				v.push_back(vertexList.dataByInd(i));
			else if (edge[i][pos] != 0)
				v.push_back(vertexList.dataByInd(i));
		}
		return v;
	}
	/*LinkedList<T>* L;
	SeqListIterator<T> viter(vertexList);
	// создать пустой список
	L = new SeqList<T>;
	// позиция в списке, соответствующая номеру строки матрицы смежности
	int pos = GetVertexPos(vertex);
	// если вершины vertex нет в списке вершин, закончить
	if (pos - << - 1)
	{
		cerr << "GetNeighbors: такой вершины нет в графе." « endl;
		return *L; // вернуть пустой список
	}
	// сканировать строку матрицы смежности и включать в список
	// все вершины, имеющие ребро ненулевого веса из vertex
	for (int i = 0; Kgraphsize; i++)
	{
		if (edge[pos][i] > 0)
			L->lnsert(viter.Data());
		viter.Next();
	}
	return *L;*/
}

template <typename T>
vector<T> Graph<T>::GetFolowers(const T& vertex) {
	vector<T> v = {};
	int pos = GetVertexPos(vertex);

	if (pos <= -1) {
		throw invalid_argument("Отсутствует требуемая вершина");
	}
	else {
		for (int i = 0; i < graphsize; i++)
		{
			if (edge[pos][i] != 0)
				v.push_back(vertexList.dataByInd(i));
			//else if (edge[i][pos] != 0)
				//v.push_back(vertexList.dataByInd(i));
		}
		return v;
	}
}

// метод вставки вершины
template <typename T>
void Graph<T>::InsertVertex(const T& vertex)
{
	// проверить, заполнен ли граф и, если да, увеличить maxGraphSize
	if (graphsize == maxGraphSize) {
		
		int newmaxGraphSize = maxGraphSize * 2;

		// создадим новую матрицу смежности с увеличенным размером
		int** temp = new int* [newmaxGraphSize];
		for (int i = 0; i < newmaxGraphSize; i++) {
			temp[i] = new int[newmaxGraphSize];
		}

		// заполнение матрицы смежности нулями
		for (int i = 0; i < newmaxGraphSize; i++)
			for (int j = 0; j < newmaxGraphSize; j++)
				temp[i][j] = 0;
		// memset или memfill

		// копирование значений из старой матрицы смежности в новую 
		for (int i = 0; i < maxGraphSize; i++)
		{
			for (int j = 0; j < maxGraphSize; j++)
			{
				temp[i][j] = edge[i][j];
			}
			// memcpy
		}

		// освобождение памяти старой матрицы смежности
		for (int i = 0; i < maxGraphSize; i++) {
			delete[] edge[i];
		}
		delete[] edge;

		// обновляем поля класса
		edge = temp;
		maxGraphSize = newmaxGraphSize;
	}

	// добавление новой вершину в список вершин
	vertexList.addNode(vertex);

	// обновление поля количества вершин графа
	graphsize++;
}

// удалить вершину из списка вершин и скорректировать матрицу
// смежности, удалив принадлежащие этой вершине ребра
template <typename T>
void Graph<T>::DeleteVertex(const T& vertex)
{
	// получить позицию вершины в списке вершин
	int pos = GetVertexPos(vertex);
	//int row, col;
	// если такой вершины нет, сообщить об этом и вернуть управление
	if (pos == -1)
	{
		throw invalid_argument("Отсутствует требуемая вершина");
	}
	
	// удалить вершину и уменьшить graphsize
	vertexList.removeNode(vertex);

	// матрица смежности делится на три области
	/*for (row = 0; row < pos; row++) { // область I
		for (col = pos + 1; col < graphsize; col++) {
			edge[row][col - 1] = edge[row][col];
		}	
	}

	for (row = pos + 1; row < graphsize; row++) {// область II
		for (col = pos + 1; col < graphsize; col++) {
			edge[row - 1][col - 1] = edge[row][col];
		}
	}

	for (row = pos + 1; row < graphsize; row++) {// область III
		for (col = 0; col < pos; col++) {
			edge[row - 1][col] = edge[row][col];
		}
	}*/
	
	int i = 0;
	// removing the vertex
	while (pos < graphsize) {
		// shifting the rows to left side
		for (i = 0; i < graphsize; ++i) {
			edge[i][pos] = edge[i][pos + 1];
		}

		// shifting the columns upwards
		for (i = 0; i < graphsize; ++i) {
			edge[pos][i] = edge[pos + 1][i];
		}
		pos++;
	}

	// decreasing the number of vertices
	graphsize = vertexList.ListSize();

}
	
// вставка ребра
template <typename T>
void Graph<T>::InsertEdge(const T& vertex1, const T& vertex2, int weight) {
	int ver1 = GetVertexPos(vertex1);
	int ver2 = GetVertexPos(vertex2);

	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("Отсутствует требуемая вершина");
	}
	else {
		edge[ver1][ver2] = weight;
	}

}

// удаление ребра
template <typename T>
void Graph<T>::DeleteEdge(const T& vertex1, const T& vertex2) {
	int ver1 = GetVertexPos(vertex1);
	int ver2 = GetVertexPos(vertex2);

	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("Отсутствует требуемая вершина");
	}
	else {
		edge[ver1][ver2] = 0;
	}
}


// Обходы графа

// обход в глубину
template <typename T>
vector<T> Graph<T>::DepthFirstSearch(const T& beginVertex) {

	if (GetVertexPos(beginVertex) == -1) {
		throw invalid_argument("Отсутствует требуемая вершина");
	}

	// стек для временного хранения вершин, ожидающих обработки
	stack<T> st;


	// L - список пройденных вершин. adjL содержит вершины,
	// смежные с текущей
	vector<T> l = {}, adjl = {};

	T vertex1;

	st.push(beginVertex);

	// продолжать обход, пока не опустеет стек
	while (!st.empty()) {
		// вытолкнуть очередную вершину
		vertex1 = st.top();
		st.pop();
		// если вершина ещё не была пройдена (не находится в списке пройденных вершин l)
		if (find(l.begin(), l.end(), vertex1) == l.end()) {
			//включить вершину в L
			l.push_back(vertex1);

			//а также получить все смежные с ней вершины
			adjl = GetFolowers(vertex1);

			// поместить все смежные вершины в стек
			for (T item : adjl) {
				st.push(item);
			}
		}
	}
	// возвратить выходной список
	return l;
}

// обход в ширину
template <typename T>
vector<T> Graph<T>::BreadthFirstSearch(const T& beginVertex) {

	if (GetVertexPos(beginVertex) == -1) {
		throw invalid_argument("Отсутствует требуемая вершина");
	}

	// очередь для временного хранения вершин, ожидающих обработки
	queue<T> qu;

	// L - список пройденных вершин. adjL содержит вершины,
	// смежные с текущей
	vector<T> l = {}, adjl = {};

	T vertex1;

	qu.push(beginVertex);

	// продолжать обход, пока не опустеет очередь
	while(!qu.empty()){
		// вытолкнуть очередную вершину
		vertex1 = qu.front();
		qu.pop();
		// если вершина ещё не была пройдена (не находится в списке пройденных вершин l)
		if (find(l.begin(), l.end(), vertex1) == l.end()) {
			//включить вершину в L
			l.push_back(vertex1);

			//а также получить все смежные с ней вершины
			adjl = GetFolowers(vertex1);

			// поместить все смежные вершины в очередь
			for (T item : adjl) {
				qu.push(item);
			}
		}
	}
	// возвратить выходной список
	return l;
}

// алгоритм Беллмана-Форда
// возвращает вектор из кратчайших путей до каждой вершины
template <typename T>
vector<T> Graph<T>::Bellman_Ford(const T& beginVertex) {
	vector<T> v = {};

	// изначально растояния неизвестны (равны бесконечности)
	for (int i = 0; i < graphsize; i++) {
		v.push_back(INT_MAX);
	}

	//расстояние до исходной вершины равно нулю
	v[beginVertex] = 0;

	// количество рёбер в графе
	int E = this->NumberOfEdges();

	for (int i = 0; i < graphsize - 1; i++) {
		for (int j = 0; j < E; j++) {
			//if ( (v[edge[j][0]] != INT_MAX) && (v[edge[j][0]] + edge[j][2] < v[edge[j][1]]) )
				//v[edge[j][1]] = v[edge[j][0]] + edge[j][2];
		}
	}
	return v;
	
}