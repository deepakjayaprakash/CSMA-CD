#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include<windows.h> //  header file for gotoxy
#include <stdio.h>     //header file for standard input output
#define kmax 15
  COORD coord={0,0}; // this is global variable
                                    //center of axis is set to the top left cornor of the screen
 void gotoxy(int x,int y)
 {
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }



using namespace std;
typedef struct
{
    int data[4];
    int destination;
    int stn_no;
}frame;

void less_time_lag()
{
    for(unsigned long long i=0;i<50000000;i++);
}
void time_lag()
{
    for(unsigned long long i=0;i<200000000;i++);
}
void sendata();
void input();
int getFrame();
int t=0;    // timer
frame frames[7];
int status[7]={0},tts[7]={0},last=0,temp[7]={0},k=1;
int channel[57]={0},nos=0,nos1=0;
int is[7]={0},js[7]={0},ds[7]={1,1,1,1,1,1,1}; //ds for how may bites of data of that station is in that channel

void jamming()
{
	for(int i=1;i<=52;i++)
	channel[i]=999;
}



int persistence(int i)
{

if(ds[i]==1&&channel[i*10-9]!=0)
{
    cout<<"\n                    Channel is busy!! Thoda ruko  \n";
    getch();
            int r=rand()%20;
            cout<<"                    station "<<i<<" resending in "<<r<<" seconds !";
            getch();
            tts[i]+=r;
            return 0;
}
else return 1;
}

void collision(int st_no)
{
   // jamming();

    for(int i=1;i<=7;i++)   //copying the tts array back
    {
        if(status[i]==0)
        {
        tts[i]=temp[i];
    is[i]=0,js[i]=0,ds[i]=1;    //re-intialising the index variables back
    }
    }


    // back-off tr algorithm

    if(k>kmax)
    {
            tts[st_no]=0;   // meaning we're not going to send the data of this station again.

            cout<<"\n            Transmission of data from station "<<st_no<<" is aborted\n";
            nos1++;
            getch();
            system("cls");
            cout<<"\nResending data";
    for(int k=0;k<5;k++)
        {
            cout<<".";
            less_time_lag();
        }

            sendata();
    }
    else
        {
            int s=pow(2,k)-1;
            int r=rand()%s;
            tts[st_no]+=r;
            k++;
            system("cls");
            cout<<"\nResending data";
        for(int k=0;k<5;k++)
        {
            cout<<".";
            less_time_lag();
        }

            sendata();

        }
}
int main()
{
    cout<<"                                  CSMA - CD                                     "<<endl;
    cout<<"================================================================================";
        char ch;
	int des,fno;
	srand ( time(NULL) );
   for(int i=1;i<=6;i++)
 	{
 		cout<<"\nIs station "<<i<<" sending data?(y/n)";
 		cin>>ch;
 		if(ch=='y'|| ch=='Y')
 		{
            nos++;
 			cout<<"\nEnter time at which frame is to be sent : ";
 			cin>>tts[i];
 			cout<<"\nEnter the destination station : ";
 			cin>>frames[i].destination;
            cout<<"\nEnter data to be sent : ";
            for(int j=1;j<=3;j++)
                cin>>frames[i].data[j];
            frames[i].stn_no=i;
 		}
 	}

 	for(int i=1;i<=7;i++)
        temp[i]=tts[i];
    cout<<"\nSending data";
    for(int k=0;k<5;k++)
        {
            cout<<".";
            less_time_lag();
        }
 	sendata();
}

void send(int sno)
{
	int databit=0,leftmost,rightmost,l;	//data bit for the station to be sent
	if(ds[sno]<=3)
	databit=frames[sno].data[ds[sno]];
	if(is[sno]==0 && js[sno]==0)		//sending for first t
	{
		is[sno]=js[sno]=sno*10-9;
		channel[sno*10-9]=databit;
	}
	else
	{
		if(channel[js[sno]-1]!=0)
        {
            channel[js[sno]]=999;
        }
		if(channel[is[sno]+1]!=0)
        {
			channel[is[sno]]=999;
        }
    	{
			if(ds[sno]<=3)
			{
				int x;
				if(sno!=6 || is[sno]!=52)
				{
					is[sno]++;
					for(x=is[sno];x>sno*10-9;x--)
					channel[x]=channel[x-1];
				}
				if(sno!=1 || js[sno]!=0)
				{
					js[sno]--;
					for(x=js[sno];x<sno*10-9;x++)
					channel[x]=channel[x+1];
				}
			channel[sno*10-9]=databit;
			}
			else
			{
				int x;
				if(sno!=6)
				{
					//if(is[sno]!=51 || frames[sno].destination==6)
					is[sno]++;
					if(is[sno]==51)
                        channel[51]=channel[52]=channel[53]=0;
					x=is[sno];
					for(int i=1;i<=3;x--)
            		{
                		channel[x]=channel[x-1];
                		i++;
            		}
            	   if(x!=(sno*10-9)||sno==1)
               		channel[x]=0;
           		 }
				if(sno!=1)
				{
					if(js[sno]!=0 || frames[sno].destination==1)
					js[sno]--;
					x=js[sno];
					for(int j=1;j<=3;x++)
					{
				    	channel[x]=channel[x+1];
				    	j++;
					}
					channel[x]=0;
				}
				if(frames[sno].destination*10-9==(is[sno]-3))
            	{
                	 status[sno]=1;
                 	nos1++;
           	 	cout<<"\n            Data send succesfully from station "<<sno<<" to destination station "<<frames[sno].destination<<".";
            	getch();
            	}
            	if(frames[sno].destination*10-9==(js[sno]+3))
            	{
                	 status[sno]=1;
                 	nos1++;
            		cout<<"\n            Data send succesfully from station "<<sno<<" to destination station "<<frames[sno].destination<<".";
            		status[sno]=1;
           			 getch();


            	}
			}
   		 }
        for(int i=1;i<=6;i++)
       {
                if(channel[i*10-9]==999)
                    {
                        cout<<"\n            collision detected....station "<<i<<" jammed!!";
                        getch();
                        for(int y=0;y<=56;y++)
                            channel[y]=0;
                        collision(sno);
                    }
       }
	}
        ds[sno]++;
}
void sendata()
{
	int tmin=getFrame();
	if(tmin==0)
	cout<<"\nNo data to send!";
	for(int t=tmin;;t++)
	{
		if(t==tts[1]&&persistence(1))
		{
			send(1);
			tts[1]++;
		}
		if(t==tts[2]&&persistence(2))
		{
			send(2);
			tts[2]++;
		}
		if(t==tts[3]&&persistence(3))
		{
			send(3);
			tts[3]++;
		}
		if(t==tts[4]&&persistence(4))
		{
			send(4);
			tts[4]++;
		}
		if(t==tts[5]&&persistence(5))
		{
			send(5);
			tts[5]++;
		}
		if(t==tts[6]&&persistence(6))
		{
			send(6);
			tts[6]++;
		}
		cout<<endl;
        system("cls");

        gotoxy(12,18);
        if(nos==nos1)
            {
                cout<<"\n            All data sent sucessfully !! Party!!!!";
                getch();
                exit(0);
            }
        for(int l=1;l<52;l=l+10)
        {
            cout<<"S"<<(l/10)+1<<"         ";

        }
               cout<<endl;
                cout<<"Channel-->  ";
                cout<<"|";
		for(int j=1;j<51;j++)
        {
            if(j%10==1&&j!=1)
                cout<<"|";
            cout<<channel[j];
        }
         cout<<"|";
        time_lag();
	}
}
int getFrame()    // obtains the next frame based on tts
{
    int min=0,i;
	for( i=1;i<=6;i++)
	{
		if(tts[i]!=0)
		{
				min=i;
				break;
		}
	}
	if(min==0)
		return 0;
    for( i=1;i<=6;i++)
    {
		if(tts[i]<tts[min] && tts[i]!=0)
		min=i;
	}
	return tts[min];       // returns the frame with next minimum tts
}
