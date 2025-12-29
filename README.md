# 🐍 STM32 Snake Console

Este proyecto consiste en el desarrollo de una consola de videojuegos portátil basada en el microcontrolador **STM32F407VGT6**, que ejecuta una versión personalizada del clásico juego "Snake". El proyecto integra periféricos analógicos y digitales para ofrecer una experiencia de juego completa, desde el control por joystick hasta efectos de sonido.

## 🕹️ Características del Proyecto

- **Control Preciso**: Uso de un joystick analógico mediante el **ADC** para el movimiento de la serpiente.
- **Interfaz Dinámica**: Pantalla LCD 16x2 gestionada por **I2C** con estados de juego (Inicio, Juego, Game Over y IDLE).
- **Sonido Arcade**: Retroalimentación sonora mediante **PWM** para comida y muerte.

## 🛠️ Especificaciones Técnicas

- **Microcontrolador**: STM32F407G-DISC1.
- **Entorno de desarrollo**: STM32CubeIDE.
- **Timers**:
  - `TIM2`: Control del ritmo y velocidad del juego.
  - `TIM3`: Generación de frecuencias para el zumbador (PWM).
- **Comunicación**: I2C para el display y ADC para la lectura de ejes del joystick.
