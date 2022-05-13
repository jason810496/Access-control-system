# IoT Remote Access control system

[中文版說明](https://github.com/jason810496/Access-control-system/blob/main/README_zh.md)

Note . `Edit time 2022/5/13`

The system is not available right now due to the cyber security concern , and my NodeMCU was borrowed from my teacher , and I have already return it back ...


## Description 

Demo of access control IoT system that allow admin user to change password instantly and control remotely

## Features

- **The system can be accessed from WAN (Wide Area Network)**

- **Change Password instanly and remotely**

- **Update the gate access record to Cloud ( Google Sheet )**

- **Front-end Management UI**

- **Back-end Authorization System (for Admin user to login)**

## How to Connect to the System ? 

### Simply type the URL on the browser

Open any browser , and type `nodemcu314.ddns.net` .

In a blink of an eye , you are successfully connect to the **Remote Access Control System** 

## The technique behide the URL 


### Reserved IP
NodeMCU have to connect to WiFi router first , once the NodeMCU connect to AP ,NodeMCU will be assigned with a private ip address ( such as `192.168.0.5`) , the process follow DHCP ( a network management protocol used to automate the process of configuring devices on IP networks ) . The problem is that the private ip address which assigned to the device ( such as NodeMCU ) would probably not be the same . 

Setting up `reserved ip` , router will reserve a private address ( take `192.168.0.9` for example )for a specific devices ( route will reconigize the device by MAC address ) . After setting reserved ip , that specific device will only be assigned with `192.168.0.9` private ip address . 


### Port Forwarding 
To remote control our device from WAN , it's essential to setup the **Port Forwading** in the AP ( Access Point , i.e. the WiFi route in my house )  , which **Forward** the request from WAN to my deviec (NodeMCU) 

### DNS Setting
I use [no-ip](https://www.noip.com/) to manage the temporary dynamic DNS record ( IP to domain name ) which is more user-friendly and convenient than manual typing IP address on the browser . 

I choise `nodemcu314.ddns.net` as my domain name , so that typing `http://nodemcu314.ddns.net/` on the browser would redirect to NodeMCU( which can also be seen as a Web server )

### After Setting 
The user could connect to the system by typing `nodemcu314.ddns.net` on the browser , which will render default home page .

### Routing & Redirecting

The Admin page is on `nodemcu314.ddns.net/admin` , but users are not permitted to access to the admin page without login .The system will redirect to user to `nodemcu314.ddns.net/login` to login first .

## How to change the Door Password ?

1. Login on the system

2. Reset the password on the Admin page

### Login

Go to `nodemcu314.ddns.net/login` to login on the system .

### Change the Password

Reset the password on the Admin page ( `nodemcu314.ddns.net/admin` )

## How the system update the record to the Cloud ?

### Google App Script ( API )

Google App Script allow programmer to create an API ( Writtern in `Javascript` ) that interact with various kind of Google's products ( Eg : Google Sheet , Google Map , Gmail ... etc )

### Get request to API
I build an API ( based on Google App Script ) that update the gate record on Google Sheet , when rescive a GET request from NodeMCU , the API will instantly update the sheet . 

### Overcome the obstacle of HTTPS request from NodeMCU 
However , NodeMCU can connect to my API in the beginning . The reason is that HTTPS is required to connect to the API , but HTTPS connection have to check the **client certificate fingerprint** first.

To overcome the obstacle , I found a [Example](https://circuits4you.com/2019/01/10/esp8266-nodemcu-https-secured-get-request/) using ESP8266 WiFi package that allow NodeMCU to start HTTPS connection by sending **lient certificate fingerprint** , which solve the problems .

## Web Server Deployment
NodeMCU can be seen as a server  , after setting **Port forwarding** , users are allowed to connect to the system from WAN ( Wide Area Network )

###### tags: `IoT` `NodeMCU` `Web Server` `Google App Script` `API` `Port Forwarding` 
