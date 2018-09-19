//PREPROCESSORE----------------------------------------------------------------
#include "bacca.h"
#include "caramella.h" //provato a mettere l'include così ho il contruttore
#include "strumento.h"


//DEFINIZIONI VARIABILI STATICHE
int Bacca::minCalorie=1;
int Bacca::maxCalorie=1000;
map<string, int> Bacca::Gusti=init_gusti();


//OVERLOADING
ostream& operator<<(ostream& s, const Bacca& b){
    cout<<"Gusto :"<<b.gusto<<endl;
    cout<<"Calorie :"<<b.calorie<<endl;
    return s;
}

//COSTRUTTORI------------------------------------------------------------------

map<string, int> Bacca::init_gusti(){
    map<string, int> ris;
    vector<string> nomi={"Dolce", "Salato", "Pepato", "Aspro", "Amaro"};
    vector<int> valori={1,2,3,4,5};
    for(unsigned int i=0; i<nomi.size(); i++){
        ris.insert(pair<string, int>(nomi[i], valori[i]));
    }
    return ris;
}


Bacca::Bacca(string g, int c) {
    calorie=checkBounds(minCalorie, maxCalorie, c);
    if (inMap(Gusti,g))
        gusto = g;
    else
        throw EccezioneBacca("Gusto non esistente");
}

//METODI GET-------------------------------------------------------------------

string Bacca::getGusto() const{
    return gusto;
}


int Bacca::getCalorie() const{
    return calorie;
}


int Bacca::getValoreGusto() const{
    return Gusti[gusto];
}


string Bacca::getGustofromValore(int val){
    for(auto it=Gusti.begin(); it!=Gusti.end(); it++){
        if(it->second==val){
            return it->first;
        }
    }
    throw EccezioneBacca("gusto non trovato");
}


int Bacca::getMaxCal(){
    return maxCalorie;
}


int Bacca::getMinCal(){
    return minCalorie;
}


//METODI SET-------------------------------------------------------------------

void Bacca::setCaloriePerc(int c){
    calorie+=calorie*c/100;
    calorie=checkBounds(minCalorie, maxCalorie, calorie+(calorie*c/100));
}


//FUNZIONI

Bacca* Bacca::clone() const{
    return new Bacca(*this);
}

void Bacca::usa(Mostro* m) const{
    if (!m->isDead()){
        m->modificaSaluteMaxPercentuale((m->getRango()+Gusti[gusto])*(calorie/100));
        m->modificaSalutePerc(Gusti[gusto]+calorie*30/100);
        m->modificaEnergia(calorie);
    }
    else
        throw EccezioneBacca("Il mostro bersaglio è morto");
}


void Bacca::esponi(Ambiente* a){
    setCaloriePerc(a->getPercAumento()-a->getPercDecremento());
}


Pozione* Bacca::spremi(){
    Pozione* p = new Pozione(Strumento::getFormatoFromValore(randomBetween(1,4)), calorie * Gusti[gusto]/5);
    return p;
}


Caramella* Bacca::cucina(Cura* materiale){
    string gusto_ris;
    int qualita_ris;
    int calorie_ris;
    Bacca* mat_bacca= dynamic_cast<Bacca*>(materiale);
    if(mat_bacca){
        gusto_ris= getGustofromValore((Gusti[gusto]+Gusti[mat_bacca->gusto])/2);
        calorie_ris= calorie+ mat_bacca->calorie;
        qualita_ris= abs(Gusti[gusto]-Gusti[mat_bacca->gusto])+1; //arriva al max a 5
        return new Caramella(gusto_ris, calorie_ris, qualita_ris);
    }
    else{
        Strumento* mat_str= dynamic_cast<Strumento*>(materiale);
        if(mat_str)
            return new Caramella(gusto, calorie, mat_str->getFormato());
        else
            throw EccezioneBacca("non posso cucinare la bacca con questo oggetto");
    }
}


QMap<QString, QString> Bacca::toMap() const{
    QMap<QString, QString> ris;
    ris.insert(QString("Calorie"),QString::number(getCalorie()));
    ris.insert(QString("Gusto"),QString::fromStdString(getGusto()));

    return ris;
}
