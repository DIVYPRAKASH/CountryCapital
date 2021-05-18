# CountryCapital

**SERVER:**
  1. Build docker image for server:
  
      `cd docker` 
      
      `docker build -t server:latest  -f Dockerfile.server .`
      
  2. Go to server folder and `mkdir Release`
  3. From the `Release` folder:
  
      `../server cmake ..`
      
      `../server make -j4`
  4. Now the server app should be present in the bin folder
  5. To run the app
  
      `../server ./bin/country_server`
      
      following message should appear on the console : `Starting REST interface. Listening on port 9080 `
  6. Pressing Ctrl + C exits the application 


**CLIENT:**
  1. Build docker image for client:
  
      `cd docker`
      
      `docker build -t client:latest  -f Dockerfile.server .`
      
  2. Go to client folder and `mkdir Release`
  3. From the `Release` folder:
  
      `../client cmake ..`
      
      `../client make -j4`
  4. Now the server app should be present in the bin folder
  5. To run the app
  
      `../client ./bin/client -h`
      
      Following message should appear on the console:
      
     ```Allowed options:
      -h [ --help ]              Produce help message
      -n [ --node ] arg          Specify source interface address.
      -m [ --method ] arg (=GET) Specify method GET or SET
      --country arg              Specify a country name
      --capital arg              Specify the capital of country ```


**USAGE:**
  
  1. Start the server (following the instructions above)
  2. Start the client :
      
      - To add a country and its capital : 
      
      `../client ./bin/client --node="127.0.0.1:9080" --method="SET" --country="Norway" --capital="Oslo"`
      
      If successfull , response would be :
      
      `STATUS_CODE : 200 STATUS_TEXT : OK`
      
     - To GET the capital of a country :
     
     `../client ./bin/client --node="127.0.0.1:9080" --method="GET" --country="Norway"`

      If successfull , response would be :
      
      ` STATUS_CODE : 200

        CAPITAL: Oslo`
    
     
