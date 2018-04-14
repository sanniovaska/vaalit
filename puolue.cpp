#include <string>
#include <iostream>
#include "puolue.h"

using namespace std;

namespace otecpp_ht_puolue {
    /*
    Tulostaa puolueen nimen ja, jos tulos on laskettu, valittujen ehdokkaiden maaran.
    */
    ostream & operator<<(ostream &out, const Puolue &p) {
        out << p.nimi;
        if(p.lkm < 0) {
            out << endl;
        }
        else {
            out << " (" << p.lkm << ")" << endl;
        }
        return out;
    }
}

