#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<fstream>

struct Flugzeug {
    std::string flugnummer;
    int hoehe;
    double x;
    double y;
    double vx;
    double vy;
};

void zeigeHoehe (const Flugzeug& f)
{
        std::cout<<f.flugnummer<<": "<<"Höhe: "<<f.hoehe<<" ft"<<std::endl;

}

bool vertikalerKonflikt(const Flugzeug& a, const Flugzeug& b)
{
    int unterschied = std::abs(a.hoehe - b.hoehe);
    return unterschied < 1000;
}

double horizontalerAbstand(const Flugzeug& a, const Flugzeug& b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool konflikt(const Flugzeug& a, const Flugzeug& b)
{
    return vertikalerKonflikt(a, b) && horizontalerAbstand(a, b) < 5.0;
}

void steige(Flugzeug& f, int ft)
{
    f.hoehe = f.hoehe + ft;
}

void bewege(Flugzeug& f)
{
    f.x = f.x + f.vx;
    f.y = f.y + f.vy;
}

int minutenBisKonflikt (Flugzeug a, Flugzeug b, int maxMinuten){
    for (int m = 1; m <= maxMinuten; m++){
        bewege(a);
        bewege(b);
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
    Flugzeug f;
    while (datei >> f.flugnummer >> f.hoehe >> f.x >> f.y >> f.vx >> f.vy) {
        flugzeuge.push_back(f);
    }
    
    int anzahl = flugzeuge.size();
    
    for (int i = 0; i < anzahl; i++) {
        for (int j = i + 1; j < anzahl; j++) {
            int ergebnis = minutenBisKonflikt(flugzeuge[i], flugzeuge[j], 10);
            if (ergebnis != -1) {
                std::cout << "Warnung: " << flugzeuge[i].flugnummer << " und "<< flugzeuge[j].flugnummer << " in " << ergebnis<< " Minute(n) im Konflikt" << std::endl;
            }
        }
    }

    
    for (int minute = 1; minute <= 5; minute++){
        for (Flugzeug& flug : flugzeuge){
            bewege(flug);
        }
            for(int i = 0; i < anzahl; i++){
                for(int j = i + 1; j < anzahl; j++){
                    if(konflikt(flugzeuge[i], flugzeuge[j])){
                        std::cout<<"Minute "<< minute <<": "<<flugzeuge[i].flugnummer<<" und "<<flugzeuge[j].flugnummer<<": Konflikt Abstand "<<horizontalerAbstand(flugzeuge[i], flugzeuge[j])<<" NM"<<std::endl;
                    
                        int unterschied = std::abs(flugzeuge[i].hoehe - flugzeuge[j].hoehe);
                        int noetig = 1000 - unterschied;
                    
                        if (flugzeuge[i].hoehe > flugzeuge[j].hoehe){
                            std::cout<<" -> Flugzeug Nummer "<<flugzeuge[i].flugnummer<<" steigt um "<<noetig<<" ft"<<std::endl;
                            steige(flugzeuge[i], noetig);
                        } else {
                            std::cout<<" -> Flugzeug Nummer "<<flugzeuge[j].flugnummer<<" steigt um "<<noetig<<" ft"<<std::endl;
                            steige(flugzeuge[j], noetig);
                        }
                    }
                }
            }
    }
    for (Flugzeug flug : flugzeuge) {
        zeigeHoehe(flug);
    }
    return 0;
}
