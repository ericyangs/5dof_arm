char isUartRxCompleted ;
char uart_buf[50];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
     UB_ServoMove(5,500,2000);
     delay(2500);
     UB_ServoMove(5,2000,2000);
     delay(2500);
}

//serialEvent()是IDE1.0及以後版本新增的功能，不清楚為什麼大部份人不願意用，這個可是相當於中斷功能一樣的啊!
void serialEvent()
{
  static unsigned int num=0;
  unsigned char ch=0;
  while (Serial.available()) 
  {    
    ch = Serial.read();              //一個位元組一個位元組地讀，下一句是讀到的放入字串陣列中組成一個完成的資料包
    uart_buf[num]=ch;
    num++;
     if(uart_buf[num-1]==0xED)
      {
        isUartRxCompleted = 1;
        num=0;
      }
  }
}

