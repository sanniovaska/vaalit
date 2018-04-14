#include <string>
#include <iostream>
#include "piiri.h"

using namespace std;

namespace otecpp_ht_piiri {
    /*
    Paivittaa vaalipiirille uuden lkm.
    */
    void Vaalipiiri::paivita(unsigned int l){
        this->lkm = l;
    }

    /*
    Tulostaa vaalipiirin nimen ja valittavien edustajien maaran.
    */
    ostream & operator<<(ostream &out, const Vaalipiiri &v) {
        out << v.nimi << " (" << v.lkm;
        if(v.lkm == 1) {
            out << " edustaja)" << endl;
        }
        else {
            out << " edustajaa)" << endl;
        }
        return out;
    }
}

