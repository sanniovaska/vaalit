#include <string>
#include <iostream>

#ifndef OTECPP_HT_PIIRI_H
#define OTECPP_HT_PIIRI_H

namespace otecpp_ht_piiri {
    class Vaalipiiri {
        std::string nimi;
        unsigned int lkm; // Valittavien ehdokkaiden m‰‰r‰.
    public:
        std::string getNimi() const { return nimi; }
        void setNimi(std::string n) { nimi = n; }

        unsigned int getLkm() const { return lkm; }
        void setLkm(unsigned int l) { lkm = l; }

        Vaalipiiri(std::string n, unsigned int l) : nimi(n), lkm(l) {
        }

        void paivita(unsigned int l); // Paivittaa vaalipiirille uuden lkm.

        friend std::ostream & operator<<(std::ostream &out, const Vaalipiiri &v);
    };
}

#endif

