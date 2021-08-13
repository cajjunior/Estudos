// Programa modifica o volume de um arquivo de audio (wav)

//Bibliotecas
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Tamanho em bytes do header de um arquivo .wav 
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Conferir a linha de comando de argumentos
    if (argc != 4)
    {
        printf("Digitar: ./volume input.wav output.wav fator\n");
        return 1;
    }

    // Abrir os arquivos (read e write)
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    // Determinar o fator de escala
    float factor = atof(argv[3]);

    // Copiar o header do arquivo a ser modificado (input) para o output
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Ler os samples de um arquivo (input) e escrever/modificar (write) os dados para o arquivo de saída (output)

    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer = factor * buffer;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }


    // Fechar arquivos
    fclose(input);
    fclose(output);
}
