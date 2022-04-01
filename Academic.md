# IoT遠端門禁系統

## 目錄

## 100w摘要

從零打造可以從WAN遠端連線修改門禁密碼、上傳紀錄到雲端進出資料的門禁系統。從硬體線路配置、port forwarding到跨平台使用使用界面完成物聯網架構。將該專案作為開發軟硬體實力兼具的證明。
## 概述

在工程設計專題再次接觸到Arduino等相關硬體
透過NodeMCU
從Arduino硬體線路配置
透過Wifi模組將硬體連網
到登入界面、管理者界面等RWD UI
並設定ddns方便用戶連線
打造可以從WAN遠端修改密碼並將開門時間紀錄在Google sheet的IoT門禁系統

在誤打誤撞中學會解決經過許多硬體困難
也開發出完整的遠端門禁系統
## 動機

在工程設計專題再次接觸到Arduino等相關硬體，而這次想要嘗試物聯網的相關應用，於是我挑戰從零打造遠端門禁系統。並且門禁系統包括跨平排的使用者界面，在不同的裝置都能使用。功能包括：遠端修改密碼、將進出資料紀錄到雲端。該專案做為自己有能力結合硬體與軟體開發物聯網應用程式的證明。
## 實做

從學校老師借NodeMCU到開發出完整的遠端門禁系統耗時約一週，途中也遇到許多硬體困難和網路協定設定需要克服。

### 功能

硬體

數字輸入面板（輸入密碼用）

LED燈（模擬門的開關）

遠端修改密碼

登入登出機制
    包括紀錄登入狀態紀錄、對未登入用戶的redirect

登入界面

管理者界面
    可以修改密碼
    連結至雲端試算表紀錄

進出紀錄：
    整合至雲端試算表

### 成果
- Github 完整程式碼連結
- 影片
- 照片

### 架構

### 困難

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

將Port Forwarding和Reversed ip設定好後，又有新的問題出現:在web的routing時無法連到正確的route，都會被redirect到Root。如我要連至(`My WAN ip/login`時都被redirect到`My WAN ip/`)
#### HTTPS連線

當門被打開時，我的server要向我寫好的google app script發出請求(可以看成呼叫API)並將紀錄寫至google sheet中。但是在測試時發現無法將

要連線到

技術知識點：

在Linux作業系統編寫Arduino

透過Arduino燒入ESP01

透過USB轉UART燒入ESP01

NodeMCU連網

ESP8266 Webserver

Port Forwarding設定

google app script

https連線

fingerprint

UI界面(RWD) 

將前端與後端、硬體端點整合

## 心得

從無到有打造一個可以遠端修改密碼、將進出紀錄上傳至雲端的門禁系統對我是一個挑戰。將硬體需求

## 未來加強

增加即時影像功能

連接Line等通訊軟體

對連線不到AP的處理


