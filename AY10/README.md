## Ayudantía 10: PyOpenCL

La instalación de PyOpenCL depende de OpencCL. La instalación de esta última librería varía según los dispositivos que tengamos por lo que se puede complicar (además de que siempre existe la posibilidad de que no quede bien configurado). Es por esto que, si no queremos pasar por el proceso de instalación, podemos usar la plataforma de Google Colab como alternativa con la tarjeta gráfica NVIDIA que nos presta Google.

En particular, lo primero que se debe hacer en Google Colab es ir a 'Entorno de ejecución' -> 'Cambiar tipo de entorno de ejecución' -> 'T4 GPU'. Segundo, Google sacó hace pocos los drivers de OpenCL del entorno base de Colab, por lo que hay que instalarlos con los siguiente comandos:

    !sudo apt update
    !sudo apt install nvidia-cuda-toolkit -y

Subiendo los códigos de la ayudantía a Colab y haciendo los pasos anteriores, no debería haber problemas corriendo los códigos con PyOpenCL.

Cabe destacar que el entorno de GPU de Google Colab no es ilimitado y, por lo general, la sesión se corta después de 6 horas aproximadamente. Es importante tener esto en consideración al realizar alguna tarea del curso (también nos podemos cambiar de cuenta de Google cuando nos pasa esto).

Por último, si alguien está interesado en instalar OpenCL en su computador, podemos conversarlo y ver la instalación juntos, ya que hay varias guías en internet sobre las formas de instalar para distintos dispositivos.