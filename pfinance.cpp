#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<ctime>
using namespace std;

struct date {
    int jj;
    int mm;
    int aa;
};

struct Effet {
    int num;
    double valeurNominal;
    date dateEcheance;
    bool place;
    bool domicilie;
    int njE;
    double AgjE;
    int njB;
    double AgjB;
    double AgE1;
    double AgCD;
    double TotAgHT;
    double TVA;
    double TotAgTTC;
    double NetEscpte;
};
int differenceBetweenDates(const std::tm& date1, const std::tm& date2) {
    time_t time1 = mktime(const_cast<tm*>(&date1));
    time_t time2 = mktime(const_cast<tm*>(&date2));
    time_t difference = time2 - time1;
    int daysDifference = difference / (60 * 60 * 24);
    return daysDifference;
}
int jourdebanque(bool onPlace,bool domicilie){
	if (onPlace && domicilie) {
        return 2;
    } else if (onPlace && !domicilie) {
        return 5;
    } else if (!onPlace && domicilie) {
        return 5;
    } else {
        return 5;
    }
}

double calculateCommission(bool onPlace, bool domicilie, double cf0, double cf1, double cf2, double cf3) {
    if (onPlace && domicilie) {
        return cf0;
    } else if (onPlace && !domicilie) {
        return cf1;
    } else if (!onPlace && domicilie) {
        return cf2;
    } else {
        return cf3;
    }
}

void sauvegarderEffets(const vector<Effet>& effets, const string& nomFichier) {
    ofstream fichier(nomFichier.c_str());

    if (fichier.is_open()) {
        for (vector<Effet>::const_iterator it = effets.begin(); it != effets.end(); ++it) {
            const Effet& effet = *it;
            fichier << effet.num << "  " << effet.valeurNominal << "  " << effet.dateEcheance.jj << "  " << effet.dateEcheance.mm << "  " << effet.dateEcheance.aa << " "
                    << effet.place << "  " << effet.domicilie << "  " << effet.njE << "  " << effet.AgjE << "  " << effet.njB << "  " << effet.AgjB << "  "
                    << effet.AgE1 << "  " << effet.AgCD << "  " << effet.TotAgHT << "  " << effet.TVA << "  " << effet.TotAgTTC<< "  "<<effet.NetEscpte<< endl;
        }

        fichier.close();
    } else {
        cerr << "Erreur lors de l'ouverture du fichier." << endl;
    }
}

void chargerEffets(vector<Effet>& effets, const string& nomFichier) {
    ifstream fichier(nomFichier.c_str());

    if (fichier.is_open()) {
        while (!fichier.eof()) {
            Effet effet;
            fichier >> effet.num >> effet.valeurNominal >> effet.dateEcheance.jj >> effet.dateEcheance.mm >> effet.dateEcheance.aa
                    >> effet.place >> effet.domicilie >> effet.njE >> effet.AgjE >> effet.njB >> effet.AgjB
                    >> effet.AgE1 >> effet.AgCD >> effet.TotAgHT >> effet.TVA >> effet.TotAgTTC>> effet.NetEscpte;

            if (!fichier.fail()) {
                effets.push_back(effet);
            }
        }

        fichier.close();
    } else {
        cerr << "Erreur lors de l'ouverture du fichier." << endl;
    }
}

int main() {
	int t;
	int tailleTableau ; 
	double cf0,cf1,cf2,cf3,TVA;
	float tot1=0,tot2=0,tot3=0,tot4=0,tot5=0,tot6=0,tot7=0,tot8=0,tot9=0,tot=0;
	date d;
	cout<<"taux d'escompte: ";
	cin>>t;
	cout<<"date d'escompte(jj mm aaaa): ";
	cin>>d.jj>>d.mm>>d.aa;
	cout<<"Commission fixe place domicilie: ";
	cin>>cf0;
	cout<<"Commission fixe place non domicilie: ";
	cin>>cf1;
	cout<<"Commission fixe non place domicilie: ";
	cin>>cf2;
	cout<<"Commission fixe non place non domicilie: ";
	cin>>cf3;
	cout<<"TVA: ";
	cin>>TVA;
	cout<<"entrer le nbre d'effets: ";
	cin>>tailleTableau;
    vector<Effet> tableauEffets(tailleTableau);

    for (int i = 0; i < tailleTableau; i++) {
        cout << "entrer le num d'effet: ";
        cin >> tableauEffets[i].num;
        cout << "entrer la valeur nominale: ";
        cin >> tableauEffets[i].valeurNominal;
        tot1+=tableauEffets[i].valeurNominal;
        cout << "entrer  date d'echeance(jj mm aa): ";
        cin >> tableauEffets[i].dateEcheance.jj>>tableauEffets[i].dateEcheance.mm>>tableauEffets[i].dateEcheance.aa;
        cout<<"domicilie(entrer 0 ou 1): "; //entrer 1 si vrai 0 sinon
        cin>>tableauEffets[i].domicilie;
        cout<<"place(entrer 0 ou 1): "; // entrer 1 si vrai 0 sinon
        cin>>tableauEffets[i].place;
         tm date1 = {};
		 date1.tm_year = d.aa - 1900 ;
		 date1.tm_mon = d.mm;
		 date1.tm_mday = d.jj;
		 tm date2 = {};
		 date2.tm_year = tableauEffets[i].dateEcheance.aa - 1900 ;
		 date2.tm_mon = tableauEffets[i].dateEcheance.mm;
		 date2.tm_mday = tableauEffets[i].dateEcheance.jj;
		 int result = differenceBetweenDates(date1, date2);
		 tableauEffets[i].njE=result;
		 tot+=tableauEffets[i].njE;
		 tableauEffets[i].AgjE=(tableauEffets[i].valeurNominal*t*result)/36000;
		 tot2+=tableauEffets[i].AgjE;
		 tableauEffets[i].njB= jourdebanque(tableauEffets[i].place,tableauEffets[i].domicilie);
		 tableauEffets[i].AgjB=(tableauEffets[i].valeurNominal*t*tableauEffets[i].njB)/36000;
		 tot3+=tableauEffets[i].AgjB;
		 tableauEffets[i].AgE1=tableauEffets[i].AgjE+tableauEffets[i].AgjB;
		 tot4+=tableauEffets[i].AgE1;
		 tableauEffets[i].AgCD=calculateCommission(tableauEffets[i].place, tableauEffets[i].domicilie, cf0,  cf1,  cf2, cf3);
		 tot5+=tableauEffets[i].AgCD;
		 tableauEffets[i].TotAgHT=tableauEffets[i].AgE1+tableauEffets[i].AgCD;
		 tot6+=tableauEffets[i].TotAgHT;
		 tableauEffets[i].TVA=TVA*(tableauEffets[i].AgCD)/100;
		 tot7+=tableauEffets[i].TVA;
		 tableauEffets[i].TotAgTTC=tableauEffets[i].TotAgHT+tableauEffets[i].TVA;
		 tot8+=tableauEffets[i].TotAgTTC;
		 tableauEffets[i].NetEscpte=tableauEffets[i].valeurNominal-tableauEffets[i].TotAgTTC;
		 tot9+=tableauEffets[i].NetEscpte;

        cout << endl; 
    
    }
    sauvegarderEffets(tableauEffets, "effets.txt");
    vector<Effet> effetsLus;
    chargerEffets(effetsLus, "effets.txt");
    
    
    
    
    cout<<"----------------------------------------------------------------------Bordeaurou d'escompte----------------------------------------------------------------------------"<<'\n';
    cout << setw(5) << "N:" << setw(20) << "Valeur nominale" << setw(15) << "Echeance" << setw(20) << "Domicile"
         << setw(10) << "Place" << setw(5) << "njE" << setw(10) << "AgjE" << setw(10) << "njB" << setw(10) << "AgjB"
         << setw(10) << "AgE1" << setw(10) << "AgCD" << setw(15) << "TotAgHT" << setw(5) << "TVA" << setw(15)
         << "TotAgTTC"<< setw(10) << "NetEscpte" << endl;

    for (vector<Effet>::const_iterator it = effetsLus.begin(); it != effetsLus.end(); ++it) {
        const Effet& effet = *it;
        cout << setw(5) << effet.num << setw(20) << effet.valeurNominal << setw(10) << effet.dateEcheance.jj << '/' << setw(2) << effet.dateEcheance.mm << '/' << setw(5) << effet.dateEcheance.aa
             << setw(15) << (effet.domicilie ? "true" : "false") << setw(10) << (effet.place ? "true" : "false") << setw(5) << effet.njE << setw(10) << effet.AgjE << setw(10) << effet.njB << setw(10) << effet.AgjB
             << setw(10) << effet.AgE1 << setw(10) << effet.AgCD << setw(15) << effet.TotAgHT << setw(7) << effet.TVA << setw(10)
             << effet.TotAgTTC<< setw(12) << effet.NetEscpte<< endl;
             cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    }
               cout << setw(5) << " total " << setw(20) << tot1 << setw(10) << "jj" << '/' << setw(2) << "mm" << '/' << setw(5) << "aaa"
             << setw(15) << " " << setw(10) << " " << setw(5) << tot << setw(10) << tot2 << setw(10) << " "<< setw(10) << tot3
             << setw(10) <<tot4 << setw(10) << tot5 << setw(15) << tot6 << setw(7) << tot7 << setw(10)
             << tot8<< setw(12) << tot9<< endl;
    return 0;
}
