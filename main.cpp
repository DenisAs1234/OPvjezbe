#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QFont>
#include <QPen>
#include <QResizeEvent>
#include <QSize>
#include <QTimer>
#include <thread>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

class Karta
{
public:
    int broj;
    int zog;
    string staza;
    int jacina;
    int vrijednost;
    int prioritet = 20;
    Karta() {};
    Karta(int b, int z)
    {
        broj = b; zog = z;
    }
    Karta(int b, int z, string s, int j, int v)
    {
        broj = b; zog = z; staza = s; jacina = j; vrijednost = v;
    }
};

class Spil;
class Igrac;

class KartaPravokutnik : public QGraphicsRectItem, public Karta
{
public:
    QGraphicsPixmapItem* slika;
    Igrac* igrac1;
    Igrac* igrac2;
    qreal orig_x = 0;
    qreal orig_y = 0;
    Spil* s;
    QGraphicsScene* scena;
    KartaPravokutnik(qreal x, qreal y, qreal width, qreal height, const QPixmap& pixmap, Igrac* i1, Igrac* i2,
        Spil* sp, QGraphicsScene* sc) : QGraphicsRectItem(x, y, width, height)
    {
        QPixmap skalirana_slika = pixmap.scaled(width, height, Qt::KeepAspectRatio,
            Qt::SmoothTransformation);
        slika = new QGraphicsPixmapItem(skalirana_slika, this);
        slika->setPos((width - skalirana_slika.width()) / 2,
            (height - skalirana_slika.height()) / 2);
        igrac1 = i1;
        igrac2 = i2;
        s = sp;
        scena = sc;
    }
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

class KartaPravokutnik;

class Igrac
{
public:
    vector<Karta*> ruka;
    bool potez;
    vector<vector<Karta*>> akuze;
    int broj_punata;
    QGraphicsTextItem* bodovi;
    QGraphicsTextItem* bele;
    KartaPravokutnik* odigrana_karta;
    vector<KartaPravokutnik*> pravokutnici;
    vector<vector<int>> status_karata{ {0,0,0},{0,0,0},{0,0,0},{0,0,0} };
    vector<int> najjace_karte{ 3,3,3,3 };
    int zeljeni_zog = -1;
    bool akuzanje = true;
    int broj_pobjeda = 0;
    QGraphicsTextItem* br_pobjeda;
    Igrac(bool p, int bp, QGraphicsTextItem* bod, QGraphicsTextItem* bel, QGraphicsTextItem* pobj)
    {
        potez = p; broj_punata = bp; bodovi = bod; bele = bel; br_pobjeda = pobj;
    }
    void DodajAkuzu(int broj, int zog);
    int akuze_racunala();
};

class Spil
{
public:
    Igrac* igrac1;
    Igrac* igrac2;
    vector<Karta*> spil;
    vector<KartaPravokutnik*> spil_prav;
    QGraphicsTextItem* broj_karata;
    void generirajSpil();
    void mijesanje_spila();
    void povuci_kartu(Igrac* igrac, Igrac* komp, QGraphicsScene* scena);
    Spil(Igrac* i1, Igrac* i2, vector<Karta*> sp, vector<KartaPravokutnik*> spprav, QGraphicsTextItem* br) 
    {
        igrac1 = i1; igrac2 = i2; spil = sp; spil_prav = spprav; broj_karata = br;
    }
};

static void resetiraj_svojstva(Igrac* i1, Igrac* i2)
{
    i1->broj_punata = 0;
    i2->broj_punata = 0;
    i1->bodovi->setPlainText("0");
    i1->bele->setPlainText("0/3");
    i2->bodovi->setPlainText("0");
    i2->bele->setPlainText("0/3");
    i1->akuze = {};
    i2->akuze = {};
    i2->status_karata = { {0,0,0},{0,0,0},{0,0,0},{0,0,0} };
    i2->najjace_karte = { 3,3,3,3 };
    i2->zeljeni_zog = -1;
    i1->akuzanje = true;
    i2->akuzanje = true;
}

static void azuriraj_bodove(Igrac* i, int dobiveni_bodovi)
{
    i->broj_punata += dobiveni_bodovi;
    int novi_bodovi = i->broj_punata / 3;
    int nove_bele = i->broj_punata % 3;
    i->bodovi->setPlainText(QString::number(novi_bodovi));
    i->bele->setPlainText(QString::number(nove_bele) + "/3");
}

static bool provjera_duplikata(vector<vector<Karta*>> akuze)
{
    int i, j, p;
    for (i = 0; i < akuze.size() - 1; i++)
    {
        p = 0;
        cout << "ZADNJA AKUZA: [ ";
        for (j = 0; j < akuze.at(akuze.size() - 1).size(); j++)
        {
            cout << "{" << akuze.at(akuze.size() - 1).at(j)->broj << "," <<
                akuze.at(akuze.size() - 1).at(j)->zog << "}";
        }
        cout << " ]" << endl;
        cout << "PRIJASNJA AKUZA: [ ";
        for (j = 0; j < akuze.at(i).size(); j++)
        {
            cout << "{" << akuze.at(i).at(j)->broj << "," <<
                akuze.at(i).at(j)->zog << "}";
        }
        cout << " ]" << endl;
        if (akuze.at(akuze.size() - 1).size() != (akuze.at(i).size()))
        {
            cout << "IF VELICINE AKUZA NISU ISTE" << endl;
            continue;
        }
        for (j = 0; j < akuze.at(i).size(); j++)
        {
            if (((akuze.at(akuze.size() - 1).at(j)->broj) != (akuze.at(i).at(j)->broj)) ||
                ((akuze.at(akuze.size() - 1).at(j)->zog) != (akuze.at(i).at(j)->zog)))
            {
                cout << "AKUZE NISU ISTE BREAK" << endl;
                p = 1;
                break;
            }
        }
        cout << "IZASAO IZ JOT PETLJE" << endl;
        if (!p)
        {
            cout << "RETURN FALSE" << endl;
            return false;
        }
    }
    cout << "RETURN TRUE" << endl;
    return true;
}

static void izbrisi_okvire(vector<KartaPravokutnik*> pravokutnici)
{
    int i;
    for (i = 0; i < pravokutnici.size(); i++)
    {
        pravokutnici.at(i)->setPen(Qt::NoPen);
    }
}

static void ispisi(vector<Karta*> v)
{
    int i;
    for (i = 0; i < v.size(); i++)
    {
        cout << "{" << v.at(i)->broj << ", " << v.at(i)->zog << ", " <<
            v.at(i)->staza << ", " << v.at(i)->jacina << ", " << v.at(i)->vrijednost
            << "}" << endl;
    }
}

static void sortiranje_karata(vector<Karta*>& ruka)
{
    int i, j;
    Karta* p;
    for (i = 0; i < ruka.size() - 1; i++)
    {
        for (j = i + 1; j < ruka.size(); j++)
        {
            if (ruka.at(j)->zog < ruka.at(i)->zog)
            {
                p = ruka.at(j);
                ruka.at(j) = ruka.at(i);
                ruka.at(i) = p;
            }
            else if (ruka.at(j)->zog == ruka.at(i)->zog)
            {
                if (ruka.at(j)->jacina > ruka.at(i)->jacina)
                {
                    p = ruka.at(j);
                    ruka.at(j) = ruka.at(i);
                    ruka.at(i) = p;
                }
            }
        }
    }
}

static void sortiranje_akuza(vector<Karta*>& akuza)
{
    int i, j;
    Karta* p;
    for (i = 0; i < akuza.size() - 1; i++)
    {
        for (j = i + 1; j < akuza.size(); j++)
        {
            if (akuza.at(j)->zog < akuza.at(i)->zog)
            {
                p = akuza.at(j);
                akuza.at(j) = akuza.at(i);
                akuza.at(i) = p;
            }
            else if (akuza.at(j)->zog == akuza.at(i)->zog)
            {
                if (akuza.at(j)->broj > akuza.at(i)->broj)
                {
                    p = akuza.at(j);
                    akuza.at(j) = akuza.at(i);
                    akuza.at(i) = p;
                }
            }
        }
    }
}

static void prikazi_sliku(KartaPravokutnik* k, qreal sirina, qreal visina)
{
    cout << "USAO U PRIKAZI SLIKU" << endl;
    QPixmap slika_karte(k->staza.c_str());
    cout << k->staza << endl;
    QPixmap skalirana_slika = slika_karte.scaled(sirina, visina, Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    k->slika->setPixmap(skalirana_slika);
    k->slika->setParentItem(k);
    k->slika->setPos((sirina - skalirana_slika.width()) / 2,
        (visina - skalirana_slika.height()) / 2);
}

static void prikazi_poledinu(KartaPravokutnik* k, qreal sirina, qreal visina)
{
    cout << "USAO U PRIKAZI POLEDINU" << endl;
    QPixmap poledina_karte("C:/Users/denis/OneDrive/Slike/pozadina.jpg");
    cout << k->staza << endl;
    QPixmap skalirana_poledina = poledina_karte.scaled(sirina, visina, Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    k->slika->setPixmap(skalirana_poledina);
    k->slika->setParentItem(k);
    k->slika->setPos((sirina - skalirana_poledina.width()) / 2,
        (visina - skalirana_poledina.height()) / 2);
}

static int prebroji_karte_jednog_zoga(Igrac* komp, int zog)
{
    int brojac = 0;
    int i;
    for (i = 0; i < komp->pravokutnici.size(); i++)
    {
        if (komp->pravokutnici.at(i)->zog == zog)
            brojac++;
    }
    return brojac;
}

static void izdvoji_karte_jednog_zoga(vector<KartaPravokutnik*> &k, Igrac* komp)
{
    int i;
    for (i = 0; i < komp->pravokutnici.size(); i++)
    {
        if (komp->pravokutnici.at(i)->zog == komp->zeljeni_zog)
            k.push_back(komp->pravokutnici.at(i));
    }
}

static void ispisi_prav(vector<KartaPravokutnik*> v)
{
    int i;
    cout << "PRAVOKUTNICI:" << endl;
    for (i = 0; i < v.size(); i++)
    {
        cout << v.at(i)->broj << ", " << v.at(i)->zog << ", " << v.at(i)->staza << endl;
    }
}

static void podijeli_u_kategorije(vector<KartaPravokutnik*> k, vector<KartaPravokutnik*> &naj, 
    vector<KartaPravokutnik*> &_32, vector<KartaPravokutnik*> &_1, vector<KartaPravokutnik*> &_131211, 
    vector<KartaPravokutnik*> &_7654, Igrac* komp)
{
    int i;
    for (i = 0; i < k.size(); i++)
    {
        if (k.at(i)->broj == 1)
            _1.push_back(k.at(i));
        else if (k.at(i)->broj < 4)
            _32.push_back(k.at(i));
        else if (k.at(i)->broj < 8)
            _7654.push_back(k.at(i));
        else
            _131211.push_back(k.at(i));
        if (k.at(i)->broj == komp->najjace_karte.at(k.at(i)->zog))
            naj.push_back(k.at(i));
    }
    cout << "NAJJACE:" << endl;
    ispisi_prav(naj);
    cout << "TRICE I DUJE:" << endl;
    ispisi_prav(_32);
    cout << "ASEVI:" << endl;
    ispisi_prav(_1);
    cout << "BELE:" << endl;
    ispisi_prav(_131211);
    cout << "LISINE:" << endl;
    ispisi_prav(_7654);
}

static void ispisi_status_karata(Igrac* komp)
{
    int i, j;
    cout << "[ ";
    for (i = 0; i < 4; i++)
    {
        cout << "{ ";
        for (j = 0; j < 3; j++)
        {
            if (j == 2)
                cout << komp->status_karata.at(i).at(j) << " } ";
            else
                cout << komp->status_karata.at(i).at(j) << ", ";
        }
    }
    cout << "]" << endl;
}

static void azuriraj_status_karte(Igrac* komp, Karta* k, int stanje)
{
    if (k->broj == 3)
        komp->status_karata.at(k->zog).at(0) = stanje;
    else if (k->broj == 2)
        komp->status_karata.at(k->zog).at(1) = stanje;
    else
        komp->status_karata.at(k->zog).at(2) = stanje;
}

static void karte_min_prioriteta(Igrac* komp, int min_prioritet)
{
    vector<KartaPravokutnik*> kandidati;
    int i, n;
    int max_broj_karata_zoga = 0;
    int max_zog = 0;
    cout << "KARTE NAJVISEG PRIORITETA:" << endl;
    for (i = 0; i < komp->pravokutnici.size(); i++)
    {
        if (komp->pravokutnici.at(i)->prioritet == min_prioritet)
        {
            kandidati.push_back(komp->pravokutnici.at(i));
            cout << komp->pravokutnici.at(i)->broj << ", " << komp->pravokutnici.at(i)->zog << " PRIO = " <<
                komp->pravokutnici.at(i)->prioritet << endl;
        }
    }
    if (kandidati.size() == 1)
    {
        kandidati.at(0)->setPos(460, 300);
        komp->odigrana_karta = kandidati.at(0);
    }
    else
    {
        for (i = 0; i < kandidati.size(); i++)
        {
            n = prebroji_karte_jednog_zoga(komp, kandidati.at(i)->zog);
            if (n > max_broj_karata_zoga)
            {
                max_broj_karata_zoga = n;
                max_zog = kandidati.at(i)->zog;
            }
            else if (kandidati.at(i)->zog != max_zog)
            {
                kandidati.erase(kandidati.begin() + i);
            }
        }
        kandidati.at(kandidati.size() - 1)->setPos(460, 300);
        komp->odigrana_karta = kandidati.at(kandidati.size() - 1);
    }
}

static void dodijeli_prioritete(Igrac* komp, vector<KartaPravokutnik*> naj, vector<KartaPravokutnik*> bele,
    vector<KartaPravokutnik*> lisine)
{
    int min_prioritet = 20;
    int i;
    if (naj.size() > 0)
    {
        for (i = 0; i < naj.size(); i++)
        {
            if ((komp->status_karata.at(naj.at(i)->zog).at(2) == 2) &&
                (komp->status_karata.at(naj.at(i)->zog).at(1) > 1))
            {
                naj.at(i)->setPos(460, 300);
                komp->odigrana_karta = naj.at(i);
                return;
            }
            else if (komp->status_karata.at(naj.at(i)->zog).at(2) == 3)
            {
                naj.at(i)->prioritet = 5;
                min_prioritet = 5;
            }
            else if ((komp->status_karata.at(naj.at(i)->zog).at(2) == 2 && (min_prioritet > 6)))
            {
                naj.at(i)->prioritet = 6;
                min_prioritet = 6;
            }
            else if ((komp->status_karata.at(naj.at(i)->zog).at(2) == 0 && (min_prioritet > 9)))
            {
                naj.at(i)->prioritet = 9;
                min_prioritet = 9;
            }
            else if (min_prioritet > 10)
            {
                naj.at(i)->prioritet = 10;
                min_prioritet = 10;
            }
        }
    }
    if (lisine.size() > 0)
    {
        for (i = 0; i < lisine.size(); i++)
        {
            if (komp->status_karata.at(lisine.at(i)->zog).at(2) == 2)
            {
                if ((prebroji_karte_jednog_zoga(komp, lisine.at(i)->zog) < 3) && (min_prioritet >= 11))
                {
                    lisine.at(i)->prioritet = 11;
                    min_prioritet = 11;
                }
                else
                {
                    lisine.at(i)->prioritet = 3;
                    min_prioritet = 3;
                }
            }
            else if ((komp->status_karata.at(lisine.at(i)->zog).at(2) == 3) && (min_prioritet >= 7))
            {
                lisine.at(i)->prioritet = 7;
                min_prioritet = 7;
            }
            else if ((komp->status_karata.at(lisine.at(i)->zog).at(2) == 0) && (min_prioritet >= 11))
            {
                lisine.at(i)->prioritet = 11;
                min_prioritet = 11;
            }
            else if (min_prioritet > 13)
            {
                lisine.at(i)->prioritet = 13;
                min_prioritet = 13;
            }
        }
    }
    if (bele.size() > 0)
    {
        for (i = 0; i < bele.size(); i++)
        {
            if ((komp->status_karata.at(bele.at(i)->zog).at(2) == 2) && (min_prioritet >= 4))
            {
                if (prebroji_karte_jednog_zoga(komp, bele.at(i)->zog) < 3 && (min_prioritet >= 12))
                {
                    bele.at(i)->prioritet = 12;
                    min_prioritet = 12;
                }
                else
                {
                    bele.at(i)->prioritet = 4;
                    min_prioritet = 4;
                }
            }
            else if ((komp->status_karata.at(bele.at(i)->zog).at(2) == 3) && (min_prioritet >= 8))
            {
                bele.at(i)->prioritet = 8;
                min_prioritet = 8;
            }
            else if ((komp->status_karata.at(bele.at(i)->zog).at(2) == 0) && (min_prioritet >= 12))
            {
                bele.at(i)->prioritet = 12;
                min_prioritet = 12;
            }
            else if (min_prioritet > 14)
            {
                bele.at(i)->prioritet = 14;
                min_prioritet = 14;
            }
        }
    }
    cout << "SVI PRIORITETI:" << endl;
    for (i = 0; i < komp->pravokutnici.size(); i++)
    {
        cout << komp->pravokutnici.at(i)->broj << ", " << komp->pravokutnici.at(i)->zog << " PRIO = " <<
            komp->pravokutnici.at(i)->prioritet << endl;
    }
    karte_min_prioriteta(komp, min_prioritet);
}

static void azuriraj_najjace_karte(KartaPravokutnik* k, Igrac* komp)
{
    int i;
    if (k->broj == 3)
    {
        if (komp->status_karata.at(k->zog).at(1) != 3)
            komp->najjace_karte.at(k->zog) = 2;
        else if (komp->status_karata.at(k->zog).at(2) != 3)
            komp->najjace_karte.at(k->zog) = 1;
        else
            komp->najjace_karte.at(k->zog) = 13;
    }
    else if (k->broj == 2)
    {
        if (komp->status_karata.at(k->zog).at(2) != 3)
            komp->najjace_karte.at(k->zog) = 1;
        else
            komp->najjace_karte.at(k->zog) = 13;
    }
    else
        komp->najjace_karte.at(k->zog) = 13;
    cout << "NOVE NAJJACE KARTE: { ";
    for (i = 0; i < 4; i++)
    {
        cout << komp->najjace_karte.at(i) << " ";
    }
    cout << "}" << endl;
}

static void skupi_bacene_karte(Igrac* igrac, Igrac* komp, Spil* spil, QGraphicsScene* scena)
{
    igrac->odigrana_karta->setVisible(false);
    komp->odigrana_karta->setVisible(false);
    if (igrac->odigrana_karta->broj < 4)
        azuriraj_status_karte(komp, igrac->odigrana_karta, 3);
    if (komp->odigrana_karta->broj < 4)
        azuriraj_status_karte(komp, komp->odigrana_karta, 3);
    if (igrac->odigrana_karta->broj == komp->najjace_karte.at(igrac->odigrana_karta->zog))
        azuriraj_najjace_karte(igrac->odigrana_karta, komp);
    if (komp->odigrana_karta->broj == komp->najjace_karte.at(komp->odigrana_karta->zog))
        azuriraj_najjace_karte(komp->odigrana_karta, komp);
    ispisi_status_karata(komp);
    int i;
    for (i = 0; i < komp->pravokutnici.size(); i++)
        komp->pravokutnici.at(i)->prioritet = 20;
    spil->povuci_kartu(igrac, komp, scena);
}

static void brisanje_vektora(vector<KartaPravokutnik*> &v)
{
    for (KartaPravokutnik* k : v)
    {
        delete k;
    }
    v.clear();
}

static void bacanje_karte(Igrac* igrac, Igrac* komp, Spil* spil, QGraphicsScene* scena)
{
    int i, j;
    if (komp->potez)
    {
        vector<KartaPravokutnik*> najjace;
        vector<KartaPravokutnik*> trice_duje;
        vector<KartaPravokutnik*> asevi;
        vector<KartaPravokutnik*> bele;
        vector<KartaPravokutnik*> lisine;
        vector<KartaPravokutnik*> karte_zeljenog_zoga;
        if (komp->zeljeni_zog >= 0)
        {
            cout << "ZELJENI ZOG: " << komp->zeljeni_zog << endl;
            izdvoji_karte_jednog_zoga(karte_zeljenog_zoga, komp);
            podijeli_u_kategorije(karte_zeljenog_zoga, najjace, trice_duje, asevi, bele, lisine, komp);
        }
        if (karte_zeljenog_zoga.size() > 0)
        {
            if (komp->status_karata.at(komp->zeljeni_zog).at(2) == 1)
            {
                cout << "IGRAC IMA SUHOG ASA" << endl;
                trice_duje.at(0)->setPos(460, 300);
                komp->odigrana_karta = trice_duje.at(0);
                cout << "KOMP ODIGRAVA " << komp->odigrana_karta->broj << ", " <<
                komp->odigrana_karta->zog << ", " << komp->odigrana_karta->staza << endl;
            }
            else if (komp->status_karata.at(komp->zeljeni_zog).at(2) == 2)
            {
                cout << "KOMP IMA ASA ZELJENOG ZOGA" << endl;
                asevi.at(0)->setPos(460, 300);
                komp->odigrana_karta = asevi.at(0);
                cout << "KOMP ODIGRAVA " << komp->odigrana_karta->broj << ", " <<
                    komp->odigrana_karta->zog << ", " << komp->odigrana_karta->staza << endl;
            }
            else
            {
                cout << "KOMP NEMA ASA ZELJENOG ZOGA" << endl;
                if (bele.size() > 0)
                {
                    bele.at(0)->setPos(460, 300);
                    komp->odigrana_karta = bele.at(0);
                    cout << "KOMP ODIGRAVA " << komp->odigrana_karta->broj << ", " <<
                        komp->odigrana_karta->zog << ", " << komp->odigrana_karta->staza << endl;
                }
                else if (trice_duje.size() > 0)
                {
                    trice_duje.at(0)->setPos(460, 300);
                    komp->odigrana_karta = trice_duje.at(0);
                    cout << "KOMP ODIGRAVA " << komp->odigrana_karta->broj << ", " <<
                        komp->odigrana_karta->zog << ", " << komp->odigrana_karta->staza << endl;
                }
                else
                {
                    lisine.at(0)->setPos(460, 300);
                    komp->odigrana_karta = lisine.at(0);
                    cout << "KOMP ODIGRAVA " << komp->odigrana_karta->broj << ", " <<
                        komp->odigrana_karta->zog << ", " << komp->odigrana_karta->staza << endl;
                }
            }
        }
        else
        {
            podijeli_u_kategorije(komp->pravokutnici, najjace, trice_duje, asevi, bele, lisine, komp);
            if (najjace.size() > 0)
            {
                int i;
                for (i = 0; i < najjace.size(); i++)
                {
                    if (najjace.at(i)->broj == 1)
                    {
                        najjace.at(i)->setPos(460, 300);
                        komp->odigrana_karta = najjace.at(i);
                    }
                    else
                        dodijeli_prioritete(komp, najjace, bele, lisine);
                    break;
                }
            }
            else
                dodijeli_prioritete(komp, najjace, bele, lisine);
        }
        for (i = 0; i < komp->ruka.size(); i++)
        {
            if ((komp->ruka.at(i)->broj == komp->odigrana_karta->broj) &&
                (komp->ruka.at(i)->zog == komp->odigrana_karta->zog))
            {
                cout << "BRISE KARTU IZ RUKE I ODIGRAVA KARTU " << komp->odigrana_karta->broj << ", " <<
                    komp->odigrana_karta->zog << endl;
                prikazi_sliku(komp->odigrana_karta, 120, 210);
                komp->ruka.erase(komp->ruka.begin() + i);
                cout << "KOMP RUKA NAKON BRISANJA" << endl;
                ispisi(komp->ruka);
                break;
            }
        }
        /*
        brisanje_vektora(karte_zeljenog_zoga);
        brisanje_vektora(najjace);
        brisanje_vektora(trice_duje);
        brisanje_vektora(asevi);
        brisanje_vektora(bele);
        brisanje_vektora(lisine);
        */
    }
    else
    {
        vector<KartaPravokutnik*> valjane_karte;
        //KARTE KOJE SU ISTOG ZOGA KAO I BACENA KARTA IDU U VALJANE KARTE
        for (i = 0; i < komp->pravokutnici.size(); i++)
        {
            if (komp->pravokutnici.at(i)->zog == igrac->odigrana_karta->zog)
                valjane_karte.push_back(komp->pravokutnici.at(i));
        }
        //AKO IMA VALJANIH KARATA
        if (valjane_karte.size() > 0)
        {
            cout << "IMA VALJANIH KARATA" << endl;
            vector<KartaPravokutnik*> jace_karte;
            //PROVJERAVAM KOJE OD VALJANIH KARATA SU JACE OD BACENE KARTE IGRACA I DODAJEM IH U JACE KARTE
            for (i = 0; i < valjane_karte.size(); i++)
            {
                if (valjane_karte.at(i)->jacina > igrac->odigrana_karta->jacina)
                {
                    cout << "JACA KARTA OD BACENE PRONADENA" << endl;
                    jace_karte.push_back(valjane_karte.at(i));
                }
            }
            //AKO KOMPJUTOR IMA JACIH KARATA OD MOJE BACENE KARTE
            if (jace_karte.size() > 0)
            {
                komp->potez = true;
                cout << "IMA JACIH KARATA" << endl;
                //PROVJERAVAM IMA LI ASA I BACA GA AKO GA IMA, ZATIM IZLAZI IZ FUNKCIJE
                for (i = 0; i < jace_karte.size(); i++)
                {
                    if (jace_karte.at(i)->broj == 1)
                    {
                        cout << "IMA ASA KOJEG BI TREBAO BACITI" << endl;
                        jace_karte.at(i)->setPos(460, 300);
                        komp->odigrana_karta = jace_karte.at(i);
                        //KADA SE BACENA KARTA ODREDI, BRISE SE TA ISTA KARTA IZ RUKE
                        for (j = 0; j < komp->ruka.size(); j++)
                        {
                            if ((komp->ruka.at(j)->broj == komp->odigrana_karta->broj) &&
                                (komp->ruka.at(j)->zog == komp->odigrana_karta->zog))
                            {
                                cout << "BRISE KARTU IZ RUKE " << komp->odigrana_karta->broj << ", " <<
                                    komp->odigrana_karta->zog << endl;
                                prikazi_sliku(komp->odigrana_karta, 120, 210);
                                komp->ruka.erase(komp->ruka.begin() + j);
                                cout << "KOMP RUKA NAKON BRISANJA" << endl;
                                ispisi(komp->ruka);
                                QTimer::singleShot(1000, [igrac, komp, spil, scena]() {
                                    azuriraj_bodove(komp, igrac->odigrana_karta->vrijednost +
                                        komp->odigrana_karta->vrijednost);
                                    skupi_bacene_karte(igrac, komp, spil, scena);
                                    });
                                return;
                            }
                        }
                    }
                }
                //AKO NEMA ASA, TRAZI NAJSLABIJU KARTU KOJA I DALJE MOZE UBITI MOJU BACENU KARTU
                int najmanja_jacina = 0; //NAJMANJA JACINA JE INDEX NAJSLABIJE KARTE KOJA MOZE UBITI MOJU KARTU
                cout << "NEMA ASA ALI IMA JACU KARTU" << endl;
                for (i = 1; i < jace_karte.size(); i++)
                {
                    if ((jace_karte.at(i)->jacina < jace_karte.at(najmanja_jacina)->jacina) &&
                        (jace_karte.at(i)->vrijednost > 0))
                    {
                        cout << "JACINA NAJSLABIJE KARTE KOJA MOZE UBITI: " << jace_karte.at(najmanja_jacina)->jacina << endl;
                        cout << "JACINA KARTE NA KOJOJ JE PETLJA: " << jace_karte.at(i)->jacina << endl;
                        najmanja_jacina = i;
                    }
                }
                jace_karte.at(najmanja_jacina)->setPos(460, 300);
                komp->odigrana_karta = jace_karte.at(najmanja_jacina);
                //KADA SE BACENA KARTA ODREDI, BRISE SE TA ISTA KARTA IZ RUKE
                for (i = 0; i < komp->ruka.size(); i++)
                {
                    if ((komp->ruka.at(i)->broj == komp->odigrana_karta->broj) &&
                        (komp->ruka.at(i)->zog == komp->odigrana_karta->zog))
                    {
                        cout << "BRISE KARTU IZ RUKE " << komp->odigrana_karta->broj << ", " <<
                            komp->odigrana_karta->zog << endl;
                        prikazi_sliku(komp->odigrana_karta, 120, 210);
                        komp->ruka.erase(komp->ruka.begin() + i);
                        cout << "KOMP RUKA NAKON BRISANJA" << endl;
                        ispisi(komp->ruka);
                        QTimer::singleShot(1000, [igrac, komp, spil, scena]() {
                            azuriraj_bodove(komp, igrac->odigrana_karta->vrijednost +
                                komp->odigrana_karta->vrijednost);
                            skupi_bacene_karte(igrac, komp, spil, scena);
                            });
                        return;
                    }
                }
            }
            //AKO NEMA JACIH KARATA, ALI IMA KARATA ISTOG ZOGA KAO I MOJA KARTA, PROVJERAVA NAJMANJE VRIJEDNU I
            //NAJSLABIJU KARTU KOJU MOZE BACITI
            else
            {
                komp->potez = false;
                cout << "NEMA JACIH, ALI IMA VALJANIH KARATA" << endl;
                int min_vrijednost = 0; //INDEX
                for (i = 1; i < valjane_karte.size(); i++)
                {
                    //AKO NADE MANJU VRIJEDNOST OD PRIJASNJE NAJMANJE VRIJEDNOSTI, INDEX TE NOVE KARTE POSTAJE
                    //MIN_VRIJEDNOST
                    if (valjane_karte.at(i)->vrijednost < valjane_karte.at(min_vrijednost)->vrijednost)
                    {
                        min_vrijednost = i;
                    }
                    //AKO NADE KARTU ISTE VRIJEDNOSTI KAO I NAJMANJA VRIJEDNOST KOJA JE OTKRIVENA DO TADA,
                    //PROVJERAVA KOJA JE KARTA SLABIJA, NPR. SEDMICA I CETVORKA SU ISTE VRIJEDNOSTI, ALI JE BOLJE
                    //SACUVATI SEDMICU I BACITI CETVORKU
                    else if (valjane_karte.at(i)->vrijednost == valjane_karte.at(min_vrijednost)->vrijednost)
                    {
                        if (valjane_karte.at(i)->jacina < valjane_karte.at(min_vrijednost)->jacina)
                            min_vrijednost = i;
                    }
                }
                valjane_karte.at(min_vrijednost)->setPos(460, 300);
                komp->odigrana_karta = valjane_karte.at(min_vrijednost);
                //KADA SE BACENA KARTA ODREDI, BRISE SE TA ISTA KARTA IZ RUKE
                for (i = 0; i < komp->ruka.size(); i++)
                {
                    if ((komp->ruka.at(i)->broj == komp->odigrana_karta->broj) &&
                        (komp->ruka.at(i)->zog == komp->odigrana_karta->zog))
                    {
                        cout << "BRISE KARTU IZ RUKE " << komp->odigrana_karta->broj << ", " <<
                            komp->odigrana_karta->zog << endl;
                        prikazi_sliku(komp->odigrana_karta, 120, 210);
                        komp->ruka.erase(komp->ruka.begin() + i);
                        cout << "KOMP RUKA NAKON BRISANJA" << endl;
                        ispisi(komp->ruka);
                        QTimer::singleShot(1000, [igrac, komp, spil, scena]() {
                            azuriraj_bodove(igrac, igrac->odigrana_karta->vrijednost +
                                komp->odigrana_karta->vrijednost);
                            skupi_bacene_karte(igrac, komp, spil, scena);
                            });
                        return;
                    }
                }
            }
            /*
            brisanje_vektora(valjane_karte);
            brisanje_vektora(jace_karte);
            */
        }
        //AKO UOPCE NEMA VALJANIH KARATA, AKO NEMA TAJ ZOG KOJEG SAM BACIO, TAKODER SE GLEDA NAJBEZVRIJEDNIJA I
        //NAJSLABIJA KARTA KOJU KOMP MOZE BACITI, JER NEMA SMISLA DA MI BEZVEZE DAJE PUNTE
        else
        {
            komp->potez = false;
            cout << "NEMA VALJANIH KARATA" << endl;
            int min_vrijednost = 0;
            for (i = 1; i < komp->pravokutnici.size(); i++)
            {
                if (komp->pravokutnici.at(i)->vrijednost < komp->pravokutnici.at(min_vrijednost)->vrijednost)
                {
                    min_vrijednost = i;
                }
                else if (komp->pravokutnici.at(i)->vrijednost == komp->pravokutnici.at(min_vrijednost)->vrijednost)
                {
                    if (komp->pravokutnici.at(i)->jacina < komp->pravokutnici.at(min_vrijednost)->jacina)
                        min_vrijednost = i;
                }
            }
            komp->pravokutnici.at(min_vrijednost)->setPos(460, 300);
            komp->odigrana_karta = komp->pravokutnici.at(min_vrijednost);
            for (i = 0; i < komp->ruka.size(); i++)
            {
                if ((komp->ruka.at(i)->broj == komp->odigrana_karta->broj) &&
                    (komp->ruka.at(i)->zog == komp->odigrana_karta->zog))
                {
                    cout << "BRISE KARTU IZ RUKE " << komp->odigrana_karta->broj << ", " <<
                        komp->odigrana_karta->zog << endl;
                    prikazi_sliku(komp->odigrana_karta, 120, 210);
                    komp->ruka.erase(komp->ruka.begin() + i);
                    cout << "KOMP RUKA NAKON BRISANJA" << endl;
                    ispisi(komp->ruka);
                    QTimer::singleShot(1000, [igrac, komp, spil, scena]() {
                        azuriraj_bodove(igrac, igrac->odigrana_karta->vrijednost +
                            komp->odigrana_karta->vrijednost);
                        skupi_bacene_karte(igrac, komp, spil, scena);
                        });
                }
            }
        }
    }
}

static void promijeni_svojstva(KartaPravokutnik* k, Karta* povucena)
{
    k->broj = povucena->broj;
    k->zog = povucena->zog;
    k->staza = povucena->staza;
    k->jacina = povucena->jacina;
    k->vrijednost = povucena->vrijednost;
    k->prioritet = 20;
}

static void sortiranje_pravokutnika(vector<KartaPravokutnik*> &ruka)
{
    int i, j;
    qreal pom_x, pom_y;
    KartaPravokutnik* k;
    for (i = 0; i < ruka.size() - 1; i++)
    {
        for (j = i + 1; j < ruka.size(); j++)
        {
            if (ruka.at(j)->zog < ruka.at(i)->zog)
            {
                cout << i << ", " << j << endl;
                cout << "LIJEVA KARTA: " << ruka.at(i)->broj << ", " << ruka.at(i)->zog << endl;
                cout << "DESNA KARTA: " << ruka.at(j)->broj << ", " << ruka.at(j)->zog << endl;
                pom_x = ruka.at(j)->x();
                cout << "POM_X: " << pom_x << endl;
                pom_y = ruka.at(j)->y();
                cout << "POM_Y: " << pom_y << endl;
                ruka.at(j)->setPos(ruka.at(i)->x(), ruka.at(i)->y());
                ruka.at(i)->setPos(pom_x, pom_y);
                k = ruka.at(j);
                ruka.at(j) = ruka.at(i);
                ruka.at(i) = k;
            }
            else if (ruka.at(j)->zog == ruka.at(i)->zog)
            {
                if (ruka.at(j)->jacina > ruka.at(i)->jacina)
                {
                    cout << i << ", " << j << endl;
                    cout << "LIJEVA KARTA: " << ruka.at(i)->broj << ", " << ruka.at(i)->zog << endl;
                    cout << "DESNA KARTA: " << ruka.at(j)->broj << ", " << ruka.at(j)->zog << endl;
                    pom_x = ruka.at(j)->x();
                    cout << "POM_X: " << pom_x << endl;
                    pom_y = ruka.at(j)->y();
                    cout << "POM_Y: " << pom_y << endl;
                    ruka.at(j)->setPos(ruka.at(i)->x(), ruka.at(i)->y());
                    ruka.at(i)->setPos(pom_x, pom_y);
                    k = ruka.at(j);
                    ruka.at(j) = ruka.at(i);
                    ruka.at(i) = k;
                }
            }
        }
    }
}

static void provjera_zeljenog_zoga(Igrac* igrac, Igrac* komp)
{
    vector<KartaPravokutnik*> karte_zeljenog_zoga;
    izdvoji_karte_jednog_zoga(karte_zeljenog_zoga, komp);
    int i;
    for (i = 0; i < karte_zeljenog_zoga.size(); i++)
    {
        if (karte_zeljenog_zoga.at(i)->jacina > igrac->odigrana_karta->jacina)
            return;
    }
    komp->zeljeni_zog = -1;
    //brisanje_vektora(karte_zeljenog_zoga);
}

static void dijeljenje_karata(Igrac* igr, Spil* s);

static void KreirajKarte(vector<KartaPravokutnik*>& igrac, vector<KartaPravokutnik*>& komp,
    QGraphicsScene* scene, Igrac* igrac1, Igrac* igrac2, Spil* spil);

static void prvi_potez(Igrac* igrac1, Igrac* igrac2, Spil* spil, QGraphicsScene* scena);

static void KreirajSpil(Igrac* i1, Igrac* i2, QGraphicsScene* scena, Spil* s)
{
    int i;
    QPixmap poledina("C:/Users/denis/OneDrive/Slike/pozadina.jpg");
    for (i = 0; i < 10; i++)
    {
        KartaPravokutnik* k = new KartaPravokutnik(0, 0, 120, 210, poledina, i1, i2, s, scena);
        s->spil_prav.push_back(k);
        s->spil_prav.at(i)->setPos(1350 + i, 300 - i);
        s->spil_prav.at(i)->setPen(Qt::NoPen);
        scena->addItem(s->spil_prav.at(i));
    }
    s->broj_karata->setPlainText("20");
    s->broj_karata->setPos(1389, 249);
}

static void brisanje_karte_iz_spila(Spil* s, QGraphicsScene* scena)
{
    s->broj_karata->setPlainText(QString::number(s->spil.size()));
    s->broj_karata->setPos(1388, 249);
    if (s->spil.size() < 10)
        s->broj_karata->setPos(1398, 249);
    scena->removeItem(s->spil_prav.at(s->spil.size() / 2));
    s->spil_prav.erase(s->spil_prav.begin() + (s->spil.size() / 2));
}

static void nova_partija(Igrac* i1, Igrac* i2, vector<KartaPravokutnik*> igrac, vector<KartaPravokutnik*> komp, 
    QGraphicsScene* scena, Spil* s)
{
    KreirajSpil(i1, i2, scena, s);
    int r = rand() % (2);
    cout << "PRVI POTEZ: " << r << endl;
    if (r)
    {
        i1->potez = true;
        i2->potez = false;
        dijeljenje_karata(i1, s);
        dijeljenje_karata(i2, s);
        dijeljenje_karata(i1, s);
        dijeljenje_karata(i2, s);
    }
    else
    {
        i1->potez = false;
        i2->potez = true;
        dijeljenje_karata(i2, s);
        dijeljenje_karata(i1, s);
        dijeljenje_karata(i2, s);
        dijeljenje_karata(i1, s);
    }
    sortiranje_karata(i1->ruka);
    cout << "Igrac1" << endl;
    ispisi(i1->ruka);
    //sortiranje_karata(i2->ruka);
    cout << "Igrac2" << endl;
    ispisi(i2->ruka);
    KreirajKarte(igrac, komp, scena, i1, i2, s);
    int i;
    for (i = 0; i < komp.size(); i++)
    {
        if (komp.at(i)->broj < 4)
            azuriraj_status_karte(i2, komp.at(i), 2);
    }
    ispisi_status_karata(i2);
    prvi_potez(i1, i2, s, scena);
}

void Spil::povuci_kartu(Igrac* igrac, Igrac* komp, QGraphicsScene* scena)
{
    if (spil.size() > 0)
    {
        igrac->odigrana_karta->setPos(igrac->odigrana_karta->orig_x, igrac->odigrana_karta->orig_y);
        komp->odigrana_karta->setPos(komp->odigrana_karta->orig_x, komp->odigrana_karta->orig_y);
        if (komp->potez)
        {
            komp->ruka.push_back(spil.at(0));
            cout << "KOMP POVUKAO KARTU " << spil.at(0)->broj << ", " << spil.at(0)->zog << endl;
            promijeni_svojstva(komp->odigrana_karta, spil.at(0));
            spil.erase(spil.begin());
            igrac->ruka.push_back(spil.at(0));
            cout << "IGRAC POVUKAO KARTU " << spil.at(0)->broj << ", " << spil.at(0)->zog << endl;
            promijeni_svojstva(igrac->odigrana_karta, spil.at(0));
            spil.erase(spil.begin());
        }
        else
        {
            igrac->ruka.push_back(spil.at(0));
            cout << "IGRAC POVUKAO KARTU " << spil.at(0)->broj << ", " << spil.at(0)->zog << endl;
            promijeni_svojstva(igrac->odigrana_karta, spil.at(0));
            spil.erase(spil.begin());
            komp->ruka.push_back(spil.at(0));
            cout << "KOMP POVUKAO KARTU " << spil.at(0)->broj << ", " << spil.at(0)->zog << endl;
            promijeni_svojstva(komp->odigrana_karta, spil.at(0));
            spil.erase(spil.begin());
        }
        brisanje_karte_iz_spila(this, scena);
        if ((komp->zeljeni_zog > -1) && ((igrac->odigrana_karta->zog == komp->zeljeni_zog)))
            provjera_zeljenog_zoga(igrac, komp);
        if (igrac->odigrana_karta->broj < 4)
            azuriraj_status_karte(komp, igrac->odigrana_karta, 1);
        if (komp->odigrana_karta->broj < 4)
            azuriraj_status_karte(komp, komp->odigrana_karta, 2);
        sortiranje_karata(igrac->ruka);
        sortiranje_pravokutnika(igrac->pravokutnici);
        ispisi_prav(igrac->pravokutnici);
        QTimer::singleShot(1000, [igrac, komp]() {
            igrac->odigrana_karta->setVisible(true);
            komp->odigrana_karta->setVisible(true);
            prikazi_poledinu(igrac->odigrana_karta, 120, 210);
            prikazi_sliku(komp->odigrana_karta, 120, 210);
            });
        QTimer::singleShot(3000, [igrac, komp]() {
            prikazi_sliku(igrac->odigrana_karta, 120, 210);
            prikazi_poledinu(komp->odigrana_karta, 120, 210);
            });
        cout << "Igrac 1:" << endl;
        ispisi(igrac->ruka);
        cout << "Igrac 2:" << endl;
        ispisi(komp->ruka);
        cout << "VELICINA SPILA: " << spil.size() << endl;
        if (komp->potez)
        {
            QTimer::singleShot(3500, [igrac, komp, this, scena]() {
                bacanje_karte(igrac, komp, this, scena);
                igrac->potez = true;
                });
        }
        else
        {
            QTimer::singleShot(3000, [igrac]() {
                igrac->potez = true;
                });
        }
    }
    else if ((igrac->ruka.size() > 0) && (komp->ruka.size() > 0))
    {
        int i;
        cout << "SPIL PRAZAN" << endl;
        for (i = 0; i < igrac->pravokutnici.size(); i++)
        {
            if ((igrac->pravokutnici.at(i)->broj == igrac->odigrana_karta->broj) &&
                (igrac->pravokutnici.at(i)->zog == igrac->odigrana_karta->zog))
            {
                cout << "IZBRISAN PRAVOKUTNIK " << igrac->pravokutnici.at(i)->broj << ", "
                    << igrac->pravokutnici.at(i)->zog << endl;
                scena->removeItem(igrac->pravokutnici.at(i));
                delete igrac->pravokutnici.at(i);
                igrac->pravokutnici.erase(igrac->pravokutnici.begin() + i);
            }
        }
        for (i = 0; i < komp->pravokutnici.size(); i++)
        {
            if ((komp->pravokutnici.at(i)->broj == komp->odigrana_karta->broj) &&
                (komp->pravokutnici.at(i)->zog == komp->odigrana_karta->zog))
            {
                cout << "IZBRISAN PRAVOKUTNIK " << komp->pravokutnici.at(i)->broj << ", "
                    << komp->pravokutnici.at(i)->zog << endl;
                scena->removeItem(komp->pravokutnici.at(i));
                delete komp->pravokutnici.at(i);
                komp->pravokutnici.erase(komp->pravokutnici.begin() + i);
            }
        }
        if (komp->potez)
        {
            QTimer::singleShot(1000, [igrac, komp, this, scena]() {
                bacanje_karte(igrac, komp, this, scena);
                igrac->potez = true;
                });
        }
        else
        {
            igrac->potez = true;
        }
    }
    else
    {
        if (komp->potez)
            azuriraj_bodove(komp, 3);
        else
            azuriraj_bodove(igrac, 3);
        QTimer::singleShot(1000, [igrac, komp, this, scena]() {
            if (igrac->broj_punata > komp->broj_punata)
            {
                igrac->broj_pobjeda++;
                if (igrac->broj_pobjeda >= 10)
                    igrac->br_pobjeda->setPos(1377, 721);
                igrac->br_pobjeda->setPlainText(QString::number(igrac->broj_pobjeda));
            }
            else if (igrac->broj_punata < komp->broj_punata)
            {
                komp->broj_pobjeda++;
                if (komp->broj_pobjeda >= 10)
                    komp->br_pobjeda->setPos(1377, 31);
                komp->br_pobjeda->setPlainText(QString::number(komp->broj_pobjeda));
            }
            delete igrac->odigrana_karta;
            delete komp->odigrana_karta;
            resetiraj_svojstva(igrac, komp);
            vector<Karta*> spil(40);
            this->spil = spil;
            generirajSpil();
            mijesanje_spila();
            vector<KartaPravokutnik*> i1_prav(10);
            vector<KartaPravokutnik*> i2_prav(10);
            nova_partija(igrac, komp, i1_prav, i2_prav, scena, this);
            });
        cout << "PARTIJA ZAVRSENA" << endl;
    }
}

void Igrac::DodajAkuzu(int broj, int zog)
{
    Karta* k = new Karta(broj, zog);
    if (akuze.size() == 0)
        akuze.resize(akuze.size() + 1);
    akuze.at(akuze.size() - 1).push_back(k);
    cout << "Broj akuza: " << akuze.size() - 1 << endl;
    cout << "Velicina: " << akuze.at(akuze.size() - 1).size() << endl;
    cout << "{" << akuze.at(akuze.size() - 1).at(akuze.at(akuze.size() - 1).size() - 1)->broj
        << ", " << akuze.at(akuze.size() - 1).at(akuze.at(akuze.size() - 1).size() - 1)->zog <<
        "}" << endl;
    int i;
    int akuza_od_4 = 0;
    if (akuze.at(akuze.size() - 1).size() == 3)
    {
        cout << "IF VELICINA 3" << endl;
        if (((akuze.at(akuze.size() - 1).at(0)->broj) == (akuze.at(akuze.size() - 1).at(1)->broj)) &&
            ((akuze.at(akuze.size() - 1).at(1)->broj) == ((akuze.at(akuze.size() - 1).at(2)->broj))))
        {
            cout << "IF SVI BROJEVI ISTI" << endl;
            int broj_akuze = akuze.at(akuze.size() - 1).at(0)->broj;
            cout << "Broj akuze" << broj_akuze << endl;
            for (i = 0; i < ruka.size(); i++)
            {
                if ((ruka.at(i)->broj == broj_akuze) &&
                    (ruka.at(i)->zog != akuze.at(akuze.size() - 1).at(0)->zog) &&
                    (ruka.at(i)->zog != akuze.at(akuze.size() - 1).at(1)->zog) &&
                    (ruka.at(i)->zog != akuze.at(akuze.size() - 1).at(2)->zog))
                {
                    akuze.at(akuze.size() - 1).push_back(ruka.at(i));
                    sortiranje_akuza(akuze.at(akuze.size() - 1));
                    if (provjera_duplikata(akuze) == true)
                    {
                        cout << "IF PROVJERA DUPLIKATA TRUE ZA 12" << endl;
                        azuriraj_bodove(this, 12);
                        akuza_od_4 = 1;
                    }
                    else
                        akuze.erase(akuze.begin() + akuze.size() - 1);
                    break;
                }
            }
            if (!akuza_od_4)
            {
                sortiranje_akuza(akuze.at(akuze.size() - 1));
                cout << "IF AKUZA OD 3 KARTE" << endl;
                if (provjera_duplikata(akuze) == true)
                {
                    cout << "IF PROVJERA DUPLIKATA TRUE ZA 9" << endl;
                    azuriraj_bodove(this, 9);
                }
                else
                    akuze.erase(akuze.begin() + akuze.size() - 1);
            }
        }
        else if (((akuze.at(akuze.size() - 1).at(0)->zog) == (akuze.at(akuze.size() - 1).at(1)->zog))
            && ((akuze.at(akuze.size() - 1).at(1)->zog) == ((akuze.at(akuze.size() - 1).at(2)->zog))))
        {
            cout << "SVI ISTI ZOGOVI" << endl;
            sortiranje_akuza(akuze.at(akuze.size() - 1));
            if (provjera_duplikata(akuze) == true)
            {
                cout << "IF PROVJERA DUPLIKATA TRUE" << endl;
                azuriraj_bodove(this, 9);
            }
            else
                akuze.erase(akuze.begin() + akuze.size() - 1);
        }
        else
            akuze.erase(akuze.begin() + akuze.size() - 1);
        akuze.resize(akuze.size() + 1);
        izbrisi_okvire(this->pravokutnici);
    }
    cout << "Broj punata:" << broj_punata << endl;
    //akuze.at(akuze.size() - 1).resize(akuze.at(akuze.size() - 1).size() + 1);
    //akuze.at(akuze.size() - 1).at(akuze.at(akuze.size() - 1).size() - 1)->broj = broj;
    //akuze.at(akuze.size() - 1).at(akuze.at(akuze.size() - 1).size() - 1)->zog = zog;
}
/*
class KartaPravokutnik : public QGraphicsRectItem
{
public:
    KartaPravokutnik(qreal x, qreal y, qreal width, qreal height)
        : QGraphicsRectItem(x, y, width, height) {};
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void prikaziKarte(vector<KartaPravokutnik*> igrac, vector<KartaPravokutnik*> komp,
        QGraphicsScene* scene, Igrac* igrac1, Igrac* igrac2);
};
*/

static bool provjera_zoga(Igrac* i1, Igrac* i2)
{
    int i;
    for (i = 0; i < i1->pravokutnici.size(); i++)
    {
        if (i1->pravokutnici.at(i)->zog == i2->odigrana_karta->zog)
            return true;
    }
    return false;
}

static void odredi_jacu(Igrac* igrac, Igrac* komp, Spil* spil, QGraphicsScene* scena)
{
    if (igrac->odigrana_karta->jacina > komp->odigrana_karta->jacina)
    {
        komp->potez = false;
        azuriraj_bodove(igrac, igrac->odigrana_karta->vrijednost + komp->odigrana_karta->vrijednost);
    }
    else
    {
        komp->potez = true;
        azuriraj_bodove(komp, igrac->odigrana_karta->vrijednost + komp->odigrana_karta->vrijednost);
    }
    skupi_bacene_karte(igrac, komp, spil, scena);
}

static void izbrisi_iz_ruke(Igrac* igrac)
{
    int i;
    for (i = 0; i < igrac->ruka.size(); i++)
    {
        if ((igrac->ruka.at(i)->broj == igrac->odigrana_karta->broj) &&
            (igrac->ruka.at(i)->zog == igrac->odigrana_karta->zog))
        {
            igrac->ruka.erase(igrac->ruka.begin() + i);
            return;
        }
    }
}

void KartaPravokutnik::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if ((contains(event->pos())) && (x() >= 100) && (x() <= 1270) && (y() == 550))
    {
        QPen pen = this->pen();
        if ((igrac1->akuzanje) && (igrac1->potez))
        {
            QPen pen = this->pen();
            if ((pen.color() != Qt::blue) && ((this->broj < 4)))
            {
                QPen plava(Qt::blue);
                plava.setWidth(5);
                this->setPen(plava);
                igrac1->DodajAkuzu(this->broj, this->zog);
                event->accept();
            }
        }
        else if (igrac1->potez)
        {
            if ((igrac2->potez) && (provjera_zoga(igrac1, igrac2)))
            {
                if (this->zog == igrac2->odigrana_karta->zog)
                {
                    this->orig_x = x();
                    cout << "ORIG X:" << this->orig_x << endl;
                    this->orig_y = y();
                    cout << "ORIG Y:" << this->orig_y << endl;
                    this->setPos(820, 300);
                    igrac1->odigrana_karta = this;
                    igrac1->potez = false;
                    izbrisi_iz_ruke(igrac1);
                    QTimer::singleShot(1000, [this]() {
                        odredi_jacu(igrac1, igrac2, s, scena);
                        });
                }
            }
            else if ((igrac2->potez) && (!provjera_zoga(igrac1, igrac2)))
            {
                this->orig_x = x();
                cout << "ORIG X:" << this->orig_x << endl;
                this->orig_y = y();
                cout << "ORIG Y:" << this->orig_y << endl;
                this->setPos(820, 300);
                igrac1->odigrana_karta = this;
                igrac1->potez = false;
                izbrisi_iz_ruke(igrac1);
                if (this->broj < 4)
                    azuriraj_status_karte(igrac2, this, 3);
                QTimer::singleShot(1000, [this]() {
                    azuriraj_bodove(igrac2, igrac1->odigrana_karta->vrijednost + igrac2->odigrana_karta->vrijednost);
                    skupi_bacene_karte(igrac1, igrac2, s, scena);
                    });
                igrac2->zeljeni_zog = igrac2->odigrana_karta->zog;
            }
            else if ((!igrac2->potez) && (igrac2->akuzanje))
            {
                this->orig_x = x();
                cout << "ORIG X:" << this->orig_x << endl;
                this->orig_y = y();
                cout << "ORIG Y:" << this->orig_y << endl;
                this->setPos(820, 300);
                igrac1->odigrana_karta = this;
                igrac1->potez = false;
                izbrisi_iz_ruke(igrac1);
                int bodovi = igrac2->akuze_racunala();
                if (bodovi > 0)
                {
                    QTimer::singleShot(1000, [this, bodovi]() {
                        azuriraj_bodove(igrac2, bodovi * 3);
                        });
                    QTimer::singleShot(5000, [this]() {
                        bacanje_karte(igrac1, igrac2, s, scena);
                        });
                }
                else
                {
                    QTimer::singleShot(1000, [this]() {
                        bacanje_karte(igrac1, igrac2, s, scena);
                        });
                }
            }
            else
            {
                this->orig_x = x();
                cout << "ORIG X:" << this->orig_x << endl;
                this->orig_y = y();
                cout << "ORIG Y:" << this->orig_y << endl;
                this->setPos(820, 300);
                igrac1->odigrana_karta = this;
                igrac1->potez = false;
                izbrisi_iz_ruke(igrac1);
                QTimer::singleShot(1000, [this]() {
                    bacanje_karte(igrac1, igrac2, s, scena);
                    });
            }
            event->accept();
        }
    }
}

class BotunZaBacanje : public QGraphicsRectItem
{
public:
    Igrac* igrac;
    Igrac* komp;
    QGraphicsScene* scena;
    BotunZaBacanje(qreal x, qreal y, qreal width, qreal height, Igrac* i, Igrac* k, QGraphicsScene* sc) :
        QGraphicsRectItem(x, y, width, height)
    {
        igrac = i;
        komp = k;
        scena = sc;
    };
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

static void brisanje_botuna(BotunZaBacanje* b)
{
    b->scena->removeItem(b);
    delete b;
}

void BotunZaBacanje::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (contains(event->pos()) && (igrac->potez))
    {
        int i, j;
        igrac->akuzanje = false;
        if (igrac->akuze.size() > 0)
        {
            for (i = 0; i < igrac->akuze.size(); i++)
            {
                if (igrac->akuze.at(i).size() < 3)
                    break;
                for (j = 0; j < igrac->akuze.at(i).size(); j++)
                {
                    azuriraj_status_karte(komp, igrac->akuze.at(i).at(j), 1);
                }
            }
        }
        ispisi_status_karata(komp);
        for (i = 0; i < igrac->pravokutnici.size(); i++)
        {
            igrac->pravokutnici.at(i)->setPen(Qt::NoPen);
        }
        brisanje_botuna(this);
    }
}

class PrilagodenPogled : public QGraphicsView
{
public:
    PrilagodenPogled(QGraphicsScene* scene) : QGraphicsView(scene) {};
    void resizeEvent(QResizeEvent* event)
    {   
        int sirina = event->size().width();
        int visina = event->size().height();

        QRadialGradient gradijent(sirina / 2, visina / 2, sirina / 2);
        gradijent.setColorAt(0, QColor(144, 238, 144));
        gradijent.setColorAt(1, QColor(34, 139, 34));

        this->scene()->setBackgroundBrush(QBrush(gradijent));
        QGraphicsView::resizeEvent(event);
    }
};

static void KreirajKarte(vector<KartaPravokutnik*> &igrac, vector<KartaPravokutnik*> &komp, 
    QGraphicsScene* scene, Igrac* igrac1, Igrac* igrac2, Spil* spil)
{
    int i;
    qreal sirina = 120;
    qreal visina = 210;
    QPixmap poledina("C:/Users/denis/OneDrive/Slike/pozadina.jpg");
    QPixmap skalirana_poledina = poledina.scaled(sirina, visina, Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    for (i = 0; i < 10; i++)
    {
        QPixmap slika(igrac1->ruka.at(i)->staza.c_str());
        igrac.at(i) = new KartaPravokutnik(0, 0, 120, 210, slika, igrac1, igrac2, spil, scene);
        igrac.at(i)->setPos(100 + i * 120, 550);
        igrac.at(i)->setPen(Qt::NoPen);
        igrac.at(i)->broj = igrac1->ruka.at(i)->broj;
        igrac.at(i)->zog = igrac1->ruka.at(i)->zog;
        igrac.at(i)->staza = igrac1->ruka.at(i)->staza.c_str();
        igrac.at(i)->jacina = igrac1->ruka.at(i)->jacina;
        igrac.at(i)->vrijednost = igrac1->ruka.at(i)->vrijednost;
        scene->addItem(igrac.at(i));
    }
    for (i = 0; i < 10; i++)
    {
        QPixmap slika(igrac2->ruka.at(i)->staza.c_str());
        komp.at(i) = new KartaPravokutnik(0, 0, 120, 210, slika, igrac1, igrac2, spil, scene);
        komp.at(i)->setPos(100 + i * 120, 50);
        komp.at(i)->orig_x = 100 + i * 120;
        komp.at(i)->orig_y = 50;
        komp.at(i)->slika->setPixmap(skalirana_poledina);
        komp.at(i)->slika->setParentItem(komp.at(i));
        komp.at(i)->slika->setPos((sirina - skalirana_poledina.width()) / 2,
            (visina - skalirana_poledina.height()) / 2);
        komp.at(i)->setPen(Qt::NoPen);
        komp.at(i)->broj = igrac2->ruka.at(i)->broj;
        komp.at(i)->zog = igrac2->ruka.at(i)->zog;
        komp.at(i)->staza = igrac2->ruka.at(i)->staza.c_str();
        komp.at(i)->jacina = igrac2->ruka.at(i)->jacina;
        komp.at(i)->vrijednost = igrac2->ruka.at(i)->vrijednost;
        scene->addItem(komp.at(i));
    }
    igrac1->pravokutnici = igrac;
    igrac2->pravokutnici = komp;

    BotunZaBacanje* baci_kartu = new BotunZaBacanje(0, 0, 128, 40, igrac1, igrac2, scene);
    baci_kartu->setPos(1346, 557);
    QRadialGradient gradijent(64, 20, 64);
    gradijent.setColorAt(0, Qt::white);
    gradijent.setColorAt(1, QColor(210, 210, 210));
    QPen crna;
    crna.setColor(Qt::black);
    crna.setWidth(4);
    baci_kartu->setPen(crna);
    baci_kartu->setBrush(QBrush(gradijent));
    QGraphicsTextItem* tekst = new QGraphicsTextItem("Baci kartu", baci_kartu);
    QFont font("Arial", 20);
    tekst->setFont(font);
    scene->addItem(baci_kartu);
}

void Spil::generirajSpil()
{
    vector<int> brojevi{ 1,2,3,4,5,6,7,11,12,13 };
    vector<int> zogovi{ 0,1,2,3 };
    vector<string> slova_zogova{ "s","b","k","d" };
    int jacina, vrijednost;
    int i, j, k = 0;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (i == 0)
            {
                jacina = 8;
                vrijednost = 3;
            }
            else if (i < 3)
            {
                jacina = i + 8;
                vrijednost = 1;
            }
            else if (i < 7)
            {
                jacina = i - 2;
                vrijednost = 0;
            }
            else
            {
                jacina = i - 2;
                vrijednost = 1;
            }
            string putanja = "C:/Users/denis/OneDrive/Slike/" +
                to_string(brojevi.at(i)) + slova_zogova.at(j) + ".jpg";
            spil.at(k) = new Karta(brojevi.at(i), zogovi.at(j), putanja, jacina, vrijednost);
            k++;
        }
    }
}

void Spil::mijesanje_spila()
{
    vector<Karta*> promijesani_spil(40);
    int i;
    for (i = 0; i < 40; i++)
    {
        int r = rand() % (40 - i);
        promijesani_spil.at(i) = spil.at(r);
        spil.erase(spil.begin() + r);
    }
    spil = promijesani_spil;
}

static void dijeljenje_karata(Igrac* igr, Spil* s)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        igr->ruka.push_back(s->spil.at(0));
        s->spil.erase(s->spil.begin());
    }
}

static void prikazi_akuze(optional<int> br, Igrac* komp, optional<int> z, bool poledina)
{
    cout << "USAO U PRIKAZI AKUZE" << endl;
    int Broj = br.value_or(-1);
    int Zog = z.value_or(-1);
    int i;
    if (Zog == -1)
    {
        cout << "AKO JE AKUZA BROJEVA" << endl;
        for (i = 0; i < komp->pravokutnici.size(); i++)
        {
            cout << "komp.at(i)->broj = " << komp->pravokutnici.at(i)->broj << endl;
            if (komp->pravokutnici.at(i)->broj == Broj)
            {
                cout << "DOSAO DO BROJA" << endl;
                if (!poledina)
                    prikazi_sliku(komp->pravokutnici.at(i), 120, 210);
                else
                    prikazi_poledinu(komp->pravokutnici.at(i), 120, 210);
            }
        }
    }
    else if (Broj == -1)
    {
        for (i = 0; i < komp->pravokutnici.size(); i++)
        {
            if ((komp->pravokutnici.at(i)->zog == Zog) && (komp->pravokutnici.at(i)->broj < 4))
                if (!poledina)
                    prikazi_sliku(komp->pravokutnici.at(i), 120, 210);
                else
                    prikazi_poledinu(komp->pravokutnici.at(i), 120, 210);
        }
    }
}

int Igrac::akuze_racunala()
{
    int bodovi = 0;
    int spadi[3] = { 0,0,0 };
    int bastoni[3] = { 0,0,0 };
    int kupe[3] = { 0,0,0 };
    int dinari[3] = { 0,0,0 };
    int ukupno[3] = { 0,0,0 };
    unsigned int i;
    for (i = 0; i < this->ruka.size(); i++)
    {
        if (this->ruka.at(i)->broj == 1)
        {
            if (this->ruka.at(i)->zog == 0)
                spadi[2]++;
            else if (this->ruka.at(i)->zog == 1)
                bastoni[2]++;
            else if (this->ruka.at(i)->zog == 2)
                kupe[2]++;
            else
                dinari[2]++;
            ukupno[2]++;
        }
        else if (this->ruka.at(i)->broj == 2)
        {
            if (this->ruka.at(i)->zog == 0)
                spadi[1]++;
            else if (this->ruka.at(i)->zog == 1)
                bastoni[1]++;
            else if (this->ruka.at(i)->zog == 2)
                kupe[1]++;
            else
                dinari[1]++;
            ukupno[1]++;
        }
        else if (this->ruka.at(i)->broj == 3)
        {
            if (this->ruka.at(i)->zog == 0)
                spadi[0]++;
            else if (this->ruka.at(i)->zog == 1)
                bastoni[0]++;
            else if (this->ruka.at(i)->zog == 2)
                kupe[0]++;
            else
                dinari[0]++;
            ukupno[0]++;
        }
    }
    if (ukupno[2] >= 3)
    {
        cout << "AKUZA ASEVA" << endl;
        QTimer::singleShot(1000, [this]() {
            prikazi_akuze(1, this, nullopt, false);
            QTimer::singleShot(3500, [this]() {
                prikazi_akuze(1, this, nullopt, true);
                });
            });
        bodovi += ukupno[2];
    }
    if (ukupno[1] >= 3)
    {
        cout << "AKUZA DUJA" << endl;
        QTimer::singleShot(1000, [this]() {
            prikazi_akuze(2, this, nullopt, false);
            QTimer::singleShot(3500, [this]() {
                prikazi_akuze(2, this, nullopt, true);
                });
            });
        bodovi += ukupno[1];
    }
    if (ukupno[0] >= 3)
    {
        cout << "AKUZA TRICA" << endl;
        QTimer::singleShot(1000, [this]() {
            prikazi_akuze(3, this, nullopt, false);
            QTimer::singleShot(3500, [this]() {
                prikazi_akuze(3, this, nullopt, true);
                });
            });
        bodovi += ukupno[0];
    }
    if (spadi[0] && spadi[1] && spadi[2])
    {
        cout << "NAPOLITANA SPADI" << endl;
        QTimer::singleShot(1000, [this]() {
            prikazi_akuze(nullopt, this, 0, false);
            QTimer::singleShot(3500, [this]() {
                prikazi_akuze(nullopt, this, 0, true);
                });
            });
        bodovi += 3;
    }
    if (bastoni[0] && bastoni[1] && bastoni[2])
    {
        cout << "NAPOLITANA BATI" << endl;
        QTimer::singleShot(1000, [this]() {
            prikazi_akuze(nullopt, this, 1, false);
            QTimer::singleShot(3500, [this]() {
                prikazi_akuze(nullopt, this, 1, true);
                });
            });
        bodovi += 3;
    }
    if (kupe[0] && kupe[1] && kupe[2])
    {
        cout << "NAPOLITANA KUPA" << endl;
        QTimer::singleShot(1000, [this]() {
            prikazi_akuze(nullopt, this, 2, false);
            QTimer::singleShot(3500, [this]() {
                prikazi_akuze(nullopt, this, 2, true);
                });
            });
        bodovi += 3;
    }
    if (dinari[0] && dinari[1] && dinari[2])
    {
        cout << "NAPOLITANA DINARA" << endl;
        QTimer::singleShot(1000, [this]() {
            prikazi_akuze(nullopt, this, 3, false);
            QTimer::singleShot(3500, [this]() {
                prikazi_akuze(nullopt, this, 3, true);
                });
            });
        bodovi += 3;
    }
    akuzanje = false;
    return bodovi;
}

static void prvi_potez(Igrac* igrac1, Igrac* igrac2, Spil* spil, QGraphicsScene* scena)
{
    if (igrac2->potez)
    {
        int bodovi = igrac2->akuze_racunala();
        if (bodovi > 0)
        {
            QTimer::singleShot(1000, [igrac2, bodovi]() {
                azuriraj_bodove(igrac2, bodovi * 3);
                });
            QTimer::singleShot(5000, [igrac1, igrac2, spil, scena]() {
                bacanje_karte(igrac1, igrac2, spil, scena);
                igrac1->potez = true;
                });
        }
        else
        {
            QTimer::singleShot(1000, [igrac1, igrac2, spil, scena]() {
                bacanje_karte(igrac1, igrac2, spil, scena);
                igrac1->potez = true;
                });
        }
    }
}

class BotunZaPocetakPartije : public QGraphicsRectItem
{
public:
    Igrac* i1;
    Igrac* i2;
    Spil* s;
    QGraphicsScene* scena;
    vector<KartaPravokutnik*> i1_prav;
    vector<KartaPravokutnik*> i2_prav;
    BotunZaPocetakPartije(qreal x, qreal y, qreal width, qreal height, Igrac* igr1, Igrac* igr2,
        Spil* sp, QGraphicsScene* sc, vector<KartaPravokutnik*> i1p, vector<KartaPravokutnik*> i2p) :
        QGraphicsRectItem(x, y, width, height)
    {
        i1 = igr1; i2 = igr2; s = sp; scena = sc; i1_prav = i1p; i2_prav = i2p;
    }
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

void BotunZaPocetakPartije::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (contains(event->pos()))
    {
        nova_partija(i1, i2, i1_prav, i2_prav, scena, s);
        scena->removeItem(this);
        delete this;
    }
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    QApplication app(argc, argv);

    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1000, 800);

    PrilagodenPogled view(scene);
    view.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view.show();

    vector<KartaPravokutnik*> igrac(10);
    vector<KartaPravokutnik*> komp(10);

    QRadialGradient gradijent(50, 50, 50);
    gradijent.setColorAt(0, Qt::white);
    gradijent.setColorAt(1, QColor(210,210,210));

    QRadialGradient gradijent2(21, 21, 21);
    gradijent2.setColorAt(0, Qt::white);
    gradijent2.setColorAt(1, QColor(210, 210, 210));

    QPen crna;
    crna.setColor(Qt::black);
    crna.setWidth(4);

    QGraphicsRectItem* okvir1 = new QGraphicsRectItem(0, 0, 100, 100);
    okvir1->setPos(1360, 610);
    okvir1->setBrush(QBrush(gradijent));
    okvir1->setPen(crna);

    QGraphicsRectItem* okvir2 = new QGraphicsRectItem(0, 0, 100, 100);
    okvir2->setPos(1360, 110);
    okvir2->setBrush(QBrush(gradijent));
    okvir2->setPen(crna);

    QGraphicsRectItem* pobj_okvir1 = new QGraphicsRectItem(0, 0, 70, 70);
    pobj_okvir1->setPos(1375, 720);
    pobj_okvir1->setBrush(QBrush(gradijent));
    pobj_okvir1->setPen(crna);

    QGraphicsRectItem* pobj_okvir2 = new QGraphicsRectItem(0, 0, 70, 70);
    pobj_okvir2->setPos(1375, 30);
    pobj_okvir2->setBrush(QBrush(gradijent));
    pobj_okvir2->setPen(crna);

    QFont font1("Arial", 50);
    font1.setBold(true);
    QFont font2("Arial", 30);
    QFont font3("Arial", 40);
    QFont font4("Arial", 25);

    QGraphicsTextItem* igrac_bodovi = new QGraphicsTextItem("0");
    igrac_bodovi->setFont(font1);
    igrac_bodovi->setPos(1365, 602);
    QGraphicsTextItem* igrac_bele = new QGraphicsTextItem("0/3");
    igrac_bele->setFont(font2);
    igrac_bele->setPos(1395, 660);

    QGraphicsTextItem* komp_bodovi = new QGraphicsTextItem("0");
    komp_bodovi->setFont(font1);
    komp_bodovi->setPos(1365, 102);
    QGraphicsTextItem* komp_bele = new QGraphicsTextItem("0/3");
    komp_bele->setFont(font2);
    komp_bele->setPos(1395, 160);

    QGraphicsTextItem* igrac_pobjede = new QGraphicsTextItem("0");
    igrac_pobjede->setFont(font3);
    igrac_pobjede->setPos(1392, 721);

    QGraphicsTextItem* komp_pobjede = new QGraphicsTextItem("0");
    komp_pobjede->setFont(font3);
    komp_pobjede->setPos(1392, 31);

    Igrac* igrac1 = new Igrac(false, 0, igrac_bodovi, igrac_bele, igrac_pobjede);
    Igrac* igrac2 = new Igrac(false, 0, komp_bodovi, komp_bele, komp_pobjede);

    vector<Karta*> spil(40);
    vector<KartaPravokutnik*> spil_prav;

    QGraphicsRectItem* okvir_br_karata = new QGraphicsRectItem(0, 0, 42, 42);
    okvir_br_karata->setPos(1390, 250);
    okvir_br_karata->setBrush(QBrush(gradijent2));
    okvir_br_karata->setPen(crna);

    QGraphicsTextItem* broj_karata = new QGraphicsTextItem("20");
    broj_karata->setPos(1389, 249);
    broj_karata->setFont(font4);

    Spil* s = new Spil(igrac1, igrac2, spil, spil_prav, broj_karata);
    s->generirajSpil();
    s->mijesanje_spila();
    ispisi(s->spil);

    scene->addItem(okvir_br_karata);
    scene->addItem(broj_karata);
    scene->addItem(okvir1);
    scene->addItem(okvir2);
    scene->addItem(igrac_bodovi);
    scene->addItem(igrac_bele);
    scene->addItem(komp_bodovi);
    scene->addItem(komp_bele);
    scene->addItem(pobj_okvir1);
    scene->addItem(pobj_okvir2);
    scene->addItem(igrac_pobjede);
    scene->addItem(komp_pobjede);

    QRadialGradient gradijent3(111, 25, 111);
    gradijent3.setColorAt(0, Qt::white);
    gradijent3.setColorAt(1, QColor(210, 210, 210));

    BotunZaPocetakPartije* zapocni = new BotunZaPocetakPartije(0, 0, 222, 50, igrac1, igrac2,
        s, scene, igrac, komp);
    zapocni->setPos(650, 370);
    zapocni->setPen(crna);
    zapocni->setBrush(QBrush(gradijent3));

    QGraphicsTextItem* tekst_zapocni = new QGraphicsTextItem("Nova partija", zapocni);
    tekst_zapocni->setFont(font2);

    scene->addItem(zapocni);

    //KreirajKarte(igrac, komp, scene, igrac1, igrac2);
    //prvi_potez(igrac1, igrac2, scene);
    //cout << "Broj punata racunala: " << akuze_racunala(igrac2->ruka, igrac2) << endl;

    return app.exec();
}