#ifndef HX711_ADC_config_h
#define HX711_ADC_config_h

// Número de amostras no conjunto de média móvel, deve ser 1, 2, 4, 8, 16, 32, 64 ou 128.
#define SAMPLES                    16      // valor padrão: 16

// Ignorar amostras altas/baixas, deve ser 0 ou 1.
#define IGN_HIGH_SAMPLE            1       // valor padrão: 1
#define IGN_LOW_SAMPLE             1       // valor padrão: 1

// Atraso em microssegundos após escrever o pino sck alto ou baixo.
#define SCK_DELAY                  1       // valor padrão: 1 (habilitado)

// Desabilitar interrupções ao escrever no pino sck.
#define SCK_DISABLE_INTERRUPTS     0       // valor padrão: 0

#endif