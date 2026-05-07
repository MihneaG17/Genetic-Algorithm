#include <bits/stdc++.h>

using namespace std;

struct Cromozom {
    string binar;
    double x;
    double fitness;
};

int n,p,etape,l;
double a,b, coefA, coefB, coefC,pc,pm;

double random_01() {
    return (double)rand()/RAND_MAX;
}

double decodificare(string binar) {
    long long v=0;
    long long putere_doi=1;
    for(int i=l-1;i>=0;i--) {
        int bit_curent=binar[i]-'0';
        v=v+bit_curent*putere_doi;
        putere_doi*=2;
    }
    return a+v*((b-a)/((1LL<<l)-1));
}

double calcul_fitness(double x) {
    return coefA*x*x+coefB*x+coefC;
}

void evalueaza_individ(Cromozom& c) {
    c.x=decodificare(c.binar);
    c.fitness=calcul_fitness(c.x);
}

void generare_populatie_initiala(vector<Cromozom>& populatie, ofstream& fout) {
    for(int i=0;i<n;i++) {
        populatie[i].binar="";
        for(int j=0;j<l;j++) {
            if(rand()%2==0) {
                populatie[i].binar+='0';
            }
            else {
                populatie[i].binar+='1';
            }
        }
        evalueaza_individ(populatie[i]);
    }
    fout<<"Populatia initiala:\n";
    for(int i=0;i<n;i++) {
        fout<<i+1<<": "<<populatie[i].binar<<" x= " << populatie[i].x
        <<" f= "<<populatie[i].fitness<<"\n";
    }
}

Cromozom extrage_elita(vector<Cromozom>& populatie) {
    int indice_elita=0;
    for(int i=1;i<n;i++) {
        if(populatie[i].fitness>populatie[indice_elita].fitness)
        {
            indice_elita=i;
        }
    }
    return populatie[indice_elita];
}

void inserare_elita(vector<Cromozom>& populatie_urmatoare, Cromozom elita) {
    int indice_slab=0;
    for(int i=1;i<n;i++) {
        if(populatie_urmatoare[i].fitness<populatie_urmatoare[indice_slab].fitness) {
            indice_slab=i;
        }
    }
    populatie_urmatoare[indice_slab]=elita;
}

void selectia_ruletei(vector<Cromozom>& populatie, vector<Cromozom>& populatie_urmatoare, bool detalii, ofstream& fout) {
    double fitness_total=0;
    for(int i=0;i<n;i++) {
        fitness_total+=populatie[i].fitness;
    }

    vector<double> prob(n), q(n+1);
    q[0]=0;

    if(detalii)
    {
        fout<<"\nProbabilitati selectie:\n";
    }
    for(int i=0;i<n;i++) {
        prob[i]=populatie[i].fitness/fitness_total;
        q[i+1]=q[i]+prob[i];
        if(detalii) {
            fout<<"cromozom "<<i+1<<" probabilitate "<<prob[i]<<"\n";
        }
    }

    if(detalii) {
        fout<<"\nIntervale probabilitati selectie:\n";
        for(int i=0;i<=n;i++) {
            fout<<q[i]<<" ";
        }
        fout<<"\n\n";
    }

    for(int i=0;i<n;i++) {
        double u=random_01();
        int sel=0;

        int st=0;
        int dr=n-1;

        while(st<=dr) {
            int mijl=st+(dr-st)/2;

            if(u>=q[mijl] && u<q[mijl+1]) {
                sel=mijl;
                break;
            }
            else if(u>=q[mijl+1]) {
                st=mijl+1;
            }
            else {
                dr=mijl-1;
            }
        }
        if (detalii) {
            fout<<"u="<<u<<" selectam cromozomul "<<sel+1<<"\n";
        }
        populatie_urmatoare[i]=populatie[sel];
    }

    if(detalii) {
        fout<<"Dupa selectie:\n";
        for(int i=0;i<n;i++) {
            fout<<i+1<<": "<<populatie_urmatoare[i].binar<<" x= "<<populatie_urmatoare[i].x
            <<" f= "<<populatie_urmatoare[i].fitness<<"\n";
        }
    }
}


void incrucisare(vector<Cromozom>& populatie_urmatoare, bool detalii, ofstream& fout) {
    vector<int> participanti;

    if(detalii) {
        fout<<"\nProbabilitatea de incrucisare "<<pc<<"\n";
    }

    for(int i=0;i<n;i++) {
        double u=random_01();
        if(detalii) {
            fout<<i+1<<": "<<populatie_urmatoare[i].binar<<" u="<<u;
        }

        if(u<pc) {
            participanti.push_back(i);
            if(detalii) {
                fout<<" <"<<pc<<" participa";
            }
        }
        if(detalii) {
            fout<<"\n";
        }
    }
    if(detalii) {
        fout<<"\n";
    }

    for(int i=0;i+1<participanti.size();i+=2) {
        int p1=participanti[i];
        int p2=participanti[i+1];
        int punct_rupere=rand()%l;

        if(detalii) {
            fout<<"Recombinare dintre cromozomul "<<p1+1<<" si cromozomul "<<p2+1<<":\n";
            fout<<populatie_urmatoare[p1].binar<<" "<<populatie_urmatoare[p2].binar<<" punct "<<punct_rupere<<"\n";

        }

        for(int j=punct_rupere;j<l;j++) {
            swap(populatie_urmatoare[p1].binar[j], populatie_urmatoare[p2].binar[j]);
        }

        evalueaza_individ(populatie_urmatoare[p1]);
        evalueaza_individ(populatie_urmatoare[p2]);

        if(detalii) {
            fout<<"Rezultat: "<<populatie_urmatoare[p1].binar<<" "<<populatie_urmatoare[p2].binar<<"\n";
        }
    }
    if(detalii) {
        fout<<"\n Dupa recombinare:\n";
        for(int i=0;i<n;i++) {
            fout<<i+1<<": "<<populatie_urmatoare[i].binar<<" x= "<<populatie_urmatoare[i].x
            <<" f= "<<populatie_urmatoare[i].fitness<<"\n";
        }
    }
}

void incrucisare_modificata(vector<Cromozom>& populatie_urmatoare, bool detalii, ofstream& fout) {
    vector<int> participanti;

    for(int i=0;i<n;i++) {
        double u=random_01();
        if(u<pc) {
            participanti.push_back(i);
        }
    }

    if(participanti.size()%2!=0) {
        participanti.pop_back();
    }

    for(int i=0;i<participanti.size();i+=2) {
        int p1=participanti[i];
        int p2=participanti[i+1];

        vector<int> valori_binare(l);
        for(int j=0;j<l;j++) {
            valori_binare[j]=rand()%2;
        }

        if(detalii) {
            fout<<"Recombinare intre "<<p1+1<<" si " <<p2+1<<":\n";
            fout<<populatie_urmatoare[p1].binar << "(Parinte 1)\n";
            fout<<populatie_urmatoare[p2].binar << "(Parinte 2)\n";

            fout<<"Vectorul binar: ";
            for(int j=0;j<l;j++)
                fout<<valori_binare[j];
            fout<<"\n";
        }

        for(int j=0;j<l;j++) {
            if(valori_binare[j]==0) {
                swap(populatie_urmatoare[p1].binar[j],populatie_urmatoare[p2].binar[j]);
            }
        }

        if(detalii) {
            fout<<"Rezultat:\n";
            fout<<populatie_urmatoare[p1].binar<<" (Copil 1)\n";
            fout<<populatie_urmatoare[p2].binar<<" (Copil 2)\n\n";
        }

        evalueaza_individ(populatie_urmatoare[p1]);
        evalueaza_individ(populatie_urmatoare[p2]);
    }
}

void mutatie(vector<Cromozom>& populatie_urmatoare, bool detalii, ofstream& fout) {
    if (detalii) {
        fout<<"\n Probabilitate de mutatie pentru fiecare gena: "<<pm<<"\n";
        fout<<"Au fost modificati cromozomii:\n";
    }
    for(int i=0;i<n;i++) {
        bool suferit_mutatie=false;
        for(int j=0;j<l;j++) {
            double u=random_01();
            if(u<pm) {
                if(populatie_urmatoare[i].binar[j]=='1')
                    populatie_urmatoare[i].binar[j]='0';
                else
                    populatie_urmatoare[i].binar[j]='1';
                suferit_mutatie=true;
            }
        }
        if(suferit_mutatie) {
            if(detalii) {
                fout<<i+1<<"\n";
            }
            evalueaza_individ(populatie_urmatoare[i]);
        }
    }
    if(detalii) {
        fout<<"\nDupa mutatie:\n";
        for(int i=0;i<n;i++) {
            fout<<i+1<<": "<<populatie_urmatoare[i].binar<<" x= "<<populatie_urmatoare[i].x
            <<" f= "<<populatie_urmatoare[i].fitness<<"\n";
        }
        fout<<"\nEvolutia maximului:\n";
    }
}

void afis_statistici(const vector<Cromozom>& populatie, int gen, ofstream& fout) {
    double max_fitness=populatie[0].fitness;
    double suma_fitness=0;

    for(int i=0;i<n;i++) {
        if(populatie[i].fitness>max_fitness) {
            max_fitness=populatie[i].fitness;
        }
        suma_fitness+=populatie[i].fitness;
    }
    fout<<"Generatia "<<gen+1<<" - Max: "<<max_fitness<<" Medie: "<<suma_fitness/n<<"\n";
}
int main()
{
    srand(time(NULL));

    ifstream fin("date.in");
    ofstream fout("Evolutie.txt");

    fin>>n>>a>>b>>coefA>>coefB>>coefC>>p>>pc>>pm>>etape;

    l=ceil(log2((b-a)*pow(10,p))-1e-9);

    vector<Cromozom> populatie(n);
    vector<Cromozom> populatie_urmatoare(n);

    fout<<fixed<<setprecision(5);

    generare_populatie_initiala(populatie,fout);

    for(int gen=0;gen<etape;gen++) {
        bool scrie_detalii=(gen==0);

        Cromozom elita_veche=extrage_elita(populatie);

        selectia_ruletei(populatie,populatie_urmatoare,scrie_detalii,fout);
        //incrucisare(populatie_urmatoare,scrie_detalii, fout);
        incrucisare_modificata(populatie_urmatoare, scrie_detalii, fout);
        mutatie(populatie_urmatoare, scrie_detalii, fout);

        inserare_elita(populatie_urmatoare,elita_veche);

        populatie=populatie_urmatoare;
        afis_statistici(populatie, gen, fout);
    }

    fin.close();
    fout.close();
    return 0;
}
