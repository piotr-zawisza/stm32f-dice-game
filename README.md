# stm32f-dice-game

An electronic version of a simplified Poker Dice/Yahtzee game designed for the **STM32F429ZIT6** microcontroller platform. The project features a full simulation of rolling five dice, a mechanism for locking selected results, and automatic score calculation based on game rules.

---

## Technical Specifications

* **Microcontroller:** STM32F429ZIT6 (ARM Cortex-M4).
* **Programming Language:** C.
* **IDE:** STM32CubeIDE.
* **Libraries:** STM32 HAL Library and BSP (Board Support Package) for LCD and SDRAM support.

### Hardware Configuration

| Peripheral | Application | Configuration |
| :--- | :--- | :--- |
| **LTDC/DMA2D** | LCD display handling and graphical operations. | 2 layers, ARGB8888 format, buffer in SDRAM. |
| **RNG** | Hardware Random Number Generator. | Rolling dice values (1-6). |
| **ADC1** | Control interface (potentiometer). | Channel 7 (PA7) for dice selection. |
| **TIM1** | Sound generator. | PWM Generation mode CH2 (PA9). |
| **RTC** | Real-Time Clock and backup registers. | High Score storage after power disconnection. |
| **CRC** | Cyclic Redundancy Check module. | Data integrity verification for High Score. |
| **GPIO** | User Button handling. | PA0 (User Button) as input with EXTI interrupt. |
| **FMC** | External memory controller. | Communication with SDRAM (video frame buffer). |

---

## Gameplay Mechanics

The main goal is to maintain the longest possible streak of successful turns without losing all lives (the player starts with 3 lives).

### Scoring Table

| Combination | Description | Points |
| :--- | :--- | :--- |
| **General (Yahtzee)** | All 5 dice show the same value. | 50 |
| **Large Straight** | Five dice forming a sequence of 5 consecutive numbers. | 40 |
| **Small Straight** | At least four dice forming a sequence of 4 consecutive numbers. | 30 |
| **Full House** | A $3,2$ pattern (three of one value, two of another). | 25 |
| **Sum (Chance)** | No special combination - total sum of all dice. | Sum of pips |

### Difficulty System
* To avoid losing a life, the score obtained in the current turn must be **higher** than the current session record (High Score).
* Every broken record becomes the new threshold to beat in subsequent turns.

---

## Controls

* **Potentiometer:** Used for navigation between the five dice (the selected die is highlighted with a blue border).
* **User Button:**
    * **Short Press (< 1s):** Locks/unlocks the selected die (turns gray when locked) or starts a new turn.
    * **Long Press (> 1s):** Confirms selection, rerolls unlocked dice, and proceeds to the scoring phase.

---

## Software Architecture

The game logic is based on a **State Machine**, ensuring smooth transitions between phases: `GAME_START`, `FIRST_ROLL`, `SELECTING`, `REROLL`, and `SCORING`.

### Key Modules
* `dice.c/h`: Dice structure management and scoring algorithms.
* `animation.c/h`: Graphics rendering using double buffering (eliminates flickering).
* `audio.c/