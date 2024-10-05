//*******************************************************************************
//  Se utiliza procesador 0 por defecto y procesador 1 en las tareas secundarias.
//
//  Usar como plantilla para tareas en simultáneo.
// (Las tareas en un mismo núcleo no se ejecutarán estrictamente en simultáneo)
//*******************************************************************************

#define LED1 2
#define LED2 4

//Declaración de tareas
TaskHandle_t Task1;
TaskHandle_t Task2;

//Función que ejecuta "Task1"
void loop1(void *parameter){  
  //Loop infinito
  while(1){ 
	  digitalWrite(LED1, 1);
	  vTaskDelay(500);
	  digitalWrite(LED1, 0);
	  vTaskDelay(500);
	  Serial.println("\t\tNúcleo utilizado-> " +  String(xPortGetCoreID()));
  }  
  vTaskDelay(10); //Para evitar WTD
}
//Función que ejecuta "Task2"
void loop2(void *parameter){  
  //Loop infinito
  while(1){ 
	  digitalWrite(LED2, 1);
	  vTaskDelay(1000);
	  digitalWrite(LED2, 0);
	  vTaskDelay(1000);
	  Serial.println("\t\t\tNúcleo utilizado-> " +  String(xPortGetCoreID()));
  }  
  vTaskDelay(10); //Para evitar WTD
}


//********************************************** SETUP **************************
void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  xTaskCreatePinnedToCore(
    loop1,			//Función que ejecuta la tarea
    "Task_1",		//Nombre de la tarea
    1000,			  //Tamaño de la pila
    NULL,			  //Parámetros que se le pasan a la tarea (NULL = Ninguno)
    1,				  //Prioridad
    &Task1,			//Nombre de la tarea
    0);				  //Procesador asignado
  
  xTaskCreatePinnedToCore(
    loop2,			//Función que ejecuta la tarea
    "Task_2",		//Nombre de la tarea
    1000,			  //Tamaño de la pila
    NULL,			  //Parámetros que se le pasan a la tarea (NULL = Ninguno)
    0,				  //Prioridad
    &Task2,			//Nombre de la tarea
    0);				  //Procesador asignado
  
}
void loop() {		//Usa procesador 1 por defecto
	Serial.println("Núcleo utilizado-> " +  String(xPortGetCoreID()));
  delay(1500);
} 