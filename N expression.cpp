#include <vector>
#include <iostream>
#define MAX 1000000000
using namespace std;

/* try expressing 'number' with minimum number of Ns and basic operators, including paranthesis.
ex) If N = 2, number = 11, then 11 can be expressed as 22/2 and the answer is 3,
since three 2s are used here and that's the minimum.
ex) if N = 5, number = 12, then 12 = (55+5)/5, so the answer is 4.
==========INPUT==========
N, number

==========OUTPUT==========
the minimum number.

https://programmers.co.kr/learn/courses/30/lessons/42895
*/

vector<int> Ns(8);
int pos_min = MAX;

void dfs(int pos, int prev, int number) {
	if (pos > 8)
		return;
	if (prev == number && pos_min > pos) {
		pos_min = pos;
		return;
	}
	for (int i = 0; i < 8; i++) {
		dfs(pos + i+1, prev + Ns[i], number);
		dfs(pos + i+1, prev - Ns[i], number);
		dfs(pos + i+1, prev * Ns[i], number);
		dfs(pos + i+1, prev / Ns[i], number);
	}
}

int Pow(int a, int b) {
	int res = 1;
	for (int i = 0; i < b; i++)
		res *= a;
	return res;
}

int solution(int N, int number) {
	for (int i = 0; i < 8; i++) {
		int tmp = 0;
		for (int j = 0; j <= i; j++)
			tmp += N * Pow(10, j);
		Ns[i] = tmp;
	}
	dfs(0, 0, number);
	if (pos_min == MAX)
		return -1;
	return pos_min;
}

int main() {
	for (int i = 1; i <= 12; i++) {
		cout << solution(5, i) << '\n';
		pos_min = MAX;
	}
	return 0;
}