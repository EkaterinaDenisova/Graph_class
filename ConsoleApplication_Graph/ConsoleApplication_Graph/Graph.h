#pragma once
//author: Денисова Екатерина

#include <stdexcept> // для исключений
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <climits> 

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
	int GetWeightByInd(int ver1, int ver2);

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

	// чтение из файла
	void ReadFromFile(const string& filename);
	// запись в файл
	void WriteToFile(const string& filename);

	// алгоритм Беллмана-Форда
	// возвращает вектор из кратчайших путей до каждой вершины
	//vector<T> Bellman_Ford(const T& beginVertex);

	// алгоритм Дейкстры
	// возвращает вектор из кратчайших путей до каждой вершины из вершины beginVertex
	vector<T> dijkstra(const T& beginVertex);

	// итератор для обхода вершин
	//friend class VertexIterator<T>;

	// геттер максимального количества вершин
	int GetMaxSize() const;

	// получение списка вершин
	vector<T> GetVertexList();

	// получение матрицы смежности
	T** GetEdges();

	// очистка графа
	void ClearGraph();
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

// очистка графа
template <typename T>
void Graph<T>::ClearGraph() {
	vertexList.ClearList();

	// заполнение матрицы смежности нулями
	for (int i = 0; i < maxGraphSize; i++)
		for (int j = 0; j < maxGraphSize; j++)
			edge[i][j] = 0;

	graphsize = 0;

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

// получение веса ребра по индексам вершин
template <typename T>
int Graph<T>::GetWeightByInd(int ver1,int ver2) {

	//int ver1 = GetVertexPos(vertex1);
	//int ver2 = GetVertexPos(vertex2);

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
	if ((graphsize+1) == maxGraphSize) {
		
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


// загрузка графа из файла
// todo
template <typename T>
void Graph<T>::ReadFromFile(const string& filename) {
	ifstream fin(filename);

	if (!fin.is_open()) // если файл не был открыт
	{
		throw invalid_argument("Файл не может быть открыт"); 
	}
	else {
		this->ClearGraph(); // очищаем граф
		string line;

		int numberOfVerticies = 0;

		//numberOfVerticies = fin.readline();
		getline(fin, line);

		numberOfVerticies = stoi(line);
		
		T node;
		//
		for (int i = 0; i < numberOfVerticies; i++) {
			getline(fin, line);
			//std::istringstream - это объект класса string, 
			//который используется для преобразования строки в различные переменные,
			//и аналогично файлы могут быть преобразованы в строки.
			std::istringstream iss(line);
			if (!(iss >> node)) {
				// В случае ошибки чтения строки
				throw invalid_argument("Ошибка чтения файла");
			}
			this->InsertVertex(node);
		}

		T vertex_1, vertex_2;
		int weight_1;
		
		// Чтение файла построчно
		while (std::getline(fin, line))
		{
			std::istringstream iss(line);
			
			// Извлекаем из строки две вершины и вес ребра
			if (!(iss >> vertex_1 >> vertex_2 >> weight_1))
			{
				// В случае ошибки чтения строки
				throw invalid_argument("Ошибка чтения файла");
			}

			// Добавляем ребро в граф
			InsertEdge(vertex_1, vertex_2, weight_1);
		}

		// Закрываем файл после чтения
		fin.close();

		// обновляем поле класса
		graphsize = numberOfVerticies;
	}
}

// запись графа в файл
template <typename T>
void Graph<T>::WriteToFile(const string& filename) {
	ofstream fout(filename);

	if (!fout.is_open()) // если файл не был открыт
	{
		throw invalid_argument("Файл не может быть открыт");
	}
	else {
		int number = this->NumberOfVertices();
		fout << number << endl;

		vector<T> vec = this->vertexList.ListToVec();
		for (int i = 0; i < number; i++) {
			fout << vec[i] << endl;
		}

		int numberEdge = 0;// количество ребер
		/// проход по матрице смежности
		for (int i = 0; i < NumberOfVertices(); i++)
		{
			for (int j = 0; j < NumberOfVertices(); j++)
			{
				if (edge[i][j] != 0) {
					// выводим 2 вершины и ребро
					fout << vertexList.dataByInd(i) << " " << vertexList.dataByInd(j) << " " << edge[i][j] << "\n";
					numberEdge++;
				}
			}
		}

		/*fout.close();
		this->vertexList.printListToFile(filename);

		fout.open(filename, 'a+');*/


		fout.close();
		
	}
}


// алгоритм Дейкстры
// возвращает вектор из кратчайших путей до каждой вершины из вершины beginVertex
template <typename T>
vector<T> Graph<T>::dijkstra(const T& beginVertex) {
	int pos = GetVertexPos(beginVertex);
	if (pos == -1) {
		throw invalid_argument("Отсутствует требуемая вершина");
	}

	vector<int> d; // вектор кратчайших растояний
	vector<bool> used; // вектор посещений

	// изначально расстояния до вершин неизвестны (INT_MAX)
	// все вершины не посещены (false)
	for (int i = 0; i < NumberOfVertices(); i++) {
		d.push_back(INT_MAX);
		used.push_back(false);
	}

	d[pos] = 0; // расстояние из вершины до самой себя равно 0

	// повторяем для всех вершин графа
	for (int k = 0; k < NumberOfVertices(); k++) {
		// для каждой вершины смотрим расстояние до всех других вершин по матрице смежности
		for (int i = 0; i < NumberOfVertices(); i++) {
			int w = GetWeightByInd(pos, i);

			if (w < 0) {
				throw invalid_argument("Алгоритм Дейкстры не поддерживает отрицательные веса");
			}

			// если путь до вершины есть, если вершина ещё не была посещена и
			// если надено меньшее расстояние до данной вершины
			if ((w != 0) && (used[i] == false) && ((d[pos] + w) < d[i])) {
				d[i] = d[pos] + w; // записываем новое значение кратчайшего пути
			}
		}
		// вершина пройдена, когда по матрице смежности были проверены все вершины относительно данной
		used[pos] = true;

		// находим индекс с минимальным значением расстояния на данный момент
		// (из непросмотренных вершин)
		int min1 = INT_MAX;
		for (int j = 0; j < NumberOfVertices(); j++) {
			if ((d[j] < min1) && (used[j] == false)) {
				pos = j; // запоминаем индекс данной вершины
				// от неё продолжится поиск кратчайших путей до остальных вершин
			}
		}

	}
	return d;

	/*for (int k = 0; k < NumberOfVertices(); k++)
	{
		// находим индекс вершины с кратчайшим расстояние
		int min1 = INT_MAX;
		int index;
		for (int v = 0; v < NumberOfVertices() - 1; v++) {
			if (used[v] == false && d[v] <= min1) {
				min1 = d[v];
				index = v;
			}
		}

		used[index] = true;

		for (int v = 0; v < NumberOfVertices(); v++) {
			if (!used[v] && edge[index][v] != 0 && d[index] != INT_MAX && d[index] + edge[index][v] < d[v])
				d[v] = d[index] + edge[index][v];

		}

	}

	return d;*/



	/*priority_queue< pair<int, int> >, vector< pair<int, int> >, greater< pair<int, int> > > pq;

	// Create a vector for distances and initialize all
	// distances as infinite (INF)
	//vector<int> dist(V, INF);
	vector <int> d; // вектор кратчайших растояний

	for (int i = 0; i < NumberOfVertices(); i++) {
		d.push_back(INT_MAX);
	}

	// Insert source itself in priority queue and initialize
	// its distance as 0.
	pq.push(make_pair(0, pos));
	dist[pos] = 0;

	//Looping till priority queue becomes empty (or all
	//distances are not finalized) 
	while (!pq.empty()) {
		// The first vertex in pair is the minimum distance
		// vertex, extract it from priority queue.
		// vertex label is stored in second of pair (it
		// has to be done this way to keep the vertices
		// sorted distance (distance must be first item
		// in pair)
		int u = pq.top().second;
		pq.pop();

		// 'i' is used to get all adjacent vertices of a
		// vertex
		list<pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i) {
			// Get vertex label and weight of current
			// adjacent of u.
			int v = (*i).first;
			int weight = (*i).second;

			// If there is shorted path to v through u.
			if (dist[v] > dist[u] + weight) {
				// Updating distance of v
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	// Print shortest distances stored in dist[]
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < V; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
	*/
	
	/*vector <int> d; // вектор кратчайших растояний
	vector<bool> used; // вектор посещений

	for (int i = 0; i < NumberOfVertices(); i++) {
		d.push_back(INT_MAX);
		used.push_back(false);
	}

	d[pos] = 0; // расстояние из вершины до самой себя равно 0

	for (int k = 0; k < NumberOfVertices(); k++)
	{
		// находим кратчайшее расстояние
		int min1 = INT_MAX;
		int index;
		for (int v = 0; v < NumberOfVertices(); v++) {
			if (used[v] == false && d[v] <= min1) {
				min1 = d[v];
				index = v;
			}
		}

		used[index] = true;

		for (int v = 0; v < NumberOfVertices(); v++) {
			if (!used[v] && edge[index][v] && d[index] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
		}



		int m = miniDist(distance, Tset);
		Tset[m] = true;
		for (int k = 0; k < 6; k++)
		{
			// updating the distance of neighbouring vertex
			if (!Tset[k] && graph[m][k] && distance[m] != INT_MAX && distance[m] + graph[m][k] < distance[k])
				distance[k] = distance[m] + graph[m][k];
		}
	}
	*/


}

// алгоритм Беллмана-Форда
// возвращает вектор из кратчайших путей до каждой вершины
/*template <typename T>
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
	
}*/