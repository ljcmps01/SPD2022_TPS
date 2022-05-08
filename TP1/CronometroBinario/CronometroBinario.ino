#define BTN_RST A1
#define BTN_STR A0

int botonRSTAntes=0;
int botonSTRAntes=0;

void setup() {
  pinMode(BTN_RST, INPUT);
  pinMode(BTN_STR, INPUT);
  Serial.begin(9600);
}

void loop() {
  int botonRSTAhora=digitalRead(BTN_RST);

  if(botonRSTAhora==1&&botonRSTAntes==0){
    //Si se presiona el boton:   
    Serial.println("Toggle RST button");
  }
  botonRSTAntes=botonRSTAhora;

  int botonSTRAhora=digitalRead(BTN_STR);

  if(botonSTRAhora==1&&botonSTRAntes==0){
    //Si se presiona el boton:   
    Serial.println("Toggle STR button");
  }
  botonSTRAntes=botonSTRAhora;
}
