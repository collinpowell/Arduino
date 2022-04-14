// KEYPAD LIBS
#include <Keypad.h>

// I2C LCD LIBRARIES
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include <LiquidCrystal.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// RFID LIBS
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

// BUZZER PIN DECLARATION
const byte buzzer = A2;
const byte numOfItems = 5;
byte currentPage = 0;

// Declaring Item Data Type
struct Item
{
  String id;
  unsigned int itemPrice;
  String itemName;
};

struct Found {
  bool found;
  unsigned int id;
};

// Declaring and Initializing Items
Item items[numOfItems] = {
  {"3C 1A D8 37", 10000, "Rice 50kg"},
  {"23 B5 09 07", 5000, "Dressed Chicken"},
  {"C5 76 58 23", 2000, "Milk 50kg"},
  {"C5 93 69 23", 25000, "Hamper Pack"},
  {"C5 F2 F3 23", 1000, "Corn Flakes"}
};

Item cart[20];
int cartCounter = 0;

// KEYPAD SETUP
const byte ROWS = 5; // 5 rows
const byte COLS = 4; // 4 columns

char specialKeysID[] = {
  'A', 'B', '#', '*',
  '1', '2', '3', 'C',
  '4', '5', '6', 'D',
  '7', '8', '9', 'E',
  'F', '0', 'G', 'H'
};

char keys[ROWS][COLS] = {
  {specialKeysID[0], specialKeysID[1], specialKeysID[2], specialKeysID[3]},
  {specialKeysID[4], specialKeysID[5], specialKeysID[6], specialKeysID[7]},
  {specialKeysID[8], specialKeysID[9], specialKeysID[10], specialKeysID[11]},
  {specialKeysID[12], specialKeysID[13], specialKeysID[14], specialKeysID[15]},
  {specialKeysID[16], specialKeysID[17], specialKeysID[18], specialKeysID[19]}
};

byte rowPins[ROWS] = {2, 3, 4, 5, 6}; // connect to the row pinouts of the kpd
byte colPins[COLS] = {A1, A0, 8, 7};  // connect to the column pinouts of the kpd

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

unsigned long loopCount;
unsigned long startTime;
String msg;

const byte priceDigits = 15;
byte count = 0;
char *priceInput[priceDigits];

String inputString;
int inputInt;

void setup()
{
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  Serial.println("RFID");
  inputString.reserve(20);

  lcd.init();      // initialize the lcd
  lcd.backlight(); // Turns On BackLight

  lcd.setCursor(3, 0);
  lcd.print("SMART CART");
  delay(2000);

  SPI.begin(); // Initiate  SPI bus
  mfrc522.PCD_Init();

  initialLCD();
}

void initialLCD()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SET BUDGET:");

  lcd.setCursor(0, 1);
  lcd.blink();
  lcd.cursor();
}

void padBeep()
{
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void errorBeep()
{
  for (int i = 0; i < 4; i++) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
  }

}

void loop()
{
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  // just print the pressed key
  if (key)
  {
    Serial.println(key);

    if (key >= '0' && key <= '9')
    { // only act on numeric keys
      inputString += key;
      lcd.setCursor(0, 1);

      lcd.print(inputString); // append new character to input string
      padBeep();
    }
    else if (key == 'H')
    { // Enter Key
      if (inputString.length() > 0)
      {
        inputInt = inputString.toInt(); // YOU GOT AN INTEGER NUMBER
        printItemMessage();
        inputString = "";
        padBeep();
        while (1)
        {
          key = keypad.getKey();
          getRFID(true);
          if (key == 'E') {
            printItemDeleteMessage();
            while (1) {
              if (getRFID(false)) {
                printItemMessage();
                break;
              }
            }
          }else if (key == 'G'){
            if(currentPage <= cartCounter){
              displayCartItems(currentPage);
              currentPage++;
            }else{
              currentPage = 0;
            }

          }else if (key == 'F'){

          }
        }
      }
    }
    else if (key == 'E')
    { // ESC Key
      padBeep();
      inputString = "";
      initialLCD(); // clear input
    }
  }
}

void printItemMessage()
{
  lcd.clear(); // clear input
  lcd.setCursor(0, 0);
  lcd.print("BUDGET:" + String(inputInt));
  lcd.setCursor(0, 1);
  lcd.print(String(cartCounter) + " ITEM(s)");
  delay(500);
}

void printItemDeleteMessage()
{
  lcd.clear(); // clear input
  lcd.setCursor(0, 0);
  lcd.print("Scan to remove");
  lcd.setCursor(0, 1);
  lcd.print(String(getItemsCost(0)));

  delay(500);
}


bool getRFID(bool plus)
{
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  // Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  Found found = scanForItem(content.substring(1));
  if (found.found)
  {
    if (plus) {
      if (addItem(items[found.id])) {
        printItemMessage();
        delay(1500);
      }

    } else {
      if (removeItem(items[found.id])) {
        delay(1500);
        return true;
      }

    }

  } else {
    Serial.println(" Access denied");
  }

}

Found scanForItem(String content) {
  //content.substring(1)
  for (byte i = 0; i < numOfItems; i++)
  {
    if (content == items[i].id) // change here the UID of the card/cards that you want to give access
    {
      Found found = {true, i};
      return found;
    }
  }
  Found found = {false, 0};
  return found;
}

bool addItem(Item item)
{
  Serial.println(item.itemName);
  if (validateItem(item))
  {
    cart[cartCounter] = item;

    cartCounter++;
    return true;
  }
  else
  {
    Serial.println("Not Validated: " + item.itemName + " Price:" + String(item.itemPrice));
    printErrorMessage();
    return false;
  }
}

void printErrorMessage()
{
  lcd.clear(); // clear input
  lcd.setCursor(0, 0);
  lcd.print("Item Price");
  lcd.setCursor(0, 1);
  lcd.print("Exceeds Budget");
  errorBeep();
  delay(1500);
  lcd.clear();
  printItemMessage();
}

int getItemsCost(int costP) {
  int itemsCost = costP;
  if (cartCounter > 0)
  {
    for (int i = 0; i <= cartCounter; i++)
    {
      itemsCost += cart[i].itemPrice;
      Serial.println(String(i) + " in  " + String(cart[i].itemPrice));
    }
  }

  return itemsCost;
}
bool validateItem(Item item)
{
  int itemsCost = getItemsCost(item.itemPrice);
  Serial.println(String(itemsCost));

  if (itemsCost > inputInt)
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool removeItem(Item item) {
  for (int i = 0; i <= cartCounter; i++)
  {
    if (cart[i].id == item.id) {
      cartCounter--;
      for (int j = i; j <= cartCounter; j++) {
        cart[j] = cart[j + 1];
      }
      printItemDeleteMessage();
      Serial.println(item.itemName + " has been removed ");
      Serial.println(getItemsCost(0) + "new Cost");
      return true;
    }

  }
}

void displayCartItems(byte page) {
  lcd.clear(); // clear input
  lcd.setCursor(0, 0);
  lcd.print(cart[page].itemName);
  lcd.setCursor(0, 1);
  lcd.print(cart[page].itemPrice);
}
