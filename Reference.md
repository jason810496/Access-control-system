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

https://www.youtube.com/watch?v=SiU-QZwik8w

nodemcu + arduino ( video)

透徹的了解keypad:

https://diyi0t.com/keypad-arduino-esp8266-esp32/


http://maker.tn.edu.tw/modules/tad_book3/page.php?tbdsn=385

arduino + ESP2688 接線

https://honeststore.com.tw/blog/esp8266_post/esp8266-pinout/

eps2688 pinout ( gpio )

https://randomnerdtutorials.com/projects-esp8266/

esp2688 project

https://hackmd.io/@wh91008/Sy9U8aZbB

google cloud function

https://create.arduino.cc/projecthub/pratikdesai/how-to-program-esp8266-esp-01-module-with-arduino-uno-598166

esp01 with arduino 

https://www.instructables.com/Using-ESP-01-and-Arduino-UNO/

esp01 with arduino project

https://www.instructables.com/Getting-Started-With-the-ESP8266-ESP-01/

get start with esp01

GPIO 意思：

General-Purpose Input Output

esp8266 GPIO pinout:

https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

NodeMCU GPIO setting with arduino IDE
https://www.electronicwings.com/nodemcu/nodemcu-gpio-with-arduino-ide


4X1 keypad :

但是有5個pin，數字朝最右邊的是GND

https://forum.arduino.cc/t/how-to-add-debounce-to-a-4x1-keypad-input-function/621001/4

4X1 keypad example code

--------- GPIO ----------

1 2 3 4 

3 2 4 5 GND 



esp01 error message
```

esptool.py v3.0
Serial port /dev/ttyUSB0
Connecting........_____....._____....._____....._____....._____....._____....._____
Traceback (most recent call last):
  File "/home/jason/.arduino15/packages/esp8266/hardware/esp8266/3.0.2/tools/upload.py", line 66, in <module>
    esptool.main(cmdline)
  File "/home/jason/.arduino15/packages/esp8266/hardware/esp8266/3.0.2/tools/esptool/esptool.py", line 3552, in main
    esp.connect(args.before, args.connect_attempts)
  File "/home/jason/.arduino15/packages/esp8266/hardware/esp8266/3.0.2/tools/esptool/esptool.py", line 529, in connect
    raise FatalError('Failed to connect to %s: %s' % (self.CHIP_NAME, last_error))
esptool.FatalError: Failed to connect to ESP8266: Timed out waiting for packet header
esptool.FatalError: Failed to connect to ESP8266: Timed out waiting for packet header
```

同時Webserver + TCPserver example : 

https://blog.csdn.net/baidu_40311265/article/details/120139534?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_paycolumn_v3&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_paycolumn_v3&utm_relevant_index=1


eps8266 wifi server相關 example code on Github

https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi/examples



接著去電子材料行補買ESP01後遇到的問題：

我按照這個教學操作：

[透過Arduino燒入ESP01](https://create.arduino.cc/projecthub/pratikdesai/how-to-program-esp8266-esp-01-module-with-arduino-uno-598166)

但是都無法連接到ESP01


所以只好再去補買Cp2101(USB轉UART)


flask get uset ip address 

https://stackoverflow.com/questions/3759981/get-ip-address-of-visitors-using-flask-for-python

NodeMCU的DNS設定（只有for內網

https://www.twblogs.net/a/5bd3dd3e2b717778ac20f967