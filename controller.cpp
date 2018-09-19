#include "controller.h"
#include "eccezionegestione.h"
#include <QDebug>
#include "displayobject.h"
#include "monsterkalk.h"

//COSTRUTTORI
Controller::Controller(MonsterKalk* view_){
    view= view_;
    modello= new Model();
    vector<string> flags={"usa", "spremi", "cucina", "esponi", "unisci", "attacca", "megamossa", "evolvi", "sacrifica", "lucida","raffina", "frammenta", "esegui", "inverti", "fusione", "finale"};

    for(unsigned int i=0; i<flags.size(); i++){
        flag.insert(pair<string, bool>(flags[i], false));
    }

}

Controller::~Controller(){
    delete modello;
}


//METODI DI SET
void Controller::setFlag(string nome, bool stato){
    auto aux=flag.find(nome);
    if(aux!=flag.end()){
        aux->second=stato;
    }
}


//METODI DI GET
bool Controller::getFlag(string nome) const{
    auto aux=flag.find(nome);
    if(aux!=flag.end())
        return aux->second;
    else
        throw("non trovata");
}


Oggetto* Controller::getLastAttuali() const{
    return modello->getLastAttuali();
}


int Controller::getSizeAttuali() const{
    return modello->getSizeAttuali();
}


//GESTIONE FLAG
void Controller::freeFlag(){
    for(auto it=flag.begin(); it!= flag.end(); it++){
        it->second=false;
    }
}


void Controller::reset(){
    modello->reset();
    freeFlag();
    freeAttuali();
    freeSalvati();
    freeRisultati();
}

void Controller::reStart(){
    setFlag("finale", false);
    freeAttuali();
    freeFlag();
}


void Controller::addAttuali(Oggetto* oggetto, QPixmap img){
    if (getFlag("finale")){
        reStart();
        view->reStart();
    }
    mappa_attuali.insert(oggetto,img);
    modello->inserisciAttuali(oggetto);
    DisplayObject* disp = new DisplayObject(img, oggetto->toMap(),view);
    view->displayAdd(disp);
}


void Controller::addSalvati(Oggetto* oggetto, QPixmap img){
    mappa_salvati.insert(oggetto,img);
    modello->inserisciSalvati(oggetto);

    QString q1(":/Icons/elimina.png");
    QString q2(":/Icons/riutilizza.png");
    DisplayObjectButton* disp = new DisplayObjectButton(q1,q2,oggetto,true,img, oggetto->toMap());
    view->salvatiAdd(disp);
}


void Controller::addFunzione(string nome){
    if (getFlag("finale")){
        reStart();
        view->reStart();
        if(mappa_risultati.size()==1){
            auto it=mappa_risultati.begin();
            addAttuali(it.key()->clone(), it.value());
        }
    }
    setFlag(nome);
    QPixmap p= QPixmap(":/Icons/"+QString::fromStdString(nome)+".png");
    DisplayObject* a= new DisplayObject(p, view);
    view->displayAdd(a);
}


void Controller::addRisultati(Oggetto* oggetto, QPixmap img){
    mappa_risultati.insert(oggetto,img);
    modello->inserisciRisultati(oggetto);

    QString q1(":/Icons/salva.png");
    QString q2(":/Icons/riutilizza.png");
    DisplayObjectButton* disp = new DisplayObjectButton(q1,q2,oggetto,false,img, oggetto->toMap());
    view->risultatiAdd(disp);
}


void Controller::freeAttuali(){
    mappa_attuali.clear();
    modello->freeAttuali();
}


void Controller::freeSalvati(){
    mappa_salvati.clear();
    modello->freeSalvati();
}


void Controller::freeRisultati(){
    mappa_risultati.clear();
    modello->freeRisultati();
}


void Controller::deleteFromAttuali(Oggetto *oggetto){
    mappa_attuali.remove(oggetto);
    modello->deleteLastAttuali();
}


void Controller::deleteFromSalvati(Oggetto *oggetto){
    mappa_salvati.remove(oggetto);
    modello->deleteFromSalvati(oggetto);
}


QPixmap Controller::getPixmap(Oggetto *obj) const{
    auto it=mappa_attuali.find(obj);
    if(it!=mappa_attuali.end()){
        return it.value();
    }
    else{
        throw EccezioneGestione("nessun oggetto da eliminare");
    }
}


vector<pair<Oggetto*, QPixmap>> Controller::toResult() const{
    vector<pair<Oggetto*, QPixmap>> ris;

    if(getFlag("usa")){
        Mostro* mostro= dynamic_cast<Mostro*>(modello->popFirstAttuali());
        Cura* cura=dynamic_cast<Cura*>(modello->popFirstAttuali());
        if(modello->getSizeAttuali()==0 && mostro && cura){
            cura->usa(mostro);
            ris.push_back(pair<Oggetto*, QPixmap>(mostro, getPixmap(mostro)));
        }
        else{
            throw EccezioneGestione("Errore! La funzione usa necessita 2 parametri, il primo deve essere un mostro ed il secondo uno strumento");
        }
    }
    else if(getFlag("spremi")){
        Cura* spremuto= dynamic_cast<Cura*>(modello->popFirstAttuali());
        if(modello->getSizeAttuali()==0 && (dynamic_cast<Bacca*>(spremuto) || dynamic_cast<Caramella*>(spremuto))){
            if(dynamic_cast<Caramella*>(spremuto)){
                Etere* prodotto=static_cast<Caramella*>(spremuto)->spremi();
                ris.push_back(pair<Oggetto*, QPixmap>(prodotto, QPixmap(":/Icons/etere.png")));
            }
            else{
                Pozione* prodotto=static_cast<Bacca*>(spremuto)->spremi();
                ris.push_back(pair<Oggetto*,QPixmap>(prodotto, QPixmap(":/Icons/pozione.png")));
            }
        }
        else{
            throw EccezioneGestione("Errore! Si possono spremere solo una BACCA o una CARAMELLA per volta.");
        }
    }
    else if(getFlag("cucina")){
        //necessita che il primo sia una bacca o una caramella il secondo deve essere una cura
        Bacca* cucinato= dynamic_cast<Bacca*>(modello->popFirstAttuali());
        Cura* additivo= dynamic_cast<Cura*>(modello->popFirstAttuali());
        if(modello->getSizeAttuali()==0 && cucinato && additivo){
            Caramella* prodotto= cucinato->cucina(additivo);
            ris.push_back(pair<Oggetto*, QPixmap>(prodotto, QPixmap(":/Icons/caramella.png")));
        }
        else{
            throw EccezioneGestione("Errore! Si possono cucinare solo una BACCA o una CARAMELLA per volta, con l'aggiunta di uno STRUMENTO o di una BACCA/CARAMELLA");

        }

    }
    else if(getFlag("esponi")){
        //devo esporre una bacca o una caramella ad un ambiente
        Bacca* esposto= dynamic_cast<Bacca*>(modello->popFirstAttuali());
        Ambiente* ambiente= dynamic_cast<Ambiente*>(modello->popFirstAttuali());
        if(modello->getSizeAttuali()==0 && esposto && ambiente){
            esposto->esponi(ambiente);
            ris.push_back(pair<Oggetto*, QPixmap>(esposto, getPixmap(esposto)));
        }
        else{
            throw EccezioneGestione("Errore! Si possono esporre solo una BACCA o una CARAMELLA ad un AMBIENTE");

        }

    }
    else if(getFlag("unisci")){
        //unisce due strumenti ed ottiene una pietra
        Strumento* materiale1= dynamic_cast<Strumento*>(modello->popFirstAttuali());
        Strumento* materiale2= dynamic_cast<Strumento*>(modello->popFirstAttuali());
        if(modello->getSizeAttuali()==0 && materiale1 && materiale2){
            Pietra* prodotto= Strumento::unisci(materiale1, materiale2);
            ris.push_back(pair<Oggetto*, QPixmap>(prodotto, QPixmap(":/Icons/pietra.png")));
        }
        else{
            throw EccezioneGestione("Errore! Si possono unire solo due STRUMENTI, non BACCHE o CARAMELLE");

        }
    }
    else if(getFlag("attacca")){
        Mostro* mostro= dynamic_cast<Mostro*>(modello->popFirstAttuali());
        if(mostro){
            if(mostro->getSaluteAttuale()==0)
                throw EccezioneGestione("il mostro è debilitato e quindi non è in grado di attaccare");
            if(modello->getSizeAttuali()>0){
                int j=getSizeAttuali();
                int ambientiCont=0;
                Ambiente* ambiente=nullptr;
                vector<Mostro*> bersagli;
                for(int i=0; i<j; i++){
                    Oggetto* ber= dynamic_cast<Oggetto*>(modello->popFirstAttuali());
                    if(dynamic_cast<Mostro*>(ber)){
                        bersagli.push_back(static_cast<Mostro*>(ber));
                    }
                    else if(dynamic_cast<Ambiente*>(ber)){
                        if(ambientiCont==0){
                            ambiente=static_cast<Ambiente*>(ber);
                            ambientiCont++;
                        }
                        else{
                            throw EccezioneGestione("trovati due ambienti, solo un ambiente è permesso");
                        }
                    }
                    else{
                        throw EccezioneGestione("trovato un non mostro e non ambiente tra i bersagli");
                    }

                }

                if(bersagli.size()==0)
                    throw EccezioneGestione("nessun bersaglio inserito, inserire almeno un mostro");

                if(ambiente){
                    mostro->attacca(bersagli, ambiente);
                }
                else{
                    mostro->attacca(bersagli);
                }

                for(unsigned int i=0; i<bersagli.size(); i++){
                    ris.push_back(pair<Oggetto*, QPixmap>(bersagli[i], getPixmap(bersagli[i])));
                }

            }
            else{
                throw EccezioneGestione("deve essere presente almeno un bersaglio in un attacco");
            }
        }
        else{
            throw EccezioneGestione("solo un mostro può attaccare");
        }

    }
    else if(getFlag("megamossa")){
        Mostro* mostro= dynamic_cast<Mostro*>(modello->popFirstAttuali());
        if(mostro){
            if(mostro->getSaluteAttuale()==0)
                throw EccezioneGestione("il mostro è debilitato e quindi non è in grado di attaccare");
            if(modello->getSizeAttuali()>0){
                int j=getSizeAttuali();
                vector<Mostro*> bersagli;
                for(int i=0; i<j; i++){
                    Mostro* ber= dynamic_cast<Mostro*>(modello->popFirstAttuali());
                    if(dynamic_cast<Mostro*>(ber)){
                        bersagli.push_back(static_cast<Mostro*>(ber));
                    }
                    else{
                        throw EccezioneGestione("trovato un non mostro tra i bersagli");
                    }
                }

                if(bersagli.size()==0)
                    throw EccezioneGestione("nessun bersaglio inserito, inserire almeno un mostro");

                mostro->megaMossa(bersagli);

                for(unsigned int i=0; i<bersagli.size(); i++){
                    ris.push_back(pair<Oggetto*, QPixmap>(bersagli[i], getPixmap(bersagli[i])));
                }

            }
            else{
                throw EccezioneGestione("deve essere presente almeno un bersaglio in un attacco");
            }
        }
        else{
            throw EccezioneGestione("solo un mostro può attaccare");
        }

    }
    else if(getFlag("evolvi")){
        //vuole un mostro, eventualmente una pietra o una megapietra
        Mostro* mostro= dynamic_cast<Mostro*>(modello->popFirstAttuali());
        if(mostro){
            if(mostro->getSaluteAttuale()==0)
                throw EccezioneGestione("il mostro è debilitato e quindi non è in grado di evolversi");
            if(modello->getSizeAttuali()==0){
                mostro->evolvi();
                ris.push_back(pair<Oggetto*, QPixmap>(mostro, getPixmap(mostro)));
            }
            else if(modello->getSizeAttuali()==1){
                Pietra* pietra= dynamic_cast<Pietra*>(modello->popFirstAttuali());
                if(pietra){
                    mostro->evolvi(pietra);
                    ris.push_back(pair<Oggetto*, QPixmap>(mostro, getPixmap(mostro)));
                }
                else{
                    throw EccezioneGestione("Un mostro può essere evoluto da solo o con una pietra");
                }
            }
            else{
                throw EccezioneGestione("Troppi oggetti, può essere evoluto solo un MOSTRO per volta con al massimo una PIETRA");
            }
        }
        else{
            throw EccezioneGestione("Mostro non trovato, può essere evoluto solo un MOSTRO per volta con al massimo una PIETRA");
        }

    }
    else if(getFlag("sacrifica")){
        //il primo mostro viene potenziato il secondo sacrificato
        Mostro* mostro= dynamic_cast<Mostro*>(modello->popFirstAttuali());
        Mostro* sacrificato= dynamic_cast<Mostro*>(modello->popFirstAttuali());
        if(modello->getSizeAttuali()==0 && mostro && sacrificato){
            mostro->sacrificio(sacrificato);
            ris.push_back(pair<Oggetto*, QPixmap>(mostro, getPixmap(mostro)));
        }
        else{
            throw EccezioneGestione("Errore! Ad un mostro può essere offerto in sacrificio un solo mostro");

        }
    }
    else if(getFlag("lucida")){
         Pietra* pietra= dynamic_cast<Pietra*>(modello->popFirstAttuali());
         if(pietra){
             if(modello->getSizeAttuali()==0){
                     pietra->lucida();
                     ris.push_back(pair<Oggetto*, QPixmap>(pietra, getPixmap(pietra)));
                 }
             else if(modello->getSizeAttuali()==1){
                 Pozione* pozione= dynamic_cast<Pozione*>(modello->popFirstAttuali());
                 if(pozione){
                     pietra->lucida(pozione);
                     ris.push_back(pair<Oggetto*, QPixmap>(pietra, getPixmap(pietra)));
                 }
                 else{
                     throw EccezioneGestione("Pozione non trovata, se una pietra deve essere lucidata con qualcosa, questo qualcosa deve essere una pozione");
                 }
             }
             else{
                 throw EccezioneGestione("Errore troppi oggetti: una pietra può essere lucidata con al massimo una pozione");
             }
         }
         else{
             throw EccezioneGestione("Errore, solo una PIETRA o una MEGAPIETRA possono essere lucidate");
         }
    }
    else if(getFlag("raffina")){
        Pietra* pietra = dynamic_cast<Pietra*>(modello->popFirstAttuali());

        if (pietra){
            if (modello->getSizeAttuali()==0){ //vuol dire che c'è solo una pietra
                MegaPietra* mp = pietra->raffina();
                ris.push_back(pair<Oggetto*,QPixmap>(mp,QPixmap(":/Icons/megapietra.png")));
            }
            else if (modello->getSizeAttuali()==1){
                Ambiente* amb1 = dynamic_cast<Ambiente*>(modello->popFirstAttuali());
                if (amb1){
                    MegaPietra* mp = pietra->raffina(amb1);
                    ris.push_back(pair<Oggetto*,QPixmap>(mp,QPixmap(":/Icons/megapietra.png")));
                }
                else{
                    throw EccezioneGestione("Ambiente non trovato, se una pietra deve essere lucidata con qualcosa, questo qualcosa deve essere un ambiente");
                }
            }
            else{
                throw EccezioneGestione("Errore troppi oggetti: una pietra può essere raffinata con al massimo un ambiente");
            }
        }
        else{
            throw EccezioneGestione("Errore! Puoi raffinare soltanto una pietra");
        }

    }
    else if(getFlag("frammenta")){
        //Revitalizzante* frammenta()
        MegaPietra* mp = dynamic_cast<MegaPietra*>(modello->popFirstAttuali());
        if (modello->getSizeAttuali()==0 && mp){
            Revitalizzante* rev = mp->frammenta();
            ris.push_back(pair<Oggetto*,QPixmap>(rev,QPixmap(":/Icons/revitalizzante.png")));

        }
        else{
            throw EccezioneGestione("Errore! Si può frammentare soltanto una megapietra");
        }

    }
    else if(getFlag("esegui")){
        Mostro* mostro= dynamic_cast<Mostro*>(modello->popFirstAttuali());
        if(mostro){
            if(mostro->getSaluteAttuale()==0)
                throw EccezioneGestione("il mostro è debilitato e quindi non è in grado di eseguire mosse");
            Mossa* mossa= dynamic_cast<Mossa*>(modello->popFirstAttuali());
            if(mossa){
                int j=getSizeAttuali();
                int ambientiCont=0; //conta quanti ambienti sono stati trovati
                Ambiente* ambiente=nullptr;
                vector<Mostro*> bersagli;

                for(int i=0; i<j; i++){
                    Oggetto* ber= dynamic_cast<Oggetto*>(modello->popFirstAttuali());
                    if(dynamic_cast<Mostro*>(ber)){
                        bersagli.push_back(static_cast<Mostro*>(ber));
                    }
                    else if(dynamic_cast<Ambiente*>(ber)){
                        if(ambientiCont==0){
                            ambiente=static_cast<Ambiente*>(ber);
                            ambientiCont++;
                        }
                        else{
                            throw EccezioneGestione("trovati due ambienti, solo un ambiente è permesso");
                        }
                    }
                    else{
                        throw EccezioneGestione("trovato un non mostro e non ambiente tra i bersagli");
                    }

                }

                if(ambiente){
                   mossa->esegui(mostro, bersagli, ambiente);
                }
                else{
                    mossa->esegui(mostro, bersagli);
                }
                ris.push_back(pair<Oggetto*, QPixmap>(mostro, getPixmap(mostro)));
                for(unsigned int i=0; i<bersagli.size(); i++){
                    ris.push_back(pair<Oggetto*, QPixmap>(bersagli[i], getPixmap(bersagli[i])));
                }
              }//chiede mossa
            else{
                throw EccezioneGestione("Errore! Solo un mostro può eseguire una mossa");
            }
        }//chiude mostro
        else{
            throw EccezioneGestione("solo un mostro può eseguire una mossa");

        }
    }//chiude esegui
    else if(getFlag("inverti")){
        Ambiente* amb1 = dynamic_cast<Ambiente*>(modello->popFirstAttuali());

        if (modello->getSizeAttuali()==0 && amb1){
            //inverti side effect su amb1
            amb1->inverti();
            ris.push_back(pair<Oggetto*,QPixmap>(amb1,getPixmap(amb1)));
        }
        else{
            throw EccezioneGestione("Errore! Si possono invertire le statistiche solo di un ambiente");
        }

    }
    else if(getFlag("fusione")){
        Oggetto* oggetto1 = modello->popFirstAttuali();
        Oggetto* oggetto2 = modello->popFirstAttuali();


        if (modello->getSizeAttuali() == 0 && dynamic_cast<Mostro*>(oggetto1) && dynamic_cast<Mostro*>(oggetto2)){
            Mostro* risultato = static_cast<Mostro*>(oggetto1)->fusione(static_cast<Mostro*>(oggetto2));
            ris.push_back(pair<Oggetto*,QPixmap>(risultato,QPixmap(":/Icons/fusione"+QString::number(randomBetween(1,4))) ));
        }
        else if(modello->getSizeAttuali() == 0 && dynamic_cast<Ambiente*>(oggetto1) && dynamic_cast<Ambiente*>(oggetto2)){
            Ambiente* risultato = static_cast<Ambiente*>(oggetto1)->fusione(static_cast<Ambiente*>(oggetto2));
            ris.push_back(pair<Oggetto*,QPixmap>(risultato,getPixmap(oggetto1)));
        }
        else{
            throw EccezioneGestione("devono essere fusi assieme DUE MOSTRI o AMBIENTI");
        }


    }
    else{
        //non c'è nessuna operazione scelta e quindi aggiungiamo ai risultati gli oggetti di attuali
        while(modello->getSizeAttuali()!=0){
            Oggetto* aux = modello->popFirstAttuali();
            ris.push_back(pair<Oggetto*,QPixmap>(aux,getPixmap(aux)));
        }
   }
   return ris;

}





