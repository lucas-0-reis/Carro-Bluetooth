#define in1 6 // Entrada do motor 1
#define in2 5 // Entrada do motor 1
#define in3 11 // Entrada do motor 2
#define in4 10 // Entrada do motor 2

int dataIn[5] {0,0,0,0}; // Vetor dos dados completos que receberemos do aplicativo
int in_byte = 0; // A informação em bytes que estamos recebendo a cada momento do aplicativo
int array_index = 0; // Índice do vetor 
int X, Y, button, velMotor; // As coordenadas em X, Y, o botão e a variável de velocidade
unsigned long time1; // Variável auxiliar para guardar tempo

void setup() {
  Serial.begin(9600);  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(2, OUTPUT); // Pino do LED indicador
}

void loop() {
  if (Serial.available() > 0) { // Verifica se há dados recebidos via Bluetooth
    time1 = millis();
    digitalWrite(2, HIGH); // LED aceso indica conexão ativa
    in_byte = Serial.read();  // Recebe um byte do app
    if (in_byte == 255)  // Byte de encerramento
      array_index = 0;
    dataIn[array_index] = in_byte;   
    array_index++;
  } else {
    if ((millis() - time1) > 500) // Se passaram mais de 0,5s sem sinal
      digitalWrite(2, LOW); // Desliga o LED (sem conexão)
  }

  X = dataIn[2] - 124; 
  Y = 124 - dataIn[3]; 
  button = dataIn[1]; 
  velMotor = Y * 2; // Cálculo de velocidade PWM

  // ----------- Para frente --------------- //
  if (Y > 1) {
    analogWrite(in1, velMotor); 
    digitalWrite(in2, LOW);
    analogWrite(in3, velMotor);
    digitalWrite(in4, LOW);
  }
  // ----------- Para trás --------------- //
  else if (Y < -1) {
    analogWrite(in2, -1 * velMotor);
    digitalWrite(in1, LOW);
    analogWrite(in4, -1 * velMotor);
    digitalWrite(in3, LOW);
  }
  // ------------ Parado ------------- //
  else {
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  // ----------- Direção ------------- //
  if (X < -34) { // Esquerda
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  } 
  else if (X > 34) { // Direita
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}
