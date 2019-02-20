unsigned long tiempo;
unsigned long tiempoAtras = 0;
byte segundos;
byte minutos;
byte horas = 6;

byte diaActual = 1;
//Hora fijada: 06:01 seis horas con un minuto en formato de 24h
byte horaDespertar = 6;
byte minutosDespertar = 1;
#define Lunes 1
#define Martes 1
#define Miercoles 1
#define Jueves 1
#define Viernes 1
#define Sabado 0
#define Domingo 0
#define LED 9
#define BUZZER 3
#define MOTOR 5
#define SENSOR A3
byte dias;
int semana[] = {Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo};
int con = 0;
boolean IN = true;
boolean OUT = false;
boolean estado = OUT;
//Dias en los cuales se activara la alarma
byte diasDeAlarma[] = {Lunes, Martes, Miercoles, Jueves, Viernes}; //Lunes, Martes, Miercoles, Jueves, Viernes, Sabado, Domingo

void setup(){
  Serial.begin(9600); 
  pinMode(LED,OUTPUT);
  pinMode(MOTOR,OUTPUT);
  pinMode(SENSOR,INPUT);
}
void loop(){
  if((horaDespertar == horas && minutosDespertar == minutos) &&(Lunes == diaActual|| Martes == diaActual || Miercoles == diaActual || Jueves == diaActual || Viernes == diaActual) && con==0){
    con++;
    digitalWrite(LED,HIGH);
    digitalWrite(BUZZER,HIGH);
    estado = IN;
    while(estado == IN){
      Serial.println("Iniciando Despertador..");
      Serial.println("...");
      int estadoSensor = analogRead(SENSOR);
      if(estadoSensor > 700){
        estado = OUT;
        digitalWrite(LED,LOW);
        digitalWrite(BUZZER,LOW);
        Serial.println("Despertador desactivado");
        break;
      }
    }
  }
  tiempo = millis();
  if((tiempo - tiempoAtras) == 1000){
    tiempoAtras = tiempo;
    segundos++;
    if(segundos == 60){
      minutos++;
    }

    if(minutos == 60){
      horas++;
    }

    if(horas  == 24){
      dias++;
      diaActual++;
      con = 0;
    }
    Serial.print("Segundos: "); Serial.print(segundos); Serial.print("  Minutos: "); Serial.print(minutos); Serial.print("  Horas: ");
    Serial.print(horas); Serial.print("  Dias: "); Serial.println(dias);
  }
}
