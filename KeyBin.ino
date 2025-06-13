// C++ code
//

const int rowPins[4] = {3, 4, 5, 6};       // Linhas (saídas)
const int colPins[4] = {8, 9, 10, 11};     // Colunas (entradas)
const int outPins[4] = {A1, A2, A3, A4};   // Saídas para o display

// Mapeamento direto das teclas [linha][coluna]
const byte keyMap[4][4] = {
  {1,  2,  3,  10},  // A = 10
  {4,  5,  6,  11},  // B = 11
  {7,  8,  9,  12},  // C = 12
  {14, 0, 15, 13}    // * = 14, 0, # = 15, D = 13
};

void setup() {
  // Configura pinos das linhas
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH); // Inicia em HIGH (inativo)
  }
  
  // Configura pinos das colunas
  for (int i = 0; i < 4; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
  
  // Configura pinos de saída do display
  for (int i = 0; i < 4; i++) {
    pinMode(outPins[i], OUTPUT);
    digitalWrite(outPins[i], LOW);
  }
}

void loop() {
  for (int row = 0; row < 4; row++) {
    // Ativa apenas a linha atual (LOW ativa)
    digitalWrite(rowPins[row], LOW);
    
    // Verifica todas as colunas
    for (int col = 0; col < 4; col++) {
      if (digitalRead(colPins[col]) == LOW) {
        handleKeyPress(row, col);
        delay(50);  // Debounce
        while(digitalRead(colPins[col]) == LOW) {} // Espera soltar
      }
    }
    
    // Desativa a linha
    digitalWrite(rowPins[row], HIGH);
    delay(1); // Pequeno delay entre linhas
  }
}

void handleKeyPress(int row, int col) {
  byte keyValue = keyMap[row][col];
  saida(keyValue);
}

void saida(int num) {
  // Converte número para representação binária nos pinos
  digitalWrite(outPins[0], bitRead(num, 0)); // LSB
  digitalWrite(outPins[1], bitRead(num, 1));
  digitalWrite(outPins[2], bitRead(num, 2));
  digitalWrite(outPins[3], bitRead(num, 3)); // MSB
}