#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ESPAsyncTCP.h>
#include <Hash.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <math.h>
#include "CComplex.h"

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "Mooazam"
#define WIFI_PASSWORD "mooazam123"

#define API_KEY "AIzaSyBoexAmZSTYXPaikHub9Pggocd-xHg5Dhk"
#define DATABASE_URL "fourth-ir-protection-default-rtdb.firebaseio.com"

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

AsyncWebServer server(80);
WiFiClient client;

unsigned long sendDataPrevMillis = 0;
int i1m, i2m, i3m, i1p, i2p, i3p, v1m, v2m, v3m, v1p, v2p, v3p;
float floatValue;
String fault;

bool signupOK = false;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", ""))
  {
    Serial.println("ok");
    signupOK = true;
  }
  else
  {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase1_current_magnitude"))
    {
      if (fbdo.dataType() == "int")
      {
        i1m = fbdo.intData();
        Serial.println(i1m);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/input/phase2_current_magnitude"))
    {
      if (fbdo.dataType() == "int")
      {
        i2m = fbdo.intData();
        Serial.println(i2m);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase3_current_magnitude"))
    {
      if (fbdo.dataType() == "int")
      {
        i3m = fbdo.intData();
        Serial.println(i3m);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase1_current_angle"))
    {
      if (fbdo.dataType() == "int")
      {
        i1p = fbdo.intData();
        Serial.println(i1p);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase2_current_angle"))
    {
      if (fbdo.dataType() == "int")
      {
        i2p = fbdo.intData();
        Serial.println(i2p);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase3_current_angle"))
    {
      if (fbdo.dataType() == "int")
      {
        i3p = fbdo.intData();
        Serial.println(i3p);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase1_voltage_magnitude"))
    {
      if (fbdo.dataType() == "int")
      {
        v1m = fbdo.intData();
        Serial.println(v1m);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase2_voltage_magnitude"))
    {
      if (fbdo.dataType() == "int")
      {
        v2m = fbdo.intData();
        Serial.println(v2m);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase3_voltage_magnitude"))
    {
      if (fbdo.dataType() == "int")
      {
        v3m = fbdo.intData();
        Serial.println(v3m);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase1_voltage_angle"))
    {
      if (fbdo.dataType() == "int")
      {
        v1p = fbdo.intData();
        Serial.println(v1p);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase2_voltage_angle"))
    {
      if (fbdo.dataType() == "int")
      {
        v2p = fbdo.intData();
        Serial.println(v2p);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/input/phase3_voltage_angle"))
    {
      if (fbdo.dataType() == "int")
      {
        v3p = fbdo.intData();
        Serial.println(v3p);
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }

    //    float v1m = v1m.toFloat();
    //    float v1p = v1p.toFloat();
    float v1x = v1m * cos(v1p * 3.14 / 180.0);
    float v1y = v1m * sin(v1p * 3.14 / 180.0);

    //    float v2m = v2m.toFloat();
    //    float v2p = v2p.toFloat();
    float v2x = v2m * cos(v2p * 3.14 / 180.0);
    float v2y = v2m * sin(v2p * 3.14 / 180.0);

    //    float v3m = v3m.toFloat();
    //    float v3p = v3p.toFloat();
    float v3x = v3m * cos(v3p * 3.14 / 180.0);
    float v3y = v3m * sin(v3p * 3.14 / 180.0);

    //    float i1m = i1m.toFloat();
    //    float i1p = i1p.toFloat();
    float i1x = i1m * cos(i1p * 3.14 / 180.0);
    float i1y = i1m * sin(i1p * 3.14 / 180.0);

    //    float i2m = i2m.toFloat();
    //    float i2p = i2p.toFloat();
    float i2x = i2m * cos(i2p * 3.14 / 180.0);
    float i2y = i2m * sin(i2p * 3.14 / 180.0);

    //    float i3m = i3m.toFloat();
    //    float i3p = i3p.toFloat();
    float i3x = i3m * cos(i3p * 3.14 / 180.0);
    float i3y = i3m * sin(i3p * 3.14 / 180.0);

    Complex v1(v1x, v1y);
    Complex v2(v2x, v2y);
    Complex v3(v3x, v3y);
    Complex i1(i1x, i1y);
    Complex i2(i2x, i2y);
    Complex i3(i3x, i3y);

    Complex matrixB[ 3 ][ 1 ] = { { i1 }, { i2 } , { i3 } };

    float a_m = 1.0;
    float a_p = 120.0;
    float ax = a_m * cos(a_p * 3.14 / 180.0);
    float ay = a_m * sin(a_p * 3.14 / 180.0);

    Complex a(ax, ay);
    Complex a2 = a * a;
    Complex matrixA[ 3 ][ 3 ] = { { 1, 1, 1 }, { 1, a, a2 } , { 1, a2, a } };

    Complex d = 0;
    Complex Iseq[3][1];
    for (int i = 0; i < 3; i++) {
      for  (int j = 0; j < 3; j++) {
        d += matrixA[i][j] * matrixB[j][0];
      }
      Iseq[i][0] = (d / 3);
      d = 0;
    }
    Complex zero_seq_i = Iseq[0][0];
    Complex positive_seq_i = Iseq[1][0];
    Complex negative_seq_i = Iseq[2][0];

    float zero_seq_i_real = zero_seq_i.real();
    float zero_seq_i_img = zero_seq_i.imag();
    float positive_seq_i_real = positive_seq_i.real();
    float positive_seq_i_img = positive_seq_i.imag();
    float negative_seq_i_real = negative_seq_i.real();
    float negative_seq_i_img = negative_seq_i.imag();

    float zero_seq_i_mag = sqrt(zero_seq_i_real * zero_seq_i_real + zero_seq_i_img * zero_seq_i_img);
    float zero_seq_i_phase = (180.0 * atan(zero_seq_i_img / zero_seq_i_real) / 3.14);
    float positive_seq_i_mag = sqrt(positive_seq_i_real * positive_seq_i_real + positive_seq_i_img * positive_seq_i_img);
    float positive_seq_i_phase = (180.0 * atan(positive_seq_i_img / positive_seq_i_real) / 3.14);
    float negative_seq_i_mag = sqrt(negative_seq_i_real * negative_seq_i_real + negative_seq_i_img * negative_seq_i_img);
    float negative_seq_i_phase = (180.0 * atan(negative_seq_i_img / negative_seq_i_real) / 3.14);

    String fault_type;

    //******************************* Conditions for Line to Ground *************************************************
    if (((i1m == 0 && i2m == 0) || (i1m == 0 && i3m == 0) || (i2m == 0 && i3m == 0))) {
      if ((i1m == 0 && i2m == 0)) {
        Serial.println("This is Line to ground fault. The fault is in phase C");
        fault_type = "This is Line to ground fault. The fault is in phase C";
      }
      else if (i1m == 0 && i3m == 0) {
        Serial.println("This is Line to ground fault. The fault is in phase B");
        fault_type = "This is Line to ground fault. The fault is in phase B";
      }
      else if (i2m == 0 && i3m == 0) {
        Serial.println("This is Line to ground fault. The fault is in phase A");
        fault_type = "This is Line to ground fault. The fault is in phase A";
      }
    }

    //********************************* Conditions for Line to Line Fault ****************************************
    if (zero_seq_i_real == 0 && zero_seq_i_img == 0)
    {
      if (i1m == 0 && (i2m > 0 && i3m > 0) && (v1m > v2m && v1m > v3m))
      {
        Serial.println("This is Line to line Fault. The fault is in phase B & phase C");
        fault_type = "This is Line to line Fault. The fault is in phase B & phase C";
      }
      else if (i1m == 0 && (i2m > 0 && i3m > 0) && (v3m > v1m && v2m > v3m))
      {
        Serial.println("This is Line to line Fault. The fault is in phase A & phase C");
        fault_type = "This is Line to line Fault. The fault is in phase A & phase C";
      }
      else if (i1m == 0 && (i2m > 0 && i3m > 0) && (v3m > v1m && v3m > v2m))
      {
        Serial.println("This is Line to line Fault. The fault is in phase A & phase B");
        fault_type = "This is Line to line Fault. The fault is in phase A & phase B";
      }
    }

    //********************************************Condition to Line to Line To Ground ****************************************************
    if ((zero_seq_i_real != 0 && positive_seq_i_real != 0 && positive_seq_i_img != 0) && (i2m == 0 || i1m == 0 || i3m == 0 ) && ((v1m == 0 && v2m == 0 ) || (v1m == 0 && v3m == 0) || (v3m == 0 && v2m == 0)))
    {
      if (i2m == 0) {
        Serial.println("This is Line to line ground fault. The fault is in phases A & C");
        fault_type = "This is Double line ground fault. The fault is in phases A & C";
      }
      else if (i3m == 0) {
        Serial.println("This is Double ground fault. The fault is in phases B & A");
        fault_type = "This is Double ground fault. The fault is in phases B & A";
      }
      else if (i1m == 0) {
        Serial.println("This is Line to line ground fault. The fault is in phases B & C");
        fault_type = "This is Double ground fault. The fault is in phases B & C";
      }
    }

    //*********************************************Condition for threee phase fault **********************************************************
    if (zero_seq_i_real == 0 && negative_seq_i_real == 0 && v1m == 0 && v2m == 0 && v3m == 0 )
    {
      Serial.println ("This is three phase fault");
      fault_type = "This is three phase fault";
    }

    else {
      fault_type = "No Fault, You are safe!!!";
    }

    //    Serial.println("Voltage 1 Real: " + (String)v1x);
    //    Serial.println("Voltage 1 Imaginary: " + (String)v1y);
    //    Serial.println("Voltage 2 Real: " + (String)v2x);
    //    Serial.println("Voltage 2 Imaginary: " + (String)v2y);
    //    Serial.println("Voltage 3 Real: " + (String)v3x);
    //    Serial.println("Voltage 3 Imaginary: " + (String)v3y);
    //    Serial.println("Current 1 Real: " + (String)i1x);
    //    Serial.println("Current 1 Imaginary: " + (String)i1y);
    //    Serial.println("Current 2 Real: " + (String)i2x);
    //    Serial.println("Current 2 Imaginary: " + (String)i2y);
    //    Serial.println("Current 3 Real: " + (String)i3x);
    //    Serial.println("Current 3 Imaginary: " + (String)i3y);
    //    Serial.println("Result Matrix start");
    //    Serial.println(zero_seq_i);
    //    Serial.println(positive_seq_i);
    //    Serial.println(negative_seq_i);
    //    Serial.println("Result Matrix end");
    Serial.println("Fault types is: " + fault_type);


    // POST CODE
    if (Firebase.RTDB.setString(&fbdo, "output/fault_type", fault_type))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }

    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}
