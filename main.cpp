#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "puolue.h"
#include "piiri.h"
#include "ehdokas.h"

using namespace std;
using otecpp_ht_puolue::Puolue;
using otecpp_ht_piiri::Vaalipiiri;
using otecpp_ht_ehdokas::Ehdokas;

/*
Poistetaan annetun merkkijonon alusta ja lopusta mahdollinen valilyonti.
Muutokset tehdaan suoraan annettuun merkkijonoon.
*/
void poistaValit(string &sana) {
    if(sana[0] == ' ') { // Jos alussa vali, poistetaan.
        sana.erase(0, 1);
    }
    if(sana[sana.length() - 1] == ' ') { // Jos lopussa vali, poistetaan
        sana.erase(sana.length() - 1, 1);
    }
}

// Aakkostaa puolueet nimen mukaan.
bool puolueVrt(const Puolue &a, const Puolue &b) {
    if(a.getNimi() < b.getNimi()) {
        return true;
    }
    else {
        return false;
    }
}
// Aakkostaa vaalipiirit nimen mukaan.
bool piiriVrt(const Vaalipiiri &a, const Vaalipiiri &b) {
    if(a.getNimi() < b.getNimi()) {
        return true;
    }
    else {
        return false;
    }
}

// Aakkostaa ehdokkaat nimen mukaan.
bool eNimiVrt(const Ehdokas &a, const Ehdokas &b) {
    if(a.getNimi() < b.getNimi()) {
        return true;
    }
    else {
        return false;
    }
}
// Aakkostaa ehdokkaat ensisijaisesti puolueen, sen jälkeen nimen mukaan.
bool ePuolueVrt(const Ehdokas &a, const Ehdokas &b) {
    if(a.getPuolue() < b.getPuolue()) {
        return true;
    }
    else if(a.getPuolue() == b.getPuolue()) {
        if(a.getNimi() < b.getNimi()) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}
// Aakkostaa puolueet ensisijaisesti vaalipiirin, sitten puolueen ja lopulta nimen mukaan.
bool ePiiriVrt(const Ehdokas &a, const Ehdokas &b) {
    if(a.getVaalipiiri() < b.getVaalipiiri()) {
        return true;
    }
    else if(a.getVaalipiiri() == b.getVaalipiiri()) {
        if(a.getPuolue() < b.getPuolue()) {
            return true;
        }
        else if(a.getPuolue() == b.getPuolue()) {
            if(a.getNimi() < b.getNimi()) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

// Jarjestaa laskevaan jarjestykseen aanien mukaan.
bool aaniVrt(const Ehdokas &a, const Ehdokas &b) {
    if(a.getAanet() > b.getAanet()) {
        return true;
    }
    else {
        return false;
    }
}
// Jarjestaa laskevaan jarjestykseen viertauslukujen mukaan.
bool vrtLukuVrt(const Ehdokas &a, const Ehdokas &b) {
    if(a.getVrtLuku() > b.getVrtLuku()) {
        return true;
    }
    else {
        return false;
    }
}

/*
Luetaan vakiosisaantulosta komentoja, kunnes saadaan "lopeta".
Lisätään vaalipiireja, puolueita ja ehdokkaita, tulostetaan niiden tietoja sekä lasketaan vaalitulos.
*/
int main() {
    // Taulut, joihin puolueet, piirit ja ehdokkaat tallennetaan.
    vector<Puolue> puolueet;
    vector<Vaalipiiri> piirit;
    vector<Ehdokas> ehdokkaat;

    bool laskettu = false; // Kertoo, onko tulos vielä laskettu.

    string rivi = "";
    string komento = "";

    string nimi;
    string lkm;
    string puolue;
    string piiri;
    string aanet;

    // Jatketaan syötteen lukemista, kunnes saadaan kasky "lopeta".
    while(1) {
        getline(cin, rivi);
        if(rivi == "lopeta") {
            break;
        }
        else if(rivi == "laskeTulos") { // Lasketaan tulos D'Hondtin menetelmalla.
            // Jarjestetaan vaalipiirit ja puolueet aakkosittain.
            sort(piirit.begin(), piirit.end(), piiriVrt);
            sort(puolueet.begin(), puolueet.end(), puolueVrt);
            // Jarjestetaan ehdokkaat ensisijaisesti piirien, sitten puolueiden ja lopulta nimien perusteella.
            sort(ehdokkaat.begin(), ehdokkaat.end(), ePiiriVrt);

            // Alustetaan jokaisen puolueen valittujen maara aluksi nollaan.
            for(unsigned int i = 0; i < puolueet.size(); ++i) {
                puolueet[i].setLkm(puolueet[i].getLkm() + 1);
            }

            unsigned int e = 0; // Ehdokaslaskuri.
            for(unsigned int v = 0; v < piirit.size(); ++v) { // Kaydaan lapi kaikki vaalipiirit.
                unsigned int e_1 = e; // Muistetaan vaalipiirin ensimmaisen ehdokkaan indeksi.
                for(unsigned int p = 0; p < puolueet.size(); ++p) { // Kaydaan lapi kaikki puolueet.
                    unsigned int e_2 = e; // Muistetaan puolueen ensimmaisen ehdokkaan indeksi.
                    int kokAanet = 0;

                    // Kaydaan lapi kaikki kyseiseen vaalipiiriin ja puolueeseen kuuluvat ehdokkaat.
                    while(ehdokkaat[e].getVaalipiiri() == piirit[v].getNimi() && ehdokkaat[e].getPuolue() == puolueet[p].getNimi()) {
                        kokAanet += ehdokkaat[e].getAanet(); // Lisataan ehdokkaan aanet puolueen kokonaisaaniin.
                        ++e;
                        // Viimeisen ehdokkaan kohdalla ei enää tutkita whilen ehtoa.
                        if(e == ehdokkaat.size()) {
                            break;
                        }
                    }

                    // Jos ehdokkaita on ainakin kaksi, jarjestetaan ne saatujen aanien mukaan.
                    if(e-e_2 > 1) {
                        sort(ehdokkaat.begin()+e_2, ehdokkaat.begin()+e, aaniVrt);
                    }

                    // Lasketaan ehdokkaille vertausluvut.
                    for(unsigned int i = 0; i < e-e_2; ++i) {
                        ehdokkaat[e_2+i].setVrtLuku(kokAanet/(i+1));
                    }
                }

                // Jarjestetaan ehdokkaat vertailuluvun mukaan.
                sort(ehdokkaat.begin()+e_1, ehdokkaat.begin()+e, vrtLukuVrt);
                // Valitaan ensimmaiset lkm edustajaa, missa lkm on vaalipiirista valittavien ehdokkaiden maara.
                for(unsigned int j = 0; j < piirit[v].getLkm(); ++j) {
                    ehdokkaat[e_1+j].setValittu(true);
                    // Etsitaan ehdokkaan puolue ja lisataan valittujen maaraa yhdella.
                    for(unsigned int k = 0; k < puolueet.size(); ++k) {
                        if(ehdokkaat[e_1+j].getPuolue() == puolueet[k].getNimi()) {
                            puolueet[k].setLkm(puolueet[k].getLkm() + 1);
                        }
                    }
                }
            }

            laskettu = true;
        }
        // Monisanainen kasky.
        else {
            // Luetaan komento, eli valilyontiin asti.
            istringstream ss(rivi);
            getline(ss, komento, ' ');

            // Vain yksi parametri, joten sitä ei tarvitse siistia.
            if(komento == "lisaaPuolue") {
                getline(ss, nimi);
                puolueet.push_back(Puolue(nimi));
            }

            // Useampi parametri erotettuna /-merkilla ja valilyonneilla, joten siivottava valilyonnit pois.
            else if(komento == "lisaaVaalipiiri") {
                getline(ss, nimi, '/');
                poistaValit(nimi);

                getline(ss, lkm);
                poistaValit(lkm);
                // Jos samanniminen vaalipiiri loytyy jo, paivitetaan vain sen tiedot.
                bool l = false;
                for(unsigned int i = 0; i < piirit.size(); ++i) {
                    if(nimi == piirit[i].getNimi()) {
                        piirit[i].paivita(atoi(lkm.c_str()));
                        l = true;
                    }
                }
                // Jos ei loytynyt, luodaan uusi vaalipiiri.
                if(!l) {
                    piirit.push_back(Vaalipiiri(nimi, atoi(lkm.c_str())));
                }
            }

            // Jalleen siivottava valimerkit pois.
            else if(komento == "lisaaEhdokas") {
                getline(ss, nimi, '/');
                poistaValit(nimi);

                getline(ss, puolue, '/');
                poistaValit(puolue);

                getline(ss, piiri, '/');
                poistaValit(piiri);

                getline(ss, aanet);
                poistaValit(aanet);

                ehdokkaat.push_back(Ehdokas(nimi, puolue, piiri, atoi(aanet.c_str())));
            }

            else if(komento == "puolueet") {
                cout << "Puolueet:" << endl;
                // Seka puolueet etta ehdokkaat tulostetaan nimen mukaisessa aakkosjarjestyksessa.
                sort(puolueet.begin(), puolueet.end(), puolueVrt);
                sort(ehdokkaat.begin(), ehdokkaat.end(), eNimiVrt);

                for(unsigned int i = 0; i < puolueet.size(); ++i) {
                    cout << puolueet[i];
                    // Jos tulos on laskettu, tulostetaan puolueen valitut ehdokkaat.
                    if(laskettu) {
                        for(unsigned int j = 0; j < ehdokkaat.size(); ++j) {
                            if(ehdokkaat[j].getPuolue() == puolueet[i].getNimi() && ehdokkaat[j].getValittu()) {
                                cout << "  " << ehdokkaat[j].getNimi() << " " << ehdokkaat[j].getVaalipiiri()
                                    << " " << ehdokkaat[j].getAanet() << endl;
                            }
                        }
                    }
                }
            }

            else if(komento == "vaalipiirit") {
                cout << "Vaalipiirit:" << endl;
                // Piirit tulostetaan nimen mukaisessa aakkosjarjestyksessa, ehdokkaat ensisijaisesti puolueen ja sitten nimen mukaisessa.
                sort(piirit.begin(), piirit.end(), piiriVrt);
                sort(ehdokkaat.begin(), ehdokkaat.end(), ePuolueVrt);
                for(unsigned int i = 0; i < piirit.size(); ++i) {
                    cout << piirit[i];
                    // Jos tulos on laskettu, tulostetaan vaalipiirin valitut ehdokkaat.
                    if(laskettu) {
                        for(unsigned int j = 0; j < ehdokkaat.size(); ++j) {
                            if(ehdokkaat[j].getVaalipiiri() == piirit[i].getNimi() && ehdokkaat[j].getValittu()) {
                                cout << "  " << ehdokkaat[j].getNimi() << " " << ehdokkaat[j].getPuolue()
                                    << " " << ehdokkaat[j].getAanet() << endl;
                            }
                        }
                    }
                }
            }

            else if(komento == "ehdokkaat") {
                cout << "Ehdokkaat:" << endl;
                // Tulostetaan ehdokkaat ensisijaisesti vaalipiirin, sittwn puolueen ja lopulta nimen mukaisessa aakkosjärjestyksessa.
                sort(ehdokkaat.begin(), ehdokkaat.end(), ePiiriVrt);
                for(unsigned int i = 0; i < ehdokkaat.size(); ++i) {
                    cout << ehdokkaat[i];
                    // Valituille ehdokkaille tulostetaan siitä tieto.
                    if(laskettu && ehdokkaat[i].getValittu()) {
                        cout << " (valittu)";
                    }
                    cout << endl;
                }
            }
        }
    }
}

