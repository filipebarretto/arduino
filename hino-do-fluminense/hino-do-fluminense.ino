
// LEDs
int ledDo = 3;
int ledRe = 4;
int ledMi = 5;
int ledFa = 6;
int ledSol = 7;
int ledLa = 8;
int ledSi = 9;


// TONES 
int DO = 3830;    // 261 Hz 
int re = 3400;    // 294 Hz 
int mi = 3038;    // 649 Hz 
int fa = 2864;    // 349 Hz 
int sol = 2550;   // 392 Hz 
int la = 2272;    // 440 Hz 
int si = 2028;    // 493 Hz 

int DOx = 3610;    // 277 Hz 
int rex = 3215;    // 311 Hz 
int mix = fa;      // 349 Hz 
int fax = 2702;    // 370 Hz 
int solx = 2409;   // 415 Hz 
int lax = 2156;    // 466 Hz 
int six = 1912;    // 523 Hz

int si3 = 4048;    // 247 Hz
int DO5 = six;     // 523 Hz
int re5 = 1703;    // 587 Hz
int mi5 = 1517;    // 659 Hz
int DO5x = 1805;   // 554 Hz


int w = 512;
int h = 256;
int q = 128;
int e = 64;
int s = 32;



// Define a special note, 'R', to represent a rest
int R = 0;

// SETUP
int speakerOut = 12;
int DEBUG = 1;

void setup() { 
  pinMode(ledDo, OUTPUT);
  pinMode(ledRe, OUTPUT);
  pinMode(ledMi, OUTPUT);
  pinMode(ledFa, OUTPUT);
  pinMode(ledSol, OUTPUT);
  pinMode(ledLa, OUTPUT);
  pinMode(ledSi, OUTPUT);
  
  
  pinMode(speakerOut, OUTPUT);
  if (DEBUG) { 
    Serial.begin(9600); // Set serial out if we want debugging
  } 
}

// MELODY and TIMING
int melody[] = {mi, DO5, mi, 
                rex, fax, la, DO5, si, 
                R, DO5, si, DO5, si, la, solx, 
                si, la, DO5, la, mi, la,
                lax, la, solx, la, lax, la, mi, la, 
                sol, fa, fa, mi, sol, fa, mi, re,
                DO, mi, mi, rex, fax, si, la,
                la, solx, si,
              
                mi, DO5, mi, 
                rex, fax, la, DO5, si, 
                R, DO5, si, DO5, si, la, solx, 
                si, la, DO5, la, mi, la,
                lax, la, solx, la, lax, la, mi, la, 
                sol, fa, fa, mi, sol, fa, mi, re,
                DO, mi, DO5, si, mi, solx, mi,
                la,
                
                sol, re, si3, re, sol, sol, sol,
                la, mi, DO, mi, sol, sol,
                R, mi, rex, mi, solx, la, si,
                mi5, DO5x, 
                mi5, re5, DO5, si, lax, si,
                
                re5, DO5, si, la, solx, la,
                fax, fax, solx, la, si, DO5,
                la,
              
                R, R};


int beats[] = {q, e, e, 
               s, s, s, s, q, e,
               s, s, s, s, s, s, 
               s, s, s, s, e+s, s,
               s, s, s, s, s, s, s, s, 
               s, s, s, s, s, s, s, s, 
               s, e, s, s, s, s, s,
               s, s, q+e,

               q, e, e, 
               s, s, s, s, q, e,
               s, s, s, s, s, s, 
               s, s, s, s, e+s, s,
               s, s, s, s, s, s, s, s, 
               s, s, s, s, s, s, s, s,
               s, e, s, s, s, s, s,
               h,
               
               s, s, s, s, s, e, s,
               s, s, s, s, s, s+e,
               s, s, s, s, e, e, e,
               q, q,
               e, e, e, e, e, e,
               
               e, e, e, e, e, e,
               s, s, s, s, e, e,
               h,
             
               w, w};


int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { 
       if (tone_ == DO || tone_ == DOx || tone_ == DO5x)
      {
        digitalWrite(ledDo, HIGH);
      }
      if (tone_ == re || tone_ == rex || tone_ == re5) 
      {
        digitalWrite(ledRe, HIGH); 
      }
      if (tone_ == mi || tone_ == mi5) 
      {
        digitalWrite(ledMi, HIGH);
      }
      if (tone_ == fa || tone_ == fax)
      {
        digitalWrite(ledFa, HIGH); 
      }
      if (tone_ == sol || tone_ == solx)
      {
        digitalWrite(ledSol, HIGH); 
      }
      if (tone_ == la || tone_ == lax) 
      {
        digitalWrite(ledLa, HIGH); 
      }
      if (tone_ == si || tone_ == six || tone_ == si3)
      {
        digitalWrite(ledSi, HIGH); 
      }
      
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);      
      delayMicroseconds(tone_ / 2);
   
    
      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
    digitalWrite(ledDo, LOW); 
    digitalWrite(ledRe, LOW); 
    digitalWrite(ledMi, LOW); 
    digitalWrite(ledFa, LOW); 
    digitalWrite(ledSol, LOW); 
    digitalWrite(ledLa, LOW); 
    digitalWrite(ledSi, LOW); 


  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}

void loop() {
  for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone(); 
    
    delayMicroseconds(pause);

    if (DEBUG) { 
      Serial.print(i);
      Serial.print(":");
      Serial.print(beat);
      Serial.print(" ");    
      Serial.print(tone_);
      Serial.print(" ");
      Serial.println(duration);
    }
  }
}

