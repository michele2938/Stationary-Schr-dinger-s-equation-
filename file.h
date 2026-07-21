#ifndef FILE_H
#define FILE_H

#include<iostream>
#include <cmath>
#include<complex>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// prodotto scalare
double sclr(const vector<double>& a, const vector<double>& b) {
    double x = 0.0;
    int N=a.size();
    for (int i = 0; i < N; i++)
        x += a[i] * b[i];
    return x;
}

//norma euclidea
double nrm(const std::vector<double>& x) {
    return sqrt(sclr(x, x));
}

template <typename T>
vector<vector<T>> HAM(int N, T A, T B, T v0) 
{
    T mL = 8.0;
    vector<vector<T>> H(N, vector<T>(N, 0.0));

    vector<T> V(N, 0.0);
    for (int i = 0; i < N; i++) 
    {
        T x = (double)i/N; 
        // BUCA POTENZIALE [L/4,3/4 L]
        if (x >= 0.25 && x < 0.75) 
        {
            V[i] = -v0;
        } 
        else {
            V[i] = 0.0;
        }
    }

    T t =(-N*N)/(2.0*mL); 
    for (int i = 0; i < N; i++) 
    {
        H[i][i] = -2.0 * t + V[i]; 
        if (i > 0) 
        	H[i][i-1] = t;  
        if (i < N-1) 
        	H[i][i+1] = t; 
    }

    H[0][0] = -2.0 * t + V[0];
    H[N-1][N-1] = -2.0 * t + V[N-1];

    return H;
}

  vector<vector<double>> prod_matrc(vector<vector<double>> A, vector<vector<double>> B) {
    int a = A.size();
    int b = B.size();
    int bz = B[0].size();

    vector<vector<double>>C(a,vector<double>(bz, 0.0));

    for (int i = 0; i < a; i++)
        for (int j = 0; j < bz; j++)
            for (int k = 0; k < b; k++)
                C[i][j] += A[i][k] * B[k][j];
    //cout<< b;
    return C;
}


//householder
vector<vector<double>> householder(const vector<vector<double>>& A, int k)
{
    int N = A.size();

    vector<double> x(N, 0.0);
    for (int i = k; i < N; i++)
        x[i] = A[i][k];

    double normx = nrm(x);
    if (normx == 0.0) return vector<vector<double>>(N, vector<double>(N, 0.0));

    int sgn = (x[k] >= 0) ? 1 : -1;

    vector<double> v = x;
    v[k] += sgn * normx;

    double vtv = sclr(v, v);

    // matrice identità
    vector<vector<double>> H(N, vector<double>(N, 0.0));
    for (int i = 0; i < N; i++)
        H[i][i] = 1.0;

    // H = I - 2 vv^T / (v^T v)
    for (int i = k; i < N; i++)
        for (int j = k; j < N; j++)
            H[i][j] -= 2.0 * v[i] * v[j] / vtv;

    return H;
}
//QR
vector<vector<vector<double>>> QR(vector<vector<double>> A)
{
    int N = A.size();
    vector<vector<double>> Q(N, vector<double>(N, 0.0));
    vector<vector<double>> R = A;

    // Q = identita
    for (int i = 0; i < N; i++)
        Q[i][i] = 1.0;

    for (int k = 0; k < N - 1; k++)
    {
        vector<vector<double>> H = householder(R, k);
        R = prod_matrc(H, R);
        Q = prod_matrc(Q, H);
    }

    return {Q, R};
}
//
vector<double> norma_vet(vector<double> v)
{
    double norm = 0.0;
    for(double x : v) norm += x*x;
    norm = sqrt(norm);

    for(double &x : v) x /= norm;
    return v;
}



/*
leggermente modificata rispetto a quella usata nell'esercizio 5
ritorno ora una matrice le cui colonne sono autovettori ed un vettore

*/
pair<vector<double>, vector<vector<double>>> QR_autov(vector<vector<double>> A,int Niter=100)
{
    int n = A.size();
    vector<vector<double>> Ak = A;

    vector<vector<double>> I (n,vector<double>(n,0.0));
    for(int j =0;j<n;j++)
        I[j][j]=1.0;

    vector<vector<double>>Qk = I;

    for (int i =0;i<Niter;i++)
    {
        auto val = QR(Ak);
        vector<vector<double>> Q = val[0];
        vector<vector<double>> R = val[1];

        Ak = prod_matrc(R,Q);
        Qk = prod_matrc(Qk,Q);
    }

    vector<double> AK (n, 0.0);
    for(int i=0;i<n;i++)
        AK[i] = Ak[i][i];

    //Ak vettore di autovalori, Qk matrice di autovettori
    // RIORDINO AUTOFUNZIONI E AUTOVETTORI
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b){ return AK[a] < AK[b]; });
 
    vector<double> AK_sorted(n);
    vector<vector<double>> Qk_sorted(n, vector<double>(n, 0.0));
    for(int i = 0; i < n; i++){
        AK_sorted[i] = AK[idx[i]];
        for(int j = 0; j < n; j++)
            Qk_sorted[j][i] = Qk[j][idx[i]];
    }
 
    //Ak vettore di autovalori, Qk matrice di autovettori
    return {AK_sorted, Qk_sorted};
}

#endif
