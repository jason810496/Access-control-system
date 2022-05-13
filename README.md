# IoT Access control system

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

## The tech behide 

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

### Login

### Change the Password

## How the system update the record to the Cloud ?

### Google App Script ( API )

### Get request to API

### Overcome the limitation of HTTPS connection 

## Web Server Deployment
NodeMCU can be seen as a server  , after setting **Port forwarding** , users are allowed to connect to the system from WAN ( Wide Area Network )

###### tags: `IoT`
