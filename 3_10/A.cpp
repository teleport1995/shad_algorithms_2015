#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using std::cin;
using std::istream;
using std::ostream;
using std::cout;
using std::vector; 
using std::string;
using std::sort;
using std::max;
using std::min;

class CompareObject
{
private:
	string &input_string;
	vector < long long > &hashes, &powers;
public:
	CompareObject(string &input_string, vector < long long > &hashes, vector < long long > &powers)
		: input_string(input_string), hashes(hashes), powers(powers)
	{
	}
	
	long long substring_hash(int left_position, int right_position)
	{
		if (left_position == 0)
			return hashes[right_position];
		return hashes[right_position] - hashes[left_position - 1] * powers[right_position - left_position + 1];
	}
	
	bool operator()(const int &first, const int &second)
	{
		
		int min_common_length = 0, max_common_length = input_string.length() - max(first, second);
		
		while (min_common_length < max_common_length)
		{
			int middle = (min_common_length + max_common_length + 1) / 2;
			
			if (substring_hash(first, first + middle - 1) != substring_hash(second, second + middle - 1))
				max_common_length = middle - 1;
			else
				min_common_length = middle;
			
		}
		
		return (first + min_common_length < (int)input_string.length() ? input_string[first + min_common_length] : -1) < 
				(second + min_common_length < (int)input_string.length() ? input_string[second + min_common_length] : -1);
		
	}
};

class SuffixArray
{
private:
	
	const int p = 257;
	
	string input_string;
	vector < int > suffix_array;
	
	
	void fill_powers()
	{
		powers.resize(input_string.length());
		if (input_string.length() > 0)
		{
			powers[0] = 1;
			for (size_t i = 1; i < input_string.length(); ++i)
				powers[i] = powers[i-1] * p;
		}
	}
	
	void build_hashes()
	{
		fill_powers();
		hashes.resize(input_string.length());
		long long current_hash = 0;
		for (size_t i = 0; i < input_string.length(); ++i)
		{
			current_hash = current_hash * p + input_string[i];
			hashes[i] = current_hash;
		}
	}
	
public:
	
	void read(istream &in)
	{
		in >> input_string;
	}
	
	void solve()
	{
		build_hashes();
		suffix_array.resize(input_string.length());
		for (size_t i = 0; i < input_string.length(); ++i)
		{
			suffix_array[i] = i;
		}
		
		CompareObject compare_object(input_string, hashes, powers);
		
		
		sort(begin(suffix_array), end(suffix_array), compare_object);
		
	}
	
	void write(ostream &out)
	{
		for (int element : suffix_array)
		{
			out << element + 1 << " ";
		}
		out << "\n";
	}
		
};

 
int main()
{
	SuffixArray solver;
	solver.read(cin);
	solver.solve();
	solver.write(cout);
	
	return 0;
}
