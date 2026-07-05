# Chassis Sketch

## Top View

```text
                 FRONT
            [ USB Camera ]
             forward-facing

      +---------------------------------+
      |       3D-printed chassis        |
      |                                 |
      |          Raspberry Pi 5         |
      |                                 |
      |        [ MPU6050 near center ]  |
      |                                 |
      |             ESP32-S3            |
      |                                 |
      |        Logic-Level Shifter      |
      |                                 |
      |        DRV8833 Motor Driver     |
      |                                 |
      |       Battery holder / motor    |
      |             power rail          |
      +----------+-------------+--------+
                 |             |
          [ Left N20 ]   [ Right N20 ]
            motor           motor
              |               |
          Left wheel      Right wheel

          Front underside:
          custom 3D-printed skid/support
```

## Mechanical Notes

- The robot uses two powered wheels and one custom 3D-printed front skid/support.
- No acrylic sheet is needed because the chassis/base is 3D printed.
- No ball caster is needed because the front support is 3D printed.
- The MPU6050 should be mounted near the center of the chassis.
- The USB camera should face forward and stay rigid during movement.
- The Raspberry Pi 5 should have airflow and room for the AI HAT+ stack.
- The ESP32-S3, logic-level shifter, and DRV8833 should stay close enough for short signal wires.
- The motor battery holder should be secured so it does not shift during turns.
- The front support height must be tuned so the powered wheels keep traction.
- Final wheelbase, wheel diameter, camera height, camera angle, and front-support height must be measured after assembly.
