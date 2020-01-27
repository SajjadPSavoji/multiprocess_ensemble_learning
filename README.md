This project is a part of Operating Systems course Taught in University of Tehran.
The main Idea is to implement an ensemble linear classifier using multiprocessing scheme.
I've tried to implement all partes according to an objectoriented method.It's known that multiproccesing might increase cpu(followed by time and enerdy) utilization ,
if we consider this fact alongside with the parallel potenial of ensebmle classifiers, using mulriprocessing makes sense.
The roadtrack of ensemble learning is to have multi classifiers of the same type and one voter who is responsible of the final decision. In this project all the data
tarnsmissions between processe(Enseble , linear classifer , voter) uses pipes(named or unnamed).