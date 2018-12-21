本專案需要使用的所有庫檔，將除了espsoftwareserial 庫之外的其他庫添加入arduino的libraries資料夾中，路徑為
C:\Users\Administrator\Documents\Arduino\libraries（不同配置下可能路徑有變）

git clone https://github.com/tzapu/WiFiManager.git 
-- WiFiManager can be installed via pio.home

git clone https://github.com/plerup/espsoftwareserial.git
-- espsoftwareserial can be installed via pio.home

git clone https://github.com/Super169/OLED12864.git
git clone https://github.com/Super169/UBTech.git -b dev

espsoftwareserial 庫需要替換掉ESP8266原本的軟串口庫，具體路徑因電腦不同而異，可根據報錯路徑進行替換，在我的電腦中，路徑為-》 C:\Users\Administrator\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.4.1\libraries\espsoftwareserial
