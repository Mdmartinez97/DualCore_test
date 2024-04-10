//***********************************************************************
//  Se utiliza procesador 0 por defecto y procesador 1 el segunda tarea.
//
//  Usar como plantilla para tareas en simultáneo.
//***********************************************************************

#define LED 2
#define VR 12

//Declaración de tareas
TaskHandle_t Task2;

//Función que ejecuta "Task2"
void loop2(void *parameter){  
  //Loop infinito
  for(;;){ 
	digitalWrite(LED, 1);
	delay(800);
	digitalWrite(LED, 0);
	delay(800);
	Serial.println("\t\t\tNúcleo utilizado-> " +  String(xPortGetCoreID()));
  }  
  vTaskDelay(10); //Para evitar WTD
}

//********************************************** SETUP *********************
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(VR, OUTPUT);

  xTaskCreatePinnedToCore(
    loop2,			//Función que ejecuta la tarea
    "Task_2",		//Nombre de la tarea
    1000,			  //Tamaño de la pila
    NULL,			  //Parámetros que se le pasan a la tarea (NULL = Ninguno)
    1,				  //Prioridad
    &Task2,			//Nombre de la tarea
    0);				  //Procesador asignado
}

void loop() {		//Usa procesador 1 por defecto
  digitalWrite(VR, 1);
	delay(400);
	digitalWrite(VR, 0);
	delay(400);
	Serial.println("Núcleo utilizado-> " +  String(xPortGetCoreID()));
  } 