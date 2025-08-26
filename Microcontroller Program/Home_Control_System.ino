String serialMessage = ""; //The expected format is "DEVICENAME=COMMAND" with each following device name being separated by a space
boolean serialMessageArrived = false;

const int kitchenLightPin = 5; //Kitchen Light output
const int livingRoomLightPin = 6; //Living Room Light output
const int onboardLED = 13;

void setup(){
  Serial.begin(9600); //Serial communication at a rate of 9600 baud
  pinMode(kitchenLightPin, OUTPUT);
  pinMode(livingRoomLightPin, OUTPUT);
  pinMode(onboardLED, OUTPUT);
  digitalWrite(onboardLED, LOW); //Ensures the onboard LED remains off after each reset of the microcontroller
}

void loop(){
  if(serialMessageArrived){
    int currentIndex = 0; //Acts as a cusor for the serial message
    serialMessage.trim(); //Eliminates any new lines or formatting characters
    
    while(currentIndex < serialMessage.length()){
      int spaceIndex = serialMessage.indexOf(" ", currentIndex); //Obtains the index the space in respect to the current index, therefore moves space by space

      //The body will execute if the original serial message does not have a space, or we have reached to the final device and command pair in the serial message
      if(spaceIndex == -1){ //No space is present
        int equalSignIndex = serialMessage.indexOf("="); //Used to separate the device name and command name
        String device = serialMessage.substring(currentIndex, equalSignIndex); //Obtains the device name
        String command = serialMessage.substring(equalSignIndex + 1); //Obtains the command name

        currentIndex = serialMessage.length(); //No more parsing is required, thus ending this while loop
        evaluateSerialMessage(device, command);
      }
      else if(spaceIndex > 0){ //If there is a space present in a valid position
        String deviceCommandPair = serialMessage.substring(currentIndex, spaceIndex); //Obtains a string of format "DEVICENAME=COMMAND"

        int equalSignIndex = deviceCommandPair.indexOf("="); //Used to separate the device name and command name
        String device = deviceCommandPair.substring(0, equalSignIndex); //Obtains device name
        String command = deviceCommandPair.substring(equalSignIndex + 1); //Obtains command name

        currentIndex = spaceIndex + 1; //Move the cursor to the beginning of the next device name
        evaluateSerialMessage(device, command);
      }
      else{ //The space was in a invalid index
        Serial.println("INVALID SERIAL MESSAGE FORMAT");
      }
    }
    serialMessage = ""; //Clears the serial buffer
    serialMessageArrived = false; //Resets the boolean flag 
  }
}

void evaluateSerialMessage(String device, String command){ //To be expanded for other devices and their commands
  device.toUpperCase(); //Formatting for device
  command.toUpperCase(); //Formatting for command

  if(device.equals("KITCHENLIGHT")){ //Kitchen Light Device is selected
    if(command.equals("ON")){
      digitalWrite(kitchenLightPin, HIGH);
      Serial.println("The Kitchen Light is on.");
    }
    else if(command.equals("OFF")){
      digitalWrite(kitchenLightPin, LOW);
      Serial.println("The Kitchen Light is off.");
    }
    else{
      Serial.println("INVALID COMMAND"); //The serial message was of valid format, but the command selected is not an available command
    }
  }
  else if(device.equals("LIVINGROOMLIGHT")){ //Living Room Light Device is selected
    if(command.equals("ON")){
      digitalWrite(livingRoomLightPin, HIGH);
      Serial.println("The Living Room Light is on.");
    }
    else if(command.equals("OFF")){
      digitalWrite(livingRoomLightPin, LOW);
      Serial.println("The Living Room Light is off.");
    }
    else{
      Serial.println("INVALID COMMAND"); //The serial message was of valid format, but the command selected is not an available command
    }
  }
  else{
    Serial.println("UNKNOWN DEVICE"); //The serial message was of valid format, but the device selected is not designated to be controlled
  }
}

//This function is called automatically, and does not need to be called within the code
void serialEvent(){ //Reads serial data when there is a serial message available
  while(Serial.available()){ //Redundancy to ensure that reading occurs at proper times
    char currentSerialCharacter = (char)Serial.read(); 
    if (currentSerialCharacter == '\n'){ //'\n' refers to the EOL, or end-of-line indicator here
      serialMessageArrived = true;
    }
    else{
      serialMessage += currentSerialCharacter;
    }
  }
}
