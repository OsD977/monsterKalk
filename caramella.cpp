//PREPROCESSORE----------------------------------------------------------------------
#include "caramella.h"
#include "etere.h"

//DEFINIZIONI VARIABILI STATICHE
int Caramella::minQualita=1;
int Caramella::maxQualita=5;
int Caramella::maxAumentoCaramella=15;


//OVERLOADING
ostream& operator<<(ostream& s, const Caramella& c){
    cout<<static_cast<Bacca>(c);
    cout<<"Qualita :"<<c.qualita<<endl;
    return s;
}


//COSTRUTTORI----------------------------------------------------------------------

Caramella::Caramella(string g, int cal, int qual): Bacca(g,cal){
    qualita=checkBounds(minQualita, maxQualita, qual);
}


//METODI DI GET---------------------------------------------------------------

int Caramella::getQualita() const{
    return qualita;
}


int Caramella::getMinQual(){
    return minQualita;
}


int Caramella::getMaxQual(){
    return maxQualita;
}


//FUNZIONI----------------------------------------------------------------------

Caramella* Caramella::clone() const{
    return new Caramella(*this);
}


void Caramella::usa(Mostro* m) const{
    m->modificaSaluteMaxPercentuale(qualita*getValoreGusto()*getCalorie()/100);
    m->modificaSalutePerc(qualita+getCalorie()/10);
    m->modificaEnergia(getCalorie()*1.5);
    m->modificaTutteStatistichePerc(checkBounds(0,maxAumentoCaramella,qualita*getValoreGusto()));
}


Etere* Caramella::spremi(){
    Etere* e = new Etere(Strumento::getFormatoFromValore(randomBetween(1,4)),getTutteStatistiche(),getCalorie()*getValoreGusto()*qualita/100);
    return e;
}


void Caramella::esponi(Ambiente* a){
    setCaloriePerc((a->getPercAumento()-a->getPercDecremento())*qualita);
}


Caramella* Caramella::cucina(Cura* materiale){
    string gusto_ris;
    int qualita_ris;
    int calorie_ris;

    Bacca* mat_bacca= dynamic_cast<Bacca*>(materiale);
    if(mat_bacca){
        gusto_ris=getGustofromValore((Gusti[getGusto()]+ Gusti[mat_bacca->getGusto()])/2);
        calorie_ris= calorie+ mat_bacca->getCalorie();
        qualita_ris=(abs(Gusti[getGusto()]-Gusti[mat_bacca->getGusto()])+1); //arriva al max a 5
        return new Caramella(gusto_ris, calorie_ris, qualita_ris);
    }
    else{
        Strumento* str= dynamic_cast<Strumento*>(materiale);
        if(str)
            return new Caramella(gusto, calorie, str->getFormato());
        else
            throw EccezioneBacca("non posso cucinare la bacca con questa cura");
    }
}


QMap<QString, QString> Caramella::toMap() const{
    QMap<QString, QString> ris;
    ris.insert(QString("Calorie"),QString::number(getCalorie()));
    ris.insert(QString("Gusto"),QString::fromStdString(getGusto()));
    ris.insert(QString("Qualità"),QString::number(getQualita()));

    return ris;
}
