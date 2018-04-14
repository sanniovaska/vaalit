#include <string>
#include <iostream>

#ifndef OTECPP_HT_PUOLUE_H
#define OTECPP_HT_PUOLUE_H

namespace otecpp_ht_puolue {
    class Puolue {
        std::string nimi;
        int lkm; // valittujen ehdokkaiden m‰‰r‰, negatiivinen jos tulosta ei viel‰ laskettu
    public:
        std::string getNimi() const { return nimi; }
        void setNimi(std::string n) { nimi = n; }

        int getLkm() const { return lkm; }
        void setLkm(int l) { lkm = l; }

        Puolue(std::string n) : nimi(n), lkm(-1) {
        }

        friend std::ostream & operator<<(std::ostream &out, const Puolue &p);
    };
}

#endif

