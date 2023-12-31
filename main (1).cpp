#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>


using namespace std;

vector<string> rastgeleModelListesi();
vector<int> rastgeleFiyatListesi(size_t uzunluk);
string rastgeleIsim();


class Berber {
private:
    string isim;
    vector<string> sacModelleri;
    vector<int> sacModelFiyatlari;
    vector<string> randevuSaatleri;
    vector<bool> saatDolulukDurumu;

public:
    Berber(const string& berberIsim) : isim(berberIsim) {
        isim = rastgeleIsim();
        sacModelleri = rastgeleModelListesi();
        sacModelFiyatlari = rastgeleFiyatListesi(sacModelleri.size());

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
        cout << "Sac Modelleri ve Fiyatlari:" << endl;
        for (size_t i = 0; i < sacModelleri.size(); ++i) {
            cout << i + 1 << ". " << sacModelleri[i] << " - " << sacModelFiyatlari[i] << " TL" << endl;
        }
    }

    void randevuSaatleriGoster()  {
        cout << "\nRandevu Saatleri:" << endl;
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
        if(saatDolulukDurumu[saat])
        saatDolulukDurumu[saat] = false;
        else
            saatDolulukDurumu[saat] = true;
    }

    int doluSaat(){
        for (int i = 9; i <= 17; ++i) {
            if(saatDolulukDurumu[i] == false){
                return i;
            }
        }
    }



};

//Kullanici clas yapisi

class Kullanici {
private:
    string isim;
    int cuzdanBakiyesi;
    bool randevuhakki = true;


public:
    Kullanici(const string& kullaniciIsim, int bakiye) : isim(kullaniciIsim), cuzdanBakiyesi(bakiye) {}



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

    cout << "Bakiye giriniz: "<<endl;
    cin >>cuzdanBakiyesi;

    return cuzdanBakiyesi;
    }

    void getRandevuBilgi(Berber& berber){
        cout<<"Randevu aldiginiz berber :"<<berber.getBerberisim()<<endl;
        cout<<"Randevu aldiginiz saat :"<<berber.doluSaat()<<".00 "<<endl;
        //cout<<"Randevu aldiginiz sac modeli :"<<endl;


    }

    void setBakiye(int geriodeme){
        cuzdanBakiyesi += geriodeme;
    }

    int bakiyeKontrolEt() {
        return cuzdanBakiyesi;
    }

};

// Rastgele isim seçen bir fonksiyon
string rastgeleIsim() {
    vector<string> isimler = {"Serdar Arslan", "Ahmet Kaya", "Mehmet Demir", "Can Yucel", "Emre Tekin", "Huseyin Aksoy", "Burak Celik", "Oguzhan Ozturk", "Yasin Aydin", "Serkan Yildirim", "Onur Korkmaz", "Mustafa Ekinci", "Gokhan Yilmaz", "Cemal Arslan", "Kaan Kaya" };
    return isimler[rand() % isimler.size()];
}

// Rastgele fiyat listesi oluşturan bir fonksiyon
vector<int> rastgeleFiyatListesi(size_t uzunluk) {
    vector<int> fiyatlar;
    for (size_t i = 0; i < uzunluk; ++i) {
        fiyatlar.push_back(rand() % 31 + 30); // 30-60 TL arası rastgele fiyatlar
    }
    return fiyatlar;
}

// Rastgele saç modeli listesi oluşturan bir fonksiyon
vector<string> rastgeleModelListesi() {
    vector<string> modeller = {"Model1", "Model2", "Model3", "Model4", "Model5", "Model6", "Model7"};

    // Rastgele bir sayı belirleyerek model sayısını belirle
    size_t modelSayisi = rand() % 6 + 5;  // 5-10 arası rastgele sayı

    vector<string> rastgeleModeller;

    // Verilen model sayısı kadar rastgele saç modeli seç
    for (size_t i = 0; i < modelSayisi; ++i) {
        size_t rastgeleIndex = rand() % modeller.size();
        rastgeleModeller.push_back(modeller[rastgeleIndex]);
    }

    return rastgeleModeller;
}


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

    cout << "Randevu almak istediginiz saat (0 iptal): ";
    int saatSecim;
    cin >> saatSecim;
    saatSecim = int(saatSecim);
    if (saatSecim == 0) {
        return; // Randevu iptali
    }

    else{
        while (true){
            cout << "\nSac modeli seciniz(0-geri):" << endl;
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

        //secilen modelin fiyatini kontrol etmek lazim. ve sat seciminden sonra model secimi lazim.
        if(!kullanici.getRandevuhakki()){
            cout <<"Randevu basariyla alinmistir randevu saatiniz: "<<saatSecim +8 <<endl;
            berber.setRandevu(saatSecim-1);
        }

    }


}

void randevuIptalEt(Berber& berber, Kullanici& kullanici) {
    if (!kullanici.getRandevuhakki()) {
        cout <<berber.getBerberisim()<<"'den almis oldugunuz randevunuz iptal edilmistir."<< endl;
        berber.setRandevu(berber.doluSaat()-9);
        kullanici.setRandevuhakki(true);
        kullanici.setBakiye(100-kullanici.bakiyeKontrolEt());
    } else {
        cout << "Henüz randevu almamışsınız." << endl;
    }
}




int main() {
    srand(time(0));

    vector<Berber> berberDukkanlari = {Berber("BerberDukkan1"), Berber("BerberDukkan2"), Berber("BerberDukkan3")};
    Kullanici kullanici("Kullanici1", 100);

    int simdikiSaat = 9;

    kullanici.getBakiye();
    while (true) {
        int secim;//berber dukkani icin secim degeri
        int secim2;//randevu aldiktan sonraki secim menusu icin deger
        if(kullanici.getRandevuhakki()){
            cout << "\nBerber Secimi:" << endl;
            for (size_t i = 0; i < berberDukkanlari.size(); ++i) {
                cout << i + 1 << ". ";
                berberDukkanlari[i].berberDetaylariniGoster();
            }
            cout<<"4- Bakiye kontrol et"<<endl;
            cout << "Seciminizi yapin (0 cikis): ";
            cin >> secim;

            if (secim == 0) {
                break;
            }

            if(secim==4){
                cout<<"Mevcut bakiyeniz: "<<kullanici.bakiyeKontrolEt()<<endl;
            }

            else if (secim > 0 && secim <= static_cast<int>(berberDukkanlari.size())) {
                Berber& secilenBerber = berberDukkanlari[secim - 1];

                while (kullanici.getRandevuhakki()) {
                    cout << "\n1. Sac Stilleri" << endl;
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
            cout << "3- Randevu iptali"<<endl;
            cout << "4- Bakiye kontrol"<<endl;

            cin >> secim2;
            if(secim2<=0 || secim2 >5){
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
            else if(secim2 == 3){
                randevuIptalEt(berberDukkanlari[secim - 1], kullanici);
            }
            else if(secim2 == 4){
                int x=kullanici.bakiyeKontrolEt();
                cout<<"Bakiyeniz: "<<x<<endl;
            }


        }


    }



    return 0;
}

