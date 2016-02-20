#include <iostream>
#include <cstdio>
#include <vector>

using std::cin;
using std::istream;
using std::ostream;
using std::cout;
using std::vector; 

class LongestAlternateSequence
{
private:
	
	vector < int > sequence;
	vector < int > answer_sequence;

public:
	
	void read(istream &in)
	{
		int sequence_size;
		in >> sequence_size;
		sequence.resize(sequence_size);
		for (int i = 0; i < (int)sequence.size(); ++i)
			cin >> sequence[i];
	}
	
	void solve()
	{
		const int NULL_INDEX = -1, NO_NEXT_INDEX = -1;
		int max_index = NULL_INDEX;
		vector < int > ans_down(sequence.size()), ans_up(sequence.size()),
				next_down(sequence.size()), next_up(sequence.size());
		for (int index = (int)sequence.size() - 1; index >= 0; --index)
		{
			ans_down[index] = 1;
			next_down[index] = NO_NEXT_INDEX;
			for (int next_index = index + 1; next_index < (int)sequence.size(); ++next_index)
				if (sequence[next_index] > sequence[index] && ans_up[next_index] + 1 > ans_down[index])
				{
					ans_down[index] = ans_up[next_index] + 1;
					next_down[index] = next_index;
				}
				
			ans_up[index] = 1;
			next_up[index] = NO_NEXT_INDEX;
			for (int next_index = index + 1; next_index < (int)sequence.size(); ++next_index)
				if (sequence[next_index] < sequence[index] && ans_down[next_index] + 1 > ans_up[index])
				{
					ans_up[index] = ans_down[next_index] + 1;
					next_up[index] = next_index;
				}
				
			if (max_index == NULL_INDEX || ans_down[index] >= ans_down[max_index])
			{
				max_index = index;
			}
		}
		bool isDown = true;
		while (max_index != NO_NEXT_INDEX)
		{
			answer_sequence.push_back(max_index + 1);
			if (isDown)
				max_index = next_down[max_index];
			else
				max_index = next_up[max_index];
			isDown ^= 1;
		}
	}
	
	void write(ostream &out)
	{
		out << answer_sequence.size() << "\n";
		for (int i = 0; i < (int)answer_sequence.size(); ++i)
			out << answer_sequence[i] << " ";
		out << "\n";
	}
		
};

 
int main()
{
	LongestAlternateSequence solver;
	solver.read(cin);
	solver.solve();
	solver.write(cout);
	
	return 0;
}
