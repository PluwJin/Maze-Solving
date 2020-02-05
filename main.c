//ERHAN OZDOGAN 160201039 - FIRAT KAPLAN 160201017
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
struct dugum{
int i;
int j;
int veri;
struct dugum*sonraki;
};
struct dugum*ilk=NULL,*son=NULL;
struct dugum*gidildi_ilk=NULL,*gidildi_son=NULL;

struct y_dugum{
struct dugum**veri;
struct y_dugum*sonraki;
};
struct y_dugum* kok = NULL;

int t=0;
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ///////////////  FONKSIYON PROTOTIPLERI ///// /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct dugum* dugum_olustur(int i_indis,int j_indis,int veriler);
void listeye_ekle(struct dugum*);
void matris_yazdir(int j_index,int sutun);
int kapi_bul(int x,int y);
void gidildi_listeye_ekle(struct dugum*dugum);
void labirent_coz(int satir,int sutun,int x,int y,int cx,int cy);
struct dugum*dugum_belirle(int x,int y);
struct dugum*gidildi_dugum_belirle(int x,int y);
int gidildi_kapi_bul(int x,int y);
void gidildi_matris_yazdir(int j_index,int sutun);
struct y_dugum*yeni_dugum(struct dugum*veri);
void yigina_ekle (struct dugum*veri);
int bosmu();
struct dugum*al();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

 int main(){
     srand(time(NULL));
     struct dugum*eklenecek=NULL;
     struct dugum*gidildi_eklenecek=NULL;
     int satir,sutun,k=-1,i_index,j_index,veri,i,x,y,cx,cy;
printf("Satir Sayisi Giriniz:");
scanf("%d",&satir);
printf("Sutun Sayisi Giriniz:");
scanf("%d",&sutun);
printf("\nOlusan Labirent:\n\n");
//GIDILDI MATRISI OLUSTURULDU LABIRENTTE AYNI YERLERE GIRMEMEK ICIN KULLANILACAK -----------------------------
for(i=0;i<satir*sutun;i++){
    j_index=i%sutun;
if(j_index==0){
    k++;
    i_index=k;
}
gidildi_eklenecek=dugum_olustur(i_index,j_index,0);
gidildi_listeye_ekle(gidildi_eklenecek);
}
//DONGU ILE MATRIS ELEMANI KADAR DUGUM FONKSIYON YARDIMI ILE OLUSTURULUP BAGLANIR-----------------------------
k=-1;
for(i=0;i<satir*sutun;i++){
    j_index=i%sutun;
if(j_index==0){
    k++;
    i_index=k;
}
veri=rand()%2;
eklenecek=dugum_olustur(i_index,j_index,veri);
listeye_ekle(eklenecek);
}

//LABIRENTIN EKRANA YAZDIRILMASI ICIN FONKSIYON CAGIRILDI-----------------------------------------------------
matris_yazdir(j_index,sutun);
printf("\n");
//LABIRENTIN GIRIS VE CIKISI ISTENDI UYGUNLUGU KONTROL EDILDI-------------------------------------------------
Loop:
printf("Labirentin Giris Koordinatlarini Giriniz:\n");
scanf("%d%d",&x,&y);
if(x<0 || y<0 || x>=satir || y>=sutun || kapi_bul(x,y)==0){
        printf("\n!!!!! Hatali Giris veya Duvar Tekrar Giriniz !!!!\n\n");
    goto Loop;
}
Loop1:
printf("Labirentin Cikis Koordinatlarini Giriniz:\n");
scanf("%d%d",&cx,&cy);
if(cx<0 || cy<0 || cx>=satir || cy>=sutun || kapi_bul(cx,cy)==0  ){
        printf("\n!!!!! Hatali Giris veya Duvar Tekrar Giriniz !!!!\n\n");
    goto Loop1;
}
//LABIRENT COZULDU -------------------------------------------------------------------------------------------
labirent_coz(satir,sutun,x,y,cx,cy);

// COZULMUS LABIRENTI EKRANA YAZDIRMA ------------------------------------------------------------------------
struct dugum*p;
while(!bosmu()){
struct dugum*k=gidildi_ilk;
p=al();
while(k!=NULL){

        if(k->i==p->i && k->j==p->j){
            k->veri=2;
        }
        if(k->i==cx && k->j==cy)
            k->veri=2;
        else if(k->veri!=2){
            k->veri=0;
        }
        k=k->sonraki;

}
}
if(t==0){
printf("\n");
gidildi_matris_yazdir(j_index,sutun);
}
getch();
 return 0;
 }

 /////////////////////////////////////////////////////////////////////////////////
/////////////////  YENI DUGUM OLUSTURUR VE BILGILERI ATAR ///// /////////////////
////////////////////////////////////////////////////////////////////////////////

struct dugum*dugum_olustur(int i_indis,int j_indis,int veriler){

 struct dugum* yenidugum=(struct dugum*)malloc(sizeof(struct dugum));
 yenidugum->i=i_indis;
 yenidugum->j=j_indis;
 yenidugum->veri=veriler;

return yenidugum;
}
//////////////////////////////////////////////////////////////////////////////////
// ///////////////  OLUSTURULAN YENI DUGUMU LISTENIN SONUNA EKLER  //////////////
////////////////////////////////////////////////////////////////////////////////

void listeye_ekle(struct dugum*dugum){
    if(ilk!=NULL){
        son->sonraki=dugum;
        son=dugum;
        son->sonraki=NULL;
    }
    else if(ilk==NULL){
        ilk=dugum;
        son=ilk;
        son->sonraki=NULL;
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////  OLUSTURULAN YENI DUGUMU LISTENIN SONUNA EKLER (GIDILDI MATRISI) ///////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
void gidildi_listeye_ekle(struct dugum*dugum){
    if(gidildi_ilk!=NULL){
        gidildi_son->sonraki=dugum;
        gidildi_son=dugum;
        gidildi_son->sonraki=NULL;
    }
    else if(gidildi_ilk==NULL){
        gidildi_ilk=dugum;
        gidildi_son=gidildi_ilk;
        gidildi_son->sonraki=NULL;
    }

}
//////////////////////////////////////////////////////////////////////////////////
// ///////////////  BAGLI LISTE ILE OLUSAN MATRISI EKRANA YAZAR  ////////////////
////////////////////////////////////////////////////////////////////////////////
void matris_yazdir(int j_index,int sutun){
     int i;
     struct dugum*p;
     p=ilk;
     while(p!=NULL){
        printf(" %d ",p->veri);
        if(p->j==sutun-1){
          printf("\n");}
          p=p->sonraki;
     }
}
//////////////////////////////////////////////////////////////////////////////////
// ///////////////  BAGLI LISTE ILE OLUSAN MATRISI EKRANA YAZAR(GIDILDI)  ///////
////////////////////////////////////////////////////////////////////////////////
void gidildi_matris_yazdir(int j_index,int sutun){
     int i;
     struct dugum*p;
     p=gidildi_ilk;
     while(p!=NULL){
        printf(" %d ",p->veri);
        if(p->j==sutun-1){
          printf("\n");}
          p=p->sonraki;
     }
}
//////////////////////////////////////////////////////////////////////////////////
// ///////////////  GIRIS VE CIKIS KAPILARININ UYGUNLUGUNU BULUR  ///////////////
////////////////////////////////////////////////////////////////////////////////
int kapi_bul(int x,int y){
struct dugum *p=ilk;
while(p!=NULL){
if(p->i==x && p->j==y){
    if(p->veri==1)
        return 1;
}
p=p->sonraki;
}
return 0;
}
//////////////////////////////////////////////////////////////////////////////////
// ///////////////  GIRIS VE CIKIS KAPILARININ UYGUNLUGUNU BULUR  ///////////////
////////////////////////////////////////////////////////////////////////////////
int gidildi_kapi_bul(int x,int y){
struct dugum *p=gidildi_ilk;
while(p!=NULL){
if(p->i==x && p->j==y){
    if(p->veri==1)
        return 1;
}
p=p->sonraki;
}
return 0;
}
//////////////////////////////////////////////////////////////////////////////////
// ///////////////  YIGINA EKLEME ICIN DUGUME VERI ATANDI //////////////////////
////////////////////////////////////////////////////////////////////////////////
struct y_dugum*yeni_dugum(struct dugum*veri){
struct y_dugum* yigindugum = (struct y_dugum*) malloc(sizeof(struct y_dugum));
 yigindugum->veri = veri;
 yigindugum->sonraki = NULL;
 return yigindugum;
};
//////////////////////////////////////////////////////////////////////////////////
// ///////////////  DUGUM YIGINA EKLENDI ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void yigina_ekle (struct dugum*veri){

 struct y_dugum* yigindugum = yeni_dugum(veri);
 yigindugum->sonraki =kok;
 kok = yigindugum;
}
//////////////////////////////////////////////////////////////////////////////////
// ///////////////  YIGIN BOSMU KONTROL /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int bosmu(){
 return !kok;
}
//////////////////////////////////////////////////////////////////////////////////
// ///////////////  YIGINDAN DUGUM CEKME ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
struct dugum*al(){
 if (bosmu())
 return 0;
 struct y_dugum*alinacak=kok;
 kok=kok->sonraki;
 struct dugum*alinan = alinacak->veri;
 free(alinacak);
 return alinan;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////  DUGUMU BELIRLEYEN FONKSIYON //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
struct dugum*dugum_belirle(int x,int y){
struct dugum*p=ilk;
while(p!=NULL){
if(p->i==x && p->j==y){
    return p;
}
p=p->sonraki;
}
}
//////////////////////////////////////////////////////////////////////////////////
/////////////////  DUGUMU BELIRLEYEN FONKSIYON (GIDILDI) ////////////////////////
////////////////////////////////////////////////////////////////////////////////
struct dugum*gidildi_dugum_belirle(int x,int y){
struct dugum*p=gidildi_ilk;
while(p!=NULL){
if(p->i==x && p->j==y){
    return p;
}
p=p->sonraki;
}
}


//////////////////////////////////////////////////////////////////////////////////
/////////////////  LABIRENTI COZEN FONKSIYON ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void labirent_coz(int satir,int sutun,int x,int y,int cx,int cy){

struct dugum*p=dugum_belirle(x,y);
struct dugum*gidildi_p=gidildi_dugum_belirle(x,y);
struct dugum*k;
gidildi_p->veri=1;
//yigina_ekle(p);
while(1){
//KUZEYE GIT------
if((p->i)-1>=0 && kapi_bul((p->i)-1,p->j)==1 && gidildi_kapi_bul((gidildi_p->i)-1,gidildi_p->j)!=1){
        yigina_ekle(p);
        p=dugum_belirle((p->i)-1,p->j);
        gidildi_p=gidildi_dugum_belirle((gidildi_p->i)-1,gidildi_p->j);
        gidildi_p->veri=1;
        yigina_ekle(p);
         if(p->i==cx && p->j==cy){
            printf("\nCikis Bulundu !!!!\n");
            break;
        }
}
//DOGUYA GIT------
else if((p->j)+1<=sutun-1 && kapi_bul(p->i,(p->j)+1)==1 && gidildi_kapi_bul(gidildi_p->i,(gidildi_p->j)+1)!=1){
    yigina_ekle(p);
        p=dugum_belirle(p->i,(p->j)+1);
        gidildi_p=gidildi_dugum_belirle(gidildi_p->i,(gidildi_p->j)+1);
        gidildi_p->veri=1;
        yigina_ekle(p);
        if(p->i==cx && p->j==cy){
            printf("\nCikis Bulundu !!!!\n");
            break;
        }
}
//GUNEYE GIT------
else if((p->i)+1<=satir-1 && kapi_bul((p->i)+1,p->j)==1 && gidildi_kapi_bul((gidildi_p->i)+1,gidildi_p->j)!=1){
    yigina_ekle(p);
        p=dugum_belirle((p->i)+1,p->j);
        gidildi_p=gidildi_dugum_belirle((gidildi_p->i)+1,gidildi_p->j);
        gidildi_p->veri=1;
        yigina_ekle(p);
         if(p->i==cx && p->j==cy){
            printf("\nCikis Bulundu !!!!\n");
            break;
        }
}
//BATIYA GIT------
else if((p->j)-1>=0 && kapi_bul(p->i,(p->j)-1)==1 && gidildi_kapi_bul(gidildi_p->i,(gidildi_p->j)-1)!=1){
    yigina_ekle(p);
        p=dugum_belirle(p->i,(p->j)-1);
        gidildi_p=gidildi_dugum_belirle(gidildi_p->i,(gidildi_p->j)-1);
        gidildi_p->veri=1;
        yigina_ekle(p);
         if(p->i==cx && p->j==cy){
            printf("\nCikis Bulundu !!!!\n");
            break;
        }
}
//HICBIRI OLMUYORSA YIGINDAN BIR ONCEKINI CIKAR VE ONA GIT-------
else{

        if(bosmu()){
            printf("\nCozum Yoktur\n");
            t=1;
            break;
        }
        p=al();
        gidildi_p=gidildi_dugum_belirle(p->i,p->j);
}
}

}



