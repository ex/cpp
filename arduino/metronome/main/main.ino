
const int POTENCIOMETER_PIN = 6;
const int BUTTON_RESET_PIN = 2;
const int BUTTON_MODE_PIN = 3;

const int LED_1R = 9;
const int LED_1G = 8;
const int LED_2B = 10;
const int LED_3B = 11;
const int LED_4B = 12;

unsigned long lastTime;
unsigned long time;

int sensor = 0; // variable to store the value coming from the sensor
int millisecondsToWait = 0;
int millisecondsElapsed  = 0;
int state = 0;
bool blink = false; // used to blink built-in led
int tempo = 4;
bool lockMode = false; 
int lastLedOn = 0;

// The setup function runs once when you press reset or power the board
void setup()
{
  pinMode( POTENCIOMETER_PIN, INPUT);
  pinMode( BUTTON_RESET_PIN, INPUT);  
  pinMode( BUTTON_MODE_PIN, INPUT);  
  
  pinMode( LED_BUILTIN, OUTPUT );
  
  pinMode( LED_1R, OUTPUT );  
  pinMode( LED_1G, OUTPUT );  
  pinMode( LED_2B, OUTPUT );  
  pinMode( LED_3B, OUTPUT );  
  pinMode( LED_4B, OUTPUT );  

  lastTime = millis();
  onStateChange();
}

// The loop function runs over and over again forever
void loop()
{
  sensor = digitalRead( BUTTON_RESET_PIN );
  if ( state < 10 && sensor == HIGH )
  {
    state = 10;
    onStateChange();    
    millisecondsElapsed = 0;            
  }
  if ( state == 10 && sensor == LOW )
  {
    state = 11;
    onStateChange();    
    millisecondsElapsed = 0;            
  }

  sensor = digitalRead( BUTTON_MODE_PIN );
  if ( sensor == LOW )
  {
    lockMode = false;
  }
  if ( !lockMode && tempo == 4 && sensor == HIGH )
  {
    tempo = 2;
    lockMode = true;    
  }
  if ( !lockMode && tempo == 2 && sensor == HIGH )
  {
    tempo = 3;
    lockMode = true;        
  }
  if ( !lockMode && tempo == 3 && sensor == HIGH )
  {
    tempo = 4;
    lockMode = true;        
  }

  time = millis();
  update( time - lastTime );
  lastTime = time;
}

void update( int dt )
{
  sensor = analogRead( POTENCIOMETER_PIN );
  millisecondsToWait = 50 + sensor;

  if ( millisecondsElapsed >= millisecondsToWait )
  {
    onStateChange();
    millisecondsElapsed = 0;        
  }
  else
  {
    millisecondsElapsed += dt;    
  }
}

void onStateChange()
{
  digitalWrite( LED_BUILTIN, blink? LOW : HIGH );  
  blink = !blink;

  switch ( state )
  {
    case 0:
      digitalWrite( lastLedOn, LOW );        
      digitalWrite( LED_1G, HIGH );
      lastLedOn = LED_1G;
      state++;
      break;
    case 1:
      digitalWrite( lastLedOn, LOW );        
      digitalWrite( LED_2B, HIGH );    
      lastLedOn = LED_2B;      
      state = ( tempo == 2 ) ? 0 : state + 1;
      break;
    case 2:
      digitalWrite( lastLedOn, LOW );        
      digitalWrite( LED_3B, HIGH );
      lastLedOn = LED_3B;      
      state = ( tempo == 3 ) ? 0 : state + 1;
      break;
    case 3:
      digitalWrite( lastLedOn, LOW );        
      digitalWrite( LED_4B, HIGH );    
      lastLedOn = LED_4B;      
      state = 0;      
      break;

    case 10:
      digitalWrite( lastLedOn, LOW );            
      state = 11;      
      break;
    case 11:
      digitalWrite( LED_1R, HIGH );    
      state = 12;      
      break;
    case 12:
      digitalWrite( LED_1R, LOW );    
      state = 13;      
      break;
    case 13:
      digitalWrite( LED_1R, HIGH );    
      state = 14;      
      break;
    case 14:
      digitalWrite( LED_1R, LOW );    
      state = 15;      
      break;
    case 15:
      digitalWrite( LED_1R, HIGH );    
      state = 16;      
      break;
    case 16:
      digitalWrite( LED_1R, LOW );    
      state = 0;      
      break;
  }
}

