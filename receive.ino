/*  
 ~~~~~~~
 uvr2web
 ~~~~~~~
 © Elias Kuiter 2013 (http://elias-kuiter.de)
 
 receive.ino:
 Empfangen und Speichern von Datenrahmen der Regelung
 Receive and save data frames by the heating control
 
 */

namespace Receive {

  void start() {
    Serial.print("\nStart in preparation");
    delay(2000);
    pulse_count = got_first = last_bit_change = 0;
    receiving = true;
    Serial.print("\nReceiving ... ");
    // on a CHANGE on the data pin pin_changed is called
    //CM -> https://www.reddit.com/r/esp8266/comments/c8lbjr/help_an_idiot_out_trouble_with_interrupts/
    //pinMode(interrupt, INPUT_PULLUP);
    //attachInterrupt(digitalPinToInterrupt(interrupt), pin_changed, CHANGE); //modified -> added digitalPinToInterrupt
    attachInterrupt(interrupt, pin_changed, CHANGE);
    Serial.print("\nInterrupt attached ... ");
  }

  void stop() {
    detachInterrupt(interrupt);
    Serial.print("\nReceived. ");
    receiving = false;
  }

  //CM -> https://www.reddit.com/r/esp8266/comments/c8lbjr/help_an_idiot_out_trouble_with_interrupts/
  void ICACHE_RAM_ATTR pin_changed() {
    byte val = digitalRead(dataPin); // Zustand einlesen // read state
    unsigned long time_diff = micros() - last_bit_change;
    last_bit_change = micros();
    // einfache Pulsweite? // singe pulse width?
    if (time_diff >= low_width && time_diff <= high_width) {
      process_bit(val);
      return;   
    }
    // doppelte Pulsweite? // double pulse width?
    if (time_diff >= double_low_width && time_diff <= double_high_width) {
      process_bit(!val);
      process_bit(val);
      return;   
    } 
  }

  void process_bit(byte b) {
    // den ersten Impuls ignorieren // ignore first pulse
    pulse_count++;
    if (pulse_count % 2)
      return;

    if (b)
      Process::data_bits[BIT_COUNT / 8] |= 1 << BIT_COUNT % 8; // Bit setzen // set bit
    else
      Process::data_bits[BIT_COUNT / 8] &= ~(1 << BIT_COUNT % 8); // Bit löschen // clear bit

    if (BIT_COUNT == Process::bit_number)
    // beende Übertragung, wenn Datenrahmen vollständig
      stop(); // stop receiving when data frame is complete
  }

}
