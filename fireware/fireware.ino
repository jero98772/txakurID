#include <ESP8266WiFi.h>

String dogname = "";
String dogtype = "";
String phone1 = "";
String ownername = "";
//String gender = "Macho";
String gender = "Hembra";
// si es hembra  añda a , si es macho no añada 

//opcional data 
bool optionaldata = true;
String phone2 = "";
String address = "";
String notes = "";
String email = "";
String diases = "";

const char* ssid = dogname.c_str();

WiFiServer server(80);

String header;

void setup() {
  Serial.begin(115200);

  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();   
  if (client) {                            
    Serial.println("New Client.");          
    String currentLine = "";              
    //Serial.print("7");
    while (client.connected()) {
      //Serial.print("6");          
      if (client.available()) {
        //Serial.print("5");            
        char c = client.read();             
        Serial.write(c);                   
        header += c;
        //Serial.print("4");
        if (c == '\n') {                  
          //Serial.print("3");next
          if (currentLine.length() == 0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            client.println("<!DOCTYPE html><html>");
            client.println("<head>");
            client.println("<meta charset='UTF-8'><title>identificacion perro</title></head><body>");
            client.println("<p><h1>yo soy  "+dogname+"</h1></p><hr>");
            if (gender == "Macho"){
                client.println("<p>soy un "+dogtype+" "+gender+"</p><br>");
                client.println("<p>mi dueño se llama <b>"+ownername+"</b>, si no lo vez cerca te agradesco que lo contactes , puedo estar perdido</p>");
              }
            else {
                client.println("<p>soy una "+dogtype+" "+gender+"</p><br>");
                client.println("<p>mi dueño se llama <b>"+ownername+"</b>, si no lo vez cerca te agradesco que lo contactes , puedo estar perdida</p>");
              }
            client.println("<p>su telefono es <b>"+phone1+"</b>, te agradesco si lo llamas.</p>");
            if (optionaldata){
              if (!(phone2 == "" && email == "")){
                client.println("<p>si nesitas otros medios de contacto puedes comunicarlo a</p>");
                if(!(phone2 == "")){
                  client.println("<p>otro es telefono es <b>"+phone2+"</b></p>");
                }
                if(!(email== "")){
                  client.println("<p>su email es <b>"+email+"</b></p>");
                }
              }
              if (!(diases == "")){
                client.println("<br><p>si no lo encuentras te agradesco  que me cuiedes un momento por que sufro de "+diases+"</p>");
              }
              if (!(address == "")){+
                client.println("<p>si no me puedes cuidar me puedes acompañar a mi casa , vivo en "+address+".</p>");
                }
              if (!(notes == "")){
                client.println("<br><p>"+notes+"</p>");
                }
              }
            break;
          }else{
            currentLine = "";
            Serial.print("-1");
          }
          Serial.print("-2");
        } else if (c != '\r') {  
          currentLine += c;
          Serial.print("-3");      
        }
      }
    }
    Serial.print("fin");
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
