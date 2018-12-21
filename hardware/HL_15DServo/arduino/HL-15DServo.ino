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

//serialEvent()是IDE1.0及以后版本新增的功能，不清楚为什么大部份人不愿意用，这个可是相当于中断功能一样的啊!  
void serialEvent()
{
  static unsigned int num=0;
  unsigned char ch=0;
  while (Serial.available()) 
  {    
    ch = Serial.read();              //一个字节一个字节地读，下一句是读到的放入字符串数组中组成一个完成的数据包
    uart_buf[num]=ch;
    num++;
     if(uart_buf[num-1]==0xED)
      {
        isUartRxCompleted = 1;
        num=0;
      }
  }
}

