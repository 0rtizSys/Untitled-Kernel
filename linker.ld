ENTRY(_start)

SECTIONS
{
    . = 1M;

    /* Código (solo ejecución) */
    .text : ALIGN(4K)
    {
        *(.multiboot)
        *(.text*)
    }

    /* Solo lectura */
    .rodata : ALIGN(4K)
    {
        *(.rodata*)
    }

    /* Datos (lectura/escritura) */
    .data : ALIGN(4K)
    {
        *(.data*)
    }

    /* BSS */
    .bss : ALIGN(4K)
    {
        *(COMMON)
        *(.bss*)
    }
}
