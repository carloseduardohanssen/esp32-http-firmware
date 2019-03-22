void initTasks() {

  xTaskCreate(
    taskReadSensor,
    "readSensor",
    4096,
    NULL,
    4,
    NULL
  );

  xTaskCreate(
    taskSendData,
    "sendData",
    4096,
    NULL,
    3,
    NULL
  );

  xTaskCreate(
    taskCheckWiFi,
    "checkWiFi",
    4096,
    NULL,
    1,
    NULL
  );

#if ESP_DASH
  xTaskCreate(
    taskUpdateESPDash,   // Função que será executada
    "updateESPDash",     // Nome da tarefa
    4096,                // Tamanho da pilha
    NULL,                // Parâmetro da tarefa
    2,                   // Prioridade da tarefa
    NULL                 // Número do core que será executada a tarefa
  );
#endif
}

void taskCheckWiFi(void* p) {
  TickType_t taskDelay = 5000 / portTICK_PERIOD_MS;

  while (true) {
    DEBUG_PRINTC(F("[WiFi] Status:"));
    DEBUG_PRINTLN(WiFi.isConnected());

    vTaskDelay(taskDelay);
  }
}

void taskReadSensor(void* p) {
  TickType_t taskDelay = 2000 / portTICK_PERIOD_MS;

  while (true) {
    DEBUG_PRINTLNC(F("[Sensor] Updating the sensor data"));

    readSensor();
    vTaskDelay(taskDelay);
  }
}

void taskSendData(void* p) {
  TickType_t taskDelay = 2000 / portTICK_PERIOD_MS;

  while (true) {

    if (WiFi.status() != WL_CONNECTED) {
      DEBUG_PRINTLNC(F("[WiFi] No connection..."));
      vTaskDelay(taskDelay);
      continue;
    }

    sendData();
    DEBUG_PRINTC(F("[ESP] Memory: "));
    DEBUG_PRINTLN(ESP.getFreeHeap());

    vTaskDelay(taskDelay);
  }
}

#if ESP_DASH
void taskUpdateESPDash(void* p) {

  TickType_t taskDelay = 2500 / portTICK_PERIOD_MS; // Valor que representa 1ms, usado nos vTaskDelays

  while (true)
  {
    DEBUG_PRINTLNC(F("[DASH] Updating the esp-dash"));

    ESPDash.updateLineChart("sensor_01", x_axis, x_axis_size, y_axis, y_axis_size);
    ESPDash.updateTemperatureCard("temperature_01", random(0, 50));

    vTaskDelay(taskDelay); // Importante: A task deve conter um delay para alimentar o Watchdog
  }
}
#endif
