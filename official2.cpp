#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void DACS_Info(){
	printf(" ________________________________________________________________________\n");
	printf("|                               DO AN CO SO                              |\n");
	printf("|TEN DO AN: XAY DUNG UNG DUNG UNG DUNG DAT MON AN VA THANH TOAN DON HANG.|\n");
	printf("|                   GVHD: CO TRAN HO THUY TIEN                           |\n");
	printf("|SINH VIEN THUC HIEN:        NGUYEN DUY THINH                            |\n");
	printf("|                              VO VAN THANH                              |\n");
	printf("|________________________________________________________________________|\n");
	//getch();
}

void passinp(char pass[100], char user[100]){
	int i = 0, n = 0;
	do{
		pass[0] = getch();
	}
	while (pass[0] == 8);
	do{
		printf("*");
		n++;
		pass[++i] = getch();
	kt:
		while (pass[i] == 8){
			system("cls");
			DACS_Info();
			printf("Tai khoan: %s\n", user);
			printf("Mat khau: ");
			for (int j = 0; j < n-1; j++) printf("*");
			n--;
			if (n == 0) {
				passinp(pass, user);
				return;
			}
			pass[--i] = getch();
			goto kt;
		}
	}
	while(pass[i] != 13);
	pass[i]=NULL;
	printf("\n");
}

void login(FILE *f){
	char user[100], pass[100], t1[100], t2[100];
	printf("Tai khoan: ");
	gets(user);
	printf("Mat khau: ");
	passinp(pass, user);
	while (fgets(t1,255,f) && fgets(t2,255,f)){
		t1[strlen(t1)-1] = NULL; t2[strlen(t2)-1] = NULL;
		if (strcmp(user,t1) == 0 && strcmp(pass,t2)==0){
			printf("Dang nhap thanh cong!\n");
			getch();
			return;
		}
	}
	printf("Sai tai khoan hoac mat khau! Vui long thu lai.\n");
	getch();
	rewind(f);
	login(f);
}

void nhapmgd(char fname[], char tg[]){
	char name[100], bname[100 ]= "D:\\DACS\\";
	printf("Nhap ma giao dich ngay hom nay: ");
	scanf("%s",&name);
	strcpy(tg,name);
	strcat(bname, name);
	strcat(bname, ".txt");
	strcpy(fname, bname);
}	

void thoigian(FILE *f){
	time_t curtime;
	time(&curtime);
	fprintf(f,"%s", ctime(&curtime));
}

void inhd(const char *file){
	char c[100];
	FILE *f = fopen(file,"r");
	while (fgets(c,100,f)){
		printf("%s",c);
	}
	printf("\n");
	fclose(f);
}

char* intien(int a){
	char *t = (char*)malloc(100*sizeof(char));
	sprintf(t, "%d", a);
	int n,l = strlen(t), i = l;
	if (l%3 == 0) n = l/3-1;
	else n = l/3;
	while (n>0){
		t[i+n-1] = t[i-1];
		t[i+n-2] = t[i-2];
		t[i+n-3] = t[i-3];
		t[i+n-4] = ',';
		n--;
		i-=3;
	}
	t[l + n + 1 + 1] = '\0';
	return t;
}

struct Menu{//KHAI BAO MENU//Tenmon17kitu
	char TenMon[100][100] = {"", "Oc nhoi thit hap ",  "Ech nau chuoi dau", "Ga tiem thuoc Bac", "Ca hoi hap       ", "Tom hum Alaska   ", "Cua hoang de     "};
	int Gia[100] = {0, 100000, 150000, 200000, 300000, 400000, 500000,};
	int SoMon = 6;
};
struct HoaDon{ //KHAI BAO HOA DON
	int MaMon[100];
	int SoLuong[100];
	int soMon = 0;		//kiem tra max so mon = 5
	int TongTien[100];
};

void InMenu(Menu &menu, int n){
	printf("       --------MENU---------\n");
	printf("MA MON\tTEN MON\t\t\tGIA\n");
	printf("------  ----------------------  -------\n");
	for (int i = 1; i < n + 1; i++)
		printf("  %d\t%s\t%s\n", i, menu.TenMon[i], intien(menu.Gia[i]));
}

int stack(int MaMon[], int SoMon, int Mamon){
	for (int i = 1; i < SoMon; i++)
		if (MaMon[i] == Mamon) return i;
	return 0;
}

int check_bug(Menu &menu, HoaDon &hoadon){
	if (hoadon.MaMon[hoadon.soMon] > menu.SoMon){
		printf("Ma mon khong ton tai, vui long thu lai: ");
		return 1;
	}
	if (hoadon.SoLuong[hoadon.soMon] > 99){
		printf("Vuot qua so luong quy dinh, vui long thu lai!!: ");
		return 1;
	}
	return 0;
}

int check_cp(float inpt){
	if (inpt != (int)inpt) return 0;
	char ipt[100];
	sprintf(ipt, "%.0f", inpt);
	if (strcmp(ipt, "0") == 0) return -1;
	else if (strcmp(ipt, "-1") == 0) return 0;
	int temp = atoi(ipt);
	if (temp - 1 < 0) return 0;
	return temp;
}

void Add_Sl(HoaDon &hoadon, Menu &menu){
	int i = stack(hoadon.MaMon, hoadon.soMon, hoadon.MaMon[hoadon.soMon]);
	hoadon.SoLuong[i] += hoadon.SoLuong[hoadon.soMon]; 
	hoadon.TongTien[i] = menu.Gia[hoadon.MaMon[i]] * hoadon.SoLuong[i];
	hoadon.soMon--;	
}

void ChonMon(Menu &menu, HoaDon &hoadon){
	hoadon.soMon++;
	do{		
		float MaMon, SoLuong;
		do{
			scanf("%f%f", &MaMon, &SoLuong);
			fflush(stdin);
			if (!(check_cp(MaMon) && check_cp(SoLuong))) printf("Co loi xay ra, vui long thu lai: ");
			hoadon.MaMon[hoadon.soMon] = check_cp(MaMon);
			hoadon.SoLuong[hoadon.soMon] = check_cp(SoLuong);
		}
		while (!(check_cp(MaMon) && check_cp(SoLuong)));	
	}
	while (check_bug(menu, hoadon));
	if (stack(hoadon.MaMon, hoadon.soMon, hoadon.MaMon[hoadon.soMon])) Add_Sl(hoadon, menu);
	hoadon.TongTien[hoadon.soMon] = menu.Gia[hoadon.MaMon[hoadon.soMon]] * hoadon.SoLuong[hoadon.soMon];
	if (hoadon.MaMon[hoadon.soMon] == -1 && hoadon.SoLuong[hoadon.soMon] == -1) hoadon.TongTien[hoadon.soMon] = -1;	
}

int check(Menu &menu, HoaDon &hoadon, int maxofmon){
	for (int i = 1; i < maxofmon; i++)
		if (hoadon.TongTien[i] == -1) return 1;
	return 0;
}

void TongTien(Menu &menu, HoaDon &hoadon, int &TongNgay, FILE *f1, FILE *f2){
	int i = 1, TTien = 0, GiamGia = 0;
	do{
		printf("Mon %d: ", i);
		ChonMon(menu, hoadon);
		if (stack(hoadon.MaMon, hoadon.soMon, hoadon.MaMon[hoadon.soMon])) i--;
		i++;
	}
	while(hoadon.soMon < 5 && !check(menu, hoadon, i));
	int temp; 
	for (int k = 1; k < i; k++)
		TTien += hoadon.TongTien[k];
	thoigian(f1);
	fprintf(f1, "\t     --------HOA DON---------\n");
	fprintf(f1, "TenMon             SL \t Gia \t\t Tong\n");
	fprintf(f1, "-----------------  -- \t -------- \t ----------\n");
	int t = 1;
	do{
		int temp = hoadon.TongTien[t] / menu.Gia[hoadon.MaMon[t]];
		fprintf(f1, "%s  %d \t %s \t %s \n", menu.TenMon[hoadon.MaMon[t]], temp, intien(menu.Gia[hoadon.MaMon[t]]), intien(hoadon.TongTien[t]));
		t++;
		if (t > menu.SoMon - 1) break;
	}
	while (!(hoadon.MaMon[t] == -1 && hoadon.SoLuong[t] == -1));	
	if (check(menu, hoadon, i)) TTien++;
	fprintf(f1, "\nTong cong:      \t\t\t%10s\n", intien(TTien));
	if (TTien >= 2000000) GiamGia = TTien * 1/4;
	fprintf(f1, "Giam gia:   	\t\t\t%10s\n", intien(GiamGia));
	fprintf(f1, "Tong thanh toan:\t\t\t%10s\n", intien(TTien - GiamGia));
	thoigian(f2);
	fprintf(f2, "Tong hoa don:           %26s\n", intien(TTien - GiamGia));
	
	TongNgay += (TTien - GiamGia);
	fclose(f1);
	inhd("D:\\DACS\\hdkh.txt");
}

void endday(char name[100], char fname[100], FILE *f2, int TongNgay){
	char  end[100];
    printf("Nhap vao ma giao dich de xac nhan ket thuc ngay lam viec: ");
    scanf("%s",&end);
    if (strcmp(name,end) == 0){
    	////system("cls");
    	fprintf(f2, "Tong thu trong ngay la: %26s\n",intien(TongNgay));
    	fclose(f2);
    	inhd(fname);
	}
    else{
    	printf("Ma giao dich khong khop vui long thu lai!\n\n");
    	endday(name, fname, f2, TongNgay);
	} 
}

main(){
	FILE *f, *f1, *f2;
	char fname[100], name[100], ans;
	int TongNgay = 0;
	
	DACS_Info();
	f = fopen("D:\\DACS\\account.txt", "r");
	if (f == NULL) printf("File khong ton tai.");
	login(f);
	fclose(f);
	
	nhapmgd(fname, name);
	f2 = fopen(fname, "a+");
	fprintf(f2, "Ma giao dich: %s\n", name);
	
	do{ 
		Menu menu;
		HoaDon hoadon;
		f1 = fopen("D:\\DACS\\hdkh.txt", "w");
		InMenu(menu, menu.SoMon);
		TongTien(menu, hoadon, TongNgay, f1, f2);
		printf("Nhan 'C' de tiep tuc phien lam viec: ");
		printf("\n");
		ans = getch();
		if (ans == 99){
			for (int i = 1; i < hoadon.soMon + 1; i++){
			hoadon.SoLuong[i] = 0;
			hoadon.TongTien[i] = 0;
			}
		}
	}
	while (ans == 99);
	endday(name, fname, f2, TongNgay);
}
