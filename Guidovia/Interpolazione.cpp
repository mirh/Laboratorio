#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>
using namespace std;

bool controllo(string x);
struct dato {
	float valore;
	float errore;
};

int main (int argc, char *argv[]) {
	ifstream leggi(argv[1]);
	ofstream scrivi("output.txt");
	
	if(!leggi.is_open()) {
		cout << "Impossibile aprire il file" << endl;
		return -1;
	}
	
	vector<float> tempo;
	vector<dato> veloc;
	int i=0;

	string temp;
	getline(leggi, temp); // scarto la prima riga

	while(getline(leggi, temp)) {
		if (controllo(temp)) break;
		i++;
		istringstream iss(temp);
    	float a;
    	iss >> a;
		tempo.push_back(a);
	}
	
	while(i>0) {
		getline(leggi, temp); //scarto la seconda "riga titolo"
		if (controllo(temp)) break;
		istringstream iss(temp);
		float a, c;
		iss >> a >> c >> c;
		veloc.push_back(dato{a, c});
		i--;
	}
	
	if(leggi.bad()) {
		cout << "Impossibile leggere il file" << endl;
		return -1;
	}
	
	//Interpolo
	float x1, y1, x2, xy, e=0;
	for (int k = 0; k < tempo.size(); k++){
		x1=x1+tempo[k]*tempo[k];
		y1=y1+veloc[k].valore;
		x2=x2+tempo[k];
		xy=xy+tempo[k]*veloc[k].valore;
	}
	float delta=tempo.size()*x1-x2*x2;
	float a=(x1*y1-x2*xy)/delta;
	float b=(xy*tempo.size()-x2*y1)/delta;
	
	for (int k = 0; k < tempo.size(); k++){
		e=((a+b*tempo[k])-veloc[k].valore);
		e=e*e;
	}
	e=sqrt(e/(tempo.size()-2));
	float eA=e*sqrt(x1/delta);
	float eB=e*sqrt(tempo.size()/delta);
	
	scrivi << "Tempo (s)\tVelocità (m/s)\t Errore velocità (m/s)" << endl;	//da controllare
	for (int k = 0; k < tempo.size(); k++){
		scrivi << tempo[k] << "\t" << veloc[k].valore << "\t" << veloc[k].errore << endl;
		}
	scrivi << "a è " << a << ", b è " << b << endl;
	scrivi << "Dev y è " << e << endl;
	scrivi << "Dev.std di a è " << eA << " e dev.std di b è " << eB;
	return 0;
}

bool controllo(string x){	
	for(auto w:x) {						
		if(isalpha(w) || (isspace(w) && !isblank(w))) return 1;   //da migliorare
		else return 0;
	}
}

//http://stackoverflow.com/questions/7868936/read-file-line-by-line
//http://en.cppreference.com/w/cpp/string/byte/isdigit http://www.cprogramming.com/tutorial/lesson2.html
