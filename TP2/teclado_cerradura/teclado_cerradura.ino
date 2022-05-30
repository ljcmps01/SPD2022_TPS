/*
TODO:
  -Funcion imprimir menu principal
  -Cambiar Funcion compararContraseña
      --Deberia realizar el analisis completo e impresion en lcd del resultado
  -Sacar delays
  -Agregar doxygen de las funciones
  -Analizar necesidad de macro C_NULL
*/

#include <Keypad.h>
#include <LiquidCrystal.h>

#define FILAS 4
#define COLUMNAS 4
#define C_NULL '\0'
#define MAX_CARACTER 7
#define BOTONES A4


//***********************SETUP KEYPAD******************************

char teclado[FILAS][COLUMNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte columnasPins[COLUMNAS] = {3,2,1,0};
byte filasPins[FILAS] = {7,6,5,4};
Keypad keypad = Keypad( makeKeymap(teclado), filasPins, columnasPins, FILAS, COLUMNAS );

int cualBoton;

//***********************FIN SETUP KEYPAD******************************

//***********************SETUP LCD******************************
const int rs = 13, en = 8, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte lockOn[8]=
{
  B01110,
    B01010,
    B11111,
    B11111,
    B11011,
    B11011,
    B01110,
    B00000,
};

byte lockOff[8]=
{
  B01110,
    B01010,
    B01000,
    B11111,
    B11111,
    B11011,
    B11011,
    B01110,
};

//***********************FIN SETUP LCD******************************


char contra[MAX_CARACTER + 1]= "2C20210";
char contraIngresada[MAX_CARACTER + 1];
int cont = 0;
int comContra;


int comparacionContra(char contraI[], int tam, int cNull);
void initVector(char vec[], int tam);
void ingresoNuevaContra(char aContra[], int tam);
void asignarContra(char nueva[], char actual[], int tam);



void setup(){
  pinMode(BOTONES, INPUT);
  
  initVector(contraIngresada, MAX_CARACTER + 1);
  
  lcd.begin(16,2);
  lcd.createChar(7,lockOn);
  lcd.createChar(8,lockOff);  
  
  lcd.setCursor(0,0);
  lcd.print("Password ");
  lcd.write(7);
  // Serial.println(contraIngresada);
  delay(1000);
  lcd.setCursor(0,1);
  
}
  
void loop(){
  char tecla = keypad.getKey();

  if(tecla)
  {
    lcd.setCursor(0,1);
    contraIngresada[cont] = tecla;
    lcd.print(contraIngresada);
    cont++;
  }

  cualBoton = analogRead(BOTONES);
  

  //Ninguno-1023
  //1-767
  //2- 682
  //3- 512
  if(cualBoton<=1000)
  {
    // Serial.print("cualBoton: ");
    lcd.print(cualBoton);
    if(cualBoton>700)//Config
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Nueva contra: ");
      lcd.setCursor(0,1);
      // Serial.println(contra);
      ingresoNuevaContra(contra, MAX_CARACTER);
      
      
    }
    else
    {
      if(cualBoton>600)//Test Pass
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Test Pass: ");
      }
      else  //Reset
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Reset: ");
        initVector(contraIngresada,MAX_CARACTER);
      }
    }
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Password ");
    lcd.write(7);
    lcd.setCursor(0,1);
  }

  if(cont == MAX_CARACTER)
  {
    // Serial.println(contraIngresada);
    // Serial.println(cont);
    lcd.clear();
    comContra = comparacionContra(contraIngresada, MAX_CARACTER, C_NULL);
    lcd.setCursor(0,0);
    if(comContra)
    {
      
      lcd.print("Wrong Password!");
      lcd.write(7); 
    }
    else
    {
    
      lcd.print("Password OK!");
      lcd.write(8);
    }
    lcd.setCursor(0,1);
    cont = 0;
    initVector(contraIngresada, MAX_CARACTER + 1);
  }
  delay(5);
}

int comparacionContra(char contraI[], int tam, int cNull)
{
  int cmp = 0;

  for(int i = 0; i < tam && contraI[i] != cNull; i++)
  {
    if(contraI[i] != contra[i])
    {
      cmp = 1;
      break; 
    }
  }
  
  return cmp;
}


void initVector(char vec[], int tam)
{
  for(int i = 0; i < tam; i++)
  {
    vec[i] = '\0';
  }
}

void ingresoNuevaContra(char aContra[], int tam)
{
  char tecla = '\0';
  char nContra[tam + 1];

  initVector(nContra, tam + 1);

  for(int i = 0; i < tam; i++)
  {
    while(!tecla)
    {
      tecla = keypad.getKey();
    }  

    nContra[i] = tecla;
    lcd.print(tecla);
    tecla = '\0';
    // Serial.println(nContra);
  }

  asignarContra(nContra, aContra, tam);
}

void asignarContra(char nueva[], char actual[], int tam)
{
  initVector(actual, tam + 1);

  for(int i = 0; i < tam; i++)
  {
    actual[i] = nueva[i];
  }
}
