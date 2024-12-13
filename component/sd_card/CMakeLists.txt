set(app_src sd_card.c)
set(pre_req log driver)        # log or driver is component of SDK
idf_component_register(SRCS ${app_src}
                    INCLUDE_DIRS "."
                    REQUIRES ${pre_req})