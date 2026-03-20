#include "unity.h"
#include "blink.h"
#include "digital_io.h"
#include <stdlib.h>
#include "test_blink.h"

// Estrutura para capturar o que acontece no Mock
typedef struct {
    bool last_value;
    int call_count;
} MockContext;

// Implementação do Mock (Statics para evitar conflitos)
static void mock_write(void* ctx, bool value) {
    MockContext* m_ctx = (MockContext*)ctx;
    m_ctx->last_value = value;
    m_ctx->call_count++;
}

// Caso de Teste
void test_led_on_should_call_write_with_true(void) {
    // 1. Setup (Prepara o Mock)
    MockContext m_ctx = { .last_value = false, .call_count = 0 };
    DigitalIO mock_led = {
        .ctx = &m_ctx,
        .write = mock_write,
        .read = NULL
    };

    // 2. Execute (Chama a lógica de domínio)
    led_on(&mock_led);

    // 3. Verify (Asserts do Unity)
    TEST_ASSERT_EQUAL(true, m_ctx.last_value);
    TEST_ASSERT_EQUAL(1, m_ctx.call_count);
}

void test_led_off_should_call_write_with_false(void) {
    MockContext m_ctx = { .last_value = true, .call_count = 0 };
    DigitalIO mock_led = { .ctx = &m_ctx, .write = mock_write };

    led_off(&mock_led);

    TEST_ASSERT_EQUAL(false, m_ctx.last_value);
    TEST_ASSERT_EQUAL(1, m_ctx.call_count);
}