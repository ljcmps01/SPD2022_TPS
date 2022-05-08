#define BOTON_RST 2 //Defino el pin de RESET
#define BOTON_START 3 //Defino el pin de START

#define FLED 4     //Defino el primer PIN  de los LED
#define MAXLEDS 13   //Defino la cantidad de LEDs conectados
  
#define INTERVALO 250  //El tiempo en milisegundos entre intervalos de millis
#define MAXVALUE 1023 //El valor maximo que puede tomar el contador

//Valores de estado de los botones
int botonRSTAntes = 0;            
int botonSTARTAntes = 0;                        

//Valores de la secuencia del contador
bool secuencia = 0;
int contador = 0;

unsigned long prevMillis = 0;


//Funcion que codifica el contador decimal a binario 
//y lo lleva a los led
//param cont: variable del contador
//param nLED: cantidad de leds conectados
//param iLED: pin del led inicial
void bin2LED(int cont);

void setup() {
  pinMode(BOTON_RST, INPUT);
  pinMode(BOTON_START, INPUT);
  
  Serial.begin(9600);
  
  for(int i = FLED;i <= MAXLEDS;i++){
    digitalWrite(i, LOW);
    pinMode(i, OUTPUT);
  }
}

void loop() {
  int botonRSTAhora = digitalRead(BOTON_RST);

  if(botonRSTAhora == 1 && botonRSTAntes == 0){
    //Si se presiona el boton:
    secuencia = 0;
    contador = 0;
    Serial.println("Toggle RST button");
    bin2LED(contador);
  }
  botonRSTAntes = botonRSTAhora;

  int botonSTARTAhora = digitalRead(BOTON_START);

  if(botonSTARTAhora == 1 && botonSTARTAntes == 0){
    //Si se presiona el boton:   
    secuencia =! secuencia;
    Serial.println("Toggle STR button");
    Serial.println(secuencia);
  }
  botonSTARTAntes = botonSTARTAhora;

  if(secuencia){    
    unsigned long millisAhora = millis();
    if(millisAhora - prevMillis >= INTERVALO){
  //    Serial.println(contador);
      prevMillis = millisAhora;
      
      if(contador < MAXVALUE){
        contador++;  
      }
      else{
        secuencia = 0; 
        contador = 0;
      }
      bin2LED(contador);
    }
  }
  delay(5);//Para TinkerCAD
}

void bin2LED(int cont){
  Serial.print("segundos: ");
  Serial.print(cont);
  Serial.print("| binario: ");
  
  for(int i = FLED;i <= MAXLEDS;i++){
    int resto = cont % 2;
    Serial.print(resto);
    digitalWrite(i, resto);
    cont = cont/2;
  }
  
  Serial.println("\n");
}
