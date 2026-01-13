# 🐍 STM32 Snake Console

Este proyecto consiste en el desarrollo de una consola de videojuegos portátil basada en el microcontrolador **STM32F407VGT6**, que ejecuta una versión personalizada del clásico juego "Snake". El proyecto integra periféricos analógicos y digitales para ofrecer una experiencia de juego completa, desde el control por joystick hasta efectos de sonido y gestión de récords.

## 🕹️ Características del Proyecto

- **Control Preciso**: Uso de un joystick analógico mediante el **ADC** para el movimiento de la serpiente.
- **Interfaz Dinámica**: Pantalla LCD 16x2 gestionada por **I2C** con estados de juego (Inicio, Juego, Game Over y Récord).
- **Sonido Arcade**: Retroalimentación sonora mediante **PWM** para comida, muerte y celebración de récords.
- **Dificultad Progresiva**: Sistema de aceleración automática conforme aumenta la puntuación.
- **Maqueta Física**: Chasis artesanal de cartón que integra todos los componentes en un formato de consola portátil.

## 🛠️ Especificaciones Técnicas

- **Microcontrolador**: STM32F407VGT6 (ARM Cortex-M4).
- **Entorno de desarrollo**: STM32CubeIDE (HAL Libraries).
- **Timers**:
  - `TIM2`: Control del ritmo y velocidad del juego.
  - `TIM3`: Generación de frecuencias para el zumbador (PWM).
- **Comunicación**: I2C para el display y ADC para la lectura de ejes del joystick.

## 📂 Estructura de Desarrollo

El repositorio refleja una progresión por hitos, subidos de forma secuencial:

1. **Funcional**: Lógica básica de movimiento y colisiones.
2. **Velocidad**: Implementación de aceleración dinámica y mejoras gráficas.
3. **Completo**: Integración de sistema de High Score y sonidos. Optimización de interfaz y montaje físico.

## 🏗️ Montaje Final

La electrónica está integrada en una consola portátil de cartón reciclado. El diseño permite el acceso directo al botón azul de la placa para el reinicio de las partidas y mantiene el cableado protegido en su interior, logrando un acabado compacto y funcional.

---
*Desarrollado para la asignatura de Sistemas Electrónicos Digitales por Laura Hernández, Manuel Sánchez y Pablo García (Grupo 31). Tutor: Giuseppe.*
