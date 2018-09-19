//PREPROCESSORE----------------------------------------------------------------------
#include "mostro.h"
#include "eccezionemostro.h"
#include <math.h>
#include "megapietra.h"

using std::string;

//STATISTICHE E SOGLIE----------------------------------------------------------
int Mostro::sogliaStat=255;
int Mostro::sogliaSaluteMax=600;
int Mostro::aumentoStatLivello=10;
int Mostro::costante_attacco=5; //cambiare
int Mostro::costante_difesa=5; //idem
int Mostro::costante_danno=5; //idem
int Mostro::sogliaEnergia=5000;
int Mostro::moltiplicatore_energia=10;
int Mostro::rangoMax=10;
//COSTRUTTORI-------------------------------------------------------------------

Mostro::Mostro(int smax, int sattuale, vector<int> st, int en, vector<string> t, int ran, bool mega):
    energia(en), salute_max(smax),salute_attuale(sattuale), rango(ran), megaevoluto(mega){

    salute_max=checkBounds(1, sogliaSaluteMax, salute_max);
    salute_attuale= checkBounds(0, salute_max,salute_attuale);

    energia=checkBounds(0, sogliaEnergia, energia);
    rango=checkBounds(1, rangoMax, rango);

    if(t.size()==0)
        throw EccezioneMostro("Nessun tipo valido inserito");

    //controllo dei tipi
    for(unsigned int i=0; i<t.size();i++){
        if(inVector(getTipi(), t[i]))
            tipo.push_back(t[i]);
    }

    if(tipo.size()==0)
        throw EccezioneMostro("Nessun tipo valido inserito");

    map<string,int>::iterator it = stats.begin();

    for(unsigned int i = 0; i<st.size(); it++, i++){
        stats.insert(it, std::pair<string,int>(statistiche[i], checkBounds(1,sogliaStat, st[i])));
    }
}


QMap<QString, QString> Mostro::toMap() const{

    QMap<QString, QString> ris;
    ris.insert(QString::fromStdString("Energia"), QString::number(getEnergia()));
    ris.insert(QString::fromStdString("Salute massima"), QString::number(getSaluteMax()));
    ris.insert(QString::fromStdString("Salute attuale"), QString::number(getSaluteAttuale()));
    ris.insert(QString::fromStdString("Rango"), QString::number(getRango()));
    ris.insert(QString::fromStdString("Megaevoluto"), QString::fromStdString(isMegaevoluto()?"Si":"No"));
    map<string,int> stat= getStatistiche();
    for(auto it=stat.begin(); it!=stat.end(); ++it){
        ris.insert(QString::fromStdString(it->first),QString::number(it->second));
    }
    vector<std::string> tipi= getTipo();
    for(unsigned int i=0; i<tipi.size();i++){
        QString s= QString::fromStdString("Tipo")+QString::number(i+1);
        ris.insert(s, QString::fromStdString(tipi[i]));
    }
    return ris;
}


//OVERLOADING---------------------------------

ostream& operator<<(ostream& os, const Mostro& m1){
    os<<"Energia: "<<m1.energia<<endl;
    os<<"Salute massima: "<<m1.salute_max<<endl;
    os<<"Salute attuale: "<<m1.salute_attuale<<endl;
    os<<"Rango: "<<m1.rango<<endl;
    os<<"Megaevoluto: ";
    if(m1.megaevoluto)
        os<<"sì"<<endl;
    else
        os<<"no"<<endl;
    os<<"Tipi: "<<m1.tipo<<endl;
    for(auto it =m1.stats.begin(); it!=m1.stats.end(); ++it){
        os<<it->first<<" "<<it->second<<endl;
    }
    return os;
}

//METODI DI SET-----------------------------------------------------------------

void Mostro::modificaSalute(int delta){
    salute_attuale=checkBounds(0, salute_max, (salute_attuale+delta));
}


void Mostro::modificaSalutePerc(int percentuale){
    salute_attuale=checkBounds(0, salute_max, (salute_attuale+(salute_attuale*percentuale/100)));
}


void Mostro::modificaSaluteMaxPercentuale(int percentuale){
    salute_max=checkBounds(0, sogliaSaluteMax, (salute_max+(salute_max*percentuale/100)));
}


void Mostro::modificaStatPercentuale(string s, int delta){
    if(!statisticaPresente(s))
        throw EccezioneMostro("statistica non presente");
    stats[s]=checkBounds(1, sogliaStat, (stats[s]+stats[s]*delta/100));

}


void Mostro::modificaTutteStatistichePerc(int percentuale){
    map<string, int>::iterator it = stats.begin();
    for (; it!=stats.end(); it++){
        this->modificaStatPercentuale(it->first, percentuale);
    }
}


void Mostro::modificaEnergia(int delta){
    if(energia+delta<0)
        throw EccezioneMostro("sotto la soglia, risultato: "+std::to_string(energia-delta));
    energia=checkBounds(1, sogliaEnergia, (energia+delta));
}


Mostro* Mostro::clone() const{
    return new Mostro(*this);
}

//METODI DI GET----------------------------------------------------------------------------------

int Mostro::getSaluteAttuale() const{
    return salute_attuale;
}


int Mostro::getSaluteMax() const{
    return salute_max;
}


map<string, int> Mostro::getStatistiche() const{
    return stats;
}


int Mostro::getEnergia() const{
    return energia;
}


bool Mostro::isSaluteMax() const{
    return salute_attuale==salute_max;
}


bool Mostro::isDead() const{
    return salute_attuale==0;
}


int Mostro::getRango() const{
    return rango;
}


bool Mostro::statisticaPresente(string s) const{
    if(stats.find(s)!=stats.end()) //se e' diverso vuol dire che e' presente
        return true;
    return false;
}


int Mostro::energiaNecessaria() const{
    return pow(rango,2)*moltiplicatore_energia;
}


double Mostro::getRandom(){
    srand(time(NULL));
    double N = double((rand() % 21 + 80))/100;
    return N;
}


double Mostro::getDannoBase(int rango, int att) const{
    return sqrt(pow(rango,2)*att);
}


bool Mostro::checkTipo(string t) const{
    return inVector(tipo,t);
}


bool Mostro::isMegaevoluto() const{
    return megaevoluto;
}


vector<string> Mostro::getTipo() const{
    return tipo;
}


int Mostro::getSogliaSaluteMax(){
    return sogliaSaluteMax;
}


int Mostro::getSogliaStat(){
    return sogliaStat;
}


int Mostro::getRangoMax(){
    return rangoMax;
}


int Mostro::getSogliaEnergia(){
    return sogliaEnergia;
}

//FUNZIONI----------------------------------------------------------------------------------

void Mostro::evolvi(){
    if(energia>=energiaNecessaria()){

        if(rango>=rangoMax){
            throw EccezioneMostro("il rango massimo è già stato raggiunto, impossibile aumentarlo ulteriormente");
        }
        else{
            energia-=energiaNecessaria();
            rango++;

            auto it= stats.begin();
            for(;it!=stats.end();it++){
                modificaStatPercentuale(it->first,aumentoStatLivello);
            }
            salute_max+=checkBounds(1, sogliaSaluteMax ,salute_max*aumentoStatLivello/100);
            modificaSalutePerc(aumentoStatLivello);
        }
    }
    else
        throw EccezioneMostro("Impossibile evolversi, manca la seguente energia: "+std::to_string(energiaNecessaria()-energia));
}


void Mostro::evolvi(Pietra* mp){
    MegaPietra* megapietra= dynamic_cast<MegaPietra*>(mp);
    if(megapietra && checkTipo(megapietra->getTipo()))
       megaevoluto=true;
    try{
        evolvi();
        evolvi();
    }
    catch(const Eccezione& e){

    }
}

Mostro* Mostro::fusione(Mostro *m2){
    if (getComuni(tipo, m2->tipo).size()>0){
        int e = energia + m2->energia;
        int smax = (salute_max + m2->salute_max)*0.8;
        vector<string> t = tipo;
        vector<string>::const_iterator it = m2->tipo.begin();

        for (; it!=m2->tipo.end(); it++){
            bool trovato=false;
            for (unsigned int i = 0; i<t.size(); i++){
                if (*it == t[i])
                    trovato=true;
            }
            if (!trovato)
                t.push_back(*it);
        }

        int a = (abs(stats["Attacco"]+m2->stats["Attacco"])/2)*1.5;
        int d = (abs(stats["Difesa"]+m2->stats["Difesa"])/2)*1.5;
        int a_sp = (abs(stats["Attacco_speciale"]+m2->stats["Attacco_speciale"])/2)*1.5;
        int d_sp = (abs(stats["Difesa_speciale"]+m2->stats["Difesa_speciale"])/2)*1.5;
        int ran=(rango+m2->rango)/2;

        vector<int> s ={a,d,a_sp,d_sp};
        return new Mostro(smax, smax, s, e, t, ran);
    }
    else
        throw EccezioneMostro("Fusione impossibili, mostri incompatibili");
}


void Mostro::attacca(vector<Mostro*> m, int mol) const{ //attacco base senza uso di mosse e senza ambiente
    vector<Mostro*>::iterator it = m.begin();
    for(; it!=m.end(); it++){
        double danno=  ((2*rango+costante_attacco*(stats.find("Attacco")->second)*getDannoBase(rango,(stats.find("Attacco")->second))) /(costante_difesa*(((*it)->stats.find("Difesa"))->second)+ 1) + costante_danno )*getEfficaciaTot(tipo,(*it)->tipo)*getRandom();
        (*it)->modificaSalute(-danno*mol);
    }
}


void Mostro::attacca(vector<Mostro*> m, Ambiente* a) const{ //attacco base senza uso di mosse e con ambiente. m è il vettore di mostri bersaglio

    vector<Mostro*>::iterator it = m.begin();
    for(; it!=m.end(); it++){
        double danno=((2*rango + costante_attacco*(stats.find("Attacco")->second)*getDannoBase(rango,(stats.find("Attacco")->second))) / (costante_difesa*(((*it)->stats.find("Difesa"))->second)*(a->fattoreAmbienteDanno((*it)->tipo)) +1) + costante_danno )*getEfficaciaTot(tipo,(*it)->tipo)* a->fattoreAmbienteDanno(tipo)*getRandom();
        (*it)->modificaSalute(-danno);
    }
}

void Mostro::megaMossa(vector<Mostro*> v){
    if(!megaevoluto)
        throw EccezioneMostro("non sei megaevoluto, non puoi usare la megamossa");
    attacca(v,5);
    megaevoluto=false;
}

void Mostro::sacrificio(Mostro *m){

    energia= checkBounds(0, sogliaEnergia,energia+m->energia);
    if (m->salute_attuale<m->salute_max/2){ // se il mostro da sacrificare è debole
        modificaTutteStatistichePerc(getComuni(tipo, m->tipo).size()*m->rango);
    }
    else{
        modificaTutteStatistichePerc(m->tipo.size()*m->rango*m->salute_attuale/100);
    }
}


