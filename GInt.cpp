
#include "GInt.h"
#include <math.h>
#include <iostream>



GInt::GInt(const GInt &copie){
    if(copie.p_uint[copie.taille-1]==0){
        taille = copie.taille - 1;

    }
    else{
        taille = copie.taille;
    }

    p_uint = new uint32_t[taille];
    for(uint32_t i=0;i<taille;i++){
        p_uint[i] = copie.p_uint[i];
    }
}


GInt & GInt::operator=(const GInt &copie) {
    delete[] this->p_uint;

    if(copie.p_uint[copie.taille-1]==0){
        taille = copie.taille - 1;

    }
    else{
        taille = copie.taille;
    }
    p_uint = new uint32_t[taille];
    for(uint32_t i =0;i<taille;i++){
        p_uint[i] = copie.p_uint[i];
    }
    return *this;
}



GInt GInt::Addition(const GInt &add){
    long long int s1,s2,c,addition;
    uint32_t a = 0;
    long long int max =(long long int) (a-1); // max unsigned int
    int taillefin;

    c=0;
    taillefin = fmax(taille,add.taille) +1;
    GInt final(taillefin);

    for(int i =0;i<taillefin;i++){
        s1 = i<taille?p_uint[i]:0; // Si on i < taille alors on prend la valeur dans le tableau sinon 0, on peut donc add deux nombre de taille differente
        s2 = i<add.taille?add.p_uint[i]:0;

        addition = s1+s2+c;

        c= addition<max ? 0 :1;

        addition = addition>max?addition-(max + 1):addition;

        final.p_uint[i] = addition;
    }


    final.p_uint[taillefin-1] = addition;


    return final;
}
GInt GInt::SoustraitUn(){
    GInt add(1);

    add.p_uint[0] = 1;

    return Soustrait(add);
}

GInt GInt::Soustrait(const GInt &add) {// On suppose que this > add
    long long int s1,s2,c,c1;
    uint32_t addition;

    uint32_t a = 0;
    long long int max =(long long int) (a-1); // max unsigned int
    c=0;
    GInt final(taille);

    for(int i =0;i<taille;i++){
        s1 = p_uint[i]; // Si on i < taille alors on prend la valeur dans le tableau sinon 0, on peut donc add deux nombre de taille differente
        s2 = i<add.taille?add.p_uint[i]:0;
        c1=c;
        c= s1>=(s2+c1)?0:1;
        addition = s1-s2 -c1 + c*(max+1);
        final.p_uint[i] = addition;
    }


    return final;
}


/*
GInt GInt::Multiplication(GInt &add);
GInt& GInt::Egal(GInt &add);*/