set(app_src ssd1306.c ssd1306_spi.c ssd1306_i2c_legacy.c)

set(pre_req log driver)        # log or driver is component of SDK

idf_component_register(SRCS ${app_src}
                    INCLUDE_DIRS "."
                    REQUIRES ${pre_req})

set(idf_version "${IDF_VERSION_MAJOR}.${IDF_VERSION_MINOR}")



