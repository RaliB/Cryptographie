#include "GInt.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <bitset>


GInt::GInt(std::string nombre){
    std::reverse(nombre.begin(),nombre.end());

    std::string b;
    int i = 0;
    GInt base(1);
    GInt base2(1);

    base.p_uint[0] = 1000000000;//10^9


    base2.p_uint[0] =  1;

    taille = floor(nombre.length()*log(10)/(32*log(2)) )+ 1;
    p_uint = new unsigned int[taille];
    p_uint[0] = 0;

    GInt ret(taille);

    while((i+1)*9<nombre.length()){
        GInt a(1);
        //for(int j = 0;j<9;j++){
        //    a.p_uint[0] += nombre[i*9 +j]*pow(10,9-j);
        //}

        b = nombre.substr(i*9,(i+1)*9);
        std::reverse(b.begin(),b.end());


        a.p_uint[0] = std::stoi(b);


        a = a.Multiplication(base2);
        ret = ret.Addition(a);


        base2 = base2.Multiplication(base);

        i++;
    };
    GInt c(1);
    //std::cout<<std::stoi(nombre.substr(i*9));

    //std::cout<<nombre.substr(i*9);


    b = nombre.substr(i*9);

    std::reverse(b.begin(),b.end());

    c.p_uint[0] = std::stoi(b);
    c = c.Multiplication(base2);


    ret = ret.Addition(c);

    for(unsigned int i=0;i<taille;i++){
        p_uint[i] = ret.p_uint[i];
    }
}


GInt::GInt(const GInt &copie){
    if(copie.taille == 0){
        p_uint = nullptr;
        taille = 0;
    }
    else{

        if(copie.p_uint[copie.taille-1]==0){ //si dernier élèment=0 j'enleve cet élèment
            taille = copie.taille - 1;

        }
        else{
            taille = copie.taille;
        }

        p_uint = new unsigned int[taille];
        for(unsigned int i=0;i<taille;i++){
            p_uint[i] = copie.p_uint[i];
        }
    }
}



GInt & GInt::operator=(const GInt &copie) {
    delete[] this->p_uint; //pr sup ce qu'il y avait avt

    if(copie.taille == 0){
        p_uint = nullptr;
        taille= 0;
    }
    else{
        if(copie.p_uint[copie.taille-1]==0){
            taille = copie.taille - 1;

        }
        else{
            taille = copie.taille;
        }
        p_uint = new unsigned int[taille];
        for(unsigned int i =0;i<taille;i++){
            p_uint[i] = copie.p_uint[i];
        }

    }
    return *this;
}



// On travail en modulo 2^32
GInt GInt::Addition(const GInt &add){
    long long int s1,s2,c,addition; //long long int-->2^63-1
    unsigned int a = 0;
    a= a-1; // a= 2^32 - 1
    long long int max =(long long int) a;//la je fais un cast // max unsigned int
    int taillefin;

    c=0;
    taillefin = fmax(taille,add.taille) +1; //fonction fmax pr déterminer qui est le + grd, ici je raj une case au cas ou le nv nbr est + grd que le + grd des 2 nbrs.
    GInt final(taillefin);

    for(int i =0;i<taillefin;i++){
        s1 = i<taille?p_uint[i]:0; // Si on a i < taille alors on prend la valeur dans le tableau sinon 0, on peut donc add deux nombre de taille differente
        s2 = i<add.taille?add.p_uint[i]:0;

        addition = s1+s2+c; //j'ajoute valeur de la case du 1er tab à celui du 2ème et j'ajoute retenue

        c= addition>max ? 1 :0; // avec max= 2^32 - 1, si dépassement c= 1

        addition = addition>max?addition-(max + 1):addition; // je fais additions mod 2^32

        final.p_uint[i] = addition;
    }

    return final;
}

GInt GInt::Multiplication(GInt &b){
    {
        unsigned long long int produit;
        unsigned int c;
        unsigned int r;

        GInt temp;
        uint32_t m = 0;
        long long int max =(long long int) (m-1); // max unsigned int

        for (unsigned int i=0;i<taille;i++)
        {
            for(unsigned int j=0;j<b.taille;j++){
                GInt a(i+j+2);
                produit = (unsigned long long int) p_uint[i]*(unsigned long long int)b.p_uint[j]; // unsigned long long int -> unsigned int
                r= produit % (max+1);
                produit -= r;
                c = produit / (max+1);

                a.p_uint[i+j+1] = c;
                a.p_uint[i+j] = r;

                for(unsigned int k = 0;k<i+j;k++){ //la on fait 0 0 0 0 0 0 0 0 R C
                    a.p_uint[k] = 0;
                }

                temp=temp.Addition(a);
            }
        }
        return temp;
    }
}


GInt GInt::Soustrait(const GInt &add) {// On suppose que this > add
    long long int s1,s2,c,c1;
    unsigned int addition;

    unsigned int a = 0;
    long long int max =(long long int) (a-1); // max unsigned int
    c=0;
    GInt final(taille); //si je fais c=a-b, le "taille" corresp à la taille de c et de a

    for(int i =0;i<taille;i++){
        s1 = p_uint[i];
        s2 = i<add.taille?add.p_uint[i]:0;
        c1=c;
        c= s1>=(s2+c1)?0:1; //si s1 inf à s2 je prend une retenue c=1
        addition = s1-s2 -c1 + c*(max+1);// si addit° négative je fais + la base (2^32)
        //ex: add= 1 0 - 0 1 + c*10 donc add= -1 + 10=9 (c=1 si s1<s2)
        final.p_uint[i] = addition;
    }


    return final;
}

GInt GInt::SoustraitUn(){
    GInt add(1); //je crée un GInt de taille 1

    add.p_uint[0] = 1;

    return Soustrait(add); // la c'est *this.Soustrait(add);
}



GInt GInt::Div10() {
    long long int a;
    uint32_t b = 0;
    GInt q1(3);
    GInt q2(3);
    GInt q3(2);
    GInt Quotient(taille);
    long long int max = (long long int) (b-1); // r - 1
    q3.p_uint[1] = 10; // Bt−1 * r

    while(p_uint[taille-1] >= 10){// Tant que A > B * r ^(n-1)
        Quotient.p_uint[taille-1] = Quotient.p_uint[taille-1] +1;
        p_uint[taille-1] = p_uint[taille-1] - 10;
    }
    for(uint32_t i = taille-1;i>0;i--){
        if(p_uint[i] == 10){
            Quotient.p_uint[i-1] = max;
        }
        else{
            Quotient.p_uint[i-1] = floor(((long long int)p_uint[i]*(max+1) + p_uint[i-1])/(10));
        }
        q2.p_uint[0] = i>2?p_uint[i-2]:0;
        q2.p_uint[1] = p_uint[i-1];
        q2.p_uint[2] = p_uint[i];
        q1.p_uint[0] = Quotient.p_uint[i-1];
        q1 = q1.Multiplication(q3);
        while(q1>q2){
            Quotient.p_uint[i-1] = Quotient.p_uint[i-1] -1;
            q1.p_uint[0] = Quotient.p_uint[i-1];
            q1 = q1.Multiplication(q3);
        }
        GInt q4(i-1);
        q4.p_uint[i-2] = 1;
        q1 = q1.Multiplication(q4);

        (*this) = this->Soustrait(q1);

    }
    std::cout<<p_uint[0]<<std::endl;
    (*this) = Quotient;
    return (*this);

}



bool GInt::EstNul() {
    bool nul = true;
    for(uint32_t i =0;i < taille;i++){
        if(p_uint[taille-i] != 0){
            nul = false;
            break;
        }
    }
    return nul;
}


bool GInt::operator>(const GInt &copie) {
    bool retour = false;

    if(taille > copie.taille){
        retour = true;
    }
    else if(taille < copie.taille){
            retour = false;
    }
    else{
        for(uint32_t i = taille-1;i>0;i--){
            if(p_uint[i]>copie.p_uint[i]){
                retour = true;
                break;
            }
            else if(p_uint[i]<copie.p_uint[i]){
                retour = false;
                break;
            }
        }
    }

    return retour;
}


/*
GInt GInt::Multiplication(GInt &add);
GInt& GInt::Egal(GInt &add);*/
