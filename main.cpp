#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "file.h"

using namespace std;

int main(int argc, char const *argv[])
{
	//parametri iniziali;
	double mL=8.0;
	double v0=10.0; 
	double v1=-10.0;
	double v2 =40.0;
	double v3 =80.0;
	double  A,B;
	B=0;
	A = B;
	int N =64;

	//matrice hamimltoniana ordine NxN
	vector<vector<double>> h= HAM(N,A,B,v0);
	vector<vector<double>> h1 = HAM(N,A,B,v1);

//buca potenziale
	auto vl = QR_autov(h);
	vector<double> E = vl.first;
	vector<vector<double>> psi = vl.second;

//muro potenziale
	auto vl1 = QR_autov(h1);
	vector<double> E1 = vl1.first;
	vector<vector<double>> psi1 = vl1.second;

		//double scala = 3.0;
 
		ofstream file("buca.txt");
		ofstream muro("muro.txt");

	for (int n = 0; n < 4; ++n)
	{
		vector<double> psi_n(N);
		vector<double> psi_n1(N);
		for(int i=0;i<N;i++){
			psi_n[i] = psi[i][n];
			psi_n1[i] = psi1[i][n];
		}
		//normalizzazione
		psi_n = norma_vet(psi_n);
		psi_n1 = norma_vet(psi_n1);
 
		for (int i = 0; i < N; ++i)
		{
			// formula esatta dell'esercizio: E_n*L + (mL)|psi_n(x_i)|
			// asse x: indice i (= x/a nel grafico)
			//buca
			double val = E[n] + mL * psi_n[i];
			//muro
			double valmuro = E1[n] + mL * psi_n1[i];
			file << i << " "<< E[n] << " "<< psi_n[i] << " "<< val << endl;
			muro << i << " "<< E1[n] << " "<< psi_n1[i] << " "<< valmuro << endl;
		}
		file << endl;
		muro << endl;
	}
	file.close();
	muro.close();
	return 0;


}
