#include <iostream>
using namespace std;
#include <string>
#include <cstdlib>
#include "carta.h"
const int lun=5;

void visualizza_campo(carta vet[][lun]);
void molt_bomb (carta vet[][lun], int diff);
int bombe_in_riga (carta vet[][lun], int riga);
int bombe_in_colonna (carta vet[][lun], int colonna);
void gioca (carta vet[][lun], int & bil);
bool check (carta vet[][lun], int i, int j);
bool chiedi (carta vet[][lun], int & riga, int & colonna);
void pulisci (carta vet[][lun]);

int main(int argc, char** argv) {
	carta vet[lun][lun];
	int bilancio=0;
	int difficolta;
	do {
		cout<<"\nInserisci la difficolta (da 1 a 3): ";
		cin>>difficolta;
	} while (difficolta<1||difficolta>3);
	cout<<"Hai scelto difficolta' "<<difficolta;
	
	
	string risposta="si";
	do
	{
		pulisci (vet);
		molt_bomb(vet,difficolta);
		gioca(vet,bilancio);
		system("cls");
		cout<<"Hai "<<bilancio<<" punti!!";
		cout<<"\nVuoi giocare ancora?: ";
		cin>>risposta;
	}
	while (risposta=="si");
	
	system("PAUSE");
}


void visualizza_campo (carta vet[][lun]) {
	//Le carte sono inizializzate
	int i,j;
	for (i=0;i<lun;++i) {
		for (j=0;j<lun;++j)
			if (vet[i][j].get_coperta())
				cout<<"#        ";
			else
				cout<<vet[i][j].get_valore()<<"        ";
			if (j==lun) {
				cout<<"  ["<<bombe_in_riga(vet,i)<<"]";
				if (i==lun-1) {
					cout<<"\n\n\n";
					for (int t=0;t<lun;++t)
						cout<<"["<<bombe_in_colonna(vet,t)<<"]      ";
				}
			}
			
		cout<<"\n\n\n";
	}
}

void molt_bomb (carta vet[][lun], int diff) {
	
	//Inserimento bombe
	int bombe=int ((diff*0.1)*(lun*lun));
	cout<<"\nSaranno inserite "<<bombe<<" bombe!";
	for (int b=0;b<bombe;)
	{
		int i=rand () % 4;
		int j=rand () % 4;
		if (vet[i][j].get_molt()!=0)
		{
			++b;
			vet[i][j].set_valore('X');
			vet[i][j].set_molt(0);
		}
	}
	
	//Inserimento moltiplicatori
	int num_m;
	switch (diff) {
		case 1: num_m=(0.5)*(lun*lun);break;
		case 2: num_m=(0.3)*(lun*lun);break;
		case 3: num_m=(0.1)*(lun*lun);break;
	}
	cout<<"\nVerranno inseriti "<<num_m<<" moltiplicatori!!";
	for (int n=0;n<num_m;)
	{
		int i=rand () % 4;
		int j=rand () % 4;
		if (vet[i][j].get_molt()!=0)
		{
			++n;
			int val=(rand () % 3) +2;
			vet[i][j].set_valore(val+48);
			vet[i][j].set_molt(val);
		}
	}
}

int bombe_in_riga (carta vet[][lun], int riga) {
	int cont=0;
	for (int j=0;j<lun;++j)
		if (vet[riga][j].get_molt()==0)
			++cont;
	return cont;
} 

int bombe_in_colonna (carta vet[][lun], int colonna) {
	int cont=0;
	for (int i=0;i<lun;++i)
		if (vet[i][colonna].get_molt()==0)
			++cont;
	return cont;
}


void gioca (carta vet[][lun],int & bil) {
	
	int totale=0;
	int riga,colonna,guadagno;
	string risposta="si";
	while (risposta=="si") {
		system("cls");
		cout<<"Totale: "<<totale;
		cout<<"\n\n\n";
		visualizza_campo(vet);
		cout<<"Vuoi scoprire una carta?: ";
		cin>>risposta;
		if (risposta=="si") {
			if (chiedi(vet,riga,colonna))
			{
				if (totale==0)
					totale=vet[riga][colonna].get_molt();
				else
					totale*=vet[riga][colonna].get_molt();
			}
			else
			{
				totale=0;
				cout<<"Hai perso!!!";
				break;
			}
		}
	}
	bil+=totale;	
}

bool chiedi (carta vet[][lun], int & riga, int & colonna) {
	do {
		cout<<"Inserisci riga : ";
		cin>>riga;
	} while (riga<=0||riga>lun);
	do {
		cout<<"Inserisci colonna: ";
		cin>>colonna;
	} while(colonna<=0||colonna>lun);
	
	--riga;
	--colonna;
	cout<<riga<<" "<<colonna;
	
	return check(vet,riga,colonna);
}

bool check (carta vet[][lun], int i, int j) {
	vet[i][j].set_coperta(false);
	if (vet[i][j].get_molt()!=0){
		return true;
	}
	else
		return false;
}

void pulisci (carta vet[][lun]) {
	for (int i=0;i<lun;++i)
		for (int j=0;j<lun;++j)
		{
			vet[i][j].set_coperta(true);
			vet[i][j].set_molt(1);
			vet[i][j].set_valore('1');
		}
}
