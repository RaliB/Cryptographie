#include "GInt.h"
#include <math.h>
#include <iostream>
#include <algorithm>


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

/*
GInt GInt::Multiplication(GInt &add);
GInt& GInt::Egal(GInt &add);*/
