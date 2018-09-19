#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <map>

#ifndef FUNZIONI_H
#define FUNZIONI_H

//template per la stampa di vettori
template <class T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v){
    for(unsigned int i=0; i<v.size(); i++){
        os<<v[i]<<" ";
    }
    return os;
}


//template che ritorna true se un elemento è presente in un vector
template <class T>
bool inVector(std::vector<T> v, T val){
    for (unsigned int i=0; i<v.size(); i++){
        if(val==v[i])
            return true;
    }
    return false;
}


//template che ritorna true se un elemento è contenuto in una map
template <class T, class V>
bool inMap(std::map<T,V> v, T key){
    return (v.find(key)!=v.end())? true:false;
}


//ritorna i valori comuni tra due vettori, PRE: i vettori non contengono doppioni
template <class T>
std::vector<T> getComuni(std::vector<T> v1, std::vector<T> v2){
    std::vector<T> ris;
    for(unsigned int i=0;i<v1.size(); i++){
       if(inVector((v2), v1[i]))
           ris.push_back(v1[i]);
    }
    return ris;
}


//funzione che ritorna un numero random tra min e max, estremi inclusi
int randomBetween(int min, int max);


//funzione che controlla se un valore rientra nei limiti, se esce torna minimo o massimo a seconda di dove "esce"
int checkBounds(int min, int max, int val);

#endif // FUNZIONI_H
