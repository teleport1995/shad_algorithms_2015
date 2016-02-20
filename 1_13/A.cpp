#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::max;

class MaxSubPalindrome
{
private:

	string input_string;
	string answer;
	
public:
	
	void read(istream &in)
	{
		in >> input_string;
	}
	
	void solve()
	{
		int string_size = (int)input_string.length();
		
		int max_subpalindrome[string_size][string_size];
		for (int i = 0; i < string_size; ++i)
		{
			max_subpalindrome[i][i] = 1;
			if (i > 0)
				max_subpalindrome[i][i-1] = 0;
		}
		
		for (int len = 1; len < string_size; ++len)
			for (int left = 0; left + len < string_size; ++left)
			{
				int right = left + len;
				max_subpalindrome[left][right] = max(max_subpalindrome[left+1][right], max_subpalindrome[left][right-1]);
				if (input_string[left] == input_string[right])
					max_subpalindrome[left][right] = max_subpalindrome[left+1][right-1] + 2;
			}
		
		int maxlen = max_subpalindrome[0][string_size-1];
		int left = 0, right = string_size - 1;
		answer = "";
		while (left <= right)
		{
			if (left == right)
			{
				answer += input_string[left];
				break;
			}
			if (input_string[left] == input_string[right])
			{
				answer += input_string[left];
				++left, --right;
			}
			else if (max_subpalindrome[left+1][right] > max_subpalindrome[left][right-1])
				++left;
			else
				--right;
		}
		
		for (int i = maxlen / 2 - 1; i >= 0; --i)
			answer += answer[i];
	}
	
	void write(ostream &out)
	{
		out << answer << "\n";
	}
	
};

int main()
{
	MaxSubPalindrome solver;
	solver.read(cin);
	solver.solve();
	solver.write(cout);
	
	return 0;
}
