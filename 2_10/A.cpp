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
using std::map; 

class FenwickTree
{
private:
	vector < int > data;

	int find_sum(int right)
	{
		if (right >= (int)data.size())
		{
			right = (int)data.size() - 1;
		}
		int sum = 0;
		for (; right >= 0; right = (right & (right + 1)) - 1)
		{
			sum += data[right];
		}
		return sum;
	}
	
public:
	
	FenwickTree(int size)
	{
		data.resize(size);
	}
	
	void init()
	{
		fill(begin(data), end(data), 0);
	}
	
	void add(int index, int value)
	{
		for (; index < (int)data.size(); index = (index | (index + 1)))
		{
			data[index] += value;
		}
	}
	
	int find_sum(int left, int right)
	{
		return find_sum(right) - find_sum(left - 1);
	}
};


class SuperInversions
{
private:
	
	vector < int > data;
	long long super_inversions_count;

	vector < int > squeeze_data()
	{
		vector < int > copy = data;
		sort(begin(copy), end(copy));
		
		vector < int > squeezed_data(data.size());
		for (size_t i = 0; i < data.size(); ++i)
		{
			squeezed_data[i] = lower_bound(begin(copy), end(copy), data[i]) - begin(copy);
		}
		
		return squeezed_data;
	}
	
public:
	
	void read(istream &in)
	{
		int data_size;
		in >> data_size;
		data.resize(data_size);
		for (int i = 0; i < data_size; ++i)
		{
			in >> data[i];
		}
	}
	
	void solve()
	{
		vector < int > squeezed_data = squeeze_data();
		
		FenwickTree fenwick = FenwickTree(squeezed_data.size());
		vector < int > greater_elements_count(squeezed_data.size());
		for (size_t i = 0; i < squeezed_data.size(); ++i)
		{
			greater_elements_count[i] = fenwick.find_sum(squeezed_data[i] + 1, (int)squeezed_data.size() - 1);
			fenwick.add(squeezed_data[i], 1);
		}
		
		fenwick.init();
		super_inversions_count = 0;
		for (int i = (int)squeezed_data.size() - 1; i >= 0; --i)
		{
			super_inversions_count += (long long)greater_elements_count[i] * fenwick.find_sum(0, squeezed_data[i] - 1);
			fenwick.add(squeezed_data[i], 1);
		}
	}
	
	void write(ostream &out)
	{
		out << super_inversions_count << "\n";
	}
		
};

 
int main()
{
	SuperInversions solver;
	solver.read(cin);
	solver.solve();
	solver.write(cout);
	
	return 0;
}
