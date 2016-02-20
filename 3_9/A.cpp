#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <unordered_set>

using std::cin;
using std::istream;
using std::ostream;
using std::cout;
using std::vector; 
using std::string;
using std::sort;
using std::max;
using std::min;
using std::unordered_set;


class LongestSameSubstrings
{
private:
	
	const int p = 257;
	
	string input_string;
	int max_length;
	
	vector < long long > powers;
	vector < long long > hashes;
	
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
	
	long long substring_hash(int left_position, int right_position)
	{
		if (left_position == 0)
			return hashes[right_position];
		return hashes[right_position] - hashes[left_position - 1] * powers[right_position - left_position + 1];
	}
	
	bool find_same_substrings(int len)
	{
		unordered_set < long long > substring_hashes;
		for (int i = len - 1; i < (int)input_string.length(); i++)
		{
			long long current_hash = substring_hash(i - len + 1, i);
			if (substring_hashes.find(current_hash) != substring_hashes.end())
				return true;
			substring_hashes.insert(current_hash);
		}
		return false;
	}
	
public:
	
	void read(istream &in)
	{
		in >> input_string;
	}
	
	void solve()
	{
		build_hashes();
		
		int min_len = 0, max_len = (int)input_string.length() - 1;
		
		while (min_len < max_len)
		{
			int middle = (min_len + max_len + 1) / 2;
			
			if (find_same_substrings(middle))
			{
				min_len = middle;
			}
			else
			{
				max_len = middle - 1;
			}
		}
		
		max_length = min_len;
	}
	
	void write(ostream &out)
	{
		out << max_length << "\n";
	}
		
};

 
int main()
{
	LongestSameSubstrings solver;
	solver.read(cin);
	solver.solve();
	solver.write(cout);
	
	return 0;
}

