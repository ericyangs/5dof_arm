#define uint8  unsigned char
#define uint32    unsigned int   
#define UB_SERVO_FRAME_HEADER1  0XFA
#define UB_SERVO_FRAME_HEADER2  0XAF
#define UB_SERVO_MOVE_ANGLE     0X01
#define UB_SERVO_LED            0X04
#define UB_SERVO_READ_ANGLE     0X02
#define UB_SERVO_ID_WRITE       0XCD
#define UB_SERVO_SET_OFFSET     0XD2
#define UB_SERVO_READ_OFFSET    0XD4
#define UB_SERVO_VERSION        0X01
#define UB_SERVO_FRAME_END      0XED
#define GET_LOW_BYTE(A)  ((uint8)(A))
#define GET_HIGH_BYTE(A) ((uint8)((A) >> 8))
extern char isUartRxCompleted ;
extern char uart_buf[50];
uint8 UB_ServoCheckSum(uint8 buf[])
{
  uint8 i;
  uint32 sum=0;
  for(i=2;i<8;i++)
  {
    sum +=buf[i];
  }
  if(sum>255)sum&=0x00FF;
  return sum;
}

void UB_ServoSetID(uint8 oldID,uint8 newID)
{
  uint8  buf[10];
  buf[0]=UB_SERVO_FRAME_HEADER1;
  buf[1]=UB_SERVO_FRAME_HEADER2;
  buf[2]=oldID;
  buf[3]=UB_SERVO_ID_WRITE;
  buf[4]=0x00;
  buf[5]=newID;
  buf[6]=0x00;
  buf[7]=0x00;
  buf[8]=UB_ServoCheckSum(buf);
  buf[9]= UB_SERVO_FRAME_END;
  Serial.write(buf,10);
  UB_ServoMsgHandle();

}

void UB_ServoMove(uint8 id,uint32 position,uint32 time)
{
  uint8  buf[10];
  buf[0]=UB_SERVO_FRAME_HEADER1;
  buf[1]=UB_SERVO_FRAME_HEADER2;
  buf[2]=id;
  buf[3]=UB_SERVO_MOVE_ANGLE ;
  buf[4]=(uint8)map(position,500,2500,0,180);
  //buf[4]=position;
  buf[5]=time/20;
  buf[6]=0x00;
  buf[7]=time/20;
  buf[8]=UB_ServoCheckSum(buf);
  buf[9]= UB_SERVO_FRAME_END;
  Serial.write(buf,10);
}

void UB_ServoReadPosition(uint8 id)
{
  uint8  buf[10];
  buf[0]=UB_SERVO_FRAME_HEADER1;
  buf[1]=UB_SERVO_FRAME_HEADER2;
  buf[2]=id;
  buf[3]=UB_SERVO_READ_ANGLE ;
  buf[4]=0x00;
  buf[5]=0x00;
  buf[6]=0x00;
  buf[7]=0x00;
  buf[8]=UB_ServoCheckSum(buf);
  buf[9]= UB_SERVO_FRAME_END;
   Serial.write(buf,10); 
  delay(2);
  UB_ServoMsgHandle();
}

void UB_ServoSetLED(uint8 id,uint8 on)
{
  uint8  buf[10];
  buf[0]=UB_SERVO_FRAME_HEADER1;
  buf[1]=UB_SERVO_FRAME_HEADER2;
  buf[2]=id;
  buf[3]=UB_SERVO_LED  ;
  buf[4]=on;
  buf[5]=0x00;
  buf[6]=0x00;
  buf[7]=0x00;
  buf[8]=UB_ServoCheckSum(buf);
  buf[9]= UB_SERVO_FRAME_END;
   Serial.write(buf,10);
}

void UB_ServoSetOffset(uint8 id,uint32 adjvalue)
{
  uint8  buf[10];
  buf[0]=UB_SERVO_FRAME_HEADER1;
  buf[1]=UB_SERVO_FRAME_HEADER2;
  buf[2]=id;
  buf[3]=UB_SERVO_SET_OFFSET;
  buf[4]=0x00;
  buf[5]=0x00;
  buf[6]=adjvalue/256;
  buf[7]=adjvalue%256;
  buf[8]=UB_ServoCheckSum(buf);
  buf[9]= UB_SERVO_FRAME_END;
  Serial.write(buf,10);
}

void UB_ServoReadOffset(uint8 id)
{
  uint8  buf[10];
  buf[0]=UB_SERVO_FRAME_HEADER1;
  buf[1]=UB_SERVO_FRAME_HEADER2;
  buf[2]=id;
  buf[3]=UB_SERVO_READ_OFFSET;
  buf[4]=0x00;
  buf[5]=0x00;
  buf[6]=0x00;
  buf[7]=0x00;
  buf[8]=UB_ServoCheckSum(buf);
  buf[9]= UB_SERVO_FRAME_END;
   Serial.write(buf,10);
  delay(10);
  UB_ServoMsgHandle();
}

void UB_ServoMsgHandle(void)
{
  if(isUartRxCompleted)
  {
    isUartRxCompleted=0;
    Serial.readBytes(uart_buf,10);
  }

}

