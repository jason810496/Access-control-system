const char ADMIN_HTML[] = R"=====(

<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style  type="text/css">

        *{
            margin: 0;
            padding: 0;
        }
        .header{
            position: absolute;
            top: 0%;
            left: 0%;
            width: 100%;
            height: 10%;
            background-color: rgb(52, 64, 75);
            
        }
        h2{
            font-size: 30px;
            font-weight: 900;
            letter-spacing:2px;
            font-family:'Courier New', Courier, monospace ;
            color: aliceblue;
            padding-left: 20px;
            padding-top: 20px;
        }
        .container{
            text-align: center;
            position: absolute;
            top:20%;
            width: 100%;
            height: 50%;
            background-color: rgb(67, 170, 122);
        }
        .input-group{
            position: absolute;
            top:10%;
            background-color: rgb(133, 91, 91);
            width: 100%;
            left: auto;
            height: 220px;

            min-width: 500px;
        }
        button{
            position:absolute;
            left:75%;
            top:30%;
            width: 10%;
            min-width: 140px;
            height: 70px;
            border-radius: 10px;
            font-size: 30px;
            font-weight: 900;
            padding-top: 10px;
            border: 5px solid rgb(52, 64, 75);
            color: aliceblue;
            background-color: rgb(52, 64, 75);
            
        }

        input{
            position: absolute;
            left: 10%;
            top: 30%;
            height: 65px;
            width: 50%;
            border: 5px solid rgb(52, 64, 75);
            border-radius: 10px;
            background-color: rgb(139, 139, 151);

            /* text */
            letter-spacing:1px;
            font-family:'Courier New', Courier, monospace ;
            color: rgb(255, 255, 255);
            padding-left: 20px;
            font-size: 25px;
        }
        input::placeholder{
            letter-spacing:1px;
            font-family:'Courier New', Courier, monospace ;
            color: rgb(255, 255, 255);
            padding-left: 20px;
            font-size: 25px;
        }

        .check{
            position:absolute;
            left:42.5%;
            top:60%;
            width: 15%;
            min-width: 200px;
            height: 70px;
            border-radius: 10px;
            font-size: 30px;
            font-weight: 900;
            font-family:'Courier New', Courier, monospace ;
            padding-top: 10px;
            border: 5px solid rgb(52, 64, 75);
            color: aliceblue;
            background-color: rgb(52, 64, 75);
        }

        svg{
            position: absolute;
            left:5%;
        }
        .Record{
            position: absolute;
            left:40%;
            top:20px;
        }


        

        
        @media screen and (max-width: 960px) {
            .header {
                height: 70px;
            }
        }

        @media screen and (max-width: 500px) {
            
            button{
                height: 55px;
                min-width: 100px;
                font-size: 20px;
                left:50%;
            }
            
            input{
                width: 170px;
                height:50px;
                left:5%;
                font-size: 15px;
            }
            input::placeholder{
                font-size: 15px;
            }

            svg{
                width: 30px;
                height: 30px;
            }

            .check{
                min-width: 170px;
                height:50px;
                font-size: 20px;
                left: 25%;
            }
        }

        
    </style>
    <title>Admin Page</title>
  </head>
  <body>
    

    <!-- header -->
    <div class="bg-dark header">
        <h2 class="test" >Admin</h2>
    </div>

   
    <div class="container">
        <div class="input-group">
            <input name="PASSWORD" placeholder="New Password" type="text" >
            <button type="submit">Submit</button>
        </div>
        
        <div class="check" onclick="location.href='https://www.youtube.com/' ">
            <svg xmlns="http://www.w3.org/2000/svg" width="50px" height="50px" fill="currentColor" viewBox="0 0 16 16">
                <path d="M5 4a.5.5 0 0 0 0 1h6a.5.5 0 0 0 0-1H5zm-.5 2.5A.5.5 0 0 1 5 6h6a.5.5 0 0 1 0 1H5a.5.5 0 0 1-.5-.5zM5 8a.5.5 0 0 0 0 1h6a.5.5 0 0 0 0-1H5zm0 2a.5.5 0 0 0 0 1h3a.5.5 0 0 0 0-1H5z"/>
                <path d="M2 2a2 2 0 0 1 2-2h8a2 2 0 0 1 2 2v12a2 2 0 0 1-2 2H4a2 2 0 0 1-2-2V2zm10-1H4a1 1 0 0 0-1 1v12a1 1 0 0 0 1 1h8a1 1 0 0 0 1-1V2a1 1 0 0 0-1-1z"/>
            </svg>
            <a class="Record">Record</a>
        </div>
    </div>

   
  </body>
</html>

)=====";
