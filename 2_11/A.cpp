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

class Node
{
public:
	int left, right;
	int ones_count;
	bool starts_with_one, ends_with_one;
	int value_to_push;
	bool need_to_push;
	
	Node()
	{
	}
	
	Node(int left, int right, int ones_count = 0, bool starts_with_one = false, 
		bool ends_with_one = false, int value_to_push = 0, bool need_to_push = false) 
		: left(left), right(right), ones_count(ones_count), starts_with_one(starts_with_one), 
		ends_with_one(ends_with_one), value_to_push(value_to_push), need_to_push(need_to_push)
	{
	}
};

class IntervalsTree
{
private:
	
	int size;
	vector < Node > data;
	
	Node combine(Node left_node, Node right_node)
	{
		Node node = Node(left_node.left, right_node.right);
		node.ones_count = left_node.ones_count + right_node.ones_count;
		if (left_node.ends_with_one && right_node.starts_with_one)
			--node.ones_count;
		
		node.starts_with_one = left_node.starts_with_one;
		node.ends_with_one = right_node.ends_with_one;
		
		
		return node;
	}
	
	void mark(int node_index, int value)
	{
		data[node_index].value_to_push = value;
		data[node_index].need_to_push = true;
		if (value == 1)
		{
			data[node_index].ones_count = 1;
			data[node_index].starts_with_one = data[node_index].ends_with_one = true;
		}
		else
		{
			data[node_index].ones_count = 0;
			data[node_index].starts_with_one = data[node_index].ends_with_one = false;
		}
	}
	
	void push(int node_index)
	{
		if (data[node_index].right - data[node_index].left == 1)
			return;
		if (data[node_index].need_to_push)
		{
			mark(node_index * 2 + 0, data[node_index].value_to_push);
			mark(node_index * 2 + 1, data[node_index].value_to_push);
			data[node_index].need_to_push = false;
		}
	}
	
	void init(int node_index, int left, int right)
	{
		if (right - left == 1)
		{
			data[node_index] = Node(left, right);
			return;
		}
		
		int middle = (left + right) / 2;
		init(node_index * 2 + 0, left, middle);
		init(node_index * 2 + 1, middle, right);
		
		data[node_index] = combine(data[node_index * 2 + 0], data[node_index * 2 + 1]);
	}
	
	void update(int node_index, int left, int right, int value)
	{
		if (data[node_index].left >= left && data[node_index].right <= right)
		{
			mark(node_index, value);
			return;
		}
		
		push(node_index);
		
		int middle = data[node_index * 2 + 0].right;
		if (middle > left)
		{
			update(node_index * 2 + 0, left, right, value);
		}
		if (middle < right)
		{
			update(node_index * 2 + 1, left, right, value);
		}
		
		data[node_index] = combine(data[node_index * 2 + 0], data[node_index * 2 + 1]);
	}
	
	Node get_answer(int node_index, int left, int right)
	{
		if (data[node_index].left >= left && data[node_index].right <= right)
		{
			return data[node_index];
		}
		
		push(node_index);
		
		int middle = data[node_index * 2 + 0].right;
		if (left < middle && middle < right)
		{
			return combine(get_answer(node_index * 2 + 0, left, right), 
							get_answer(node_index * 2 + 1, left, right));
		}
		else if (left < middle)
		{
			return get_answer(node_index * 2 + 0, left, right);
		}
		else
		{
			return get_answer(node_index * 2 + 1, left, right);
		}
	}
	
public:
	
	IntervalsTree(int size)
	{
		this->size = size;
		data.resize(size * 4);
	}
	
	void init()
	{
		init(1, 0, size);
	}
	
	void update(int left, int right, int value)
	{
		update(1, left, right, value);
	}
	
	int get_answer(int left, int right)
	{
		return get_answer(1, left, right).ones_count;
	}
	
};

class Query
{
public:
	int type, left, right;
	
	Query()
	{
	}
	
	Query(int type, int left, int right): type(type), left(left), right(right)
	{
	}
};

class ZerosOnesIntervalsSolver
{
private:
	
	int data_size;
	vector < Query > queries;
	
	vector < int > answers;
	
public:
	
	void read(istream &in)
	{
		in >> data_size;
		int queries_size;
		in >> queries_size;
		queries.resize(queries_size);
		for (int i = 0; i < queries_size; ++i)
		{
			int type, left, right;
			in >> type >> left >> right;
			queries[i] = Query(type, left - 1, right);
		}
	}
	
	void solve()
	{
		IntervalsTree tree = IntervalsTree(data_size);
		tree.init();
		
		for (size_t i = 0; i < queries.size(); ++i)
		{
			if (queries[i].type < 2)
				tree.update(queries[i].left, queries[i].right, queries[i].type);
			else
				answers.push_back(tree.get_answer(queries[i].left, queries[i].right));
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
	ZerosOnesIntervalsSolver solver;
	solver.read(cin);
	solver.solve();
	solver.write(cout);
	
	return 0;
}

