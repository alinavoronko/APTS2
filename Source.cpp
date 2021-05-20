#include<fstream>
#include <iostream>

using namespace std;
struct dalibnieks {
	int id;
	int siev;
	int vir;
	dalibnieks* next;
	dalibnieks(int _id, int _siev, int _vir, dalibnieks* _next=NULL) {
		id = _id;
		siev = _siev;
		vir = _vir;
		next = _next;

	}
};

class saraksts {
	dalibnieks* pirmais;
	dalibnieks* pedejais;
public:
	saraksts() {
		pirmais = pedejais=NULL;


	}
	dalibnieks* getPirmais() {

		return pirmais;
	}
	void add_dalib(dalibnieks* dal) {

		if (!pirmais) {
			pirmais = pedejais = dal;
		}
		else {
			pedejais->next = dal;
			pedejais = pedejais->next;
		}
	};
	void print() {
		dalibnieks* nor = this->pirmais;
		while (nor != this->pedejais) {
			cout << "dalibnieks: " << nor->id << " " << nor->siev << " " << nor->vir << endl;
			nor = nor->next;
		}
	};
	dalibnieks* atrast(int _id) {

		dalibnieks* nor = this->pirmais;
		while (nor->id != _id) {
			nor = nor->next;
		}
		return nor;
	}

};

struct mezgls {
	int id;
	mezgls* siev;
	mezgls* vir;


};
mezgls* izveidot(saraksts sar, int _id) {
	dalibnieks* d = sar.atrast(_id);
	mezgls* m = new mezgls();
	m->id = _id;
	if (d->siev && d->siev!=0) {
		m->siev = izveidot(sar, d->siev);
	}
	if (d->vir&&d->vir!=0) {
		m->vir = izveidot(sar, d->vir);
	}
	return m;
}



void izvaditLimeni( mezgls* sakne, int k, ofstream& f2 )
{
	if (sakne == NULL)
		return;
	if (k == 0)
	{
		f2 << sakne->id<<" ";
		/*cout << sakne->id << " ";*/
		return;
	}
	else
	{
		izvaditLimeni(sakne->siev, k - 1, f2);
		izvaditLimeni(sakne->vir, k - 1, f2);
	}
}


int kokaDzilums(mezgls* sakne)
{
	if (sakne == NULL)
		return 0;
	else
	{
		
		int lDepth = kokaDzilums(sakne->siev);
		int rDepth = kokaDzilums(sakne->vir);

		
		if (lDepth > rDepth)
			return(lDepth+1);
		else return(rDepth+1);
	}
}



int main() {
	int dal;
	int siev;
	int vir;
	saraksts Dalibnieki;
	ifstream f("team.in");
	while (!f.eof()) {
		f >> dal;
		f >> siev;
		f >> vir;
		if (dal != 0) {
			dalibnieks* jauns = new dalibnieks(dal, siev, vir);
			Dalibnieki.add_dalib(jauns);
		}
	}
	Dalibnieki.print();

	mezgls*m = izveidot(Dalibnieki, Dalibnieki.getPirmais()->id);
	f.close();
	//izvaditLimeni(m, 2);
	ofstream f2("team.out");
	int n = kokaDzilums(m)-1;
	for (int i = n;i >= 0; i--) {
		f2 << i << ": ";
		izvaditLimeni(m, i, f2);
		f2 << "\n";
	 }

}

