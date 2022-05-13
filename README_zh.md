# IoT 遠端門禁系統

[English version](https://github.com/jason810496/Access-control-system/blob/main/README.md)

註 . `編輯時間 2022/5/13`

這個系統現在無法使用（ 以下說明的`url`無法連線是正常的）因為資安疑慮加上 NodeMCU 是我跟老師借的 ， 而且我已經還回去了 ... 


## 說明 

這是一個演示的遠端門禁系統的專案，並且可以即時從遠端修改密碼...

## 功能

- **這個系統可以從外網（ WAN ）連線**

- **可以遠端、即時的修改密碼**

- **可以將進出紀錄同步到雲端( Google 試算表 )**

- **有前端管理者使用界面( 跨裝置界面 )**

- **有後端身分驗證系統( 讓管理者登入 )**

## 如何連接到本系統 ？ 

### 指需要在瀏覽器輸入該網址

打開瀏覽器 , 並輸入 `nodemcu314.ddns.net` .

過幾秒 , 就可以成功連線到本**遠端門禁系統** 

## 網址背後的技術細節

### 保留 ip 位置( Reserved IP )
NodeMCU 必須先連接到 WiFi 路由器，而路由器會指定一個私有 ip 給NodeMCU ( 例如 `192.168.0.5` ) , 這個過程會遵守動態主機設定協定 (DHCP  , 在內部網路自動分配私有 ip 給各個裝置的管理協定) 

而問題是：每次裝置被分配到的私有 ip 都不一定會一樣

設定保留 ip ，路由器會保留一組私有 ip (以 `192.168.0.9` 為例 )給特定裝置（ 路由器可以透過MAC地址來確認裝置 ）在設定保留 ip 後 , 該裝置在每次的流線都會被分配到 `192.168.0.9` 這個私有 ip 位置. 

### 通訊埠轉發 ( Port Forwarding )  

要從外網控制裝置，在路由器設定**通訊埠轉發**是必要的，這樣路由器才能轉發從外網的特定通訊埠的請求給我的裝置( NodeMCU )

缺少通訊埠轉發 ， 路由器就不知道該如何處理這些從外網連線的請求 ，使用者也無法從遠端控制裝置。

### 網域設定 ( DNS )

我使用 [no-ip](https://www.noip.com/) 來管理這些暫時的網域設定 ( 將 ip 位置轉為網址 ) 達成更便利、友善的使用者環境（相較於手動輸入 ip 位置 ) 

最後使用 `nodemcu314.ddns.net` 當作我的網域名 ， 所以在瀏覽器輸入 `http://nodemcu314.ddns.net/` 就可以連線到 NodeMCU ( 它同時可以被視為一個網頁伺服器 )

### 完成設定後

使用者可以在瀏覽器輸入 `nodemcu314.ddns.net` 來連線到系統 ，會直接導引到初始的網頁首頁

### 路由＆重新導向( Routing & Redirecting )

管理者界面在 `nodemcu314.ddns.net/admin` 但是在沒有登入的情況並沒有權限進入管理者頁面 ， 系統會先將用戶重新導向到`nodemcu314.ddns.net/login` 先登入 。

## 如何更改門禁密碼 ?

1. 登入系統

2. 在管理者界面更改密碼

### 登入

連線到`nodemcu314.ddns.net/login`來登入到系統

### 更改密碼

在管理者界面 ( `nodemcu314.ddns.net/admin` ) 重設密碼

## 如何將門禁資料同步到雲端 ?

### Google App Script ( API )

Google App Script 允許開發者來創見 API ( 用 `Javascript` 寫 ) 與其他 Google 的產品互動 ( 如 : Google 試算表 , Google 地圖 , Gmail ... 等 )

### 向 API 發出 GET 請求

我建立一個 API ( 使用 Google App Script 架構 ) 來更新門禁資料到 Google 試算表 , 當 API 收到 GET 請求時會即時更新試算表的資料。

### 解決從 NodeMCU 建立 HTTPS 連線的困難

然額 ， 在一開始 NodeMCU 並沒有辦法連接到我的 API 。 原因是必須要透過 HTTPS 連線才能訪問 API , 但是要建立 HTTPS 連線需要先檢查**客戶端憑證的指紋**

為了解決問題 ， 我找到一個使用 EPS8266 WiFi 模組讓 NodeMCU 可以透過發送**客戶端憑證的指紋**建立 HTTPS 連線的[例子](https://circuits4you.com/2019/01/10/esp8266-nodemcu-https-secured-get-request/) ， 也解決 HTTPS 連線的問題 。 

## 部屬伺服器

NodeMCU 本身就是一個網頁伺服器 ， 在設定**通訊埠轉發**後，用戶可以從外網連線至系統 。

###### tags: `IoT` `NodeMCU` `Web Server` `Google App Script` `API` `Port Forwarding` 

