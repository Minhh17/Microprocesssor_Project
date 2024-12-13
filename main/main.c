#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "ssd1306.h"
#include "font8x8_basic.h"

#define tag "SSD1306"

void display_centered_text(SSD1306_t *dev, int line, const char *text) {
    int text_len = strlen(text);
    int max_chars_per_line = 16;  // Tối đa 16 ký tự trên mỗi dòng (128 pixel / 8 pixel mỗi ký tự)
    
    if (text_len > max_chars_per_line) {
        char temp_text[max_chars_per_line + 1];
        strncpy(temp_text, text, max_chars_per_line);
        temp_text[max_chars_per_line] = '\0';  // Đảm bảo kết thúc chuỗi
        text = temp_text;  // Cập nhật chuỗi văn bản để hiển thị
    }

    int width = 128;  // Chiều rộng màn hình
    int font_size = 8;  // Kích thước font 8x8
    int text_width = strlen(text) * font_size;

    // Tính toán vị trí căn giữa
    int x_pos = (width - text_width) / 2;

    // Hiển thị văn bản tại vị trí đã tính
    ssd1306_display_text(dev, line, text, strlen(text), false);  // Sử dụng kích thước font 8x8
}

void app_main(void)
{
    SSD1306_t dev;
	int center, top, bottom;
	char lineChar[20];

    printf("Start Main\n");

#if CONFIG_I2C_INTERFACE  // chỉ được biên dịch nếu CONFIG_I2C_INTERFACE enable
	ESP_LOGI(tag, "INTERFACE is i2c");
	ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(tag, "INTERFACE is SPI");
	ESP_LOGI(tag, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(tag, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	ESP_LOGI(tag, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(tag, "CONFIG_DC_GPIO=%d",CONFIG_DC_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_SSD1306_128x64
	ESP_LOGI(tag, "Panel is 128x64");
	ssd1306_init(&dev, 128, 64);
#endif // CONFIG_SSD1306_128x64

	ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);
	ssd1306_display_text_x3(&dev, 0, "Checkin", 5, false);
	ssd1306_display_text_x3(&dev, 4, "Done!", 5, false);
	vTaskDelay(3000 / portTICK_PERIOD_MS);
    
    #if CONFIG_SSD1306_128x64
	 // Hiển thị thông tin trên màn hình
	 ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 0xff);
    display_centered_text(&dev, 0, "Nguyen Hai Minh");  // Tên
    display_centered_text(&dev, 1, "ID: 20214006");     // ID sinh viên
    display_centered_text(&dev, 2, "Timestamp:");  // Thời gian Check-out
	display_centered_text(&dev, 2, "22:22:22");
	display_centered_text(&dev, 5, " Hello World!!");

	vTaskDelay(3000 / portTICK_PERIOD_MS);
#endif // CONFIG_SSD1306_128x64

	// Restart module
	esp_restart();
}
