## Ayudantía 8: Instalación PyOpenCL

La instalación de OpenCL (y de PyOpenCL) varía según los dispositivos que tengamos por lo que puede no ser muy directa (además de que siempre existe la posibilidad de que no quede bien configurado). Es por esto que, si no queremos pasar por el proceso de instalación, podemos usar, como alternativa, la plataforma de Google Colab con la tarjeta gráfica NVIDIA TESLA T4 que nos presta Google.

En particular, lo primero que se debe hacer en Google Colab es ir a 'Entorno de ejecución' -> 'Cambiar tipo de entorno de ejecución' -> 'T4 GPU'. Segundo, Google sacó hace un tiempo los drivers de OpenCL del entorno base de Colab, por lo que hay que instalarlos con los siguiente comandos:

    !sudo apt -y update
    !sudo apt install -y nvidia-cuda-toolkit

    # Para poder también correr nuestros códigos en la CPU del entorno de GPU de Colab:
    !sudo apt install -y pocl-opencl-icd

    # Finalmente, solo nos falta instalar PyOpenCL en el entorno:
    !pip install pyopencl

Todos estos pasos se explican con mayor detalle en el notebook ```0_installation.ipynb```.

Subiendo los códigos de la ayudantía a Colab y haciendo los pasos anteriores, no debería haber problemas corriendo los códigos con PyOpenCL.

Cabe destacar que el entorno de GPU de Google Colab no es ilimitado y, por lo general, la sesión se corta después de 6 horas aproximadamente (puede variar bastante). Es importante tener esto en consideración al realizar alguna tarea del curso (también nos podemos cambiar de cuenta de Google cuando nos pasa esto).

Por último, si alguien está interesado en instalar OpenCL en su computador, podemos conversarlo y ver la instalación juntos, ya que hay varias guías en internet sobre las formas de instalarlo para distintos dispositivos.

### Correr en GPU y CPU

Para correr en ambos dispositivos, es necesario instalar los drivers de más arriba y definir un contexto para cada uno (antes utilizábamos ```ctx = cl.create_some_context()``` por defecto). Ahora:

    platforms_cuda = cl.get_platforms()[0] # GPU
    platforms_pocl = cl.get_platforms()[1] # CPU

    devices_gpu = platforms_cuda.get_devices(device_type=cl.device_type.GPU)
    devices_cpu = platforms_pocl.get_devices(device_type=cl.device_type.CPU)

    # Contexto para GPU:
    ctx_gpu = cl.Context(devices=devices_gpu)
    # Contexto para CPU:
    ctx_cpu = cl.Context(devices=devices_cpu)

    # Esto está asumiendo que la plataforma 0 es la de GPU y la 1 de CPU.
    # Pueden comprobar esto imprimiendo las plataformas antes de indexarlas.

Luego, el resto de códigos se mantienen igual. Basta con cambiar el contexto para trabajar en CPU/GPU.
