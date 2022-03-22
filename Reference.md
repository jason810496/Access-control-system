### Reference

[Install ESP2688 board on Arduino IDE](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/)

[Linux serial port permisson denied](https://stackoverflow.com/questions/27858041/oserror-errno-13-permission-denied-dev-ttyacm0-using-pyserial-from-pyth)

https://playground.arduino.cc/Linux/All/#Permission

Error:
```shell
esptool.FatalError: Failed to connect to ESP8266: Timed out waiting for packet header
esptool.FatalError: Failed to connect to ESP8266: Timed out waiting for packet header
```
原本以為不是serial port的問題，因為我有查到permission denied的問題

permission denied的solution:


```shell 
sudo chmod 777 /dev/ttyUSB0  
```
不過沒有搞懂`777`的meaning
很像是更改`/dev/ttyUSB0`的權限
更：（`chmod`可以對檔案的許可權進行設定與更改，用法`chmod abc file`，a,b,c各為一個數字，分別代表User、Group、及Other的許可權。a,b,c各為一個數字，分別代表User、Group、及Other的許可權。其中`777`代表：設定所有人可以讀寫及執行
```shell
ls -l /dev/ttyUSB0    
```
看一下現在的狀態


解果經過以下幾個操作後，竟然可以用了！
我重載了`esptool`
按了nodeMCU的reset鍵跟flash鍵
重新看了serial port的選單發現有/dev/ttyUSB0 （原本只有/dev/ttyS4
允許`/dev/ttyUSB0`後就成功上傳了

更：正確操作
上傳程式前，必須先將模式切到Flash Mode，並按一下Reset鍵。上傳程式時，會出現「Hard resetting via RTS pin...」的訊息，然後停在「Connecting...」，這時只要按一下Reset鍵，就能進入上傳程序了。
上傳完成後，請把模式切回Normal Mode，再按一下Reset鍵，讓程式開始運作。

https://blog.jmaker.com.tw/esp8266-esp01/

show current connected WiFi ssid
`iwgetid` provides the ssid

`iwgetid` -r gives just the name.

記得把`Serial.begin(rate)`改成`9600`
原本找的範例程式碼是`115200`，在serial monitor回傳的都是亂碼
改成`9600`後就正常了

連接WiFi成功,可以在同一個網域連到nodeMCU了！

3/17 22:50

明天進度：
- 連上外部網站
- 完成硬體demo (看ESP8266可不可以接上Arduino 畢竟腳位太少了)
- flask app for admin user login etc

ThingSpeak 雲端平台