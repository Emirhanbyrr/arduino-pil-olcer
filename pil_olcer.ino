#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define pil A1

const int MIN_ADC = 240;   // ~1.17V
const int MAX_ADC = 350;   // ~1.71V

int okuADC() {
  long t = 0;
  for (int i=0; i<20; i++) {
    t += analogRead(pil);
    delay(2);
  }
  return t / 20;
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("PIL OLCER");
}

void loop() {
  int adc = okuADC();

  // PIL YOK
  if (adc < 100) {
    lcd.setCursor(0,1);
    lcd.print("Pil yok       ");
    delay(500);
    return;
  }

  adc = constrain(adc, MIN_ADC, MAX_ADC);
  int yuzde = map(adc, MIN_ADC, MAX_ADC, 0, 100);
  yuzde = constrain(yuzde, 0, 100);

  lcd.setCursor(0,1);
  lcd.print("Doluluk: %   ");
  lcd.setCursor(10,1);
  lcd.print(yuzde);

  delay(500);
}
