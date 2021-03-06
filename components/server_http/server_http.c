#include "server_http.h"

static const char *TAG = "SERVER_HTTP.C";

static esp_err_t setConfiguration_post_handler(httpd_req_t *req)
{
    char buf[250];
    int ret, remaining = req->content_len;

    while (remaining > 0) 
    {
        /* Read the data for the request */
        if ((ret = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf)))) <= 0) 
        {
            if (ret == HTTPD_SOCK_ERR_TIMEOUT) 
            {
                /* Retry receiving if timeout occurred */
                continue;
            }
            return ESP_FAIL;
        }

        remaining -= ret;
    }

    if(jsonParseSetConfiguration(buf) == jsonParseErr)
    {
        ESP_LOGI(TAG, "jsonParseSetConfiguration did not work properly\n");
        httpd_resp_send(req, "ERROR", HTTPD_RESP_USE_STRLEN);
    }
    else
    {
        httpd_resp_send(req, "Configration set OK", HTTPD_RESP_USE_STRLEN);
    }

    return ESP_OK;
}

static const httpd_uri_t setDeviceConfig = {
    .uri       = "/SetConfiguration",
    .method    = HTTP_POST,
    .handler   = setConfiguration_post_handler,
    .user_ctx  = NULL
};

static esp_err_t setRgbProgramConfig_post_handler(httpd_req_t *req)
{
    char buf[250];
    int ret, remaining = req->content_len;

    while (remaining > 0) 
    {
        /* Read the data for the request */
        if ((ret = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf)))) <= 0) 
        {
            if (ret == HTTPD_SOCK_ERR_TIMEOUT) 
            {
                /* Retry receiving if timeout occurred */
                continue;
            }
            return ESP_FAIL;
        }

        remaining -= ret;
    }

    if(jsonParseSetRgbProgramConfiguration(buf) == jsonParseErr)
    {
        ESP_LOGI(TAG, "jsonParseSetRgbProgramConfiguration did not work properly\n");
        httpd_resp_send(req, "ERROR", HTTPD_RESP_USE_STRLEN);
    }
    else
    {
        httpd_resp_send(req, "RGB Program Config set OK", HTTPD_RESP_USE_STRLEN);
    }

    return ESP_OK;
}

static const httpd_uri_t setRgbProgramConfig = {
    .uri       = "/SetRgbProgramConfiguration",
    .method    = HTTP_POST,
    .handler   = setRgbProgramConfig_post_handler,
    .user_ctx  = NULL
};

static esp_err_t setWifi_post_handler(httpd_req_t *req)
{
    char buf[250];
    int ret, remaining = req->content_len;

    while (remaining > 0) 
    {
        /* Read the data for the request */
        if ((ret = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf)))) <= 0) 
        {
            if (ret == HTTPD_SOCK_ERR_TIMEOUT) 
            {
                /* Retry receiving if timeout occurred */
                continue;
            }
            return ESP_FAIL;
        }

        remaining -= ret;
    }

    if(jsonParseWifi(buf) == jsonParseErr)
    {
        ESP_LOGI(TAG, "jsonParseWifi did not work properly\n");
        httpd_resp_send(req, "ERROR", HTTPD_RESP_USE_STRLEN);
    }
    else
    {
        httpd_resp_send(req, "Wifi credentials received", HTTPD_RESP_USE_STRLEN);
    }

    return ESP_OK;
}

static const httpd_uri_t setWifi = {
    .uri       = "/SetWifi",
    .method    = HTTP_POST,
    .handler   = setWifi_post_handler,
    .user_ctx  = NULL
};

static esp_err_t getMeasurements_get_handler(httpd_req_t *req)
{
    const char* resp_str = (const char*) jsonBuildMeasurements();
    httpd_resp_send(req, resp_str, HTTPD_RESP_USE_STRLEN);

    if (httpd_req_get_hdr_value_len(req, "Host") == 0) 
    {
        ESP_LOGI(TAG, "Request headers lost");
    }
    return ESP_OK;
}
static const httpd_uri_t getMeasurements = {
    .uri       = "/GetMeasurements",
    .method    = HTTP_GET,
    .handler   = getMeasurements_get_handler,
    .user_ctx  = NULL
};

static esp_err_t getConfiguration_get_handler(httpd_req_t *req)
{
    const char* resp_str = (const char*) jsonBuildConfiguration();
    httpd_resp_send(req, resp_str, HTTPD_RESP_USE_STRLEN);

    if (httpd_req_get_hdr_value_len(req, "Host") == 0) 
    {
        ESP_LOGI(TAG, "Request headers lost");
    }
    return ESP_OK;
}
static const httpd_uri_t getConfiguration = {
    .uri       = "/GetConfig",
    .method    = HTTP_GET,
    .handler   = getConfiguration_get_handler,
    .user_ctx  = NULL
};

esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err)
{
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
    return ESP_FAIL;
}

static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) 
    {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &setDeviceConfig);
        httpd_register_uri_handler(server, &setRgbProgramConfig);
        httpd_register_uri_handler(server, &getMeasurements);
        httpd_register_uri_handler(server, &getConfiguration);
        httpd_register_uri_handler(server, &setWifi);
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

static void stop_webserver(httpd_handle_t server)
{
    httpd_stop(server);
}

static void disconnect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server) 
    {
        ESP_LOGI(TAG, "Stopping webserver");
        stop_webserver(*server);
        *server = NULL;
    }
}

static void connect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server == NULL) 
    {
        ESP_LOGI(TAG, "Starting webserver");
        *server = start_webserver();
    }
}

void startServerHttp(void)
{
    static httpd_handle_t server = NULL;

    /* Register event handlers to stop the server when Wi-Fi or Ethernet is disconnected,
     * and re-start it upon connection.
     */
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));

    /* Start the server for the first time */
    server = start_webserver();
}