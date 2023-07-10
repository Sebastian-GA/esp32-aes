#include "AES128.h"

char cleartext[256];  // Buffer to save strings
char ciphertext[512];
unsigned long tick, tock;

void setup() {
    Serial.begin(115200);
    while (!Serial)
        ;
    delay(2000);

    aes_init();
    Serial.println("AES128 Encrypter");
    Serial.println();
}

void loop() {
    if (Serial.available()) {
        Serial.println();

        String readBuffer = Serial.readStringUntil('\n');
        Serial.println("INPUT: " + readBuffer);

        // Encrypt
        sprintf(cleartext, "%s", readBuffer.c_str());  // must not exceed 255 bytes; may contain a newline
        tick = micros();
        String encrypted = aes_encrypt(cleartext);
        tock = micros();
        Serial.println("Ciphertext: " + encrypted);
        Serial.println("Time taked: " + String(tock - tick) + "uS");

            // Decrypt
            sprintf(ciphertext, "%s", encrypted.c_str());
        tick = micros();
        String decrypted = aes_decrypt(ciphertext);
        tock = micros();
        Serial.println("Cleartext: " + decrypted);
        Serial.println("Time taked: " + String(tock - tick) + "uS");

            // Validate
            if (decrypted.equals(cleartext))
                Serial.println("SUCCES");
        else
            Serial.println("FAILURE");
    }
}
