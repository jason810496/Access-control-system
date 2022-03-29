const char ADMIN_HTML[] = R"=====(

<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">

    <title>Hello, world!</title>
  </head>
  <body>
    

    <!-- header -->
    <nav class="navbar navbar-light bg-light">
        <div class="container-fluid">
          <span class="navbar-brand mb-0 h1">Admin</span>
        </div>
      </nav>
      
    <div class="w-75 h-50 bg-light position-absolute top-50 start-50 translate-middle " >
        <form method="post">
        
        <div class="input-group mb-3 p-5">
            <input name="cookie" type="text" class="form-control" placeholder="New Password" >
            <button name="change" value="Change" class="btn btn-outline-secondary" type="submit" >Submit</button>
        </div>
    
        <div class="col-auto"> 
            <button name="check" value="Check" type="submit" class="btn btn-secondary mb-3 position-absolute top-50 start-50 translate-middle">Check record</button>
        </div>
        
        </form>
    
    
    </div>
    

    
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js" integrity="sha384-IQsoLXl5PILFhosVNubq5LC7Qb9DXgDA9i+tQ8Zj3iwWAwPtgFTxbJ8NT4GN1R8p" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.min.js" integrity="sha384-cVKIPhGWiC2Al4u+LWgxfKTRIcfu0JTxR+EQDz/bgldoEyl4H0zUF0QKbrJ0EcQF" crossorigin="anonymous"></script>
   
  </body>
</html>

)=====";
