// Pins for addresses A0, A1, A2, ..., A14
const char ADDR_PINS[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};

// Pins for I/O0, I/O1, I/O2, ..., I/O7
const char DATA_PINS[] = {23, 25, 27, 29, 31, 33, 35, 37};

// Pins for !WE, !OE and !CS
const char WE_PIN = 2;
const char OE_PIN = 3;
const char CS_PIN = 4;

// Amount of microseconds to wait in case the memory is slower than the arduino.
const char OP_WAIT = 0;

// Testing a 32KB memory
const unsigned int MEMORY_SIZE = 32768; //1024 bytes * 32;

// Byte to be writen, read and compared
const unsigned char TESTING_BYTE = 0xfa;


void setup() {
  // Configure all address pins to output
  for(int n = 0; n < 16; n += 1) {
    pinMode(ADDR_PINS[n], OUTPUT);
  }

  // Configure all control pins to output
  pinMode(WE_PIN, OUTPUT);
  pinMode(OE_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);

  // Configure Write Enable, Output Enable and Chip Select to HIGHT.
  resetControlPins();  
  
  Serial.begin(57600);
  
  // Start testing
  test();
}

// Write a byte into memory at the address specified
void writeByte(unsigned char byte, unsigned int address) {
  // Configure all data pins to output
  for(int n = 0; n < 8; n += 1) {
    pinMode(DATA_PINS[n], OUTPUT);
  }
  
  setAddress(address);

  // Set CS to low, in order to select the chip
  digitalWrite(CS_PIN, LOW);
  
  delayMicroseconds(OP_WAIT); // wait 

  // Set the data pins with the byte
  for(int b = 0; b < 8; b++) {
    if(byte & 1<<(b)) {    
      digitalWrite(DATA_PINS[b], HIGH);
    } else {
      digitalWrite(DATA_PINS[b], LOW);
    }
  }  

  // Set WE to low, in order to write the data
  digitalWrite(WE_PIN, LOW);
  delayMicroseconds(OP_WAIT); // wait 

  resetControlPins();
}

// Read a byte from memory at the address specified
unsigned char readByte(unsigned int address) {
  // Configure all data pins to input
  for(int n = 0; n < 8; n += 1) {
    pinMode(DATA_PINS[n], INPUT);
  }

  setAddress(address);
  
  // Set CS to low, in order to select the chip
  digitalWrite(CS_PIN, LOW);
  // Set OE to low, in order to read the data
  digitalWrite(OE_PIN, LOW);

  delayMicroseconds(OP_WAIT); // wait 

  unsigned char byte = 0;
  
  // Read the data pins
  for(int b = 0; b < 8; b++) {
    if(digitalRead(DATA_PINS[b])) {
      byte = byte | 1<<(b);  
    }
  }

  resetControlPins();

  return byte;
}

// Set the address pins to represent the address passed
void setAddress(unsigned int address) {
  for(int b = 0; b < 16; b++) {
    if(address & 1<<(b)) {    
      digitalWrite(ADDR_PINS[b], HIGH);
    } else {
      digitalWrite(ADDR_PINS[b], LOW);
    }
  }  
}

// Configure Write Enable, Output Enable and Chip Select to HIGHT.
void resetControlPins() {
  digitalWrite(WE_PIN, HIGH);
  digitalWrite(OE_PIN, HIGH);
  digitalWrite(CS_PIN, HIGH);
}

void test() {
  Serial.println("Testing...");

  char output[100];
  for(unsigned int address = 0; address < MEMORY_SIZE; address++) {
    writeByte(TESTING_BYTE, address);
    delayMicroseconds(OP_WAIT); // wait 
    unsigned char byte = readByte(address);
    
    if(TESTING_BYTE != byte) {
      sprintf(output, "Error at address: %04X - written: %02X read: %02X", address, TESTING_BYTE, byte);
      Serial.println(output);
    }
    delayMicroseconds(OP_WAIT); // wait 

    if(address%1024==0) {
      Serial.print((address/1024)+1);
      Serial.print(" KB");
    }
  }
  
  Serial.println("End of test. Your 62256 is good if no errors have been reported");
}

void loop() {
}
