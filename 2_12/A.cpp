#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using std::cin;
using std::istream;
using std::ostream;
using std::cout;
using std::vector;
using std::max;
using std::map;

class Node
{
public:
	int left, right;
	vector < int > sorted;
	
	Node()
	{
	}
	
	Node(int left, int right): left(left), right(right)
	{
	}
};

class IntervalsTree
{
private:
	
	int size;
	vector < Node > data;
	
	void init(int node_index, int left, int right, vector < int > &sequence)
	{
		data[node_index] = Node(left, right);
		data[node_index].sorted.resize(right - left);
		if (right - left == 1)
		{
			data[node_index].sorted[0] = sequence[left];
			return;
		}
		
		int middle = (left + right) / 2;
		init(node_index * 2 + 0, left, middle, sequence);
		init(node_index * 2 + 1, middle, right, sequence);
		
		
		merge(begin(data[node_index * 2 + 0].sorted), end(data[node_index * 2 + 0].sorted), 
				begin(data[node_index * 2 + 1].sorted), end(data[node_index * 2 + 1].sorted), 
				begin(data[node_index].sorted));
	}
	
	
	int get_answer(int node_index, int left, int right)
	{
		if (data[node_index].left >= left && data[node_index].right <= right)
		{
			return lower_bound(data[node_index].sorted.begin(), data[node_index].sorted.end(), left)
			 - data[node_index].sorted.begin();
		}
		
		int answer = 0;
		int middle = data[node_index * 2 + 0].right;
		if (left < middle)
		{
			answer += get_answer(node_index * 2 + 0, left, right);
		}
		if (middle < right)
		{
			answer += get_answer(node_index * 2 + 1, left, right);
		}
		
		return answer;
	}
	
public:
	
	void init(vector < int > &sequence)
	{
		data.resize(sequence.size() * 4);
		init(1, 0, sequence.size(), sequence);
	}
	
	int get_answer(int left, int right)
	{
		return get_answer(1, left, right);
	}
	
};

class Query
{
public:
	int left, right;
	
	Query()
	{
	}
	
	Query(int left, int right): left(left), right(right)
	{
	}
};

class UniqueCountSolver
{
private:
	
	vector < int > data;
	
	vector < Query > queries;
	
	vector < int > answers;
	
	vector < int > get_prev_positions()
	{
		const int NO_PREV = -1;
		map < int , int > last_position;
		vector < int > prev_positions(data.size());
		for (size_t i = 0; i < data.size(); ++i)
		{
			if (last_position.find(data[i]) == last_position.end())
				prev_positions[i] = NO_PREV;
			else
				prev_positions[i] = last_position[data[i]];
			
			last_position[data[i]] = i;
		}
		return prev_positions;
	}
	
public:
	
	void read(istream &in)
	{
		int data_size, queries_size;
		in >> data_size >> queries_size;
		data.resize(data_size);
		for (int i = 0; i < data_size; ++i)
		{
			in >> data[i];
		}
		
		queries.resize(queries_size);
		for (int i = 0; i < queries_size; ++i)
		{
			int left, right;
			in >> left >> right;
			queries[i] = Query(left - 1, right);
		}
	}
	
	void solve()
	{
		vector < int > prev_positions = get_prev_positions();
		IntervalsTree tree;
		tree.init(prev_positions);
		
		answers.resize(queries.size());
		for (size_t i = 0; i < queries.size(); ++i)
		{
			answers[i] = tree.get_answer(queries[i].left, queries[i].right);
		}
	}
	
	void write(ostream &out)
	{
		for (size_t i = 0; i < answers.size(); ++i)
		{
			out << answers[i] << "\n";
		}
	}
		
};

 
int main()
{
	UniqueCountSolver solver;
	solver.read(cin);
	solver.solve();
	solver.write(cout);
	
	return 0;
}
