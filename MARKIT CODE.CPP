#include<fstream.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<process.h>
#include<iomanip.h>

class item
{protected:
 char pr_name[15];int code,stock,qtyi,qtyo;float price,dcount,t;
 public:
 item();
 void input();
 void update_stock();

 void display();
 char* gpr_name(){return pr_name;}
 float getd()
 {return dcount;}
 int getcode()
 {return code;}
 float gett()
 {return t;}
 void putqty()
 {cin>>qtyo;}
 float getp()
 {return price;}
 void putt()
 {t=price-(price*dcount)/100;
  t*=qtyo;}

 friend void convert(item);
 friend void pay(int cod)};

 item::item()
 {strcpy(pr_name," ");
  code=0;
  qtyi=0;
  qtyo=0;
  stock=0;
  price=0.0;
  dcount=0.0;
  t=0.0;}

 void pay(int cod)
  {item i;
   fstream mf("item.dat",ios::binary|ios::in|ios::out);
   mf.read((char*)&i,sizeof(i));
   while(mf && i.getcode()!=cod)
   mf.read((char*)&i,sizeof(i));
   if(i.getcode()==cod)
   {long z=mf.tellg();
	 z-=sizeof(i);
    mf.seekg(z,ios::beg);
    cout<<"enter qty for "<<i.gpr_name();
    cin>>i.qtyo;
   for(int k=0;k<i.qtyo;k++)
    i.update_stock();
   i.t=i.price-(i.price*i.dcount/100);
   i.t*=i.qtyo;
   mf.write((char*)&i,sizeof(i));
   cout<<i.t<<'\n';}
   else cout<<"not found";

   }

 void convert(item i)
 {ifstream mf("cart.dat",ios::binary);
  ofstream tf("text.txt");
 mf.read((char*)&i,sizeof(i));
 while(mf)
 {tf<<i.pr_name<<' '<<i.code<<' '<<' '<<' '<<' '<<i.qtyo<<' '<<' '<<' '<<i.price<<' '<<' '<<' '<<i.dcount<<' '<<' '<<' '<<' '<<i.t<<endl;
  mf.read((char*)&i,sizeof(i));}
  mf.close();tf.close();}



 void item::update_stock()
 {stock--;}



  void item::display()
  {cout<<"CODE: "<<code<<'\n';
   cout<<"ITEM NAME: "<<pr_name<<'\n';
   cout<<"PRICE: "<<price<<" rupees"<<'\n';
   cout<<"DISCOUNT AVAIL: "<<dcount<<'%'<<'\n';
  }
  void item::input()
  {cout<<"enter the following details"<<'\n';
   cout<<"code";cin>>code;
   cout<<"item name";gets(pr_name);
   cout<<"price";cin>>price;
   cout<<"quantity";cin>>qtyi;
   stock=qtyi;
   cout<<"% discount available";cin>>dcount;}

 struct nam{char name[20],pass[20];};
 class retailer:public item
 {nam a;
  public:
  retailer();
   void putn()
   {gets(a.name);}
   char* getn()
   {return a.name;}
   char* getp()
   {return a.pass;}
   void newit();
   void new_r();
   void itemfile();
   void dispfile();
   void search(int num);
   void upd_stk(int num);
   };
 void retailer::newit()
 {fstream mf("item.dat",ios::binary|ios::app);
  if(!mf){exit(0);}
   item it;
   it.input();
   mf.write((char*)&it,sizeof(it));
   mf.close();}


 retailer::retailer():item()
  {strcpy(a.name,"no name");
   strcpy(a.pass," ");}

  void retailer::new_r()
  {//ofstream mf("ret.dat",ios::binary|ios::app);
   cout<<"name:";gets(a.name);
   cout<<"password:";
   gets(a.pass);}
  // mf.write("ret.dat",sizeof(a));}

/*  void r_menu(retailer s);
  int checkp(retailer s,char ch[20])
  {ifstream mf("ret.dat",ios::binary);
   nam q;
   mf.read((char*)&q,sizeof(q));
   while(mf && strcmpi(q.name,s.getn())!=0)
    mf.read((char*)&q,sizeof(q));
   if(strcmpi(q.name,s.getn())==0)
    {if(strcmp(q.pass,ch)==0)
     {mf.close();return 1;}
     else
     {mf.close();return 0;}}
   else {mf.close();return 0;}
	}
*/
 void retailer::itemfile()
 { ofstream mf("item.dat",ios::binary);
   if(!mf)
   {cout<<"error";exit(0);}
   item i;char ch;
   do{i.input();
      mf.write((char*)&i,sizeof(i));
      cout<<"more items?";cin>>ch;}while(ch=='y'||ch=='Y');
      mf.close();}


 void retailer::dispfile()
 {ifstream mf("item.dat",ios::binary);
  item it;
  mf.read((char*)&it,sizeof(it));
  while(mf)
  {it.display();
   cout<<"*************************************************************"<<'\n';getch();
   mf.read((char*)&it,sizeof(it));}
  mf.close();}

  void retailer::search(int num)
  {ifstream mf("item.dat",ios::binary);
   item i;
   mf.read((char*)&i,sizeof(i));
   while(mf&& i.getcode()!=num)
    mf.read((char*)&i,sizeof(i));
   if(i.getcode()==num)
    i.display();
   else
    cout<<"not found";
   mf.close();}

  void retailer::upd_stk(int num)//use with buy now
  {fstream mf("item.dat",ios::binary|ios::in|ios::out);
   if(!mf){exit(0);}
   item it;
   mf.read((char*)&it,sizeof(it));
   while(mf && it.getcode()!=num)
    mf.read((char*)&it,sizeof(it));
   if(it.getcode()==num)
    {long pos=mf.tellg();
     pos-=sizeof(it);
     mf.seekg(pos,ios::cur);
     it.update_stock();
     mf.write((char*)&it,sizeof(it));
     }
   else
    cout<<"not found";
  mf.close();}

 class consumer
 {char username[20];//add password
  public:
  consumer();
  void putu()
  {cin>>username;}
  void getname()
  {cout<<username<<'\n';}
  void search_n();
  void search_p();
  void search_d();
  void addcart(item it);
  };
  consumer::consumer()
  {strcpy(username," ");}

  void consumer::search_p()
  {int num;cout<<"enter code";cin>>num;
   ifstream mf("item.dat",ios::binary);
   item i;
   mf.read((char*)&i,sizeof(i));
   while(mf && i.getcode()!=num)
   mf.read((char*)&i,sizeof(i));
   if(i.getcode()==num)
   {i.display();
    char ans;
     cout<<"add to cart?";
     cin>>ans;
     if(ans=='y'||ans=='Y')
      addcart(i);
     else cout<<"thanks for visiting";}
   else
   cout<<"not found";
   mf.close();}

  void consumer::search_d()
  {float d;cout<<"enter desired discount";
   cin>>d;
   ifstream mf("item.dat",ios::binary);
   item i;
   mf.read((char*)&i,sizeof(i));
   while(mf && i.getd()!=d)
   mf.read((char*)&i,sizeof(i));
   if(i.getd()==d)
   {i.display();
    char ans;
     cout<<"add to cart?";
     cin>>ans;
     if(ans=='y'||ans=='Y')
      addcart(i);
     else cout<<"thanks for visiting";}
   else
   cout<<"not found";
   mf.close();}

  void consumer::search_n()//add to switch case
  {ifstream mf("item.dat",ios::binary);
   char prod[15];
   cout<<"what are you looking for?";
   gets(prod);
   item it;
   mf.read((char*)&it,sizeof(it));
   while(mf && strcmpi(prod,it.gpr_name())!=0)
    mf.read((char*)&it,sizeof(it));
   if(strcmpi(prod,it.gpr_name())==0)
    {it.display();
     char ans;
     cout<<"add to cart?";
     cin>>ans;
     if(ans=='y'||ans=='Y')
      addcart(it);
     else cout<<"thanks for visiting";
     }
    else cout<<"not found";
    mf.close();
    }
  void consumer::addcart(item it)
  {
   fstream mf("cart.dat",ios::binary|ios::app|ios::in|ios::out);
   item cart;
   cart=it;
   cout<<"enter qty for"<<cart.gpr_name();
   cart.putqty();
   cart.putt();
   mf.write((char*)&cart,sizeof(cart));
  // pay(it.getcode());


   mf.close();
   }
   void text();
   void bill()
   {retailer r;
   float z=0.0;
   ifstream nf("cart.dat",ios::binary);
   item i;
   nf.read((char*)&i,sizeof(i));
     while(nf)
      {z+=i.gett();
       r.upd_stk(i.getcode());
       nf.read((char*)&i,sizeof(i));}
//   clrscr();
   convert(i);text();
   cout<<'\n'<<"Please Pay Rupees "<<z;
   nf.close();
   remove("cart.dat");}



void text()
{ifstream tf("text.txt");
 char ch[100];
 gotoxy(0,8);

 cout<<"                       THANK YOU FOR SHOPPING WITH MARK-IT!           "<<'\n';
 cout<<"DATED:";
 char datebuf[9];
 _strdate(datebuf);
 cout<<datebuf;
 cout<<'\n'<<setw(10)<<"NAME"<<setw(10)<<"CODE"<<setw(10)<<"QTY"<<setw(10)<<"PRICE"<<setw(10)<<"DSCT"<<setw(10)<<"NET"<<endl;
 tf>>ch;int n=0;
 while(tf)
 {cout<<setw(10)<<ch;n++;
  if(n%6==0)
  cout<<'\n';
 // tf.getline(ch,100);
  tf>>ch;}
}
void c_menu(consumer m,retailer r)
{ remove("cart.dat");

	 int sel;char ch;
	 cout<<"VIEW ALL-1, SEARCH-2, EXIT-3";cin>>sel;
	 switch(sel)
	 {case 1:r.dispfile();break;
	  case 2:{int yep;
		do{cout<<"search via name-1,code-2,discount-3";
		   cin>>yep;
		   switch(yep)
		   {case 1:m.search_n();break;
		    case 2:m.search_p();break;
		    case 3:m.search_d();break;
		    default:cout<<"error";
		   }
		  cout<<"continue shopping?";
		  cin>>ch;
		  }while(ch=='y'||ch=='Y');
		if(ch=='n'||ch=='N')
		 {clrscr();
		  cout<<endl<<"Mr/Ms ";
		  m.getname();cout<<'\n';
		  bill();}
		 }break;
	  case 3:exit(0);break;
	  default:cout<<"error";break;
     }}

      void r_menu(retailer s);
	     void login(retailer s)
	      {	 char ent[]="......",ch;
		 nam o;int i=0,a=0;

		 cout<<"|--------------:RETAILER LOGIN:-------------------|"<<endl;
		 cout<<"|";cout<<setw(50)<<"|"<<endl;
		 cout<<"|";cout<<setw(50)<<"|"<<endl;
		 cout<<"|";cout<<setw(50)<<"|"<<endl;
		 cout<<"| USERNAME:";gets(o.name);
		 cout<<"|                                                 |"<<endl;
		 cout<<"|                                                 |"<<endl;
		 cout<<"| PASSWORD:                                       |"<<endl;
		 cout<<"|-------------------------------------------------|"<<endl;
		 while((int)a!=13 && i<20)
		  {ch=getch();
		   a=ch;
		   if(a!=13)
		   {cout<<'*';
		    ent[i]=ch;
		    i++;
		   }
		  }
		 if(strcmp(ent,"qwerty")==0)
		 {clrscr();r_menu(s);}
		 else cout<<endl<<"access denied"; }

	       void r_menu(retailer s)
		{int j;
		 cout<<"access granted"<<endl;
		 cout<<'\n'<<"Activate account -1,disp acc-2, search item-3, add item-4, exit-5"<<endl;
		 cin>>j;
		 switch(j)
		 {case 1:s.itemfile();break;
		  case 2:s.dispfile();break;
		  case 3:int no;cout<<"enter item no.";cin>>no;
			 s.search(no);break;
		  case 4:s.newit();break;
		  case 5:exit(0);
		  default:cout<<"error";
		  }
		 }





void main()
{clrscr();
 consumer m;
 retailer r;
 int num;int ch;item i;
do{ clrscr();
    gotoxy(30,5);cout<<"WELCOME TO MARK-IT"<<'\n';
    gotoxy(22,3);cout<<"----------------------------------";
    for(int i=3;i<=11;i++)
    {gotoxy(22,i);cout<<'|'<<'\n';}
    gotoxy(22,11);cout<<"----------------------------------";
    for( i=3;i<=11;i++)
    {gotoxy(56,i);cout<<'|'<<'\n';}

    gotoxy(28,8);cout<<"Select your domain:"<<'\n';
    gotoxy(28,9);cout<<"1.RETAILER";
    gotoxy(28,10);cout<<"2.CONSUMER";

    cin>>num; clrscr();
 switch(num)
 {case 1:login(r);;break;
  case 2: cout<<"Enter Username:";
	 m.putu();
	 c_menu(m,r);break;
  default:cout<<"error";}
  cout<<'\n'<<" go back-1  logout-2 exit-3";cin>>ch;} while(ch==2);
  if(ch!=2)
  switch(ch)
  {case 1: switch(num)
	  {case 1:r_menu(r);break;
	   case 2:c_menu(m,r);break;
	   default:cout<<"error";}break;
   case 3:exit(0);
   default:cout<<"error";}

  getch();}

