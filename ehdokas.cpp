#include <string>
#include <iostream>
#include "ehdokas.h"

using namespace std;

namespace otecpp_ht_ehdokas {
    /*
    Tulostaa ehdokkaan tiedot.
    */
    ostream & operator<<(ostream &out, const Ehdokas &e) {
        out << e.nimi << " " << e.puolue << " " << e.vaalipiiri << " " << e.aanet;
        return out;
    }
}

