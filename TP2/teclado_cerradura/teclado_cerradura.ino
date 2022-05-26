#include <Keypad.h>

#define FILAS 4
#define COLUMNAS 4
#define C_NULL '\0'
#define MAX_CARACTER 7
#define BOTONES A4

char teclado[FILAS][COLUMNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte filasPins[FILAS] = {2, 3, 4, 5};
byte columnasPins[COLUMNAS] = {6, 7, 8, 9};

char contra[MAX_CARACTER + 1]= "2C2021";
char contraIngresada[MAX_CARACTER + 1];
int cont = 0;
int comContra;

int comparacionContra(char contraI[], int tam, int cNull);
void initVector(char vec[], int tam);
void asignarContra(char nueva[], char actual[], int tam);

Keypad keypad = Keypad( makeKeymap(teclado), filasPins, columnasPins, FILAS, COLUMNAS );

void setup(){
  pinMode(BOTONES, INPUT);
  
  initVector(contraIngresada, MAX_CARACTER + 1);
  
  Serial.begin(9600);
  Serial.println(contra);
  Serial.println(contraIngresada);
}
  
void loop(){
  char tecla = keypad.getKey();

  if(tecla)
  {
    contraIngresada[cont] = tecla;
    Serial.println(contraIngresada);
    cont++;
  }
  

  if(cont == MAX_CARACTER)
  {
    Serial.println(contraIngresada);
    Serial.println(cont);
    comContra = comparacionContra(contraIngresada, MAX_CARACTER, C_NULL);
    Serial.println(comContra);
    cont = 0;
    initVector(contraIngresada, MAX_CARACTER + 1);
  }
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

void asignarContra(char nueva[], char actual[], int tam)
{
  
}
