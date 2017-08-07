
#include <iostream>
#include <windows.h>
using namespace std;

bool estBissextile(int);
// renvoi une année qui ne peut etre superieure à l'année actuelle
int getAnnee(SYSTEMTIME);
// renvoi un mois compris entre 1 et le mois actuelle si l'année saisie precedement
// 		est l'année actuelle;
// sinon renvoi un mois entre 1 et 12
int getMois(int, SYSTEMTIME);
// renvoi un jours compris entre 1 et
int getJour(int, int, SYSTEMTIME);
//renvoi une saisie user pour un mois ayant 31jours max
int getJours31(int, int, SYSTEMTIME);
//renvoi une saisie user pour un mois ayant 30jours max
int getJours30(int, int, SYSTEMTIME);
//renvoi une saisie user pour le mois de fevrier, si annee non-bissextile
//saisie, alors limite la saisie à 28jours, sinon 29jours.
int getJoursBi(int, int, SYSTEMTIME);

int main()
{
    int anneeSaisie, moisSaisie, jourSaisie, jourActu, moisActu, anneeActu;
    SYSTEMTIME st;
    //*** RECUPERATION DATE ACTUELLE ***
    GetSystemTime(&st);
    //*** DEMANDEs SAISIEs ***
		anneeSaisie = getAnnee(st);
		moisSaisie = getMois(anneeSaisie, st);
		jourSaisie = getJour(anneeSaisie, moisSaisie, st);
    //*** CALCULS ***
/*         il faut rechercher le nombre d'annees bisextiles depuis son jour
			de naissance
			nbAnneesBisextiles compteur */





        int nbAnneesBisextiles = 0;
        int age=-1;
        for (int i=anneeSaisie; i<=st.wYear; i++){
            if (estBissextile(i)) nbAnneesBisextiles++;
            age++;
        }
        // * calcul le nombre de jours *
        //par ans (bissextiles et non-bissextiles)
        int ageT_jours = (age - nbAnneesBisextiles) * 365 + nbAnneesBisextiles * 366;
        //par mois (un mois est composé de 4 semaines de 7 jours) vous pouvez
        //changer ici en tout cas à vos desires
        ageT_jours += abs(moisSaisie - st.wMonth) * 28;
        // ajoute les jours
        ageT_jours += abs(jourSaisie - st.wDay);

        //int ageT_jours = nbJours_annees + nbJours_mois + nbJours_jours;

        //int ageReel = ageT_jours / 365;
        int moisReel = (ageT_jours % 365) / 28;
        int joursReel = ((ageT_jours % 365) % 28);
    cout << "\nVous avez " << age << " ans, " << moisReel << " mois et " << joursReel << " jours ";
    return 0;
}
bool estBissextile(int annee){
	//Une année bisextile est une année divisible par 4
	//sauf si elle est divisible par 100 auquel cas elle doit être divisible par 400.
	if (annee%100==0 && annee%400==0) return false;
	else if (annee%4==0) return true;
}
int calculAnnees_Jours(int annee, SYSTEMTIME st_){
	return st_.wYear - annee;
}
int getAnnee(SYSTEMTIME st){
	int annee;
	do {
		cout << "Veuillez saisir votre annee de naissance (inferieur a " << st.wYear << "):";
		cin >> annee;
	}while (!(annee <= st.wYear ));
	return annee;
}

int getMois(int annee, SYSTEMTIME st){
	int mois;
	do {
		cout << "Veuillez saisir votre mois de naissance ";
		if (annee == st.wYear) cout << "(inferieur a " << st.wMonth << ")";
		cout << ":";
		cin >> mois;
	}while (!(mois<=12 && mois>=1));
	return mois;
}

int getJour(int annee, int mois, SYSTEMTIME st){
	int jour=0;
	if (annee == st.wYear && mois == st.wMonth)
		cout << "Veuillez saisir votre jour de naissance (inferieur a " << st.wDay << "):";
	else{
		switch (mois){
			//mois à 31
				case 1:jour=getJours31(annee, mois, st);break;
				case 3:jour=getJours31(annee, mois, st);break;
				case 5:jour=getJours31(annee, mois, st);break;
				case 7:jour=getJours31(annee, mois, st);break;
				case 8:jour=getJours31(annee, mois, st);break;
				case 10:jour=getJours31(annee, mois, st);break;
				case 12:jour=getJours31(annee, mois, st);break;
			//mois à 30
				case 4:jour=getJours30(annee, mois, st);break;
				case 6:jour=getJours30(annee, mois, st);break;
				case 9:jour=getJours30(annee, mois, st);break;
				case 11:jour=getJours30(annee, mois, st);break;
			//mois de fevrier check si année bissextile
				case 2:jour=getJoursBi(annee, mois, st);
		}
	}
	return jour;
}

/* **** FONCTIONS *** */
int getJours31(int annee, int mois, SYSTEMTIME st){
	int jour;
	do {
			cout << "Veuillez saisir votre jour de naissance (entre 1 et 31):";
			cin >> jour;
		}while(!(jour>=1 && jour<=31));
	return jour;
}

int getJours30(int annee, int mois, SYSTEMTIME st){
	int jour;
	do {
			cout << "Veuillez saisir votre jour de naissance (entre 1 et 30):";
			cin >> jour;
		}while(!(jour>=1 && jour<=30));
	return jour;
}

int getJoursBi(int annee, int mois, SYSTEMTIME st){
	int jour;
		if (estBissextile(annee)){
			do{
				cout << "Veuillez saisir votre jour de naissance (entre 1 et 29):";
				cin >> jour;
			}while(!(jour>=1 && jour<=29));
			return jour;
		}
		else {
			do{
				cout << "Veuillez saisir votre jour de naissance (entre 1 et 28):";
				cin >> jour;
			}while(!(jour>=1 && jour<=28));
			return jour;
		}
}
/* *** FIN FONCTIONS *** */
