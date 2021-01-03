#include <iostream>
#include <fstream>
#include "string"
#include <algorithm>
#include "string.h"
#include <queue>

using namespace std;
class CMP
{
public: 
	bool operator()(pair<long long,long long>a, pair<long long,long long> b)
	{
		return a.second > b.second;
	}
};
class edge
{
public:
	long long weight;
	long long first;
	long long second;
	
	edge(long long first, long long second, long long weight)
	{
		this->first = first;
		this->second = second;
		this->weight = weight;
	}
	edge()
	{

	}
};

int main()
{
	//using queue_type = std::priority_queue<long long, std::vector<long long>, std::greater<long long>>
	priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, CMP> priorQueue;
	long long INF = LLONG_MAX;
	long long n, m;
	ofstream fout("output.txt");
	ifstream fin("input.txt");
	fin >> n;
	fin >> m;
	if (n == 1)
	{
		fout << 0 << endl;
		return 0;
	}
	if (m == 0)
	{
		fout << 0 << endl;
		return 0;
	}
	edge* EDGES = new edge[m];
	long long* dist = new long long[n];
	for (long long i = 0; i < n; i++)
	{
		dist[i] = INF;
	}
	dist[0] = 0;
	bool* processed = new bool[n] {};
	vector < vector < pair<long long, long long> > > g(n);
	long long tmp;
	for (long long i = 0; i < m; i++)
	{
		fin >> tmp;
		EDGES[i].first = tmp - 1;
		fin >> tmp;
		EDGES[i].second = tmp - 1;
		fin >> EDGES[i].weight;
		g[EDGES[i].first].push_back(pair<long long, long long>(EDGES[i].second, EDGES[i].weight));
		g[EDGES[i].second].push_back(pair<long long, long long>(EDGES[i].first, EDGES[i].weight));
	}
	priorQueue.push(pair<long long, long long>(0, 0));
	while (!priorQueue.empty())
	{
		pair<long long,long long> tmp_pair = priorQueue.top();
		priorQueue.pop();
		if (processed[tmp_pair.first])
			continue;
		else
		{
			processed[tmp_pair.first] = true;
			dist[tmp_pair.first] = tmp_pair.second;
			for (long long i = 0; i < g[tmp_pair.first].size(); i++)
			{
				if (((tmp_pair.second + g[tmp_pair.first][i].second) < dist[g[tmp_pair.first][i].first]))
					priorQueue.push(pair<long long,long long>( g[tmp_pair.first][i].first, tmp_pair.second + g[tmp_pair.first][i].second));
			}
		}
	}
	fout << dist[n - 1] << endl;
}
