#include<iostream.h>
#include<conio2.h>
#include<string.h>
#include<fstream.h>
#include<process.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<stdio.h>
using namespace std;
//using namespace conio;
class games
{
	public:
	int score;
	char name[15];
};

class member
{
	public:
	int credits;
	char name[15];
	char password[15];
	games last5[10];
	char access;
	int n;
};
void dispprofile(member x);
fstream file("member.dat",ios::in|ios::out|ios::binary|ios::ate);

void newmember(member &x)
{
	int flag;
	member s;
	member a;



		cout<<"\n\t\t Please enter your USERNAME: ";cin>>x.name;

	do{
		flag=1;
		cout<<"\n\n\t\t Enter your PASSWORD: ";cin>>x.password;
		if(strlen(x.password)<6||strlen(x.password)>13)
			{flag=0;cout<<"\n\t\t Password length should be between 6-13";}

	}while(!flag);
	cout<<"\n\t\t  ***You are given 30 free CREDITS!***";
	x.credits=30;x.n=0;x.access='y';
	file.write( (char*)&x,sizeof(x));
	getch();

}
int validate(member &x)
{
	char password[15], uname[15];
	file.seekg(0);
		cout<<"\n\t\t\tEnter USERNAME: ";cin>>uname;
		while(file.read( (char*)&x,sizeof(x)))
		if(!(strcmp(uname, x.name)))
		{cout<<"\n\t\t\t**USERNAME verified**";break;}

	cout<<"\n\n\t\t\tEnter PASSWORD: ";cin>>password;
	if((!strcmp(password, x.password)) && x.access=='y')
	return 1;
	else
		if(x.access=='n') cout<<"\n Your access is denied by Manager!";
	return 0;
}

void dispprofile(member x)
{
	system("cls");;
	cout<<"\n\tHi!, "<<x.name;
	cout<<'\t'<<'\t'<<'\t'<<"\t\t"<<"Credits: "<<x.credits;
	cout<<"\n\n\tYour Last 5 Played Games:\n\n\t\t         Game Name\t\tScore\n ";
	for(int i=0;i<x.n;i++)
	cout<<"           \t"<<i+1<<".    \t"<<x.last5[i].name<<"    \t"<<x.last5[i].score<<endl;
	cout<<"\n\t\t\t*****---------------------*****";
	cout<<"\n\n\t\t\t\t1.Play Games\n\n\t\t\t\t2.Edit Profile\n\n\t\t\t\t0.Logout";
	cout<<"\n\n\t\t\t*****---------------------*****";
}
int ptr;
char ch1;
void editprofile(member &x)
{

	char opass[10],npass[10],cpass[10];

	ptr=file.tellg();
	file.seekp(ptr-sizeof(x));
	do
	{
		system("cls");;
		cout<<"\n\n\t\tWhat do you want to change?";
		cout<<"\n\n\t\t1.USERNAME \n\n\t\t2.PASSWORD \n\n\t\t0.Back to profile\n ";cin>>ch1;

		switch(ch1)
		{
		case '1':cout<<"\nEnter new USERNAME(no spaces) ";cin>>x.name;
				 cout<<"\n Your new username is :" <<x.name; getche();
                 break;
		case '2':cout<<"\nEnter old PASSWORD:     ";cin>>opass;
				 cout<<"\nEnter new password:     ";cin>>npass;
				 cout<<"\nPlease confirm password:";cin>>cpass;

				 if( !strcmp(opass,x.password))
					 if( !strcmp(opass,cpass))
					 strcpy(x.password,npass);
					 else
					 cout<<"\nPasswords do not match";
				 else
					 cout<<"\nPlease enter correct old password";
				 break;
		case '0':cout<<"\n Your profile is being displayed";
		default:cout<<"\nINVALID CHOICE";
		}
	}
	while(ch1!='0');
	file.write( ((char*)&x) ,sizeof(x));
}
void wordgame(member &x)
{
	if(x.credits>=10)
	{
		x.credits-=10;
		system("cls");;
		char words[5][6][25]={ {"kiwi","peach","plum","guava","grapes","fruits"},
							  {"squash","fencing","lawn balls","gymnastics","javelin","sports"},
							  {"lamborghini","volkswagen","land rover","masserati","bentley","automobile companies"},
							  {"turkey","south africa","argentina","mauritius","madagascar","countries"},
							  {"islamabad","port louis","johannesburg","nairobi","kathmandu","capitals"}};
		char str1[20],str2[20],a,cd;
		int l=0,letters=0,scr=10,i,j,r,score=0;
		int k,flag,len=0;
		
 for(j=0;j<5;j++)
 {
	srand(time(0));
	r=(int)(rand()%5 );
	strcpy(str1,words[j][r]);
		scr=6+j;
	len=l=letters=0;
	for(i=0 ; str1[i]!='\0' ;i++)
	{
		len++;
		if(str1[i]==' ')
		str2[i]=1;
		else
		{
		 str2[i]=0;
		 letters++;
		}
	}

	cout<<"jital";
		while(letters>l && scr>0)
	{
	  system("cls");;
	  cout<<" \tLevel: "<<j+1<<'\n';
	  cout<<"\nCategory: "<<words[j][5]<<endl;
	  for(i=0 ; i<len ;i++)
	  {
		if(str2[i]==1) cout<<"   ";
		else
			if(str2[i]==0) cout<<" __";
			else
				 cout<<" "<<str2[i]<<" ";
	  }
	  cout<<endl<<"\nLetters "<<l<<"\t\t"<<"False hits left: "<<scr;


	  cout<<"\nEnter a letter: ";
	  cin>>a;

	  flag=1;
	  cd=(char)tolower(a);
	  for(i=0 ; str1[i]!='\0' ;i++)
	  {
		if(str1[i]==cd && str2[i]!=cd)
		{
		  str2[i]=cd;
		  flag=0;
		  l++;
		}
	  }

		if(flag)
		scr--;
	}
	score=+scr;
	if(!scr)break;
	}
		if(!scr) cout<<"\n You have lost";
		else     cout<<"\n You have won";
	  cout<<"\n\nYou have won "<<score<<" credits";
		x.credits=x.credits+score;
		for(int z=x.n;z>=0;z--)
		x.last5[z]=x.last5[z-1];
		strcpy(x.last5[0].name,"WORD GAME");
		x.last5[0].score=score*10;
		if(x.n<5)
        x.n++;
		ptr=file.tellg();
		file.seekp(ptr-sizeof(x));
		file.write( ((char*)&x) ,sizeof(x));
 }
	else cout<<"\n Credits too low";
	getche();
}
void memorygm(member &x)
{
  if(x.credits>=10)
  {
	int a[4][4]={{2,3,9,7},
					 {4,8,5,1},
					 {8,7,2,1},
					 {3,5,4,9}}, b[20][20];
	int i1, j1, i2, j2, box=0,i,mov=0,score;

	for(i=0; i<4; i++)
		for(int j=0; j<4; j++)
				b[i][j]=0;

		for(i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
				{
					if(b[i][j]==0)
						cout<<"["<<i<<j<<"]\t";
					else cout<<b[i][j];
				}
				cout<<endl;
		}
	while(box<=8&&mov<20)
	{
		cout<<"\nEnter Row, Column: ";
		cin>>i1>>j1;
		b[i1][j1]=a[i1][j1];
		system("cls");;
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
				{
					if(b[i][j]==0)
						cout<<"["<<i<<j<<"]\t";
					else cout<<b[i][j]<<'\t';
				}
				cout<<endl;
		}
		cout<<"\nEnter Row, Column: ";
		cin>>i2>>j2;
		b[i2][j2]=a[i2][j2];
		system("cls");;
		for(i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
				{
					if(b[i][j]==0)
						cout<<"["<<i<<j<<"]\t";
					else cout<<b[i][j]<<'\t';
				}
				cout<<endl;
		}
		if(b[i2][j2]!=b[i1][j1])
		{
			b[i2][j2]=0; b[i1][j1]=0;
		}
		else box++;
		 mov++;
	}
	score=25-mov;
		cout<<"\nYou have won"<<score<<"Credits";
		x.credits=x.credits+score-10;
		for(int z=x.n;z>=0;z--)
		x.last5[z]=x.last5[z-1];
		strcpy(x.last5[0].name,"MEMORY GAME");
		x.last5[0].score=score;
		if(x.n<5)
        x.n++;
		ptr=file.tellg();
		file.seekp(ptr-sizeof(x));
		file.write( ((char*)&x) ,sizeof(x));
  }
  else cout<<"\nCredits too low";
	getch();


}
void noguess(member &x)
 {
	int gses=0;
	int gsno=0;
	int simno=0;
	int score=0;
	char ans;
	srand(time(0));
		simno=(rand()%100) +1;
		cout<<"\nWelcome to High Low Game";
		cout<<"\n\nThe computer will randomly select a number from 1 to 100";
		cout<<"\n\nYou have to guess the number in 7 chances.";
		while(gses!=7)
		{
			cout<<"\nEnter Your Number: ";
			cin>>gsno;
			cout<<"\nYou have "<<7-gses<<" chances left.";
			gses++;
			if(gsno>simno)
				cout<<"\n\nNumber is High";
			else
				if(gsno<simno)
					cout<<"\n\nNumber is Low";
			else if(gsno==simno)
					 {
						cout<<"\n\nCongratulations!";
						cout<<"\n\nThe number is "<<simno;
						break;
					}

		}
		score=(8-gses)*2;
		cout<<"\nScore= "<<score;
		for(int a=x.n;a>=0;a--)
		x.last5[a]=x.last5[a-1];
		strcpy(x.last5[0].name,"NUMBER GUESS");
		x.last5[0].score=score*10;
		x.credits+=score;
		if(x.n<5)
        x.n++;
		ptr=file.tellg();
		file.seekp(ptr-sizeof(x));
		file.write( ((char*)&x) ,sizeof(x));
		getch();
}
void manager()
{
	member x;
	int a,flag,credits=0;
	char uname[15],ch;
	cout<<"\n\n\t\t\tEnter your PASSKEY: ";cin>>a;
	if(a==12345)
	{
	  ab:
	  system("cls");;
	  cout<<"\n\t\t\t    ***Welcome Manager***\n";
      file.clear();
	  file.seekg(0);
	  cout<<"\n\t\t***---------------------------------------***";
	  cout<<"\n\t\t\tName\tCredits\tStatus\tPassword";
	  while(file.read( (char*)&x,sizeof(x)))
	  cout<<"\n\n"<<"\t\t\t"<<x.name<<'\t'<<x.credits<<'\t'<<x.access<<'\t'<<x.password;
	  cout<<"\n\n\t\t***---------------------------------------***";
	  cout<<"\n\n\t\t\t1.Allow acess to Members.\n\t\t\t2.Deny access to Members.\n\t\t\t3.Add credits.\n\t\t\t0.Main menu\n\n\t\t\tEnter your choice: ";
	  ch='0';
      cout<<scanf(" %c",&ch);
	  flag=0;file.clear();file.seekg(0);
	  switch(ch)
	  {
		case '1': cout<<"\n\t\tName of Member you want to allow access: ";cin>>uname;
					while(file.read( (char*)&x,sizeof(x)))
						if(!(strcmp(uname,x.name)))
						{
							x.access='y';
							ptr=file.tellg();
							file.seekp(ptr-sizeof(x));
							file.write( ((char*)&x) ,sizeof(x));
							cout<<"\n\t\t\tMember: "<<uname<<" access allowed.";
							cout<<"\n\t\t   ***Access rights succesfully changed***";
							getch();flag=1;break;
						 }
						 if(!flag)cout<<"\n record does not exist";
						goto ab;
		case '2':  cout<<"\n\t\tName of member you want to deny access: ";cin>>uname;
					while(file.read( (char*)&x,sizeof(x)))
						if(!(strcmp(uname,x.name)))
						{
							x.access='n';
							ptr=file.tellg();
							file.seekp(ptr-sizeof(x));
							file.write( ((char*)&x) ,sizeof(x));
							cout<<"\n\t\t\tMember: "<<uname<<" access denied.";
							cout<<"\n\t\t   ***Access rights succesfully changed***";
							getch();flag=1;break;
						 }
						 if(!flag)cout<<"\n record does not exist";
						 goto ab;
		 case '3':  cout<<"\n\t\tName of member you want to add credits ";cin>>uname;
					cout<<"\n\t\tNo. of  credits to add ";cin>>credits;
					while(file.read( (char*)&x,sizeof(x)))
						if(!(strcmp(uname,x.name)))
						{
							x.credits+=credits;
							ptr=file.tellg();
							file.seekp(ptr-sizeof(x));
							file.write( ((char*)&x) ,sizeof(x));
							cout<<"\n\t\t\tMember: "<<uname<<" awarded "<<credits<<" credits\n";
							cout<<"\n\t\t   ***Credits added succesfully ***";
							getch();flag=1;break;
						 }
						 if(!flag)cout<<"\n record does not exist";
						 goto ab;
		case '0': break;
		 default: cout<<"\nInvalid choice";getch(); goto ab;
		}
	}
	else {cout<<"\nACCESS DENIED"; getch();}
}
void playgames(member &x)
{
	char chg;

	do{
		system("cls");;
		cout<<"\n\t\t  ***--------------------------------***";

		cout<<"\n\n\t\t\t Select game you want to play\n\n\t\t\t1.WORD GAME\t10credits\n\n\t\t\t2.MEMORY GAME\t 10credits\n\n\t\t\t3.NUMBER GUESS\t 0credits\n\n\t\t\t0.Back to profile";
		cout<<"\n\n\t\t  ***--------------------------------***";
		cout<<"\n\n\t\t\t Enter choice: ";
		chg='0';
        scanf(" %c",&chg);
	    switch(chg)
		{
			case '1':wordgame(x);break;
			case '2':memorygm(x);break;
			case '3':noguess(x);break;
			case '0':break;
			default:cout<<"\nINVALID CHOICE";
		}
	  }while(chg!='0');
}
int main()
{
	int val,i=0;
	char ch;
    member a;
 
	xyz:
	system("cls");
	cout<<"\n\t***:::============ Welcome to Zedge Games ============:::***";
	cout<<"\n\n\t\t      |::::::::::MAIN MENU::::::::::|";
	cout<<"\n\n\t\t---------------------------------------------";
	cout<<"\n\n\t\t\t1.Sign Up (Create A New Account) \n\n\t\t\t2.Login as Member\n\n\t\t\t3.Login as Administrator\n\n\t\t\t0.Exit";
	cout<<"\n\n\t\t---------------------------------------------";
	cout<<"\n\n\t\t\t     Enter your choice: ";
	ch='0';
    scanf(" %c",&ch);
	//cout<<ch;
	switch(ch)
	{
		case '1':newmember(a); goto xyz;
		case '2':val=validate(a); break;
		case '3':manager(); goto xyz;
		case '0':cout<<"\n Thanks for playing "; ch=getche();exit(0);
		default:cout<<"\n INVALID CHOICE \nPress Enter to continue";ch=getche();goto xyz;
	}
	if(val==0)
	{
		i++;
		if(i==3){cout<<"\n No tries left, restart again. ";exit(0);}
		cout<<"\nPlease enter correct password Tries left: "<<3-i; getche();
		goto xyz;
	}
	do
	{
		system("cls");;
		dispprofile(a);
		cout<<"\n\n\t\t\tEnter your choice: ";ch='0';
        scanf(" %c",&ch);
	
		switch(ch)
		{
			case '1': playgames(a);break;
			case '2': editprofile(a); break;
			case '0': goto xyz;
			default:cout<<"\n INVALID CHOICE ";getche();
		};
	}while(ch!='0');
	file.close();
 
   return 0;
}


