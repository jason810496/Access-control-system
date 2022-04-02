# IoT遠端門禁系統

## 目錄

## 100w摘要

從零打造可以從WAN遠端連線修改門禁密碼、上傳紀錄到雲端進出資料的門禁系統。從硬體線路配置、port forwarding到跨平台使用使用界面完成物聯網架構。將該專案作為開發軟硬體實力兼具的證明。
## 概述

契機：在工程設計專題再次接觸到Arduino等相關硬體
實作與技術細節：從NodeMCU硬體線路配置
運用相關Wifi模組將硬體連網
建立登入界面、管理者界面等RWD UI
並設定ddns方便用戶連線
打造可以從WAN遠端修改密碼並將開門時間紀錄在Google sheet的IoT門禁系統

困難與解決：NodeMCU , Port Forwarding , https連線...

成果：演示完整的遠端門禁系統

心得：
在除錯的過程中尋找網路資料與詢問相關專業人士
在過程學會解決經過許多實作IoT系統的問題
最後也成功開發出有完整功能的遠端門禁系統
## 動機

在工程設計專題再次接觸到Arduino等相關硬體，而這次想要嘗試物聯網的相關應用，於是我挑戰從零打造遠端門禁系統。並且門禁系統包括跨平排的使用者界面，在不同的裝置都能使用。功能包括：遠端修改密碼、將進出資料紀錄到雲端。該專案做為自己有能力結合硬體與軟體開發物聯網應用程式的證明。
## 實做

從學校老師借NodeMCU到開發出完整的遠端門禁系統耗時約一週，途中也遇到許多硬體困難和網路協定設定，自行從網路研究和詢問相關專業人士後實作出系統。

### 功能

#### 硬體

* 數字輸入面板（輸入密碼用）

* LED燈（模擬門的開關）

#### 軟體

使用者界面：

* 登入界面
專門給管理者登入的界面
* 登入登出機制
包括利用cookie紀錄登入狀態紀錄、對未登入用戶的redirect

* 管理者界面
可以遠端修改密碼
連結至雲端試算表紀錄

* 記錄門禁
將進出資料整合至Google雲端試算表

### 成果
- Github
- 影片
- 照片

線路配置

RWD使用者界面

### 架構與技術細節


NodeMCU連網

ESP8266 Webserver

Port Forwarding設定

google app script

https連線

fingerprint

UI界面(RWD) 

將前端與後端、硬體端點整合

### 困難

#### 在Linux系統編寫Arduino 

首先要解決serial port的permission denied問題，這是因為serial port的權限不足，無法完成燒入讀寫的動作。解決方法：使用`chmod`指令更變對檔案檔案的permission進行設定與更改。

#### NodeMCU腳位限制

在初次使用`NodeMCU`時忘記初始化腳位的`PinMode`(設定該腳位的訊號源是輸出、輸入)導致只有`GPIO4`和`GPIO5`正常運作(`GPIO`是`General Purpose Input Output`)所以先去買專用的擴充板，但事實上擴充板可控制的腳位數量與NodeMCU是相同的。在事後才發現是一開始沒有初始化腳位的問題，而不是NodeMCU的腳位限制。

NodeMCU照片
#### EPS01連線

因為當時以為是NodeMCU的腳位限制，所以我在搜尋相關資訊時發現：`EPS01`WiFi模組。我想：「將Arduino連接`ESP01`等於是一個有很多可控制腳位的`NodeMCU`」。由於沒有專門對接ESP01的燒入器，所以需要透過Arduino燒入ESP01，電腦與ESP01無法溝通。在經過幾天的測試和參考網路上不同資料的線路配置仍無法燒入，所以主動向網路上的專業人士協助。

透過Arduino燒入ESP01線路圖

透過USB轉UART線路圖

#### 重回NodeMCU

在重新查尋NodeMCU的GPIO後，發現其實有10來個腳位可以控制。所以再次測試時才發現原先是因為沒有初始化腳位所造成的問題。

將NodeMCU接上KeyPad和LED的線路配置

#### Port Forwarding

在寫好整體的Client server(這邊的server同樣是NodeMCU，NodeMCU可以使用相關library來作為TCP server)後嘗試以`LAN`(`Local Area Network`)測試都可以成功連至server。但是我想達成的功能不只要能在`LAN`連線也要能從`WAN`(`WAN`是`Wide Area Network`)連至server，但是無法連線。在查尋相關資料後，得知需要透過**Port Forwarding**(通訊埠轉發)的技術來達成透過`WAN`連接在`LAN`的裝置

AP後台Port Forwarding設定

這邊的Pubic ip是指對外的固定ip，private ip則是由`DHCP`(`Dynamic Host Configuration Protocol`)分配給裝置的`LAN ip`

port

因為當時不熟悉網管和AP使用者界面，我花了許多時間在設定port。最後將`WAN`和`LAN`的 80 port對接，並且server也要開在80 port也要確認NodeMCU有連到網路而且要在設定的`LAN ip`才成功。

又因為`DHCP`分配給NodeMCU的`LAN ip`不一定每次相同，所以我額外設定`reversed ip`(將指定的`LAN ip`保留給指定的裝置)

#### Routing

將Port Forwarding和Reversed ip設定好後，又有新的問題出現:在web的routing時無法連到正確的route，都會被redirect到Root。如我要連至(`My WAN ip/login`時都被redirect到`My WAN ip/`)請教相關專家後判斷應該是AP預設佔用80port對外聯絡，而routing的動作導致AP不知道將Client轉發到那裡所以就轉發會root。所以我嘗試開在8080port並將server也開在8080 port就解決routing的問題了。

#### HTTPS連線

當門被打開時，我的server要向我寫好的google app script發出請求(可以看成呼叫API)並將紀錄寫至google sheet中。但是在測試時發現無法向google app script發出請求，我判定應該是需要https連線才可以連至google。而搜尋eps2688相關社群的資料找到叫WiFiClientSecure的libaray透過fingerprint來建立https連線。因為N無法像瀏覽器一樣建立電子憑證，但是NodeMCU可以透過瀏覽器產生之憑證中的憑證指紋，偽裝成瀏覽器向網頁伺服器發出請求。

## 心得

從無到有打造一個可以遠端修改密碼、將進出紀錄上傳至雲端的門禁系統對我是一個挑戰。也因為不熟悉網管也沒實作物聯網的經驗，在實作的過程中遇到許多困難。從一開始對`WAN`、`LAN`都不了解到自己操作port forwarding和ddns設定。實作將完整的IoT遠端門禁系統的過程我學會打造物聯網和遠端連線的基本技術;在遇到參考網路資料都無法解決時，我主動請教IoT專業人士討論技術細節，也在討論過程中學到許多IoT的專業技術知識與經驗。

## 未來挑戰

增加即時影像功能：
更完善門禁系統的功能，讓管理者可以確認即時畫面

連接Line或messneger等通訊軟體：
當server出現錯誤時可以即時通知管理者

在管理者界面增加連接AP裝置的設定：
目前對AP的連線是寫定在程式中，應該要可以透過UI界面更變AP連線設定。

增加有時限性密碼和隨機亂數密碼功能：
管理者可以針對當前密碼設定有效日期，並在期限後生成隨機密碼。






