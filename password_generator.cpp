#include<iostream>
#include<conio.h>
#include <windows.h>
#include<time.h>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<cstdlib>


#define delay Sleep
#define gotoxy gotoXY
#define clrscr() system("CLS")
#define random(x) rand()%x
#define DATE_TIME TIME_DATE



using namespace std;

struct ENCODE
{
        int pass[100];
        int site[100];
        int id;
};

struct SEQUENCE
{
        char pass[100];
        char site[100];
        int id;
        int s_l,p_l;
};

int h,w;
int T1,T2,L;
char KEY[85];


void randomize()
{

        time_t t;
        time(&t);
        srand(t);
}

void gotoXY(int X_AXIS,int Y_AXIS)
{
    COORD coordinates;

    coordinates.X=X_AXIS;
    coordinates.Y=Y_AXIS;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}


enum COLORS{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,GRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE};


/***********************************************************************************************************************************************\
                                                          CONSOLE SIZE MODULE
\***********************************************************************************************************************************************/

void GET_CONSOLE_SIZE(int & HEIGHT_H, int & WIDTH_W)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    WIDTH_W = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    HEIGHT_H = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

/***********************************************************************************************************************************************\
                                                          CONSOLE SIZE MODULE END
\***********************************************************************************************************************************************/

                                   /**------------------------------------------------------------------------------*/

/***********************************************************************************************************************************************\
                                        SYSTEM DATE AND TIME
\***********************************************************************************************************************************************/

class TIME_DATE
{


  private:
    time_t t;
    struct tm * timeinfo;
  public:
        char DATE[12];
        char TIME[10];

        TIME_DATE()
        {
            time(&t);
            timeinfo=localtime(&t);
            sprintf(DATE,"%d-%d-%d",timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900);
            sprintf(TIME,"%d:%d:%d",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
        }
};

/***********************************************************************************************************************************************\
                                                             SYSTEM DATE AND TIME END
\***********************************************************************************************************************************************/

                                   /**------------------------------------------------------------------------------*/

/***********************************************************************************************************************************************\
                                                                  SYSTEM COLORS
\***********************************************************************************************************************************************/

void SetColors(int FOREGROUND,int BACKGROUND)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(FOREGROUND+(BACKGROUND*16)));
}

void INITIALIZE()
{
    fstream file;
    file.open("KEY.DAT",ios::binary|ios::in|ios::app);
    file>>KEY;
    file.close();

}

int En_Make_Id( )
{
    fstream file,fil;
    SEQUENCE T;

    file.open("SEQUENCE.DAT",ios::binary|ios::out|ios::in);
    if(!file)
    {
        file.open("SEQUENCE.DAT",ios::binary|ios::app);
        remove("ENCODE.DAT");
        fil.open("ENCODE.DAT",ios::binary|ios::app);
        fil.close();
        file.close();
        return 1;
    }
    fstream file1;
    file1.open("SEQUENCE.DAT",ios::binary|ios::in|ios::out);
    int i1=0;
    SEQUENCE S1;
    while(file1.read((char *)&S1,sizeof(S1)))
    {
        i1++;
    }
    file1.close();

    if(i1==0)
    {
        return 1;
    }

    else
    {
        while(file.read((char *)&T,sizeof(T)));
        file.close();
        return(T.id+1);
    }

}
//7974811986
ENCODE En_Init()
{
    ENCODE T;
    int f,c,val,temp;

    randomize();

    for( f=0 ; f<sizeof(T.pass)/4 ; )
    {
        val=random(100);
        temp=1;
        for( c=0 ; c<f ; c++)
        {
            if(T.pass[c]==val)
            {
                temp=0;
            }

        }
        if(temp)
        {
            T.pass[f]=val;
            f++;
        }
    }


    for( f=0 ; f<sizeof(T.site)/4 ; )
    {
        val=random(100);
        temp=1;
        for( c=0 ; c<f ; c++)
        {
            if(T.site[c]==val)
            {
                temp=0;
            }

        }
        if(temp)
        {
            T.site[f]=val;
            f++;
        }
    }

    return T;
}

void TYPE(int &T1,int &T2)
{
    char MSG[5][25] = { "1.ONLY NUMERIC         ",
                        "2.ONLY ALPHABET        ",
                        "3.ONLY ALPHANUMERIC    ",
                        "4.RANDOM               ",
                        "CHOICE NUMBER [ ]\b\b"};


    int r;
    do
    {
        clrscr();
        for(r=0;r<5;r++)
        {
            gotoxy(w/2-12,h/2-2+r);
            cout<<MSG[r];
        }
            cin>>T1;/**to be changed*/
            clrscr();

            if(T1<=0||T1>=5)
            {
              gotoxy(w/2-15,h/2-5);
              cout<<"!!WRONG CHOICE NUMBER!!\a";
              T1=0;
              delay(2000);
            }

    }while(T1==0);

    if(T1==1||T1==2)
    {
        T2=0;
        return ;
    }

    switch(T1)
    {
        case 3:
            {
                char MSG1[3][40]={"1.ATLEAST ONE CAPITAL & SMALL LETTER",
                                  "2.RANDOM                  ",
                                  "CHOICE NUMBER [ ]\b\b"
                              };
                do
                {
                    clrscr();
                    for(r=0;r<3;r++)
                    {
                        gotoxy(w/2-15,h/2-2+r);
                        cout<<MSG1[r];
                    }
                    cin>>T2;
                    clrscr();
                    if(T2<=0||T2>2)
                    {
                        gotoxy(w/2-15,h/2-5);
                        cout<<"!!WRONG CHOICE NUMBER!!\a";
                        T2=0;
                        delay(2000);
                    }
                }while(T2==0);

            }
            break;
        case 4:
            {
                char MSG1[5][40]={"1.ATLEAST ONE CAPITAL & SMALL LETTER",
                                  "2.ATLEAST ONE NUMERIC VALUE",
                                  "3.BOTH 1 & 2",
                                  "4.RANDOM",
                                  "CHOICE NUMBER [ ]\b\b"
                              };

               do
                {
                    clrscr();
                    for(r=0;r<5;r++)
                    {
                        gotoxy(w/2-15,h/2-3+r);
                        cout<<MSG1[r];
                    }
                    cin>>T2;
                    clrscr();
                    if(T2<=0||T2>4)
                    {
                        gotoxy(w/2-15,h/2-5);
                        cout<<"!!WRONG CHOICE NUMBER!!\a";
                        T2=0;
                        delay(2000);
                    }
                }while(T2==0);

            }
            break;
    }

}
void LENGTH( )
{
    int L1;

      do
      {
          clrscr();
          gotoxy(w/2-15,h/2-5);
          cout<<"ENTER THE SIZE OF PASSWORD : ";
          cin>>L1;/**to be changed*/
          clrscr();
          if(L1<8||L1>=100)
          {
              gotoxy(w/2-15,h/2-5);
              cout<<"!!PASSWORD LENGTH INVALID!!\a";
              L1=0;
              delay(2000);
          }

      }while(L1==0);

      L=L1;
}
void LOADER()
{
    for(int i=1;i<=25;i++)
  {
      SetColors(0,GREEN);

      gotoXY(w/2-25+i,h/2-1);
      cout<<" ";
      gotoXY(w/2+26-i,h/2-1);
      cout<<" ";
      gotoXY(w/2-25+i,h/2+1);
      cout<<" ";
      gotoXY(w/2-i+26,h/2+1);
      cout<<" ";
      gotoXY(w/2+26-i,h/2);
      cout<<" ";
      gotoXY(w/2-    25+i,h/2);
      cout<<" ";
      SetColors(17,15);
      gotoXY(w/2,h/2-2);
      cout<<i*4<<"%";
      delay(random(90));
  }

  delay(300);
  SetColors(WHITE,BLACK);
  clrscr();

}
#include<string>
void EncryptFile_DAta(SEQUENCE &T,ENCODE &E)
{
    char site[100];
    char pass[100];

    strcpy(site,T.site);
    strcpy(pass,T.pass);

    int i;
    for(i=0;i<100;i++)
    {
        T.pass[E.pass[i]]=pass[i];
        T.site[E.site[i]]=site[i];
    }
}

void PAss_MAker(char A[],int TYPE1,int TYPE2,int length)
{
    int i=0;
    char ch;
    INITIALIZE();


       if(TYPE2==0)
       {
           if(TYPE1==1)
           {
               randomize();
               while(i<length)
               {
                   ch=KEY[random(10)+52];
                   A[i]=ch;
                   i++;
               }

           }
           else
           {
               randomize();
               while(i<length)
               {
                   ch=KEY[random(52)];
                   A[i]=ch;
                   i++;
               }

               int U,L;
               U=random(length-1);
               A[U]=toupper(A[U]);

               do
               {
                    L=random(length-1);
               }while(U==L);
               A[L]=tolower(A[L]);
            }
            A[i]='\0';
           return;
       }

    if(TYPE1==3)
    {
        int U=0,L=0;
        char ch;

               randomize();
               while(i<length)
               {
                   ch=KEY[random(62)];
                   A[i]=ch;
                   i++;
               }

           int n=random(length-1);
           A[n]= KEY[random(10)+52];

           if(TYPE2==1)
           {
               int u,l,t=0;
               do{
                        u=random(length);

                        if(isalpha(A[u]))
                        {
                            A[u]==toupper(A[u]);
                            U++;
                        }
                }while(U==0);
              do{

                  do
                  {
                        l=random(length);
                  }while(l==t);
                        if(isalpha(A[l]))
                        {
                            A[l]==tolower(A[l]);
                            L++;
                        }
                }while(L==0);

           }
           A[i]='\0';
        return;
    }

    if(TYPE1==4)
    {
        int U=0,L=0,N=0;
        char ch;

               randomize();
               while(i<length)
               {
                   ch=KEY[random(84)];
                   A[i]=ch;
                   i++;
               }
                A[i]='\0';

                int u,l,n;
            if(TYPE2==1)
           {
               while(U==0||L==0)
               {
                  u=random(length-1);
                  l=random(length-4);
                  if(u==l)
                    l++;
                  if(isalpha(A[u])&&U==0)
                  {
                      A[u]==toupper(A[u]);
                      U++;
                      n=u;
                  }
                  if(isalpha(A[l])&&L==0&&l!=n)
                  {
                      A[l]==tolower(A[l]);
                      L++;
                  }
               }
           }
           if(TYPE2==2)
           {
             n=random(length-1);
             A[n]= KEY[random(10)+52];
           }
           if(TYPE2==3)
           {
               int t11=0,t22;
               while(U==0||L==0||N==0)
               {

                  u=random(length-1);
                  l=random(length-4);
                  if(u==l)
                    l++;
                  if(isalpha(A[u])&&U==0)
                  {
                      A[u]==toupper(A[u]);
                      U++;
                      t11=u;
                  }
                  if(isalpha(A[l])&&L==0&&l!=t11)
                  {
                      A[l]==toupper(A[l]);
                      L++;
                      t22=l;
                  }
                   n=random(length-2);
                   if(n!=t11&&n!=t22&&N==0)
                   {
                     A[n]=KEY[random(10)+52];
                     N++;
                   }
               }

           }
    }
}
SEQUENCE Seq_taker()
{
    SEQUENCE T;
    int i;
    char ch;

    PAss_MAker(T.pass,T1,T2,L);

    cout<<"ENTER THE SITE NAME\t: ";
    for( i=0 ; i<(sizeof(T.site)-2) ; )
    {
        ch=getch();
        if(ch==13) ///13 == enter
            break;
        if(ch==8)/// 8== backspace
        {
            if(i==0)
                {
                }
            else
               {
                cout<<"\b \b";
                i--;
               }
        }
        else
        {
             cout<<ch;
             T.site[i]=ch;
             i++;
        }
    }
        T.p_l=L;
        T.s_l=i;
    T.site[i]='\0';
    return T;

}
void Save_Cnfm(SEQUENCE T,ENCODE E)
{

   gotoxy(w/2-45,2); cout<<"+-----------------------------------+---------------------------------+----------+";
   gotoxy(w/2-45,3); cout<<"|                 SITE NAME         |             PASSWORD            |    ID    |";
   gotoxy(w/2-45,4); cout<<"+-----------------------------------+---------------------------------+----------+";
   gotoxy(w/2-45,5); cout<<"|       "<<T.site;
   gotoxy(w/2-9,05); cout<<"|       "<<T.pass;
   gotoxy(w/2+25,5); cout<<"|   "<<T.id;
   gotoxy(w/2+36,5); cout<<"|";
   gotoxy(w/2-45,6); cout<<"+-----------------------------------+---------------------------------+----------+";

   gotoxy(w/2-15,10);cout<<"DO YOU WANT TO SAVE IT(Y|N)? : ";
   char ch;
   cin>>ch;
   ch=toupper(ch);

   EncryptFile_DAta(T,E);

   switch(ch)
                {
                    case 'Y':
                        {
                            clrscr();
                            gotoxy(w/2-8,h/2);
                            cout<<"!!DATA SAVED!!"<<"\a";
                            getch();
                            fstream file,FIL;
                            if(T.id!=1)
                            {
                              file.open("SEQUENCE.DAT",ios::binary|ios::in|ios::out|ios::app);
                              FIL.open("ENCODE.DAT",ios::binary|ios::in|ios::out|ios::app);
                            }
                            else
                            {
                              file.open("SEQUENCE.DAT",ios::binary|ios::out);
                              FIL.open("ENCODE.DAT",ios::binary|ios::out);
                            }
                            file.write((char*)&T,sizeof(T));
                            FIL.write((char*)&E,sizeof(E));
                            file.close();
                            FIL.close();
                            return;
                        }
                    default :
                        {
                            clrscr();
                            gotoxy(w/2-10,h/2);
                            cout<<"!!DATA NOT SAVED!!"<<"\a";
                        }
                }
}
void GENERATOR(char ch='M')
{
    TYPE(T1,T2);
    LENGTH();
    SEQUENCE T;
    T=Seq_taker();
    if(ch=='N')
    T.id=En_Make_Id();
    clrscr();
    LOADER();
    ENCODE E;
    E=En_Init();
    E.id=T.id;
    Save_Cnfm(T,E);
}
void Main_Menu()
{
    char ch;
    int op;

    do
    {

        do
        {
            gotoXY(w/2-16,h/4);
            cout<<"1.SEE PASSWORDS";
            gotoXY(w/2-16,h/4+1);
            cout<<"2.GENERATE PASSWORD";
            gotoXY(w/2-16,h/4+2);
            cout<<"ENTER CHOICE NUMBER[ ]\b\b";
            cin>>op;

            if(op==1)
                {
                    void Show_pass();
                    Show_pass();
                }
            else if(op==2)
                {
                   GENERATOR('N');
                }
            else
            {

            gotoxy(w/2-15,h/2-5);
            cout<<"!!WRONG CHOICE NUMBER!!\a";
            op=0;
            delay(2000);
            clrscr();
            }
        }while(op==0);

      clrscr();
      gotoxy(w/2-8,8);
      cout<<"RUN AGAIN(Y|N) ? ";
      cin>>ch;
      clrscr();
    }while(ch=='y'||ch=='Y');

}
int main()
{
   GET_CONSOLE_SIZE(h,w);
   Main_Menu();


}

void Show_pass()
{
    clrscr();

  fstream file1;
  file1.open("SEQUENCE.DAT",ios::binary|ios::in|ios::out);
  int i1=0;
  SEQUENCE S1;
  if(!file1)
  {
        gotoxy(w/2,5);
        cout<<"FILE NOT FOUND";
        return;
  }
  while(file1.read((char *)&S1,sizeof(S1)))
  {
      i1++;
  }
   file1.close();
   if(i1==0)
   {
       gotoxy(w/2-8,5);
       cout<<"~NO FILE FOUND~";
       getch();
       return ;
   }

    int pass;
    fstream fie;

    {
        fie.open("password.DAT",ios::app);
        fie.close();
        fie.open("password.DAT",ios::in|ios::out);
        randomize();
        pass= random(10000);
        fie<<pass;

        fie.close();
        gotoxy(w/2-10,1);
        clrscr();
    }
    int key;
    cout<<"ENTER THE PASSCODE : ";
    cin>>key;
    clrscr();
    remove("password.DAT");
    char op;
    if(key==pass)
    do{
        clrscr();
        fstream file,fil;
    SEQUENCE S;
    ENCODE E;

    file.open("SEQUENCE.DAT",ios::binary|ios::in|ios::out);
    fil.open("ENCODE.DAT",ios::binary|ios::in|ios::out);
    INT k=0;


   gotoxy(w/2-45,2); cout<<"+-----------------------------------+---------------------------------+----------+";
   gotoxy(w/2-45,3); cout<<"|                 SITE NAME         |             PASSWORD            |    ID    |";
   gotoxy(w/2-45,4); cout<<"+-----------------------------------+---------------------------------+----------+";
   ///void show(SEQUENCE,ENCODE);
   int i,f=0;
   while(file.read((char*)&S,sizeof(S)))
    {
        fil.read((char*)&E,sizeof(E));
        gotoxy(w/2-45,5+f); cout<<"|       ";
   for(i=0;i<S.s_l;i++)
   {
       cout<<S.site[E.site[i]];
   }
   gotoxy(w/2-9,05+f); cout<<"|       ";
   for(i=0;i<S.p_l;i++)
   {
       cout<<S.pass[E.pass[i]];
   }
   gotoxy(w/2+25,5+f); cout<<"|   "<<S.id;
   gotoxy(w/2+36,5+f); cout<<"|";

     f++;
    }
    gotoxy(w/2-45,5+f); cout<<"+-----------------------------------+---------------------------------+----------+";
    file.close();
    fil.close();


    gotoxy(w/2-9,10+f);cout<<"1.DELETE PASSWORD";
    gotoxy(w/2-9,11+f);cout<<"2.MODIFY PASSWORD";
    gotoxy(w/2-9,12+f);cout<<"3.BACK TO MENU";
    gotoxy(w/2-9,13+f);cout<<"CHOICE NUMBER[ ]\b\b";
    cin>>op;
  void Del_Pass();
    switch(op)
    {
      case '1':
              {
                  Del_Pass();
                  break;
              }
      case '2':
             {
               /**void Mod_Pass();
               Mod_Pass();*/
               break;
             }
      case '3':
            {
                  break;
            }
      default :
          {
              clrscr();
              gotoxy(w/2-12,14+f);cout<<"!!WRONG CHOICE NUMBER!!";
              getch();
          }
    }

    }while(op!='3');



}


void Del_Pass()
{
    int id;
do{
    clrscr();
    fstream file,fil;
    SEQUENCE S;
    ENCODE E;

    file.open("SEQUENCE.DAT",ios::binary|ios::in|ios::out);
    fil.open("ENCODE.DAT",ios::binary|ios::in|ios::out);

    if(!file)
    {
        gotoxy(w/2-8,5);
        cout<<"FILE NOT FOUND";
        return;
    }


   gotoxy(w/2-45,2); cout<<"+-----------------------------------+---------------------------------+----------+";
   gotoxy(w/2-45,3); cout<<"|                 SITE NAME         |             PASSWORD            |    ID    |";
   gotoxy(w/2-45,4); cout<<"+-----------------------------------+---------------------------------+----------+";
   ///void show(SEQUENCE,ENCODE);
   int i,f=0;
   while(file.read((char*)&S,sizeof(S)))
    {
        fil.read((char*)&E,sizeof(E));
        gotoxy(w/2-45,5+f); cout<<"|       ";
   for(i=0;i<S.s_l;i++)
   {
       cout<<S.site[E.site[i]];
   }
   gotoxy(w/2-9,05+f); cout<<"|       ";
   for(i=0;i<S.p_l;i++)
   {
       cout<<S.pass[E.pass[i]];
   }
   gotoxy(w/2+25,5+f); cout<<"|   "<<S.id;
   gotoxy(w/2+36,5+f); cout<<"|";

     f++;
    }
    gotoxy(w/2-45,5+f); cout<<"+-----------------------------------+---------------------------------+----------+";
    file.close();
    fil.close();

    gotoxy(w/2-12,8+f);cout<<"ENTER THE PASSWORD ID[ ]\b\b";
    cin>>id;
    file.open("SEQUENCE.DAT",ios::binary|ios::in|ios::out);
    ///fil.open("ENCODE.DAT",ios::binary|ios::in|ios::out);
    int flag=0;
   while(file.read((char*)&S,sizeof(S)))
    {
        ///fil.read((char*)&E,sizeof(E));
        if(id==S.id)
            flag=1;
    }
    file.close();
    if(flag==0)
    {
        clrscr();
        gotoxy(w/2-12,5);cout<<"!!WRONG CHOICE NUMBER!!";
        id=0;
        getch();
    }
    else
    {
      file.open("SEQUENCE.DAT",ios::binary|ios::in|ios::out);
      fil.open("ENCODE.DAT",ios::binary|ios::in|ios::out);

      clrscr();
        gotoxy(w/2-45,2); cout<<"+-----------------------------------+---------------------------------+----------+";
        gotoxy(w/2-45,3); cout<<"|                 SITE NAME         |             PASSWORD            |    ID    |";
        gotoxy(w/2-45,4); cout<<"+-----------------------------------+---------------------------------+----------+";

  while(file.read((char*)&S,sizeof(S)))
    {
        fil.read((char*)&E,sizeof(E));
        if(S.id==id)
        {
            gotoxy(w/2-45,5); cout<<"|       ";
   for(i=0;i<S.s_l;i++)
   {
       cout<<S.site[E.site[i]];
   }
   gotoxy(w/2-9,05); cout<<"|       ";
   for(i=0;i<S.p_l;i++)
   {
       cout<<S.pass[E.pass[i]];
   }
   gotoxy(w/2+25,5); cout<<"|   "<<S.id;
   gotoxy(w/2+36,5); cout<<"|";

        }

    }
    gotoxy(w/2-45,6); cout<<"+-----------------------------------+---------------------------------+----------+";
    file.close();
    fil.close();

    char op;
    gotoxy(w/2-11,10);cout<<"ARE YOU SURE (Y|N)? : ";
    op=getche();

    if(op=='y'||op=='Y')
    {
      file.open("SEQUENCE.DAT",ios::binary|ios::in|ios::out);
      fil.open("ENCODE.DAT",ios::binary|ios::in|ios::out);
      fstream FILE,FIL;
      FILE.open("SEQUENCE_.DAT",ios::binary|ios::in|ios::out|ios::app);
      FIL.open("ENCODE_.DAT",ios::binary|ios::in|ios::out|ios::app);

      int i=0;
      while(fil.read((char*)&E,sizeof(E)))
      {
          file.read((char*)&S,sizeof(S));
          if(id!=S.id)
          {
              FILE.write((char*)&S,sizeof(S));
              FIL.write((char*)&E,sizeof(E));
          }
          i++;
      }
       file.close();
       fil.close();
       FILE.close();
       FIL.close();
       remove("ENCODE.DAT");
       remove("SEQUENCE.DAT");
       rename("ENCODE_.DAT","ENCODE.DAT");
       rename("SEQUENCE_.DAT","SEQUENCE.DAT");
    }

    }

    }while(id==0);
}

