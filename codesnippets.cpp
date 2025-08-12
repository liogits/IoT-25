bool sent = false;
  int8_t i;

if (!sent) {
    for (i = 0; i < 3; i++) {
      artnet.setByte(i, 255);
    }
    artnet.write();
    sent = !sent;
    Serial.println("sent on");
    delay(50);
  }

  if (sent) {
    for (i = 0; i < 3; i++) {
      artnet.setByte(i, 0);
    }
    artnet.write();
    sent = !sent;
    Serial.println("sent off");
    delay(50);
  }


//
u_int8_t counter = 0;

void onNoteOn(byte channel, byte pitch, byte velocity) {
  counter = counter + 3;
  Serial.print("MIDI note on. Channel: ");
  Serial.println(channel);
  Serial.print("Pitch: ");
  Serial.println(pitch);

  if (counter > 18) {
    counter = 0;
  }
  float h = pitch * 2;
  RGB rgb = hue_to_rgb(h);
  artnetSendRGB(rgb, counter);
  Serial.println(counter);
}


void onNoteOff(byte channel, byte pitch, byte velocity) {
  Serial.print("MIDI note off. Channel: ");
  Serial.println(channel);
  Serial.print("Pitch: ");
  Serial.println(pitch);

  artnetClearRGB(counter);  
}





void artnetSetRGB(RGB rgb, u_int8_t start_channel, ArtnetWifi& artnet) {
  artnet.setByte(start_channel, rgb.r);
  artnet.setByte(start_channel + 1, rgb.g);
  artnet.setByte(start_channel + 2, rgb.b);
  if (LOG_RENDERER) Serial.print(".");
  //Serial.print("Channel: ");
  //Serial.print(start_channel);
  //Serial.print("  ");
}