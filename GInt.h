

#include <cstdint>
#include <string>

class GInt {
private:
    uint32_t * p_uint;
    uint32_t taille;
public:
    GInt(const uint32_t tailletab){
        taille = tailletab;
        p_uint = new uint32_t[taille];
        for(uint32_t i =0;i<taille;i++){
            p_uint[i] = 0;
        }
    }

    GInt(std::string nombre);
    GInt(){
        taille = 0;
        p_uint = nullptr;
    }
    GInt(const GInt &copie);


    GInt & operator=(const GInt &copie);

    GInt Addition(const GInt &add);
    GInt Multiplication(GInt &add);
    GInt SoustraitUn();

    GInt Soustrait(const GInt &add);

    // Juste pour les test :
    void setp_int(uint32_t * p_int){
        p_uint = p_int;
    }
    void settaille(uint32_t t){
        taille = t;
    }

    uint32_t* getp_int(){
        return p_uint;
    }
    uint32_t gettaille(){
        return taille;
    }

    static GInt max(GInt &a,GInt &b){
        return a.p_uint[a.taille-1]>b.p_uint[b.taille-1]?a:b;
    }

    ~GInt(){
        delete [] p_uint;
    }


    GInt &Egal(GInt copie);

    GInt Div10(); // Affiche reste retourne quotient

    bool EstNul();
    bool operator>(const GInt &copie);

};