#include "vga.h"

/* Puntero directo a la memoria de video VGA.
 * 0xB8000 es la dirección física donde la tarjeta de video
 * muestra el contenido en pantalla en modo texto.
 * volatile = le dice al compilador que NO optimice este puntero,
 * porque la memoria puede cambiar sin que el CPU lo sepa.
 * u16 = cada celda ocupa 2 bytes: 1 para el caracter y 1 para el color */
static volatile u16* VGA_MEMORY = (u16*) 0xB8000;

/* Posición actual del cursor en la pantalla.
 * cursor_x = columna (0 a 79)
 * cursor_y = fila    (0 a 24) */
static int cursor_x = 0;
static int cursor_y = 0;

/* Limpia toda la pantalla llenándola con espacios en blanco.
 * 0x07 = color por defecto (texto gris claro sobre fondo negro)
 * 0x07 << 8 = mueve el byte de color a la mitad alta del u16
 * | ' ' = pone un espacio en la mitad baja (el caracter)
 * Al final regresa el cursor al origen (0, 0) */
void vga_clear() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        VGA_MEMORY[i] = (0x07 << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

/* Dibuja un solo caracter en la posición (x, y) con el color dado.
 * Primero calcula el índice lineal: fila * ancho + columna
 * Luego construye el u16: color en el byte alto, caracter en el byte bajo
 * Ejemplo: color=0x0F, c='A' → 0x0F41 en memoria */
void vga_put_char(int x, int y, char c, u8 color) {
    int index = y * VGA_WIDTH + x;
    VGA_MEMORY[index] = (color << 8) | c;
}

/* Avanza el cursor una posición a la derecha.
 * Si llega al borde derecho (columna 80),
 * regresa al inicio de la siguiente línea */
static void advance_cursor() {
    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
}

/* Escribe una cadena de texto en pantalla con el color especificado.
 * Recorre cada caracter hasta encontrar '\0' (fin de cadena).
 * Si encuentra '\n' (salto de línea): regresa a columna 0 y baja una fila,
 * y con continue salta el resto del loop para no dibujar el '\n' como caracter.
 * Para cualquier otro caracter: lo dibuja en la posición actual
 * y llama a advance_cursor() para moverse al siguiente espacio */
void vga_write(const char *str, u8 color) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
            continue;
        }
        vga_put_char(cursor_x, cursor_y, str[i], color);
        advance_cursor();
    }
}