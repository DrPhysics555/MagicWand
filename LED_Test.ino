bool lightSwitchState = HIGH;  //represnts the original boolean state for the lightswitch.  High in this case is off
bool lastButtonState = HIGH; //Last state of the button (pushed = LOW)
bool debounced = LOW;  //Check to see if we are still in boncing mode  LOW means we are not bouncing

const int LEDPin = 8;  //Where the LED on the wand is plugged into the arduino
const int buttonPin = 2;  // Where our button is plugged into the Arduino

unsigned long lastButtonActivation = 0;  //Keeps track of the time of the last button press
unsigned long debounceDelay = 250;  //How long before we will recognize another button push
//This delay stops our pressing of a button to be seen as multiple presses

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //begin the serial connection at 9600 baud
  pinMode(LEDPin, OUTPUT);  //activate the LED pin in output mode
  pinMode(buttonPin, INPUT_PULLUP); //activate the button pin as an input.
  //INPUT_PULLUP allows us to activate the pin and make it default to HIGH
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonPress = digitalRead(buttonPin);  //Check to see what the value of the button pin is

  if (buttonPress != lastButtonState && debounced == LOW) //if the button has changed state (off to on or on to off and we are looking for input
  {
    lastButtonActivation=millis();  //get the time of when the button is being pushed
    debounced = HIGH; //With debounced set to HIGH we are now going to wait till the button is released
  }
  if((millis()-lastButtonActivation) > debounceDelay) //compare the current time minus the time when the button was originally pressed.
                                                      //if the value is larger than the delay we set, then this is a new button press
  {
    if (buttonPress==LOW) //verify that the button is really pressed
    {
      lightSwitchState = !lightSwitchState;  //Change the state of the LED (on to off or off to on)
      digitalWrite(LEDPin, lightSwitchState); //Send the command to change the switch
      debounced = LOW; //We can now look for another button press
    }
  }
}
