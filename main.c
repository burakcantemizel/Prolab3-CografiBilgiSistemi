#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAKS_KLAVYE_GIRDI 200

struct AnaSehirDugum {
    int plaka;
    char * isim; //İsimler dinamik bir sekilde olusturuluyor
    char bolge[3]; //Bölge isimleri hep 2 karakter + sonlandırma karakteri
    int komsuSayisi;
    struct AnaSehirDugum * onceki;
    struct AnaSehirDugum * sonraki;
    struct KomsuSehirListe * komsuListesi; // KomsuSehirDüğümleri gosteren ek bir isaretci
};

struct KomsuSehirDugum {
    int plaka;
    struct KomsuSehirDugum * sonraki;
};

struct KomsuSehirListe { // KomsuSehirDugumlerde ilk ve sonu gosteren ek bir isaretci
    struct KomsuSehirDugum * ilk;
    struct KomsuSehirDugum * son;
};

struct AnaSehirDugum * ilkAnaSehir = NULL, *sonAnaSehir = NULL; // Ana Liste tek bir tane oldugu icin ilk ve son isaretcileri

struct AnaSehirDugum * anaSehirDugumOlustur(int plaka, char isim[], char bolge[]) { // Bu fonksiyon yeni bir anaSehirDugum Olusturuyor.
    struct AnaSehirDugum * yeniDugum = (struct AnaSehirDugum *) malloc(sizeof(struct AnaSehirDugum));
    yeniDugum->plaka = plaka;
    strcpy(yeniDugum->bolge, bolge);
    yeniDugum->isim = isim; //!isim degiskenleri disarida olusturuluyor isaretciye ataniyor.
    yeniDugum->komsuListesi = NULL;
    return yeniDugum;
}

void sonaEkle(int plaka, char isim[], char bolge[]) {
    struct AnaSehirDugum * yeniDugum = anaSehirDugumOlustur(plaka,isim,bolge);

    if(ilkAnaSehir == NULL) { //Eğer liste boşsa listeye direkt ekleniyor
        ilkAnaSehir = yeniDugum; // ilk ve son isaretciler kendisini gosteriyor
        sonAnaSehir = yeniDugum;
        ilkAnaSehir->onceki = NULL;
        sonAnaSehir->sonraki = NULL;
    } else { // Eğer liste boş değilse sona ekleme islemi yapiliyor
        sonAnaSehir->sonraki = yeniDugum;
        yeniDugum->onceki = sonAnaSehir; //Çift yönlü liste olduğu için
        sonAnaSehir = yeniDugum;
        sonAnaSehir->sonraki = NULL;
    }
}

void komsuSonaEkle(struct KomsuSehirListe * komsuSehirListe,int plaka) {
    struct KomsuSehirDugum * yeniDugum = malloc(sizeof(struct KomsuSehirDugum));
    yeniDugum->plaka = plaka;

    if(komsuSehirListe->ilk == NULL) {
        komsuSehirListe->ilk = yeniDugum;
        komsuSehirListe->son = yeniDugum;
        komsuSehirListe->son->sonraki = NULL;
    } else {
        komsuSehirListe->son->sonraki = yeniDugum;
        komsuSehirListe->son = yeniDugum;
        komsuSehirListe->son->sonraki = NULL;
    }
}

void basaEkle(int plaka, char isim[], char bolge[]) {
    struct AnaSehirDugum * yeniDugum = anaSehirDugumOlustur(plaka,isim,bolge);

    if(ilkAnaSehir == NULL) {
        ilkAnaSehir = yeniDugum;
        ilkAnaSehir->sonraki = NULL;
        ilkAnaSehir->onceki = NULL;
        sonAnaSehir = ilkAnaSehir;
    } else {
        yeniDugum->sonraki = ilkAnaSehir;
        ilkAnaSehir->onceki = yeniDugum;
        ilkAnaSehir = yeniDugum;
    }
}

void komsuBasaEkle(struct KomsuSehirListe * komsuSehirListe, int plaka) {
    struct KomsuSehirDugum * yeniDugum = malloc(sizeof(struct KomsuSehirDugum));
    yeniDugum->plaka = plaka;

    if(komsuSehirListe->ilk == NULL) {
        komsuSehirListe->ilk = yeniDugum;
        komsuSehirListe->son = yeniDugum;
        komsuSehirListe->son->sonraki = NULL;
    } else {
        yeniDugum->sonraki = komsuSehirListe->ilk;
        komsuSehirListe->ilk = yeniDugum;
    }
}

void siraliEkle(int plaka, char isim[], char bolge[]) {
    struct AnaSehirDugum * yeniDugum = anaSehirDugumOlustur(plaka,isim,bolge);

    if(ilkAnaSehir == NULL) {
        ilkAnaSehir = yeniDugum;
        sonAnaSehir = yeniDugum;
        sonAnaSehir->sonraki = NULL;
        sonAnaSehir->onceki = NULL;
    } else {
        if(yeniDugum->plaka < ilkAnaSehir->plaka) {
            basaEkle(plaka,isim,bolge);
        } else if(yeniDugum->plaka > sonAnaSehir->plaka) {
            sonaEkle(plaka,isim,bolge);
        } else {
            struct AnaSehirDugum * gezginDugum;
            gezginDugum = ilkAnaSehir;

            while(gezginDugum->sonraki->plaka < yeniDugum->plaka) {
                gezginDugum = gezginDugum->sonraki;
            }

            yeniDugum->sonraki = gezginDugum->sonraki;
            yeniDugum->onceki = gezginDugum;
            gezginDugum->sonraki = yeniDugum;
            gezginDugum->sonraki->onceki = yeniDugum;
        }
    }
}

void komsuSiraliEkle(struct KomsuSehirListe * komsuSehirListe, int plaka) {
    struct KomsuSehirDugum * yeniDugum = malloc(sizeof(struct KomsuSehirDugum));
    yeniDugum->plaka = plaka;

    if(komsuSehirListe->ilk == NULL) {
        komsuSehirListe->ilk = yeniDugum;
        komsuSehirListe->son = yeniDugum;
        komsuSehirListe->son->sonraki = NULL;
    } else {
        if(yeniDugum->plaka < komsuSehirListe->ilk->plaka) {
            komsuBasaEkle(komsuSehirListe, plaka);
        } else if(yeniDugum->plaka > komsuSehirListe->son->plaka) {
            komsuSonaEkle(komsuSehirListe, plaka);
        } else {
            struct KomsuSehirDugum * gezginDugum = komsuSehirListe->ilk;
            while(gezginDugum->sonraki->plaka < yeniDugum->plaka) {
                gezginDugum = gezginDugum->sonraki;
            }
            yeniDugum->sonraki = gezginDugum->sonraki;
            gezginDugum->sonraki = yeniDugum;
        }
    }


}

struct AnaSehirDugum * plakaAra(int plaka) {
    struct AnaSehirDugum * aranacak;
    aranacak = ilkAnaSehir;

    while(aranacak != NULL) {
        if(aranacak->plaka == plaka) {
            return aranacak;
        }

        aranacak = aranacak->sonraki;
    }

    return NULL;
}

struct AnaSehirDugum * isimAra(char * isim) {
    struct AnaSehirDugum * aranacak;
    aranacak = ilkAnaSehir;

    while(aranacak != NULL) {
        if(strcasecmp(isim, aranacak->isim) == 0) {
            return aranacak;
        }

        aranacak = aranacak->sonraki;
    }
    return NULL;
}

struct KomsuSehirDugum * komsuPlakaAra(struct KomsuSehirListe * komsuListesi,int plaka) {
    struct KomsuSehirDugum * aranacak = komsuListesi->ilk;

    while(aranacak != NULL) {
        if(aranacak->plaka == plaka) {
            return aranacak;
        }
        aranacak = aranacak->sonraki;
    }
    return NULL;
}

void komsuYazdir(struct KomsuSehirListe * komsuSehirListe) {
    if(komsuSehirListe != NULL) {
        struct KomsuSehirDugum * gezginDugum = komsuSehirListe->ilk;
        while(gezginDugum != NULL) {
            printf("%d ", gezginDugum->plaka);
            gezginDugum = gezginDugum->sonraki;
        }
    }
}

void ciktiYazdir() {
    struct AnaSehirDugum * gezginDugum;
    gezginDugum = ilkAnaSehir;

    while(gezginDugum != NULL) {
        printf("%d %s %s ", gezginDugum->plaka, gezginDugum->isim, gezginDugum->bolge);

        komsuYazdir(gezginDugum->komsuListesi);
        printf("Komsu Sayisi: %d", gezginDugum->komsuSayisi);

        printf("\n");
        gezginDugum = gezginDugum->sonraki;
    }
}

void sehirBilgiGoster(struct AnaSehirDugum * sehir) {
    printf("Plaka: %d\n",sehir->plaka);
    printf("Isim: %s\n",sehir->isim);
    printf("Bolge: %s\n",sehir->bolge);
}

void sil(int plaka) {
    struct AnaSehirDugum * silinecek = ilkAnaSehir; //Listenin ilk elemanını silinecek olarak belirliyoruz
    struct AnaSehirDugum * onceki = NULL; //Baslangicta onceki null

    while(silinecek != NULL) { // Liste bos degilse
        if(silinecek->plaka == plaka) {
            break; //İlk eleman silinecek ise breakleyip silinecegi degistirmiyoruz ilk eleman olarak kaliyor
        } else {
            onceki = silinecek; //Eger ilk eleman degilse silinecegi ilerletiyoruz oncekied onun bir arkasindaki dugum oluyor
            silinecek = silinecek->sonraki; //silinecek olan dugum tespit ediliyor
        }
    }
    if(silinecek != NULL) { //Silme islemi icin dugumun null olmamasi gerek
        if(silinecek == ilkAnaSehir) { //Eger ilk dugumde kalinmissa ilk dugum silinecekse
            ilkAnaSehir = ilkAnaSehir->sonraki;
            ilkAnaSehir->onceki = NULL;
        } else if(silinecek == sonAnaSehir) { // Eger son dugumde kalinmissa son dugum silinecekse
            sonAnaSehir = onceki;
            onceki->sonraki = NULL;
        } else { //Arada bir dugumde kalinmissa arada bir dugum silinecekse
            silinecek->sonraki->onceki = onceki;
            onceki->sonraki = silinecek->sonraki;
        }
        free(silinecek);
    }
}

void komsuSil(struct KomsuSehirListe * komsuSehirListe, int plaka) {
    struct KomsuSehirDugum * silinecek = komsuSehirListe->ilk;
    struct KomsuSehirDugum * onceki = NULL;

    while(silinecek != NULL) { //Liste boþ deðilse
        if(silinecek->plaka == plaka) {
            break; //Ýlk silinecekse onceki null kalýyor silinecek ilkanasehir oluyor
        } else {
            onceki = silinecek;
            silinecek = silinecek->sonraki; //silinecek olan dugum tespit ediliyor
        }
    }
    if(silinecek != NULL) {
        if(silinecek == komsuSehirListe->ilk) {
            komsuSehirListe->ilk = komsuSehirListe->ilk->sonraki;
        } else if(silinecek == komsuSehirListe->son) {
            komsuSehirListe->son = onceki;
            komsuSehirListe->son->sonraki = NULL;
        } else {
            onceki->sonraki = silinecek->sonraki;
        }
        free(silinecek);
    }
}

FILE * dosya; // sehirler.txt dosya degiskeni
FILE * dosya_cikti; // cikti.txt dosya degiskeni

void dosyaOkuListeOlustur() {
    char satir[MAKS_KLAVYE_GIRDI];
    const char * ayrac = ",";
    int kelimeSayisi = 0;
    int plaka;
    char * isim;
    char bolge[3];

    if( (dosya = fopen("sehirler.txt", "r")) == NULL) {
        printf("Dosya acilirken bir sorun olustu.\n");
        exit(1);
    }

    while( fgets(satir,MAKS_KLAVYE_GIRDI, dosya) != NULL) {
        if(satir[strlen(satir)-1] == '\n') {
            satir[strlen(satir)-1] = '\0';
        }

        kelimeSayisi = 0;
        char * kelime = strtok(satir,ayrac);
        kelimeSayisi++;
        plaka = atoi(kelime);
        while(kelime != NULL) {
            kelime = strtok(NULL,ayrac);
            kelimeSayisi++;

            if(kelimeSayisi == 2) {
                isim = (char *)malloc(sizeof(char) * (strlen(kelime)+1));
                strcpy(isim, kelime);
            }

            if(kelimeSayisi == 3) {
                strcpy(bolge, kelime);
            }
        }
        siraliEkle(plaka,isim,bolge);
    }
    fclose(dosya);
}

void dosyaOkuKomsuOlustur() {
    char satir[MAKS_KLAVYE_GIRDI];
    const char * ayrac = ",";
    int kelimeSayisi = 0;
    int plaka;

    if( (dosya = fopen("sehirler.txt", "r")) == NULL) {
        printf("Dosya acilirken bir sorun olustu.\n");
        exit(1);
    }

    while( fgets(satir,MAKS_KLAVYE_GIRDI, dosya) != NULL) {
        if(satir[strlen(satir)-1] == '\n') {
            satir[strlen(satir)-1] = '\0';
        }

        kelimeSayisi = 0;
        char * kelime = strtok(satir,ayrac);
        plaka = atoi(kelime);
        kelimeSayisi++;

        struct KomsuSehirListe * yeniKomsuListe;
        yeniKomsuListe = malloc(sizeof(struct KomsuSehirListe));
        yeniKomsuListe->ilk = NULL;
        yeniKomsuListe->son = NULL;


        while(kelime != NULL) {
            if(kelimeSayisi > 3) {
                komsuSiraliEkle(yeniKomsuListe,isimAra(kelime)->plaka);
            }

            kelime = strtok(NULL,ayrac);
            kelimeSayisi++;

        }
        plakaAra(plaka)->komsuListesi = yeniKomsuListe;
        plakaAra(plaka)->komsuSayisi = kelimeSayisi - 4; // plaka,isim,bolge + 1 de fazladan sayac donuyor
    }
    fclose(dosya);
}

void ciktiDosyaYazdir() {
    //printf("\n>> Mevcut guncel cikti dosyaya yazdirildi...\n\n");

    if( (dosya_cikti = fopen("cikti.txt", "w")) == NULL) {
        printf("Dosya acilirken bir sorun olustu.\n");
        exit(1);
    }

    struct AnaSehirDugum * gezginDugum;
    gezginDugum = ilkAnaSehir;

    while(gezginDugum != NULL) {
        fprintf(dosya_cikti,"Plaka: %d\n",gezginDugum->plaka);
        fprintf(dosya_cikti,"Isim: %s ",gezginDugum->isim);

        struct KomsuSehirDugum * gezginDugum2;
        gezginDugum2 = gezginDugum->komsuListesi->ilk;

        while(gezginDugum2 != NULL) {
            fprintf(dosya_cikti,"-> %d ", gezginDugum2->plaka);
            gezginDugum2 = gezginDugum2->sonraki;
        }

        fprintf(dosya_cikti,"\nBolge: %s\n",gezginDugum->bolge);

        fprintf(dosya_cikti,"Komsu Sayisi: %d\n",gezginDugum->komsuSayisi);

        if(gezginDugum->sonraki != NULL) {
            fputs("| |\n| |",dosya_cikti);
            fputs("\n",dosya_cikti);
        }
        gezginDugum = gezginDugum->sonraki;
    }


    fclose(dosya_cikti);
}

char girdi_cevap[MAKS_KLAVYE_GIRDI];
int girdi_plaka;
char girdi_arananisim[MAKS_KLAVYE_GIRDI];

void sehirEkle() {
    char girdi_isim[MAKS_KLAVYE_GIRDI];
    char girdi_bolge[3];
    int girdi_plaka;

    printf("\nEklemek istediginiz sehrin adini giriniz >> ");
    scanf("%s",girdi_isim);
    printf("Eklemek istediginiz sehrin plakasini giriniz >> ");
    scanf("%d",&girdi_plaka);
    printf("Eklemek istediginiz sehrin bolgesini giriniz >> ");
    scanf("%s",girdi_bolge);

    if( plakaAra(girdi_plaka) != NULL || isimAra(girdi_isim) != NULL ) {
        if( plakaAra(girdi_plaka) != NULL )
            printf("\nBu plakaya sahip bir sehir zaten mevcut!\n");
        if(isimAra(girdi_isim) != NULL)
            printf("\nBu isime sahip bir sehir zaten mevcut!\n");
    } else {
        char * isim = malloc(sizeof(girdi_isim));
        strcpy(isim,girdi_isim);
        siraliEkle(girdi_plaka,isim,girdi_bolge);
        struct KomsuSehirListe * yeniKomsuListe;
        yeniKomsuListe = malloc(sizeof(struct KomsuSehirListe));
        yeniKomsuListe->ilk = NULL;
        yeniKomsuListe->son = NULL;
        plakaAra(girdi_plaka)->komsuListesi = yeniKomsuListe;
        printf("\nSehir listeye eklendi.\n");
    }

    printf("\n");

}

void komsulukEkle() {
    char girdi_isim[MAKS_KLAVYE_GIRDI];
    char girdi_komsu[MAKS_KLAVYE_GIRDI];

    printf("\nYeni komsuluk eklemek istediginiz sehrin adini giriniz >> ");
    scanf("%s",girdi_isim);

    if(isimAra(girdi_isim) == NULL) {
        printf("\nSehir listede yok eklemek ister misiniz? (Eklemek icin evet yaziniz.)\n>> ");
        scanf("%s",girdi_cevap);
        if(strcasecmp(girdi_cevap,"evet") == 0) {
            sehirEkle();
            return;
        }
    } else {

        printf("Bu sehire eklemek istediginiz komsu sehrin ismini giriniz >> ");
        scanf("%s",girdi_komsu);

        if(strcasecmp(girdi_isim, girdi_komsu) == 0) {
            printf("\nBir sehir kendisiyle komsu olamaz!\n\n");
            return;
        }

        if(isimAra(girdi_komsu) == NULL) {
            printf("\nSehir listede yok eklemek ister misiniz? (eklemek icin evet yaziniz.)\n>> ");
            scanf("%s",girdi_cevap);
            if(strcasecmp(girdi_cevap,"evet") == 0) {
                sehirEkle();
                return;
            }
        } else {

            if( komsuPlakaAra( isimAra(girdi_isim)->komsuListesi, isimAra(girdi_komsu)->plaka) == NULL ) {
                komsuSiraliEkle(isimAra(girdi_isim)->komsuListesi, isimAra(girdi_komsu)->plaka);
                isimAra(girdi_isim)->komsuSayisi += 1;

                komsuSiraliEkle(isimAra(girdi_komsu)->komsuListesi, isimAra(girdi_isim)->plaka);
                isimAra(girdi_komsu)->komsuSayisi += 1;
                printf("\nKomsuluk eklendi.\n");
            } else {
                printf("\nBu sehir zaten bu komsuya sahip!\n");
            }

        }

    }
    printf("\n");
}

void bonus(){
           //- Belli bir sayı aralığında komşu sayısına sahip şehirlerden belirli ortak komşulara sahip olan şehirlerin listelenmesi
            //(Örneğin: Komşu sayısı 3 ile 7 arasında olan illerden hem Ankara hem de Konya’ya komşu olan şehirler: Aksaray, Eskişehir) (+10p)
            int hata = 0;
            int altsinir;
            int ustsinir;
            int ortak_komsu_adeti;
            int komsu_sayac = 0;
            //char girdi_ortak_komsu[200];
            //char * ortak_komsu_dizisi = malloc(sizeof(MAKS_KLAVYE_GIRDI));

            printf("Hangi degerden fazla sayida komsuya sahip sehirleri filtrelemek istersiniz? >> ");
            scanf("%d",&altsinir);
            printf("\nHangi degerden az sayida komsuya sahip sehirleri filtrelemek istersiniz? >> ");
            scanf("%d",&ustsinir);
            printf("\nFiltrelemek istediginiz ortak komsu adetini giriniz >> ");
            scanf("%d",&ortak_komsu_adeti);

            char ortak_komsular[ortak_komsu_adeti][MAKS_KLAVYE_GIRDI];

            //ortak_komsu_dizisi = (char *)realloc(ortak_komsu_dizisi, ortak_komsu_adeti * sizeof(MAKS_KLAVYE_GIRDI));

            while(komsu_sayac < ortak_komsu_adeti) {

                printf("\nOrtak komsu yaziniz >> ");
                scanf("%s",ortak_komsular[komsu_sayac]);

                if(isimAra(ortak_komsular[komsu_sayac]) == NULL) {
                    printf("\nBoyle bir sehir bulunmamaktadir!\n\n");
                    hata = 1;
                    break;
                }
                //strcpy(ortak_komsu_dizisi + (komsu_sayac) * sizeof(girdi_ortak_komsu), girdi_ortak_komsu);
                komsu_sayac += 1;

            }

            if(hata == 0) {
                printf("\n");
                komsu_sayac = 0;

                struct AnaSehirDugum * gezginDugum = ilkAnaSehir;
                while(gezginDugum != NULL) {
                    if(gezginDugum->komsuSayisi >= altsinir && gezginDugum->komsuSayisi <= ustsinir) {
                        int bulunan_ortak = 0;
                        int i;
                        for(i = 0; i < ortak_komsu_adeti; i++) {
                            struct KomsuSehirDugum * gezginDugum2;
                            gezginDugum2 = gezginDugum->komsuListesi->ilk;
                            while(gezginDugum2 != NULL) {

                                if(gezginDugum2->plaka == isimAra(ortak_komsular[i])->plaka ) {
                                    bulunan_ortak += 1;
                                }
                                gezginDugum2 = gezginDugum2->sonraki;
                            }

                        }

                        if(bulunan_ortak == ortak_komsu_adeti) {
                            printf("%d %s %s ", gezginDugum->plaka, gezginDugum->isim, gezginDugum->bolge);
                            komsuYazdir(gezginDugum->komsuListesi);
                            printf("Komsu sayisi: %d \n", gezginDugum->komsuSayisi);
                        }
                    }
                    gezginDugum = gezginDugum->sonraki;
                }
                printf("\n");
            }
}

int main() {
    dosyaOkuListeOlustur();
    dosyaOkuKomsuOlustur();

    printf("Cografi Bilgi Sistemi\n\n");
    printf(">> \"sehirler.txt\" okundu ve bagli liste olusturuldu.\n");
    printf(">> \"cikti.txt\" her islemden sonra otomatik olarak guncellenmektedir.\n\n");

    int islem;
    int aramaturu;
    int altsinir;
    int ustsinir;

    int girdi_silinecek_komsu_plaka;

    while(1) {
        ciktiDosyaYazdir();
        printf("Islem Menusu:\n");
        printf("1 - Mevcut modeli ekrana yazdir\n");
        printf("2 - Yeni sehir veya komsuluk ekle\n");
        printf("3 - Sehir arat ve bilgilerini goster\n");
        printf("4 - Bolgeye gore sehir filtrele\n");
        printf("5 - Sehir veya komsuluk sil\n");
        printf("6 - Komsu sayisina gore sehir filtrele\n");
        printf("7 - Komsu sayisina ve ortak sehirlere gore sehir filtrele(Bonus)\n");
        printf("8 - Cikis\n\n");

        printf("Gerceklestirmek istediginiz islemi giriniz >> ");
        scanf("%d",&islem);
        printf("\n");

        switch(islem) {
        case 1: // Ekrana cikti basiliyor
            ciktiYazdir();
            printf("\n");
            break;

        case 2: // Yeni sehir, komsuluk ekleme
            printf("1 - Yeni bir sehir ekle \n2 - Mevcut bir sehire komsuluk ekle\n\nGerceklestirmek istediginiz islemi giriniz >> ");
            scanf("%d",&islem);

            if(islem == 1) {
                sehirEkle();
            } else if(islem == 2) {
                komsulukEkle();
            } else {
                printf("\nGecersiz islem!\n\n");
            }
            break;

        case 3:
            printf("1 - Plaka ile arama\n2 - Isim ile arama\n\nGerceklestirmek istediginiz islemi giriniz >> ");
            scanf("%d",&aramaturu);
            if(aramaturu == 1) {
                printf("\nPlaka giriniz >> ");
                int arananplaka;
                scanf("%d",&arananplaka);

                if(plakaAra(arananplaka) != NULL) {
                    printf("\nSehir Bilgileri: \n");
                    sehirBilgiGoster(plakaAra(arananplaka));
                    printf("Komsu sayisi: %d\n", plakaAra(arananplaka)->komsuSayisi);
                    printf("\nKomsu Sehirlerin Bilgileri:\n");

                    struct KomsuSehirDugum * gezginDugum;
                    gezginDugum = plakaAra(arananplaka)->komsuListesi->ilk;
                    while(gezginDugum != NULL) {
                        sehirBilgiGoster(plakaAra(gezginDugum->plaka));
                        printf("\n");

                        gezginDugum = gezginDugum->sonraki;
                    }
                } else {
                    printf("\nSehir listede yok eklemek ister misiniz?(Eklemek icin evet yaziniz.)\n>> ");
                    scanf("%s",girdi_cevap);
                    if(strcasecmp(girdi_cevap,"evet") == 0) {
                        sehirEkle();
                    }
                }
            } else if(aramaturu == 2) {
                printf("\nIsim giriniz >> ");
                scanf("%s",girdi_arananisim);

                if(isimAra(girdi_arananisim) != NULL) {
                    printf("\nSehir Bilgileri: \n");
                    sehirBilgiGoster(isimAra(girdi_arananisim));
                    printf("Komsu sayisi: %d\n", isimAra(girdi_arananisim)->komsuSayisi);

                    printf("\nKomsu Sehirlerin Bilgileri:\n");

                    struct KomsuSehirDugum * gezginDugum;
                    gezginDugum = isimAra(girdi_arananisim)->komsuListesi->ilk;
                    while(gezginDugum != NULL) {
                        sehirBilgiGoster(plakaAra(gezginDugum->plaka));
                        printf("\n");

                        gezginDugum = gezginDugum->sonraki;
                    }
                } else {
                    printf("\nSehir listede yok eklemek ister misiniz?(Eklemek icin evet yaziniz.)\n>> ");
                    scanf("%s",girdi_cevap);
                    if(strcasecmp(girdi_cevap,"evet") == 0) {
                        sehirEkle();
                    }
                }
            } else {
                printf("\nGecersiz islem!\n");
            }

            printf("\n");
            break;

        case 4:
            printf("Ege - EG\nMarmara - MA\nAkdeniz - AK\nKaradeniz - KA\nIc Anadolu - IA\nDogu Anadolu - DA\nGuneydogu Anadolu - GA\n\n");
            printf("Filtreleme yapacaginiz bolgenin 2 karakterlik kodunu giriniz >> ");
            char arananbolge[3];
            scanf("%s",arananbolge);
            printf("\n");

            struct AnaSehirDugum * gezginDugum;
            gezginDugum = ilkAnaSehir;

            while(gezginDugum != NULL) {
                if(strcasecmp(gezginDugum->bolge,arananbolge) == 0) {
                    printf("%d %s %s \n", gezginDugum->plaka, gezginDugum->isim, gezginDugum->bolge);
                }

                gezginDugum = gezginDugum->sonraki;
            }

            printf("\n\n");

            break;

        case 5:
            printf("1 - Bir sehri sil\n2 - Bir sehrin komsulugunu sil\n\nGerceklestirmek istediginiz islemi giriniz >> ");
            scanf("%d",&islem);

            if(islem == 1) {
                //Sehir veya komsuluk silme
                printf("\nSilmek istediginiz sehrin plakasini giriniz >> ");
                scanf("%d",&girdi_plaka);

                if(plakaAra(girdi_plaka) == NULL) {
                    printf("\nBoyle bir sehir bulunmamaktadir!\n\n");
                } else {
                    sil(girdi_plaka);

                    //Sehiri sildikten sonra onun komsu oldugu tüm illerdende sehiri silmemiz gerek
                    gezginDugum = ilkAnaSehir;

                    while(gezginDugum != NULL) {
                        struct KomsuSehirListe * komsuSehirListe = gezginDugum->komsuListesi;
                        if(komsuSehirListe != NULL) {
                            struct KomsuSehirDugum * gezginDugum2 = komsuSehirListe->ilk;
                            while(gezginDugum2 != NULL) {
                                //Burada gezginDugum2 bize komsu plakaları tek tek geziyor.
                                if(gezginDugum2->plaka == girdi_plaka) { //Eğer silincek şehir varsa o komşu listeden silcez
                                    komsuSil(gezginDugum->komsuListesi, girdi_plaka);
                                    gezginDugum->komsuSayisi -= 1; //Komsu sayisini da güncelliyoruz.
                                }
                                gezginDugum2 = gezginDugum2->sonraki;
                            }
                        }
                        gezginDugum = gezginDugum->sonraki;
                    }

                    printf("\nSehir silindi.\n\n");
                }
            } else if(islem == 2) {
                printf("\nKomsulugunu silmek istediginiz sehrin plakasini giriniz >> ");
                scanf("%d",&girdi_plaka);
                if(plakaAra(girdi_plaka) == NULL) {
                    printf("\nBoyle bir sehir bulunmamaktadir!\n\n");
                    break;
                }
                printf("\nSilmek istediginiz komsu sehrin plakasini giriniz >> ");
                scanf("%d",&girdi_silinecek_komsu_plaka);

                if(komsuPlakaAra(plakaAra(girdi_plaka)->komsuListesi,girdi_silinecek_komsu_plaka) == NULL) {
                    printf("\nSilmek istediginiz komsu sehir bulunamadi!\n\n");
                } else {
                    struct KomsuSehirDugum * gezginDugum3;
                    gezginDugum3 = plakaAra(girdi_plaka)->komsuListesi->ilk;

                    while(gezginDugum3 != NULL) {
                        if(gezginDugum3->plaka == girdi_silinecek_komsu_plaka) {
                            komsuSil(plakaAra(girdi_plaka)->komsuListesi,girdi_silinecek_komsu_plaka);
                            plakaAra(girdi_plaka)->komsuSayisi -= 1;

                            komsuSil(plakaAra(girdi_silinecek_komsu_plaka)->komsuListesi, girdi_plaka);
                            plakaAra(girdi_silinecek_komsu_plaka)->komsuSayisi -= 1;
                        }
                        gezginDugum3 = gezginDugum3->sonraki;
                    }
                    printf("\nKomsuluk silindi.\n\n");
                }

            } else {
                printf("\nGecersiz islem!\n\n");
            }

            break;

        case 6:
            printf("1 - Belli bir degere esit ya da fazla komsuya sahip sehirleri filtrele\n");
            printf("2 - Belli bir degere esit ya da daha az komsuya sahip sehirleri filtrele\n");
            printf("3 - Belli iki degere esit ve arasinda komsu sayisina sahip sehirleri filtrele\n\n>> ");
            scanf("%d",&aramaturu);

            switch(aramaturu) {
            case 1:
                printf("\nHangi degerden fazla sayida komsuya sahip sehirleri filtrelemek istersiniz? >> ");
                scanf("%d",&altsinir);
                printf("\n");
                struct AnaSehirDugum * gezginDugum = ilkAnaSehir;
                while(gezginDugum != NULL) {
                    if(gezginDugum->komsuSayisi >= altsinir) {
                        printf("%d %s %s ", gezginDugum->plaka, gezginDugum->isim, gezginDugum->bolge);
                        komsuYazdir(gezginDugum->komsuListesi);
                        printf("Komsu sayisi: %d \n", gezginDugum->komsuSayisi);
                    }
                    gezginDugum = gezginDugum->sonraki;
                }
                printf("\n");
                break;

            case 2:
                printf("\nHangi degerden az sayida komsuya sahip sehirleri filtrelemek istersiniz? >> ");
                scanf("%d",&ustsinir);
                printf("\n");
                gezginDugum = ilkAnaSehir;
                while(gezginDugum != NULL) {
                    if(gezginDugum->komsuSayisi <= ustsinir) {
                        printf("%d %s %s ", gezginDugum->plaka, gezginDugum->isim, gezginDugum->bolge);
                        komsuYazdir(gezginDugum->komsuListesi);
                        printf("Komsu sayisi: %d \n", gezginDugum->komsuSayisi);
                    }
                    gezginDugum = gezginDugum->sonraki;
                }
                printf("\n");
                break;

            case 3:
                printf("\nHangi degerden fazla sayida komsuya sahip sehirleri filtrelemek istersiniz? >> ");
                scanf("%d",&altsinir);
                printf("\nHangi degerden az sayida komsuya sahip sehirleri filtrelemek istersiniz? >> ");
                scanf("%d",&ustsinir);

                printf("\n");
                gezginDugum = ilkAnaSehir;
                while(gezginDugum != NULL) {
                    if(gezginDugum->komsuSayisi >= altsinir && gezginDugum->komsuSayisi <= ustsinir) {
                        printf("%d %s %s ", gezginDugum->plaka, gezginDugum->isim, gezginDugum->bolge);
                        komsuYazdir(gezginDugum->komsuListesi);
                        printf("Komsu sayisi: %d \n", gezginDugum->komsuSayisi);
                    }
                    gezginDugum = gezginDugum->sonraki;
                }
                printf("\n");
                break;

            default:
                printf("\nGecersiz islem.\n\n");
                break;
            }

            break;

        case 7:
            bonus();
            break;

        case 8:
            exit(0);
            break;
        }//switch
    }//while
    return 0;
}//main
