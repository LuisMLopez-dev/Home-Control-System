const int kitchenLight = 5; //Kitchen Light Device
const int livingRoomLight = 6; //Living Room Light Device
const int onboardLED = 13;
String incomingSerialMessage = "";

void setup(){
  Serial.begin(9600); //9600 baud rate for serial communication

  pinMode(kitchenLight, OUTPUT);
  pinMode(livingRoomLight, OUTPUT);
  pinMode(onboardLED, OUTPUT);

  digitalWrite(onboardLED, LOW); //Ensures the onboard LED remains off after the microcontroller resets, and both the RX and TX lights go off
}

void loop(){ //Loops indefinitely
  while (Serial.available() > 0){ //As long as there are bytes in the serial buffer, or as long as there is something to be read in the serial buffer
    char currentSerialCharacter = Serial.read(); 

    if (currentSerialCharacter == '\n'){ //If the current character in the serial message is the end-of-line indicator
      incomingSerialMessage.trim(); //Removes any extra spaces or line breaks from the serial message
      int spaceIndex = incomingSerialMessage.indexOf(" "); 

      if (spaceIndex > 0){
        String device = incomingSerialMessage.substring(0, spaceIndex); //Obtains the name of the device from the serial message
        String command = incomingSerialMessage.substring(spaceIndex + 1); //Obtains the command from the serial message

        evaluateCommand(device, command);
      } 
      else{ //No space was present, or the space was at the beginning
        Serial.println("INVALID FORMAT");
      }
      incomingSerialMessage = ""; //Resets the incoming serial message 
    } 
    else{
      incomingSerialMessage += currentSerialCharacter; //The serial message is stored character by character per iteration of this function
    }
  }
}

void evaluateCommand(String device, String command){ //To be expanded for other devices
  device.toUpperCase(); //Formatting for device
  command.toUpperCase(); //Formatting for command

  if (device.equals("KITCHENLIGHT")){ //Kitchen Light Device is selected
    if (command.equals("ON")){
      digitalWrite(kitchenLight, HIGH);
      Serial.println("Kitchen Light is on.");
    } 
    else if (command.equals("OFF")){
      digitalWrite(kitchenLight, LOW);
      Serial.println("Kitchen Light is off.");
    } 
    else{
      Serial.println("INVALID COMMAND"); //The serial message was of valid format, but the command selected is not an available command
    }
  }
  else if(device.equals("LIVINGROOMLIGHT")){ //Living Room Light Device is selected
    if(command.equals("ON")){
      digitalWrite(livingRoomLight, HIGH);
      Serial.println("Living Room Light is on.");
    }
    else if(command.equals("OFF")){
      digitalWrite(livingRoomLight, LOW);
      Serial.println("Living Room Light is on.");
    }
    else{
      Serial.println("INVALID COMMAND"); //The serial message was of valid format, but the command selected is not an available command
    }
  }
  else{
    Serial.println("UNKNOWN DEVICE"); //The serial message was of valid format, but the device selected is not designated to be controlled
  }
}
