# IoT遠端門禁系統

## 目錄

## 100w摘要

## 概述

## 動機


## 實做

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

- 影片
- 照片

### 困難

#### NodeMCU腳位限制

在初次使用`NodeMCU`時忘記初始化腳位的`PinMode`(設定該腳位的訊號源是輸出、輸入)導致只有`GPIO4`和`GPIO5`正常運作(`GPIO`是`General Purpose Input Output`)所以先去買專用的擴充板，但事實上擴充板可控制的腳位數量與NodeMCU是相同的。在事後才發現是一開始沒有初始化腳位的問題，而不是NodeMCU的腳位限制。
#### EPS01燒入

因為當時以為是NodeMCU的腳位限制，所以我在搜尋相關資訊時發現：`EPS01`WiFi模組。我認為將Arduino連接`ESP01`等於是一個有很多可控制腳位的`NodeMCU`。

#### 重回NodeMCU

在重新查尋NodeMCU的GPIO後，發現其實有10來個腳位可以控制。所以再次測試時才發現原先是因為沒有初始化腳位所造成的問題。
#### Port Forwarding

在寫好大致的Client server後嘗試以`WAN ip`(`WAN`是`Wide Area Network`)連至server，但是無法連線。
#### Routing

將Port Forwarding和Reversed ip設定好後，在web的routing時無法連到正確的route，都會被redirect到Root
#### HTTPS連線

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


