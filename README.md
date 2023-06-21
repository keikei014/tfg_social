# Implementación de Comportamientos Sociales en un Robot Móvil
Repositorio para Trabajo de Fin de Grado "Implementación de Comportamientos Sociales en un Robot Móvil"

# Paquetes necesarios para el funcionamiento del repositorio (comandos para la versión noetic de ROS)
sudo apt install ros-noetic-fake-localization
sudo apt install ros-noetic-map-server
sudo apt install ros-noetic-dwa-local-planner
sudo apt install ros-noetic-move-base
sudo apt install ros-noetic-gmapping
sudo apt install ros-noetic-robot-state-publisher

# Listado de comportamientos sociales a implementar
1. Modificación de la velocidad del robot en función de la distancia a las personas detectadas
2. Modificación de la trayectoria del robot para no pasar entre dos personas que podrían estar hablando
   2.1 Implementar forma de detectar que dos personas están interactuando
   2.2 Alterar mapas de costes para que el planner modifique la trayectoria
3. Modificación del algoritmo de navegación para que el robot se aparte y espere para que una persona pueda pasar por un pasillo
   3.1 Implementar detección de espacios estrechos
   3.2 Cancelar navegación enviando un objetivo al que el robot se desplazará para esperar
   3.3 Implementar timer para que el robot intente pasar después de un tiempo si la persona se queda quieta
4. Modificación de la navegación del robot para que este siga a una persona si se le ordena
5. Implementar en el robot la función de acercarse a una persona para interactuar con ella
6. Implementar modo de aumentar la distancia proxémica del robot si se le pide (modificar parámetros de capa proxémica en tiempo de ejecución)
7. Modificar navegación para que el robot retroceda un poco y deje pasar en espacios MUY estrechos (se encuentra con una persona en una puerta)
