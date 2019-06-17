#include "zimo.h"
#include "uc1701.h"
void UC1701InverseCharDispaly(unsigned char ucLine, unsigned char ucRow, char *pcChar)
{
     do
     {
        UC1701InverseDispaly(ucLine,ucRow,*pcChar++);
        ucRow++;
        if(ucRow>15)
        {
             ucLine++;
            ucRow=0;
            if(ucLine>3)
                break;
        }
     }
     while(*pcChar!='\0');  
 }

void UC1701InverseChineseDispaly(unsigned char ucLine, unsigned char ucRow, unsigned char ucLength, char *pcChar)
{ 
     int i,j=0;

     for(j=0;j<ucLength;j++)
     {
         for(i=0;i<16;i++)
         {
             UC1701AddressSet((ucLine*2),(129-(ucRow*8)-i));
             UC1701DataWrite(~pcChar[j*32+i]);
         }  
         for(i=0;i<16;i++)
         {
             UC1701AddressSet((ucLine*2)+1,(129-(ucRow*8)-i));
             UC1701DataWrite(~pcChar[j*32+16+i]);
         }  
         ucRow = ucRow +2;
 }    
}
void screen_inverse_menu1()
{
        UC1701InverseChineseDispaly(0,0,2,dy);
        UC1701InverseChineseDispaly(0,4,1,he);
        UC1701InverseChineseDispaly(0,6,4,bphd);
}
void screen_inverse_menu2()
{        
        UC1701InverseChineseDispaly(1,0,2,dl);
        UC1701InverseChineseDispaly(1,4,1,he);
        UC1701InverseChineseDispaly(1,6,4,bphd);
}
void screen_inverse_menu3()
{            
        UC1701InverseChineseDispaly(2,0,4,glcs);
}
void screen_inverse_menu4()
{   
        UC1701InverseCharDispaly(3,0,"A");
        UC1701InverseChineseDispaly(3,1,3,xdl);
        UC1701InverseChineseDispaly(3,7,3,ppt);
 }
void screen_inverse_menu5()
{
        UC1701InverseCharDispaly(0,0,"B");
        UC1701InverseChineseDispaly(0,1,3,xdl);
        UC1701InverseChineseDispaly(0,7,3,ppt);
}
void screen_inverse_menu6()
{
        UC1701InverseCharDispaly(1,0,"C");
        UC1701InverseChineseDispaly(1,1,3,xdl);
        UC1701InverseChineseDispaly(1,7,3,ppt);
}

void screen_inverse_menu7()
{
        UC1701InverseCharDispaly(2,0,"A");
        UC1701InverseChineseDispaly(2,1,3,xdy);
        UC1701InverseChineseDispaly(2,7,3,ppt);
 }
void screen_inverse_menu8()
{           
        UC1701InverseCharDispaly(3,0,"B");
        UC1701InverseChineseDispaly(3,1,3,xdy);
        UC1701InverseChineseDispaly(3,7,3,ppt);
}
void screen_inverse_menu9()
{            
        UC1701InverseCharDispaly(0,0,"C");
        UC1701InverseChineseDispaly(0,1,3,xdy);
        UC1701InverseChineseDispaly(0,7,3,ppt);
}
void screen_inverse_menu10()
{
        UC1701InverseChineseDispaly(1,0,2,dy);
        UC1701InverseChineseDispaly(1,4,2,pc);
        UC1701InverseChineseDispaly(1,8,1,he);
        UC1701InverseChineseDispaly(1,10,2,pl);
}
void screen_inverse_menu11()
{
        UC1701InverseChineseDispaly(2,0,2,dy);
        UC1701InverseCharDispaly(2,4,"THD");
}
void screen_inverse_menu12()
{            
        UC1701InverseChineseDispaly(3,0,2,dl);
        UC1701InverseCharDispaly(3,4,"THD");
}
void screen_inverse_menu13()
{            
        UC1701InverseChineseDispaly(0,0,4,dyzdsj);
 }
void screen_inverse_menu14()
{           
        UC1701InverseChineseDispaly(1,0,4,dyzjsj);
}
void screen_menu1()
{
        UC1701ChineseDispaly(0,0,2,dy);
        UC1701ChineseDispaly(0,4,1,he);
        UC1701ChineseDispaly(0,6,4,bphd);
}
void screen_menu2()
{        
        UC1701ChineseDispaly(1,0,2,dl);
        UC1701ChineseDispaly(1,4,1,he);
        UC1701ChineseDispaly(1,6,4,bphd);
}
void screen_menu3()
{            
        UC1701ChineseDispaly(2,0,4,glcs);
}
void screen_menu4()
{   
        UC1701CharDispaly(3,0,"A");
        UC1701ChineseDispaly(3,1,3,xdl);
        UC1701ChineseDispaly(3,7,3,ppt);
 }
void screen_menu5()
{
        UC1701CharDispaly(0,0,"B");
        UC1701ChineseDispaly(0,1,3,xdl);
        UC1701ChineseDispaly(0,7,3,ppt);
}
void screen_menu6()
{
        UC1701CharDispaly(1,0,"C");
        UC1701ChineseDispaly(1,1,3,xdl);
        UC1701ChineseDispaly(1,7,3,ppt);
}
void screen_menu7()
{
        UC1701CharDispaly(2,0,"A");
        UC1701ChineseDispaly(2,1,3,xdy);
        UC1701ChineseDispaly(2,7,3,ppt);
 }
void screen_menu8()
{
        UC1701CharDispaly(3,0,"B");
        UC1701ChineseDispaly(3,1,3,xdy);
        UC1701ChineseDispaly(3,7,3,ppt);
}
void screen_menu9()
{
        UC1701CharDispaly(0,0,"C");
        UC1701ChineseDispaly(0,1,3,xdy);
        UC1701ChineseDispaly(0,7,3,ppt);
}
void screen_menu10()
{            
        UC1701ChineseDispaly(1,0,2,dy);
        UC1701ChineseDispaly(1,4,2,pc);
        UC1701ChineseDispaly(1,8,1,he);
        UC1701ChineseDispaly(1,10,2,pl);
}
void screen_menu11()
{
        UC1701ChineseDispaly(2,0,2,dy);
        UC1701CharDispaly(2,4,"THD");
}
void screen_menu12()
{            
        UC1701ChineseDispaly(3,0,2,dl);
        UC1701CharDispaly(3,4,"THD");
}
void screen_menu13()
{            
        UC1701ChineseDispaly(0,0,4,dyzdsj);
 }
void screen_menu14()
{           
        UC1701ChineseDispaly(1,0,4,dyzjsj);
}
void screen_menu(unsigned int n)
{
        UC1701Clear();
        switch(n)
        {
            case(1):
            {
                screen_menu1();
                screen_menu2();
                screen_menu3();
                screen_menu4();
                break;
            }
            
            case(2):
            {
                screen_menu5();
                screen_menu6();
                screen_menu7();
                screen_menu8();
                break;
            }
            
            case(3):  
            {
                screen_menu9();
                screen_menu10();
                screen_menu11();
                screen_menu12();
                break;
            }
            
            case(4):
            {
                screen_menu13();
                screen_menu14();
                break;
            }
        }
}
void  highlight(unsigned char screen_menu, unsigned char m, unsigned char n )//高亮第screen_menu个菜单的第m行,并恢复第n行
    {
        unsigned char array[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
         switch(array[screen_menu - 1][m-1])
          {
                        case(1):{screen_inverse_menu1();break;}
                        case(2):{screen_inverse_menu2();break;}
                        case(3):{screen_inverse_menu3();break;}
                        case(4):{screen_inverse_menu4();break;}

                        case(5):{screen_inverse_menu5();break;}
                        case(6):{screen_inverse_menu6();break;}
                        case(7):  {screen_inverse_menu7();break;}
                        case(8):{screen_inverse_menu8();break;}

                        case(9):{screen_inverse_menu9();break;}
                        case(10):{screen_inverse_menu10();break;}
                        case(11):{screen_inverse_menu11();break;}
                        case(12):{screen_inverse_menu12();break;}

                        case(13):{screen_inverse_menu13();break;}
                        case(14):{screen_inverse_menu14();break;}
                        default:break;
          }
         if(n != 100)
         {

         switch(array[screen_menu - 1][n-1])
         {
                        case(1):{screen_menu1();break;}
                        case(2):{screen_menu2();break;}
                        case(3):{screen_menu3();break;}
                        case(4):{screen_menu4();break;}

                        case(5):{screen_menu5();break;}
                        case(6):{screen_menu6();break;}
                        case(7):  {screen_menu7();break;}
                        case(8):{screen_menu8();break;}

                        case(9):{screen_menu9();break;}
                        case(10):{screen_menu10();break;}
                        case(11):{screen_menu11();break;}
                        case(12):{screen_menu12();break;}

                        case(13):{screen_menu13();break;}
                        case(14):{screen_menu14();break;}

                        default:break;
        }
         }
}
