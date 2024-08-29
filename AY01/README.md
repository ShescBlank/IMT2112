# AY01

Introducción a la librería Joblib y comparaciones de rendimiento.

Librerías utilizadas para esta ayudantía:
- Numpy
- Joblib

Todas estas librerías se pueden instalar usando pip (Ej: ```pip install joblib```).

También pueden usar Google Colab para correr todos los códigos.

## ¿Cómo observar la cantidad de procesos e hilos que está usando nuestro programa?

Para mirar estas dos cantidades podemos utilizar el administrador de tareas (Windows) o monitor de actividad (Mac) de nuestro computador. En específico, para los procesos basta con fijarse en cuántas instancias de Python podemos ver abiertas y trabajando (básicamente, programas con el nombre de Python). En relación a la cantidad de hilos, en Mac es sencillo ya que el mismo monitor de actividad lo dice directamente, sin embargo, en Windows esta opción está un poco más escondida y hay que seguir los siguientes pasos para poder verla:

- Abrir el Administrador de Tareas
- Ir a la pestaña de detalles
- Hacer click derecho en alguno de los nombres de las columnas y apretar "Seleccionar columnas"
- Bajar en el listado hasta encontrar la opción de "Threads" o "Subprocesos" e incluirla en el listado
- ¡Listo! Ahora podemos ver cuántos hilos está usando cada programa por separado