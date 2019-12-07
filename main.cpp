#include <iostream>
#include "GInt.h"

int main(){
    uint32_t a = 0;
    a = a-1;

    GInt c("144111111567813");
    GInt d("4");
    std::cout<<std::endl;
    /*c.getp_int()[0] = a;
    c.getp_int()[0] = c.getp_int()[0] >> 4;
    c.getp_int()[0] =  c.getp_int()[0] << 4;
    std::cout << a- c.getp_int()[0];// Ascii peut se faire comme ça, on fait un GInt et tous les 7 bits = un carac ascii
   */
    c.Div10();
    /*
    while(c.getp_int()[0] != 0 && c.gettaille() != 0){
        c.Div10();
    }*/

    return 0;
}

