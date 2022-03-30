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

### Get MAC address

https://techtutorialsx.com/2017/04/09/esp8266-get-mac-address/

### Get request with NodeMCU

https://randomnerdtutorials.com/esp32-http-get-post-arduino/


### Reversed ip 

Reserved IP設定

(TP link)[https://www.tp-link.com/tw/support/faq/182/]

如何在 TP-Link 無線路由器上設定位址保留

當您為 LAN 中的電腦指定一個保留的 IP 位址，該電腦每次連線到 DHCP 伺服器時，它會接收到同一個 IP 位址。如果 LAN 中的某些電腦需要永久的 IP 位址，請在路由器設定位址保留以達到此目的。

### 常見的port

https://yun1450.pixnet.net/blog/post/47494172

### Port forwarding (ASUS)

https://www.asus.com/tw/support/FAQ/114093/

### WAN , LAN 衝突

解決辦法

https://oilcut123.pixnet.net/blog/post/269282582


設定好reversed ip(將一個ip保留特定裝置)

可以解決果以下情況：

裝置在連線至AP(Access point，如路由器)時，AP會分配一組ip給該裝置，如A裝置為`192.168.3.10`、B裝置為`192.168.3.11`、C裝置為`192.168.3.12`，並且每個裝置每次被分配到的ip都不一定一樣

如下次連到網路時：剛好只有C裝置使用網路，就可能被分配到`192.168.3.10`的ip

假設現在NodeMCU被分配到的ip是`192.168.3.12`我port porwording將`192.168.3.12`對接WAN卻沒有使用reversed ip時

我不能保證下次ip位置是`192.168.3.12`的裝置一定是NodeMCU(也有可能在`192.168.3.12`的裝置是我的筆電、我的手機等)而外網可以連線到在`192.168.3.12`的裝置

假設下次的連線：NodeMCU的ip是`192.168.3.10`，而我的手機的ip`192.168.3.12`，port forwording一樣對接`192.168.3.12`在這種情況下：外網由WAN連線時是對接到我的手機而不是NodeMCU!這不但沒有達成外網連NodeMCU，還讓我的手機置於風險之中！

而Reversed ip 的功用是：

**將一個Private LAN ip保留給指定裝置**

那要如何**指定裝置**?

是透過MAC Address（裝置上的網卡）來指定

如：我NodeMCU的MAC address是`E0:98:06:85:E5:BD`

而其他裝置的MAC address會不同：可能是`A1:54:29:D5:38:81`等

透過Reversed ip 設定：

我們可以將`192.168.3.50`的ip都保留下來給MAC Adderss是`E0:98:06:85:E5:BD`的裝置（我的NodeMCU)

那這樣每次MAC Address是`E0:98:06:85:E5:BD`的裝置連線到AP時被分配到的ip都是`192.168.3.50`

所以將Port forwording的對接口改成`192.168.3.50`（透過Reversed ip 設定保留給NodeMCU的ip）就可以解決以上的情況了！


### 新問題

當我寫好大致的server時是開在`80 port`

結果在routing 時(連到`12.34.56.78/login`or`.../user`)卻一直被redirect到`root`（`12.34.56.78/`）去

原本以為是content-type的問題，因為有另一份code的return content-type剛好是`text/plain`就可以routing(我也還不確定卻切的原因)

我以為是






