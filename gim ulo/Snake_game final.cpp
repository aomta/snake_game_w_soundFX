#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <mmsystem.h>
#include <cmath>
#include <math.h>
#include <unistd.h>
#include <limits>
using namespace std;

bool gameover; //variabel penentu game berakhir
int lebar = 100; //ukuran arena
int tinggi = 30; //ukuran arena
int x; //koordinat x kepala ular
int again;
int y; //koordinat y kepala ular
int bX; //koordinat x makanan ular
int bY; //koordinat y makanan ular
int score; //variabel penyimpan skor pemain
int maks=0; //variabel penyimpan highscore
int laju; //variabel penentu kecepatan ular
int tailX[100]; //array x ekor ular
int tailY[100]; //array y ekor ular
int nTail; //ekor ular
int levelpermainan; //variabel penentu level permainan
int z =-1;
int History;
struct namaa
{
    string name;
    int score;

};
namaa nm[10000];
enum eDirection { STOP= 0, kiri, kanan, atas, bawah, };
eDirection dir; //struct penyimpan arah gerak ular

//prosedur untuk menghapus input yang mungkin ada di buffer
void ignoreInput() {
    while (_kbhit()) {
        _getch();
    }
}

//prosedur animasi ular
void logo_bergerak(){
    system("cls");
    system("color Cb");
    Beep(650,500);
    const char logoo [] =
    "\t\t\t\t\t\t                                          *\n\
     \t\t\t\t\t\t        *                                ***\n\
     \t\t\t\t\t\t       ***                              *****\n\
     \t\t\t\t\t\t      *****                             *****\n\
     \t\t\t\t\t\t      *****                              *****\n\
     \t\t\t\t\t\t      *****                               ****\n\
     \t\t\t\t\t\t     *****                               ****\n\
     \t\t\t\t\t\t    *****                               ****\n\
     \t\t\t\t\t\t    *****              *                ****\n\
     \t\t\t\t\t\t     *****            ***               *****\n\
     \t\t\t\t\t\t      *****           ***                *****\n\
     \t\t\t\t\t\t       *****           ***                ****\n\
     \t\t\t\t\t\t       *****            ***              ****\n\
     \t\t\t\t\t\t      *****             ***             ****        snake game^-^\n\
     \t\t\t\t\t\t     *****             ***               ***        *\n\
     \t\t\t\t\t\t     *****            ***                 **       **\n\
     \t\t\t\t\t\t      ***              **                  **    ***\n\
     \t\t\t\t\t\t       **               *                   **  ***\n\
     \t\t\t\t\t\t        *                                    ****\n\
     \t\t\t\t\t\t                                              **\n\
     ";

    for (int i = 0; i < 50; i++) cout << endl; // melompat ke bawah konsol
    cout << logoo ;
    int j = 300000;
    for (int i = 0; i < 50; i++) {
        usleep(j); // bergerak lebih cepat,
        j = (int)(j * 0.9); // waktu sleep
        cout << endl; // memindahkan baris logo ke atas
    }
    Sleep(1600); //delay sebelum lanjut ke program selanjutnya
 	system ("cls");
}

//prosedur tampilan logo game snake
void logo_game(){
    system("cls");
    system("color 5F");
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t                       	             ----------    ----      ---           ---           ---    ----    ----------                                  "<<endl;
	cout<<"\t                                     ----------    -----     ---          -- --          ---  ----      ----------                                "<<endl;
	cout<<"\t                                     ---           --- --    ---         --   --         -------        ---                                       "<<endl;
	cout<<"\t                                     ----------    ---  --   ---        ---   ---        ------         ----------                                "<<endl;
	cout<<"\t                                     ----------    ---   --  ---       -----------       ------         ----------                                "<<endl;
	cout<<"\t                                            --     ---    -- ---      -------------      -------        ---                                       "<<endl;
	cout<<"\t                                     ----------    ---     -----     ---         ---     ---  ----      ----------                                "<<endl;
	cout<<"\t                                     ----------    ---      ----    ---           ---    ---    ----    ----------                                "<<endl;
	cout<<"\t                                                                                                                                                  "<<endl;
	cout<<"\t                                                                                                                                                 "<<endl;
	cout<<"\t                                          -----------           ---           -----      -----    ----------                                        "<<endl;
	cout<<"\t                                         -----------           -- --          ------    ------    ----------                                        "<<endl;
	cout<<"\t                                         ---                  --   --         ---  --  --  ---    ---                                               "<<endl;
	cout<<"\t                                         ---    -----        ---   ---        ---   ----   ---    ----------                                        "<<endl;
	cout<<"\t                                         ---     ----       -----------       ---          ---    ----------                                        "<<endl;
	cout<<"\t                                         ---      ---      -------------      ---          ---    ---                                               "<<endl;
	cout<<"\t                                          -----------     ---         ---     ---          ---    ----------                                        "<<endl;
	cout<<"\t                                           ---------     ---           ---    ---          ---    ----------                                        ";
	cout<<"\t                                                                                                              "<<endl;
    cout<<"\t                                                                                                               "<<endl;
    cout<<"\t                                                                                                               "<<endl;
    cout<<"\t\t                                                                                     ******                  "<<endl;
    cout<<"\t\t                             *                                                     *** * ****      **                    "<<endl;
    cout<<"\t\t                            ***                                                   *************  **  **                  "<<endl;
    cout<<"\t\t                           *****           ******             ******             ***** * ****          **                "<<endl;
    cout<<"\t\t                            *****         ********           ********           ***** ******                             "<<endl;
    cout<<"\t\t                             *****      *****  *****       *****  *****       ******                                     "<<endl;
    cout<<"\t\t                               *****  *****      *****   *****      *****   *****                                      "<<endl;
    cout<<"\t\t                                 *******           *********          *********                                      "<<endl;
    cout<<"\t\t                                  *****              *****              *****                                      "<<endl;
    cout<<"\t\t                                                                     "<<endl;
	Sleep(1800);
 	system ("cls");
}

//prosedur untuk memesan koordinat x dan y
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//prosedur tampilan loading
void loading(){
    system("cls");
    char x = 219;   //karakter loading bar
    int width = 70; // lebar loading bar
    gotoxy(40, 17);
    cout <<"Loading. . . \n\t\t\t\t\t";
    for(int i = 0; i < width; i++) cout << " ";

    for(int i = 0; i <= width; i++) {
        gotoxy(40, 18); // posisi loading bar
        for(int j = 0; j < i; j++) {
            cout << x;
        }

        gotoxy(36 + width, 17); // posisi persentase
        cout << i + 30 << "%";

        Sleep(25);
    }

    Beep(800, 125);
    Beep(800, 125);

    gotoxy(0, 19); // posisi line selanjutnya setelah loading selesai
    ignoreInput();
}

//prosedur tampilan loading
void loading_exit(){
    char x = 219;
    int width = 100; // lebar loading bar
    cout << "\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t";
    gotoxy(48, 33);
    cout << "exit the game. . . \n\t\t\t\t\t";
    for(int i = 0; i < width; i++) cout << " ";

    for(int i = 0; i <= width; i++) {
        gotoxy(48, 34); // posisi loading bar
        for(int j = 0; j < i; j++) {
            cout << x;
        }

        gotoxy(44 + width, 33); // posisi persentase
        cout << i + 30<< "%";

        Sleep(25);
    }

    Beep(800, 125);
    Beep(800, 125);

    gotoxy(0, 34); // posisi line selanjutnya setelah loading selesai
    ignoreInput();
}

//prosedur tampilan penutup
void tutup(){
    system("cls");
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t\t\t        *************     ****     ****          ***          ****     ****     ****   ****     "<<endl;
    cout<<"\t\t\t        *************     ****     ****         *****         *****    ****     ****  ****      "<<endl;
    cout<<"\t\t\t            *****         ****     ****       **     **       **** *   ****     **** ****       "<<endl;
    cout<<"\t\t\t            *****         *************      ***     ***      **** **  ****     ********     "<<endl;
    cout<<"\t\t\t            *****         *************     ****     ****     ****  ** ****     ********     "<<endl;
    cout<<"\t\t\t            *****         ****     ****     *************     ****   ******     **** ****     "<<endl;
    cout<<"\t\t\t            *****         ****     ****     ****     ****     ****    *****     ****  ****     "<<endl;
    cout<<"\t\t\t            *****         ****     ****     ****     ****     ****     ****     ****   ****     "<<endl;
    cout<<"\t\t                                                                       "<<endl;
    cout<<"\t\t                                                                       "<<endl;
    cout<<"\t\t\t                          ****     ****          ***          ****     **** "<<endl;
    cout<<"\t\t\t                          ****     ****        *** ***        ****     **** "<<endl;
    cout<<"\t\t\t                           ****   ****        ***   ***       ****     **** "<<endl;
    cout<<"\t\t\t                             *** ***        ****     ****     ****     **** "<<endl;
    cout<<"\t\t\t                              *****         ****     ****     ****     **** "<<endl;
    cout<<"\t\t\t                              *****           ***   ***        ***     ***  "<<endl;
    cout<<"\t\t\t                              *****            *** ***          **** ****   "<<endl;
    cout<<"\t\t\t                              *****              ***              *****     "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    exit(0);
}

//prosedur untuk memasukkan username
void user(){
    system("cls");
    system("color 5F");
    ignoreInput();
    z+=1;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                                                             ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ "<<endl;
    cout<<"                                                             *                                   * "<<endl;
    cout<<"                                                             *          Inputkan Username        * "<<endl;
    cout<<"                                                             *            ------------           * "<<endl;
    cout<<"                                                             *                                   * "<<endl;
    cout<<"                                                             ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ "<<endl;
    cout<<"                                                                                                               "<<endl;
    cout<<"\t\t\t\t\t\t             Ketik 0 jika ingin kembali ke MENU!!! "<<endl;
    cin.get();
    cout<<endl<<endl<<"                                                                        >>>  ";getline(cin, nm[z].name);
    cin.get();
    cout<<endl;
    cout<<endl;
    loading();
}

//fungsi mengecek apakah musik latar belakang hidup
bool isBackgroundSoundPlaying = false;

//prosedur untuk menjeda musik latar belakang
void stopBackgroundSound() {
    // Stop the background sound
    (NULL, 0, 0);
    isBackgroundSoundPlaying = false;
    return;
}

//prosedur untuk mengontrol musik
void playMusic(const char* soundFile = "background.wav "){
	system("cls");
	//Setting musik
	cout << endl <<endl;
	cout <<"\t\t\t\t\t   ||  ||  ((|||))   ||   || |||||| ||||)))  ((|||))   ||  \n";
	cout <<"\t\t\t\t\t   || ||  ((     ))  |||  ||   ||   ||  ))  ((     ))  || \n";
	cout <<"\t\t\t\t\t   ||||  ((       )) || | ||   ||   ||)))  ((       )) ||  \n";
	cout <<"\t\t\t\t\t   || ||  ((     ))  ||  |||   ||   || ||   ((     ))  ||   \n";
	cout <<"\t\t\t\t\t   ||  ||  ((|||))   ||   ||   ||   ||  ||   ((|||))   ||||||  \n";
	cout << endl;
	cout <<"\t\t\t\t\t\t     ||   || ||  ||  ||||| ||| ||  || \n";
	cout <<"\t\t\t\t\t\t     ||| ||| ||  || |||    ||| || ||  \n";
	cout <<"\t\t\t\t\t\t     || | || ||  ||  ||||  ||| ||||   \n";
	cout <<"\t\t\t\t\t\t     ||   || ||  ||    ||| ||| || ||   \n";
	cout <<"\t\t\t\t\t\t     ||   || |||||| |||||  ||| ||  ||   \n";
	cout <<"\t\t\t_________________________________________________________________________________________________\n";
	cout << "\t\t\t\t Berikut Beberapa Tombol yang Dapat Digunakan Untuk Mengontrol Musik Latar Belakang\n";
	cout <<"\t\t\t_________________________________________________________________________________________________\n";
    cout << "\t\t\t\tTekan Tombol 'p' pada Keyboard Untuk Menjeda Musik Sebelum Memulai Permainan\n";
    cout << "\t\t\t\tTekan Tombol 'r' pada Keyboard Untuk Kembali Memainkan Musik\n";
    cout << "\t\t\t\tTekan Tombol 'q' pada Keyboard Untuk Kembali ke Permainan\n";
    cout <<"\t\t\t_________________________________________________________________________________________________\n";
    cout << "\t\t\t\tMusic source :  Bye, Bye Brain! by Alexander Nakarada | https://creatorchords.com\n";
    cout <<"\t\t\t_________________________________________________________________________________________________\n\n";

    bool isPlaying = false;
    //perulangan untuk mengecek tombol yang diinput
    while (true) {
        if (_kbhit()) { 
            char key = _getch();
            //tombol p untuk menjeda musik latar belakang
            /*musik latar belakang hanya dijeda saat pemilihan opsi
            pada saat permainan dimulai musik latar belakang akan diputar kembali*/
            if (key == 'p') {
                stopBackgroundSound();
                cout<<"\t\t\t\t  Musik telah berhasil dijeda!"<<endl;
            }
            //tombol r untuk memutar kembali musik
            else if (key == 'r') {
                // Start playing music
                isPlaying = true;
                PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
                cout<<"\t\t\t\t  Musik kembali dimainkan!"<<endl;
            }
            //tombol q untuk kembali ke menu
			else if (key == 'q') {
				cout<<"\t\t\t\t  Anda akan kembali melanjutkan ke permainan!"<<endl;
				cout<<"\t\t\t\t  Mohon Tunggu Sebentar..."<<endl;
				sleep(2);
				loading();
				return;
            }
        }
	}
	sleep(20);
    }

//prosedur untuk memilih opsi menu
void select_option(){
    ignoreInput();
    int opsi;
    menu:
        system("cls");
        system("color 5F");
    {
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                                              ================================================================== "<<endl;
    cout<<"                                              |                                                                | "<<endl;
    cout<<"                                              |                               MENU                             | "<<endl;
    cout<<"                                              |                           ------------                         | "<<endl;
    cout<<"                                              |                                                                | "<<endl;
    cout<<"                                              ================================================================== "<<endl;
    cout<<"                                              |                                                                | "<<endl;
    cout<<"                                              |                       Start GAME    ==> 1                      | "<<endl;
    cout<<"                                              |                                                                | "<<endl;
    cout<<"                                              |                       Music Setting ==> 2                      | "<<endl;
    cout<<"                                              |                                                                | "<<endl;
    cout<<"                                              |                       Exit          ==> 3                      | "<<endl;
    cout<<"                                              |                                                                | "<<endl;
    cout<<"                                              ================================================================== "<<endl<<endl<<endl;
    cout<<"                                                                    Masukkan Opsi (1-3) : ";

    //kondisi jika opsi yang diinputkan diluar pilihan opsi yang ada
    while (!(cin >> opsi) || opsi< 1 || opsi > 3||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        gotoxy(40, 20);
        cout<<endl<<endl<<endl<<"\t\t\t\t\t                                Input tidak valid.";
        cout<<endl<<"\t\t\t\t\t                   Ketik apa saja untuk menginputkan ulang (1-3)!!";
        getch();
        goto menu;
    }
    cout<<endl<<endl<<endl;
    if (opsi == 1){
        loading();
    }

    else if (opsi == 2){
    	loading();
    	playMusic();
	}

    else if (opsi == 3){
        loading_exit();
        logo_bergerak();
        tutup();
    }
    }
}

//mencetak arena permainan, bentuk ular serta makanan ular
//prosedur shape1 hingga shape80 mencetak bentuk arena persegi
void shape1()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i=0;i<lebar+2;i++)
        cout<<'-';
    cout<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        for(int j = 0; j < lebar; j++)
        {
            if (j ==0 )
                cout<< '|';
            if(i == y && j == x)
                cout<< '*';
            else if (i==bY && j==bX)
                cout<<"a";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"*";//ular
                        print=true;
                    }
                }
                if(!print)
                        cout<<' ';
                }
            if(j==lebar-1)
                cout<<'|';
                }
            cout<<endl;
            }
    for(int i=0;i<lebar+2;i++)
        cout<<'-';
    cout<<endl;
}
void shape2()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< '-';
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< '|';
            if (i==y && j==x)
            {
                cout<< '*';//ular
            }
            else if (i==bY && j==bX)
                cout<<'b';//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<'*';//ular
                        print=true;
                    }
                }
                if(!print)
                    cout<<' ';
            }
            if(j==lebar-1)
                cout<<'|';
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
cout<<endl;
}
void shape3()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "*";//ular
            }
            else if (i==bY && j==bX)
                cout<<"d";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"*";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
    cout<<endl;
}
void shape4()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "*";//ular
            }
            else if (i==bY && j==bX)
                cout<<"e";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"*";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
    cout<<endl;
}
void shape5()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "*";//ular
            }
            else if (i==bY && j==bX)
                cout<<"n";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"*";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
    cout<<endl;
}
void shape6()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "*";//ular
            }
            else if (i==bY && j==bX)
                cout<<"r";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"*";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
    cout<<endl;
}
void shape7()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "*";//ular
            }
            else if (i==bY && j==bX)
                cout<<"q";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"*";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape8()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "*";//ular
            }
            else if (i==bY && j==bX)
                cout<<"t";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"*";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape9()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i=0;i<lebar+2;i++)
        cout<<'-';
    cout<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        for(int j = 0; j < lebar; j++)
        {
            if (j ==0 )
                cout<< '|';
            if(i == y && j == x)
                cout<< '0';
            else if (i==bY && j==bX)
                cout<<"a";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"0";//ular
                        print=true;
                    }
                }
                if(!print)
                        cout<<' ';
                }
            if(j==lebar-1)
                cout<<'|';
                }
            cout<<endl;
            }
    for(int i=0;i<lebar+2;i++)
        cout<<'-';
    cout<<endl;
}
void shape10()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "0";//ular
            }
            else if (i==bY && j==bX)
                cout<<"b";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"0";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape11()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "0";//ular
            }
            else if (i==bY && j==bX)
                cout<<"d";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"0";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape12()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "0";//ular
            }
            else if (i==bY && j==bX)
                cout<<"e";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"0";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape13()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "0";//ular
            }
            else if (i==bY && j==bX)
                cout<<"n";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"0";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape14 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "0";//ular
            }
            else if (i==bY && j==bX)
                cout<<"r";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"0";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape15 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "0";//ular
            }
            else if (i==bY && j==bX)
                cout<<"q";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"0";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape16 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "0";//ular
            }
            else if (i==bY && j==bX)
                cout<<"t";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"0";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape17 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "~";//ular
            }
            else if (i==bY && j==bX)
                cout<<"a";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"~";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape18 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "~";//ular
            }
            else if (i==bY && j==bX)
                cout<<"b";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"~";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape19 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "~";//ular
            }
            else if (i==bY && j==bX)
                cout<<"d";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"~";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape20 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "~";//ular
            }
            else if (i==bY && j==bX)
                cout<<"e";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"~";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape21 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "~";//ular
            }
            else if (i==bY && j==bX)
                cout<<"n";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"~";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape22 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "~";//ular
            }
            else if (i==bY && j==bX)
                cout<<"r";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"~";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape23 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "~";//ular
            }
            else if (i==bY && j==bX)
                cout<<"q";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"~";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape24 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "~";//ular
            }
            else if (i==bY && j==bX)
                cout<<"t";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"~";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape25 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "#";//ular
            }
            else if (i==bY && j==bX)
                cout<<"a";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"#";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}


void shape26 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "#";//ular
            }
            else if (i==bY && j==bX)
                cout<<"b";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"#";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape27 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "#";//ular
            }
            else if (i==bY && j==bX)
                cout<<"d";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"#";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape28 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "#";//ular
            }
            else if (i==bY && j==bX)
                cout<<"e";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"#";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape29 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "#";//ular
            }
            else if (i==bY && j==bX)
                cout<<"n";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"#";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape30 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "#";//ular
            }
            else if (i==bY && j==bX)
                cout<<"r";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"#";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape31 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "#";//ular
            }
            else if (i==bY && j==bX)
                cout<<"q";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"#";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape32 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "#";//ular
            }
            else if (i==bY && j==bX)
                cout<<"t";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"#";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape33 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "@";//ular
            }
            else if (i==bY && j==bX)
                cout<<"a";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"@";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape34 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "@";//ular
            }
            else if (i==bY && j==bX)
                cout<<"b";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"@";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape35 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "@";//ular
            }
            else if (i==bY && j==bX)
                cout<<"d";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"@";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape36 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "@";//ular
            }
            else if (i==bY && j==bX)
                cout<<"e";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"@";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape37 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "@";//ular
            }
            else if (i==bY && j==bX)
                cout<<"n";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"@";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape38 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "@";//ular
            }
            else if (i==bY && j==bX)
                cout<<"r";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"@";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape39 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "@";//ular
            }
            else if (i==bY && j==bX)
                cout<<"q";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"@";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape40 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "@";//ular
            }
            else if (i==bY && j==bX)
                cout<<"t";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"@";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape41 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "Z";//ular
            }
            else if (i==bY && j==bX)
                cout<<"a";//makanan
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"Z";//ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape42()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "Z";
            }
            else if (i==bY && j==bX)
                cout<<"b";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"Z";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape43()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "Z";
            }
            else if (i==bY && j==bX)
                cout<<"d";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"Z";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape44()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "Z";
            }
            else if (i==bY && j==bX)
                cout<<"e";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"Z";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape45()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "Z";
            }
            else if (i==bY && j==bX)
                cout<<"n";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"Z";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape46()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "Z";
            }
            else if (i==bY && j==bX)
                cout<<"r";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"Z";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape47()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "Z";
            }
            else if (i==bY && j==bX)
                cout<<"q";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"Z";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape48()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "Z";
            }
            else if (i==bY && j==bX)
                cout<<"t";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"Z";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape49()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "A";
            }
            else if (i==bY && j==bX)
                cout<<"a";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"A";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape50()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "A";
            }
            else if (i==bY && j==bX)
                cout<<"b";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"A";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape51()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "A";
            }
            else if (i==bY && j==bX)
                cout<<"d";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"A";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape52 ()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "A";
            }
            else if (i==bY && j==bX)
                cout<<"e";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"A";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape53()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "A";
            }
            else if (i==bY && j==bX)
                cout<<"n";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"A";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape54()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "A";
            }
            else if (i==bY && j==bX)
                cout<<"r";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"A";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape55()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "A";
            }
            else if (i==bY && j==bX)
                cout<<"q";
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"A";
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape56()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "A"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"t"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"A"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape57()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "%"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"a"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"%"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape58()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "%"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"b"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"%"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape59()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "%"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"d"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"%"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape60()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "%"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"e"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"%"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape61()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "%"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"n"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"%"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape62()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "%"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"r"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"%"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape63()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "%"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"q"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"%"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape64()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "%"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"t"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"%"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape65()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "<"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"a"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"<"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}
void shape66()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "<"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"b"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"<"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape67()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "<"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"d"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"<"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape68()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "<"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"e"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"<"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape69()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "<"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"n"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"<"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape70()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "<"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"r"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"<"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape71()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "<"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"q"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"<"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape72()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "<"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"t"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"<"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape73()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "X"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"a"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"X"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape74()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "X"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"b"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"X"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape75()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "X"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"d"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"X"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape76()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "X"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"e"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"X"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape77()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "X"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"n"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"X"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape78()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "X"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"r"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"X"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape79()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "X"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"q"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"X"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

void shape80()
{
    system ("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for (int i=0; i< lebar+2;i++)
        cout<< "-";
    cout<<endl;
    for (int i=0; i<tinggi;i++)
    {
        for (int j=0;j< lebar;j++)
        {
            if (j==0)
            cout<< "|";
            if (i==y && j==x)
            {
                cout<< "X"; //kepala ular
            }
            //bX adalah koordinat x makanan ular bY adalah koordinat y makanan ular
            else if (i==bY && j==bX)
                cout<<"t"; //makanan ular
            else
            {
                bool print=false;
                for (int k=0;k<nTail;k++)
                {
                    if (tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"X"; //ekor ular
                        print=true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if(j==lebar-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i=0;i<lebar+2;i++)
        cout<<"-";
        cout<<endl;
}

//prosedur shape81 hingga shape160 untuk mencetak arena segitiga
void shape81()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '*';
                else if (i == bY && j == bX) // makanan
                    cout << 'a';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '*';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' ';
            }
        }
       cout<<endl;
}
}


void shape82()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '*';
                else if (i == bY && j == bX) // makanan
                    cout << 'b';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '*';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}

void shape83()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '*';
                else if (i == bY && j == bX) // makanan
                    cout << 'd';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '*';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}

void shape84()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '*';
                else if (i == bY && j == bX) // makanan
                    cout << 'e';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '*';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}

void shape85()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '*';
                else if (i == bY && j == bX) // makanan
                    cout << 'n';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '*';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}

void shape86()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '*';
                else if (i == bY && j == bX) // makanan
                    cout << 'r';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '*';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}


void shape87()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '*';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '*';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}

void shape88()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '*';
                else if (i == bY && j == bX) // makanan
                    cout << 't';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '*';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}


void shape89()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '0';
                else if (i == bY && j == bX) // makanan
                    cout << 'a';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '0';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}

void shape90()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '0';
                else if (i == bY && j == bX) // makanan
                    cout << 'b';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '0';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}

void shape91()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '0';
                else if (i == bY && j == bX) // makanan
                    cout << 'd';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '0';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}


void shape92()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '0';
                else if (i == bY && j == bX) // makanan
                    cout << 'e';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '0';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}


void shape93()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '0';
                else if (i == bY && j == bX) // makanan
                    cout << 'n';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '0';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
       cout<<endl;
}
}

void shape94()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '0';
                else if (i == bY && j == bX) // makanan
                    cout << 'r';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '0';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
    cout<<endl;
}
}

void shape95()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '0';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '0';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
    cout<<endl;
}
}

void shape96()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '0';
                else if (i == bY && j == bX) // makanan
                    cout << 't';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '0';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
    cout<<endl;
}
}

void shape97()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '~';
                else if (i == bY && j == bX) // makanan
                    cout << 'a';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '~';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
    cout<<endl;
}
}


void shape98()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '~';
                else if (i == bY && j == bX) // makanan
                    cout << 'b';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '~';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
    cout<<endl;
}
}


void shape99()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '~';
                else if (i == bY && j == bX) // makanan
                    cout << 'd';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '~';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
    cout<<endl;
}
}

void shape100()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '~';
                else if (i == bY && j == bX) // makanan
                    cout << 'e';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '~';//ular
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
    cout<<endl;
}
}

void shape101()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '~';
                else if (i == bY && j == bX) // makanan
                    cout << 'n';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '~';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
    cout<<endl;
}
}

void shape102()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '~';
                else if (i == bY && j == bX) // makanan
                    cout << 'r';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '~';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape103()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '~';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '~';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape104()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '~';
                else if (i == bY && j == bX) // makanan
                    cout << 't';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '~';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape105()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '#';
                else if (i == bY && j == bX) // makanan
                    cout << 'a';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '#';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}


void shape106()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '#';
                else if (i == bY && j == bX) // makanan
                    cout << 'b';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '#';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}


void shape107()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '#';
                else if (i == bY && j == bX) // makanan
                    cout << 'd';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '#';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}


void shape108()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '#';
                else if (i == bY && j == bX) // makanan
                    cout << 'e';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '#';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}


void shape109()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '#';
                else if (i == bY && j == bX) // makanan
                    cout << 'n';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '#';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}


void shape110()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '#';
                else if (i == bY && j == bX) // makanan
                    cout << 'r';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '#';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape111()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'A';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'A';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape112()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'A';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'A';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape113()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '@';
                else if (i == bY && j == bX) // makanan
                    cout << 'a';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '@';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape114()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '@';
                else if (i == bY && j == bX) // makanan
                    cout << 'b';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '@';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape115()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '@';
                else if (i == bY && j == bX) // makanan
                    cout << 'd';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '@';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape116()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '@';
                else if (i == bY && j == bX) // makanan
                    cout << 'e';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '@';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape117()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '@';
                else if (i == bY && j == bX) // makanan
                    cout << 'n';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '@';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape118()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '@';
                else if (i == bY && j == bX) // makanan
                    cout << 'r';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '@';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape119()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '@';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '@';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape120()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '@';
                else if (i == bY && j == bX) // makanan
                    cout << 't';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '@';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape121()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'Z';
                else if (i == bY && j == bX) // makanan
                    cout << 'a';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'Z';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape122()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'Z';
                else if (i == bY && j == bX) // makanan
                    cout << 'b';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'Z';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape123()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'Z';
                else if (i == bY && j == bX) // makanan
                    cout << 'd';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'Z';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape124()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'Z';
                else if (i == bY && j == bX) // makanan
                    cout << 'e';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'Z';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape125()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'Z';
                else if (i == bY && j == bX) // makanan
                    cout << 'n';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'Z';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape126()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'Z';
                else if (i == bY && j == bX) // makanan
                    cout << 'r';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'Z';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape127()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'Z';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'Z';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape128()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'Z';
                else if (i == bY && j == bX) // makanan
                    cout << 't';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'Z';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape129()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'A';
                else if (i == bY && j == bX) // makanan
                    cout << 'a';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'A';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape130()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'A';
                else if (i == bY && j == bX) // makanan
                    cout << 'b';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'A';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape131()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'A';
                else if (i == bY && j == bX) // makanan
                    cout << 'd';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'A';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape132()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'A';
                else if (i == bY && j == bX) // makanan
                    cout << 'e';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'A';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape133()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'A';
                else if (i == bY && j == bX) // makanan
                    cout << 'n';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'A';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape134()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'A';
                else if (i == bY && j == bX) // makanan
                    cout << 'r';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'A';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape135()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'A';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'A';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape136()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'A';
                else if (i == bY && j == bX) // makanan
                    cout << 't';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'A';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape137()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '%';
                else if (i == bY && j == bX) // makanan
                    cout << 'a';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '%';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape138()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '%';
                else if (i == bY && j == bX) // makanan
                    cout << 'b';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '%';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape139()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '%';
                else if (i == bY && j == bX) // makanan
                    cout << 'd';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '%';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape140()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '%';
                else if (i == bY && j == bX) // makanan
                    cout << 'e';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '%';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape141()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '%';
                else if (i == bY && j == bX) // makanan
                    cout << 'n';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '%';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape142()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '%';
                else if (i == bY && j == bX) // makanan
                    cout << 'r';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '%';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape143()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '%';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '%';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape144()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '%';
                else if (i == bY && j == bX) // makanan
                    cout << 't';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '%';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape145()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '<';
                else if (i == bY && j == bX) // makanan
                    cout << 'a';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '<';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape146()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '<';
                else if (i == bY && j == bX) // makanan
                    cout << 'b';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '<';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape147()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '<';
                else if (i == bY && j == bX) // makanan
                    cout << 'd';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '<';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape148()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '<';
                else if (i == bY && j == bX) // makanan
                    cout << 'e';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '<';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape149()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '<';
                else if (i == bY && j == bX) // makanan
                    cout << 'n';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '<';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape150()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '<';
                else if (i == bY && j == bX) // makanan
                    cout << 'r';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '<';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape151()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '<';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '<';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}
void shape152()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << '<';
                else if (i == bY && j == bX) // makanan
                    cout << 't';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << '<';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}
void shape153()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'X';
                else if (i == bY && j == bX) // makanan
                    cout << 'a';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'X';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}
void shape154()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'X';
                else if (i == bY && j == bX) // makanan
                    cout << 'b';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'X';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}void shape155()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'X';
                else if (i == bY && j == bX) // makanan
                    cout << 'd';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'X';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}
void shape156()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'X';
                else if (i == bY && j == bX) // makanan
                    cout << 'e';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'X';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}
void shape157()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'X';
                else if (i == bY && j == bX) // makanan
                    cout << 'n';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'X';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}
void shape158()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'X';
                else if (i == bY && j == bX) // makanan
                    cout << 'r';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'X';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}
void shape159()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'X';
                else if (i == bY && j == bX) // makanan
                    cout << 'q';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'X';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

void shape160()
{
    system("cls"); // membersihkan layar
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << " ";
        for(int j = 0; j < tinggi*2; j++)
        {
            if (j >= tinggi - i - 1 && j <= tinggi + i - 1) // cek apakah di dalam segitiga
            {
                if (i == tinggi - 1 || j == tinggi - i - 1 || j == tinggi + i - 1) // dinding
                    cout << '*';
                else if (i == y && j == x) // kepala ular
                    cout << 'X';
                else if (i == bY && j == bX) // makanan
                    cout << 't';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) // tubuh ular
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << 'X';
                            print = true;
                        }
                    }
                    if (!print) // ruang kosong di dalam ular
                        cout << ' ';
                }
            }
            else
            {
                cout << ' '; // spasi di luar segitiga
            }
        }
        cout<<endl;
}
}

//prosedur shape 161 hingga shape 240 untuk mencetak bentuk arena jajargenjang
void shape161()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '*';
            else if (i == bY && j == bX) // Makanan
                cout << 'a';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '*';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape162()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '*';
            else if (i == bY && j == bX) // Makanan
                cout << 'b';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '*';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape163()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '*';
            else if (i == bY && j == bX) // Makanan
                cout << 'd';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '*';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape164()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '*';
            else if (i == bY && j == bX) // Makanan
                cout << 'e';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '*';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape165()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '*';
            else if (i == bY && j == bX) // Makanan
                cout << 'n';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '*';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape166()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '*';
            else if (i == bY && j == bX) // Makanan
                cout << 'r';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '*';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape167()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '*';
            else if (i == bY && j == bX) // Makanan
                cout << 'q';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '*';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape168()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '*';
            else if (i == bY && j == bX) // Makanan
                cout << 't';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '*';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape169()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '0';
            else if (i == bY && j == bX) // Makanan
                cout << 'a';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '0';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape170()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '0';
            else if (i == bY && j == bX) // Makanan
                cout << 'b';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '0';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape171()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '0';
            else if (i == bY && j == bX) // Makanan
                cout << 'd';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '0';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape172()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '0';
            else if (i == bY && j == bX) // Makanan
                cout << 'e';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '0';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape173()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '0';
            else if (i == bY && j == bX) // Makanan
                cout << 'n';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '0';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape174()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '0';
            else if (i == bY && j == bX) // Makanan
                cout << 'r';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '0';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape175()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '0';
            else if (i == bY && j == bX) // Makanan
                cout << 'q';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '0';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape176()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '0';
            else if (i == bY && j == bX) // Makanan
                cout << 't';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '0';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape177()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '~';
            else if (i == bY && j == bX) // Makanan
                cout << 'a';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '~';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape178()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '~';
            else if (i == bY && j == bX) // Makanan
                cout << 'b';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '~';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape179()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '~';
            else if (i == bY && j == bX) // Makanan
                cout << 'd';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '~';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape180()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '~';
            else if (i == bY && j == bX) // Makanan
                cout << 'e';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '~';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape181()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '~';
            else if (i == bY && j == bX) // Makanan
                cout << 'n';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '~';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape182()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '~';
            else if (i == bY && j == bX) // Makanan
                cout << 'r';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '~';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape183()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '~';
            else if (i == bY && j == bX) // Makanan
                cout << 'q';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '~';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape184()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '~';
            else if (i == bY && j == bX) // Makanan
                cout << 't';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '~';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape185()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '#';
            else if (i == bY && j == bX) // Makanan
                cout << 'a';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '#';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape186()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '#';
            else if (i == bY && j == bX) // Makanan
                cout << 'b';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '#';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape187()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '#';
            else if (i == bY && j == bX) // Makanan
                cout << 'd';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '#';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape188()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '#';
            else if (i == bY && j == bX) // Makanan
                cout << 'e';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '#';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape189()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '#';
            else if (i == bY && j == bX) // Makanan
                cout << 'n';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '#';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape190()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '#';
            else if (i == bY && j == bX) // Makanan
                cout << 'r';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '#';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape191()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '#';
            else if (i == bY && j == bX) // Makanan
                cout << 'q';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '#';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape192()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '#';
            else if (i == bY && j == bX) // Makanan
                cout << 't';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '#';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape193()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '@';
            else if (i == bY && j == bX) // Makanan
                cout << 'a';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '@';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape194()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '@';
            else if (i == bY && j == bX) // Makanan
                cout << 'b';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '@';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape195()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '@';
            else if (i == bY && j == bX) // Makanan
                cout << 'd';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '@';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape196()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '@';
            else if (i == bY && j == bX) // Makanan
                cout << 'e';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '@';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape197()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '@';
            else if (i == bY && j == bX) // Makanan
                cout << 'n';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '@';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape198()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '@';
            else if (i == bY && j == bX) // Makanan
                cout << 'r';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '@';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape199()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '@';
            else if (i == bY && j == bX) // Makanan
                cout << 'q';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '@';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape200()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '@';
            else if (i == bY && j == bX) // Makanan
                cout << 't';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '@';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape201()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'Z';
            else if (i == bY && j == bX) // Makanan
                cout << 'a';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'Z';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape202()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'Z';
            else if (i == bY && j == bX) // Makanan
                cout << 'b';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'Z';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape203()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'Z';
            else if (i == bY && j == bX) // Makanan
                cout << 'd';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'Z';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape204()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'Z';
            else if (i == bY && j == bX) // Makanan
                cout << 'e';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'Z';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape205()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'Z';
            else if (i == bY && j == bX) // Makanan
                cout << 'n';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'Z';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape206()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'Z';
            else if (i == bY && j == bX) // Makanan
                cout << 'r';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'Z';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape207()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'Z';
            else if (i == bY && j == bX) // Makanan
                cout << 'q';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'Z';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape208()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'Z';
            else if (i == bY && j == bX) // Makanan
                cout << 't';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'Z';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape209()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'A';
            else if (i == bY && j == bX) // Makanan
                cout << 'a';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'A';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape210()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'A';
            else if (i == bY && j == bX) // Makanan
                cout << 'b';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'A';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape211()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'A';
            else if (i == bY && j == bX) // Makanan
                cout << 'd';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'A';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape212()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'A';
            else if (i == bY && j == bX) // Makanan
                cout << 'e';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'A';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape213()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'A';
            else if (i == bY && j == bX) // Makanan
                cout << 'n';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'A';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape214()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'A';
            else if (i == bY && j == bX) // Makanan
                cout << 'r';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'A';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape215()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'A';
            else if (i == bY && j == bX) // Makanan
                cout << 'q';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'A';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape216()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'A';
            else if (i == bY && j == bX) // Makanan
                cout << 't';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'A';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape217()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '%';
            else if (i == bY && j == bX) // Makanan
                cout << 'a';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '%';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape218()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '%';
            else if (i == bY && j == bX) // Makanan
                cout << 'b';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '%';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape219()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '%';
            else if (i == bY && j == bX) // Makanan
                cout << 'd';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '%';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}
void shape220()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '%';
            else if (i == bY && j == bX) // Makanan
                cout << 'e';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '%';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape221()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '%';
            else if (i == bY && j == bX) // Makanan
                cout << 'n';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '%';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape222()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '%';
            else if (i == bY && j == bX) // Makanan
                cout << 'r';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '%';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape223()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '%';
            else if (i == bY && j == bX) // Makanan
                cout << 'q';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '%';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape224()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '%';
            else if (i == bY && j == bX) // Makanan
                cout << 't';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '%';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape225()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '<';
            else if (i == bY && j == bX) // Makanan
                cout << 'a';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '<';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape226()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '<';
            else if (i == bY && j == bX) // Makanan
                cout << 'b';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '<';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape227()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '<';
            else if (i == bY && j == bX) // Makanan
                cout << 'd';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '<';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape228()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '<';
            else if (i == bY && j == bX) // Makanan
                cout << 'e';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '<';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape229()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '<';
            else if (i == bY && j == bX) // Makanan
                cout << 'n';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '<';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape230()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '<';
            else if (i == bY && j == bX) // Makanan
                cout << 'r';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '<';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape231()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '<';
            else if (i == bY && j == bX) // Makanan
                cout << 'q';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '<';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape232()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << '<';
            else if (i == bY && j == bX) // Makanan
                cout << 't';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << '<';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape233()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'X';
            else if (i == bY && j == bX) // Makanan
                cout << 'a';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'X';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape234()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'X';
            else if (i == bY && j == bX) // Makanan
                cout << 'b';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'X';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape235()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'X';
            else if (i == bY && j == bX) // Makanan
                cout << 'd';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'X';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape236()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'X';
            else if (i == bY && j == bX) // Makanan
                cout << 'e';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'X';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape237()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'X';
            else if (i == bY && j == bX) // Makanan
                cout << 'n';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'X';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape238()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'X';
            else if (i == bY && j == bX) // Makanan
                cout << 'r';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'X';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape239()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'X';
            else if (i == bY && j == bX) // Makanan
                cout << 'q';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'X';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

void shape240()
{
    system("cls");
    cout<<"username: "<<nm[z].name<<"\t\t\t\t\t\t\t\t\t\t     score: "<<nm[z].score<<endl;
    for(int i = 0; i < tinggi; i++)
    {
        cout << string(i, ' '); // Spasi untuk membentuk jajar genjang
        for(int j = 0; j < lebar; j++)
        {
            if (i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1) // Dinding
                cout << '#';
            else if (i == y && j == x) // Kepala ular
                cout << 'X';
            else if (i == bY && j == bX) // Makanan
                cout << 't';
            else
            {
                bool print = false;
                // Cek apakah koordinat ini adalah bagian dari tubuh ular
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'X';
                        print = true;
                    }
                }
                // Cek apakah ada ruang kosong di dalam jajar genjang
                if (!print)
                {
                    bool space = true;
                    // Cek apakah koordinat ini adalah bagian dari jalur ular
                    for (int k = 1; k < nTail; k++)
                    {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            space = false;
                            break;
                        }
                    }
                    if (space)
                        cout << ' ';
                    else
                        cout << '#'; // Karakter lain selain '0' dan ' ' untuk menandai jalur ular
                }
            }
        }
        cout<<endl;
}
}

//prosedur untuk menentukan arena, bentuk ular, dan bentuk makanan yang dicetak berdasarkan pilihan pemain
void bentuk_ular_makanan (int benUlar, int benMakan, int pil)
{
    if(benUlar==1 && benMakan==1 && pil==1)
        shape1();
    else if(benUlar==1 && benMakan==2 && pil==1)
        shape2();
    else if(benUlar==1 && benMakan==3 && pil==1)
        shape3();
    else if(benUlar==1 && benMakan==4 && pil==1)
        shape4();
    else if(benUlar==1 && benMakan==5 && pil==1)
        shape5();
    else if(benUlar==1 && benMakan==6 && pil==1)
        shape6();
    else if(benUlar==1 && benMakan==7 && pil==1)
        shape7();
    else if(benUlar==1 && benMakan==8 && pil==1)
        shape8();
    else if(benUlar==2 && benMakan==1 && pil==1)
        shape9();
    else if(benUlar==2 && benMakan==2 && pil==1)
        shape10();
    else if(benUlar==2 && benMakan==3 && pil==1)
        shape11();
    else if(benUlar==2 && benMakan==4 && pil==1)
        shape12();
    else if(benUlar==2 && benMakan==5 && pil==1)
        shape13();
    else if(benUlar==2 && benMakan==6 && pil==1)
        shape14();
    else if(benUlar==2 && benMakan==7 && pil==1)
        shape15();
    else if(benUlar==2 && benMakan==8 && pil==1)
        shape16();
    else if(benUlar==3 && benMakan==1 && pil==1)
        shape17();
    else if(benUlar==3 && benMakan==2 && pil==1)
        shape18();
    else if(benUlar==3 && benMakan==3 && pil==1)
        shape19();
    else if(benUlar==3 && benMakan==4 && pil==1)
        shape20();
    else if(benUlar==3 && benMakan==5 && pil==1)
        shape21();
    else if(benUlar==3 && benMakan==6 && pil==1)
        shape22();
    else if(benUlar==3 && benMakan==7 && pil==1)
        shape23();
    else if(benUlar==3 && benMakan==8 && pil==1)
        shape24();
    else if(benUlar==4 && benMakan==1 && pil==1)
        shape25();
    else if(benUlar==4 && benMakan==2 && pil==1)
        shape26();
    else if(benUlar==4 && benMakan==3 && pil==1)
        shape27();
    else if(benUlar==4 && benMakan==4 && pil==1)
        shape28();
    else if(benUlar==4 && benMakan==5 && pil==1)
        shape29();
    else if(benUlar==4 && benMakan==6 && pil==1)
        shape30();
    else if(benUlar==4 && benMakan==7 && pil==1)
        shape31();
    else if(benUlar==4 && benMakan==8 && pil==1)
        shape32();
    else if(benUlar==5 && benMakan==1 && pil==1)
        shape33();
    else if(benUlar==5 && benMakan==2 && pil==1)
        shape34();
    else if(benUlar==5 && benMakan==3 && pil==1)
        shape35();
    else if(benUlar==5 && benMakan==4 && pil==1)
        shape36();
    else if(benUlar==5 && benMakan==5 && pil==1)
        shape37();
    else if(benUlar==5 && benMakan==6 && pil==1)
        shape38();
    else if(benUlar==5 && benMakan==7 && pil==1)
        shape39();
    else if(benUlar==5 && benMakan==8 && pil==1)
        shape40();
    else if(benUlar==6 && benMakan==1 && pil==1)
        shape41();
    else if(benUlar==6 && benMakan==2 && pil==1)
        shape42();
    else if(benUlar==6 && benMakan==3 && pil==1)
        shape43();
    else if(benUlar==6 && benMakan==4 && pil==1)
        shape44();
    else if(benUlar==6 && benMakan==5 && pil==1)
        shape45();
    else if(benUlar==6 && benMakan==6 && pil==1)
        shape46();
    else if(benUlar==6 && benMakan==7 && pil==1)
        shape47();
    else if(benUlar==6 && benMakan==8 && pil==1)
        shape48();
    else if(benUlar==7 && benMakan==1 && pil==1)
        shape49();
    else if(benUlar==7 && benMakan==2 && pil==1)
        shape50();
    else if(benUlar==7 && benMakan==3 && pil==1)
        shape51();
    else if(benUlar==7 && benMakan==4 && pil==1)
        shape52();
    else if(benUlar==7 && benMakan==5 && pil==1)
        shape53();
    else if(benUlar==7 && benMakan==6 && pil==1)
        shape54();
    else if(benUlar==7 && benMakan==7 && pil==1)
        shape55();
    else if(benUlar==7 && benMakan==8 && pil==1)
        shape56();
    else if(benUlar==8 && benMakan==1 && pil==1)
        shape57();
    else if(benUlar==8 && benMakan==2 && pil==1)
        shape58();
    else if(benUlar==8 && benMakan==3 && pil==1)
        shape59();
    else if(benUlar==8 && benMakan==4 && pil==1)
        shape60();
    else if(benUlar==8 && benMakan==5 && pil==1)
        shape61();
    else if(benUlar==8 && benMakan==6 && pil==1)
        shape62();
    else if(benUlar==8 && benMakan==7 && pil==1)
        shape63();
    else if(benUlar==8 && benMakan==8 && pil==1)
        shape64();
    else if(benUlar==9 && benMakan==1 && pil==1)
        shape65();
    else if(benUlar==9 && benMakan==2 && pil==1)
        shape66();
    else if(benUlar==9 && benMakan==3 && pil==1)
        shape67();
    else if(benUlar==9 && benMakan==4 && pil==1)
        shape68();
    else if(benUlar==9 && benMakan==5 && pil==1)
        shape69();
    else if(benUlar==9 && benMakan==6 && pil==1)
        shape70();
    else if(benUlar==9 && benMakan==7 && pil==1)
        shape71();
    else if(benUlar==9 && benMakan==8 && pil==1)
        shape72();
    else if(benUlar==10 && benMakan==1 && pil==1)
        shape73();
    else if(benUlar==10 && benMakan==2 && pil==1)
        shape74();
    else if(benUlar==10 && benMakan==3 && pil==1)
        shape75();
    else if(benUlar==10 && benMakan==4 && pil==1)
        shape76();
    else if(benUlar==10 && benMakan==5 && pil==1)
        shape77();
    else if(benUlar==10 && benMakan==6 && pil==1)
        shape78();
    else if(benUlar==10 && benMakan==7 && pil==1)
        shape79();
    else if(benUlar==10 && benMakan==8 && pil==1)
        shape80();
    else if(benUlar==1 && benMakan==1 && pil==2)
        shape81();
    else if(benUlar==1 && benMakan==2 && pil==2)
        shape82();
    else if(benUlar==1 && benMakan==3 && pil==2)
        shape83();
    else if(benUlar==1 && benMakan==4 && pil==2)
        shape84();
    else if(benUlar==1 && benMakan==5 && pil==2)
        shape85();
    else if(benUlar==1 && benMakan==6 && pil==2)
        shape86();
    else if(benUlar==1 && benMakan==7 && pil==2)
        shape87();
    else if(benUlar==1 && benMakan==8 && pil==2)
        shape88();
    else if(benUlar==2 && benMakan==1 && pil==2)
        shape89();
    else if(benUlar==2 && benMakan==2 && pil==2)
        shape90();
    else if(benUlar==2 && benMakan==3 && pil==2)
        shape91();
    else if(benUlar==2 && benMakan==4 && pil==2)
        shape92();
    else if(benUlar==2 && benMakan==5 && pil==2)
        shape93();
    else if(benUlar==2 && benMakan==6 && pil==2)
        shape94();
    else if(benUlar==2 && benMakan==7 && pil==2)
        shape95();
    else if(benUlar==2 && benMakan==8 && pil==2)
        shape96();
    else if(benUlar==3 && benMakan==1 && pil==2)
        shape97();
    else if(benUlar==3 && benMakan==2 && pil==2)
        shape98();
    else if(benUlar==3 && benMakan==3 && pil==2)
        shape99();
    else if(benUlar==3 && benMakan==4 && pil==2)
        shape100();
    else if(benUlar==3 && benMakan==5 && pil==2)
        shape101();
    else if(benUlar==3 && benMakan==6 && pil==2)
        shape102();
    else if(benUlar==3 && benMakan==7 && pil==2)
        shape103();
    else if(benUlar==3 && benMakan==8 && pil==2)
        shape104();
    else if(benUlar==4 && benMakan==1 && pil==2)
        shape105();
    else if(benUlar==4 && benMakan==2 && pil==2)
        shape106();
    else if(benUlar==4 && benMakan==3 && pil==2)
        shape107();
    else if(benUlar==4 && benMakan==4 && pil==2)
        shape108();
    else if(benUlar==4 && benMakan==5 && pil==2)
        shape109();
    else if(benUlar==4 && benMakan==6 && pil==2)
        shape110();
    else if(benUlar==4 && benMakan==7 && pil==2)
        shape111();
    else if(benUlar==4 && benMakan==8 && pil==2)
        shape112();
    else if(benUlar==5 && benMakan==1 && pil==2)
        shape113();
    else if(benUlar==5 && benMakan==2 && pil==2)
        shape114();
    else if(benUlar==5 && benMakan==3 && pil==2)
        shape115();
    else if(benUlar==5 && benMakan==4 && pil==2)
        shape116();
    else if(benUlar==5 && benMakan==5 && pil==2)
        shape117();
    else if(benUlar==5 && benMakan==6 && pil==2)
        shape118();
    else if(benUlar==5 && benMakan==7 && pil==2)
        shape119();
    else if(benUlar==5 && benMakan==8 && pil==2)
        shape120();
    else if(benUlar==6 && benMakan==1 && pil==2)
        shape121();
    else if(benUlar==6 && benMakan==2 && pil==2)
        shape122();
    else if(benUlar==6 && benMakan==3 && pil==2)
        shape123();
    else if(benUlar==6 && benMakan==4 && pil==2)
        shape124();
    else if(benUlar==6 && benMakan==5 && pil==2)
        shape125();
    else if(benUlar==6 && benMakan==6 && pil==2)
        shape126();
    else if(benUlar==6 && benMakan==7 && pil==2)
        shape127();
    else if(benUlar==6 && benMakan==8 && pil==2)
        shape128();
    else if(benUlar==7 && benMakan==1 && pil==2)
        shape129();
    else if(benUlar==7 && benMakan==2 && pil==2)
        shape130();
    else if(benUlar==7 && benMakan==3 && pil==2)
        shape131();
    else if(benUlar==7 && benMakan==4 && pil==2)
        shape132();
    else if(benUlar==7 && benMakan==5 && pil==2)
        shape133();
    else if(benUlar==7 && benMakan==6 && pil==2)
        shape134();
    else if(benUlar==7 && benMakan==7 && pil==2)
        shape135();
    else if(benUlar==7 && benMakan==8 && pil==2)
        shape136();
    else if(benUlar==8 && benMakan==1 && pil==2)
        shape137();
    else if(benUlar==8 && benMakan==2 && pil==2)
        shape138();
    else if(benUlar==8 && benMakan==3 && pil==2)
        shape139();
    else if(benUlar==8 && benMakan==4 && pil==2)
        shape140();
    else if(benUlar==8 && benMakan==5 && pil==2)
        shape141();
    else if(benUlar==8 && benMakan==6 && pil==2)
        shape142();
    else if(benUlar==8 && benMakan==7 && pil==2)
        shape143();
    else if(benUlar==8 && benMakan==8 && pil==2)
        shape144();
    else if(benUlar==9 && benMakan==1 && pil==2)
        shape145();
    else if(benUlar==9 && benMakan==2 && pil==2)
        shape146();
    else if(benUlar==9 && benMakan==3 && pil==2)
        shape147();
    else if(benUlar==9 && benMakan==4 && pil==2)
        shape148();
    else if(benUlar==9 && benMakan==5 && pil==2)
        shape149();
    else if(benUlar==9 && benMakan==6 && pil==2)
        shape150();
    else if(benUlar==9 && benMakan==7 && pil==2)
        shape151();
    else if(benUlar==9 && benMakan==8 && pil==2)
        shape152();
    else if(benUlar==10 && benMakan==1 && pil==2)
        shape153();
    else if(benUlar==10 && benMakan==2 && pil==2)
        shape154();
    else if(benUlar==10 && benMakan==3 && pil==2)
        shape155();
    else if(benUlar==10 && benMakan==4 && pil==2)
        shape156();
    else if(benUlar==10 && benMakan==5 && pil==2)
        shape157();
    else if(benUlar==10 && benMakan==6 && pil==2)
        shape158();
    else if(benUlar==10 && benMakan==7 && pil==2)
        shape159();
    else if(benUlar==10 && benMakan==8 && pil==2)
        shape160();
    else if(benUlar==1 && benMakan==1 && pil==3)
        shape161();
    else if(benUlar==1 && benMakan==2 && pil==3)
        shape162();
    else if(benUlar==1 && benMakan==3 && pil==3)
        shape163();
    else if(benUlar==1 && benMakan==4 && pil==3)
        shape164();
    else if(benUlar==1 && benMakan==5 && pil==3)
        shape165();
    else if(benUlar==1 && benMakan==6 && pil==3)
        shape166();
    else if(benUlar==1 && benMakan==7 && pil==3)
        shape167();
    else if(benUlar==1 && benMakan==8 && pil==3)
        shape168();
    else if(benUlar==2 && benMakan==1 && pil==3)
        shape169();
    else if(benUlar==2 && benMakan==2 && pil==3)
        shape170();
    else if(benUlar==2 && benMakan==3 && pil==3)
        shape171();
    else if(benUlar==2 && benMakan==4 && pil==3)
        shape172();
    else if(benUlar==2 && benMakan==5 && pil==3)
        shape173();
    else if(benUlar==2 && benMakan==6 && pil==3)
        shape174();
    else if(benUlar==2 && benMakan==7 && pil==3)
        shape175();
    else if(benUlar==2 && benMakan==8 && pil==3)
        shape176();
    else if(benUlar==3 && benMakan==1 && pil==3)
        shape177();
    else if(benUlar==3 && benMakan==2 && pil==3)
        shape178();
    else if(benUlar==3 && benMakan==3 && pil==3)
        shape179();
    else if(benUlar==3 && benMakan==4 && pil==3)
        shape180();
    else if(benUlar==3 && benMakan==5 && pil==3)
        shape181();
    else if(benUlar==3 && benMakan==6 && pil==3)
        shape182();
    else if(benUlar==3 && benMakan==7 && pil==3)
        shape183();
    else if(benUlar==3 && benMakan==8 && pil==3)
        shape184();
    else if(benUlar==4 && benMakan==1 && pil==3)
        shape185();
    else if(benUlar==4 && benMakan==2 && pil==3)
        shape186();
    else if(benUlar==4 && benMakan==3 && pil==3)
        shape187();
    else if(benUlar==4 && benMakan==4 && pil==3)
        shape188();
    else if(benUlar==4 && benMakan==5 && pil==3)
        shape189();
    else if(benUlar==4 && benMakan==6 && pil==3)
        shape190();
    else if(benUlar==4 && benMakan==7 && pil==3)
        shape191();
    else if(benUlar==4 && benMakan==8 && pil==3)
        shape192();
    else if(benUlar==5 && benMakan==1 && pil==3)
        shape193();
    else if(benUlar==5 && benMakan==2 && pil==3)
        shape194();
    else if(benUlar==5 && benMakan==3 && pil==3)
        shape195();
    else if(benUlar==5 && benMakan==4 && pil==3)
        shape196();
    else if(benUlar==5 && benMakan==5 && pil==3)
        shape197();
    else if(benUlar==5 && benMakan==6 && pil==3)
        shape198();
    else if(benUlar==5 && benMakan==7 && pil==3)
        shape199();
    else if(benUlar==5 && benMakan==8 && pil==3)
        shape200();
    else if(benUlar==6 && benMakan==1 && pil==3)
        shape201();
    else if(benUlar==6 && benMakan==2 && pil==3)
        shape202();
    else if(benUlar==6 && benMakan==3 && pil==3)
        shape203();
    else if(benUlar==6 && benMakan==4 && pil==3)
        shape204();
    else if(benUlar==6 && benMakan==5 && pil==3)
        shape205();
    else if(benUlar==6 && benMakan==6 && pil==3)
        shape206();
    else if(benUlar==6 && benMakan==7 && pil==3)
        shape207();
    else if(benUlar==6 && benMakan==8 && pil==3)
        shape208();
    else if(benUlar==7 && benMakan==1 && pil==3)
        shape209();
    else if(benUlar==7 && benMakan==2 && pil==3)
        shape210();
    else if(benUlar==7 && benMakan==3 && pil==3)
        shape211();
    else if(benUlar==7 && benMakan==4 && pil==3)
        shape212();
    else if(benUlar==7 && benMakan==5 && pil==3)
        shape213();
    else if(benUlar==7 && benMakan==6 && pil==3)
        shape214();
    else if(benUlar==7 && benMakan==7 && pil==3)
        shape215();
    else if(benUlar==7 && benMakan==8 && pil==3)
        shape216();
    else if(benUlar==8 && benMakan==1 && pil==3)
        shape217();
    else if(benUlar==8 && benMakan==2 && pil==3)
        shape218();
    else if(benUlar==8 && benMakan==3 && pil==3)
        shape219();
    else if(benUlar==8 && benMakan==4 && pil==3)
        shape220();
    else if(benUlar==8 && benMakan==5 && pil==3)
        shape221();
    else if(benUlar==8 && benMakan==6 && pil==3)
        shape222();
    else if(benUlar==8 && benMakan==7 && pil==3)
        shape223();
    else if(benUlar==8 && benMakan==8 && pil==3)
        shape224();
    else if(benUlar==9 && benMakan==1 && pil==3)
        shape225();
    else if(benUlar==9 && benMakan==2 && pil==3)
        shape226();
    else if(benUlar==9 && benMakan==3 && pil==3)
        shape227();
    else if(benUlar==9 && benMakan==4 && pil==3)
        shape228();
    else if(benUlar==9 && benMakan==5 && pil==3)
        shape229();
    else if(benUlar==9 && benMakan==6 && pil==3)
        shape230();
    else if(benUlar==9 && benMakan==7 && pil==3)
        shape231();
    else if(benUlar==9 && benMakan==8 && pil==3)
        shape232();
    else if(benUlar==10 && benMakan==1 && pil==3)
        shape233();
    else if(benUlar==10 && benMakan==2 && pil==3)
        shape234();
    else if(benUlar==10 && benMakan==3 && pil==3)
        shape235();
    else if(benUlar==10 && benMakan==4 && pil==3)
        shape236();
    else if(benUlar==10 && benMakan==5 && pil==3)
        shape237();
    else if(benUlar==10 && benMakan==6 && pil==3)
        shape238();
    else if(benUlar==10 && benMakan==7 && pil==3)
        shape239();
    else if(benUlar==10 && benMakan==8 && pil==3)
        shape240();
}

//program membaca inputan warna ular dan background
void warna_ular_background(int warnaular, int warnabg)
{
    if ( warnaular==1 && warnabg==1 )
    {
        system("color 07");
        //"Putih bg Hitam"
    }
    if ( warnaular==1 && warnabg==2 )
    {
        system("color 17");
        //"Putih bg Biru"
    }
    if ( warnaular==1 && warnabg==3 )
    {
        system("color 27");
        //"Putih bg Hijau"
    }
    if ( warnaular==1 && warnabg==4 )
    {
        system("color 37");
        //"Putih bg Aqua"
    }
    if ( warnaular==1 && warnabg==5 )
    {
        system("color 57");
        //"Putih bg Ungu"
    }
    if ( warnaular==1 && warnabg==6 )
    {
        system("color 87");
        //"Putih bg Abu-abu"
    }
    if ( warnaular==1 && warnabg==7 )
    {
        system("color 97");
        //"Putih bg Biru Muda"
    }
    if ( warnaular==1 && warnabg==8 )
    {
        system("color E7");
        //"Putih bg Kuning Muda"
    }
    if ( warnaular==1 && warnabg==9 )
    {
        system("color F7");
        //"Putih bg Light White"
    }
    if ( warnaular==1 && warnabg==10 )
    {
        system("color B7");
        //"Putih bg Light Aqua"
    }
    if ( warnaular==2 && warnabg==1 )
    {
        system("color 04");
        //"Merah bg Hitam"
    }
    if ( warnaular==2 && warnabg==2 )
    {
        system("color 14");
        //"Merah bg Biru"
    }
    if ( warnaular==2 && warnabg==3 )
    {
        system("color 24");
        //"Merah bg Hijau"
    }
    if ( warnaular==2 && warnabg==4 )
    {
        system("color 34");
        //"Merah bg Aqua"
    }
    if ( warnaular==2 && warnabg==5 )
    {
        system("color 54");
        //"Merah bg Ungu"
    }
    if ( warnaular==2 && warnabg==6 )
    {
        system("color 84");
       //"Merah bg Abu-abu"
    }
    if ( warnaular==2 && warnabg==7 )
    {
        system("color 94");
    //"Merah bg Biru Muda"
    }
    if ( warnaular==2 && warnabg==8 )
    {
        system("color E4");
        //"Merah bg Kuning Muda"
    }
    if ( warnaular==2 && warnabg==9 )
    {
        system("color F4");
        //"Merah bg Light White"
    }
    if ( warnaular==2 && warnabg==10 )
    {
        system("color B4");
        //"Merah bg Light Aqua"
    }
    if ( warnaular==3 && warnabg==1 )
    {
        system("color 0D");
        //"Ungu muda bg Hitam"
    }
    if ( warnaular==3 && warnabg==2 )
    {
        system("color 1D");
        //"Ungu muda bg Biru"
    }
    if ( warnaular==3 && warnabg==3 )
    {
        system("color 2D");
        //"Ungu muda bg Hijau"
    }
    if ( warnaular==3 && warnabg==4 )
    {
        system("color 3D");
       //"Ungu muda bg Aqua"
    }
    if ( warnaular==3 && warnabg==5 )
    {
        system("color 5D");
       //"Ungu muda bg Ungu"
    }
    if ( warnaular==3 && warnabg==6 )
    {
        system("color 8D");
       //"Ungu muda bg Abu-abu"
    }
    if ( warnaular==3 && warnabg==7 )
    {
        system("color 9D");
        //"Ungu muda bg Biru Muda"
    }
    if ( warnaular==3 && warnabg==8 )
    {
        system("color ED");
        //"Ungu muda bg Kuning Muda"
    }
    if ( warnaular==3 && warnabg==9 )
    {
        system("color FD");
        //"Ungu muda bg Light White"
    }
    if ( warnaular==3 && warnabg==10 )
    {
        system("color BD");
        //"Ungu muda bg Light Aqua"
    }
    if ( warnaular==4 && warnabg==1 )
    {
        system("color 0A");
        //"Hijau muda bg Hitam"
    }
    if ( warnaular==4 && warnabg==2 )
    {
        system("color 1A");
        //"Hijau muda bg Biru"
    }
    if ( warnaular==4 && warnabg==3 )
    {
        system("color 2A");
        //"Hijau muda bg Hijau"
    }
    if ( warnaular==4 && warnabg==4 )
    {
        system("color 3A");
        //"Hijau muda bg Aqua"
    }
    if ( warnaular==4 && warnabg==5 )
    {
        system("color 5A");
        //"Hijau muda bg Ungu"
    }
    if ( warnaular==4 && warnabg==6 )
    {
        system("color 8A");
        //"Hijau muda bg Abu-abu"
    }
    if ( warnaular==4 && warnabg==7 )
    {
        system("color 9A");
        //Hijau muda bg Biru Muda"
    }
    if ( warnaular==4 && warnabg==8 )
    {
        system("color EA");
       //"Hijau muda bg Kuning Muda"
    }
    if ( warnaular==4 && warnabg==9 )
    {
        system("color FA");
       //"Hijau muda bg Light White"
    }
    if ( warnaular==4 && warnabg==10 )
    {
        system("color BA");
        //"Hijau muda bg Light Aqua"
    }
    if ( warnaular==5 && warnabg==1 )
    {
        system("color 06");
        //"Kuning bg Hitam"
    }
    if ( warnaular==5 && warnabg==2 )
    {
        system("color 16");
       //"Kuning bg Biru"
    }
    if ( warnaular==5 && warnabg==3 )
    {
        system("color 26");
       //"Kuning bg Hijau"
    }
    if ( warnaular==5 && warnabg==4 )
    {
        system("color 36");
       //"Kuning bg Aqua"
    }
    if ( warnaular==5 && warnabg==5 )
    {
        system("color 56");
        cout<<"Kuning bg Ungu";
        cout<<endl;
    }
    if ( warnaular==5 && warnabg==6 )
    {
        system("color 86");
        //"Kuning bg Abu-abu"
    }
    if ( warnaular==5 && warnabg==7 )
    {
        system("color 96");
       //"Kuning bg Biru Muda"
    }
    if ( warnaular==5 && warnabg==8 )
    {
        system("color E6");
       //"Kuning bg Kuning Muda"
    }
    if ( warnaular==5 && warnabg==9 )
    {
        system("color F6");
       //"Kuning bg Light White"
    }
    if ( warnaular==5 && warnabg==10 )
    {
        system("color B6");
        //"Kuning bg Light Aqua"
    }
    if ( warnaular==6 && warnabg==1 )
    {
        system("color 0C");
        //"Merah muda bg Hitam"
    }
    if ( warnaular==6 && warnabg==2 )
    {
        system("color 1C");
        //"Merah muda bg Biru"
    }
    if ( warnaular==6 && warnabg==3 )
    {
        system("color 2C");
        //"Merah muda bg Hijau"
    }
    if ( warnaular==6 && warnabg==4 )
    {
        system("color 3C");
        //"Merah muda bg Aqua"
    }
    if ( warnaular==6 && warnabg==5 )
    {
        system("color 5C");
        //"Merah muda bg Ungu"
    }
    if ( warnaular==6 && warnabg==6 )
    {
        system("color 8C");
        //"Merah muda bg Abu-abu"
    }
    if ( warnaular==6 && warnabg==7 )
    {
        system("color 9C");
       //"Merah muda bg Biru Muda"
    }
    if ( warnaular==6 && warnabg==8 )
    {
        system("color EC");
        //"Merah muda bg Kuning Muda"
    }
    if ( warnaular==6 && warnabg==9 )
    {
        system("color FC");
        //"Merah muda bg Light White"
    }
    if ( warnaular==6 && warnabg==10 )
    {
        system("color BC");
        //"Merah muda bg Light Aqua"
    }
}

//fungsi keluar
void stop(){
    int pX=pX;
    int pY=pY;
    int p2X,p2Y;
for(int i=0;i<nTail;i++)
    {
        p2X=p2X;
        p2Y=p2Y;
        tailX[i]=tailX[i];
        tailY[i]=tailY[i];
        pX=pX;
        pY=pY;
    }
}

//fumgsi untuk pause
void stop_main()
{
    masukan:
         system ("cls");
 cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
    	cout<<"                                                                                                                     "<<endl;
		cout<<"                                                                         ---- Pause Snake game ----          "<<endl<<endl;
        cout<<"                                                                         Username      : "<<nm[z].name<<"                  "<<endl;
		cout<<"                                                                         Score         : "<<nm[z].score<<"                  "<<endl;
		cout<<endl;
		cout<<"                                                    ================================================================== "<<endl;
		cout<<"                                                    |                                                                | "<<endl;
		cout<<"                                                    |     				        Resume Game ==> 1    |                    "<<endl;
		cout<<"                                                    |                                                                | "<<endl;
		cout<<"                                                    |                                                  Quit ==> 2    | "<<endl;
		cout<<"                                                    |                                                                | "<<endl;
		cout<<"                                                    ================================================================== "<<endl;
		cout<<"                                                                             Masukkan opsi (1/2) : ";
		while (!(cin >> again) ||again < 1 || again >2||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout<<endl<<endl<<"                                                              MAAF, INPUTAN ANDA SALAH, SILAHKAN COBA LAGI   "<<endl;
        cout<<"                                                              	  ----------------------------------        "<<endl;
        cout<<"                                                                          KLIK APA SAJA UNTUK COBA LAGI      "<<endl;
        getch ();
        goto masukan;
    }
        if (again==1)
            stop();
        else if (again==2)
        {
            loading_exit();
            system("cls");
            logo_bergerak();
            tutup();
        }



       }

// fungsi untuk menerima input dari player
void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'w':
        {
        if(nTail>0){
            if(dir==bawah){
    		gameover=true;
    		//menjeda musik latar belakang
    		stopBackgroundSound();
    		//memutar efek suara nabrak
    		PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
			}
            else dir=atas;
        }
        else dir=atas;
        break;
        }
        case 'a':
        {
            if(nTail>0){
            if(dir==kanan){
    		gameover=true;
    		//menjeda musik latar belakang
    		stopBackgroundSound();
    		//memutar efek suara nabrak
    		PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
			}
            else dir=kiri;
        }
            else dir=kiri;
            break;
        }
        case 's':
        {
            if(nTail>0){
            if(dir==atas){
    		gameover=true;
    		//menjeda musik latar belakang
    		stopBackgroundSound();
    		//memutar efek suara nabrak
    		PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
			}
            else dir=bawah;
        }
            else dir=bawah;
            break;
        }
        case 'd':
        {
            if(nTail>0){
            if(dir==kiri){
    		gameover=true;
    		//menjeda musik latar belakang
   			stopBackgroundSound();
    		//memutar efek suara nabrak
    		PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
	}
            else dir=kanan;
        }
            else dir=kanan;
            break;
        }
        case 'x':
        {
            gameover=true;
            break;
        }
        case 'p':
        {
            dir=STOP;
            stop_main();
            break;
        }
        case 72:
        {
            if(nTail>0){
            if(dir==bawah){
    		gameover=true;
    		//menjeda musik latar belakang
    		stopBackgroundSound();
    		//memutar efek suara nabrak
    		PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
			}
            else dir=atas;
        }
        else dir=atas;
        break;
        }
        case 75:
        {
            if(nTail>0){
            if(dir==kanan){
    		gameover=true;
    		//menjeda musik latar belakang
    		stopBackgroundSound();
    		//memutar efek suara nabrak
    		PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
			}
            else dir=kiri;
        }
            else dir=kiri;
            break;
        }
        case 80:
        {
            if(nTail>0){
            if(dir==atas){
    		gameover=true;
    		//menjeda musik latar belakang
    		stopBackgroundSound();
    		//memutar efek suara nabrak
    		PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
			}
            else dir=bawah;
        }
            else dir=bawah;
            break;
        }
        case 77:
        {
            if(nTail>0){
            if(dir==kiri){
    		gameover=true;
    		//menjeda musik latar belakang
    		stopBackgroundSound();
    		//memutar efek suara nabrak
    		PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
			}
            else dir=kanan;
        }
            else dir=kanan;
            break;
        }
        }
    }
}

//menangkap makanan dan menambah score
//arena persegi
void makan(int levelpermainan){
if(x==bX&&y==bY)
{
	PlaySound(TEXT("inspectorj__chewing-carrot-a.wav"), NULL, SND_FILENAME |SND_SYNC);
    if(levelpermainan == 1)
    nm[z].score+=5;
    else if(levelpermainan == 2)
    nm[z].score+=10;
    else if(levelpermainan == 3)
    nm[z].score+=15;
    bX=rand()%lebar;
    bY=rand()%tinggi;
    nTail++;
    laju-=2;
    PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
    }
}

//arena segitiga
void makan2(int levelpermainan){
if(x==bX&&y==bY)
{
	PlaySound(TEXT("inspectorj__chewing-carrot-a.wav"), NULL, SND_FILENAME |SND_SYNC);
    if(levelpermainan == 1)
    nm[z].score+=5;
    else if(levelpermainan == 2)
    nm[z].score+=10;
    else if(levelpermainan == 3)
    nm[z].score+=15;
    bY=tinggi-10;
    bX=rand()%(tinggi-6)+12;
    nTail++;
    laju-=2;
    PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
    }

}

//arena jajar genjang
void makan3(int levelpermainan) {
if (x == bX && y == bY) {
	PlaySound(TEXT("inspectorj__chewing-carrot-a.wav"), NULL, SND_FILENAME |SND_SYNC);
    if(levelpermainan == 1)
    nm[z].score+=5;
    else if(levelpermainan == 2)
    nm[z].score+=10;
    else if(levelpermainan == 3)
    nm[z].score+=15;
    bX = rand() % (lebar - 2) + 1;
    bY = rand() % (tinggi - 2) + 1;
    nTail++;
    laju-=2;
    PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
}
}

// fungsi untuk mengupdate posisi ular
void logic(int tembus,int pil,int levelpermainan)
{

    if(dir!=STOP){
    int pX=tailX[0];
    int pY=tailY[0];
    int p2X,p2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<nTail;i++)
    {
        p2X=tailX[i];
        p2Y=tailY[i];
        tailX[i]=pX;
        tailY[i]=pY;
        pX=p2X;
        pY=p2Y;
    }}

    //arena persegi atau segitiga
    if(pil==1||pil==2){
    switch (dir)
    {
        case atas:
        y--;
        break;
        case kiri:
        x--;
        break;
        case bawah:
        y++;
        break;
        case kanan:
        x++;
        break;
        default:
        break;
    }
    }

    //arena jajargenjang
    else if(pil==3){
        switch (dir)
    {
        case atas:
        {
        y--;
        x++;
        }
        break;
        case kiri:
        x--;
        break;
        case bawah:
        {
        y++;
        x--;
        }
        break;
        case kanan:
        x++;
        break;
        default:
        break;
    }
    }

    //mengecek apakah ular menabrak tembok atau ekornya sendiri
    //arena persegi
    if(pil==1){
    //mengecek apakah ular menabrak tembok
    if(tembus==1){
    if(x<0||x>=lebar||y<0||y>=tinggi){
    	gameover=true;
    //menjeda musik latar belakang
    stopBackgroundSound();
    //memutar efek suara nabrak
    PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
	}
}
    //ular menembus tembok
    if(tembus==2){
    if(x>=lebar) x=0;
    else if (x<0) x=lebar-1;
    if(y>=tinggi) y=0;
    else if (y<0) y=tinggi-1;
    }
    }

    //arena segitiga
    if(pil==2){
    //mengecek apakah ular menabrak tembok
    if(tembus==1){
    if(x<0||y<=0||y>tinggi-2||(x<(30-y)||x>(28+y))){
    	gameover=true;
    //menjeda musik latar belakang
    stopBackgroundSound();
    //memutar efek suara nabrak
    PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
	}
    }
    //ular menembus tembok
    if(tembus==2){
    if(dir==kiri||dir==kanan){
    if(x>(28+y)) x=30-y;
    else if (x<(30-y)) x=28+y;
    }
    if(dir==atas||dir==bawah){
    if(y>=tinggi-1)
    y=(abs((tinggi-1)-x))+1;
    else if (y<(abs((tinggi-1)-x))+1) y=tinggi-2;
    }
    }
    }

    //arena jajargenjang
    if(pil==3){
    //mengecek apakah ular menabrak tembok
    if(tembus==1){
    if (x == 0 || x == lebar - 1 || y == 0 || y == tinggi - 1){
    	gameover=true;
    //menjeda musik latar belakang
    stopBackgroundSound();
    //memutar efek suara nabrak
    PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
	}
        }
    //ular menembus tembok
    if (tembus == 2) {
    if(dir==kiri||dir==kanan){
    if (x >= lebar)
        x = 0;
    else if (x < 0)
        x = lebar - 1;
    }
    if(dir==atas||dir==bawah){
    if (x == lebar-1){
        x=x-tinggi+y+2;
        y = tinggi-2;
        }
    else if (x==0){
        x+=y-1;
        y = 1;
        }
    if (y>=tinggi-1){
        if(x>68){
        y=x-68;
        x=97;
    }
    else
    {
        y = 1;
        x+=tinggi;
    }
    }
    else if (y <= 0){
    if(x<30){
        y=x-1;
        x=1;
    }
    else{
    y=tinggi-2;
    x-=tinggi;
    }
    }
    }
    }
    }

    for(int i=1;i<nTail;i++)
    {
    if(tailX[i]==x && tailY[i]==y){
	//menjeda musik latar belakang
    stopBackgroundSound();
    //memutar efek suara nabrak
    PlaySound(TEXT("Sounds-wall.wav"), NULL, SND_FILENAME |SND_SYNC);
    gameover=true;
	}
    }
    if(pil==1)
    makan(levelpermainan);
    else if(pil==2)
    makan2(levelpermainan);
    else if(pil==3)
    makan3(levelpermainan);
}

//setup arena persegi
void setup(){
gameover=false;
dir=STOP; //ular dalam posisi diam
x=lebar/2; //koordinat x kepala ular
y=tinggi/2; //koordinat y kepala ular
bX=rand()%lebar; //koordinat x buah
bY=rand()%tinggi; //koordinat x buah
score=0;
    int pX=tailX[0];
    int pY=tailY[0];
    int p2X,p2Y;
nTail=0;
}

//setup arena segitiga
void setup2(){
gameover=false;
dir=STOP;
x=tinggi-1;
y=tinggi/2;
bY=tinggi-10;
bX=rand()%(tinggi-6)+9;
score=0;
    int pX=tailX[0];
    int pY=tailY[0];
    int p2X,p2Y;
nTail=0;
}

//setup arena jajargenjang
void setup3() {
gameover = false;
dir = STOP;
x=lebar/2; //koordinat x kepala ular
y=tinggi/2; //koordinat y kepala ular
bX = rand() % (lebar - 2) + 1;
bY = rand() % (tinggi - 2) + 1;
score=0;
    int pX=tailX[0];
    int pY=tailY[0];
    int p2X,p2Y;
nTail=0;
}

//prosedur untuk menghilangkan kursor
void CursorDestroyer()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

//prosedur untuk menghilangkan scrollbar
void ScrollbarDestroyer()
{
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);
	COORD new_screen_buffer_size;
	new_screen_buffer_size.X = screenBufferInfo.srWindow.Right -
		screenBufferInfo.srWindow.Left + 1;
	new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom -
		screenBufferInfo.srWindow.Top + 1;
	SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);
}

int main() {
    CursorDestroyer(); //memanggil prosedur penghilang kursor
    ScrollbarDestroyer(); //memanggil prosedur penghilang scrollbar
    PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);//memutar lagu saat awal program
    int mati, again, over,pil;
    int benUlar; //variabel penyimpan pilhan bentuk ular
    int benMakan; //variabel penyimpan pilhan makanan ular
    int warnaular; //variabel penyimpan pilihan warna ular
    int warnabg; //variabel penyimpan pilihan warna background

    // Start playing music in the background
    loading(); //memanggil prosedur loading
    logo_bergerak(); //memanggil prosedur animasi ular
    logo_game(); //memanggil prosedur logo game snake
    ignoreInput(); //mengabaikan input

    main:
    select_option(); //memanggil prosedur pilihan opsi

    nama:
    user(); //memanggil prosedur input username

    if (nm[z].name[0]=='0')
    {
        z-=1;
         goto main;
    }
    system("cls");

//memilih bentuk ular

bentukular:
system("cls"); //membersihkan layar
system("color 1E"); //mengubah warna background dan font
cout<<endl;
cout<<"\t\t\t\t\t\t  _________   __     __   ________   _________   _________   "<<endl;
cout<<"\t\t\t\t\t\t |         | |  |   |  | |   __   | |   ____  | |         |  "<<endl;
cout<<"\t\t\t\t\t\t |   ------  |  |   |  | |  |  |  | |  |    | | |  _______|  "<<endl;
cout<<"\t\t\t\t\t\t |  |        |  |   |  | |  |  |  | |  |____| | |  |______    "<<endl;
cout<<"\t\t\t\t\t\t |   ------  |  |___|  | |  |_ |  | |   ____| | |        |   "<<endl;
cout<<"\t\t\t\t\t\t |______   | |   ___   | |   __   | |  |        |   _____|   "<<endl;
cout<<"\t\t\t\t\t\t        |  | |  |   |  | |  |  |  | |  |        |  |______   "<<endl;
cout<<"\t\t\t\t\t\t  ------   | |  |   |  | |  |  |  | |  |        |         |  "<<endl;
cout<<"\t\t\t\t\t\t |_________| |__|   |__| |__|  |__| |__|        |_________|  "<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t         >>>>>>>>>> PILIHAN BENTUK ULAR <<<<<<<<<<     "<<endl;
cout<<endl;
cout<<"\t\t\t\t\t                              ---------------            "<<endl;
cout<<"\t\t\t\t\t                             *       1.      *          "<<endl;
cout<<"\t\t\t\t\t                             *               *          "<<endl;
cout<<"\t\t\t\t\t                             *     *****     *          "<<endl;
cout<<"\t\t\t\t\t                              ---------------             ";
cout<<endl;
cout<<"\t\t\t\t\t                    ---------------      ---------------        "<<endl;
cout<<"\t\t\t\t\t                   *       2.      *    *       3.      *       "<<endl;
cout<<"\t\t\t\t\t                   *               *    *               *       "<<endl;
cout<<"\t\t\t\t\t                   *     00000     *    *     ~~~~~     *       "<<endl;
cout<<"\t\t\t\t\t                    ---------------      ---------------        ";
cout<<endl;
cout<<"\t\t\t\t\t          ---------------      ---------------      ---------------        "<<endl;
cout<<"\t\t\t\t\t         *       4.      *    *       5.      *    *       6.      *       "<<endl;
cout<<"\t\t\t\t\t         *               *    *               *    *               *       "<<endl;
cout<<"\t\t\t\t\t         *     #####     *    *     @@@@@     *    *     ZZZZZ     *       "<<endl;
cout<<"\t\t\t\t\t          ---------------      ---------------      ---------------        ";
cout<<endl;
cout<<"\t\t\t\t\t   ---------------    ---------------    ---------------    ---------------      "<<endl;
cout<<"\t\t\t\t\t  *       7.      *  *       8.      *  *       9.      *  *       10.     *     "<<endl;
cout<<"\t\t\t\t\t  *               *  *               *  *               *  *               *     "<<endl;
cout<<"\t\t\t\t\t  *     AAAAA     *  *     %%%%%     *  *     <<<<<     *  *     XXXXX     *     "<<endl;
cout<<"\t\t\t\t\t   ---------------    ---------------    ---------------    ---------------      ";
cout<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t               Ketik 0 untuk kembali ke username "<<endl;
cout<<"\t\t\t\t\t\t            Ketik 11 jika ingin kembali ke MENU!!! "<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t                     PILIH BENTUK ULAR: ";

while (!(cin >> benUlar) || benUlar < 0 || benUlar > 11||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout <<endl<< "\t\t\t\t\t\t                     Input tidak valid !!! ";
        cout <<endl<< "\t\t\t\t\t\t         Ketik apa saja untuk menginputkan ulang (0-11)";
        getch ();
        goto bentukular;

    }

    if (benUlar== 0) {
    z-=1;
     goto nama;
}
    if (benUlar==11){
    system("cls");
    z-=1;
    goto main; //memilih opsi
        }

// memilih warna ular
    warnaular:
    system ("cls");
    system("color E5");

    cout<<endl;
    cout<<"\t\t\t\t\t                                                                               "<<endl;
    cout << "\t\t\t\t\t  /\\                /\\    ------    /-------\\  |||      ||    ------" << endl;
    cout << "\t\t\t\t\t  ||                ||  / ------ \\  ||     ||  ||||     ||  / ------ \\" << endl;
    cout << "\t\t\t\t\t  ||                ||  ||      ||  ||     ||  || ||    ||  ||      ||" << endl;
    cout << "\t\t\t\t\t  ||                ||  ||      ||  ||     ||  ||  ||   ||  ||      ||" << endl;
    cout << "\t\t\t\t\t  ||       /\\       ||  ||      ||  ||------/  ||   ||  ||  ||      ||" << endl;
    cout << "\t\t\t\t\t   ||      ||      ||   |--------|  ||\\\\       ||    || ||  |--------|" << endl;
    cout << "\t\t\t\t\t    ||   ||  ||   ||    ||      ||  ||  \\\\     ||     ||||  ||      ||" << endl;
    cout << "\t\t\t\t\t     || ||    || ||     ||      ||  ||    \\\\   ||      |||  ||      ||" << endl;
    cout << "\t\t\t\t\t       ||      ||       ||      ||  ||     \\\\  ||       ||  ||      ||" <<endl;
    cout<<"\t\t\t\t\t                                                                               "<<endl;
    cout<<"\t\t\t\t\t *********************************************************************"<<endl;
    cout<<"\t\t\t\t\t *********************************************************************"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t                       ^-^ PILIH WARNA ULAR!!! ^-^                    "<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t          _________             _________            _________     "<<endl;
    cout<<"\t\t\t\t\t         |         |           |         |          |         |       "<<endl;
    cout<<"\t\t\t\t\t         |    1.   |           |    2.   |          |    3.   |       "<<endl;
    cout<<"\t\t\t\t\t         |         |           |         |          |         |       "<<endl;
    cout<<"\t\t\t\t\t         |  Putih  |           |  Merah  |          |  Ungu   |       "<<endl;
    cout<<"\t\t\t\t\t         |         |           |         |          |  Muda   |       "<<endl;
    cout<<"\t\t\t\t\t         |_________|           |_________|          |_________|       "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t          _________             _________            _________     "<<endl;
    cout<<"\t\t\t\t\t         |         |           |         |          |         |       "<<endl;
    cout<<"\t\t\t\t\t         |    4.   |           |    5.   |          |    6.   |       "<<endl;
    cout<<"\t\t\t\t\t         |         |           |         |          |         |       "<<endl;
    cout<<"\t\t\t\t\t         |  Hijau  |           | Kuning  |          |  Merah  |       "<<endl;
    cout<<"\t\t\t\t\t         |  Muda   |           |         |          |  Muda   |       "<<endl;
    cout<<"\t\t\t\t\t         |_________|           |_________|          |_________|       "<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t             Ketik 0 untuk kembali ke pemilihan bentuk ular "<<endl;
    cout<<"\t\t\t\t\t                 Ketik 7 jika ingin kembali ke MENU!!!         "<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t                      ^-^ Pilihan warna ular : ";

    while (!(cin >> warnaular) || warnaular < 0 || warnaular >7||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout <<endl<< "\t\t\t\t\t                          Input tidak valid !!!";
        cout <<endl<< "\t\t\t\t\t                Ketik apa saja untuk menginputkan ulang (0-7)";
         getch ();
        goto warnaular;
    }

    if(warnaular==0)
        goto bentukular; //memilih bentuk ular
    if (warnaular==7){
        system("cls");
        z-=1;
        goto main; //memilih opsi
        }
    cout<<"\t\t\t                                                                                                    "<<endl;
    cout<<"\t\t\t                                                                                                    "<<endl;
    cout<<"\t\t\t                                                                                                    "<<endl;

//jenis makanan ULAR

makananular:
system ("cls");
system ("color 4E");
cout<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t        =======   =======     =======     =======             "<<endl;
cout<<"\t\t\t\t\t\t       |         |       |   |       |   |       |            "<<endl;
cout<<"\t\t\t\t\t\t       |         |       |   |       |   |        |           "<<endl;
cout<<"\t\t\t\t\t\t       |=======  |       |   |       |   |         |          "<<endl;
cout<<"\t\t\t\t\t\t       |         |       |   |       |   |        |           "<<endl;
cout<<"\t\t\t\t\t\t       |         |       |   |       |   |       |            "<<endl;
cout<<"\t\t\t\t\t\t       |          =======     =======     =======             "<<endl;
cout<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t       <<<<<<<<<<<  JENIS MAKANAN ULAR  >>>>>>>>>>>        "<<endl;
cout<<endl;
cout<<endl;
cout<<"\t\t\t\t\t          =============        =============        =============         "<<endl;
cout<<"\t\t\t\t\t         *      1.     *      *      2.     *      *      3.     *       "<<endl;
cout<<"\t\t\t\t\t         *             *      *             *      *             *       "<<endl;
cout<<"\t\t\t\t\t         *      a      *      *      b      *      *      d      *       "<<endl;
cout<<"\t\t\t\t\t          =============        =============        =============        "<<endl;
cout<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t           =============           =============         "<<endl;
cout<<"\t\t\t\t\t\t          *      4.     *         *      5.     *       "<<endl;
cout<<"\t\t\t\t\t\t          *             *         *             *       "<<endl;
cout<<"\t\t\t\t\t\t          *      e      *         *      n      *       "<<endl;
cout<<"\t\t\t\t\t\t           =============           =============         "<<endl;
cout<<endl;
cout<<endl;
cout<<"\t\t\t\t\t          =============        =============        =============   "<<endl;
cout<<"\t\t\t\t\t         *      6.     *      *      7.     *      *      8.     *   "<<endl;
cout<<"\t\t\t\t\t         *             *      *             *      *             *   "<<endl;
cout<<"\t\t\t\t\t         *      r      *      *      q      *      *      t      *   "<<endl;
cout<<"\t\t\t\t\t          =============        =============        =============  "<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t        Ketik 0 untuk kembali ke pemilihan warna ular "<<endl;
cout<<"\t\t\t\t\t\t            Ketik 9 jika ingin kembali ke MENU!!!         "<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t                PILIH JENIS MAKANAN ULAR: ";

while (!(cin >> benMakan) ||benMakan < 0 || benMakan >9||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout <<endl<< "\t\t\t\t\t\t                    Input tidak valid !!! ";
        cout <<endl<< "\t\t\t\t\t\t         Ketik apa saja untuk menginputkan ulang (0-9)";
        getch();
        goto makananular;
    }

if(benMakan==0)
    goto warnaular; //memilih warna ular
if (benMakan==9){
    system("cls");
    z-=1;
    goto main; //memilih opsi
        }
system("cls"); //membersihkan layar

// Memilih warna background
    background:
    system("cls");
    system("color DF");
    cout<<endl;
    cout << "\t\t\t\t\t  /\\                /\\    ------    /-------\\  |||      ||    ------" << endl;
    cout << "\t\t\t\t\t  ||                ||  / ------ \\  ||     ||  ||||     ||  / ------ \\" << endl;
    cout << "\t\t\t\t\t  ||                ||  ||      ||  ||     ||  ||  ||   ||  ||      ||" << endl;
    cout << "\t\t\t\t\t  ||       /\\       ||  ||      ||  ||------/  ||   ||  ||  ||      ||" << endl;
    cout << "\t\t\t\t\t   ||      ||      ||   |--------|  ||\\\\       ||    || ||  |--------|" << endl;
    cout << "\t\t\t\t\t    ||   ||  ||   ||    ||      ||  ||  \\\\     ||     ||||  ||      ||" << endl;
    cout << "\t\t\t\t\t     || ||    || ||     ||      ||  ||    \\\\   ||      |||  ||      ||" << endl;
    cout << "\t\t\t\t\t       ||      ||       ||      ||  ||     \\\\  ||       ||  ||      ||" <<endl;
    cout<<endl;
    cout << "\t\t\t\t                                     PILIHAN WARNA BACKGROUND "<<endl;
    cout<<endl;
    cout << "\t\t\t\t              **************          **************          **************          "<<endl;
    cout << "\t\t\t\t             |      1.      |        |      2.      |        |      3.      |            "<<endl;
    cout << "\t\t\t\t             |    HITAM     |        |     BIRU     |        |    HIJAU     |            "<<endl;
    cout << "\t\t\t\t             |              |        |              |        |              |             "<<endl;
    cout << "\t\t\t\t              **************          **************          **************             "<<endl;
    cout<<endl;
    cout << "\t\t\t\t              **************                                  **************          "<<endl;
    cout << "\t\t\t\t             |      4.      |                                |      5.      |            "<<endl;
    cout << "\t\t\t\t             |     AQUA     |                                |     UNGU     |            "<<endl;
    cout << "\t\t\t\t             |              |                                |              | "<<endl;
    cout << "\t\t\t\t              **************                                  **************             ";
    cout<<endl;
    cout << "\t\t\t\t              **************                                  **************          "<<endl;
    cout << "\t\t\t\t             |      6.      |                                |      7.      |"<<endl;
    cout << "\t\t\t\t             |     GRAY     |                                |     BIRU     |"<<endl;
    cout << "\t\t\t\t             |              |                                |     MUDA     |"<<endl;
    cout << "\t\t\t\t              **************                                  ************** "<<endl;
    cout<<endl;
    cout << "\t\t\t\t              **************          **************          ************** "<<endl;
    cout << "\t\t\t\t             |      8.      |        |      9.      |        |      10.     |"<<endl;
    cout << "\t\t\t\t             |    KUNING    |        |    LIGHT     |        |     LIGHT    |"<<endl;
    cout << "\t\t\t\t             |     MUDA     |        |    WHITE     |        |     AQUA     |"<<endl;
    cout << "\t\t\t\t              **************          **************          ************** "<<endl;
    cout<<"\t\t\t                                                                                                    "<<endl;
    cout<<"\t\t\t\t\t\t     Ketik 0 untuk kembali ke pemilihan jenis makanan ular "<<endl;
    cout<<"\t\t\t\t\t\t             Ketik 11 untuk kembali ke MENU!!! "<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t\t           Masukkan Pilihan Warna Background : ";

    while (!(cin >> warnabg) ||warnabg < 0 || warnabg >11||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout <<endl<< "\t\t\t\t\t                          Input tidak valid !!! ";
        cout <<endl<< "\t\t\t\t\t                Ketik apa saja untuk menginputkan ulang (0-11)";
        getch();
        goto background; //memilih background
    }

    if(warnabg==0)
        goto makananular;
    if (warnabg==11){
    system("cls");
    z-=1;
    goto main;
        }
    cout<<"\t\t\t                                                                                                    "<<endl;
    cout<<"\t\t\t                                                                                                    "<<endl;
    cout<<"\t\t\t                                                                                                 "<<endl;

//level ular
    level:
    system("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "\t\t\t\t       _____            _________     __         __     _________     ____       " << endl;
    cout << "\t\t\t\t       |   |           |  ______|    |  |       |  |    |  _____|     |   |      " << endl;
    cout << "\t\t\t\t       |   |           |  |_____      |  |     |  |     |  |____      |   |      " << endl;
    cout << "\t\t\t\t       |   |           |   _____|      |  |   |  |      |  _____|     |   |      " << endl;
    cout << "\t\t\t\t       |   |______     |  |_____        |  |_|  |       |  |____      |   |______ " << endl;
    cout << "\t\t\t\t       |__________|    |________|        |_____|        |_______|     |__________|" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "\t\t\t\t                          _____________________________________" << endl;
    cout << "\t\t\t\t                          |                                   |" << endl;
    cout << "\t\t\t\t                          |                                   |" << endl;
    cout << "\t\t\t\t                          |         Choose Difficult          |" << endl;
    cout << "\t\t\t\t                          |                                   |" << endl;
    cout << "\t\t\t\t                          |             1. Easy               |" << endl;
    cout << "\t\t\t\t                          |         (Kecepatan Normal)        |" << endl;
    cout << "\t\t\t\t                          |             2. Medium             |" << endl;
    cout << "\t\t\t\t                          |      (Kecepatan Lumayan Cepat)    |" << endl;
    cout << "\t\t\t\t                          |             3. Hard               |" << endl;
    cout << "\t\t\t\t                          |         (Kecepatan Cepat)         |" << endl;
    cout << "\t\t\t\t                          |                                   |" << endl;
    cout << "\t\t\t\t                          |                                   |" << endl;
    cout << "\t\t\t\t                          |___________________________________|" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout<<"\t\t\t\t\t            Ketik 0 untuk kembali ke pemilihan warna background"<<endl;
    cout<<"\t\t\t\t\t                     Ketik 4 untuk kembali ke MENU!!!"<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t                        Masukkan Pilihan Level:";

    while (!(cin >> levelpermainan) ||levelpermainan < 0 || levelpermainan >4||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout << endl<< "\t\t\t\t\t                          Input tidak valid !!! ";
        cout <<endl<<  "\t\t\t\t\t                Ketik apa saja untuk menginputkan ulang (0-4)";
        getch();
        goto level; //memilih level
    }

    if (levelpermainan==4){
    system("cls");
    z-=1;
    goto main;
        }
    if(levelpermainan == 1)
        laju = 80;
    else if(levelpermainan == 2)
        laju = 50;
    else if(levelpermainan == 3)
        laju = 30;
    else if(levelpermainan == 0) goto background; //memiliih warna background
    cout << endl;
    cout << endl;
    cout << " \t\t\t\t\t\t       Klik Enter Untuk Melanjutkan ";
    system("cls");

//Jenis papan permainan

    papanpermainan:
        system ("cls");
        system ("color E4");
    cout<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t\t       #####    ######        #       #####    ######   " <<endl;
    cout<<"\t\t\t\t\t\t       #    #  #      #      # #      #    #   #     #  " <<endl;
    cout<<"\t\t\t\t\t\t       #    #  #      #     #   #     #    #   #     #  " <<endl;
    cout<<"\t\t\t\t\t\t       ######  #      #    #######    #####    #     #  " <<endl;
    cout<<"\t\t\t\t\t\t       #    #  #      #   #       #   #   #    #     #  " <<endl;
    cout<<"\t\t\t\t\t\t       #    #  #      #  #         #  #    #   #     #  " <<endl;
    cout<<"\t\t\t\t\t\t       #####    ######  #           # #     #  ######   " <<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t\t       ######  #      #        #       #####   ######   " <<endl;
    cout<<"\t\t\t\t\t\t       #       #      #       # #      #    #  #        " <<endl;
    cout<<"\t\t\t\t\t\t       #       #      #      #   #     #    #  #        " <<endl;
    cout<<"\t\t\t\t\t\t       ######  ########     #######    #####   ######   " <<endl;
    cout<<"\t\t\t\t\t\t            #  #      #    #       #   #       #        " <<endl;
    cout<<"\t\t\t\t\t\t            #  #      #   #         #  #       #        " <<endl;
    cout<<"\t\t\t\t\t\t       ######  #      #  #           # #       ######   " <<endl;
    cout<<endl;
    cout<<endl;

    cout<<"\t\t\t\t\t\t  ~~~~~~~~~~~~~~~~~~ jenis papan bermain ~~~~~~~~~~~~~~~~~~~" <<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t\t\t           ||-------------------||                          " <<endl;
    cout<<"\t\t\t\t\t\t\t           ||   1. PERSEGI      ||                          " <<endl;
    cout<<"\t\t\t\t\t\t\t           ||-------------------||                          " <<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t\t\t           ||-------------------||                          " <<endl;
    cout<<"\t\t\t\t\t\t\t           ||   2. SEGITIGA     ||                          " <<endl;
    cout<<"\t\t\t\t\t\t\t           ||-------------------||                          " <<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t\t\t           ||-------------------||                          " <<endl;
    cout<<"\t\t\t\t\t\t\t           ||  3. JAJAR GENJANG ||                          " <<endl;
    cout<<"\t\t\t\t\t\t\t           ||-------------------||                          " <<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t                 Ketik 0 untuk kembali ke pemilihan level "<<endl;
    cout<<"\t\t\t\t\t                     Ketik 4 untuk kembali ke MENU!!!"<<endl<<endl;
    cout<<"\t\t\t\t\t                        Pilih jenis papan bermain : ";

    while (!(cin >> pil) ||pil < 0 || pil >4||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout << endl<<"\t\t\t\t\t                             Input tidak valid!!! ";
        cout <<endl<< "\t\t\t\t\t                  Ketik apa saja untuk menginputkan ulang (0-4)";
        getch();
        goto papanpermainan;
    }

    if(pil==0) goto level;
    if (pil==4){
    system("cls");
    z-=1;
    goto main; //memilih pilihan opsi
        }

//opsi ppermainan
    opsipermainan:
    int tembus;
    system ("cls");
    system ("color E4");
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t\t       -----------------------------------------------       "<<endl;
    cout<<"\t\t\t\t\t\t       |                                             |       "<<endl;
    cout<<"\t\t\t\t\t\t       |        PILIH OPSI PERMAINAN !!! ^-^         |       "<<endl;
    cout<<"\t\t\t\t\t\t       |                                             |       "<<endl;
    cout<<"\t\t\t\t\t\t       |     1. Syarat Mati = Tabrak badan ular      |       "<<endl;
    cout<<"\t\t\t\t\t\t       |        dan Tabrak Dinding Permainan         |       "<<endl;
    cout<<"\t\t\t\t\t\t       |     2. Syarat Mati = Tabrak badan ular saja |       "<<endl;
    cout<<"\t\t\t\t\t\t       |                                             |       "<<endl;
    cout<<"\t\t\t\t\t\t       -----------------------------------------------       "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t            Ketik 0 untuk kembali ke pemilihan jenis papan bermain"<<endl;
    cout<<"\t\t\t\t\t                       Ketik 3 untuk kembali ke MENU!!!"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t\t\t                                       Masukkan Pilihan Anda (1/2) : ";

    while (!(cin >> tembus) ||tembus < 0 || tembus >3||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout <<endl<< "\t\t\t                                            Input tidak valid!! ";
        cout <<endl<< "\t\t\t                                 Ketik apa saja untuk menginputkan ulang (0-3)";
        getch();
        goto opsipermainan;
    }

    if(tembus==0) goto papanpermainan; //memilih jenis bentuk arena
    if (tembus==3){
    system("cls");
    z-=1;
    goto main; //memilih pilihan opsi
        }

    // tampilan peraturan permainan
    tampilan:
    system("cls");
    system("color DF");
    cout<<endl;
    cout<<endl;
    cout<<"\t\t\t\t\t    ================================================================== "<<endl;
    cout<<"\t\t\t\t\t    ================================================================== "<<endl;
    cout<<"\t\t\t\t\t    ================================================================== "<<endl;
    cout<<"\t\t\t\t\t    ==============                                      ============== "<<endl;
    cout<<"\t\t\t\t\t    =============                                        ============= "<<endl;
    cout<<"\t\t\t\t\t    ============   ***** PETUNJUK PERMAINAN SNAKE *****   ============ "<<endl;
    cout<<"\t\t\t\t\t    ===========                                            =========== "<<endl;
    cout<<"\t\t\t\t\t    ==========     1. Tekan Tombol 'W' atau 'Panah Atas'    ========== "<<endl;
    cout<<"\t\t\t\t\t    =========         untuk Ular Begerak ke Atas             ========= "<<endl;
    cout<<"\t\t\t\t\t    ========                                                  ======== "<<endl;
    cout<<"\t\t\t\t\t    =======        2. Tekan Tombol 'S' atau 'Panah Bawah'      ======= "<<endl;
    cout<<"\t\t\t\t\t    ======            untuk Ular Begerak ke Bawah               ====== "<<endl;
    cout<<"\t\t\t\t\t    =====                                                        ===== "<<endl;
    cout<<"\t\t\t\t\t    ====           3. Tekan Tombol 'A' atau 'Panah Kiri'          ==== "<<endl;
    cout<<"\t\t\t\t\t    ===               untuk Ular Begerak ke Kiri                   === "<<endl;
    cout<<"\t\t\t\t\t    ====                                                          ==== "<<endl;
    cout<<"\t\t\t\t\t    =====          4. Tekan Tombol 'D' atau 'Panah Kanan'        ===== "<<endl;
    cout<<"\t\t\t\t\t    ======            untuk Ular Begerak ke Kanan               ====== "<<endl;
    cout<<"\t\t\t\t\t    =======                                                    ======= "<<endl;
    cout<<"\t\t\t\t\t    ========       5. Tekan Tombol 'P' untuk pause            ======== "<<endl;
    cout<<"\t\t\t\t\t    =========         permainan ular saat dimainkan          ========= "<<endl;
    cout<<"\t\t\t\t\t    ==========                                              ========== "<<endl;
    cout<<"\t\t\t\t\t    ===========    6. Tekan Tombol 'X' untuk keluar        =========== "<<endl;
    cout<<"\t\t\t\t\t    ============      dari permainan ular                 ============ "<<endl;
    cout<<"\t\t\t\t\t    =============                                        ============= "<<endl;
    cout<<"\t\t\t\t\t    ==============                                      ============== "<<endl;
    cout<<"\t\t\t\t\t    ================================================================== "<<endl;
    cout<<"\t\t\t\t\t    ================================================================== "<<endl;
    cout<<"\t\t\t\t\t    ================================================================== "<<endl;
    cout<<endl;
    cout<<endl;
    int balik;
    cout<<"\t\t\t\t\t\t\t    Ketik 0 untuk kembali ke opsi permainan" <<endl;
    cout<<"\t\t\t\t\t\t\t    >> Klik 1 Untuk Memulai Permainan Snake " <<endl;
    cout<<"\t\t\t\t\t\t\t    >> Klik 2 Untuk Kembali Ke MENU!!!" <<endl<<endl;
    cout<<"\t\t\t\t\t\t\t         Masukkan Pilihan Anda : ";
     while (!(cin >> balik) ||balik < 0 || balik >2||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout <<endl<< "\t\t\t\t\t\t                  Input tidak valid!!! ";
        cout <<endl<< "\t\t\t\t\t\t      Ketik apa saja untuk menginputkan ulang (0-2)";
        getch();
        goto tampilan;
    }
    if(balik==0) goto opsipermainan;
    if (balik==2){
    system("cls");
    z-=1;
   goto main; //memilih opsi
        }
    cout<<endl;
    cout<<endl;
    cout<<endl;


    game:
    if(pil==1)
    setup(); //memanggil prosedur setup arena persegi
    else if(pil==2)
    setup2(); //memanggil prosedur setup arena segitiga
    else if(pil==3)
    setup3(); //memanggil prosedur setup arena jajargenjang

    // panggil fungsi warna ular background
    warna_ular_background(warnaular, warnabg);
    //program selama game berlangsung
    while(!gameover){
    // panggil fungsi bentuk ular dan bentuk makanan ular dan arena permainan
    bentuk_ular_makanan(benUlar, benMakan, pil);
    input(); //membaca input pindah arah ular dari pemain
    logic(tembus,pil,levelpermainan); //memanggil prosedur logic
    Sleep(laju); //kecepatan ular
    }

    if(gameover){
    	//memutar efek suara game over
    	PlaySound (TEXT("irishcoder__game-over.wav"), NULL, SND_FILENAME | SND_ASYNC);
    sini:
        system ("cls");
    	if(nm[z].score>maks){ //untuk highscore
        maks=nm[z].score;
        cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
    	cout<<endl;
    	cout<<"                                                                                                                     "<<endl;
		cout<<"                                                                 Selamat Anda mencapai High score baru!!           "<<endl;
		cout<<"                                                                               ------------                          "<<endl;
		cout<<"                                                                         Username      : "<<nm[z].name<<"                  "<<endl;
		cout<<"                                                                         New Highscore : "<<maks<<"                  "<<endl;
		cout<<"                                                                                                                     "<<endl;
		cout<<"                                                    ================================================================== "<<endl;
		cout<<"                                                    |     			   Try Again ==> 1                   |            "<<endl;
		cout<<"                                                    |                                  Menu  ==> 2                   | "<<endl;
		cout<<"                                                    |                                History ==> 3                   | "<<endl;
		cout<<"                                                    |                                   Quit ==> 4                   | "<<endl;
		cout<<"                                                    ================================================================== "<<endl;
		cout<<"                                                                             Masukkan opsi : ";

        while (!(cin >> mati) ||mati < 1 || mati >4||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
        cout<<"                                                              MAAF, INPUTAN ANDA SALAH, SILAHKAN COBA LAGI   "<<endl;
        cout<<"                                                              	  ----------------------------------        "<<endl;
        cout<<"                                                                   KLIK APA SAJA UNTUK INPUT ULANG         "<<endl;
        getch ();
        goto sini; //mengulang input
		cout<<endl<<endl<<endl;
    	}
    	}
    	else{  //kalau pemain tidak mancapai highscore
        cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
    	cout<<endl;
    	cout<<"                                                                                                                     "<<endl;
		cout<<"                                                                             ---- Game Over ----          "<<endl;
		cout<<"                                                                                                                     "<<endl;
		cout<<"                                                                         Username      : "<<nm[z].name<<"                  "<<endl;
		cout<<"                                                                         Score         : "<<nm[z].score<<"                  "<<endl;
		cout<<"                                                                         Highscore     : "<<maks<<"                  "<<endl;
		cout<<"                                                                                                                     "<<endl;
		cout<<"                                                    ================================================================== "<<endl;
		cout<<"                                                    |     			   Try Again ==> 1                   |            "<<endl;
		cout<<"                                                    |                                  Menu  ==> 2                   | "<<endl;
		cout<<"                                                    |                                History ==> 3                   | "<<endl;
		cout<<"                                                    |                                   Quit ==> 4                   | "<<endl;
		cout<<"                                                    ================================================================== "<<endl;
		cout<<"                                                                             Masukkan opsi : ";
        while (!(cin >> mati) ||mati < 1 || mati >4||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
        cout<<"                                                              MAAF, INPUTAN ANDA SALAH, SILAHKAN COBA LAGI   "<<endl;
        cout<<"                                                              	  ----------------------------------        "<<endl;
        cout<<"                                                                    KLIK APA SAJA UNTUK INPUT ULANG         "<<endl;
        getch ();
        goto sini;
        }
		cout<<endl<<endl<<endl;
    	}
        if (mati==1) {
        	PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
            z++;
            nm[z].name = nm[z-1].name;
            goto game;
        }
        else if (mati==2)
        {
            system("cls");
            PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
            goto main; //memilih opsi menu
        }


else if (mati == 3) //history
{
	PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
    Histor:
    system("cls");
    system("color B1");
    cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
        cout<<"                                                                             HISTORI PERMAINAN                      "<<endl;
        cout<<"                                                 ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~ "<<endl;
		for (int t = 0; t <= z; t++)
        {
            cout<<"                                                   " << t + 1 << ". " <<"Username      : "<<nm[t].name<<"                   "<<endl;
            cout<<"                                                      Score         : "<<nm[t].score<<"                  "<<endl;

        }

		cout<<"                                                 ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~ "<<endl;


        cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
        cout<<"                                                 ================================================================== "<<endl;
		cout<<"                                                 |                          Try Again ==> 1                       | "<<endl;
		cout<<"                                                 |                              Menu  ==> 2                       | "<<endl;
		cout<<"                                                 |                               Quit ==> 3                       | "<<endl;
		cout<<"                                                 ================================================================== "<<endl;
		cout<<"                                                                             Masukkan opsi : ";
		while (!(cin >> History) ||History < 1 || History >3||cin.peek()!='\n') {
        cin.clear(); // mengatur kembali status input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan input stream
        cout<<endl<<endl<<endl;
    	cout<<endl<<endl<<endl;
        cout<<"                                                              MAAF, INPUTAN ANDA SALAH, SILAHKAN COBA LAGI   "<<endl;
        cout<<"                                                              	  ----------------------------------        "<<endl;
        cout<<"                                                                     KLIK APA SAJA UNTUK INPUT ULANG         "<<endl;
        getch ();
        goto Histor;
		cout<<endl<<endl<<endl;
    	}
    	if (History==1) {
    		PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
            z++;
            nm[z].name = nm[z-1].name;
            goto game;
        }
        else if (History==2)
        {
        	PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
            system("cls");
            goto main; //memilih opsi menu
        }
         else if (History==3)
        {
            loading_exit(); //memanggil prosedur loading
            system("cls"); //membersihkan layar
            logo_bergerak(); //memanggil prosedur animasi ular
            tutup(); //memanggil prosedur penutup
        }
}
        else if (mati==4)
        {
            loading_exit(); //memanggil prosedur loading
            system("cls"); //membersihkan layar
            logo_bergerak(); //memanggil prosedur animasi ular
            tutup(); //memanggil prosedur penutup
        }

    }
}
