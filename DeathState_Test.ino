// Bulb Pop - QUICK! 
// Into slow global dimming filament
// Flickering Filament Constant
// Dead faces or low smoldering faces

#define BLACKOUT makeColorHSB(0,0,0)

Timer popTimer;
#define POP_DURATION 800

Timer surgeTimer;
#define SURGE_DURATION 400

Timer shimmerTimer;
#define SHIMMER_DURATION 100

bool hasPopped = false;

Timer nextFlash; 

#define HEARTBEAT makeColorHSB(40, 230,200)
#define PULSE_LENGTH 6000

void setup() 
{
  setColor(HEARTBEAT);
  
  // Set the timer to not expire at the beginning. 
  popTimer.never();
  surgeTimer.never();
  shimmerTimer.never();
}

void loop() 
{
    if(buttonSingleClicked())
    {
      // START THE POP TIMER!
      popTimer.set(POP_DURATION);
  
      // START POP ANIMATION - these should chain together between each other - I don't expect them to be called here sequentually.
      
      // 1. PopSurge - Increase the intensity really quickly 
      PopSurge();
    }

    // 2. PopShimmer - Shimmer VERY quickly 
    if(surgeTimer.isExpired())
    {
      PopShimmer();
    }
    
    if(popTimer.isExpired())
    {
      DeadLoop();
    }
}

void DeadLoop()
{ 
     Smoulder();
     Flicker();
}

// THIS DOESN'T RAMP UP - IT NEEDS TO SURGE UP BRIGHTNESS ON A CURVE 
void PopSurge()
{
   setColor(BLACKOUT);

   surgeTimer.set(SURGE_DURATION);

   if(!surgeTimer.isExpired())
   {
    int surgeProgress = millis() % SURGE_DURATION;
    
    byte surgeMapped = map(surgeProgress, 0, SURGE_DURATION, 0, 255);
    
    byte brightness = sin8_C(surgeMapped);
    
    setColor(makeColorHSB(40,255,brightness));
   }
}

// NEEDS TO REALLY SHIMMER FAST
void PopShimmer()
{
      Timer nextFlash;

      if(nextFlash.isExpired()) 
      {
      setColor(WHITE);      
      nextFlash.set(40);   // Flash again in 200 millseconds    
      } 
      else 
      {
      setColor(OFF);  
      }
}

void Smoulder()
{
  FOREACH_FACE(f) 
    {  
      // OFF  
      //setColorOnFace(makeColorHSB(0,0,0),f);

      // Smoulder RED
       setColorOnFace(makeColorHSB(0, 255, random(40)), f);

       // DIM RED
       // setColorOnFace(makeColorHSB(0, 255, 30), f);

       // SLOW RED PULSE
       /* 
          int pulseProgress = millis() % PULSE_LENGTH;
          byte pulseMapped = map(pulseProgress, 0, PULSE_LENGTH, 0, 255);
          byte dimness = sin8_C(pulseMapped);
          setColor(dim(makeColorHSB(0, 255, 40), dimness));
       */
    }
}

void Flicker()
{
  setColorOnFace(makeColorHSB(30 , 255, 255 - 6 - random(55)), 0);
}
