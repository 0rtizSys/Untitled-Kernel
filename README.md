# Untitled Kernel

Un kernel muy basico que corre en x86 de 32 bits escrito en C y Assembly.
Proyecto personal de aprendizaje

## Estado actual
En desarrollo temprano - actualmente bootea y muestra texto en pantalla via VGA.

## Caracteristicas
- Bootea con GRUB (Multiboot)
- Driver VGA modo texto con soporte de colores
- Modo protegido de 32 bits

## Estructura

```txt
.
├── kernel
│   ├── arch **Entry point de assembly**
│   │   ├── handler.c
│   │   ├── idt.c
│   │   ├── idt.h
│   │   ├── isr.asm
│   │   └── kernel_entry.asm
│   ├── core **Aqui va el kernel principal**
│   │   └── kernel.c
│   ├── drivers **Drivers de hardware**
│   │   └── video **Drivers VGA**
│   │       ├── vga.c
│   │       └── vga.h
│   └── include **Tipos y definiciones**
│       └── types.h
├── linker.ld **Script del linker**
├── makefile
├── os **Configuracion de GRUB**
│   └── grub.cfg
└── README.md

```

## Requisitos
- gcc
- nasm
- qemu-system-i386
- grub
- make

## Compilar y correr
```
make all [Compila y genera el ISO]
make run [Corre el ISO en qemu 32 bits]

(Opcional) make clean [Limpia y borra todo el build]
```

## Roadmap
- [] GDT
- [x] IDT e Interrupciones
- [ ] Driver de teclado
- [ ] Manejo de memoria
- [ ] Scheduler