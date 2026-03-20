idf_component_register(SRCS "test_blink.c" "mock_digital_io.c"
                    INCLUDE_DIRS "include"
                    REQUIRES core unity domain)