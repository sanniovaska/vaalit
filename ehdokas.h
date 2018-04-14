#include <string>
#include <iostream>

#ifndef OTECPP_HT_EHDOKAS_H
#define OTECPP_HT_EHDOKAS_H

namespace otecpp_ht_ehdokas {
    class Ehdokas {
        std::string nimi;
        std::string puolue;
        std::string vaalipiiri;
        int aanet; // Ehdokkaan saamat aanet.
        int vrtLuku; // Laskettu vertailuluku.
        bool valittu; // Valittu vai ei, oletuksena false.
    public:
        std::string getNimi() const { return nimi; }
        void setNimi(std::string n) { nimi = n; }

        std::string getPuolue() const { return puolue; }
        void setPuolue(std::string p) { puolue = p; }

        std::string getVaalipiiri() const { return vaalipiiri; }
        void setVaalipiiri(std::string v) { vaalipiiri = v; }

        int getAanet() const { return aanet; }
        void setAanet(int a) { aanet = a; }

        int getVrtLuku() const { return vrtLuku; }
        void setVrtLuku(int v) { vrtLuku = v; }

        bool getValittu() const { return valittu; }
        void setValittu(bool v) { valittu = v; }

        Ehdokas(std::string n, std::string p, std::string v, int a)
            : nimi(n), puolue(p), vaalipiiri(v), aanet(a), valittu(false) {
        }

        friend std::ostream & operator<<(std::ostream &out, const Ehdokas &e);
        };
}

#endif


