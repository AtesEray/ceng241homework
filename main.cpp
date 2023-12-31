#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Berber {
private:
    string isim;
    vector<string> sacModelleri;
    vector<int> sacModelFiyatlari;
    vector<string> randevuSaatleri;
    vector<bool> saatDolulukDurumu;

public:
    Berber(const string& berberIsim) : isim(berberIsim) {
        sacModelleri = {"Model1", "Model2", "Model3", "Model4", "Model5"};
        sacModelFiyatlari = {30, 40, 50, 60, 70};

        //randevu saatlerini ayarladigi kisim
        for (int i = 9; i <= 17; ++i) {
            randevuSaatleri.push_back(to_string(i) + ":00");
            saatDolulukDurumu.push_back(false);
        }
    }



    void berberDetaylariniGoster()  {
        cout << "Berber: " << isim << endl;
    }

    void sacStilleriGoster()  {
        cout << "Saç Modelleri ve Fiyatları:" << endl;
        for (size_t i = 0; i < sacModelleri.size(); ++i) {
            cout << i + 1 << ". " << sacModelleri[i] << " - " << sacModelFiyatlari[i] << " TL" << endl;
        }
    }

    void randevuSaatleriGoster()  {
        cout << "Randevu Saatleri:" << endl;
        for (size_t i = 0; i < randevuSaatleri.size(); ++i) {
            if (!saatDolulukDurumu[i]) {
                cout << i + 1 << ". " << randevuSaatleri[i] << endl;
            }
        }
    }

    string getBerberisim(){
        return isim;
    }
    int getFiyat(int i){
        return sacModelFiyatlari[i];
    }
    int getSacmodel(){
        return sacModelFiyatlari.size();
    }

    //kullancinin randevu aldigi saati true ya cevirir
    void setRandevu(int saat){
    saatDolulukDurumu[saat] = true;
    }

    int doluSaat(){
        for (int i = 9; i <= 17; ++i) {
            if(saatDolulukDurumu[i] == false){
                return i;
            }
        }
    }


    // Diğer gerekli fonksiyonlar buraya eklenir.
    // Örneğin, randevu al, randevu iptal et, bakiye kontrolü yap gibi.
};

//Kullanici clas yapisi

class Kullanici {
private:
    string isim;
    int cuzdanBakiyesi;
    bool randevuhakki = true;


public:
    Kullanici(const string& kullaniciIsim, int bakiye) : isim(kullaniciIsim), cuzdanBakiyesi(bakiye) {}

    // Diğer gerekli fonksiyonlar buraya eklenir.
    // Örneğin, berber seç, randevu al, bakiye kontrolü yap gibi.

    void getRandevu(int ucret){
        if(ucret > cuzdanBakiyesi){
            cout<<"bakiyeniz yetersiz bu sac stilini alamazsiniz!"<<endl;
        }
        else{
            cuzdanBakiyesi -= ucret;
            cout<<"Basarili bir sekilde randevu aldiniz kalan bakiyeniz:"<<cuzdanBakiyesi<<endl;
            randevuhakki = false;
        }
    }
    bool getRandevuhakki(){
        return randevuhakki;
    }
    void setRandevuhakki(bool x){
        randevuhakki = x;
    }
    int getBakiye(){
        return cuzdanBakiyesi;
    }

    void getRandevuBilgi(Berber& berber){ 
        cout<<"Randevu aldiginiz berber :"<<berber.getBerberisim()<<endl;
        cout<<"Randevu aldiginiz saat :"<<berber.doluSaat()<<".00 "<<endl;
        //cout<<"Randevu aldiginiz sac modeli :"<<endl;  BUNU EKLEMESEKTE OLUR
    }

};

//kullanicinin berbere her 1 km yi kac dakika da gidecegini rast gele belirleyecek fonksiyon
int rastgeleDakikaBelirle() {
    return rand() % 31 + 30;
}

//daha hazir degil bu tam nasil calisiyor bilmiyom gpt yapti
bool berbereYetis(Kullanici& kullanici, int mesafeKm, int randevuSaat, int simdikiSaat) {
    int toplamDakika = 0;

    for (int i = 0; i < mesafeKm; ++i) {
        int dakika = rastgeleDakikaBelirle();
        toplamDakika += dakika;

        if (simdikiSaat + toplamDakika >= randevuSaat) {
            cout << i + 1 << " km gidildi, toplam " << toplamDakika << " dakika sürdü." << endl;
            cout << "Berbere yetişilemedi. Randevu iptal edildi." << endl;
            return false;
        }

        cout << i + 1 << " km gidildi, toplam " << toplamDakika << " dakika sürdü." << endl;
    }

    cout << "Berbere başarıyla yetişildi!" << endl;
    return true;
}


//Kullanici icin berberden randevu alma sistemi
void randevuAl(Kullanici& kullanici, Berber& berber) {
    berber.randevuSaatleriGoster();

    cout << "Randevu almak istediğiniz saat (0 iptal): ";
    int saatSecim;
    cin >> saatSecim;
    saatSecim = int(saatSecim);
    if (saatSecim == 0) {
        return; // Randevu iptali
    }

    else{
        while (true){
            cout << "Sac modeli seciniz(0-geri):" << endl;
            berber.sacStilleriGoster();
            int sacsecim;
            cin >> sacsecim;
            int size = berber.getSacmodel();
            if(sacsecim == 0){
                break;
            }
            else if(sacsecim < 0 || sacsecim > size){
                cout<<"Lutfen gecerli bir sac modeli giriniz!"<<endl;
            }
            else{

                kullanici.getRandevu(berber.getFiyat(sacsecim-1));
                break;
            }

        }
        cout<<kullanici.getRandevuhakki()<<endl;
        //secilen modelin fiyatini kontrol etmek lazim. ve sat seciminden sonra model secimi lazim.
        if(kullanici.getRandevuhakki()){
            cout <<"Randevu basariyla alinmistir randevu saatiniz: "<<saatSecim +8 <<endl;
            berber.setRandevu(saatSecim-1);
        }

    }


}

int main() {
    srand(time(0));

    vector<Berber> berberDukkanlari = {Berber("BerberDukkan1"), Berber("BerberDukkan2"), Berber("BerberDukkan3")};
    Kullanici kullanici("Kullanici1", 100);

    int simdikiSaat = 9;

    while (true) {
        int secim;//berber dukkani icin secim degeri
        int secim2;//randevu aldiktan sonraki secim menusu icin deger
        if(kullanici.getRandevuhakki()){
            cout << "Berber Secimi:" << endl;
            for (size_t i = 0; i < berberDukkanlari.size(); ++i) {
                cout << i + 1 << ". ";
                berberDukkanlari[i].berberDetaylariniGoster();
            }
            cout << "Seciminizi yapin (0 cikis): ";
            cin >> secim;

            if (secim == 0) {
                break;
            }

            if (secim > 0 && secim <= static_cast<int>(berberDukkanlari.size())) {
                Berber& secilenBerber = berberDukkanlari[secim - 1];

                while (kullanici.getRandevuhakki()) {
                    cout << "1. Saç Stilleri" << endl;
                    cout << "2. Randevu Al" << endl;
                    cout << "3. Geri" << endl;

                    cout << "Seciminizi yapin: ";
                    int altMenuSecim;
                    cin >> altMenuSecim;

                    if (altMenuSecim == 1) {
                        secilenBerber.sacStilleriGoster();
                    } else if (altMenuSecim == 2) {
                        randevuAl(kullanici, secilenBerber);
                    } else if (altMenuSecim == 3) {
                        break; // Alt menüden çıkış
                    } else {
                        cout << "Hatali secim!" << endl;
                    }
                }

            } else {
                cout << "Hatali secim!" << endl;
            }
        }
        else{

            cout << "1- Randevu bilgisi"<<endl;
            cout << "2- Yola cik"<<endl;

            cin >> secim2;
            if(secim2<=0 || secim2 >2){
                cout<<"Lutfen gecerli bir tercih yapiniz!!"<<endl;
                break;
            }
            else if(secim2==1){
                //Randevu bilgi sorgulama kismi
                kullanici.getRandevuBilgi(berberDukkanlari[secim-1]);
            }
            else if(secim2==2){
                //berbere yol alma sureci
                //kullanici.yolacik();
            }
        }


    }



    return 0;
}

