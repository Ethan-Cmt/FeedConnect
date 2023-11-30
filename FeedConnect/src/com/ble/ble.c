// ble.c
#include "ble.h"
#include <esp_bt.h>
#include <esp_gap_ble_api.h>

// Définir un nom pour votre périphérique BLE
#define DEVICE_NAME "ESP32_Device"

static esp_ble_adv_params_t ble_adv_params = {
    .adv_int_min        = 0x20,
    .adv_int_max        = 0x40,
    .adv_type           = ADV_TYPE_IND,
    .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
    .channel_map        = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
    switch (event) {
        case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
            esp_ble_gap_start_advertising(&ble_adv_params);
            break;
        default:
            break;
    }
}

void setup_ble() {
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_BLE);

    esp_bluedroid_init();
    esp_bluedroid_enable();

    esp_ble_gap_register_callback(gap_event_handler);

    // Configurer le nom du périphérique
    esp_ble_gap_set_device_name(DEVICE_NAME);

    // Configurer les données publicitaires (facultatif)
    esp_ble_gap_config_adv_data_raw(NULL, 0);
    esp_ble_gap_config_scan_rsp_data_raw(NULL, 0);

    // Configurer les paramètres d'annonce BLE
    esp_ble_gap_config_adv_params(&ble_adv_params);
}

void ble_handler() {
    // Gestionnaire des événements BLE
    // ...
}
