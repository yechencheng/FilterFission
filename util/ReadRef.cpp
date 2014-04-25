#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>

using namespace std;

string getval(string x){
				cout << x << endl;
				int pos=0;
				while(!isdigit(x[pos]))
								pos++;
				while(x[pos] != ' ')
								pos++;
				return x.substr(0, pos);
}

int main(int argc, char **argv){

				int cnt = 0;
				string r[3];
				string m[3];
				char tmp[1024];
				for(int i = 1; i < argc; i++){
								ifstream fin(argv[i]);
								string x;

								for(int i = 0; i < 3; i++)
												fin.getline(tmp, 1024);
								fin >> r[cnt];
								fin.getline(tmp,1024);
								fin >> m[cnt];
								fin.close();
								cnt++;

								if(cnt == 3){
												cnt = 0;
												for(int i = 0; i < 3; i++)
																cout << r[i] << "\t";
												for(int i = 0; i < 3; i++)
																cout << m[i] << "\t";
												cout << endl;
								}
				}
}
