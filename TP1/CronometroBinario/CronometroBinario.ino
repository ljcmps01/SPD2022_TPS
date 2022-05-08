#define BTN_RST 2 //Defino el pin de RESET
#define BTN_STR 3 //Defino el pin de START

#define FLED 4     //Defino el primer PIN  de los LED
#define NLEDS 10   //Defino la cantidad de LEDs conectados

#define INTERVALO 250  //El tiempo en milisegundos entre intervalos de millis
#define MAXVALUE 1023 //El valor maximo que puede tomar el contador

//Valores de estado de los botones
int botonRSTAntes=0;
int botonSTRAntes=0;

//Valores de la secuencia del contador
bool secuencia=0;
int contador=0;

unsigned long prevMillis=0;


//Funcion que codifica el contador decimal a binario 
//y lo lleva a los led
//param cont: variable del contador
//param nLED: cantidad de leds conectados
//param iLED: pin del led inicial
void bin2LED(int cont, int nLED, int iLED);

void setup() {
  pinMode(BTN_RST, INPUT);
  pinMode(BTN_STR, INPUT);
  Serial.begin(9600);
  for(int i=0;i<NLEDS;i++){
    digitalWrite(FLED+i, LOW);
    pinMode(FLED+i,OUTPUT);
  }
}

void loop() {
  int botonRSTAhora=digitalRead(BTN_RST);

  if(botonRSTAhora==1&&botonRSTAntes==0){
    //Si se presiona el boton:
    secuencia=0;
    contador=0;
    Serial.println("Toggle RST button");
    bin2LED(contador,NLEDS,FLED);
  }
  botonRSTAntes=botonRSTAhora;

  int botonSTRAhora=digitalRead(BTN_STR);

  if(botonSTRAhora==1&&botonSTRAntes==0){
    //Si se presiona el boton:   
    secuencia=!secuencia;
    Serial.println("Toggle STR button");
    Serial.println(secuencia);
  }
  botonSTRAntes=botonSTRAhora;

  if(secuencia){    
    unsigned long millisAhora=millis();
    if(millisAhora-prevMillis>=INTERVALO){
  //    Serial.println(contador);
      prevMillis=millisAhora;
      
      if(contador<MAXVALUE){
        contador++;  
      }
      else{
        secuencia=0; 
        contador=0;
      }
      bin2LED(contador,NLEDS,FLED);
    }
  }
  delay(5);//Para TinkerCAD
}

void bin2LED(int cont, int nLED, int iLED){
  Serial.print("segundos: ");
  Serial.print(cont);
  Serial.print("| binario: ");
  for(int i=0;i<nLED;i++){
    int resto=cont%2;
    Serial.print(resto);
    digitalWrite(i+iLED,resto);
    cont=cont/2;
  }
  Serial.println("\n");
}
