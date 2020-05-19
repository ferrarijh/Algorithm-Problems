#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

/* M x M key and N x N lock is given. Is the lock unlockable with the given key?
M <= N, both key and lock has protrusion(1) or a slot(0) at key[i,j].
It is a 'perfect match' if all lock slots are matched by key's protrusions and all lock protrusions are matched by slots in key.
Key can be rotated by 90 degrees.
Key may stick out of the lock, which means outside area of the lock doesn't matter for the perfect match.
Show whether the perfect match is possible or not.
https://programmers.co.kr/learn/courses/30/lessons/60059

=========OUTPUT==========
True(possible) or False(impossible).
*/

/*
KEY : indexing & defining perfect fit
*/

void Print(vector<vector<int>>& vec) {
	int n = (int)vec.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << vec[i][j] << " ";
		cout << "\n";
	}
}

vector<vector<int>> rotate(vector<vector<int>> key) {
	int m = key.size();
	vector<vector<int>> res(m, vector<int>(m));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			res[j][m - 1 - i] = key[i][j];
	return res;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	int m = (int)key.size();
	int n = (int)lock.size();

	int holes = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (!lock[i][j])
				holes++;
	
	int fit = 0;
	bool flag = 0;
	for (int i = 0; i <= n+m-2; i++)
		for (int j = 0; j <= n+m-2; j++)
			for (int k = 0; k < 4; k++) {
				for (int x = 0; x < m; x++) {			//key 움직이니 무조건 key는 >= 0, <m 범위여야.
					for (int y = 0; y < m; y++) {
						if (i - m + 1 + x < 0 || i - m + 1 + x >= n		// i-m+1+x, i-m+1+y
							|| j - m + 1 + y < 0 || j - m + 1 + y >= n)
							continue;
						if (!(key[x][y] ^ lock[i-m+1+x][j-m+1+y])) {
							flag = 1;
							break;
						}
						else if (key[x][y])
							fit++;
					}
					if (flag) {
						flag = 0;
						break;
					}
				}
				if (fit == holes)
					return 1;
				fit = 0;
				key = rotate(key);
			}
	return 0;
}

int main() {

	int n, m;
	cin >> m >> n;
	vector<vector<int>> key(m, vector<int>(m));
	vector<vector<int>> lock(n, vector<int>(n));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			cin >> key[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> lock[i][j];


	cout << solution(key, lock);
	return 0;
}

/*
=====test input=====
3 3
0 0 0 
1 0 0
0 1 1 
1 1 1 
1 1 0
1 0 1
>>answer:True. (i=3, j=3, k=1)
*/