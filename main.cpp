#include <iostream>
#include "GInt.h"

int main(){
    GInt a(1),b(1),c;

    a.getp_int()[0] = 5;
    b.getp_int()[0] = 5;

    c = a.Addition(b);

    for(uint32_t i = 0;i<c.gettaille();i++){
        std::cout<<c.getp_int()[i]<<std::endl;
    }

    return 0;
}

