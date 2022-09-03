#include <Wire.h>
#include <DS3231.h>
#include "LedControl.h"
#include <SoftwareSerial.h>

SoftwareSerial Arduino_softserial(9,3);// Rx,Tx
int currentHour,currentMinute,currentSecond,currentMonth,currentYear,weekday;

int logic_for_31days_bangla;

int8_t indexOfA,indexOfB,indexOfC,indexOfD,indexOfE,indexOfF,indexOfG;

char c;
String dataIn;

String data1="\0",data2,data3,data4,data5,data6,data7;


//initialize byte maps

//NUMBERS:

byte zero[] = {0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c};

byte one[] = {0x3c, 0x62, 0x62, 0x5c, 0x40, 0x20, 0x18, 0x04};

byte two[] = {0x40, 0x20, 0x1e, 0x3f, 0x61, 0x60, 0x3f, 0x03};

byte three[] = {0x3c, 0x42, 0x81, 0x81, 0x99, 0xa5, 0x65, 0x38};

byte four[] = {0x3c, 0x42, 0x42, 0x3c, 0x42, 0x42, 0x42, 0x3c};

byte five[] = {0x1c, 0x22, 0x41, 0x71, 0x51, 0x11, 0x2e, 0x22};

byte six[] = {0x1c, 0x22, 0x41, 0x41, 0x71, 0x11, 0x10, 0x10};

byte seven[] = {0x60, 0x20, 0x20, 0x3c, 0x22, 0x22, 0x22, 0x3c};

byte eight[] = {0x1c, 0x22, 0x22, 0x22, 0xde, 0x02, 0x02, 0x03};

byte nine[] = {0x38, 0x50, 0x99, 0x89, 0x86, 0x40, 0x30, 0x08};//0x38, 0x52, 0x99, 0x89, 0x86, 0x40, 0x30, 0x08


//Boishakh:

byte boi[] ={0x44, 0x62, 0x51, 0x49, 0x52, 0xff, 0x04, 0x03};

byte sha[] = {0xa0, 0xa0, 0xaa, 0xa4, 0xae, 0xfb, 0x00, 0x00};

byte kh[] ={0x78, 0x44, 0x48, 0x52, 0x4d, 0xc5, 0x00, 0x00};

//joishtho:

byte joi[] = {0xb2, 0x49, 0x75, 0x11, 0xa2, 0xff, 0x04, 0x03};

byte sh[] = {0x08, 0x91, 0x4a, 0x89, 0x50, 0xff, 0x00, 0x00};

byte tha[] = {0x07, 0x09, 0x09, 0x09, 0x07, 0xff, 0x06, 0x0c};

//AASHAR:

byte aa[] = {0x9e, 0xe1, 0xa1, 0xa1, 0xac, 0x9c, 0xff, 0x00};

byte sha1[] = {0xc2, 0xb2, 0x8a, 0xf2, 0x92, 0x8a, 0xff, 0x00};

byte r[] = {0x12, 0x32, 0x4a, 0x6a, 0x6a, 0x0a, 0xff, 0x00};

//SRABON:

byte sra[] = {0xbe, 0xa1, 0xa1, 0xaa, 0xa4, 0xae, 0xfb, 0x00};

byte bo[] = {0x10, 0x18, 0x14, 0x52, 0x54, 0x98, 0x3f, 0x00};

byte n[] = {0x04, 0x04, 0x04, 0x06, 0x06, 0x05, 0x1c, 0x00};

//VADRO:

byte va[] = {0x9c, 0xa2, 0xb9, 0x85, 0xa4, 0x98, 0xff, 0x00};

byte dra[] = {0x7c, 0x42, 0x5a, 0x68, 0x48, 0x08, 0xff, 0x00};

//AASHWIN:

byte aa1[] = {0x4c, 0x72, 0x51, 0x54, 0x4c, 0xff, 0x00, 0x00};

byte shwi[] = {0x85, 0x45, 0x85, 0x55, 0x25, 0xdf, 0x04, 0xf8};

byte n1[] = {0x21, 0x2d, 0x25, 0x39, 0x21, 0x3f, 0x00, 0x00};

//KARTIK:

byte ka[] = {0x8c, 0x8a, 0xa9, 0xba, 0x8c, 0xff, 0x00, 0x00};

byte rti[] = {0x72, 0x8a, 0x86, 0x92, 0x72, 0xff, 0x42, 0x9c};

byte k[] = {0x18, 0x14, 0x52, 0x74, 0x18, 0xff, 0x00, 0x00};

//AGRAHAYON:

byte aa2[] = {0x9e, 0xe1, 0xa1, 0xa1, 0xac, 0x9c, 0xff, 0x00};

byte gra[] = {0x3e, 0x21, 0xa4, 0x28, 0xa4, 0xb2, 0xec, 0x00};

byte ha[] = {0x14, 0xd2, 0x91, 0x12, 0x94, 0x53, 0xff, 0x00};

byte yo[] = {0x01, 0x07, 0x04, 0x05, 0x94, 0x94, 0x67, 0x00};

byte n2[] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00};

//POUSH:

byte pou[] = {0x42, 0x59, 0x69, 0x69, 0x5a, 0xff, 0x00, 0xf0};

byte sh1[] = {0x39, 0x45, 0x69, 0x59, 0x45, 0xff, 0x01, 0x00};

//MAGH:

byte ma[] = {0x57, 0x55, 0x5f, 0x54, 0x54, 0x53, 0xff, 0x00};

byte gh[] = {0x1e, 0x11, 0x12, 0x11, 0x11, 0x12, 0x3f, 0x00};

//FALGUN:

byte fa[] = {0x1e, 0x11, 0x12, 0x54, 0x52, 0x21, 0xff, 0x00};

byte lgu[] = {0x39, 0x45, 0x41, 0x25, 0x49, 0x25, 0xd9, 0x00};

byte n3[] = {0x10, 0x10, 0x19, 0x19, 0x16, 0x10, 0x7f, 0x00};

//CHOITRO:

byte choi[] = {0x3a, 0x49, 0x49, 0x39, 0x0a, 0xff, 0x0c, 0x03};

byte tra[] = {0x3e, 0x21, 0x2d, 0x24, 0x3c, 0x7f, 0x00, 0x00};


//January:

byte jan1[] = {0x10, 0x2c, 0x52, 0x5d, 0x24, 0x18, 0xff, 0x00};

byte jan2[] = {0x71, 0xb1, 0x25, 0x3d, 0x21, 0xa1, 0xff, 0x00};

byte jan3[] = {0xa2, 0xaf, 0xa9, 0xaa, 0xa9, 0xa8, 0xff, 0x80};

byte jan4[] = {0x12, 0x18, 0x14, 0x12, 0x14, 0x18, 0xff, 0x3f};

//February:

byte feb1[] = {0x82, 0xf9, 0x91, 0xa1, 0x91, 0x0a, 0xff, 0x00};

byte feb2[] = {0x7c, 0x60, 0x52, 0xca, 0x51, 0x60, 0xff, 0x00};

byte feb3[] = {0x10, 0x7c, 0x48, 0x51, 0x49, 0x44, 0xff, 0x00};

byte feb4[] = {0x55, 0x65, 0x55, 0x4d, 0x55, 0x65, 0xff, 0xfc};

//March:

byte mar1[] = {0x57, 0x55, 0x5f, 0x54, 0x53, 0xff, 0x80, 0xc0};

byte mar2[] = {0x07, 0x09, 0x09, 0x07, 0x01, 0x1f, 0x01, 0x00};

//April:

byte apr1[] = {0xbe, 0xa1, 0xa1, 0xac, 0xa4, 0xbc, 0x80, 0x00};

byte apr2[] = {0x3e, 0xa0, 0xae, 0xb2, 0x32, 0xee, 0x40, 0x3f};

byte apr3[] = {0x08, 0x08, 0x0a, 0x0f, 0x08, 0x1f, 0x00, 0x00};

//May:

byte may1[] = {0xba, 0xa9, 0xf9, 0xa1, 0xa1, 0x9a, 0xff, 0x00};

byte may2[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00};

//June:

byte jun1[] = {0xcc, 0xd2, 0x51, 0x9c, 0x44, 0x28, 0xff, 0x00};

byte jun2[] = {0x21, 0x2c, 0x24, 0x3c, 0x20, 0x20, 0x7f, 0x00};

//july:

byte jul1[] = {0xcc, 0xd2, 0x51, 0x9c, 0x44, 0x28, 0xff, 0x00};

byte jul2[] = {0x41, 0x44, 0x54, 0x7c, 0x40, 0x40, 0xff, 0x00};

byte jul3[] = {0x21, 0x11, 0x0d, 0x11, 0x25, 0x3d, 0x1f, 0xf0};

//August:

byte aug1[] = {0x9e, 0xe1, 0xa1, 0xa1, 0xac, 0x9c, 0xff, 0x00};

byte aug2[] = {0x42, 0x42, 0x4a, 0x52, 0x4a, 0x4a, 0xb3, 0x00};

byte aug3[] = {0x38, 0x48, 0x49, 0x2e, 0x0a, 0x09, 0xff, 0x1f};

//September:

byte sep1[] = {0x4a, 0x51, 0x71, 0x49, 0x49, 0x52, 0xff, 0x00};

byte sep2[] = {0xc2, 0x41, 0x59, 0x69, 0x69, 0x5a, 0xc3, 0x78};

byte sep3[] = {0x61, 0x52, 0x62, 0x5b, 0x78, 0x50, 0xff, 0x00};

byte sep4[] = {0x09, 0x0c, 0x0a, 0x09, 0x0a, 0x0c, 0x1f, 0x00};

//October:

byte oct1[] = {0x9e, 0xe1, 0xa1, 0xa1, 0xac, 0x9c, 0xff, 0x00};

byte oct2[] = {0xe2, 0x21, 0xa1, 0x31, 0xa9, 0x72, 0xff, 0x3c};

byte oct3[] = {0x84, 0xc5, 0xa5, 0x94, 0xa4, 0xc4, 0xff, 0x00};

byte oct4[] = {0x12, 0x18, 0x14, 0x12, 0x14, 0x18, 0x1f, 0x00};

//November:

byte nov1[] = {0x48, 0x2b, 0xa9, 0xaf, 0x28, 0x48, 0xff, 0x00};

byte nov2[] = {0x0e, 0x91, 0x1c, 0xc2, 0xd2, 0x8c, 0xff, 0x00};

byte nov3[] = {0x4b, 0x62, 0x53, 0x4a, 0x53, 0x62, 0xff, 0x00};

//December:

byte dec1[] = {0x39, 0x45, 0x45, 0x75, 0x15, 0x11, 0xff, 0x1f};

byte dec2[] = {0x4a, 0x51, 0x71, 0x49, 0x49, 0x52, 0xff, 0x00};

byte dec3[] = {0x2c, 0x8a, 0x4c, 0x2b, 0x4f, 0x8a, 0xff, 0x00};

byte dec4[] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00};


//DAYS

//SUNDAY:

byte RO[] ={0x59, 0x54, 0x52, 0x54, 0x58, 0xff, 0x40, 0x80};

byte BI[] ={0x0c, 0x0a, 0x09, 0x0a, 0x0c, 0x3f, 0x10, 0x0f};

//MONDAY:

byte sho[] = {0x4a, 0x51, 0x71, 0x49, 0x49, 0x52, 0xff, 0x00};

byte m[] = {0x5d, 0x55, 0x7d, 0x51, 0x51, 0x4d, 0xff, 0x00};

//TUESDAY

byte mo[] = {0x17, 0x95, 0x5f, 0x14, 0xd4, 0x53, 0xdf, 0x00};

byte ng[] = {0x41, 0x40, 0x44, 0x48, 0x65, 0x65, 0xd9, 0x00};

byte l[] = {0x10, 0x11, 0x15, 0x1f, 0x10, 0x10, 0x3f, 0x00};

//WED

byte bu[] = {0x9e, 0x4e, 0x2a, 0x49, 0xea, 0x2c, 0x5f, 0x00};

byte dh[] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00};


//THURS

byte bri[] = {0x04, 0x02, 0xcc, 0x0a, 0x69, 0x2a, 0xec, 0xff};

byte ho[] = {0x06, 0x01, 0x00, 0x01, 0x02, 0x02, 0x01, 0x07};

//FRI

byte shu[] = {0x38, 0xa8, 0x78, 0x20, 0x2a, 0x24, 0x2e, 0xd3};

byte kro[] = {0x3e, 0x21, 0x21, 0x20, 0xa8, 0x64, 0x24, 0xff};


//SAT

byte sho1[] = {0xa0, 0xa0, 0xaa, 0xa4, 0xbe, 0xeb, 0x80, 0x00};

byte ni[] = {0x10, 0x10, 0x14, 0x12, 0x12, 0x7c, 0x20, 0x1f};





// dot

byte dot[] = {0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00};



LedControl lc2=LedControl(7,6,5,8);//din,clk,load
LedControl lc1=LedControl(12,11,10,8);



//initialize time
int hr=14;
int mins=23;
int sec=45;

int day=3;
int day_bangla=25;
int month_bangla=8;
int year_bangla=3742;


int day_greg=23;
int month_greg=8;
int year_greg=2022;

//scrolling variable
int scroll=34;
int led[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33};
int gap=10000;
int greg_order=1;


int flag,fig = 0;// initial time

void setup () {
    Serial.begin(115200);
    Arduino_softserial.begin(115200);
    Wire.begin();
    //delay(500);
    //Serial.println("Nano Ready!");

  for(int i=0;i<8;i++){
    lc1.shutdown(i,false);
    lc1.setIntensity(i,1);
    lc1.clearDisplay(i);
  }

  for(int i=0;i<8;i++){
    lc2.shutdown(i,false);
    lc2.setIntensity(i,1);
    lc2.clearDisplay(i);
  }   
flag = 0;
  }





void initial(){
  //Serial.println("askgdgk");
  //Serial.println(Arduino_softserial.available());
    while (Arduino_softserial.available()>0){
      c = Arduino_softserial.read();

      // show all data to serial monitor
      //Serial.println("Hour : " + data1);
      //Serial.println("Minute : " + data2);
      //Serial.println("Second : " + data3);
      //Serial.println("Weekday : " + data4);
      //Serial.println("Month : " + data5);
      //Serial.println("Year : " + data6);
      //Serial.println("===================================================");      

      if(c == '\n') break;
      else  dataIn+=c;
    }
  if(c == '\n'){
      parseTheData();

      // reset the variable
      c = 0;
      dataIn = "";
    }


  //initialize variables

  hr=data1.toInt();
  mins=data2.toInt();
  sec=data3.toInt();
  

  
  day_greg=data4.toInt();
  month_greg=data5.toInt();
  year_greg=data6.toInt();
  day=data7.toInt();
  day=4;
  //Serial.println(day_greg);
conv();
  flag = 0;
  }


  void parseTheData(){
    indexOfA = dataIn.indexOf("A");
    indexOfB = dataIn.indexOf("B");
    indexOfC = dataIn.indexOf("C");
    indexOfD  = dataIn.indexOf("D");
    indexOfE  = dataIn.indexOf("E");
    indexOfF  = dataIn.indexOf("F");
    indexOfG  = dataIn.indexOf("G");


    data1 = dataIn.substring(0,indexOfA);
    data2 = dataIn.substring(indexOfA+1,indexOfB);
    data3 = dataIn.substring(indexOfB+1,indexOfC);
    data4 = dataIn.substring(indexOfC+1,indexOfD);
    data5 = dataIn.substring(indexOfD+1,indexOfE);
    data6 = dataIn.substring(indexOfE+1,indexOfF);
    data7 = dataIn.substring(indexOfF+1,indexOfG);
  }
// put bangla numbers in led

void no_pattern1(int number, int led_no){
  // This function takes all the splitted digits input from the clock data and puts output the Bangla Bitmap
  for(int i=0;i<8;i++){
    
    // setting up the bitmap case
      if(number==0){
   
               lc1.setRow(led_no,i,zero[i]); 
            
            }
    if(number==1){
   
               lc1.setRow(led_no,i,one[i]); 
            
            }
            if(number==2){
   
               lc1.setRow(led_no,i,two[i]); 
            
            }
            if(number==3){
   
               lc1.setRow(led_no,i,three[i]); 
            
            }
            if(number==4){
   
               lc1.setRow(led_no,i,four[i]); 
            
            }if(number==5){
   
               lc1.setRow(led_no,i,five[i]); 
            
            }
            if(number==6){
   
               lc1.setRow(led_no,i,six[i]); 
            
            }
            if(number==7){
   
               lc1.setRow(led_no,i,seven[i]); 
            
            }
            if(number==8){
   
               lc1.setRow(led_no,i,eight[i]); 
            
            }
            if(number==9){
   
               lc1.setRow(led_no,i,nine[i]); 
            
            }
    

  }

  
  }


void no_pattern2(int number, int led_no){
  // This function takes all the splitted digits input from the clock data and puts output the Bangla Bitmap
  for(int i=0;i<8;i++){
    
    // setting up the bitmap case
      if(number==0){
   
               lc2.setRow(led_no,i,zero[i]); 
            
            }
    if(number==1){
   
               lc2.setRow(led_no,i,one[i]); 
            
            }
            if(number==2){
   
               lc2.setRow(led_no,i,two[i]); 
            
            }
            if(number==3){
   
               lc2.setRow(led_no,i,three[i]); 
            
            }
            if(number==4){
   
               lc2.setRow(led_no,i,four[i]); 
            
            }if(number==5){
   
               lc2.setRow(led_no,i,five[i]); 
            
            }
            if(number==6){
   
               lc2.setRow(led_no,i,six[i]); 
            
            }
            if(number==7){
   
               lc2.setRow(led_no,i,seven[i]); 
            
            }
            if(number==8){
   
               lc2.setRow(led_no,i,eight[i]); 
            
            }
            if(number==9){
   
               lc2.setRow(led_no,i,nine[i]); 
            
            }
    

  }

  
  }
//put bangla calender in led


void bangla_calender(int led_no, int month){
  
  for(int i=0;i<8;i++){
    
    // setting up the bitmap case
      if(month==1){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
             
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,boi[i]);
             
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,sha[i]);
             
        } 
         if(greg_order==4){
               lc1.setRow((led_no),i,kh[i]);
          
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);
              
            }
      }
      
      if(month==2){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
              
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,joi[i]);
             
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,sh[i]);
             
        } 
         if(greg_order==4){
               lc1.setRow((led_no),i,tha[i]);
           
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);
         
            }
      }
      if(month==3){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
           
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,aa[i]);
        
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,sha1[i]);
       
        } 
         if(greg_order==4){
               lc1.setRow((led_no),i,r[i]);
     
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);
               greg_order=1;
            }
      }
      if(month==4){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
             
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,sra[i]);
         
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,bo[i]);
       
        } 
         if(greg_order==4){
               lc1.setRow((led_no),i,n[i]);
        
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);
               greg_order=1;
            }
      }
       if(month==5){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
         
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,va[i]);
      
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,dra[i]);
        
        } 
         if(greg_order==4){
               lc1.clearDisplay(led_no);
   
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);
        
            }
      }
                  if(month==6){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
          
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,aa1[i]);
        
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,shwi[i]);
           
        } 
         if(greg_order==4){
               lc1.setRow((led_no),i,n1[i]);
        
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);
      
            }
      }
                  if(month==7){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
        
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,ka[i]);
          
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,rti[i]);
      
        } 
         if(greg_order==4){
               lc1.setRow((led_no),i,k[i]);
      
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);
    
            }
      }
                  if(month==8){
        if(greg_order==1){
               lc1.setRow((led_no),i,aa2[i]);
   
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,gra[i]);
            
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,ha[i]);
             
        } 
         if(greg_order==4){
               lc1.setRow((led_no),i,yo[i]);
             
        } 
        if(greg_order==5){
               lc1.setRow((led_no),i,n2[i]);
     
            }
      }
                  if(month==9){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
   
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,pou[i]);
       
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,sh1[i]);
            
        } 
         if(greg_order==4){
               lc1.clearDisplay(led_no);
       
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);
   
            }
      }
                  if(month==10){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
       
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,ma[i]);
             
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,gh[i]);
   
        } 
         if(greg_order==4){
               lc1.clearDisplay(led_no);
      
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);

            }
      }
                  if(month==11){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
           
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,fa[i]);
    
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,lgu[i]);
  
        } 
         if(greg_order==4){
               lc1.setRow((led_no),i,n3[i]);
   
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);

            }
      }
                  if(month==12){
        if(greg_order==1){
               lc1.clearDisplay(led_no);
      
        }
        if(greg_order==2){
               lc1.setRow((led_no),i,choi[i]);
     
        } 
        if(greg_order==3){
               lc1.setRow((led_no),i,tra[i]);
          
        } 
         if(greg_order==4){
               lc1.clearDisplay(led_no);
       
        } 
        if(greg_order==5){
               lc1.clearDisplay(led_no);

            }
      }
  }


  
  }



  //put gregorian calender in led


void greg_calender(int led_no,int month){
  
  for(int i=0;i<8;i++){
    
    // setting up the bitmap case
      if(month==1){
               if(greg_order==1){
               lc1.setRow((led_no),i,jan1[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,jan2[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,jan3[i]); 
         
               } 

               if(greg_order==4){
               lc1.clearDisplay(led_no);

            }
              
            }

                  if(month==2){
               if(greg_order==1){
               lc1.setRow((led_no),i,feb1[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,feb2[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,feb3[i]); 
         
               } 

               if(greg_order==4){
               lc1.setRow((led_no),i,feb4[i]); 

            }
              
            }
                  if(month==3){
               if(greg_order==1){
                 lc1.clearDisplay(led_no);
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,mar1[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,mar2[i]); 
         
               } 

               if(greg_order==4){
               lc1.clearDisplay(led_no);

            }
              
            }
                  if(month==4){
               if(greg_order==1){
               lc1.setRow((led_no),i,apr1[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,apr2[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,apr3[i]); 
         
               } 

               if(greg_order==4){
               lc1.clearDisplay(led_no);

            }
              
            }
                  if(month==5){
               if(greg_order==1){
                lc1.clearDisplay(led_no);
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,may1[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,may2[i]); 
         
               } 

               if(greg_order==4){
               lc1.clearDisplay(led_no);

            }
              
            }
                  if(month==6){
               if(greg_order==1){
                 lc1.clearDisplay(led_no);
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,jun1[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,jun2[i]); 
         
               } 

               if(greg_order==4){
               lc1.clearDisplay(led_no);

            }
              
            }
                  if(month==7){
               if(greg_order==1){
               lc1.setRow((led_no),i,jul1[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,jul2[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,jul3[i]); 
         
               } 

               if(greg_order==4){
               lc1.clearDisplay(led_no);

            }
              
            }
                  if(month==8){
               if(greg_order==1){
               lc1.setRow((led_no),i,aug1[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,aug2[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,aug3[i]); 
         
               } 

               if(greg_order==4){
               lc1.clearDisplay(led_no);

            }
              
            }
                  if(month==9){
               if(greg_order==1){
               lc1.setRow((led_no),i,sep1[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,sep2[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,sep3[i]); 
         
               } 

               if(greg_order==4){
              lc1.setRow((led_no),i,sep4[i]); 

            }
              
            }
                  if(month==10){
               if(greg_order==1){
               lc1.setRow((led_no),i,oct1[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,oct2[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,oct3[i]); 
         
               } 

               if(greg_order==4){
              lc1.setRow((led_no),i,oct4[i]); 

            }
              
            }
                  if(month==11){
               if(greg_order==1){
               lc1.setRow((led_no),i,nov1[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,nov2[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,nov3[i]); 
         
               } 

               if(greg_order==4){
               lc1.clearDisplay(led_no);

            }
              
            }
                  if(month==12){
               if(greg_order==1){
               lc1.setRow((led_no),i,dec1[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,dec2[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,dec3[i]); 
         
               } 

               if(greg_order==4){
              lc1.setRow((led_no),i,dec4[i]); 

            }
              
            }

     
  }
}


void day_pattern(int led_no){
  
  for(int i=0;i<8;i++){
    
    // setting up the bitmap case
      if(day==7){
               if(greg_order==1){
               lc1.setRow((led_no),i,RO[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,BI[i]); 
            
               }
               if(greg_order==3){
               lc1.clearDisplay(led_no);
         
               } 


              
            }

                  if(day==1){
               if(greg_order==1){
               lc1.setRow((led_no),i,sho[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,m[i]); 
            
               }
               if(greg_order==3){
               lc1.clearDisplay(led_no);
               } 

              
            }
                  if(day==3){
               if(greg_order==1){
                 lc1.setRow((led_no),i,mo[i]);
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,ng[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,l[i]); 
         
               } 

              
            }
                  if(day==4){
               if(greg_order==1){
               lc1.setRow((led_no),i,bu[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,dh[i]); 
            
               }
               if(greg_order==3){
               lc1.clearDisplay(led_no);
         
               } 

              
            }
                  if(day==5){
               if(greg_order==1){
                lc1.clearDisplay(led_no);
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,bri[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,ho[i]); 
         
               } 

 
              
            }
                  if(day==6){
               if(greg_order==1){
                 lc1.clearDisplay(led_no);
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,shu[i]); 
            
               }
               if(greg_order==3){
               lc1.setRow((led_no),i,kro[i]); 
         
               } 
 
            }
                  if(day==7){
               if(greg_order==1){
               lc1.setRow((led_no),i,sho1[i]); 
              
               }
               if(greg_order==2){
               lc1.setRow((led_no),i,ni[i]); 
            
               }

               if(greg_order==3){
               lc1.clearDisplay(led_no);

            }
              
            }
  }
}


void disp(){
  int hr1,hr2,mins1,mins2,sec1,sec2;
  int day1_bangla,day2_bangla,yr1_bangla,yr2_bangla,yr3_bangla,yr4_bangla;
  int day1_greg,day2_greg,yr1_greg,yr2_greg,yr3_greg,yr4_greg;

  // getting the splitted english digits
  
  // set bangla year and day
  yr1_bangla=floor(year_bangla/1000);
  yr2_bangla=floor(year_bangla/100)-yr1_bangla*10;
  yr3_bangla=floor(year_bangla/10)-yr1_bangla*100-yr2_bangla*10;
  yr4_bangla=year_bangla-yr1_bangla*1000-yr2_bangla*100-yr3_bangla*10;
  day1_bangla=floor(day_bangla/10);
  day2_bangla=day_bangla%10;
  
  
  // set gregorian year and day
  yr1_greg=floor(year_greg/1000);
  yr2_greg=floor(year_greg/100)-yr1_greg*10;
  yr3_greg=floor(year_greg/10)-yr1_greg*100-yr2_greg*10;
  yr4_greg=year_greg-yr1_greg*1000-yr2_greg*100-yr3_greg*10;
  day1_greg=floor(day_greg/10);
  day2_greg=day_greg%10;
  
  
  
  hr1=floor(hr/10);
  hr2=hr%10;
  mins1=floor(mins/10);
  mins2=mins%10;
  sec1=floor(sec/10);
  sec2=sec%10;

  
  // generating the bitmaps


 // generating the number bitmaps

  no_pattern2(sec2,7);
  no_pattern2(sec1,6);

  for(int j=0;j<8;j++){
    
    lc2.setRow(5,j,dot[j]); 
    }
  no_pattern2(mins2,4);
  no_pattern2(mins1,3);
    for(int j=0;j<8;j++){
    
    lc2.setRow(2,j,dot[j]); 
    }
  no_pattern2(hr1,0);
  no_pattern2(hr2,1);
  

  int numbers[34]={day,day,day,gap,day1_bangla,day2_bangla,gap,month_bangla,month_bangla,month_bangla,month_bangla,month_bangla,gap,yr1_bangla,yr2_bangla,yr3_bangla,yr4_bangla,gap,gap,gap,day1_greg,day2_greg,gap,month_greg,month_greg,month_greg,gap,yr1_greg,yr2_greg,yr3_greg,yr4_greg,gap,gap,gap};
  
  for(int i=0;i<scroll;i++){

    //check whether to print
    if (led[i]<8){

      
      if( (i>=7) & (i<=11) ) {
        
          //Serial.println("bangla");
          greg_order=i-6;
        bangla_calender(led[i],numbers[i]);

      
      }
      
      
      else if((i>=23 & i<=25)){
       
          //Serial.println("greg");
          greg_order=i-22;
        greg_calender(led[i],numbers[i]);

        
        }

        else if(i<=2){
       
          //Serial.println("greg");
          greg_order=i+1;
        day_pattern(led[i]);

        
        }
      else if(numbers[i]==gap){
        //Serial.println("gap");
        lc1.clearDisplay(led[i]);
          }

       else{
        //Serial.println("number");
             no_pattern1(numbers[i],led[i]);
            }


      }

    

      
    //change led number

   led[i]=led[i]+1;
   if(led[i]==scroll){
    
    led[i]=0;
    }
    //Serial.println(led[i]);
    
  }
//Serial.println(" ");

}
  
// converting initial english time to bangla
void conv(){

  int day_e =14, me = 4;
int day_b = 1, mb = 1;
  
  int logic_for_31days_greg,logic_for_31day;
  for(int i =0; i<365;i++){

    logic_for_31days_bangla=(mb<=5);

  if(day_b==(30+logic_for_31days_bangla+1)){
    
    mb=mb+1;
    day_b=1;
       }
   
  logic_for_31days_greg=( ( (me<8) & ( (me%2)!=0 ) )| ( (me>=8) & ( (me%2)==0 ) ) );

  if(day_e==(30+logic_for_31days_greg+1)){
    
    me=me+1;
    day_e=1;
       }

    if ((day_e == 31) && (me == 12)){
      day_e = 1;
      me    = 1;
      }
     day_e++;
     day_b++; 

     if((day_e == day_greg) && ( me == month_greg)){
      day_bangla = day_b;
      month_bangla = mb;
      year_bangla=year_greg-593;
   // Serial.print(day_bangla);
   // Serial.print("\n");
   // Serial.print(month_bangla);
      break;
      }
    }
    //Serial.print(day_bangla);
    
    //Serial.print(month_bangla);
    
}


void loop () {
  delay(713);//713
  int leap;
  int logic_for_31days_bangla;
  int logic_for_31days_greg;


 // time initialization


 if(flag==0){
  if(fig<10){
   initial();
   fig++;
  }
  if (fig == 10){
   flag = 1;
  }
  if(data1!="\0"){
    flag = 1;
    }
    Serial.println(flag);
}
//Serial.println(fig); 
  
  //display present time
  disp();

  //update time
  
  
  sec=sec+1;
  if((mins==59)&(sec==60)){
    sec=0;
    mins=0;
    hr=hr+1;
  }
  else if(sec==60){
    mins=mins+1;
    sec=0;
  }

  //day change
  if(hr==24){
    sec=0;
    mins=0;
    hr=0;
    day_bangla=day_bangla+1;
    day_greg=day_greg+1;
  }


  //........................................update bangla calender......................................................................
  // month change
  
  // check leap year

  leap=0;
  if( ((year_bangla%400)==0) | ((year_bangla%4==0) & (year_bangla%100)) ){
    
    leap=1;
    }

    
  logic_for_31days_bangla=(month_bangla<=(5+leap));

  if(day_bangla==(30+logic_for_31days_bangla+1)){
    
    month_bangla=month_bangla+1;
    day_bangla=1;
       }
  

  // year change


  if(month_bangla==13){
    
    year_bangla=year_bangla+1;
    month_bangla=1;
    
    }




  //........................................update gregorian calender......................................................................
  // month change
  
  // check leap year

  leap=0;
  if(month_greg==2){
    if( ((year_greg%400)==0) | ((year_greg%4==0) & (year_greg%100)) ){
    
    leap=1;
    }

  }    
  logic_for_31days_greg=( ( (month_greg<8) & ( (month_greg%2)!=0 ) )| ( (month_greg>=8) & ( (month_greg%2)==0 ) ) );

  if(day_greg==(30+logic_for_31days_greg-leap+1)){
    
    month_greg=month_greg+1;
    day_greg=1;
       }
  

  // year change


  if(month_greg==13){
    
    year_greg=year_greg+1;
    month_greg=1;
    
    }

 
    
    
    
}
    
