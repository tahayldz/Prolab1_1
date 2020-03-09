//TAHA YILDIZ 180201019 - AHMET FURKAN KAŞIKCI 180201030

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
struct Hatali
{
    char hattali[20][50];
    int dsayi;
};

struct BinHatali
{
    char hataliBin[20][50];
    int bsayi;
};

struct Noktalar
{
    double nokta;
};

struct Binary1
{
    float x,y,z;
};

struct Binary2
{
    float x,y,z;
    int r,g,b;
};

void Uyumlumu();
void MatrisAta();
void Kup();
void Kure();
void Ortalama();

int main()
{
    struct Hatali hata;
    struct BinHatali hataBin;
    DIR *dir;
    FILE *dosya,*yaz;
    struct dirent *girdi;

    while(1)
    {
        int secim;
        printf("\n\t1- Dosyanin uyumlulugu\n");
        printf("\t2- Birbirine en yakin ve en uzak noktalar\n");
        printf("\t3- Tum noktalari icine alan kupun kenar noktalari\n");
        printf("\t4- Kure \n");
        printf("\t5- Uzaklik ortalama\n");

        scanf("%d",&secim);

        if(secim==1)
        {
            Uyumlumu(dir,&hata,&hataBin);
            continue;

        }

        else if(secim==2)
        {
            MatrisAta(dir,&hata,&hataBin);
            continue;
        }

        else if(secim==3)
        {
            Kup(dir,&hata,&hataBin);
            continue;
        }

        else if(secim==4)
        {
            Kure(dir,&hata,&hataBin);
            continue;
        }

        else if(secim==5)
        {
            Ortalama(dir,&hata,&hataBin);
        }

        break;
    }

    return 0;
}

void Uyumlumu(DIR *dir,struct Hatali* hata,struct BinHatali *hataBin)
{

    int k=0,header=0;
    char nab[100];
    char krkter,krkter2;
    char hatalidosya[100][100];
    FILE *dosya,*dosya2,*asciidosya,*yaz;
    char Alanlar[100];
    char Data[100];
    char Version[100];
    char Noktalar[100];
    char veri[45];
    char asciiveri[45];
    char binaryveri[45];
    char dizi[100][100];
    char tur[45];

    char *ascii,*binary,*ascii2;
    int i=0;
    int a=0,b=0;
    struct dirent *girdi;
    yaz=fopen("OUTPUT.nkt","w+");
    fprintf(yaz,"##################SECIM 1##################\n\n");
    if ((dir = opendir(".")) == NULL)
        printf("Dizin acılamadı.");
    else
    {

        while ((girdi = readdir(dir)) != NULL)
        {
            sscanf(girdi->d_name,"%s",&dizi[i]);
            i++;

LOOP:
            while(k<i)
            {

                if(strstr(dizi[k]+strlen(dizi[k])-4,".nkt"))
                {

                    dosya=fopen(dizi[k],"rb");
                    if(dosya==NULL)
                    {
                        printf("dosya acılamadi");
                    }
                    else
                    {


                        if(strstr(dizi[k],"OUTPUT"))
                        {
                            k++;
                            continue;
                        }

                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);

                        strcpy(tur,veri);

                        fclose(dosya);
                        dosya=fopen(dizi[k],"rb");
                        if(strstr(tur,"ascii"))
                        {
                            int satirsayac=1;

                            while(!feof(dosya))
                            {
                                krkter=fgetc(dosya);
                                if(krkter=='\n')
                                {
                                    satirsayac++;
                                    if(satirsayac==2)
                                    {
                                        fgets(Version,100,dosya);
                                        satirsayac++;
                                    }
                                    if(satirsayac==3)  //Satir sayisi 3 olunca Alanlar satirini string dizisine attýk.
                                    {
                                        fgets(Alanlar,100,dosya); //Bunun icin fgets kullandýk.
                                        satirsayac++; //if icinde yine bir artim yaparak düzenli artýsý sagladýk.

                                    }

                                    if(satirsayac==4)
                                    {
                                        fgets(Noktalar,100,dosya);
                                        satirsayac++;

                                    }

                                }
                            }

                            if(Alanlar[8]!='x' || Alanlar[10] != 'y' || Alanlar[12] != 'z')
                            {

                                fprintf(yaz,"%s: ALANLAR BASLIGINDA KOORDINAT BILGISI YOK.\n",dizi[k]);
                                strcpy(hata->hattali[a],dizi[k]);
                                a++;
                                k++;

                                continue;
                            }

                            int j,kelimesayac=0,bosluk_sayisi=0,nokta=0,vers=0;
                            for (j=0; j<strlen(Alanlar); j++)
                            {
                                if(Alanlar[j]==' ')
                                {
                                    kelimesayac++;
                                }

                            }

                            nokta = atoi(9+Noktalar);
                            vers= atoi(8+Version);
                            fclose(dosya);
                            if(vers!=1)
                            {
                                fprintf(yaz,"%s VERSION 1 DEGIL\n",dizi[k]);
                                strcpy(hata->hattali[a],dizi[k]);
                                a++;
                                k++;

                                continue;
                            }
                            int saybakem=0;
                            int hatalinokta=0;
                            dosya2=fopen(dizi[k],"r");
                            int header=0;
                            while(header<=5)
                            {
                                ascii=fgets(asciiveri,45,dosya2);
                                header++;
                            }
                            while(ascii != NULL)
                            {
                                saybakem=0;
                                for(ascii2=strtok(asciiveri," "); ascii2!=NULL; ascii2=strtok(NULL," "))
                                {
                                    saybakem++;
                                }
                                ascii=fgets(asciiveri,45,dosya2);
                                hatalinokta++;

                                if(saybakem==kelimesayac-1)
                                {
                                    continue;
                                }

                                if(saybakem!=kelimesayac)
                                {

                                    fprintf(yaz,"%s: %d. NOKTANIN RENK BILGISI EKSIK\n",dizi[k],hatalinokta);
                                    strcpy(hata->hattali[a],dizi[k]);
                                    a++;
                                    k++;
                                    goto LOOP;
                                }

                            }
                            if(nokta!=satirsayac-5)

                            {

                                fprintf(yaz,"%s: NOKTA BILGISI YANLIS.\n",dizi[k]);
                                strcpy(hata->hattali[a],dizi[k]);
                                a++;
                                k++;
                                continue;


                            }

                            fclose(dosya2);
                            if(strcmp(hata->hattali[a],dizi[k])!=0 && !strstr(dizi[k],"OUTPUT.nkt"))
                            {
                                fprintf(yaz,"%s : uyumlu\n",dizi[k]);
                            }

                        }

                        else if(tur,"binary")
                        {

                            binary=fgets(binaryveri,45,dosya);
                            binary=fgets(binaryveri,45,dosya);
                            strcpy(Version,binaryveri);
                            binary=fgets(binaryveri,45,dosya);
                            strcpy(Alanlar,binaryveri);
                            binary=fgets(binaryveri,45,dosya);
                            strcpy(Noktalar,binaryveri);
                            binary=fgets(binaryveri,45,dosya);

                            int nokta=0,vers=0;
                            nokta=atoi(9+Noktalar);
                            vers=atoi(8+Version);
                            int artim=0;
                            if(strstr(Alanlar,"x y z r g b") && Alanlar[19]=='\n')
                            {
                                struct Binary2 rgbdizi[nokta+1];

                                while(!feof(dosya))
                                {
                                    fread(&rgbdizi[artim],sizeof(struct Binary2),1,dosya);
                                    artim++;
                                }

                                if(vers!=1)
                                {
                                    fprintf(yaz,"%s: VERSION 1 DEGIL.\n",dizi[k]);
                                    strcpy(hataBin->hataliBin[b],dizi[k]);
                                    b++;
                                    k++;
                                    continue;
                                }

                                if(nokta!=artim-1)
                                {

                                    fprintf(yaz,"%s: NOKTA BILGISI YANLIS.\n",dizi[k]);
                                    strcpy(hataBin->hataliBin[b],dizi[k]);
                                    b++;
                                    k++;
                                    continue;
                                }



                                fprintf(yaz,"%s uyumlu\n",dizi[k]);
                                k++;
                                continue;

                            }

                            else if(strstr(Alanlar,"x y z") && Alanlar[13]=='\n')
                            {
                                struct Binary1 xyzdizi[nokta+1];

                                while(!feof(dosya))
                                {
                                    fread(&xyzdizi[artim],sizeof(struct Binary1),1,dosya);
                                    artim++;
                                }

                                if(vers!=1)
                                {
                                    fprintf(yaz,"%s: VERSION 1 DEGIL.\n",dizi[k]);
                                    strcpy(hataBin->hataliBin[b],dizi[k]);
                                    b++;
                                    k++;
                                    continue;
                                }
                                if(nokta!=artim-1)
                                {

                                    fprintf(yaz,"%s: NOKTA BILGISI YANLIS.\n",dizi[k]);
                                    strcpy(hataBin->hataliBin[b],dizi[k]);
                                    b++;
                                    k++;
                                    continue;
                                }



                                fprintf(yaz,"%s uyumlu\n",dizi[k]);
                                k++;
                                continue;


                            }
                            else
                            {

                                fprintf(yaz,"%s: ALANLAR BASLIGINDA KOORDINAT BILGISI YOK.\n",dizi[k]);
                                strcpy(hataBin->hataliBin[b],dizi[k]);
                                b++;
                                k++;
                                continue;

                            }

                            fclose(dosya);


                        }

                    }
                }

                k++;
            }
        }

        closedir(dir);
    }

    hata->dsayi=a;
    hataBin->bsayi=b;
    fclose(yaz);
}
void MatrisAta(DIR *dir,struct Hatali *hata,struct BinHatali *hataBin)
{

    FILE *dosya,*dosya2,*dosya3,*yaz,*asciidosya;
    char *naber,*naber2,*naber3;
    char veri2[45];
    char veri[45];
    char binaryveri[45];
    char tur[45];
    char dizi[100][100];
    char hatalidosya[100][100];
    char Alanlar[45],Noktalar[45];
    char *asciinaber,*binarynaber,*asciinaber2;
    int a=0,j=0,k=0,sutun=0,satir=0,m=0;

    yaz=fopen("OUTPUT.nkt","a+");
    fprintf(yaz,"\n\n##################SECIM 2##################\n\n");
    struct dirent *girdi;
    if ((dir = opendir(".")) == NULL)
        printf("Dizin acılamadı.");
    else
    {

        while ((girdi = readdir(dir)) != NULL)
        {
            sscanf(girdi->d_name,"%s",&dizi[a]);
            a++;
LOOP:
            while(k<a)
            {

                if(strstr(dizi[k]+strlen(dizi[k])-4,".nkt"))
                {

                    dosya=fopen(dizi[k],"rb");
                    if(dosya==NULL)
                    {
                        printf("dosya acılamadi");
                    }
                    else
                    {

                        if(strstr(dizi[k],"OUTPUT"))
                        {
                            k++;
                            continue;

                        }


                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);

                        strcpy(tur,veri);

                        fclose(dosya);
                        dosya=fopen(dizi[k],"r");
                        if(strstr(tur,"ascii"))
                        {

                            for(int b=0; b<hata->dsayi; b++)
                            {

                                if(strcmp(hata->hattali[b],dizi[k])==0)
                                {
                                    k++;
                                    goto LOOP;
                                }
                            }



                            int satirsayisi=1;

                            char krkter;
                            while(!feof(dosya))
                            {
                                krkter=fgetc(dosya);
                                if(krkter=='\n')
                                {
                                    satirsayisi++;

                                }
                            }

                            struct Noktalar d1[satirsayisi-5][3];
                            dosya3=fopen(dizi[k],"r");
                            int header=0;
                            while(header<=5)
                            {
                                asciinaber=fgets(veri2,45,dosya3);
                                header++;
                            }

                            while(asciinaber != NULL)
                            {
                                sutun=0;
                                asciinaber2 = strtok(veri2," ");
                                sscanf(asciinaber2,"%lf",&d1[satir][sutun].nokta);
                                sutun++;
                                asciinaber2 = strtok(NULL," ");
                                sscanf(asciinaber2,"%lf",&d1[satir][sutun].nokta);
                                sutun++;
                                asciinaber2 = strtok(NULL,"\n");
                                sscanf(asciinaber2,"%lf",&d1[satir][sutun].nokta);
                                satir++;

                                asciinaber=fgets(veri2,45,dosya3);

                            }

                            satir=0;
                            header=0;



                            fclose(dosya3);
                            double enYakin[2][3];
                            int yer[2];
                            int uzakyer[2];
                            double enUzak[2][3];
                            double anlik=0;
                            double enkucuk=0;
                            double enbuyuk=0;
                            int z,h,o;
                            double toplam=0;
                            double bolum=0;

                            enkucuk=sqrt(pow((d1[0][0].nokta-d1[1][0].nokta),2)+pow((d1[0][1].nokta-d1[1][1].nokta),2)+pow((d1[0][2].nokta-d1[1][2].nokta),2));
                            enbuyuk=enkucuk;
                            for(z=0; z<satirsayisi-5; z++)
                            {
                                for(h=z+1; h<satirsayisi-5; h++)
                                {
                                    anlik=sqrt(pow((d1[z][0].nokta-d1[h][0].nokta),2)+pow((d1[z][1].nokta-d1[h][1].nokta),2)+pow((d1[z][2].nokta-d1[h][2].nokta),2));
                                    toplam+=anlik;
                                    if(enkucuk>=anlik)
                                    {
                                        enkucuk=anlik;
                                        for(o=0; o<3; o++)
                                        {
                                            enYakin[0][o]=d1[z][o].nokta;
                                            enYakin[1][o]=d1[h][o].nokta;
                                        }
                                        yer[0]=z;
                                        yer[1]=h;
                                    }
                                    if(enbuyuk<=anlik)
                                    {
                                        enbuyuk=anlik;
                                        for(o=0; o<3; o++)
                                        {
                                            enUzak[0][o]=d1[z][o].nokta;
                                            enUzak[1][o]=d1[h][o].nokta;
                                        }
                                        uzakyer[0]=z;
                                        uzakyer[1]=h;
                                    }

                                }
                            }
                            bolum=(((double)(satirsayisi-5)*(satirsayisi-6))/2);
                            toplam/=bolum;
                            fclose(dosya);
                            dosya2=fopen(dizi[k],"r");
                            char yakin1[45],yakin2[45];
                            char uzak1[45],uzak2[45];
                            int header2=0;
                            while(header<=5)
                            {
                                naber3=fgets(veri2,45,dosya2);
                                header++;
                            }

                            while(naber3 != NULL)
                            {
                                if(header2==yer[0])
                                {
                                    strcpy(yakin1,veri2);
                                }
                                else if((header2)==yer[1])
                                {
                                    strcpy(yakin2,veri2);
                                }
                                else if((header2)==uzakyer[0])
                                {
                                    strcpy(uzak1,veri2);
                                }
                                else if((header2)==uzakyer[1])
                                {
                                    strcpy(uzak2,veri2);
                                }
                                naber3=fgets(veri2,45,dosya2);
                                header2++;
                            }
                            fprintf(yaz,"%s icin... \n",dizi[k]);

                            fprintf(yaz,"Birbirine en yakin olan noktalar:\n%s\%s\n",yakin1,yakin2);


                            fprintf(yaz,"Birbirine en uzak olan noktalar:\n%s\%s\n",uzak1,uzak2);

                            fclose(dosya2);
                        }

                        else if(strstr(tur,"binary"))
                        {
                            for(int b=0; b<hataBin->bsayi; b++)
                            {

                                if(strcmp(hataBin->hataliBin[b],dizi[k])==0)
                                {
                                    k++;
                                    goto LOOP;
                                }
                            }

                            int i=0,artim=0;
                            int z,h,o;
                            double enkucuk=0,enbuyuk=0,anlik=0;
                            binarynaber=fgets(binaryveri,45,dosya);
                            binarynaber=fgets(binaryveri,45,dosya);
                            binarynaber=fgets(binaryveri,45,dosya);
                            strcpy(Alanlar,binaryveri);
                            binarynaber=fgets(binaryveri,45,dosya);
                            strcpy(Noktalar,binaryveri);
                            binarynaber=fgets(binaryveri,45,dosya);

                            int nokta = atoi(9+Noktalar);
                            if(strstr(Alanlar,"r g b"))
                            {
                                double enUzak[2][6];
                                double enYakin[2][6];
                                struct Binary2 rgbdizi[nokta];

                                while(!feof(dosya))
                                {
                                    fread(&rgbdizi[artim],sizeof(struct Binary2),1,dosya);
                                    artim++;
                                }
                                enkucuk=sqrt(pow((rgbdizi[0].x-rgbdizi[1].x),2)+pow((rgbdizi[0].y-rgbdizi[1].y),2)+pow((rgbdizi[0].z-rgbdizi[1].z),2));
                                enbuyuk=enkucuk;

                                for(z=0; z<artim-1; z++)
                                {
                                    for(h=z+1; h<artim-1; h++)
                                    {
                                        anlik=sqrt(pow((rgbdizi[z].x-rgbdizi[h].x),2)+pow((rgbdizi[z].y-rgbdizi[h].y),2)+pow((rgbdizi[z].z-rgbdizi[h].z),2));
                                        if(enkucuk>=anlik)
                                        {
                                            enkucuk=anlik;

                                            enYakin[0][0]=rgbdizi[z].x;
                                            enYakin[0][1]=rgbdizi[z].y;
                                            enYakin[0][2]=rgbdizi[z].z;
                                            enYakin[0][3]=rgbdizi[z].r;
                                            enYakin[0][4]=rgbdizi[z].g;
                                            enYakin[0][5]=rgbdizi[z].b;

                                            enYakin[1][0]=rgbdizi[h].x;
                                            enYakin[1][1]=rgbdizi[h].y;
                                            enYakin[1][2]=rgbdizi[h].z;
                                            enYakin[1][3]=rgbdizi[h].r;
                                            enYakin[1][4]=rgbdizi[h].g;
                                            enYakin[1][5]=rgbdizi[h].b;

                                        }
                                        if(enbuyuk<=anlik)
                                        {
                                            enbuyuk=anlik;
                                            enUzak[0][0]=rgbdizi[z].x;
                                            enUzak[0][1]=rgbdizi[z].y;
                                            enUzak[0][2]=rgbdizi[z].z;
                                            enUzak[0][3]=rgbdizi[z].r;
                                            enUzak[0][4]=rgbdizi[z].g;
                                            enUzak[0][5]=rgbdizi[z].b;

                                            enUzak[1][0]=rgbdizi[h].x;
                                            enUzak[1][1]=rgbdizi[h].y;
                                            enUzak[1][2]=rgbdizi[h].z;
                                            enUzak[1][3]=rgbdizi[h].r;
                                            enUzak[1][4]=rgbdizi[h].g;
                                            enUzak[1][5]=rgbdizi[h].b;

                                        }
                                    }
                                }

                                fprintf(yaz,"%s icin... \n",dizi[k]);

                                fprintf(yaz,"Birbirine en yakin noktalar:\n%f %f %f %.f %.f %.f\n%f %f %f %.f %.f %.f\n",enYakin[0][0],enYakin[0][1],enYakin[0][2],enYakin[0][3],enYakin[0][4],enYakin[0][5],enYakin[1][0],enYakin[1][1],enYakin[1][2],enYakin[1][3],enYakin[1][4],enYakin[1][5]);

                                fprintf(yaz,"Birbirine en uzak noktalar:\n%f %f %f %.f %.f %.f\n%f %f %f %.f %.f %.f\n",enUzak[0][0],enUzak[0][1],enUzak[0][2],enUzak[0][3],enUzak[0][4],enUzak[0][5],enUzak[1][0],enUzak[1][1],enUzak[1][2],enUzak[1][3],enUzak[1][4],enUzak[1][5]);

                            }

                            else
                            {
                                double enUzak[2][3];
                                double enYakin[2][3];
                                struct Binary1 xyzdizi[nokta];

                                while(!feof(dosya))
                                {
                                    fread(&xyzdizi[artim],sizeof(struct Binary1),1,dosya);
                                    artim++;
                                }

                                enkucuk=sqrt(pow((xyzdizi[0].x-xyzdizi[1].x),2)+pow((xyzdizi[0].y-xyzdizi[1].y),2)+pow((xyzdizi[0].z-xyzdizi[1].z),2));
                                enbuyuk=enkucuk;

                                for(z=0; z<artim-1; z++)
                                {
                                    for(h=z+1; h<artim-1; h++)
                                    {
                                        anlik=sqrt(pow((xyzdizi[z].x-xyzdizi[h].x),2)+pow((xyzdizi[z].y-xyzdizi[h].y),2)+pow((xyzdizi[z].z-xyzdizi[h].z),2));
                                        if(enkucuk>=anlik)
                                        {
                                            enkucuk=anlik;
                                            enYakin[0][0]=xyzdizi[z].x;
                                            enYakin[0][1]=xyzdizi[z].y;
                                            enYakin[0][2]=xyzdizi[z].z;
                                            enYakin[1][0]=xyzdizi[h].x;
                                            enYakin[1][1]=xyzdizi[h].y;
                                            enYakin[1][2]=xyzdizi[h].z;
                                        }
                                        if(enbuyuk<=anlik)
                                        {
                                            enbuyuk=anlik;
                                            enUzak[0][0]=xyzdizi[z].x;
                                            enUzak[0][1]=xyzdizi[z].y;
                                            enUzak[0][2]=xyzdizi[z].z;
                                            enUzak[1][0]=xyzdizi[h].x;
                                            enUzak[1][1]=xyzdizi[h].y;
                                            enUzak[1][2]=xyzdizi[h].z;
                                        }


                                    }
                                }

                                fprintf(yaz,"%s icin \n",dizi[k]);

                                fprintf(yaz,"Birbirine en yakin noktalar:\n%f %f %f\n%f %f %f\n",enYakin[0][0],enYakin[0][1],enYakin[0][2],enYakin[1][0],enYakin[1][1],enYakin[1][2]);


                                fprintf(yaz,"Birbirine en uzak noktalar:\n%f %f %f\n%f %f %f\n",enUzak[0][0],enUzak[0][1],enUzak[0][2],enUzak[1][0],enUzak[1][1],enUzak[1][2]);

                            }
                        }

                    }


                }

                k++;
            }
        }

        closedir(dir);
    }
    fclose(yaz);
}
void Kup(DIR *dir,struct Hatali *hata,struct BinHatali *hataBin)
{
    FILE *dosya,*yaz,*dosya3,*binarydosya,*asciidosya;
    char *naber,*naber2;
    char veri2[45],veri[45];
    char binaryveri[45];
    int a=0,sutun=0,satir=0,k=0;
    char dizi[100][100];
    char tur[45];
    char *asciinaber,*binarynaber;
    char Alanlar[45],Nokta[45];
    double anlik=0;
    int m;

    yaz=fopen("OUTPUT.nkt","a+");
    fprintf(yaz,"\n\n##################SECIM 3##################\n\n");

    struct dirent *girdi;
    if ((dir = opendir(".")) == NULL)
        printf("Dizin acılamadı.");
    else
    {

        while ((girdi = readdir(dir)) != NULL)
        {
            sscanf(girdi->d_name,"%s",&dizi[a]);
            a++;
LOOP:
            while(k<a)
            {

                if(strstr(dizi[k]+strlen(dizi[k])-4,".nkt"))
                {

                    dosya=fopen(dizi[k],"rb");
                    if(dosya==NULL)
                    {
                        printf("dosya acılamadi");
                    }
                    else
                    {

                        if(strstr(dizi[k],"OUTPUT"))
                        {
                            k++;
                            continue;

                        }

                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);

                        strcpy(tur,veri);

                        fclose(dosya);
                        asciidosya=fopen(dizi[k],"r");

                        if(strstr(tur,"ascii"))
                        {
                            int i=0;
                            for(int b=0; b<hata->dsayi; b++)
                            {

                                if(strcmp(hata->hattali[b],dizi[k])==0)
                                {
                                    k++;
                                    goto LOOP;
                                }
                            }

                            int satirsayisi=1;

                            char krkter;
                            while(!feof(dosya))
                            {
                                krkter=fgetc(dosya);
                                if(krkter=='\n')
                                {
                                    satirsayisi++;

                                }
                            }
                            struct Noktalar d1[satirsayisi-5][3];
                            fclose(dosya);
                            dosya3=fopen(dizi[k],"r");
                            int header=0;
                            while(header<=5)
                            {
                                naber=fgets(veri2,45,dosya3);
                                header++;
                            }
                            while(naber != NULL)
                            {
                                sutun=0;
                                asciinaber = strtok(veri2," ");
                                sscanf(asciinaber,"%lf",&d1[satir][sutun].nokta);
                                sutun++;
                                asciinaber = strtok(NULL," ");
                                sscanf(asciinaber,"%lf",&d1[satir][sutun].nokta);
                                sutun++;
                                asciinaber = strtok(NULL,"\n");
                                sscanf(asciinaber,"%lf",&d1[satir][sutun].nokta);
                                satir++;

                                naber=fgets(veri2,45,dosya3);


                            }

                            satir=0;
                            header=0;
                            double kupMaksDizi[3];
                            double kupMinDizi[3];
                            double enb=0;
                            double enk=0;

                            kupMaksDizi[0]=d1[0][0].nokta;
                            kupMaksDizi[1]=d1[0][1].nokta;
                            kupMaksDizi[2]=d1[0][2].nokta;

                            for(i=0; i<satirsayisi-5; i++)
                            {
                                if(d1[i][0].nokta>=kupMaksDizi[0])
                                {
                                    kupMaksDizi[0]=d1[i][0].nokta;
                                }
                                if(d1[i][1].nokta>=kupMaksDizi[1])
                                {
                                    kupMaksDizi[1]=d1[i][1].nokta;
                                }
                                if(d1[i][2].nokta>=kupMaksDizi[2])
                                {
                                    kupMaksDizi[2]=d1[i][2].nokta;
                                }
                            }

                            enb=kupMaksDizi[0];
                            for(i=0; i<3; i++)
                            {
                                if(kupMaksDizi[i]>=enb)
                                {
                                    enb=kupMaksDizi[i];
                                }
                            }

                            kupMinDizi[0]=d1[0][0].nokta;
                            kupMinDizi[1]=d1[0][1].nokta;
                            kupMinDizi[2]=d1[0][2].nokta;

                            for(i=0; i<satirsayisi-5; i++)
                            {
                                if(d1[i][0].nokta<=kupMinDizi[0])
                                {
                                    kupMinDizi[0]=d1[i][0].nokta;
                                }
                                if(d1[i][1].nokta<=kupMinDizi[1])
                                {
                                    kupMinDizi[1]=d1[i][1].nokta;
                                }
                                if(d1[i][2].nokta<=kupMinDizi[2])
                                {
                                    kupMinDizi[2]=d1[i][2].nokta;
                                }
                            }

                            enk=kupMinDizi[0];
                            for(i=0; i<3; i++)
                            {
                                if(kupMinDizi[i]<=enk)
                                {
                                    enk=kupMinDizi[i];
                                }
                            }
                            fprintf(yaz,"%s isimli dosyanin kup kose noktalari\n",dizi[k]);
                            fprintf(yaz,"%lf\t%lf\t%lf\n",enb,enk,enb);
                            fprintf(yaz,"%lf\t%lf\t%lf\n",enb,enb,enb);
                            fprintf(yaz,"%lf\t%lf\t%lf\n",enb,enb,enk);
                            fprintf(yaz,"%lf\t%lf\t%lf\n",enb,enk,enk);
                            fprintf(yaz,"%lf\t%lf\t%lf\n",enk,enk,enk);
                            fprintf(yaz,"%lf\t%lf\t%lf\n",enk,enb,enb);
                            fprintf(yaz,"%lf\t%lf\t%lf\n",enk,enb,enk);
                            fprintf(yaz,"%lf\t%lf\t%lf\n",enk,enk,enb);

                            fclose(dosya3);

                        }

                        else if(strstr(tur,"binary"))
                        {

                            for(int b=0; b<hataBin->bsayi; b++)
                            {
                                if(strcmp(hataBin->hataliBin[b],dizi[k])==0)
                                {
                                    k++;
                                    goto LOOP;
                                }
                            }



                            binarynaber=fgets(binaryveri,45,dosya);
                            binarynaber=fgets(binaryveri,45,dosya);
                            binarynaber=fgets(binaryveri,45,dosya);
                            strcpy(Alanlar,binaryveri);
                            binarynaber=fgets(binaryveri,45,dosya);
                            strcpy(Nokta,binaryveri);
                            binarynaber=fgets(binaryveri,45,dosya);
                            int nokta = atoi(9+Nokta);
                            int artim=0,i=0;
                            int u;
                            if(strstr(Alanlar,"r g b"))
                            {

                                double enUzak[2][6];
                                double enYakin[2][6];
                                struct Binary2 rgbdizi[nokta];

                                while(!feof(dosya))
                                {
                                    fread(&rgbdizi[artim],sizeof(struct Binary2),1,dosya);
                                    artim++;
                                }

                                double kupMaksDizi[3];
                                double kupMinDizi[3];
                                double enb=0;
                                double enk=0;

                                kupMaksDizi[0]=rgbdizi[0].x;
                                kupMaksDizi[1]=rgbdizi[0].y;
                                kupMaksDizi[2]=rgbdizi[0].z;

                                for(u=0; u<artim-1; u++)
                                {
                                    if(rgbdizi[u].x>=kupMaksDizi[0])
                                    {
                                        kupMaksDizi[0]=rgbdizi[u].x;
                                    }
                                    if(rgbdizi[u].y>=kupMaksDizi[1])
                                    {
                                        kupMaksDizi[1]=rgbdizi[u].y;
                                    }
                                    if(rgbdizi[u].z>=kupMaksDizi[2])
                                    {
                                        kupMaksDizi[2]=rgbdizi[u].z;
                                    }
                                }

                                enb=kupMaksDizi[0];
                                for(i=0; i<3; i++)
                                {
                                    if(kupMaksDizi[i]>=enb)
                                    {
                                        enb=kupMaksDizi[i];
                                    }
                                }

                                kupMinDizi[0]=rgbdizi[0].x;
                                kupMinDizi[1]=rgbdizi[0].y;
                                kupMinDizi[2]=rgbdizi[0].z;

                                for(i=0; i<artim-1; i++)
                                {
                                    if(rgbdizi[i].x<=kupMinDizi[0])
                                    {
                                        kupMinDizi[0]=rgbdizi[i].x;
                                    }
                                    if(rgbdizi[i].y<=kupMinDizi[1])
                                    {
                                        kupMinDizi[1]=rgbdizi[i].y;
                                    }
                                    if(rgbdizi[i].z<=kupMinDizi[2])
                                    {
                                        kupMinDizi[2]=rgbdizi[i].z;
                                    }
                                }

                                enk=kupMinDizi[0];
                                for(i=0; i<3; i++)
                                {
                                    if(kupMinDizi[i]<=enk)
                                    {
                                        enk=kupMinDizi[i];
                                    }
                                }
                                fprintf(yaz,"%s isimli dosyanin kup kose noktalari\n",dizi[k]);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enb,enk,enb);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enb,enb,enb);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enb,enb,enk);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enb,enk,enk);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enk,enk,enk);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enk,enb,enb);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enk,enb,enk);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enk,enk,enb);


                                fclose(dosya);
                                k++;
                                goto LOOP;
                            }

                            else
                            {

                                struct Binary1 xyzdizi[nokta];

                                while(!feof(dosya))
                                {
                                    fread(&xyzdizi[artim],sizeof(struct Binary1),1,dosya);
                                    artim++;
                                }


                                double kupMaksDizi1[3];
                                double kupMinDizi1[3];
                                double enb1=0;
                                double enk1=0;

                                kupMaksDizi1[0]=xyzdizi[0].x;
                                kupMaksDizi1[1]=xyzdizi[0].y;
                                kupMaksDizi1[2]=xyzdizi[0].z;

                                for(i=0; i<artim-1; i++)
                                {
                                    if(xyzdizi[i].x>=kupMaksDizi1[0])
                                    {
                                        kupMaksDizi1[0]=xyzdizi[i].x;
                                    }
                                    if(xyzdizi[i].y>=kupMaksDizi1[1])
                                    {
                                        kupMaksDizi1[1]=xyzdizi[i].y;
                                    }
                                    if(xyzdizi[i].z>=kupMaksDizi1[2])
                                    {
                                        kupMaksDizi1[2]=xyzdizi[i].z;
                                    }
                                }

                                enb1=kupMaksDizi1[0];
                                for(i=0; i<3; i++)
                                {
                                    if(kupMaksDizi1[i]>=enb1)
                                    {
                                        enb1=kupMaksDizi1[i];
                                    }
                                }

                                kupMinDizi1[0]=xyzdizi[0].x;
                                kupMinDizi1[1]=xyzdizi[0].y;
                                kupMinDizi1[2]=xyzdizi[0].z;

                                for(i=0; i<artim-1; i++)
                                {
                                    if(xyzdizi[i].x<=kupMinDizi1[0])
                                    {
                                        kupMinDizi1[0]=xyzdizi[i].x;
                                    }
                                    if(xyzdizi[i].y<=kupMinDizi1[1])
                                    {
                                        kupMinDizi1[1]=xyzdizi[i].y;
                                    }
                                    if(xyzdizi[i].z<=kupMinDizi1[2])
                                    {
                                        kupMinDizi1[2]=xyzdizi[i].z;
                                    }
                                }

                                enk1=kupMinDizi1[0];
                                for(i=0; i<3; i++)
                                {
                                    if(kupMinDizi1[i]<=enk1)
                                    {
                                        enk1=kupMinDizi1[i];
                                    }
                                }

                                fprintf(yaz,"%s isimli dosyanin kup kose noktalari\n",dizi[k]);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enb1,enk1,enb1);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enb1,enb1,enb1);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enb1,enb1,enk1);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enb1,enk1,enk1);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enk1,enk1,enk1);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enk1,enb1,enb1);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enk1,enb1,enk1);
                                fprintf(yaz,"%lf\t%lf\t%lf\n",enk1,enk1,enb1);


                                fclose(dosya);
                                k++;
                                continue;
                            }

                        }


                    }


                }

                k++;
            }
        }

        closedir(dir);
    }
    fclose(yaz);

}

void Kure(DIR *dir,struct Hatali *hata,struct BinHatali *hataBin)
{

    FILE *dosya,*dosya2,*asciidosya,*yaz;
    char *naber,*naber2,*naber3,*binarynaber;
    char veri2[45],veri[45],tur[45],binaryveri[45],Alanlar[45],Nokta[45];
    char dizi[100][100];
    int a=0,j=0,k=0,sutun=0,satir=0,header2=0;
    double x,y,z,r;
    yaz=fopen("OUTPUT.nkt","a");
    fprintf(yaz,"\n\n##################SECIM 4##################\n\n");
    printf("kure icin x,y,z,r girin\n");
    printf("x: ");
    scanf("%lf",&x);
    printf("y: ");
    scanf("%lf",&y);
    printf("z: ");
    scanf("%lf",&z);
    printf("r: ");
    scanf("%lf",&r);

    struct dirent *girdi;
    if ((dir = opendir(".")) == NULL)
        printf("Dizin acılamadı.");
    else
    {

        while ((girdi = readdir(dir)) != NULL)
        {
            sscanf(girdi->d_name,"%s",&dizi[a]);
            a++;
LOOP:
            while(k<a)
            {

                if(strstr(dizi[k]+strlen(dizi[k])-4,".nkt"))
                {


                    dosya=fopen(dizi[k],"rb");
                    if(dosya==NULL)
                    {
                        printf("dosya acılamadi");
                    }
                    else
                    {

                        if(strstr(dizi[k],"OUTPUT"))
                        {
                            k++;
                            continue;

                        }


                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);

                        strcpy(tur,veri);

                        fclose(dosya);

                        dosya=fopen(dizi[k],"r");
                        if(strstr(tur,"ascii"))
                        {

                            for(int b=0; b<hata->dsayi; b++)
                            {
                                if(strcmp(hata->hattali[b],dizi[k])==0)
                                {
                                    k++;
                                    goto LOOP;
                                }
                            }



                            int satirsayisi=1;

                            char krkter;
                            while(!feof(dosya))
                            {
                                krkter=fgetc(dosya);
                                if(krkter=='\n')
                                {
                                    satirsayisi++;

                                }
                            }
                            fclose(dosya);
                            struct Noktalar d1[satirsayisi-5][3];
                            int header=0;
                            dosya2=fopen(dizi[k],"r");
                            while(header<=5)
                            {
                                naber=fgets(veri2,45,dosya2);
                                header++;
                            }

                            while(naber != NULL)
                            {
                                sutun=0;
                                naber2 = strtok(veri2," ");
                                sscanf(naber2,"%lf",&d1[satir][sutun].nokta);
                                sutun++;
                                naber2 = strtok(NULL," ");
                                sscanf(naber2,"%lf",&d1[satir][sutun].nokta);
                                sutun++;
                                naber2 = strtok(NULL,"\n");
                                sscanf(naber2,"%lf",&d1[satir][sutun].nokta);
                                satir++;

                                naber=fgets(veri2,45,dosya2);


                            }

                            satir=0;
                            header=0;

                            double oAnkiMesafe=0;
                            int m;

                            fprintf(yaz,"%s kure icindeki noktalar:\n",dizi[k]);
                            for(m=0; m<satirsayisi-5; m++)
                            {

                                oAnkiMesafe=sqrt(pow((d1[m][0].nokta-x),2)+pow((d1[m][1].nokta-y),2)+pow((d1[m][2].nokta-z),2));

                                if(oAnkiMesafe<=r)
                                {
                                    fprintf(yaz,"%f %f %f\n",d1[m][0].nokta,d1[m][1].nokta,d1[m][2].nokta);
                                }
                            }


                        }
                        else if(strstr(tur,"binary"));
                        {
                            for(int b=0; b<hataBin->bsayi; b++)
                            {
                                if(strcmp(hataBin->hataliBin[b],dizi[k])==0)
                                {
                                    k++;
                                    goto LOOP;
                                }
                            }



                            binarynaber=fgets(binaryveri,45,dosya);
                            binarynaber=fgets(binaryveri,45,dosya);
                            binarynaber=fgets(binaryveri,45,dosya);
                            strcpy(Alanlar,binaryveri);
                            binarynaber=fgets(binaryveri,45,dosya);
                            strcpy(Nokta,binaryveri);
                            binarynaber=fgets(binaryveri,45,dosya);
                            int nokta = atoi(9+Nokta);
                            int artim=0,i=0;
                            int u;

                            if(strstr(Alanlar,"r g b"))
                            {
                                double enUzak[2][6];
                                double enYakin[2][6];
                                double anlik=0;
                                struct Binary2 rgbdizi[nokta];

                                while(!feof(dosya))
                                {
                                    fread(&rgbdizi[artim],sizeof(struct Binary2),1,dosya);
                                    artim++;
                                }
                                int m;
                                fprintf(yaz,"%s kure icindeki noktalar:\n",dizi[k]);
                                for(m=0; m<artim-1; m++)
                                {
                                    anlik=sqrt(pow((rgbdizi[m].x-x),2)+pow((rgbdizi[m].y-y),2)+pow((rgbdizi[m].z-z),2));
                                    if(anlik<=r)
                                    {
                                        fprintf(yaz,"%f %f %f %d %d %d\n",rgbdizi[m].x,rgbdizi[m].y,rgbdizi[m].z,rgbdizi[m].r,rgbdizi[m].g,rgbdizi[m].b);
                                    }
                                }
                                fclose(dosya);
                            }

                            else
                            {
                                double enUzak[2][3];
                                double enYakin[2][3];
                                double anlik=0;
                                struct Binary1 xyzdizi[nokta];

                                while(!feof(dosya))
                                {
                                    fread(&xyzdizi[artim],sizeof(struct Binary1),1,dosya);
                                    artim++;
                                }
                                int m;

                                fprintf(yaz,"\n\n%s kure icindeki noktalar:\n\n",dizi[k]);
                                for(m=0; m<artim-1; m++)
                                {
                                    anlik=sqrt(pow((xyzdizi[m].x-x),2)+pow((xyzdizi[m].y-y),2)+pow((xyzdizi[m].z-z),2));
                                    if(anlik<=r)
                                    {

                                        fprintf(yaz,"%f %f %f\n",xyzdizi[m].x,xyzdizi[m].y,xyzdizi[m].z);
                                    }

                                }
                                fclose(dosya);


                            }

                        }
                    }

                }
                k++;
            }

        }
        closedir(dir);
    }
    fclose(yaz);

}

void Ortalama(DIR *dir,struct Hatali *hata,struct BinHatali *hataBin)
{
    FILE *dosya,*dosya2,*dosya3,*bindos,*yaz;
    char dizi[100][100];
    int a=0,k=0,satir=0,sutun=0;
    char veri[45],tur[45],veri2[45],binaryveri[45];
    char *naber,*asciinaber,*naber2;
    char Alanlar[45],Nokta[45];

    yaz=fopen("OUTPUT.nkt","a+");
    fprintf(yaz,"\n\n##################SECIM 5##################\n\n");


    struct dirent *girdi;
    if ((dir = opendir(".")) == NULL)
        printf("Dizin acılamadı.");
    else
    {

        while ((girdi = readdir(dir)) != NULL)
        {
            sscanf(girdi->d_name,"%s",&dizi[a]);
            a++;
LOOP:
            while(k<a)
            {


                if(strstr(dizi[k]+strlen(dizi[k])-4,".nkt"))
                {

                    dosya=fopen(dizi[k],"rb");
                    if(dosya==NULL)
                    {
                        printf("dosya acılamadi");
                    }
                    else
                    {

                        if(strstr(dizi[k],"OUTPUT"))
                        {
                            k++;
                            continue;

                        }


                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);
                        fgets(veri,45,dosya);

                        strcpy(tur,veri);

                        fclose(dosya);
                        if(strstr(tur,"ascii"))
                        {
                            int i=0;
                            for(int b=0; b<hata->dsayi; b++)
                            {

                                if(strcmp(hata->hattali[b],dizi[k])==0)
                                {
                                    k++;
                                    goto LOOP;
                                }
                            }

                            int satirsayisi=1;

                            dosya2=fopen(dizi[k],"r");
                            char krkter;
                            while(!feof(dosya2))
                            {
                                krkter=fgetc(dosya2);
                                if(krkter=='\n')
                                {
                                    satirsayisi++;

                                }
                            }
                            struct Noktalar d1[satirsayisi-5][3];
                            fclose(dosya2);
                            dosya3=fopen(dizi[k],"r");
                            int header=0;
                            while(header<=5)
                            {
                                naber=fgets(veri2,45,dosya3);
                                header++;
                            }

                            while(naber != NULL)
                            {
                                sutun=0;
                                asciinaber = strtok(veri2," ");
                                sscanf(asciinaber,"%lf",&d1[satir][sutun].nokta);
                                sutun++;
                                asciinaber = strtok(NULL," ");
                                sscanf(asciinaber,"%lf",&d1[satir][sutun].nokta);
                                sutun++;
                                asciinaber = strtok(NULL,"\n");
                                sscanf(asciinaber,"%lf",&d1[satir][sutun].nokta);
                                satir++;

                                naber=fgets(veri2,45,dosya3);


                            }

                            satir=0;
                            header=0;
                            double toplam=0;
                            double anlik=0;
                            int z=0,h=0;

                            for(z=0; z<satirsayisi-5; z++)
                            {
                                for(h=z+1; h<satirsayisi-5; h++)
                                {
                                    anlik=sqrt(pow((d1[z][0].nokta-d1[h][0].nokta),2)+pow((d1[z][1].nokta-d1[h][1].nokta),2)+pow((d1[z][2].nokta-d1[h][2].nokta),2));
                                    toplam+=anlik;

                                }
                            }

                            toplam/=((((double)satirsayisi-5)*(satirsayisi-6))/2);
                            fprintf(yaz,"%s dosyasinin ortalamasi: %lf\n",dizi[k],toplam);

                            fclose(dosya2);


                        }
                        else if(strstr(tur,"binary"))
                        {
                            for(int b=0; b<hataBin->bsayi; b++)
                            {

                                if(strcmp(hataBin->hataliBin[b],dizi[k])==0)
                                {
                                    k++;
                                    goto LOOP;
                                }
                            }

                            bindos=fopen(dizi[k],"rb");
                            naber2=fgets(binaryveri,45,bindos);
                            naber2=fgets(binaryveri,45,bindos);
                            naber2=fgets(binaryveri,45,bindos);
                            strcpy(Alanlar,binaryveri);
                            naber2=fgets(binaryveri,45,bindos);
                            strcpy(Nokta,binaryveri);
                            naber2=fgets(binaryveri,45,bindos);

                            int nokta = atoi(9+Nokta);
                            int artim=0;
                            int m=0,n=0;
                            double anlik=0;
                            double toplam=0;
                            if(strstr(Alanlar,"r g b"))
                            {
                                double enUzak[2][6];
                                double enYakin[2][6];

                                struct Binary2 rgbdizi[nokta];

                                while(!feof(bindos))
                                {
                                    fread(&rgbdizi[artim],sizeof(struct Binary2),1,bindos);
                                    artim++;
                                }

                                for(m=0; m<artim-1; m++)
                                {
                                    for(n=m+1; n<artim-1; n++)
                                    {
                                        anlik=sqrt(pow((rgbdizi[m].x-rgbdizi[n].x),2)+pow((rgbdizi[m].y-rgbdizi[n].y),2)+pow((rgbdizi[m].z-rgbdizi[n].z),2));
                                        toplam+=anlik;
                                    }

                                }


                                toplam=toplam/(((float)((artim-1)*(artim-2)))/2);
                                fprintf(yaz,"%s dosyasinin ortalamasi: %f\n",dizi[k],toplam);

                            }

                            else
                            {
                                double enUzak[2][3];
                                double enYakin[2][3];
                                struct Binary1 xyzdizi[nokta];

                                while(!feof(bindos))
                                {
                                    fread(&xyzdizi[artim],sizeof(struct Binary1),1,bindos);
                                    artim++;
                                }

                                for(m=0; m<artim-1; m++)
                                {
                                    for(n=m+1; n<artim-1; n++)
                                    {
                                        anlik=sqrt(pow((xyzdizi[m].x-xyzdizi[n].x),2)+pow((xyzdizi[m].y-xyzdizi[n].y),2)+pow((xyzdizi[m].z-xyzdizi[n].z),2));
                                        toplam+=anlik;
                                    }
                                }
                                toplam/=(((artim-1)*(artim-2))/2);
                                fprintf(yaz,"%s dosyasinin ortalamasi: %f\n",dizi[k],toplam);

                            }
                            fclose(bindos);
                        }
                    }
                }
                k++;
            }

        }
        closedir(dir);
    }

    fclose(yaz);
}
