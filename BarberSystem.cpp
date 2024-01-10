#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <iomanip>

using namespace std;

vector<string> rastgeleModelListesi();
vector<int> rastgeleFiyatListesi(size_t uzunluk);
vector<string> isimler = {"Serdar Arslan", "Ahmet Kaya", "Mehmet Demir", "Can Yucel", "Emre Tekin", "Huseyin Aksoy", "Burak Celik", "Oguzhan Ozturk", "Yasin Aydin", "Serkan Yildirim", "Onur Korkmaz", "Mustafa Ekinci", "Gokhan Yilmaz", "Cemal Arslan", "Kaan Kaya" };

float simdikisaat = 9;

class Berber {
private:
    string isim;
    vector<string> sacModelleri;
    vector<int> sacModelFiyatlari;
    vector<string> randevuSaatleri;
    vector<bool> saatDolulukDurumu;



public:
    int mesafe;
    Berber(const string& berberIsim) : isim(berberIsim) {
        rastgeleIsim();
        sacModelleri = rastgeleModelListesi();
        sacModelFiyatlari = rastgeleFiyatListesi(sacModelleri.size());
        randmesafe();
        //randevu saatlerini ayarladigi kisim
        for (int i = 9; i <= 17; ++i) {
            randevuSaatleri.push_back(to_string(i) + ":00");
            saatDolulukDurumu.push_back(false);
        }
    }

    //berberin rastgele olarak mesafesini belirleyen ve mesafeyi döndüren fonksiyon
    int randmesafe(){
        int max = 25;
        int min = 5;
        mesafe= min + rand() % (max - min + 1);
        return mesafe;
    }


    void berberDetaylariniGoster()  {
        cout << "Berber: " << isim <<"- Uzaklik: "<<mesafe<<" km."<< endl;
    }

    void sacStilleriGoster()  {
        cout << "\nSac Modelleri ve Fiyatlari:" << endl;
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
        for (int i = 0; i <= 8; ++i) {
            if(saatDolulukDurumu[i]){
                return i+9;
            }
        }
    }

    // Rastgele isim seçen bir fonksiyon
    void rastgeleIsim() {
        int index =rand() % isimler.size();
        isim = isimler[index];
        //berber isimlerinin farklı olarak ayarlamak için alınan ismi listeden çıkarıyoruz.
        isimler.erase(isimler.begin()+ index);
    }

    string getSacmodel(int i){
        return sacModelleri[i];
    }

};

//Kullanici clas yapisi

class Kullanici {
private:
    string isim;
    int cuzdanBakiyesi;
    bool randevuhakki = true;
    string sacmodel;


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

    void setSacmodel(string sac){
        sacmodel = sac;
    }
    string getSacmodel(){
        return sacmodel;
    }
    void getRandevuBilgi(Berber& berber){
        cout<<"Randevu aldiginiz berber :"<<berber.getBerberisim()<<endl;
        cout<<"Randevu aldiginiz saat :"<<berber.doluSaat()<<".00 "<<endl;
        cout<<"Randevu aldiginiz sac modeli : "<<sacmodel<<endl;
    }

    void setBakiye(int geriodeme){
        cuzdanBakiyesi += geriodeme;
    }

    int bakiyeKontrolEt() {
        return cuzdanBakiyesi;
    }

};

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
    vector<string> modeller = {
            "Kivircik", "Icardi", "3 numara","Serdar Arslan Model", "Apaci", "Polat alemdar modeli",
            "Afro", "Kel", "Tas kafa", "Dizo model", "Yanlar Kisa Ust kalsin",
            "Erkek cocuk", "Ikiye ayirma", "Ronaldo modeli", "Amerikan", "Subay tiras","Mercedesim var modeli"
    };

    // Rastgele bir sayı belirleyerek model sayısını belirle
    // Verilen model sayısı kadar rastgele saç modeli seç

    size_t modelSayisi = rand() % 7+3;  // 3-9 arası rastgele sayı
    vector<string>eklenecekModeller;

    for(int i = 0; i < modeller.size(); i++){
        int x = rand()%2;
        if(x==1){
            eklenecekModeller.push_back(modeller[i]);
        }
    }
    return eklenecekModeller;
}


//kullanicinin berbere her 1 km yi kac dakika da gidecegini rast gele belirleyecek fonksiyon
float rastgeleDakikaBelirle() {
    float randomdakika= (rand() % 31 + 10);
    randomdakika = randomdakika/60;
    return  randomdakika;
}


//SEVGİLİ TEPKİ FONKSİYONU
bool sevgiliKarar(Berber& berber, Kullanici& kullanici){
    cout<<"1-Sevgilinizin yanina duzgun bir sacla gitmek icin randevuyu ertelemek isteyin"<<endl;
    cout<<"2-Sevgilinizin yanina gidin ve durumu anlatin"<<endl;
    int karar;
    cin >> karar;
    if(karar == 1){
        int kaderGunu;
        kaderGunu = rand()%2+1;
        if(kaderGunu == 1){
            cout<<"Sevgiliniz sorun etmedi ve randevu yarina ertelendi."<<endl;
            cout<<"Yeni gun basliyor"<<endl;
            simdikisaat = 9;
            this_thread::sleep_for(chrono::seconds(1));
            return true;
        }
        else{
            cout<<"Sevgiliniz zorla bugun bulusturdu.."<<endl;
            this_thread::sleep_for(chrono::seconds(1));
            kaderGunu = rand()%2+1;
            if(kaderGunu == 1){
                cout<<"Sevgiliniz sacinizi begendi ve mutlusunuz hayat devam ediyor.."<<endl;
            }
            else{
                cout<<"Sevgiliniz yeni sacinizi hic begenmedi ve Ex'ine dondu hayat bitti..."<<endl;
            }
        }
    }
    else{
        int kaderGunu;
        kaderGunu = rand()%2+1;
        if(kaderGunu == 1){
            cout<<"Sevgiliniz sacinizi begendi ve mutlusunuz hayat devam ediyor.."<<endl;

        }
        else{
            cout<<"Sevgiliniz yeni sacinizi hic begenmedi ve Ex'ine dondu hayat bitti..."<<endl;
        }
    }
    return false;
}

//SAÇ KESİM ANINDA YAŞANAN OLAYLAR BURADA.
bool sacKesim(Kullanici& kullanici, Berber& berber){

    int karar = rand()%2 +1;
    //Saçı güzel kesme ihtimali
    if (karar == 1){
        cout<<"Berber sacinizi cok guzel kesti Serdar hoca gibi yakisikli oldunuz :)))"<<endl;
        cout<<"Fakat..."<<endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Sevgiliniz sacinizi gorunce eski sevgilisi Serdar Arslan aklina geldi ve uzuldu"<<endl;
        kullanici.setRandevuhakki(false);
        return false;
    }
    //Saçı kötü kesme ihtimali
    else{
        cout<<"Berber sacinizi kotu kesti sevgilinizin yaniniza gidemezsiniz"<<endl;
        cout<<"1-Berberle kavga et parani iste"<<endl;
        cout<<"2-Bir sey deme ve sevgilinin yanina git"<<endl;
        int kavgakarar;
        cin>>kavgakarar;
        //BERBERİ DÖVME OLASILIĞI
        if(kavgakarar == 1){
            int kavga = rand()%2 +1;
            if(kavga == 1){
                cout<<"TEBRIKLERRR!! Berberi dovdunuz ve paranizi geri aldiniz.."<<endl;
                berber.setRandevu(berber.doluSaat()-9);
                kullanici.setRandevuhakki(true);
                kullanici.setBakiye(100-kullanici.bakiyeKontrolEt());
                //Sevgili kararı
                return sevgiliKarar(berber, kullanici);
            }
            //BERBERDEN DAYAK YEME OLASILIĞI
            else{
                cout<<"Berber elinizi yuzunuzu dagitti.."<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                cout<<"Kavga ettiginiz icin iki kat para aldi..."<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                kullanici.setBakiye((kullanici.bakiyeKontrolEt() *(-1)));
                cout<<"Sevgiliniz "<<kullanici.getSacmodel() <<" sacinizi hic begenmedi ve dayak yediginizi icin sizden ayrıldı hayat bitti..."<<endl;
                kullanici.setRandevuhakki(false);
                return false;
            }
        }
        else{
            int kaderGunu;
            kaderGunu = rand()%2+1;
            if(kaderGunu == 1){
                cout<<"Sevgiliniz "<<kullanici.getSacmodel() <<" sacinizi cok begendi ve mutlusunuz hayat devam ediyor.."<<endl;
                kullanici.setRandevuhakki(false);
            }
            else{
                cout<<"Sevgiliniz yeni sacinizi hic begenmedi ve Ex'ine döndu hayat bitti..."<<endl;
                kullanici.setRandevuhakki(false);
            }
            return false;
        }
    }
}


//Randevuyu kaçırdığı zaman berberini kararını belirleyen fonksiyon
void randevuKacirma(Kullanici& kullanici, Berber& berber){
    int karar = rand()%2 +1;
    if(karar == 1){
        cout<<"Berber paranizi iade etmeye karar verdi yarin tekrar randevu alabilirsiniz."<<endl;
        kullanici.setBakiye(100- kullanici.bakiyeKontrolEt());
        cout<<"Randevu paraniz: "<<100 - kullanici.bakiyeKontrolEt()<< "hesabiniza yatirilmistir iyi gunler.." <<endl;
        cout<<"Gun bitti yeni bir gun basliyor.."<<endl;
        //Bir sonraki gün için randevu saatleri tekrar boşaltıldı ve kullanıcıya randevu alma hakkı verildi bakiyesi tazelendi.
        berber.setRandevu(berber.doluSaat()-9);
        kullanici.setRandevuhakki(true);
        kullanici.setBakiye(100-kullanici.bakiyeKontrolEt());;

        simdikisaat = 9;
        this_thread::sleep_for(chrono::seconds(1));
    }
    else{
        cout<<"Berber paranizi iade etmeyi reddetti."<<endl;
        cout<<"Lutfen bir daha randevu saatinize yetisiniz. Iyı gunler.."<<endl;
        cout<<"Gun bitti yeni bir gun basliyor.."<<endl;
        // randevu saatleri düzenlendi randevu hakkı verildi saat başa sardı para geri verilmedi
        berber.setRandevu(berber.doluSaat()-9);
        kullanici.setRandevuhakki(true);
        simdikisaat = 9;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

//daha hazir degil bu tam nasil calisiyor bilmiyom.
bool berbereYetis(Kullanici& kullanici, int mesafeKm, int randevuSaat , Berber& berber) {

    float toplamsaat = 0;
    int tamKisim;
    int dakikaKisim;
    for (int i = 0; i < mesafeKm; ++i) {
        float dakika = rastgeleDakikaBelirle();
        simdikisaat += dakika;
        toplamsaat += dakika;
        //bu kısımda saati ve dakikayı yan yana bastırmak için işelem yapıyor.
        tamKisim = static_cast<int>(simdikisaat);
        dakikaKisim = static_cast<int>((simdikisaat - tamKisim) * 60);

        cout<<"1 km'yi "<<dakika *60<<" dakika icerisinde gittiniz kalan yol: "<< mesafeKm - i<<" km."<<endl;
        cout << "Suanki saat : "<< tamKisim<<"."<<setfill('0')<<setw(2)<<dakikaKisim <<" Randevu saati: "<<randevuSaat<<".00"<< endl<<endl;
        this_thread::sleep_for(chrono::seconds(1));



        if (simdikisaat  > randevuSaat) {
            cout << i + 1 << " km gidildi, toplam " << toplamsaat * 60 << " dakika surdu." << endl;
            cout << "Berbere yetisilemedi. Randevu iptal edildi." << endl;
            cout << "Dukkana bilgilendirme yapiliyor cevap bekleyin lutfen.." << endl;
            //berberin randevu parasını verecek mi vermeyecek mi fonksiyonu eklenecek.
            randevuKacirma(kullanici , berber);
            return true;
        }


    }

    cout << "Berbere basariyla yetisildi!" << endl;
    cout << "Sac kesiminiz basliyor..." << endl;
    //Saç kesim fonksiyonu konulup bir durum geri dönüşü alınabilir.

    return sacKesim(kullanici,berber);
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
                kullanici.setSacmodel(berber.getSacmodel(sacsecim-1));
                break;
            }

        }


        if(!kullanici.getRandevuhakki()){
            cout <<"Randevu basariyla alinmistir randevu saatiniz: "<<saatSecim +8<<":00" <<endl;
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



//MAİN FONKSİYON

int main() {
    srand(time(0));

    int berberrandomsayisi = rand()%5 +3;

    Kullanici kullanici("Kullanici1", 100);
    vector<Berber> berberDukkanlari ;

    for(int i = 0 ; i < berberrandomsayisi;i++){
        //Geçici berber ismi belirleniyor daha sonrasında berber classın içinde otomatik random isim belirleme çalışıyor
        string berberismi = "Berber" + to_string(i);

        Berber berber(berberismi);
        berberDukkanlari.push_back(berber);
    }




    while (true) {
        int secim;//berber dukkani icin secim degeri
        int secim2;//randevu aldiktan sonraki secim menusu icin deger
        if(kullanici.getRandevuhakki()){
            cout << "\nBerber Secimi:" << endl;
            for (size_t i = 0; i < berberDukkanlari.size(); ++i) {
                cout << i + 1 << ". ";
                berberDukkanlari[i].berberDetaylariniGoster();
            }
            cout<<berberDukkanlari.size() + 1<<"- Bakiye kontrol et"<<endl;
            cout << "Seciminizi yapin (0 cikis): ";
            cin >> secim;

            if (secim == 0) {
                break;
            }

            if(secim==berberDukkanlari.size()+1){
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
                if(!berbereYetis(kullanici, berberDukkanlari[secim-1].mesafe , berberDukkanlari[secim-1].doluSaat(), berberDukkanlari[secim-1]))
                    break;
                for(int i = 0 ; i < berberDukkanlari.size() ; i++){
                        berberDukkanlari[i].randmesafe();
                        berberDukkanlari[i].rastgeleIsim();
                }


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

