#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<fstream>

const int MIN_HOEHENABSTAND_FT = 1000;
const double MIN_HORIZONTALABSTAND_NM = 5.0;

class Flugzeug {
    private:
    std::string flugnummer;
    int hoehe;
    double x;
    double y;
    double vx;
    double vy;
    
    public:
    Flugzeug(std::string nr, int h, double px, double py, double geschwX, double geschwY) {
        flugnummer = nr;
        hoehe = h;
        x = px;
        y = py;
        vx = geschwX;
        vy = geschwY;
    }

    
    void zeigeHoehe () const {
    std::cout<<flugnummer<<": "<<"Höhe: "<<hoehe<<" ft"<<std::endl;
    }
    
    void steige(int ft) {
    hoehe = hoehe + ft;
    }
    
    void bewege() {
    x = x + vx;
    y = y + vy;
    }
    
    bool vertikalerKonflikt(const Flugzeug& anderes) const {
    int unterschied = std::abs(hoehe - anderes.hoehe);
    return unterschied < MIN_HOEHENABSTAND_FT;
    }
    
    double horizontalerAbstand(const Flugzeug& anderes) const {
    double dx = x - anderes.x;
    double dy = y - anderes.y;
    return std::sqrt(dx * dx + dy * dy);
    }
    
    std::string getFlugnummer() const {
        return flugnummer;
    }
    
    int getHoehe() const {
        return hoehe;
    }
};

bool konflikt(const Flugzeug& a, const Flugzeug& b)
{
    return a.vertikalerKonflikt(b) && a.horizontalerAbstand(b) < MIN_HORIZONTALABSTAND_NM;
}


int minutenBisKonflikt (Flugzeug a, Flugzeug b, int maxMinuten){
    for (int m = 1; m <= maxMinuten; m++){
        a.bewege();
        b.bewege();
        if (konflikt(a, b)){
            return m;
        }
    }
    return -1;
}

int main ()
{
    std::ifstream datei("flugzeuge.txt");
    if (!datei) {
        std::cout << "Datei nicht gefunden" << std::endl;
        return 1;
    }
    
    std::vector<Flugzeug> flugzeuge;
    std::string nr;
    int h;
    double px, py, geschwX, geschwY;
    while(datei >> nr >> h >> px >> py >> geschwX >> geschwY) {
        flugzeuge.push_back(Flugzeug(nr, h, px, py, geschwX, geschwY));
    }

    int anzahl = flugzeuge.size();
    
    for (int i = 0; i < anzahl; i++) {
        for (int j = i + 1; j < anzahl; j++) {
            int ergebnis = minutenBisKonflikt(flugzeuge[i], flugzeuge[j], 10);
            if (ergebnis != -1) {
                std::cout << "Warnung: " << flugzeuge[i].getFlugnummer() << " und "<< flugzeuge[j].getFlugnummer() << " in " << ergebnis<< " Minute(n) im Konflikt" << std::endl;
            }
        }
    }
    for (int minute = 1; minute <= 5; minute++){
        for (Flugzeug& flug : flugzeuge){
            flug.bewege();
        }
            for(int i = 0; i < anzahl; i++){
                for(int j = i + 1; j < anzahl; j++){
                    if(konflikt(flugzeuge[i], flugzeuge[j])){
                        std::cout<<"Minute "<< minute <<": "<<flugzeuge[i].getFlugnummer()<<" und "<<flugzeuge[j].getFlugnummer()<<": Konflikt Abstand "<<flugzeuge[i].horizontalerAbstand(flugzeuge[j])<<" NM"<<std::endl;
                    
                        int unterschied = std::abs(flugzeuge[i].getHoehe() - flugzeuge[j].getHoehe());
                        int noetig = MIN_HOEHENABSTAND_FT - unterschied;
                    
                        if (flugzeuge[i].getHoehe() > flugzeuge[j].getHoehe()){
                            std::cout<<" -> Flugzeug Nummer "<<flugzeuge[i].getFlugnummer()<<" steigt um "<<noetig<<" ft"<<std::endl;
                            flugzeuge[i].steige(noetig);
                        } else {
                            std::cout<<" -> Flugzeug Nummer "<<flugzeuge[j].getFlugnummer()<<" steigt um "<<noetig<<" ft"<<std::endl;
                            flugzeuge[j].steige(noetig);
                        }
                    }
                }
            }
    }
    for (const Flugzeug& flug : flugzeuge) {
        flug.zeigeHoehe();
    }
    return 0;
    
}
