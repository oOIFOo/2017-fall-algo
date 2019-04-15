#include<iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
// change this to your id
static const char* student_id = "0416313";
//using namespace::std;

// do not edit prototype
void LCS(int *, int*, int*);

// X,Y are input strings, C is answer string
//
// data structure :  
// length of array X is m+1, length of array Y is n+1, length of array C is m+n
// X[0] = m+1, Y[0] = n+1, 
// all element of C are "-1"
// other datas are in [0,255] means the symble in ASCII or ANSI table


// you only allow declare a table with size (m+1)*(n+1)
//
// do your homework here
//

void LCS(int* X, int* Y, int* C) {
	using namespace::std;
	vector<vector <int>> ans(X[0] + 1, vector<int>(Y[0] + 1));
	for (int i = 0; i <= X[0]; i++) ans[i][0] = 0;
	for (int j = 0; j <= Y[0]; j++) ans[0][j] = 0;

	//cout << Y[0];

	for (int j = 1; j < Y[0]; j++) {
		for (int i = 1; i < X[0]; i++) {
			if (X[i] == Y[j]) {
				ans[i][j] = ans[i - 1][j - 1] + 1;
				//cout << i <<  " " <<  j << " " << ans[i][j] << endl;
			}
			else {
				if (ans[i - 1][j] > ans[i][j - 1]) ans[i][j] = ans[i - 1][j];
				else  ans[i][j] = ans[i][j - 1];

			}
		}
	}
	C[0] = ans[X[0] - 1][Y[0] - 1];
	//cout << C[0];

	int x = X[0] - 1, y = Y[0] - 1;
	//cout << y;
	while (1) {
		if (x == 0 || y == 0) break;

		if (ans[x][y] > ans[x - 1][y] && ans[x][y] > ans[x][y - 1]) {
			C[ans[x][y] - 1] = X[x];
			//cout << ans[x][y] << endl;
			x--;
			y--;
		}
		else if (ans[x][y] > ans[x - 1][y] && ans[x][y] == ans[x][y - 1]) y--;
		else if (ans[x][y] == ans[x - 1][y] && ans[x][y] > ans[x][y - 1]) x--;
		else y--;
	}
	return;
}

/*int main(void) {
using namespace::std;
int x[9] = { 8 , 1 , 2 , 3 , 1 , 2 , 3 , 2 , 1 };
int y[10] = { 9 , 3 , 2 , 1 , 2 , 3 , 1 , 2 , 3 , 3};
int ans[19] = { -1 };
LCS(x, y, ans);
for (int i = 0; i <= ans[0];i++)cout << ans[i] << " ";
system("pause");
return 0;
}*/