// made with luv 💙 by Kittyawn
#define _shift_pin    12
#define _dt_pin       11
#define _en_pin       10

byte ledValue[32] = {0};  // safety agar semua saat awal running LED nya mati semua
byte pinOutput[3] = {_shift_pin, _dt_pin, _en_pin};

byte digits[10][8] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0: ABCDEF-
  {0, 1, 1, 0, 0, 0, 0}, // 1: -BC----
  {1, 1, 0, 1, 1, 0, 1}, // 2: AB-DEG-
  {1, 1, 1, 1, 0, 0, 1}, // 3: ABCD--G
  {0, 1, 1, 0, 0, 1, 1}, // 4: -BC-FG-
  {1, 0, 1, 1, 0, 1, 1}, // 5: A-CD-FG
  {1, 0, 1, 1, 1, 1, 1}, // 6: A-CDEFG
  {1, 1, 1, 0, 0, 0, 0}, // 7: ABC----
  {1, 1, 1, 1, 1, 1, 1}, // 8: ABCDEFG
  {1, 1, 1, 1, 0, 1, 1}  // 9: ABCD-FG
};

void setup() {
  for(byte i = 0; i < 3; i++) {
    pinMode(pinOutput[i], OUTPUT);
    digitalWrite(pinOutput[i], LOW);
  }

  // Run Starter Anim
  starter();
}

void loop() {
  number1();
  number2();
  number3();

  // stop biar ga loop boss
  while (true);
}

void starter() {
  // starter anim disini
  for (byte i = 0; i < 8; i++) {
    for (byte j = 0; j < 4; j++) {
      // Reset ledValue
      for (byte k = 0; k < 32; k++) {
        ledValue[k] = 0;
      }
      ledValue[i + (j * 8)] = 1; // Nyalakan satu segmen dari IC ke j

      // show anim nya
      shiftData();
      delay(50);
    }
  }

  // reset led value biar aman lagi
  for (byte k = 0; k < 32; k++) {
    ledValue[k] = 0;
  }
  shiftData();
}

void number1() {
  // show angka 0 sampai 9 di IC ke-4
  for (byte num = 0; num < 10; num++) {
    // reset ledValue
    for (byte i = 0; i < 32; i++) {
      ledValue[i] = 0;
    }
    // Assign nilai digit ke IC ke-4
    for (byte i = 0; i < 8; i++) {
      ledValue[i + 24] = digits[num][i]; // IC ke-4
    }

    // show digit yg sesuai
    shiftData();
    delay(500);
  }
}

void number2() {
  // tampilin angka absen kuh boss (16)
  for (byte i = 0; i < 32; i++) {
    ledValue[i] = 0; // reset semua
  }
  // 1 di IC ke-3
  for (byte i = 0; i < 8; i++) {
    ledValue[i + 16] = digits[1][i]; // IC ke-3
  }
  // 6 di IC ke-4
  for (byte i = 0; i < 8; i++) {
    ledValue[i + 24] = digits[6][i]; // IC ke-4
  }
  shiftData();
  delay(5000);
}

void number3() {
  // tampilin angka tahun 2024
  for (byte i = 0; i < 32; i++) {
    ledValue[i] = 0; // Reset semua
  }
  // angka 2 di IC ke-1
  for (byte i = 0; i < 8; i++) {
    ledValue[i] = digits[2][i]; // IC ke-1
  }
  // angka0 di IC ke-2
  for (byte i = 0; i < 8; i++) {
    ledValue[i + 8] = digits[0][i]; // IC ke-2
  }
  // angka 2 di IC ke-3
  for (byte i = 0; i < 8; i++) {
    ledValue[i + 16] = digits[2][i]; // IC ke-3
  }
  // angka 4 di IC ke-4
  for (byte i = 0; i < 8; i++) {
    ledValue[i + 24] = digits[4][i]; // IC ke-4
  }
  shiftData();
  delay(5000);
}

void shiftData(){
  for(byte i = 0; i < 32; i++) {
    // send data shift di pin dt (DS) pada IC ShiftRegister 74HC696
    digitalWrite(_dt_pin, !ledValue[31-i]);

    // geser data dgn send clock pada kaki shift (SH_CP)
    digitalWrite(_shift_pin, HIGH);
    delayMicroseconds(40);
    digitalWrite(_shift_pin, LOW);
    delayMicroseconds(40);
  }

  digitalWrite(_en_pin, HIGH);
  delayMicroseconds(40);
  digitalWrite(_en_pin, LOW);
  delayMicroseconds(40);
}
