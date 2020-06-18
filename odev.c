#include <stdio.h>
#include <time.h>

/*************************************************************************
	Parametre olarak gelen sayiyi basamaklarina ayirarak char dizisine 
	yazar ve bu diziyi geri dondurur. Basamaklara ayirmak mod 10 islemi 
	uygulanarak en dusuk degerlikli basamaktaki rakam elde edilir. Siradaki 
	basamagin carpanini bulmak icin bir onceki icin basamagin degeri 
	rasgeleSayi'dan cikartilir. 
	
**************************************************************************/
char *sayiyiBasamaklaraAyir(int rasgeleSayi) {

	// Rakamlari basamak degerlerine gore ayristir
	char r1 = rasgeleSayi % 10;
	char r2 = ((rasgeleSayi - r1) / 10) % 10;
	char r3 = ((rasgeleSayi - r1 - r2 * 10) / 100) % 10;
	char r4 = ((rasgeleSayi - r1 - r2 * 10 - r3 * 100) / 1000) % 10;	

	char basamaklar[4];
	basamaklar[0] = r1;
	basamaklar[1] = r2;
	basamaklar[2] = r3;
	basamaklar[3] = r4;
	
	return basamaklar;
}

/***************************************************************************
  Parametre olarak verilan sayiyi (sayi) char tipli bir diziye 
  aktararak basamaklarina ayirir ve ardindan kriterleri saglayip saglamadigina 
  bakar. Sartlar saglaniyorsa baslangicta 0 degerine sahip tumSartlarUygun 
  char degiskeninin degerini 1 olarak ayarlar ve geri dondurur.
  
*****************************************************************************/
char sayiKriterlereUygunMu(int sayi) {
	
	char *basamaklar;
	char r1, r2, r3, r4;

	basamaklar = sayiyiBasamaklaraAyir(sayi);
	r1 = basamaklar[0];
	r2 = basamaklar[1];
	r3 = basamaklar[2];
	r4 = basamaklar[3];
	
	// Sartlari kontrol et
	char tumSartlarUygun = 0;
	
	// Ilk rakam 0 olamaz
	if (r1 != 0)
		// Hicbir rakam birbirinin ayni olamaz
		if (r1 != r2 && r1 != r3 && r1 != r4)
			if (r2 != r3 && r2 != r4)
				if (r3 != r4)
					tumSartlarUygun = 1;
	
	return tumSartlarUygun;
}

/****************************************************************************
Bu fonksiyon kritelere uygun bir sayi uretir. rand() ile sayi uretmeden once
srand ile rasgele sayi ureteci karistirilir. Boylece daha rastlantisal 
degerlerin uretilmesi mumkun olur. Rastlantisalligi artirmak icin kullanilan 
deger mevcut sistem zamaninin ve bir onceki adimda uretilen rasgele degerin 
toplami alinarak belirlenmistir.

	// Kriteler:
	// - 0 ile baslamayacak
	// - rakamlari birbirinden farkli 4 haneli olacak
	
*****************************************************************************/
int sayiUret() {
		
	// ******************************
	int rasgeleSayiUret(int rasgele) {
		
		// Rasgele sayi uretecini onyukle	
		srand(time(0)+rasgele);
		
		// min=1000, max=9999 araliginda bir sayi uret.
		// rand() degerini araliga indirgemek icin % modulunu al.
		int rasgeleSayi = 1000 + (rand() % (9999 - 1000 + 1));		
		
		// Tum sartlar uygunsa dondur	
		if (sayiKriterlereUygunMu(rasgeleSayi) == 1)
			return (int) rasgeleSayi;
		
		// Sartlar saglanmadiysa yeni sayi uret
		else
			rasgeleSayiUret(rasgeleSayi);
	}
			
	// Recursive rasgele ureteci cagir
	int sayi = rasgeleSayiUret(9999);
	
	return sayi;
}

/*****************************************************************************
  Kullanicidan bir sayi tahmin ederek giris yapmasini ister.
  Tahmin edilen sayi kriterlere uygunsa geri dondurulur.
  Degilse sayiIste_ fonksitonu ozyinelemeli (recursive) olarak yeniden cagrilir.
	Kriteler:
	- 0 ile baslamayacak
	- rakamlari birbirinden farkli 4 haneli olacak
	
******************************************************************************/
int sayiIste() {

	// ************
	int sayiIste_() {	
		
		int tahmin;	
		printf("Bir sayi giriniz: ");
		scanf("%d", &tahmin);
		
		if (sayiKriterlereUygunMu(tahmin) == 1)
			return tahmin;
		else {
			printf("Girilen sayi kriterlere uygun degil.\n");
			sayiIste_();
		}				
	}
	return sayiIste_();
}

/********************************************************************************
  Bilgisayarin tuttugu sayiyi (rasgele) ve oyuncunun tahmin (tahmin) ettigi
  sayilari basamaklarina ayirarak basamaklari karsilastirir.
  Iki sayida da ayni degerde olan basamaklar icin arti degiskeninin
  degerini 1 artitir. Farkli olanlar icin 1 eksiltir ve eksi degiskenine kaydeder.
  Ozel durum olarak; Eger eksi 4 degerine sahipse "Eslesen kayit yok" mesajini yazar.
  Diger durumlarda "%d arti, %d eksi" formatinda eslesme durumunu yazar.
    
*********************************************************************************/	
int sayiKontrol(int rasgele, int tahmin) {
	char *r_basamaklar;
	char *t_basamaklar; 
	int arti = 0, eksi = 0, i;
	
	char r1, r2, r3, r4;
	r_basamaklar = sayiyiBasamaklaraAyir(rasgele);
	r1 = r_basamaklar[0];
	r2 = r_basamaklar[1];
	r3 = r_basamaklar[2];
	r4 = r_basamaklar[3];
	
	char t1, t2, t3, t4;
	t_basamaklar = sayiyiBasamaklaraAyir(tahmin);
	t1 = r_basamaklar[0];
	t2 = r_basamaklar[1];
	t3 = r_basamaklar[2];
	t4 = r_basamaklar[3];
	
	if (r1 == t1) arti++; else eksi++;
	if (r2 == t2) arti++; else eksi++;
	if (r3 == t3) arti++; else eksi++;
	if (r4 == t4) arti++; else eksi++;
		
	if (eksi == 4)
		printf("Eslesen kayit yok.\n");
	else
		printf("%d arti, %d eksi\n", arti, eksi);
		
	return arti;	
}

/******************************************************
 Bu fonksiyon eslesenSayisi 4 ise
 "Sayi bulundu, tebrikler" mesajini ekrana basar ve
 geriye 0 dondurur. Aksi halde 1 dondurerek
 ana dongunun devam etmesini saglar.
*******************************************************/
char oyunBittimi(char eslesenSayisi) {
	
	if (eslesenSayisi == 4) {
		printf("Sayi bulundu, tebrikler.\n");
		return 0;
	} else
		return 1;
}

/*********************************************************************
	Ana program bir rasgele sayi ureteci ile 
	dongu icinde calisan 3 alt programdan olusur.
	Alt programlarin gorevleri sunlardir:
	
	- sayiUret: Oyun baslangicinda rakamlari birbirinden 
		farkli 4 basamakli sayi üretir.
		
	- sayiIste: Kullanicidan sayi ister ve girilen 
		sayiyi basamaklarina ayirir.
		
	- sayiKontrol: Girilen sayi ve tutulan sayi arasinda 
		karsilastirma yaparak dönüt verir.
		
	- oyunBittimi: Kullanicinin dogru sayiyi bulmasi 
		durumunda oyunun bittigini belirterek programi 
		bitirir fonksiyondur.
		
********************************************************************/
int main() {
	
	// Kullanilacak degiskenleri tanimla
	int rasgele, tahmin, eslesenSayisi;
	
	// Kriterlere uygun rasgele sayi uret
	// Kriteler:
	// - 0 ile baslamayacak
	// - rakamlari birbirinden farkli 4 haneli olacak
	rasgele = sayiUret();
	
	// Donguye basla
	do {	
		// Oyuncu'dan sayi iste
		tahmin = sayiIste();
		
		// Oyuncunun girdigi sayiyi kriterlere uygun mu?
		// Kriteler:
		// - 0 ile baslamayacak
		// - rakamlari birbirinden farkli 4 haneli olacak
		eslesenSayisi = sayiKontrol(rasgele, tahmin);		
		
	} 
	// Eslesen sayisi tanmsa oyunu bitir
	while (oyunBittimi(eslesenSayisi) == 1);
	
	return 0;
}
