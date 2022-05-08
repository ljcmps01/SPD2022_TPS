/* GRUPO=NULL
 *  INTEGRANTES:
 *    Obregon Alex 
 *    Campos Alejo
 */
/*
 *  Trabajo Práctico 1: Cronómetro Binario
 *
 *  Al iniciar la simulacion, todos los led deben comenzar apagados.
 *  Cada 1 segundo que transcurra, se deben encender los led
 *  de acuerdo al numero que representan.
 *
 *  Ejemplo:
 *   
 *  El numero 15 (0000001111) se representaria encendiendo los 
 *  leds AMARILLO y NARANJA.
 *  Al pasar al numero 16 (0000010000), se deben apagar todos 
 *  los led anteriores y encenderse uno de los leds VERDES. 
 *  Notese, en el ejemplo los 0 representan los led apagados 
 *  y los 1 los led encendidos). 
 *   
 *  -------------------------------------------------------
 *   
 *  Al presionarse el boton START, debe iniciar el cronometro.
 *  Volver a presionarlo hace que la secuencia se detenga. 
 *  (Como si se hubiese presionado pausa).
 *  Al presionarse el boton RESET, el cronometro
 *  debe reiniciarse y arrancar de 0.
 *
 *  Tip: Modularizar la función que controla el encendido de los 
 *  LEDS y de ser posible, todo el código para evitar repetir lineas lo mas posible.
 *  Usar millis para controlar el tiempo del contador para que el cambio de los 
 *  leds encendidos sea perceptible para el ojo humano y 
 *  documentar cada función creada en el código. 
 *  Un breve comentario que diga que es lo que hace esa función
 *  y de corresponder, que retorna).
*/

#define BOTON_RST 2 //Defino el pin de RESET
#define BOTON_START 3 //Defino el pin de START

#define PRIMER_LED 4     //Defino el primer PIN  de los LED
#define ULTIMO_LED 13   //Defino la cantidad de LEDs conectados
  
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
  
  for(int i = PRIMER_LED;i <= ULTIMO_LED;i++){
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
      prevMillis = millisAhora;

      //Si el contador no llego a MAXVALUE
      //incremento el contador
      if(contador < MAXVALUE){
        contador++;  
      }
      //Caso contrario Deshabilito la secuencia
      //Y reinicio el contador
      else{
        secuencia = 0; 
        contador = 0;
      }
      //Llamo a la funcion para codificar el contador
      //decimal a LEDs en binario
      bin2LED(contador);
    }
  }
  delay(5);//Para TinkerCAD
}

void bin2LED(int cont){
  Serial.print("segundos: ");
  Serial.print(cont);
  Serial.print("| binario: ");

  //Cada iteracion de este for determina el estado de un LED
  for(int i = PRIMER_LED;i <= ULTIMO_LED;i++){
    int resto = cont % 2;
    Serial.print(resto);
    digitalWrite(i, resto);
    cont = cont/2;
  }
  
  Serial.println("\n");
}
