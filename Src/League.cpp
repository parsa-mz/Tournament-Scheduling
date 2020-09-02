#include <iostream>

using namespace std;

/**
 @author Parsa Mazaheri
*/

int grid[1001][1001];

void solve(int l, int r){


    if((r-l) % 2 != 0){
        int len = r - l;
        for (int i = 0; i < len; i++){
            for (int j = 1; j < len; j++)
                grid[(i + j) % len + l][(i - j + len) % len + l] = i + 1;
        }
        return ;
    }

    int m = (r + l) /2;
    if((m-l) % 2 == 0){
        solve(l, m);
        solve(m, r);
        for(int i = l; i < m; i++)
            for(int j = m; j < r; j++)
                grid[i][j] = grid[j][i] = m - l + (j - i) % (m - l);
        return;
    }
    else{
        solve(l, m);
        solve(m, r);
        int off1[1001], off2[1001];
        for (int d = 1; d <= m - l; d ++){
            for (int i = l; i < m; i++)
            {
                bool flag = 0;
                for (int j = l; j < m; j++)
                    if (i != j && grid[i][j] == d)
                        flag = 1;
                if (!flag)
                    off1[d - 1] = i;
            }
            for (int i = m; i < r; i++)
            {
                bool flag = 0;
                for (int j = m; j < r; j++)
                    if (i != j && grid[i][j] == d)
                        flag = 1;
                if (!flag)
                    off2[d - 1] = i;
            }
        }
        for (int i = 0; i < m - l; i++){
            grid[off1[i]][off2[i]] = grid[off2[i]][off1[i]] = i + 1;
        }
        for (int i = 0; i < m - l; i++){
            for (int j = 1; j < m - l; j++){
                int v = off1[i];
                int u = off2[(i + j) % (m - l)];
                grid[v][u] = grid[u][v] = m - l + j;
            }
        }
        return;
    }
}

void printTable(int n)
{
    int MX = n-1;
    if(n % 2  == 1)
        MX = n;

    for(int d = 1; d <= MX; d++){
        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++)
                if(grid[i][j] == d)
                    cout << i+1 << " vs " << j+1 << "  ";
        cout << endl;
    }


}

int main(){

    int n;
    printf("Enter number of teams: \n");
    scanf("%d", &n);

    solve(0, n);

    printTable(n);
}
