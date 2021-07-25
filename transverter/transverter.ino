/*!
   ADF4351 transverter program
   Arduino Pro / Pro mini
   ATMega 328P / 3.3V 8MHz
*/

#include <Arduino.h>
#include "adf4351.h"

#define SWVERSION "1.0"

#define PIN_SS 10  ///< SPI slave select pin, default value

ADF4351  vfo(PIN_SS, SPI_MODE0, 1000000UL , MSBFIRST) ;



void setup()
{
  Serial.begin(9600) ;
  Serial.print("ADF4351 programmer v") ;
  Serial.println(SWVERSION) ;
  Serial.println("https://github.com/tczerwonka/adf4351-1") ;
  Wire.begin() ;
  /*!
     setup the chip (for a 10 mhz ref freq)
     most of these are defaults
  */
  vfo.pwrlevel = 0 ; ///< sets to -4 dBm output
  vfo.RD2refdouble = 0 ; ///< ref doubler off
  vfo.RD1Rdiv2 = 0 ;   ///< ref divider off
  vfo.ClkDiv = 150 ;
  vfo.BandSelClock = 80 ;
  vfo.RCounter = 1 ;  ///< R counter to 1 (no division)
  vfo.ChanStep = steps[2] ;  ///< set to 10 kHz steps

  /*!
     sets the reference frequency to 10 Mhz
  */
  //if ( vfo.setrf(10000000UL) ==  0 )
  if ( vfo.setrf(9999697UL) ==  0 )

    Serial.println("ref freq set to 10 Mhz") ;
    else
      Serial.println("ref freq set error") ;
      /*!
         initialize the chip
      */
      vfo.init() ;

  /*!
     enable frequency output
  */
  vfo.enable() ;

  /*
     just set to 194MHz for use as 222 transverter LO
  */
  delay(5000);
  Serial.println("setf() to 194 MHz") ;

  if ( vfo.setf(194000000UL) == 0 ) {
    Serial.print("setf() success freq:") ;
    Serial.println(vfo.cfreq) ;
  } else {
    Serial.println("setf() error") ;
  }
}



void loop()
{
}
