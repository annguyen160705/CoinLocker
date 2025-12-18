/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rc522.h"
#include "stdio.h"
#include "string.h"
#include "ILI9341_GFX.h"
#include "ILI9341_STM32_Driver.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_tx;

/* USER CODE BEGIN PV */
uint8_t status;
uint8_t str[MAX_LEN]; // Max_LEN = 16
uint8_t sNum[5];
#define COLOR_BACKGROUND BLACK
#define COLOR_BUTTON NAVY
#define COLOR_BUTTON_HIGHLIGHT BLUE
#define COLOR_TEXT WHITE
#define COLOR_ERROR RED
#define COLOR_SUCCESS GREEN
#define COLOR_LOCKER_EMPTY GREEN
#define COLOR_LOCKER_OCCUPIED RED
#define COLOR_WARNING YELLOW
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void key(void);
void locker(void);
void quetthe(void);
void lock(void);
void unlock(void);
void guihanhly(void);
void confirm(void);
void taocode(void);
void xincamon(void);
void unlock(void);
void sosanhpass(void);
void dongcua(void);
void layhanhly(void);
void taolaipassword();
uint32_t timeout = 0;
uint8_t i = 0, k = 0, dacohanhly = 0, count = 1, close = 0;
uint8_t f=1;
char keyPressed = 0;
char keystack[5], Password[5], sosanh[5];
uint8_t from_locker = 0;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
	MFRC522_Init();
	ILI9341_Init();
	// Lcd_PortType ports[] = { D4_GPIO_Port, D5_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port };
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if (close == 0) {
					dongcua();
				} else {
					locker();
				}
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */
 /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Solenoid_Pin|RST_Pin|SS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin|LCD_CS_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, C1_Pin|C2_Pin|C3_Pin|C4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : R1_Pin R2_Pin R3_Pin R4_Pin */
  GPIO_InitStruct.Pin = R1_Pin|R2_Pin|R3_Pin|R4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Input_Hanhtrinh_Pin */
  GPIO_InitStruct.Pin = Input_Hanhtrinh_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Input_Hanhtrinh_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Solenoid_Pin RST_Pin SS_Pin */
  GPIO_InitStruct.Pin = Solenoid_Pin|RST_Pin|SS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RST_Pin LCD_DC_Pin LCD_CS_Pin PB3
                           PB4 PB6 PB7 PB8 */
  GPIO_InitStruct.Pin = LCD_RST_Pin|LCD_DC_Pin|LCD_CS_Pin|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : C1_Pin C2_Pin C3_Pin C4_Pin */
  GPIO_InitStruct.Pin = C1_Pin|C2_Pin|C3_Pin|C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void drawTitle(const char *text) {
	ILI9341_DrawFilledRectangleCoord(0, 0, 239, 30, COLOR_BUTTON);
	ILI9341_DrawText(text, FONT4, 20, 8, COLOR_TEXT, COLOR_BUTTON);
}
void drawUnlockedPadlock(uint8_t x, uint8_t y, uint8_t color) {
     // Vẽ thân khóa (hình vuông 30x30)
     ILI9341_DrawFilledRectangleCoord(x, y, x + 30, y + 30, color);

     // Vẽ vòng khóa mở lệch phải (bán nguyệt)
     ILI9341_DrawHollowCircle(x + 20, y - 10, 15, color);

     // Xóa phần dưới của vòng khóa để tạo hiệu ứng "mở"
     ILI9341_DrawFilledRectangleCoord(x + 10, y - 10, x + 35, y, COLOR_BACKGROUND);
 }
void drawLockedPadlock(uint8_t x, uint8_t y, uint8_t color) {
    // Vẽ thân khóa (hình chữ nhật)
    ILI9341_DrawFilledRectangleCoord(x, y + 15, x + 40, y + 50, color);

    // Vẽ vòng khóa (hình bán nguyệt)
    ILI9341_DrawHollowCircle(x + 20, y + 15, 15, color);
    ILI9341_DrawFilledRectangleCoord(x + 5, y + 15, x + 35, y + 20, color); // Nối vòng khóa với thân khóa

    // Vẽ chốt khóa (đường dọc ở giữa ổ khóa)
    ILI9341_DrawFilledRectangleCoord(x + 18, y + 30, x + 22, y + 45, COLOR_BACKGROUND);
}
void drawLuggageIcon(uint16_t x, uint16_t y, uint16_t color) {
	// Thân vali (hình chữ nhật)
	ILI9341_DrawFilledRectangleCoord(x, y, x + 20, y + 25, color);

	// Tay cầm vali (hình chữ nhật nhỏ trên cùng)
	ILI9341_DrawFilledRectangleCoord(x + 5, y - 5, x + 15, y, color);

	// Bánh xe vali (hai hình tròn nhỏ)
	ILI9341_DrawFilledCircle(x + 3, y + 27, 2, color);
	ILI9341_DrawFilledCircle(x + 17, y + 27, 2, color);
}
void drawHandHoldingLuggage(uint16_t x, uint16_t y, uint16_t color) {
	// Tay cầm (hình chữ nhật nhỏ, giả lập ngón tay)
	ILI9341_DrawFilledRectangleCoord(x, y, x + 20, y + 6, color); // Ngón tay cầm

	// Tay người (vẽ hình oval nhỏ tượng trưng)
	ILI9341_DrawFilledCircle(x + 10, y - 5, 6, color);

	// Tay nắm vali (thanh ngang nối tay và vali)
	ILI9341_DrawHLine(x + 5, y + 6, 10, color);

	// Thân vali
	ILI9341_DrawFilledRectangleCoord(x, y + 10, x + 20, y + 35, color);

	// Bánh xe vali
	ILI9341_DrawFilledCircle(x + 4, y + 37, 2, color);
	ILI9341_DrawFilledCircle(x + 16, y + 37, 2, color);
}
void drawMainScreen() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("TU GUI HANH LY");

	// Viền phân cách giữa 2 phần
	ILI9341_DrawHLine(20, 150, 200, COLOR_TEXT);

	// Nút "Gửi hành lý" (trên)
	ILI9341_DrawFilledRectangleCoord(20, 80, 220, 140, COLOR_BUTTON);
	ILI9341_DrawHollowRectangleCoord(20, 80, 220, 140, COLOR_TEXT);  // Viền sáng
	drawLuggageIcon(30, 95, COLOR_TEXT);  // Vẽ icon vali
	ILI9341_DrawText("A. Gui hanh ly", FONT4, 70, 105, COLOR_TEXT, COLOR_BUTTON);

	// Nút "Lấy hành lý" (dưới)
	ILI9341_DrawFilledRectangleCoord(20, 160, 220, 220, COLOR_BUTTON_HIGHLIGHT);
	ILI9341_DrawHollowRectangleCoord(20, 160, 220, 220, COLOR_TEXT);  // Viền sáng
	drawHandHoldingLuggage(30, 175, COLOR_TEXT);  // Vẽ icon tay cầm vali
	ILI9341_DrawText("B. Lay hanh ly", FONT4, 70, 185, COLOR_TEXT, COLOR_BUTTON_HIGHLIGHT);
}
void drawCloseDoorScreen() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("DONG CUA");

	// Hiển thị thông báo yêu cầu đóng cửa
	ILI9341_DrawFilledRectangleCoord(20, 80, 220, 120, COLOR_BUTTON);
	ILI9341_DrawHollowRectangleCoord(20, 80, 220, 120, COLOR_TEXT);
	ILI9341_DrawText("Vui long dong cua", FONT4, 40, 95, COLOR_TEXT, COLOR_BUTTON);

	// Hiển thị trạng thái "Đang chờ đóng cửa"
	ILI9341_DrawFilledRectangleCoord(20, 140, 220, 180, COLOR_BUTTON_HIGHLIGHT);
	ILI9341_DrawHollowRectangleCoord(20, 140, 220, 180, COLOR_TEXT);
	ILI9341_DrawText("Dang cho...", FONT4, 80, 155, COLOR_TEXT, COLOR_BUTTON_HIGHLIGHT);
}
void drawDoorLockedScreen() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("TU DA KHOA");

	// Hiển thị thông báo "Tủ đã khóa thành công"
	ILI9341_DrawFilledRectangleCoord(35, 70, 249, 110, COLOR_BUTTON_HIGHLIGHT);
	ILI9341_DrawHollowRectangleCoord(35, 70, 249, 110, COLOR_TEXT);
	ILI9341_DrawText("Tu da khoa thanh cong", FONT4, 40, 85, COLOR_TEXT, COLOR_BUTTON_HIGHLIGHT);

	// Vẽ ổ khóa đã khóa
	drawLockedPadlock(135, 140,COLOR_TEXT);
}
void drawTimeoutScreen() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("HET THOI GIAN");

	// Hiển thị thông báo chính
	ILI9341_DrawText("Thao tac qua thoi gian!", FONT4, 60, 80, COLOR_ERROR, COLOR_BACKGROUND);

	// Vẽ đồng hồ cát biểu thị thời gian hết hạn
	uint16_t clock_x = 150, clock_y = 140;
		   ILI9341_DrawHollowCircle(clock_x, clock_y, 20, COLOR_TEXT); // Viền đồng hồ
		   ILI9341_DrawFilledRectangleCoord(clock_x - 2, clock_y - 10, clock_x + 2, clock_y + 5, COLOR_TEXT); // Kim phút
		   ILI9341_DrawFilledRectangleCoord(clock_x - 5, clock_y - 2, clock_x + 10, clock_y + 2, COLOR_TEXT); // Kim giờ
		   ILI9341_DrawHollowRectangleCoord(clock_x - 10, clock_y + 20, clock_x + 10, clock_y + 30, COLOR_TEXT); // Chân đồng hồ
	// Thông báo quay lại màn hình chính
	ILI9341_DrawText("Quay ve man hinh chinh...", FONT4, 50, 190, COLOR_WARNING, COLOR_BACKGROUND);

	HAL_Delay(3000); // Đợi 3 giây trước khi quay lại màn hình chính
}
void drawLockerOpenWarning() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("CANH BAO!");

	// Hiển thị thông báo chính
	ILI9341_DrawText("Tu dang mo!", FONT4, 90, 70, COLOR_ERROR, COLOR_BACKGROUND);
	ILI9341_DrawText("Hay dong tu truoc khi su dung.", FONT4, 30, 110, COLOR_ERROR, COLOR_BACKGROUND);

	// Vẽ ổ khóa mở
	uint16_t lockX = 130, lockY = 170; // Tọa độ trung tâm ổ khóa
	drawUnlockedPadlock(lockX, lockY, COLOR_ERROR);

	// Hiệu ứng cảnh báo (sóng tín hiệu đỏ)
	ILI9341_DrawHollowCircle(lockX + 20, lockY + 10, 25, COLOR_ERROR);
	ILI9341_DrawHollowCircle(lockX + 20, lockY + 10, 35, COLOR_ERROR);

}
void drawLockerOpenScreen2() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("YEU CAU NGUOI DUNG");
	// Hiển thị thông báo
	ILI9341_DrawText("An C de mo tu", FONT4, 90, 80, COLOR_WARNING, COLOR_BACKGROUND);

	// Vẽ cửa (hình chữ nhật có viền)
	uint16_t door_x1 = 120, door_y1 = 120;
	uint16_t door_x2 = 200, door_y2 = 200;

	ILI9341_DrawFilledRectangleCoord(door_x1, door_y1, door_x2, door_y2, COLOR_WARNING); // Cửa chính
	ILI9341_DrawHollowRectangleCoord(door_x1, door_y1, door_x2, door_y2, COLOR_TEXT);    // Viền cửa

	// Vẽ khoảng trống cửa mở
	ILI9341_DrawFilledRectangleCoord(door_x2 - 10, door_y1, door_x2, door_y2, COLOR_BACKGROUND);

	// Viền cho khoảng trống cửa mở
	ILI9341_DrawHollowRectangleCoord(door_x2 - 10, door_y1, door_x2, door_y2, COLOR_TEXT);

	// Vẽ tay nắm cửa (hình chữ nhật nhỏ có viền)
	uint16_t handle_x1 = 130, handle_y1 = 150;
	uint16_t handle_x2 = 140, handle_y2 = 160;

	ILI9341_DrawFilledRectangleCoord(handle_x1, handle_y1, handle_x2, handle_y2, COLOR_BACKGROUND);
	ILI9341_DrawHollowRectangleCoord(handle_x1, handle_y1, handle_x2, handle_y2, COLOR_TEXT);
}
void drawLockerOpenWarning2() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("GUI HANH LY");

	// Hiển thị thông báo chính
	ILI9341_DrawText("Tu dang mo!", FONT4, 90, 70, COLOR_TEXT, COLOR_BACKGROUND);
	ILI9341_DrawText("Dong tu de tiep tuc", FONT4, 70, 110, COLOR_TEXT, COLOR_BACKGROUND);

	// Vẽ ổ khóa mở
	uint16_t lockX = 130, lockY = 170; // Tọa độ trung tâm ổ khóa
	drawUnlockedPadlock(lockX, lockY, COLOR_TEXT);


}
void drawConfirmScreen() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("XAC NHAN");

	// Hiển thị thông báo
	ILI9341_DrawText("An phim D de confirm", FONT4, 60, 100, COLOR_TEXT, COLOR_BACKGROUND);

	// Vẽ ô chứa chữ CONFIRM
	uint16_t box_x1 = 80, box_y1 = 150;  // Góc trên trái
	uint16_t box_x2 = 200, box_y2 = 200; // Góc dưới phải

	// Vẽ nền và viền
	ILI9341_DrawFilledRectangleCoord(box_x1, box_y1, box_x2, box_y2, COLOR_BUTTON);
	ILI9341_DrawHollowRectangleCoord(box_x1, box_y1, box_x2, box_y2, COLOR_TEXT); // Viền sáng

	// Chữ CONFIRM
	ILI9341_DrawText("CONFIRM", FONT4, 100, 170, COLOR_TEXT, COLOR_BUTTON);

}
void drawCardSuccess() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("QUET THE");

	// Chữ thông báo (dịch phải)
	ILI9341_DrawText("Quet the thanh cong!", FONT4, 50, 100, COLOR_SUCCESS, COLOR_BACKGROUND);

	// Biểu tượng thẻ (dịch phải)
	uint16_t card_x = 120 - 50 + 30; // Dịch phải 20 pixel
	uint16_t card_y = 160 - 25;
	ILI9341_DrawFilledRectangleCoord(card_x, card_y, card_x + 100, card_y + 50, COLOR_TEXT);
	ILI9341_DrawFilledRectangleCoord(card_x + 5, card_y + 5, card_x + 90, card_y + 15, COLOR_BACKGROUND);

	// Hiệu ứng sóng NFC (dịch phải)
	uint16_t nfc_x = 120 + 30; // Dịch phải 20 pixel
	uint16_t nfc_y = card_y + 70;
	ILI9341_DrawHollowCircle(nfc_x, nfc_y, 10, COLOR_SUCCESS);
	ILI9341_DrawHollowCircle(nfc_x, nfc_y, 15, COLOR_SUCCESS);
	ILI9341_DrawHollowCircle(nfc_x, nfc_y, 20, COLOR_SUCCESS);
}
void drawCardFail() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("QUET THE");

	// Chữ thông báo lỗi
	ILI9341_DrawText("Quet the that bai!", FONT4, 80, 90, COLOR_ERROR, COLOR_BACKGROUND);

	// Vẽ thẻ
	uint16_t card_x = 110  ; // Dịch phải 20 pixel
	uint16_t card_y = 140 - 25;
	ILI9341_DrawFilledRectangleCoord(card_x, card_y, card_x + 100, card_y + 50, COLOR_TEXT);
	ILI9341_DrawFilledRectangleCoord(card_x + 5, card_y + 5, card_x + 90, card_y + 15, COLOR_BACKGROUND);

	// Vẽ dấu ❌ đơn giản (bằng 2 đường chéo)
	ILI9341_DrawText("X", FONT4, 155, 170, COLOR_ERROR, COLOR_BACKGROUND);
	ILI9341_DrawText("Vui long quet the lai", FONT4, 80, 90, COLOR_ERROR, COLOR_BACKGROUND);
}

void drawPaymentScreen() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("THANH TOAN");

	// Hướng dẫn quét thẻ (dịch phải)
	ILI9341_DrawText("Vui long quet the de thanh toan", FONT4, 20, 100, COLOR_TEXT, COLOR_BACKGROUND);

	// Biểu tượng thẻ (dịch phải)
	uint16_t card_x = 120 - 50 + 40;
	uint16_t card_y = 160 - 25;
	ILI9341_DrawFilledRectangleCoord(card_x, card_y, card_x + 100, card_y + 50, COLOR_TEXT);
	ILI9341_DrawFilledRectangleCoord(card_x + 5, card_y + 5, card_x + 90, card_y + 15, COLOR_BACKGROUND);

	// Hiệu ứng sóng NFC (dịch phải)
	uint16_t nfc_x = 120 + 35;
	uint16_t nfc_y = card_y + 70;
	ILI9341_DrawHollowCircle(nfc_x, nfc_y, 10, COLOR_TEXT);
	ILI9341_DrawHollowCircle(nfc_x, nfc_y, 15, COLOR_TEXT);
}
void drawCardTimeout() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("QUET THE");
	// Hiển thị thông báo
	ILI9341_DrawText("Het thoi gian quet the!", FONT4, 50, 90, COLOR_ERROR, COLOR_BACKGROUND);

	uint16_t clock_x = 140, clock_y = 160;
	  ILI9341_DrawHollowCircle(clock_x, clock_y, 20, COLOR_TEXT); // Viền đồng hồ
	  ILI9341_DrawFilledRectangleCoord(clock_x - 2, clock_y - 10, clock_x + 2, clock_y + 5, COLOR_TEXT); // Kim phút
	  ILI9341_DrawFilledRectangleCoord(clock_x - 5, clock_y - 2, clock_x + 10, clock_y + 2, COLOR_TEXT); // Kim giờ
	  ILI9341_DrawHollowRectangleCoord(clock_x - 10, clock_y + 20, clock_x + 10, clock_y + 30, COLOR_TEXT); // Chân đồng hồ


}
void drawEnterPasswordScreen() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("NHAP MAT KHAU");

	// Hiển thị hướng dẫn
	ILI9341_DrawText("Nhap mat khau (5 so):", FONT4, 50, 80, COLOR_TEXT, COLOR_BACKGROUND);

	// Vẽ các ô nhập mật khẩu
	for (int i = 0; i < 5; i++) {
		ILI9341_DrawHollowRectangleCoord(60 + i * 40, 130, 90 + i * 40, 170, COLOR_TEXT);
	}
}
void updatePasswordDisplay(uint8_t index, char digit) {
	if (index < 5) { // Chỉ cập nhật khi index hợp lệ (0-4)
		char str[2] = {digit, '\0'}; // Chuyển số thành chuỗi (để vẽ)

		// Tính vị trí x để căn giữa trong ô 30px (kích thước chữ là 15px)
		int xPos = 60 + index * 40 + (30 - 15) / 2;

		// Tính vị trí y để căn giữa trong ô 40px (kích thước chữ là 19px)
		int yPos = 150;  // Căn giữa trong ô 130 đến 170 (40px chiều cao)

		// Vẽ số tại ô nhập mật khẩu tương ứng
		ILI9341_DrawText(str, FONT4, xPos, yPos, COLOR_TEXT, COLOR_BACKGROUND);
	}
}
void drawConfirmResetPasswordScreen() {
	ILI9341_FillScreen(COLOR_BACKGROUND);  // Xóa màn hình, tô nền tối
	drawTitle("TAO LAI MAT KHAU");    // Tiêu đề trên cùng

	// Hiển thị câu hỏi xác nhận
	ILI9341_DrawText("Ban co muon tao lai", FONT4, 60, 80, COLOR_TEXT, COLOR_BACKGROUND);
	ILI9341_DrawText("password khong?", FONT4, 80, 110, COLOR_TEXT, COLOR_BACKGROUND);

	// Vẽ khung viền cho lựa chọn *YES
	ILI9341_DrawHollowRectangleCoord(50, 160, 130, 190, COLOR_BUTTON_HIGHLIGHT);
	ILI9341_DrawText("* YES", FONT4, 65, 165, COLOR_BUTTON_HIGHLIGHT, COLOR_BACKGROUND);

	// Vẽ khung viền cho lựa chọn #NO
	ILI9341_DrawHollowRectangleCoord(150, 160, 230, 190, COLOR_TEXT);
	ILI9341_DrawText("# NO", FONT4, 170, 165, COLOR_TEXT, COLOR_BACKGROUND);
}
void drawThankYouScreen() {
	ILI9341_FillScreen(COLOR_BACKGROUND);  // Xóa màn hình, tô nền tối

	// Vẽ đường kẻ trang trí trên & dưới
	ILI9341_DrawFilledRectangleCoord(40, 60, 250, 70, COLOR_TEXT);
	ILI9341_DrawFilledRectangleCoord(40, 180, 250, 190, COLOR_TEXT);

	// Hiển thị tiêu đề cảm ơn
	ILI9341_DrawText("CAM ON QUY KHACH", FONT4, 50, 90, COLOR_TEXT, COLOR_BACKGROUND);

	// Hiển thị dòng chữ nhỏ hơn
	ILI9341_DrawText("DA SU DUNG DICH VU", FONT4, 45, 130, COLOR_TEXT, COLOR_BACKGROUND);

	HAL_Delay(2000);  // Hiển thị 2 giây rồi quay lại màn hình chính
}
void drawIncorrectPasswordAttemptScreen(int count) {
	ILI9341_FillScreen(COLOR_BACKGROUND);  // Tô nền tối
	drawTitle("SAI MAT KHAU !!!");

	// Tạo chuỗi hiển thị số lần nhập sai
	char text[50];
	sprintf(text, "Ban da nhap sai %d lan", count);  // Tạo thông báo
	

	// Hiển thị thông báo lên màn hình
	ILI9341_DrawText(text, FONT4, 40, 100, RED, COLOR_BACKGROUND);  // Vị trí hiển thị thông báo
	HAL_Delay(2000);
}
void drawLockerOpenScreen() {
	ILI9341_FillScreen(COLOR_BACKGROUND);
	drawTitle("CUA MO!");

	// Hiển thị thông báo
	ILI9341_DrawText("VUI LONG LAY HANH LY", FONT4, 50, 80, COLOR_WARNING, COLOR_BACKGROUND);

	// Vẽ cửa (hình chữ nhật có viền)
	uint16_t door_x1 = 120, door_y1 = 120;
	uint16_t door_x2 = 200, door_y2 = 200;

	ILI9341_DrawFilledRectangleCoord(door_x1, door_y1, door_x2, door_y2, COLOR_WARNING); // Cửa chính
	ILI9341_DrawHollowRectangleCoord(door_x1, door_y1, door_x2, door_y2, COLOR_TEXT);    // Viền cửa

	// Vẽ khoảng trống cửa mở
	ILI9341_DrawFilledRectangleCoord(door_x2 - 10, door_y1, door_x2, door_y2, COLOR_BACKGROUND);

	// Viền cho khoảng trống cửa mở
	ILI9341_DrawHollowRectangleCoord(door_x2 - 10, door_y1, door_x2, door_y2, COLOR_TEXT);

	// Vẽ tay nắm cửa (hình chữ nhật nhỏ có viền)
	uint16_t handle_x1 = 130, handle_y1 = 150;
	uint16_t handle_x2 = 140, handle_y2 = 160;

	ILI9341_DrawFilledRectangleCoord(handle_x1, handle_y1, handle_x2, handle_y2, COLOR_BACKGROUND);
	ILI9341_DrawHollowRectangleCoord(handle_x1, handle_y1, handle_x2, handle_y2, COLOR_TEXT);
}

void drawLockerEmptyScreen() {
    ILI9341_FillScreen(COLOR_BACKGROUND);  // Xóa toàn bộ màn hình về màu nền

    drawTitle("THONG BAO");  // Tiêu đề ở trên cùng

    // Nội dung chính
    ILI9341_DrawText("Tu chua co hanh ly", FONT4, 20, 80, COLOR_TEXT, COLOR_BACKGROUND);
    ILI9341_DrawText("Vui long chon", FONT4, 20, 110, COLOR_TEXT, COLOR_BACKGROUND);
  ILI9341_DrawText("Gui hanh ly (A)", FONT4, 20, 140, COLOR_BUTTON_HIGHLIGHT, COLOR_BACKGROUND);

    // Vẽ khung hình minh họa đơn giản
    ILI9341_DrawHollowRectangleCoord(10, 70, 230, 170, COLOR_TEXT);  // khung chữ
}















void dongcua() {
	i = 0; //Trạng thái 0
	timeout=0;
	HAL_Delay(50);
	drawCloseDoorScreen();

	// Chờ cho đến khi công tắc hành trình báo tủ đã đóng
	while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) != 0) {
		HAL_Delay(500);  // Kiểm tra lại sau mỗi 500ms
	}

	drawDoorLockedScreen();
	HAL_Delay(300);
	// Khi tủ đã đóng, khóa lại
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
	close = 1;
	f=1;
	locker();  // Quay lại menu chính
}
void locker() {
	keyPressed = 0; //Đảm bảo không có kí tự đè
	HAL_Delay(50);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0); // Đảm bảo khóa tủ lúc bắt đầu
	i = 1;

	if(f==1) drawMainScreen();
	f=0;
	// Kiểm tra trạng thái cửa trước khi cho phép chọn chức năng
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1) {
		drawLockerOpenWarning();
		HAL_Delay(300);
		dongcua();
		return;
	}
	key();
	HAL_Delay(500);
	if (keyPressed == 65) {  // A = Gửi hành lý
		HAL_Delay(100);
		lock();
	} else if (keyPressed == 66) {  // B = Lấy hành lý
		keyPressed=0;
		HAL_Delay(100);
		unlock();
	}
}
void lock() {
	i = 2;
	timeout=0;
	drawLockerOpenScreen2();
	timeout = HAL_GetTick() + 100000;  // Timeout sau 100 giây
	//PA1 la mach hanh trinh
	while (HAL_GetTick() < timeout-90000) {
		key();
		// Kiểm tra xem tủ đã có hành lý chưa
		if (dacohanhly == 1) {
			ILI9341_FillScreen(COLOR_BACKGROUND);
			drawTitle("CANH BAO!!");
			ILI9341_DrawText("Tu da co hanh ly. Thoat sau 5s", FONT4, 15, 80, COLOR_WARNING, COLOR_BACKGROUND);
			uint8_t clock_x = 150, clock_y = 140;
			ILI9341_DrawHollowCircle(clock_x, clock_y, 20, COLOR_TEXT); // Viền đồng hồ
			ILI9341_DrawFilledRectangleCoord(clock_x - 2, clock_y - 10, clock_x + 2, clock_y + 5, COLOR_TEXT); // Kim phút
			ILI9341_DrawFilledRectangleCoord(clock_x - 5, clock_y - 2, clock_x + 10, clock_y + 2, COLOR_TEXT); // Kim giờ
			ILI9341_DrawHollowRectangleCoord(clock_x - 10, clock_y + 20, clock_x + 10, clock_y + 30, COLOR_TEXT); // Chân đồng hồ
			HAL_Delay(5000);
			f=1;
			locker();
			return;
		}

		// Chờ nhập phím C để gửi hành lý

		else {
			if (keyPressed == 67) {
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1); //Mở chốt solenoid
				HAL_Delay(50);
				guihanhly();
			}
		}
	}
}

void guihanhly() {
	i = 3;
	close = 0;
	timeout=0;
	timeout = HAL_GetTick() + 100000;  // Timeout sau 100 giây
	//PA1 la mach hanh trinh
	while (HAL_GetTick() < timeout) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1); //chắc chắn rằng tủ đang mở
		drawLockerOpenWarning2();
		HAL_Delay(2000); // chống nhảy qua trạng thái i4 quá sớm nếu khách chưa kịp mở tủ
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0) {
			close = 1;
			confirm();

		}

		HAL_Delay(50);  // Kiểm tra lại sau mỗi 2050
	}

	// Sau 100 giây, thử lại quy trình tủ
	locker();
}
void confirm() {
	drawConfirmScreen();
	i = 4;
	timeout=0;
	timeout = HAL_GetTick() + 100000;
	while (HAL_GetTick() < timeout) {
		keyPressed = 0;  //Chắc chắn không có kí tự đè
		key();
		if (keyPressed == 68) { //Nhấn D để confirm rằng đã gửi hành lý xong
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0) { //Công tắc hành trình đóng
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0); //Tủ chốt lại
				close = 1;
				taocode();
			} else {
				guihanhly();

			}
		}
		HAL_Delay(10);
	}
	locker();
}

void quetthe() {
	i = 5;
	timeout = HAL_GetTick() + 100000;
	uint8_t str[5];
	const uint8_t expectedID[5] = { 254, 226, 48, 3, 47 }; // Thẻ đúng

	drawPaymentScreen();

	while (HAL_GetTick() < timeout) {
		// Kiểm tra nếu đọc thẻ thành công
		if (MFRC522_Request(PICC_REQIDL, str) == MI_OK //Kiểm tra xem có thẻ nào trong vùng quét không. Nếu có, thông tin lưu vào str.
		&& MFRC522_Anticoll(str) == MI_OK) { //Đọc số seri (UID) của thẻ để tránh trùng lặp.
			//Nếu cả hai hàm trả về MI_OK, nghĩa là đọc thẻ thành công, thì tiếp tục.
			memcpy(sNum, str, 5); //Sao chép 5 byte số seri UID vào biến sNum.

			// Kiểm tra nếu thẻ hợp lệ
			if (memcmp(str, expectedID, 5) == 0) { //Nếu 5 byte trong str trùng với expectedID, nghĩa là thẻ hợp lệ.
				drawCardSuccess();
				layhanhly();
				return; // Thẻ hợp lệ, thoát hàm ngay
			} else {
				i = 16;
				drawCardFail();
			}
		}

		HAL_Delay(500); // Tránh spam UART
	}
	locker(); // Chỉ khóa nếu hết thời gian mà không có thẻ hợp lệ
}

void taocode() {
	i = 6;
	k = 0;
	timeout=0;
	keyPressed = 0;
	drawEnterPasswordScreen();
	timeout = HAL_GetTick() + 100000;
	HAL_Delay(500);
	while (HAL_GetTick() < timeout) {
		keyPressed=0;
		printf("Password: %d%d%d%d%d\n", keystack[0], keystack[1], keystack[2],
				keystack[3], keystack[4]);
		key();
		if (keyPressed != 0) {
			keystack[k] = keyPressed; // Lưu giá trị vào vị trí k
			updatePasswordDisplay(k, keystack[k]);
			k++;                   // Tăng k để lần nhập sau lưu vào vị trí mớ
			keyPressed = 0;		//reset lại để tạo vòng lặp mới
			HAL_Delay(500);
			if (k == 5) {
				for (int j = 0; j < 5; j++) {
					Password[j] = keystack[j]; //gán Password = keystack theo thứ tự j
					keystack[j] = 0;//reset keystack để chuẩn bị cho chương trình kế tiếp
				}
				taolaipassword();

			}
		}
	}
	locker();
}
void taolaipassword() {
	dacohanhly = 0;
	timeout=0;
	i = 7;
	k = 0;
	drawEnterPasswordScreen();
	for (int a = 0; a < 5; a++) {
	        updatePasswordDisplay(a, Password[a]);
	    }
	printf("Password: %d%d%d%d%d\n", Password[0], Password[1], Password[2],
			Password[3], Password[4]);
	drawConfirmResetPasswordScreen();
	printf("Ban co muon tao lai password khong? *Yes #No"); //  42 la * 35 la # theo ASCII
	keyPressed = 0;
	timeout = HAL_GetTick() + 100000;
	while (HAL_GetTick() < timeout) {
		key();
		if (keyPressed == 35) {
			xincamon(); //Nhấn # NO
		}
		if (keyPressed == 42) {
			taocode(); //Nhấn * YES
		}
	}
	xincamon();

}
void xincamon() {
//ien thi da thuc hien thanh cong tro ve trang thai ban dau sau 10s

	i = 8;
	timeout=0;
	timeout = HAL_GetTick() + 3000;
	drawThankYouScreen();
	while (HAL_GetTick() < timeout) {
		dacohanhly = 1;

	}
	HAL_Delay(2000);
	f=1;
	locker();

}

void unlock() {
	timeout=0;
	updatePasswordDisplay(k, keystack[k]);
	HAL_Delay(100);
	keyPressed = 0; //Đảm bảo không có kí tự đè
	k = 0;
	i = 9;
	if(dacohanhly==0){
		drawLockerEmptyScreen();
		HAL_Delay(3000);
		f=1;
		locker();
	}
	if(dacohanhly==1){
		drawEnterPasswordScreen();
		timeout = HAL_GetTick() + 100000;
		while (HAL_GetTick() < timeout) {
			printf("Hay nhap password");
			printf("Password: %d%d%d%d%d\n", keystack[0], keystack[1], keystack[2],
					keystack[3], keystack[4]);
			key();
			if (keyPressed != 0) {
				keystack[k] = keyPressed; // Lưu giá trị vào vị trí j
				updatePasswordDisplay(k, keystack[k]);
				k++;    // Tăng j để lần nhập sau lưu vào vị trí mới
				keyPressed = 0;			// Reset giá trị sau khi lưu
				HAL_Delay(500);
				if (k == 5) {
					for (int j = 0; j < 5; j++) {
						sosanh[j] = keystack[j];
						keystack[j] = 0;
						k = 0;
					}
					sosanhpass();
				}
			}
		}
	}
	printf("Het thoi gian nhap password");
	f=1;
	locker();
}
void sosanhpass() {
	i = 10;
	for (int t = 0; t < 5; t++) {
		if (sosanh[t] != Password[t]) {
			//printf("Ban da nhap sai %d lan password", count);
			drawIncorrectPasswordAttemptScreen(count);
			count++;

			if (count > 3) {
				printf("Ban da nhap qua 3 lan password he thong se bi khoa trong 5p");
				ILI9341_DrawText("                         ", FONT4, 40, 100, RED, COLOR_BACKGROUND);
				ILI9341_DrawText("Ban da nhap sai qua 3 lan", FONT4, 40, 100, RED, COLOR_BACKGROUND);
				ILI9341_DrawText("He thong bi khoa trong 5 phut", FONT4, 40, 120, RED, COLOR_BACKGROUND);
				HAL_Delay(30000);  // Khóa tạm 5 phút
				count = 1;  // Reset bộ đếm sau khi khóa
				locker(); //Trở về trạng thái ban đầu
			}

			unlock();  // Cho phép nhập lại
		}
	}

// Nếu vòng lặp chạy hết mà không có lỗi -> Mở tủ

	quetthe();

}

void layhanhly() {
	i = 11;
	count = 0;
	close = 0;
	timeout=0;
	timeout = HAL_GetTick() + 1000;
	dacohanhly = 0;
	drawLockerOpenScreen();
	HAL_Delay(3000);
	while (HAL_GetTick() < timeout) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
	}
	f=1;
	locker(); //Hết thời gian thì quay về locker, cho dù có không đóng cửa thì cũng đã có hàm dongcua để backup
}
void key() {

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 0);
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1) {
		keyPressed = 68; //ASCII value of D
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1) {
		keyPressed = 67; //ASCII value of C
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 1) {
		keyPressed = 66; //ASCII value of B
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == 1) {
		keyPressed = 65; //ASCII value of A
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 0);
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1) {
		keyPressed = 35; //ASCII value of #
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1) {
		keyPressed = 57; //ASCII value of 9
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 1) {
		keyPressed = 54; //ASCII value of 6
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == 1) {
		keyPressed = 51; //ASCII value of 3
	}

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 0);
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1) {
		keyPressed = 48; //ASCII value of 0
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1) {
		keyPressed = 56; //ASCII value of 8
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 1) {
		keyPressed = 53; //ASCII value of 5
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == 1) {
		keyPressed = 50; //ASCII value of 2
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 1);
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1) {
		keyPressed = 42; //ASCII value of *
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1) {
		keyPressed = 55; //ASCII value of 7
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 1) {
		keyPressed = 52; //ASCII value of 4
	} else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == 1) {
		keyPressed = 49; //ASCII value of 1
	}

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
